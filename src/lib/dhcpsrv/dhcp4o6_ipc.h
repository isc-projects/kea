// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCP4O6_IPC_H
#define DHCP4O6_IPC_H

/// @file dhcp4o6_ipc.h Defines the Dhcp4o6IpcBase class.
/// This file defines the class Kea uses as a base for
/// DHCPv4-over-DHCPv6 communication between servers.
///
#include <dhcp/pkt6.h>

#include <boost/noncopyable.hpp>

#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief 
///
class Dhcp4o6IpcBase : public boost::noncopyable {
protected:
    /// @brief Constructor
    ///
    /// Default constructor
    Dhcp4o6IpcBase();

    /// @brief Destructor.
    virtual ~Dhcp4o6IpcBase();

    /// @brief Open communication socket (from base class)
    ///
    /// @param port port number to use (0 for disabled)
    /// @param side side of the server (4 or 6)
    ///
    /// @return new socket descriptor
    int open(uint16_t port, int side);

public:
    /// @brief Open communication socket (for derived classes)
    virtual void open() = 0;

    /// @brief Close communication socket
    void close();

    /// @brief Receive IPC message
    ///
    /// @return a pointer to a DHCPv6 message with interface and remote
    /// address set from the IPC message
    Pkt6Ptr receive();

    /// @brief Send IPC message
    ///
    /// @param a pointer to a DHCPv6 message with interface and remote
    /// address set for the IPC message
    void send(Pkt6Ptr pkt);

protected:
    /// @brief Port number
    uint16_t port_;

    /// @brief Socket descriptor
    int socket_fd_;
};

} // namespace isc
} // namespace dhcp

#endif
