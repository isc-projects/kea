// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __IOFETCH_H
#define __IOFETCH_H 1

#include <config.h>

#include <asio.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <asiolink/asiolink.h>
#include <asiolink/internal/coroutine.h>

// This file contains UDP-specific implementations of generic classes 
// defined in asiolink.h.  It is *not* intended to be part of the public
// API.

namespace asiolink {
//
// Asynchronous UDP coroutine for upstream queries
//
class IOFetch : public coroutine {
public:
    // TODO Maybe this should be more generic than just for IOFetch?
    ///
    /// \brief Result of the query
    ///
    /// This is related only to contacting the remote server. If the answer
    ///indicates error, it is still counted as SUCCESS here, if it comes back.
    ///
    enum Result {
        SUCCESS,
        TIME_OUT,
        STOPPED
    };
    /// Abstract callback for the IOFetch.
    class Callback {
    public:
        virtual ~Callback() {}

        /// This will be called when the IOFetch is completed
        virtual void operator()(Result result) = 0;
    };
    ///
    /// \brief Constructor.
    ///
    /// It creates the query.
    /// @param callback will be called when we terminate. It is your task to
    ///        delete it if allocated on heap.
    ///@param timeout in ms.
    ///
    explicit IOFetch(asio::io_service& io_service,
                      const isc::dns::Question& q,
                      const IOAddress& addr, uint16_t port,
                      isc::dns::OutputBufferPtr buffer,
                      Callback* callback, int timeout = -1);
    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);
    /// Terminate the query.
    void stop(Result reason = STOPPED);
private:
    enum { MAX_LENGTH = 4096 };

    ///
    /// \short Private data
    ///
    /// They are not private because of stability of the
    /// interface (this is private class anyway), but because this class
    /// will be copyed often (it is used as a coroutine and passed as callback
    /// to many async_*() functions) and we want keep the same data. Some of
    /// the data is not copyable too.
    ///
    struct IOFetchProtocol;
    boost::shared_ptr<IOFetchProtocol> data_;
};
}


#endif // __IOFETCH_H

// Local Variables: 
// mode: c++
// End: 
