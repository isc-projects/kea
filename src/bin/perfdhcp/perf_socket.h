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
    /// Is socket valid. It will not be valid if the provided socket
    /// descriptor does not point to valid socket.
    bool valid_;

    /// \brief Constructor of socket wrapper class.
    ///
    /// This constructor uses provided socket descriptor to
    /// find the name of the interface where socket has been
    /// bound to. If provided socket descriptor is invalid then
    /// valid_ field is set to false;
    ///
    /// \param socket socket descriptor.
    PerfSocket(const int socket);

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
};

}
}

#endif /* PERF_SOCKET_H */
