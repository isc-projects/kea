// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP_SOCKET_INFO_H
#define DHCP_SOCKET_INFO_H

#include <asiolink/io_address.h>
#include <cstdint>


namespace isc {

namespace dhcp {

/// Holds information about socket.
struct SocketInfo {

    isc::asiolink::IOAddress addr_; /// bound address
    uint16_t port_;   /// socket port
    uint16_t family_; /// IPv4 or IPv6

    /// @brief Socket descriptor (a.k.a. primary socket).
    int sockfd_;

    /// @brief Fallback socket descriptor.
    ///
    /// This socket descriptor holds the handle to the fallback socket.
    /// The fallback socket is created when there is a need for the regular
    /// datagram socket to be bound to an IP address and port, besides
    /// primary socket (sockfd_) which is actually used to receive and process
    /// the DHCP messages. The fallback socket (if exists) is always associated
    /// with the primary socket. In particular, the need for the fallback socket
    /// arises when raw socket is a primary one. When primary socket is open,
    /// it is bound to an interface not the address and port. The implications
    /// include the possibility that the other process (e.g. the other instance
    /// of DHCP server) will bind to the same address and port through which the
    /// raw socket receives the DHCP messages. Another implication is that the
    /// kernel, being unaware of the DHCP server operating through the raw
    /// socket, will respond with the ICMP "Destination port unreachable"
    /// messages when DHCP messages are only received through the raw socket.
    /// In order to workaround the issues mentioned here, the fallback socket
    /// should be opened so as/ the kernel is aware that the certain address
    /// and port is in use.
    ///
    /// The fallback description is supposed to be set to a negative value if
    /// the fallback socket is closed (not open).
    int fallbackfd_;

    /// @brief SocketInfo constructor.
    ///
    /// @param addr An address the socket is bound to.
    /// @param port A port the socket is bound to.
    /// @param sockfd Socket descriptor.
    /// @param fallbackfd A descriptor of the fallback socket.
    SocketInfo(const isc::asiolink::IOAddress& addr, const uint16_t port,
               const int sockfd, const int fallbackfd = -1)
        : addr_(addr), port_(port), family_(addr.getFamily()),
          sockfd_(sockfd), fallbackfd_(fallbackfd) { }

};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP_SOCKET_INFO_H
