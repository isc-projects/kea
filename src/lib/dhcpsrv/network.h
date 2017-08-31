// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETWORK_H
#define NETWORK_H

#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Common interface representing a network to which the DHCP clients
/// are connected.
///
/// The most common type of network, in Kea's terminology, is a subnet. The
/// @ref Subnet implements this interface. Another types of objects implementing
/// this interface are @ref SharedNetwork objects. They group multiple subnets
/// together to provide means for extending available address pools (a single
/// client may obtain IP address from any of the pools belonging to subnets in
/// the shared network), or for selecting a subnet on a given link, depending
/// on the class of the client (e.g. cable network case: different subnet is
/// selected for cable modems, different one for routers).
///
/// The subnets and shared networks share many data structures, e.g. DHCP
/// options, local interface name, address manipulation methods, thus this
/// class provides an abstract interface that must be implemented by derived
/// classes and, where appropriate, implements common methods used by the
/// derived classes.
class Network {
public:

    /// @brief Virtual destructor.
    ///
    /// Does nothing at the moment.
    virtual ~Network() { };

    /// @brief Sets local name of the interface for which this network is
    /// selected.
    ///
    /// If the interface is specified, the server will use the network
    /// associated with this local interface to allocate IP addresses and
    /// other resources to a client.
    ///
    /// @param iface_name Interface name.
    void setIface(const std::string& iface_name) {
        iface_name_ = iface_name;
    }

    /// @brief Returns name of the local interface for which this network is
    /// selected.
    ///
    /// @return Interface name as text.
    std::string getIface() const {
        return (iface_name_);
    };

protected:

    /// @brief Holds interface name for which this network is selected.
    std::string iface_name_;

};

/// @brief Pointer to the @ref Network object.
typedef boost::shared_ptr<Network> NetworkPtr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // NETWORK_H
