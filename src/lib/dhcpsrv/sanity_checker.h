// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SANITY_CHECKER_H
#define SANITY_CHECKER_H

#include <dhcpsrv/lease.h>
#include <dhcpsrv/cfg_consistency.h>

namespace isc {
namespace dhcp {

/// @brief Code used to conduct various sanity checks. Currently used for leases.
///
/// This class is expected to be used as a simple interface sanity checker for
/// various run-time and configuration elements. Currently is provides sanity
/// checking and correction for subnet-id parameter in leases.
///
/// @note: the extended info checker for leases is in the lease manager.
class SanityChecker {
public:

    /// @brief Sanity checks and possibly corrects an IPv4 lease
    ///
    /// Depending on the sanity-checks/lease-checks parameter value (see
    /// @ref CfgConsistency for details), this code may print a warning,
    /// correct subnet-id or discard the lease.
    ///
    /// @param lease Lease to be sanity-checked
    /// @param current specify whether to use current (true) or staging
    ///        (false) config
    void checkLease(Lease4Ptr& lease, bool current = true);

    /// @brief Sanity checks and possibly corrects an IPv6 lease
    ///
    /// Depending on the sanity-checks/lease-checks parameter value (see
    /// @ref CfgConsistency for details), this code may print a warning,
    /// correct subnet-id or discard the lease.  Note that if the lease
    /// type is TYPE_PD, it simply returns.
    ///
    /// @param lease Lease to be sanity-checked
    /// @param current specify whether to use current (true) or staging
    ///        (false) config
    void checkLease(Lease6Ptr& lease, bool current = true);

    /// @brief Indicates the specified configuration enables lease sanity checking.
    ///
    /// @param current specifies whether to use current (true) or staging(false)
    /// server configuration
    /// @return true if the sanity-checks/lease-checks parameter value (see
    /// @ref CfgConsistency for details) is not CfgConsistency::LEASE_CHECK_NONE.
    static bool leaseCheckingEnabled(bool current = true);

 private:

    /// @brief Internal implementation for checkLease command
    ///
    /// @tparam LeaseType type of the lease (Lease4Ptr or Lease6Ptr)
    /// @tparam SubnetsType type of the subnets container (CfgSubnets4Ptr or
    ///         CfgSubnets6Ptr)
    /// @param lease a lease to be checked/corrected
    /// @param checks a pointer to CfgConsistency structure (type of checks
    ///        specified here)
    /// @param subnets configuration structure with subnets
    template<typename LeaseType, typename SubnetsType>
    void checkLeaseInternal(LeaseType& lease, const CfgConsistencyPtr& checks,
                            const SubnetsType& subnets);

    /// @brief Internal method for finding appropriate subnet-id
    ///
    /// @tparam LeaseType type of the lease (Lease4Ptr or Lease6Ptr)
    /// @tparam SubnetsType type of the subnets container (CfgSubnets4Ptr or
    ///         CfgSubnets6Ptr)
    /// @param lease a lease to be checked/corrected
    /// @param subnets configuration structure with subnets
    template<typename LeaseType, typename SubnetsType>
    SubnetID findSubnetId(const LeaseType& lease, const SubnetsType& subnets);
};

}
}

#endif /* SANITY_CHECKER_H */
