// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NCR_GENERATOR_H
#define NCR_GENERATOR_H

#include <dhcp_ddns/ncr_msg.h>
#include <dhcpsrv/lease.h>

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

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // NCR_GENERATOR_H
