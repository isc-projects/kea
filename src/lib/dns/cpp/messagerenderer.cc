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

// $Id$

#include <cctype>
#include <cassert>
#include <set>

#include "buffer.h"
#include "name.h"
#include "messagerenderer.h"

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
    NameCompressNode(const OutputBuffer& buffer, size_t pos, size_t len) :
        buffer_(buffer), pos_(pos), len_(len) {}
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

        uint16_t pos1 = n1.pos_;
        uint16_t pos2 = n2.pos_;
        uint16_t l1 = 0;
        uint16_t l2 = 0;
        for (uint16_t i = 0; i < n1.len_; i++, pos1++, pos2++) {
            pos1 = nextPosition(n1.buffer_, pos1, l1);
            pos2 = nextPosition(n2.buffer_, pos2, l2);
            if (tolower(n1.buffer_[pos1]) < tolower(n2.buffer_[pos2])) {
                return (true);
            } else if (tolower(n1.buffer_[pos1]) > tolower(n2.buffer_[pos2])) {
                return (false);
            }
        }

        return (false);
    }

private:
    uint16_t nextPosition(const OutputBuffer& buffer,
                          uint16_t pos, uint16_t& llen) const
    {
        if (llen == 0) {
            int i = 0;

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
struct MessageRendererImpl {
    /// \brief Constructor from an output buffer.
    ///
    /// \param buffer An \c OutputBuffer object to which wire format data is
    /// written.
    MessageRendererImpl(OutputBuffer& buffer) :
        buffer_(buffer), nbuffer_(Name::MAX_WIRE) {}
    /// The buffer that holds the entire DNS message.
    OutputBuffer& buffer_;
    /// A local working buffer to convert each given name into wire format.
    /// This could be a local variable of the \c writeName() method, but
    /// we keep it in the class so that we can reuse it and avoid construction
    /// overhead.
    OutputBuffer nbuffer_;
    /// A set of compression pointers.
    std::set<NameCompressNode, NameCompare> nodeset_;
};

MessageRenderer::MessageRenderer(OutputBuffer& buffer) :
    impl_(new MessageRendererImpl(buffer))
{}

MessageRenderer::~MessageRenderer()
{
    delete impl_;
}

void
MessageRenderer::writeUint16(uint16_t data)
{
    impl_->buffer_.writeUint16(data);
}

void
MessageRenderer::writeUint32(uint32_t data)
{
    impl_->buffer_.writeUint32(data);
}

const void*
MessageRenderer::getData() const
{
    return (impl_->buffer_.getData());
}

size_t
MessageRenderer::getLength() const
{
    return (impl_->buffer_.getLength());
}

void
MessageRenderer::writeName(const Name& name, bool compress)
{
    impl_->nbuffer_.clear();
    name.toWire(impl_->nbuffer_);

    unsigned int i;
    std::set<NameCompressNode>::const_iterator n;

    // Find the longest ancestor name in the rendered set that matches the
    // given name.
    for (i = 0; i < impl_->nbuffer_.getLength(); i += impl_->nbuffer_[i] + 1) {
        // skip the trailing null label
        if (impl_->nbuffer_[i] == 0) {
            continue;
        }
        n = impl_->nodeset_.find(NameCompressNode(impl_->nbuffer_, i,
                                                  impl_->nbuffer_.getLength() -
                                                  i));
        if (n != impl_->nodeset_.end()) {
            break;
        }
    }

    // Record the current offset before extending the buffer.
    size_t offset = impl_->buffer_.getLength();
    // Write uncompress part...
    impl_->buffer_.writeData(impl_->nbuffer_.getData(),
                             compress ? i : impl_->nbuffer_.getLength());
    if (compress && n != impl_->nodeset_.end()) {
        // ...and compression pointer if available.
        uint16_t pointer = (*n).pos_;
        pointer |= Name::COMPRESS_POINTER_MARK16;
        impl_->buffer_.writeUint16(pointer);
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
        impl_->nodeset_.insert(NameCompressNode(impl_->buffer_, offset + j,
                                                impl_->nbuffer_.getLength() -
                                                j));
    }
}
}
}
