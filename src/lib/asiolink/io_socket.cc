// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include "io_socket.h"

#include <boost/asio.hpp>

namespace isc {
namespace asiolink {

/// \brief The \c DummySocket class is a concrete derived class of
/// \c IOSocket that is not associated with any real socket.
///
/// This main purpose of this class is tests, where it may be desirable to
/// instantiate an \c IOSocket object without involving system resource
/// allocation such as real network sockets.
class DummySocket : public IOSocket {
private:
    DummySocket(const DummySocket& source);
    DummySocket& operator=(const DummySocket& source);
public:
    /// \brief Constructor from the protocol number.
    ///
    /// The protocol must validly identify a standard network protocol.
    /// For example, to specify TCP \c protocol must be \c IPPROTO_TCP.
    ///
    /// \param protocol The network protocol number for the socket.
    DummySocket(const int protocol) : protocol_(protocol) {}

    /// \brief A dummy derived method of \c IOSocket::getNative().
    ///
    /// This version of method always returns -1 as the object is not
    /// associated with a real (native) socket.
    virtual int getNative() const { return (-1); }

    virtual int getProtocol() const { return (protocol_); }
private:
    const int protocol_;
};

IOSocket&
IOSocket::getDummyUDPSocket() {
    static DummySocket socket(IPPROTO_UDP);
    return (socket);
}

IOSocket&
IOSocket::getDummyTCPSocket() {
    static DummySocket socket(IPPROTO_TCP);
    return (socket);
}

} // namespace asiolink
} // namespace isc
