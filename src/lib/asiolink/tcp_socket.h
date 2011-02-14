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

#ifndef __TCP_SOCKET_H
#define __TCP_SOCKET_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/iosocket.h>

namespace asiolink {

/// \brief The \c TCPSocket class is a concrete derived class of
/// \c IOSocket that represents a TCP socket.
///
/// In the current implementation, an object of this class is always
/// instantiated within the wrapper routines.  Applications are expected to
/// get access to the object via the abstract base class, \c IOSocket.
/// This design may be changed when we generalize the wrapper interface.
class TCPSocket : public IOSocket {
private:
    TCPSocket(const TCPSocket& source);
    TCPSocket& operator=(const TCPSocket& source);
public:
    /// \brief Constructor from an ASIO TCP socket.
    ///
    /// \param socket The ASIO representation of the TCP socket.
    TCPSocket(asio::ip::tcp::socket& socket) : socket_(socket) {}

    int getNative() const { return (socket_.native()); }
    int getProtocol() const { return (IPPROTO_TCP); }

private:
    asio::ip::tcp::socket& socket_;
};


}      // namespace asiolink
#endif // __TCP_SOCKET_H
