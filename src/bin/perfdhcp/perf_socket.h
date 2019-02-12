// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PERF_SOCKET_H
#define PERF_SOCKET_H

#include <dhcp/socket_info.h>

namespace isc {
namespace perfdhcp {


/// \brief Socket wrapper structure.
///
/// This is the wrapper that holds descriptor of the socket
/// used to run DHCP test. The wrapped socket is closed in
/// the destructor. This prevents resource leaks when
/// function that created the socket ends (normally or
/// when exception occurs). This structure extends parent
/// structure with new field ifindex_ that holds interface
/// index where socket is bound to.
struct PerfSocket : public dhcp::SocketInfo {
    /// Interface index.
    uint16_t ifindex_;

    /// \brief Constructor of socket wrapper class.
    ///
    /// This constructor uses provided socket descriptor to
    /// find the name of the interface where socket has been
    /// bound to.
    PerfSocket();

    /// \brief Destructor of the socket wrapper class.
    ///
    /// Destructor closes wrapped socket.
    virtual ~PerfSocket();

private:
    /// \brief Initialize socket data.
    ///
    /// This method initializes members of the class that Interface
    /// Manager holds: interface name, local address.
    ///
    /// \throw isc::BadValue if interface for specified socket
    /// descriptor does not exist.
    void initSocketData();

    /// \brief Open socket to communicate with DHCP server.
    ///
    /// Method opens socket and binds it to local address. Function will
    /// use either interface name, local address or server address
    /// to create a socket, depending on what is available (specified
    /// from the command line). If socket can't be created for any
    /// reason, exception is thrown.
    /// If destination address is broadcast (for DHCPv4) or multicast
    /// (for DHCPv6) than broadcast or multicast option is set on
    /// the socket. Opened socket is registered and managed by IfaceMgr.
    ///
    /// \throw isc::BadValue if socket can't be created for given
    /// interface, local address or remote address.
    /// \throw isc::InvalidOperation if broadcast option can't be
    /// set for the v4 socket or if multicast option can't be set
    /// for the v6 socket.
    /// \throw isc::Unexpected if internal unexpected error occurred.
    /// \return socket descriptor.
    int openSocket() const;
};

}
}

#endif /* PERF_SOCKET_H */
