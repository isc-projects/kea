// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
