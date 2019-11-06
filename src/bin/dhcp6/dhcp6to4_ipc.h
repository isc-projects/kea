// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP6TO4_IPC_H
#define DHCP6TO4_IPC_H

/// @file dhcp6to4_ipc.h Defines the Dhcp6to4Ipc class.
/// This file defines the class Kea uses to act as the DHCPv6 server
/// side of DHCPv4-over-DHCPv6 communication between servers.
///
#include <dhcpsrv/dhcp4o6_ipc.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Handles DHCPv4-over-DHCPv6 IPC on the DHCPv6 server side
class Dhcp6to4Ipc : public Dhcp4o6IpcBase {
protected:
    /// @brief Constructor
    ///
    /// Default constructor
    Dhcp6to4Ipc();

    /// @brief Destructor.
    virtual ~Dhcp6to4Ipc() { }

public:
    /// @brief Returns pointer to the sole instance of Dhcp6to4Ipc
    ///
    /// Dhcp6to4Ipc is a singleton class
    ///
    /// @return the only existing instance of DHCP4o6 IPC
    static Dhcp6to4Ipc& instance();

    /// @brief Open communication socket
    ///
    /// Call base open method and sets the handler/callback when needed
    virtual void open();

    /// @brief On receive handler
    ///
    /// The handler sends the DHCPv6 packet back to the remote address
    static void handler(int /* fd */);

    /// @param client_port UDP port where all responses are sent to.
    /// Not zero is mostly useful for testing purposes.
    static uint16_t client_port;
};

} // namespace isc
} // namespace dhcp

#endif
