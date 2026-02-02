// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/str.h>

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
                    const ConstSubnetPtr subnet) {
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
    util::Optional<uint32_t> ddns_ttl;
    util::Optional<uint32_t> ddns_ttl_min;
    util::Optional<uint32_t> ddns_ttl_max;
    if (subnet) {
        // Create a DdnsParams so we have access to pool scope values.
        DdnsParams ddns_params(subnet, true);
        static_cast<void>(ddns_params.setPoolFromAddress(lease->addr_));

        auto mode = ddns_params.getConflictResolutionMode();
        if (!mode.empty()) {
            conflict_resolution_mode = StringToConflictResolutionMode(mode);
        }

        ddns_ttl_percent = ddns_params.getTtlPercent();
        ddns_ttl = ddns_params.getTtl();
        ddns_ttl_min = ddns_params.getTtlMin();
        ddns_ttl_max = ddns_params.getTtlMax();
    }

    try {
        // Create DHCID
        std::vector<uint8_t> hostname_wire;
        OptionDataTypeUtil::writeFqdn(lease->hostname_, hostname_wire, true);
        D2Dhcid dhcid = D2Dhcid(identifier, hostname_wire);

        // Calculate the TTL based on lease life time.
        uint32_t ttl = calculateDdnsTtl(lease->valid_lft_,
                                        ddns_ttl_percent, ddns_ttl,
                                        ddns_ttl_min, ddns_ttl_max);

        // Create name change request.
        NameChangeRequestPtr ncr
            (new NameChangeRequest(chg_type, lease->fqdn_fwd_, lease->fqdn_rev_,
                                   lease->hostname_, lease->addr_.toText(),
                                   dhcid, ttl, conflict_resolution_mode));

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
        ConstSubnet4Ptr subnet = CfgMgr::instance().getCurrentCfg()
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
        ConstSubnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()
                            ->getCfgSubnets6()->getSubnet(lease->subnet_id_);
        queueNCRCommon(chg_type, lease, *(lease->duid_),
                       Pkt6::makeLabel(lease->duid_, lease->hwaddr_), subnet);
    }
}

uint32_t calculateDdnsTtl(uint32_t lease_lft,
                          const util::Optional<double>& ddns_ttl_percent,
                          const util::Optional<uint32_t>& ddns_ttl,
                          const util::Optional<uint32_t>& ddns_ttl_min,
                          const util::Optional<uint32_t>& ddns_ttl_max) {
    //  If we have an explicit value use it.
    if (!ddns_ttl.unspecified() && ddns_ttl.get() > 0) {
        return (ddns_ttl.get());
    }

    // Use specified percentage (if one) or 1/3 as called for in RFC 4702.
    double ttl_percent = (ddns_ttl_percent.get() > 0.0 ?
                          ddns_ttl_percent.get() :  0.33333);

    // Calculate the ttl.
    uint32_t ttl = static_cast<uint32_t>(round(ttl_percent * lease_lft));

    // Adjust for minimum and maximum.
    // If we have a custom minimum enforce it, otherwise per RFC 4702 it
    // should not less than 600.
    uint32_t ttl_min = (ddns_ttl_min.get() > 0) ? ddns_ttl_min.get() : 600;
    if (ttl < ttl_min) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL_DATA,
                      DHCPSRV_DDNS_TTL_TOO_SMALL)
                  .arg(util::str::dumpDouble(ttl_percent))
                  .arg(lease_lft)
                  .arg(ttl)
                  .arg(ttl_min);
        return (ttl_min);
    }

    // If we have a maximum enforce it.
    uint32_t ttl_max = ddns_ttl_max.get();
    if (ttl_max && ttl > ttl_max) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL_DATA,
                      DHCPSRV_DDNS_TTL_TOO_LARGE)
                     .arg(util::str::dumpDouble(ttl_percent))
                     .arg(lease_lft)
                     .arg(ttl)
                     .arg(ttl_max);
        return (ttl_max);
    }

    return (ttl);
}

}
}
