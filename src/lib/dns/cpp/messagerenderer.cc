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

#include <iostream>

#include "buffer.h"
#include "name.h"
#include "messagerenderer.h"

namespace isc {
namespace dns {

struct NameCompressNode {
    NameCompressNode(const OutputBuffer& buffer, size_t pos, size_t len) :
        buffer_(buffer), pos_(pos), len_(len) {}
    const OutputBuffer& buffer_;
    uint16_t pos_;
    uint16_t len_;
};

///
/// Helper class to give ordering for MessageRendererImpl::nodeset_.
///
struct NameCompare : public std::binary_function<NameCompressNode,
                                                 NameCompressNode,
                                                 bool> {
    ///
    /// Returns true if n1 < n2 as a result of case-insensitive comparison;
    /// otherwise return false.
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

    uint16_t nextPosition(const OutputBuffer& buffer,
                          uint16_t pos, uint16_t& llen) const
    {
        if (llen == 0) {
            int i = 0;
            while ((buffer[pos] & 0xc0) == 0xc0) {
                pos = (buffer[pos] & 0x3f) * 256 + buffer[pos + 1];

                // This loop should stop as long as the buffer has been
                // constructed validly and the search/insert argument is based
                // on a valid name, which is an assumption for this class.
                // But we'll abort if a bug could cause an infinite loop.
                i += 2;
                assert(i < Name::MAX_WIRE);
            }
            llen = buffer[pos];
        } else
            --llen;
        return (pos);
    }
};

struct MessageRendererImpl {
    MessageRendererImpl(OutputBuffer& buffer) :
        buffer_(buffer), nbuffer_(Name::MAX_WIRE) {}
    OutputBuffer& buffer_;
    OutputBuffer nbuffer_;
    std::set<NameCompressNode, NameCompare> nodeset_;
};

MessageRenderer::MessageRenderer(OutputBuffer& buffer)
{
    impl_ = new MessageRendererImpl(buffer);
}

MessageRenderer::~MessageRenderer()
{
    delete impl_;
}

void
MessageRenderer::writeName(const Name& name, bool compress)
{
    impl_->nbuffer_.clear();
    name.toWire(impl_->nbuffer_);

    unsigned int i;
    std::set<NameCompressNode>::const_iterator n;

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

    size_t offset = impl_->buffer_.getLength();
    // write uncompress part...
    impl_->buffer_.writeData(impl_->nbuffer_.getData(),
                             compress ? i : impl_->nbuffer_.getLength());
    if (compress && n != impl_->nodeset_.end()) {
        // ...and compression pointer if available.
        uint16_t pointer = (*n).pos_;
        pointer |= 0xc000;
        impl_->buffer_.writeUint16(pointer);
    }

    for (unsigned int j = 0; j < i; j += impl_->nbuffer_[j] + 1) {
        if (impl_->nbuffer_[j] == 0) {
            continue;
        }
        if (offset + j >= 0x4000) {
            break;
        }
        impl_->nodeset_.insert(NameCompressNode(impl_->buffer_, offset + j,
                                                impl_->nbuffer_.getLength() -
                                                j));
    }
}
}
}
