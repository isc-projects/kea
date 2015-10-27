// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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
