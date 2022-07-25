// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ADAPTOR_SUBNET_H
#define ISC_ADAPTOR_SUBNET_H 1

#include <yang/adaptor.h>
#include <dhcpsrv/subnet_id.h>
#include <set>

namespace isc {
namespace yang {

/// @brief Set of SubnetIDs.
typedef std::set<isc::dhcp::SubnetID> SubnetIDSet;

/// @brief JSON adaptor for subnets adding IDs and canonizes relays.
///
/// Adding IDs is done in two passes walking through subnets.
///  -1- Add in the set used values and return false when there is no ID
///      so the caller can decide if the second pass is needed.
///  -2- For a subnet without an ID, assigned the next unused ID.
///
/// For relays an old syntax ip-address is translated into a new syntax
/// ip-addresses. Note as all canonization adaptor it is optional, i.e.,
/// code should work without it.
class AdaptorSubnet {
public:

    /// @brief Constructor.
    AdaptorSubnet();

    /// @brief Destructor.
    virtual ~AdaptorSubnet();

    /// @brief Collect a subnet ID.
    ///
    /// @param subnet The subnet.
    /// @param set The reference to the set of assigned IDs.
    /// @return True if the subnet has an ID, false otherwise.
    static bool collectID(isc::data::ConstElementPtr subnet, SubnetIDSet& set);

    /// @brief Assign subnet ID.
    ///
    /// @param subnet The subnet.
    /// @param set The reference to the set of assigned IDs.
    /// @param next The next ID.
    static void assignID(isc::data::ElementPtr subnet, SubnetIDSet& set,
                         isc::dhcp::SubnetID& next);

    /// @brief Update relay.
    ///
    /// Force the use of ip-addresses when it finds an ip-address entry.
    /// Can be used for shared networks too.
    ///
    /// @param subnet The subnet.
    static void updateRelay(isc::data::ElementPtr subnet);
};

}  // end of namespace isc::yang
}  // end of namespace isc

#endif // ISC_ADAPTOR_SUBNET_H
