// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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
/// @param chg_type type of change to create CHG_ADD or CHG_REMOVE
/// @param lease Pointer to a lease for which NCR should be sent.
/// @param identifier Identifier to be used to generate DHCID for
/// the DNS update. For DHCPv4 it will be hardware address or client
/// identifier. For DHCPv6 it will be a DUID.
/// @param label Client identification information in the textual format.
/// This is used for logging purposes.
/// @param subnet subnet to which the lease belongs.
///
/// @tparam LeasePtrType Pointer to a lease.
/// @tparam IdentifierType HW Address, Client Identifier or DUID.
template<typename LeasePtrType, typename IdentifierType>
void queueNCRCommon(const NameChangeType& chg_type, const LeasePtrType& lease,
                    const IdentifierType& identifier, const std::string& label,
                    NetworkPtr subnet) {
    // Check if there is a need for update.
    if (lease->hostname_.empty() || (!lease->fqdn_fwd_ && !lease->fqdn_rev_)
        || !CfgMgr::instance().getD2ClientMgr().ddnsEnabled()) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_QUEUE_NCR_SKIP)
            .arg(label)
            .arg(lease->addr_.toText());

        return;
    }

     ConflictResolutionMode conflict_resolution_mode = CHECK_WITH_DHCID;
     util::Optional<double> ddns_ttl_percent;
     if (subnet) {
         auto mode = subnet->getDdnsConflictResolutionMode();
         if (!mode.empty()) {
             conflict_resolution_mode = StringToConflictResolutionMode(mode);
         }

         ddns_ttl_percent = subnet->getDdnsTtlPercent();
     }

    try {
        // Create DHCID
        std::vector<uint8_t> hostname_wire;
        OptionDataTypeUtil::writeFqdn(lease->hostname_, hostname_wire, true);
        D2Dhcid dhcid = D2Dhcid(identifier, hostname_wire);

        // Calculate the TTL based on lease life time.
        uint32_t ttl = calculateDdnsTtl(lease->valid_lft_, ddns_ttl_percent);

        // Create name change request.
        NameChangeRequestPtr ncr
            (new NameChangeRequest(chg_type, lease->fqdn_fwd_, lease->fqdn_rev_,
                                   lease->hostname_, lease->addr_.toText(),
                                   dhcid, lease->cltt_ + ttl,
                                   ttl, conflict_resolution_mode));

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
        // Figure out from the lease's subnet if we should use conflict resolution.
        // If there's no subnet, something hinky is going on so we'll set it true.
        Subnet4Ptr subnet = CfgMgr::instance().getCurrentCfg()
                            ->getCfgSubnets4()->getSubnet(lease->subnet_id_);

        // Client id takes precedence over HW address.
        if (lease->client_id_) {
            queueNCRCommon(chg_type, lease, lease->client_id_->getClientId(),
                           Pkt4::makeLabel(lease->hwaddr_, lease->client_id_), subnet);
        } else {
            // Client id is not specified for the lease. Use HW address
            // instead.
            queueNCRCommon(chg_type, lease, lease->hwaddr_,
                           Pkt4::makeLabel(lease->hwaddr_, lease->client_id_), subnet);
        }
    }
}

void queueNCR(const NameChangeType& chg_type, const Lease6Ptr& lease) {
    // DUID is required to generate NCR.
    if (lease && (lease->type_ != Lease::TYPE_PD) && lease->duid_) {
        // Figure out from the lease's subnet if we should use conflict resolution.
        // If there's no subnet, something hinky is going on so we'll set it true.
        Subnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()
                            ->getCfgSubnets6()->getSubnet(lease->subnet_id_);
        queueNCRCommon(chg_type, lease, *(lease->duid_),
                       Pkt6::makeLabel(lease->duid_, lease->hwaddr_), subnet);
    }
}

uint32_t calculateDdnsTtl(uint32_t lease_lft, const util::Optional<double>& ddns_ttl_percent) {
    //  If we have a configured percentage use it to calculate TTL.
    if (!ddns_ttl_percent.unspecified() && (ddns_ttl_percent.get() > 0.0)) {
        uint32_t new_lft = static_cast<uint32_t>(round(ddns_ttl_percent.get() * lease_lft));
        if (new_lft > 0) {
            return (new_lft);
        } else {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL_DATA,
                      DHCPSRV_DDNS_TTL_PERCENT_TOO_SMALL)
                .arg(ddns_ttl_percent.get())
                .arg(lease_lft);
        }
    }

    // Per RFC 4702 DDNS RR TTL should be given by:
    // ((lease life time / 3) < 10 minutes) ? 10 minutes : (lease life time / 3)
    if (lease_lft < 1800) {
        return (600);
    }

    return (lease_lft / 3);
}

}
}
