// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ADAPTOR_SUBNET_H
#define ISC_ADAPTOR_SUBNET_H 1

#include <dhcpsrv/subnet_id.h>
#include <yang/adaptor.h>

namespace isc {
namespace yang {

/// @brief JSON adaptor for subnets adding IDs and canonizes relays.
///
/// Adding IDs is done in two passes walking through subnets.
///  -1- Add in the set used values and return false when there is no ID
///      so the caller can decide if the second pass is needed.
///  -2- For a subnet without an ID, assigned the next unused ID.
///
/// Note as all canonization adaptors it is optional, i.e., code should work
/// without it.
class AdaptorSubnet {
public:
    /// @brief Destructor.
    virtual ~AdaptorSubnet() = default;

    /// @brief Collect a subnet ID.
    ///
    /// @param subnet The subnet.
    /// @param set The reference to the set of assigned IDs.
    /// @return True if the subnet has an ID, false otherwise.
    static bool collectID(isc::data::ConstElementPtr subnet,
                          isc::dhcp::SubnetIDSet& set);

    /// @brief Assign subnet ID.
    ///
    /// @param subnet The subnet.
    /// @param set The reference to the set of assigned IDs.
    /// @param next The next ID.
    static void assignID(isc::data::ElementPtr subnet,
                         isc::dhcp::SubnetIDSet& set,
                         isc::dhcp::SubnetID& next);

    /// @brief Update relay.
    ///
    /// Can be used for shared networks too.
    ///
    /// @param subnet The subnet.
    static void updateRelay(isc::data::ElementPtr subnet);
};  // AdaptorSubnet

}  // namespace yang
}  // namespace isc

#endif  // ISC_ADAPTOR_SUBNET_H
