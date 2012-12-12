// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DUMMY_IO_CB_H
#define DUMMY_IO_CB_H

#include <iostream>

#include <asio/error.hpp>
#include <asio/error_code.hpp>

namespace isc {
namespace asiolink {

/// \brief Asynchronous I/O Completion Callback
///
/// The two socket classes (UDPSocket and TCPSocket) require that the I/O
/// completion callback function have an operator() method with the appropriate
/// signature.  The classes are templates, any class with that method and
/// signature can be passed as the callback object - there is no need for a
/// base class defining the interface.  However, some users of the socket
/// classes do not use the asynchronous I/O operations, yet have to supply a
/// template parameter.  This is the reason for this class - it is the dummy
/// template parameter.

class DummyIOCallback {
public:

    /// \brief Asynchronous I/O callback method
    ///
    /// TODO: explain why this method should never be called.
    /// This should be unused.
    void operator()(asio::error_code)
    {
        // TODO: log an error if this method ever gets called.
    }

    /// \brief Asynchronous I/O callback method
    ///
    /// TODO: explain why this method should never be called.
    /// This should be unused.
    void operator()(asio::error_code, size_t)
    {
        // TODO: log an error if this method ever gets called.
    }
};

} // namespace asiolink
} // namespace isc

#endif // DUMMY_IO_CB_H
