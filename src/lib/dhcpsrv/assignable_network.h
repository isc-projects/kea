// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ASSIGNABLE_NETWORK_H
#define ASSIGNABLE_NETWORK_H

#include <dhcpsrv/network.h>

namespace isc {
namespace dhcp {

/// @brief Represents a network that can be associated with a subnet.
///
/// This class represents a network that can be associated with a subnet
/// using @c Subnet::setSharedNetwork method. This class is a friend
/// of a @ref Subnet class, so it can call its @c Subnet::setSharedNetwork
/// private method. Association of a network with a subnet must be always
/// conducted using this class. This prevents unwanted replacements of
/// shared networks within subnets.
class AssignableNetwork {
protected:

    /// @brief Virtual destructor.
    virtual ~AssignableNetwork() { }

    /// @brief Returns shared pointer to this object.
    ///
    /// This abstract method must be implemented by derived classes to
    /// return shared pointers the derivation.
    ///
    /// @return Pointer to this network.
    virtual NetworkPtr sharedFromThis() = 0;

    /// @brief Associates a subnet with this network.
    ///
    /// @param subnet Pointer to a subnet to be associated with the network.
    ///
    /// @tparam SubnetPtr Type of the subnet pointer.
    template<typename SubnetPtr>
    void setSharedNetwork(const SubnetPtr& subnet) {
        subnet->setSharedNetwork(sharedFromThis());
    }

    /// @brief Removes association of a subnet with a network.
    ///
    /// @param subnet Pointer to a subnet for which association should be
    /// removed.
    ///
    /// @tparam SubnetPtr Type of the subnet pointer.
    template<typename SubnetPtr>
    void clearSharedNetwork(const SubnetPtr& subnet) {
        subnet->setSharedNetwork(NetworkPtr());
    }
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // ASSIGNABLE_NETWORK_H
