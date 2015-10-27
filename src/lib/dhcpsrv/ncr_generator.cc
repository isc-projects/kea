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

#include <dhcp/option_data_types.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/ncr_generator.h>
#include <stdint.h>
#include <vector>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;

namespace {

/// @brief Sends name change request to D2 using lease information.
///
/// This method is exception safe.
///
/// @param lease Pointer to a lease for which NCR should be sent.
/// @param identifier Identifier to be used to generate DHCID for
/// the DNS update. For DHCPv4 it will be hardware address or client
/// identifier. For DHCPv6 it will be a DUID.
/// @param label Client identification information in the textual format.
/// This is used for logging purposes.
///
/// @tparam LeasePtrType Pointer to a lease.
/// @tparam IdentifierType HW Address, Client Identifier or DUID.
template<typename LeasePtrType, typename IdentifierType>
void queueNCRCommon(const NameChangeType& chg_type, const LeasePtrType& lease,
                    const IdentifierType& identifier, const std::string& label) {

    // Check if there is a need for update.
    if (lease->hostname_.empty() || (!lease->fqdn_fwd_ && !lease->fqdn_rev_)
        || !CfgMgr::instance().getD2ClientMgr().ddnsEnabled()) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_QUEUE_NCR_SKIP)
            .arg(label)
            .arg(lease->addr_.toText());
            
        return;
    }

    try {
        // Create DHCID
        std::vector<uint8_t> hostname_wire;
        OptionDataTypeUtil::writeFqdn(lease->hostname_, hostname_wire, true);
        D2Dhcid dhcid = D2Dhcid(identifier, hostname_wire);

        // Create name change request.
        NameChangeRequestPtr ncr
            (new NameChangeRequest(chg_type, lease->fqdn_fwd_, lease->fqdn_rev_,
                                   lease->hostname_, lease->addr_.toText(),
                                   dhcid, lease->cltt_ + lease->valid_lft_,
                                   lease->valid_lft_));

        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL_DATA, DHCPSRV_QUEUE_NCR)
            .arg(label)
            .arg(chg_type == CHG_ADD ? "add" : "remove")
            .arg(ncr->toText());

        // Send name change request.
        CfgMgr::instance().getD2ClientMgr().sendRequest(ncr);

    } catch (const std::exception& ex) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_QUEUE_NCR_FAILED)
            .arg(label)
            .arg(chg_type == CHG_ADD ? "add" : "remove")
            .arg(lease->addr_.toText())
            .arg(ex.what());
    }
}

} // end of anonymous namespace

namespace isc {
namespace dhcp {

void queueNCR(const NameChangeType& chg_type, const Lease4Ptr& lease) {
    if (lease) {
        // Client id takes precedence over HW address.
        if (lease->client_id_) {
            queueNCRCommon(chg_type, lease, lease->client_id_->getClientId(),
                           Pkt4::makeLabel(lease->hwaddr_, lease->client_id_));

        } else {
            // Client id is not specified for the lease. Use HW address
            // instead.
            queueNCRCommon(chg_type, lease, lease->hwaddr_,
                           Pkt4::makeLabel(lease->hwaddr_, lease->client_id_));
        }
    }
}

void queueNCR(const NameChangeType& chg_type, const Lease6Ptr& lease) {
    // DUID is required to generate NCR.
    if (lease && (lease->type_ != Lease::TYPE_PD) && lease->duid_) {
        queueNCRCommon(chg_type, lease, *(lease->duid_),
                       Pkt6::makeLabel(lease->duid_, lease->hwaddr_));
    }
}

}
}
