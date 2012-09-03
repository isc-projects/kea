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

#ifndef __OLDMESSAGERENDERER_H
#define __OLDMESSAGERENDERER_H 1

//
// This is a copy of an older version of MessageRenderer class.  It is kept
// here to provide a benchmark target.
//

#include <dns/messagerenderer.h>

namespace isc {
namespace dns {

class OldMessageRenderer : public AbstractMessageRenderer {
public:
    using AbstractMessageRenderer::CASE_INSENSITIVE;
    using AbstractMessageRenderer::CASE_SENSITIVE;

    /// \brief Constructor from an output buffer.
    OldMessageRenderer();

    virtual ~OldMessageRenderer();
    virtual bool isTruncated() const;
    virtual size_t getLengthLimit() const;
    virtual CompressMode getCompressMode() const;
    virtual void setTruncated();
    virtual void setLengthLimit(size_t len);
    virtual void setCompressMode(CompressMode mode);
    virtual void clear();
    virtual void writeName(const Name& name, bool compress = true);
    virtual void writeName(const LabelSequence& labels, bool compress);
private:
    struct MessageRendererImpl;
    MessageRendererImpl* impl_;
};
}
}
#endif // __OLDMESSAGERENDERER_H

// Local Variables:
// mode: c++
// End:
