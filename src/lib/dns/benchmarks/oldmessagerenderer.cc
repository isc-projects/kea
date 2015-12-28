// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <dns/name.h>
#include <dns/labelsequence.h>
#include <oldmessagerenderer.h>

#include <cctype>
#include <cassert>
#include <set>

using namespace isc::util;

namespace isc {
namespace dns {

namespace {     // hide internal-only names from the public namespaces
///
/// \brief The \c NameCompressNode class represents a pointer to a name
/// rendered in the internal buffer for the \c MessageRendererImpl object.
///
/// A \c MessageRendererImpl object maintains a set of the \c NameCompressNode
/// objects, and searches the set for the position of the longest match
/// (ancestor) name against each new name to be rendered into the buffer.
struct NameCompressNode {
    NameCompressNode(const OldMessageRenderer& renderer,
                     const OutputBuffer& buffer, const size_t pos,
                     const size_t len) :
        renderer_(renderer), buffer_(buffer), pos_(pos), len_(len) {}
    /// The renderer that performs name compression using the node.
    /// This is kept in each node to detect the compression mode
    /// (case-sensitive or not) in the comparison functor (\c NameCompare).
    const OldMessageRenderer& renderer_;
    /// The buffer in which the corresponding name is rendered.
    const OutputBuffer& buffer_;
    /// The position (offset from the beginning) in the buffer where the
    /// name starts.
    uint16_t pos_;
    /// The length of the corresponding name.
    uint16_t len_;
};

///
/// \brief The \c NameCompare class is a functor that gives ordering among
/// \c NameCompressNode objects stored in \c MessageRendererImpl::nodeset_.
///
/// Its only public method as a functor, \c operator(), gives the ordering
/// between two \c NameCompressNode objects in terms of equivalence, that is,
/// returns whether one is "less than" the other.
/// For our purpose we only need to distinguish two different names, so the
/// ordering is different from the canonical DNS name order used in DNSSEC;
/// basically, it gives the case-insensitive ordering of the two names as their
/// textual representation.
struct NameCompare : public std::binary_function<NameCompressNode,
                                                 NameCompressNode,
                                                 bool> {
    ///
    /// Returns true if n1 < n2 as a result of case-insensitive comparison;
    /// otherwise return false.
    ///
    /// The name corresponding to \c n1 or \c n2 may be compressed, in which
    /// case we must follow the compression pointer in the associated buffer.
    /// The helper private method \c nextPosition() gives the position in the
    /// buffer for the next character, taking into account compression.
    ///
    bool operator()(const NameCompressNode& n1,
                    const NameCompressNode& n2) const
    {
        if (n1.len_ < n2.len_) {
            return (true);
        } else if (n1.len_ > n2.len_) {
            return (false);
        }

        const bool case_sensitive =
            (n1.renderer_.getCompressMode() == OldMessageRenderer::CASE_SENSITIVE);

        uint16_t pos1 = n1.pos_;
        uint16_t pos2 = n2.pos_;
        uint16_t l1 = 0;
        uint16_t l2 = 0;
        for (uint16_t i = 0; i < n1.len_; i++, pos1++, pos2++) {
            pos1 = nextPosition(n1.buffer_, pos1, l1);
            pos2 = nextPosition(n2.buffer_, pos2, l2);
            if (case_sensitive) {
                if (n1.buffer_[pos1] < n2.buffer_[pos2]) {
                    return (true);
                } else if (n1.buffer_[pos1] > n2.buffer_[pos2]) {
                    return (false);
                }
            } else {
                if (tolower(n1.buffer_[pos1]) < tolower(n2.buffer_[pos2])) {
                    return (true);
                } else if (tolower(n1.buffer_[pos1]) >
                           tolower(n2.buffer_[pos2])) {
                    return (false);
                }
            }
        }

        return (false);
    }

private:
    uint16_t nextPosition(const OutputBuffer& buffer,
                          uint16_t pos, uint16_t& llen) const
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
};
}

///
/// \brief The \c MessageRendererImpl class is the actual implementation of
/// \c MessageRenderer.
///
/// The implementation is hidden from applications.  We can refer to specific
/// members of this class only within the implementation source file.
///
struct OldMessageRenderer::MessageRendererImpl {
    /// \brief Constructor from an output buffer.
    ///
    MessageRendererImpl() :
        nbuffer_(Name::MAX_WIRE), msglength_limit_(512),
        truncated_(false), compress_mode_(OldMessageRenderer::CASE_INSENSITIVE)
    {}
    /// A local working buffer to convert each given name into wire format.
    /// This could be a local variable of the \c writeName() method, but
    /// we keep it in the class so that we can reuse it and avoid construction
    /// overhead.
    OutputBuffer nbuffer_;
    /// A set of compression pointers.
    std::set<NameCompressNode, NameCompare> nodeset_;
    /// The maximum length of rendered data that can fit without
    /// truncation.
    uint16_t msglength_limit_;
    /// A boolean flag that indicates truncation has occurred while rendering
    /// the data.
    bool truncated_;
    /// The name compression mode.
    CompressMode compress_mode_;
};

OldMessageRenderer::OldMessageRenderer() :
    AbstractMessageRenderer(),
    impl_(new MessageRendererImpl)
{}

OldMessageRenderer::~OldMessageRenderer() {
    delete impl_;
}

void
OldMessageRenderer::clear() {
    AbstractMessageRenderer::clear();
    impl_->nbuffer_.clear();
    impl_->nodeset_.clear();
    impl_->msglength_limit_ = 512;
    impl_->truncated_ = false;
    impl_->compress_mode_ = CASE_INSENSITIVE;
}

size_t
OldMessageRenderer::getLengthLimit() const {
    return (impl_->msglength_limit_);
}

void
OldMessageRenderer::setLengthLimit(const size_t len) {
    impl_->msglength_limit_ = len;
}

bool
OldMessageRenderer::isTruncated() const {
    return (impl_->truncated_);
}

void
OldMessageRenderer::setTruncated() {
    impl_->truncated_ = true;
}

OldMessageRenderer::CompressMode
OldMessageRenderer::getCompressMode() const {
    return (impl_->compress_mode_);
}

void
OldMessageRenderer::setCompressMode(const CompressMode mode) {
    impl_->compress_mode_ = mode;
}

void
OldMessageRenderer::writeName(const Name& name, const bool compress) {
    impl_->nbuffer_.clear();
    name.toWire(impl_->nbuffer_);

    unsigned int i;
    std::set<NameCompressNode, NameCompare>::const_iterator notfound =
        impl_->nodeset_.end();
    std::set<NameCompressNode, NameCompare>::const_iterator n = notfound;

    // Find the longest ancestor name in the rendered set that matches the
    // given name.
    for (i = 0; i < impl_->nbuffer_.getLength(); i += impl_->nbuffer_[i] + 1) {
        // skip the trailing null label
        if (impl_->nbuffer_[i] == 0) {
            continue;
        }
        n = impl_->nodeset_.find(NameCompressNode(*this, impl_->nbuffer_, i,
                                                  impl_->nbuffer_.getLength() -
                                                  i));
        if (n != notfound) {
            break;
        }
    }

    // Record the current offset before extending the buffer.
    const size_t offset = getLength();
    // Write uncompress part...
    writeData(impl_->nbuffer_.getData(),
              compress ? i : impl_->nbuffer_.getLength());
    if (compress && n != notfound) {
        // ...and compression pointer if available.
        uint16_t pointer = (*n).pos_;
        pointer |= Name::COMPRESS_POINTER_MARK16;
        writeUint16(pointer);
    }

    // Finally, add to the set the newly rendered name and its ancestors that
    // have not been in the set.
    for (unsigned int j = 0; j < i; j += impl_->nbuffer_[j] + 1) {
        if (impl_->nbuffer_[j] == 0) {
            continue;
        }
        if (offset + j > Name::MAX_COMPRESS_POINTER) {
            break;
        }
        impl_->nodeset_.insert(NameCompressNode(*this, getBuffer(),
                                                offset + j,
                                                impl_->nbuffer_.getLength() -
                                                j));
    }
}

void
OldMessageRenderer::writeName(const LabelSequence&, const bool) {
    // We shouldn't use this version of writeName (and we internally
    // control it, so we simply assert it here)
    assert(false);
}

}
}
