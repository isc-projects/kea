// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OLDMESSAGERENDERER_H
#define OLDMESSAGERENDERER_H 1

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
#endif // OLDMESSAGERENDERER_H

// Local Variables:
// mode: c++
// End:
