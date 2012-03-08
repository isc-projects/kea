// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/expmessagerenderer.h>

#include <cassert>
#include <vector>

using namespace std;
using namespace isc::util;

namespace isc {
namespace dns {

///
/// \brief The \c MessageRendererImpl class is the actual implementation of
/// \c MessageRenderer.
///
/// The implementation is hidden from applications.  We can refer to specific
/// members of this class only within the implementation source file.
///
/// It internally holds a hash table for LabelSequence objects corresponding
/// to portions of names rendered in this renderer with their offset from
/// the beginning to the entire rendered data.  It's used to handle name
/// compression.
struct ExpMessageRenderer::MessageRendererImpl {
    // The size of hash buckets
    static const size_t BUCKETS = 64;
    // Number of hash entries per bucket for which space is preallocated and
    // keep reserved for subsequent rendering, inneding to provide better
    // performance.
    static const size_t RESERVED_ITEMS = 16;
    static const uint16_t NO_OFFSET = 65535; // used as a marker of 'not found'

    // Structure used as hash entries
    struct OffsetItem {
        OffsetItem(const LabelSequence& labels_param, uint16_t offset_param) :
            labels(labels_param), offset(offset_param)
        {}
        LabelSequence labels;
        uint16_t offset;
    };

    MessageRendererImpl() :
        msglength_limit_(512), truncated_(false),
        compress_mode_(ExpMessageRenderer::CASE_INSENSITIVE)
    {
        // Reserve some spaces for hash and name placeholders.
        for (size_t i = 0; i < BUCKETS; ++i) {
            table_[i].reserve(RESERVED_ITEMS);
        }
        names_.reserve(BUCKETS);
    }

    // A helper structure to find the hash entry whose labelsequence is
    // equal to the search key ("target").
    struct SequenceComp {
        SequenceComp(const LabelSequence& target, bool case_sensitive) :
            target_(target), case_sensitive_(case_sensitive)
        {}
        bool operator()(const OffsetItem& item) const {
            return (item.labels.equals(target_, case_sensitive_));
        }
    private:
        const LabelSequence& target_;
        bool case_sensitive_;
    };

    uint16_t findOffset(const LabelSequence& sequence) const {
        const bool case_sensitive = (compress_mode_ ==
                                     ExpMessageRenderer::CASE_SENSITIVE);
        const size_t bucket = (sequence.getHash(case_sensitive) % BUCKETS);

        // Find a matching entry, if any.  We use some heuristics here: often
        // the same name appers consecutively (like repeating the same owner
        // name for a single RRset), so in case there's a collision in the
        // bucket it will be more likely to find it in the tail side of the
        // bucket.
        vector<OffsetItem>::const_reverse_iterator found =
            find_if(table_[bucket].rbegin(), table_[bucket].rend(),
                    SequenceComp(sequence, case_sensitive));
        if (found != table_[bucket].rend()) {
            return (found->offset);
        }
        return (NO_OFFSET);
    }

    void addOffset(const LabelSequence& sequence, uint16_t offset) {
        const bool case_sensitive = (compress_mode_ ==
                                     ExpMessageRenderer::CASE_SENSITIVE);
        const size_t bucket = (sequence.getHash(case_sensitive) % BUCKETS);
        table_[bucket].push_back(OffsetItem(sequence, offset));
    }

    /// The maximum length of rendered data that can fit without
    /// truncation.
    uint16_t msglength_limit_;
    /// A boolean flag that indicates truncation has occurred while rendering
    /// the data.
    bool truncated_;
    /// The name compression mode.
    CompressMode compress_mode_;

    // The hash table for the (LabelSequence * offset) entries
    vector<OffsetItem> table_[BUCKETS];
    // Placeholder for names referenced from the stored LabelSequences
    vector<Name> names_;
};

ExpMessageRenderer::ExpMessageRenderer() :
    AbstractMessageRenderer(),
    impl_(new MessageRendererImpl)
{}

ExpMessageRenderer::~ExpMessageRenderer() {
    delete impl_;
}

void
ExpMessageRenderer::clear() {
    AbstractMessageRenderer::clear();
    impl_->msglength_limit_ = 512;
    impl_->truncated_ = false;
    impl_->compress_mode_ = CASE_INSENSITIVE;

    // Clear the hash table and name placeholders.  We reserve the minimum
    // space for possible subsequent use of the renderer.
    for (size_t i = 0; i < MessageRendererImpl::BUCKETS; ++i) {
        if (impl_->table_[i].size() > MessageRendererImpl::RESERVED_ITEMS) {
            impl_->table_[i].reserve(MessageRendererImpl::RESERVED_ITEMS);
            vector<MessageRendererImpl::OffsetItem>(impl_->table_[i].begin(),
                                                    impl_->table_[i].end()).
                swap(impl_->table_[i]);
        }
        impl_->table_[i].clear();
    }
    if (impl_->names_.size() > MessageRendererImpl::BUCKETS) {
        impl_->names_.reserve(MessageRendererImpl::BUCKETS);
        vector<Name>(impl_->names_.begin(), impl_->names_.end()).
            swap(impl_->names_);
    }
    impl_->names_.clear();
}

size_t
ExpMessageRenderer::getLengthLimit() const {
    return (impl_->msglength_limit_);
}

void
ExpMessageRenderer::setLengthLimit(const size_t len) {
    impl_->msglength_limit_ = len;
}

bool
ExpMessageRenderer::isTruncated() const {
    return (impl_->truncated_);
}

void
ExpMessageRenderer::setTruncated() {
    impl_->truncated_ = true;
}

ExpMessageRenderer::CompressMode
ExpMessageRenderer::getCompressMode() const {
    return (impl_->compress_mode_);
}

void
ExpMessageRenderer::setCompressMode(const CompressMode mode) {
    if (!impl_->names_.empty()) {
        isc_throw(isc::InvalidParameter,
                  "compress mode cannot be changed during rendering");
    }
    impl_->compress_mode_ = mode;
}

void
ExpMessageRenderer::writeName(const Name& name, const bool compress) {
    LabelSequence sequence(name);
    const size_t nlabels = sequence.getLabelCount();
    size_t data_len;
    const char* data;

    // Find the offset in the offset table whose name gives the longest
    // match against the name to be rendered.
    size_t nlabels_uncomp;
    uint16_t ptr_offset = MessageRendererImpl::NO_OFFSET;
    for (nlabels_uncomp = 0; nlabels_uncomp < nlabels; ++nlabels_uncomp) {
        if (sequence.getDataLength() == 1) { // trailing dot.
            ++nlabels_uncomp;
            break;
        }
        ptr_offset = impl_->findOffset(sequence);
        if (ptr_offset != MessageRendererImpl::NO_OFFSET) {
            break;
        }
        sequence.stripLeft(1);
    }

    // Record the current offset before updating the offset table
    size_t offset = getLength();
    // Write uncompress part:
    if (nlabels_uncomp > 0 || !compress) {
        LabelSequence uncomp_sequence(name);
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

    // Finally, add the newly rendered name and its ancestors that
    // have not been in the set.  We need to make our copy of name and generate
    // sequence(s) from the copied name because it's not guaranteed that
    // the caller keeps the name valid after this call.
    if (nlabels_uncomp > 0) {
        impl_->names_.push_back(name);
        LabelSequence saved_sequence(impl_->names_.back());
        size_t seqlen = saved_sequence.getDataLength();
        while (nlabels_uncomp-- > 0) {
            if (seqlen == 1) { // root name doesn't need to be stored.
                break;
            }
            if (offset > Name::MAX_COMPRESS_POINTER) {
                break;
            }
            impl_->addOffset(saved_sequence, offset);
            saved_sequence.stripLeft(1);
            const size_t new_seqlen = saved_sequence.getDataLength();
            offset += (seqlen - new_seqlen);
            seqlen = new_seqlen;
        }
    }
}

}
}
