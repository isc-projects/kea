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

#ifndef __MESSAGERENDERERHANDLE_H
#define __MESSAGERENDERERHANDLE_H 1

#include <dns/messagerenderer.h>

namespace isc {

namespace dns {

/// The \c MessageRendererHandle is a handle class for
/// \c MessageRendere.
///
/// A \c MessageRendererHandle object is constructed with a \c MessageRenderer
/// object.
class MessageRendererHandle {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private.
    //@{
private:
    MessageRendererHandle(const MessageRendererHandle& renderer);
    MessageRendererHandle& operator=(const MessageRendererHandle& renderer);
public:
    /// The constructor.
    ///
    /// \param use_cache Whether to enable hot spot cache for lookup results.
    /// \param xfrout_client Communication interface with a separate xfrout
    /// process.  It's normally a reference to an xfr::XfroutClient object,
    /// but can refer to a local mock object for te
    explicit MessageRendererHandle():renderer_(NULL){
        renderer_ = new MessageRenderer();
    }
    ~MessageRendererHandle() {
        if(NULL != renderer_) {
            delete renderer_;
            renderer_ = NULL;
        }
    }
    //@}
public:
    /// \brief Return the length of data written in the internal buffer.
    size_t getLength() const {
           return (renderer_->getLength());
    }
    /// \brief Set the buffer.
    void setBuffer(isc::util::OutputBuffer* buffer) {
        renderer_->setBuffer(buffer);
    }
    MessageRenderer& getRenderer() const {
        return *renderer_;
    }
    /// \brief Set the maximum length of rendered data that can fit in the
    /// corresponding DNS message without truncation.
    ///
    /// \param len The maximum length in bytes.
    void setLengthLimit(size_t len) {
        renderer_->setLengthLimit(len);
    }
private:
    MessageRenderer * renderer_;
};
}
}
#endif // __MESSAGERENDERERHANDLE_H

// Local Variables:
// mode: c++
// End:
