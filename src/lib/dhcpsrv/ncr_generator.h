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
/// The logic for calculating TTL is as follow:
///
/// If ddns-ttl is specified use it unconditionally.
///
/// If ddns-ttl-percnet is specified use it otherwise use 1/3 as
/// called for by RFC 4702.
///
/// Calculate the candidate TTL based on the deteremined percentage.
///
/// If ddsn-ttl-min is specified used it otherwise use a minimum of
/// 600 per RFC 4702.  If the TTL is less than the mininum return
/// the minimum.
///
/// If ddsn-ttl-max is specified limit the ttl to that value otherwse
/// return the ttl.
///
/// @param lease_life_time valid life time of the lease
/// @param ddns_ttl_percent optional percentage to use in calculation
/// @param ddns_ttl optional percentage to use in calculation
/// @param ddns_ttl_min optional minium TTL to allow
/// @param ddns_ttl_max optional maximum TTL to allow
///
/// @return the calculated TTL.
uint32_t calculateDdnsTtl(uint32_t lease_life_time,
                          const util::Optional<double>& ddns_ttl_percent
                          = util::Optional<double>(),
                          const util::Optional<uint32_t>& ddns_ttl
                          = util::Optional<uint32_t>(),
                          const util::Optional<uint32_t>& ddns_ttl_min
                          = util::Optional<uint32_t>(),
                          const util::Optional<uint32_t>& ddns_ttl_max
                          = util::Optional<uint32_t>());

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // NCR_GENERATOR_H
