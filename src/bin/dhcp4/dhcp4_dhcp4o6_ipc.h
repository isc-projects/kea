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

#ifndef DHCP4_DHCP4O6_IPC_H
#define DHCP4_DHCP4O6_IPC_H

/// @file dhcp4_dhcp4o6_ipc.h Defines the Dhcp4o6Ipc class.
/// This file defines the class Kea uses to act as the DHCPv4 server
/// side of DHCPv4-over-DHCPv6 communication between servers.
///

#include <dhcp/pkt4o6.h>
#include <dhcpsrv/dhcp4o6_ipc.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Handles DHCPv4-over-DHCPv6 IPC on the DHCPv4 server side
class Dhcp4to6Ipc : public Dhcp4o6IpcBase {
protected:
    /// @brief Constructor
    ///
    /// Default constructor
    Dhcp4to6Ipc();

    /// @brief Destructor.
    virtual ~Dhcp4to6Ipc() { }

public:
    /// @brief Returns pointer to the sole instance of Dhcp4o6Ipc
    ///
    /// Dhcp4to6Ipc is a singleton class
    ///
    /// @return the only existing instance of DHCP4o6 IPC
    static Dhcp4to6Ipc& instance();

    /// @brief Open communication socket
    ///
    /// Call base open method and sets the handler/callback when needed
    virtual void open();

    /// @brief On receive handler
    ///
    /// The handler processes the DHCPv4-query DHCPv6 packet and
    /// sends the DHCPv4-response DHCPv6 packet back to the DHCPv6 server
    static void handler();

    /// @brief Returns last received packet
    ///
    /// @return a reference to a shared pointer to the last received packet
    /// @note This reference should be cleared after use
    Pkt4o6Ptr& getReceived();

private:
    /// @brief last received packet
    Pkt4o6Ptr received_;
};

} // namespace isc
} // namespace dhcp

#endif
