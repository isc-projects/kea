// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ADAPTOR_POOL_H
#define ISC_ADAPTOR_POOL_H 1

#include <yang/adaptor.h>

namespace isc {
namespace yang {

/// @brief JSON adaptor for pools between canonical Kea and YANG models.
///
/// First adaptor canonizePool checks and fixes if needed the pool entry
/// to a canonical form which is no space for prefix and one space each
/// side of the minus character for ranges.
///
/// Second adaptor is specific to the IETF DHCPv6 model (and does nothing
/// with a Kea DHCP model): it moves timer definitions from the subnet scope,
/// i.e. the scope where they are in Kea, to the pool scope, i.e. the scope
/// where they are in the IETF model, and back. The from way leaves timers
/// in the subnet scope as they are ignored by the translator, the to way
/// removes timers from pools as they are not expected by Kea at this scope.
class AdaptorPool {
public:
    /// @brief Destructor.
    virtual ~AdaptorPool() = default;

    /// @brief Canonize pool.
    ///
    /// Remove spaces and replace "-" by " - " for readability.
    /// @param pool The pool.
    static void canonizePool(isc::data::ElementPtr pool);

    /// @brief Moves parameters from subnets to pools.
    ///
    /// Move parameters from the subnet to each pool. Currently the only
    /// supported model is ietf-dhcpv6-server. The parameters moved are
    /// valid-lifetime, preferred-lifetime, renew-timer, rebind-timer.
    ///
    /// @param model Model name.
    /// @param subnet The subnet element.
    /// @param pools The children pools.
    /// @throw NotImplemented on unexpected model.
    static void fromSubnet(const std::string& model,
                           isc::data::ConstElementPtr subnet,
                           isc::data::ConstElementPtr pools);

    /// @brief Move parameters from pools to the subnet.
    ///
    /// Move parameters from pool to its parent subnet. Currently the only
    /// supported model is ietf-dhcpv6-server. The parameters moved are
    /// valid-lifetime, preferred-lifetime, renew-timer, rebind-timer.
    ///
    /// @note: currently it is the only from YANG to JSON aka
    /// post-processing adaptor.
    ///
    /// @param model Model name.
    /// @param subnet The subnet element.
    /// @param pools The children pools.
    /// @throw NotImplemented on unexpected model.
    /// @throw BadValue on inconsistent (different timer values) pools.
    static void toSubnet(const std::string& model,
                         isc::data::ElementPtr subnet,
                         isc::data::ConstElementPtr pools);

protected:
    /// @brief From subnets for ietf-dhcpv6-server.
    ///
    /// Use common and move valid-lifetime and preferred-lifetime.
    ///
    /// @param subnet The subnet element.
    /// @param pools The children pools.
    static void fromSubnetIetf6(isc::data::ConstElementPtr subnet,
                                isc::data::ConstElementPtr pools);

    /// @brief To subnet for ietf-dhcpv6-server.
    ///
    /// Use common and move valid-lifetime and preferred-lifetime.
    ///
    /// @param subnet The subnet element.
    /// @param pools The children pools.
    static void toSubnetIetf6(isc::data::ElementPtr subnet,
                              isc::data::ConstElementPtr pools);
};  // AdaptorPool

}  // namespace yang
}  // namespace isc

#endif  // ISC_ADAPTOR_POOL_H
