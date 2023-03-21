// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NCR_GENERATOR_H
#define NCR_GENERATOR_H

#include <dhcp_ddns/ncr_msg.h>
#include <dhcpsrv/lease.h>
#include <util/optional.h>

namespace isc {
namespace dhcp {

/// @brief Creates name change request from the DHCPv4 lease.
///
/// This function creates name change request from the information contained
/// in the DHCPv4 lease. If the client identifier is present in the lease,
/// this identifier is used to compute the DHCID, otherwise the HW address
/// is used.
///
/// This function is exception safe. On failure, it logs an error.
///
/// @param chg_type Type of the name change request
/// @param lease Pointer to the lease.
void queueNCR(const dhcp_ddns::NameChangeType& chg_type, const Lease4Ptr& lease);

/// @brief Creates name change request from the DHCPv6 lease.
///
/// This function creates name change request from the information contained
/// in the DHCPv6 lease. The DUID is used to compute the DHCID for the name
/// change request.
///
/// This function will skip sending the NCR if the lease type is a delegated
/// prefix.
///
/// This function is exception safe. On failure, it logs an error.
///
/// @param chg_type Type of the name change request
/// @param lease Pointer to the lease.
void queueNCR(const dhcp_ddns::NameChangeType& chg_type, const Lease6Ptr& lease);

/// @brief Calculates TTL for a DNS resource record based on lease life time.
///
/// If the parameter, ddns_ttl_percent is greater than zero, it is used to calculate
/// the TTL directly:
///
/// TTL = (lease life time * ddns-ttl-percent)
///
/// Otherwise it is calculated as per RFC 4702 Section 5:
///
/// TTL = ((lease life time / 3)  < 10 minutes) ? 10 minutes : (lease life time / 3)
///
/// @param lease_life_time valid life time of the lease
/// @param ddns_ttl_percent optional percentage to use in calculation
///
/// @return the calculated TTL.
uint32_t calculateDdnsTtl(uint32_t lease_life_time,
                          const util::Optional<double>& ddns_ttl_percent
                          = util::Optional<double>());

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // NCR_GENERATOR_H
