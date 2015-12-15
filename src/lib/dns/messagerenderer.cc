// Copyright (C) 2009, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <dns/name.h>
#include <dns/name_internal.h>
#include <dns/labelsequence.h>
#include <dns/messagerenderer.h>

#include <boost/array.hpp>
#include <boost/static_assert.hpp>

#include <limits>
#include <cassert>
#include <vector>

using namespace std;
using namespace isc::util;
using isc::dns::name::internal::maptolower;

namespace isc {
namespace dns {

namespace {     // hide internal-only names from the public namespaces
///
/// \brief The \c OffsetItem class represents a pointer to a name
/// rendered in the internal buffer for the \c MessageRendererImpl object.
///
/// A \c MessageRendererImpl object maintains a set of \c OffsetItem
/// objects in a hash table, and searches the table for the position of the
/// longest match (ancestor) name against each new name to be rendered into
/// the buffer.
struct OffsetItem {
    OffsetItem(size_t hash, size_t pos, size_t len) :
        hash_(hash), pos_(pos), len_(len)
    {}

    /// The hash value for the stored name calculated by LabelSequence.getHash.
    /// This will help make name comparison in \c NameCompare more efficient.
    size_t hash_;

    /// The position (offset from the beginning) in the buffer where the
    /// name starts.
    uint16_t pos_;

    /// The length of the corresponding sequence (which is a domain name).
    uint16_t len_;
};

/// \brief The \c NameCompare class is a functor that checks equality
/// between the name corresponding to an \c OffsetItem object and the name
/// consists of labels represented by a \c LabelSequence object.
///
/// Template parameter CASE_SENSITIVE determines whether to ignore the case
/// of the names.  This policy doesn't change throughout the lifetime of
/// this object, so we separate these using template to avoid unnecessary
/// condition check.
template <bool CASE_SENSITIVE>
struct NameCompare {
    /// \brief Constructor
    ///
    /// \param buffer The buffer for rendering used in the caller renderer
    /// \param name_buf An input buffer storing the wire-format data of the
    /// name to be newly rendered (and only that data).
    /// \param hash The hash value for the name.
    NameCompare(const OutputBuffer& buffer, InputBuffer& name_buf,
                size_t hash) :
        buffer_(&buffer), name_buf_(&name_buf), hash_(hash)
    {}

    bool operator()(const OffsetItem& item) const {
        // Trivial inequality check.  If either the hash or the total length
        // doesn't match, the names are obviously different.
        if (item.hash_  != hash_ || item.len_ != name_buf_->getLength()) {
            return (false);
        }

        // Compare the name data, character-by-character.
        // item_pos keeps track of the position in the buffer corresponding to
        // the character to compare.  item_label_len is the number of
        // characters in the labels where the character pointed by item_pos
        // belongs.  When it reaches zero, nextPosition() identifies the
        // position for the subsequent label, taking into account name
        // compression, and resets item_label_len to the length of the new
        // label.
        name_buf_->setPosition(0); // buffer can be reused, so reset position
        uint16_t item_pos = item.pos_;
        uint16_t item_label_len = 0;
        for (size_t i = 0; i < item.len_; ++i, ++item_pos) {
            item_pos = nextPosition(*buffer_, item_pos, item_label_len);
            const uint8_t ch1 = (*buffer_)[item_pos];
            const uint8_t ch2 = name_buf_->readUint8();
            if (CASE_SENSITIVE) {
                if (ch1 != ch2) {
                    return (false);
                }
            } else {
                if (maptolower[ch1] != maptolower[ch2]) {
                    return (false);
                }
            }
        }

        return (true);
    }

private:
    static uint16_t nextPosition(const OutputBuffer& buffer,
                                 uint16_t pos, uint16_t& llen)
    {
        if (llen == 0) {
            size_t i = 0;

            while ((buffer[pos] & Name::COMPRESS_POINTER_MARK8) ==
                   Name::COMPRESS_POINTER_MARK8) {
                pos = (buffer[pos] & ~Name::COMPRESS_POINTER_MARK8) *
                    256 + buffer[pos + 1];

                // This loop should stop as long as the buffer has been
                // constructed validly and the search/insert argument is based
                // on a valid name, which is an assumption for this class.
                // But we'll abort if a bug could cause an infinite loop.
                i += 2;
                assert(i < Name::MAX_WIRE);
            }
            llen = buffer[pos];
        } else {
            --llen;
        }
        return (pos);
    }

    const OutputBuffer* buffer_;
    InputBuffer* name_buf_;
    const size_t hash_;
};
}

///
/// \brief The \c MessageRendererImpl class is the actual implementation of
/// \c MessageRenderer.
///
/// The implementation is hidden from applications.  We can refer to specific
/// members of this class only within the implementation source file.
///
/// It internally holds a hash table for OffsetItem objects corresponding
/// to portions of names rendered in this renderer.  The offset information
/// is used to compress subsequent names to be rendered.
struct MessageRenderer::MessageRendererImpl {
    // The size of hash buckets and number of hash entries per bucket for
    // which space is preallocated and kept reserved for subsequent rendering
    // to provide better performance.  These values are derived from the
    // BIND 9 implementation that uses a similar hash table.
    static const size_t BUCKETS = 64;
    static const size_t RESERVED_ITEMS = 16;
    static const uint16_t NO_OFFSET = 65535; // used as a marker of 'not found'

    /// \brief Constructor
    MessageRendererImpl() :
        msglength_limit_(512), truncated_(false),
        compress_mode_(MessageRenderer::CASE_INSENSITIVE)
    {
        // Reserve some spaces for hash table items.
        for (size_t i = 0; i < BUCKETS; ++i) {
            table_[i].reserve(RESERVED_ITEMS);
        }
    }

    uint16_t findOffset(const OutputBuffer& buffer, InputBuffer& name_buf,
                        size_t hash, bool case_sensitive) const
    {
        // Find a matching entry, if any.  We use some heuristics here: often
        // the same name appears consecutively (like repeating the same owner
        // name for a single RRset), so in case there's a collision in the
        // bucket it will be more likely to find it in the tail side of the
        // bucket.
        const size_t bucket_id = hash % BUCKETS;
        vector<OffsetItem>::const_reverse_iterator found;
        if (case_sensitive) {
            found = find_if(table_[bucket_id].rbegin(),
                            table_[bucket_id].rend(),
                            NameCompare<true>(buffer, name_buf, hash));
        } else {
            found = find_if(table_[bucket_id].rbegin(),
                            table_[bucket_id].rend(),
                            NameCompare<false>(buffer, name_buf, hash));
        }
        if (found != table_[bucket_id].rend()) {
            return (found->pos_);
        }
        return (NO_OFFSET);
    }

    void addOffset(size_t hash, size_t offset, size_t len) {
        table_[hash % BUCKETS].push_back(OffsetItem(hash, offset, len));
    }

    // The hash table for the (offset + position in the buffer) entries
    vector<OffsetItem> table_[BUCKETS];
    /// The maximum length of rendered data that can fit without
    /// truncation.
    uint16_t msglength_limit_;
    /// A boolean flag that indicates truncation has occurred while rendering
    /// the data.
    bool truncated_;
    /// The name compression mode.
    CompressMode compress_mode_;

    // Placeholder for hash values as they are calculated in writeName().
    // Note: we may want to make it a local variable of writeName() if it
    // works more efficiently.
    boost::array<size_t, Name::MAX_LABELS> seq_hashes_;
};

MessageRenderer::MessageRenderer() :
    AbstractMessageRenderer(),
    impl_(new MessageRendererImpl)
{}

MessageRenderer::~MessageRenderer() {
    delete impl_;
}

void
MessageRenderer::clear() {
    AbstractMessageRenderer::clear();
    impl_->msglength_limit_ = 512;
    impl_->truncated_ = false;
    impl_->compress_mode_ = CASE_INSENSITIVE;

    // Clear the hash table.  We reserve the minimum space for possible
    // subsequent use of the renderer.
    for (size_t i = 0; i < MessageRendererImpl::BUCKETS; ++i) {
        if (impl_->table_[i].size() > MessageRendererImpl::RESERVED_ITEMS) {
            // Trim excessive capacity: swap ensures the new capacity is only
            // reasonably large for the reserved space.
            vector<OffsetItem> new_table;
            new_table.reserve(MessageRendererImpl::RESERVED_ITEMS);
            new_table.swap(impl_->table_[i]);
        }
        impl_->table_[i].clear();
    }
}

size_t
MessageRenderer::getLengthLimit() const {
    return (impl_->msglength_limit_);
}

void
MessageRenderer::setLengthLimit(const size_t len) {
    impl_->msglength_limit_ = len;
}

bool
MessageRenderer::isTruncated() const {
    return (impl_->truncated_);
}

void
MessageRenderer::setTruncated() {
    impl_->truncated_ = true;
}

MessageRenderer::CompressMode
MessageRenderer::getCompressMode() const {
    return (impl_->compress_mode_);
}

void
MessageRenderer::setCompressMode(const CompressMode mode) {
    if (getLength() != 0) {
        isc_throw(isc::InvalidParameter,
                  "compress mode cannot be changed during rendering");
    }
    impl_->compress_mode_ = mode;
}

void
MessageRenderer::writeName(const LabelSequence& ls, const bool compress) {
    LabelSequence sequence(ls);
    const size_t nlabels = sequence.getLabelCount();
    size_t data_len;
    const uint8_t* data;

    // Find the offset in the offset table whose name gives the longest
    // match against the name to be rendered.
    size_t nlabels_uncomp;
    uint16_t ptr_offset = MessageRendererImpl::NO_OFFSET;
    const bool case_sensitive = (impl_->compress_mode_ ==
                                 MessageRenderer::CASE_SENSITIVE);
    for (nlabels_uncomp = 0; nlabels_uncomp < nlabels; ++nlabels_uncomp) {
        if (nlabels_uncomp > 0) {
            sequence.stripLeft(1);
        }

        data = sequence.getData(&data_len);
        if (data_len == 1) { // trailing dot.
            ++nlabels_uncomp;
            break;
        }
        // write with range check for safety
        impl_->seq_hashes_.at(nlabels_uncomp) =
            sequence.getHash(impl_->compress_mode_);
        InputBuffer name_buf(data, data_len);
        ptr_offset = impl_->findOffset(getBuffer(), name_buf,
                                       impl_->seq_hashes_[nlabels_uncomp],
                                       case_sensitive);
        if (ptr_offset != MessageRendererImpl::NO_OFFSET) {
            break;
        }
    }

    // Record the current offset before updating the offset table
    size_t offset = getLength();
    // Write uncompress part:
    if (nlabels_uncomp > 0 || !compress) {
        LabelSequence uncomp_sequence(ls);
        if (compress && nlabels > nlabels_uncomp) {
            // If there's compressed part, strip off that part.
            uncomp_sequence.stripRight(nlabels - nlabels_uncomp);
        }
        data = uncomp_sequence.getData(&data_len);
        writeData(data, data_len);
    }
    // And write compression pointer if available:
    if (compress && ptr_offset != MessageRendererImpl::NO_OFFSET) {
        ptr_offset |= Name::COMPRESS_POINTER_MARK16;
        writeUint16(ptr_offset);
    }

    // Finally, record the offset and length for each uncompressed sequence
    // in the hash table.  The renderer's buffer has just stored the
    // corresponding data, so we use the rendered data to get the length
    // of each label of the names.
    size_t seqlen = ls.getDataLength();
    for (size_t i = 0; i < nlabels_uncomp; ++i) {
        const uint8_t label_len = getBuffer()[offset];
        if (label_len == 0) { // offset for root doesn't need to be stored.
            break;
        }
        if (offset > Name::MAX_COMPRESS_POINTER) {
            break;
        }
        // Store the tuple of <hash, offset, len> to the table.  Note that we
        // already know the hash value for each name.
        impl_->addOffset(impl_->seq_hashes_[i], offset, seqlen);
        offset += (label_len + 1);
        seqlen -= (label_len + 1);
    }
}

void
MessageRenderer::writeName(const Name& name, const bool compress) {
    const LabelSequence ls(name);
    writeName(ls, compress);
}

AbstractMessageRenderer::AbstractMessageRenderer() :
    local_buffer_(0), buffer_(&local_buffer_)
{
}

void
AbstractMessageRenderer::setBuffer(OutputBuffer* buffer) {
    if (buffer != NULL && buffer_->getLength() != 0) {
        isc_throw(isc::InvalidParameter,
                  "MessageRenderer buffer cannot be set when in use");
    }
    if (buffer == NULL && buffer_ == &local_buffer_) {
        isc_throw(isc::InvalidParameter,
                  "Default MessageRenderer buffer cannot be reset");
    }

    if (buffer == NULL) {
        // Reset to the default buffer, then clear other internal resources.
        // The order is important; we need to keep the used buffer intact.
        buffer_ = &local_buffer_;
        clear();
    } else {
        buffer_ = buffer;
    }
}

void
AbstractMessageRenderer::clear() {
    buffer_->clear();
}

}
}
