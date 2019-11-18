// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP4TO6_IPC_H
#define DHCP4TO6_IPC_H

/// @file dhcp4to6_ipc.h Defines the Dhcp4o6Ipc class.
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
    /// @brief Returns pointer to the sole instance of Dhcp4to6Ipc
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
    static void handler(int /* fd */);
};

} // namespace isc
} // namespace dhcp

#endif
