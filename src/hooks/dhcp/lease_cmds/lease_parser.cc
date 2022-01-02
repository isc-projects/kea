// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/data.h>
#include <dhcp/hwaddr.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_consistency.h>
#include <lease_parser.h>

#include <config.h>

using namespace std;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace lease_cmds {

Lease4Ptr
Lease4Parser::parse(ConstSrvConfigPtr& cfg,
                    const ConstElementPtr& lease_info,
                    bool& force_create) {
    if (!lease_info) {
        isc_throw(BadValue, "lease information missing");
    }

    // These are mandatory parameters.
    IOAddress addr = getAddress(lease_info, "ip-address");
    if (!addr.isV4()) {
        isc_throw(BadValue, "Non-IPv4 address specified: " << addr);
    }

    // Not a most straightforward conversion, but it works.
    string hwaddr_txt = getString(lease_info, "hw-address");
    HWAddr hwaddr = HWAddr::fromText(hwaddr_txt);
    HWAddrPtr hwaddr_ptr = HWAddrPtr(new HWAddr(hwaddr));

    // Now sort out the subnet-id. If specified, it must have correct value.
    // If not specified, Kea will try to sort it out.
    SubnetID subnet_id = 0;
    if (lease_info->contains("subnet-id")) {
        subnet_id = getUint32(lease_info, "subnet-id");
    }
    ConstSubnet4Ptr subnet;
    if (subnet_id) {
        // If subnet-id is specified, it has to match.
        subnet = cfg->getCfgSubnets4()->getBySubnetId(subnet_id);
        if (!subnet) {
            isc_throw(BadValue, "Invalid subnet-id: No IPv4 subnet with subnet-id="
                      << subnet_id << " currently configured.");
        }

        if (!subnet->inRange(addr)) {
            isc_throw(BadValue, "The address " << addr.toText() << " does not belong "
                      "to subnet " << subnet->toText() << ", subnet-id=" << subnet_id);
        }

    } else {
        // Subnet-id was not specified. Let's try to figure it out on our own.
        subnet = cfg->getCfgSubnets4()->selectSubnet(addr);
        if (!subnet) {
            isc_throw(BadValue, "subnet-id not specified and failed to find a"
                      << " subnet for address " << addr);
        }
        subnet_id = subnet->getID();
    }

    // Client-id is optional.
    ClientIdPtr client_id;
    if (lease_info->contains("client-id")) {
        string txt = getString(lease_info, "client-id");
        client_id = ClientId::fromText(txt);
    }

    // These parameters are optional. If not specified, we'll derive them from
    // the current subnet configuration, if possible.
    uint32_t valid_lft = 0;
    if (lease_info->contains("valid-lft")) {
        valid_lft = getUint32(lease_info, "valid-lft");
    } else {
        valid_lft = subnet->getValid();
    }

    /// Let's calculate client last transmission time (cltt). If expiration
    /// timestamp is specified explicitly, we will use that. Note there are no
    /// checks whether this is in the past. There may be valid cases when user
    /// wants to insert expired leases, e.g. when migrating from one DHCP server
    /// to another and wants to migrate the database as is, without discarding
    /// any leases.
    time_t cltt;
    if (lease_info->contains("expire")) {
        int64_t expire_time = getInteger(lease_info, "expire");
        if (expire_time <= 0) {
            isc_throw(BadValue , "expiration time must be positive for address "
                      << addr);

        } else if (expire_time < valid_lft) {
            isc_throw(BadValue, "expiration time must be greater than valid lifetime"
                      " for address " << addr);
        }
        cltt = static_cast<time_t>(expire_time - valid_lft);
    } else {
        cltt = time(NULL);
    }

    bool fqdn_fwd = false;
    if (lease_info->contains("fqdn-fwd")) {
        fqdn_fwd = getBoolean(lease_info, "fqdn-fwd");
    }
    bool fqdn_rev = false;
    if (lease_info->contains("fqdn-rev")) {
        fqdn_rev = getBoolean(lease_info, "fqdn-rev");
    }
    string hostname;
    if (lease_info->contains("hostname")) {
        hostname = getString(lease_info, "hostname");
    }
    if (hostname.empty() && (fqdn_fwd || fqdn_rev)) {
        isc_throw(BadValue, "No hostname specified and either forward or reverse"
                  " fqdn was set to true.");
    }

    uint32_t state = 0;
    if (lease_info->contains("state")) {
        state = getUint8(lease_info, "state");
    }

    // Check if the state value is sane.
    if (state > Lease::STATE_EXPIRED_RECLAIMED) {
        isc_throw(BadValue, "Invalid state value: " << state << ", supported "
                  "values are: 0 (default), 1 (declined) and 2 (expired-reclaimed)");
    }

    // Handle user context.
    ConstElementPtr ctx = lease_info->get("user-context");
    if (ctx && (ctx->getType() != Element::map)) {
        isc_throw(BadValue, "Invalid user context '" << ctx->str()
                  << "' is not a JSON map.");
    }

    // Handle comment.
    ConstElementPtr comment = lease_info->get("comment");
    if (comment) {
        if (ctx && ctx->contains("comment")) {
            isc_throw(BadValue, "Duplicated comment entry '" << comment->str()
                      << "' in user context '" << ctx->str() << "'");
        }
        ElementPtr copied;
        if (ctx) {
            copied = copy(ctx, 0);
        } else {
            copied = Element::createMap();
        }
        copied->set("comment", comment);
        ctx = copied;
    }

    // Let's fabricate some data and we're ready to go.

    Lease4Ptr l(new Lease4(addr, hwaddr_ptr, client_id, valid_lft,
                           cltt, subnet_id,
                           fqdn_fwd, fqdn_rev, hostname));
    l->state_ = state;
    l->setContext(ctx);

    // Retrieve the optional flag indicating if the lease must be created when it
    // doesn't exist during the update.
    force_create = false;
    if (lease_info->contains("force-create")) {
        force_create = getBoolean(lease_info, "force-create");
    }

    return (l);
}

Lease6Ptr
Lease6Parser::parse(ConstSrvConfigPtr& cfg,
                    const ConstElementPtr& lease_info,
                    bool& force_create) {
    if (!lease_info) {
        isc_throw(BadValue, "lease information missing");
    }

    // These are mandatory parameters.
    IOAddress addr = getAddress(lease_info, "ip-address");
    if (addr.isV4()) {
        isc_throw(BadValue, "Non-IPv6 address specified: " << addr);
    }

    // Not a most straightforward conversion, but it works.
    string duid_txt = getString(lease_info, "duid");
    DUID duid = DUID::fromText(duid_txt);
    DuidPtr duid_ptr = DuidPtr(new DUID(duid));

    Lease::Type type = Lease::TYPE_NA;
    uint8_t prefix_len = 128;
    if (lease_info->contains("type")) {
        string txt = getString(lease_info, "type");
        if (txt == "IA_NA") {
            type = Lease::TYPE_NA;
        } else if (txt == "IA_TA") {
            type = Lease::TYPE_TA;
        } else if (txt == "IA_PD") {
            type = Lease::TYPE_PD;

            prefix_len = getUint8(lease_info, "prefix-len");
        } else {
            isc_throw(BadValue, "Incorrect lease type: " << txt << ", the only "
                      "supported values are: na, ta and pd");
        }
    }

    // Now sort out the subnet-id. If specified, it must have correct value.
    // If not specified, Kea will try to sort it out.
    SubnetID subnet_id = 0;
    if (lease_info->contains("subnet-id")) {
        subnet_id = getUint32(lease_info, "subnet-id");
    }

    // Check if the subnet-id specified is sane.
    ConstSubnet6Ptr subnet;
    if (subnet_id) {
        // If subnet-id is specified, it has to match.
        subnet = cfg->getCfgSubnets6()->getBySubnetId(subnet_id);
        if (!subnet) {
            isc_throw(BadValue, "Invalid subnet-id: No IPv6 subnet with subnet-id="
                      << subnet_id << " currently configured.");
        }

        // Check if the address specified really belongs to the subnet.
        if ((type == Lease::TYPE_NA) && !subnet->inRange(addr)) {
            isc_throw(BadValue, "The address " << addr.toText() << " does not belong "
                      "to subnet " << subnet->toText() << ", subnet-id=" << subnet_id);
        }

    } else {
        if (type != Lease::TYPE_NA) {
            isc_throw(BadValue, "Subnet-id is 0 or not specified. This is allowed for"
                      " address leases only, not prefix leases.");
        }
        subnet = cfg->getCfgSubnets6()->selectSubnet(addr);
        if (!subnet) {
            isc_throw(BadValue, "subnet-id not specified and failed to find a "
                      "subnet for address " << addr);
        }
        subnet_id = subnet->getID();
    }

    uint32_t iaid = getUint32(lease_info, "iaid");

    // Hw-address is optional in v6 leases.
    HWAddrPtr hwaddr_ptr;
    if (lease_info->contains("hw-address")) {
        string hwaddr_txt = getString(lease_info, "hw-address");
        HWAddr hwaddr = HWAddr::fromText(hwaddr_txt);
        hwaddr_ptr = HWAddrPtr(new HWAddr(hwaddr));
    }

    // These parameters are optional. If not specified, we'll derive them
    // from the current subnet configuration, if possible.
    uint32_t valid_lft = 0;
    if (lease_info->contains("valid-lft")) {
        valid_lft = getUint32(lease_info, "valid-lft");
    } else {
        valid_lft = subnet->getValid();
    }

    // These parameters are optional. If not specified, we'll derive them
    // from the current subnet configuration, if possible.
    uint32_t pref_lft = 0;
    if (lease_info->contains("preferred-lft")) {
        pref_lft = getUint32(lease_info, "preferred-lft");
    } else {
        pref_lft = subnet->getValid();
    }

    /// Let's calculate client last transmission time (cltt). If expiration
    /// timestamp is specified explicitly, we will use that. Note there are
    /// no checks whether this is in the past. There may be valid cases when
    /// user wants to insert expired leases, e.g. when migrating from one
    /// DHCP server to another and wants to migrate the database as is, without
    /// discarding any leases.
    time_t cltt;
    if (lease_info->contains("expire")) {
        int64_t expire_time = getInteger(lease_info, "expire");
        if (expire_time <= 0) {
            isc_throw(BadValue , "expiration time must be positive for address "
                      << addr);

        } else if (expire_time < valid_lft) {
            isc_throw(BadValue, "expiration time must be greater than valid lifetime"
                      " for address " << addr);
        }

        cltt = static_cast<time_t>(expire_time - valid_lft);
    } else {
        cltt = time(NULL);
    }

    bool fqdn_fwd = false;
    if (lease_info->contains("fqdn-fwd")) {
        fqdn_fwd = getBoolean(lease_info, "fqdn-fwd");
    }
    bool fqdn_rev = false;
    if (lease_info->contains("fqdn-rev")) {
        fqdn_rev = getBoolean(lease_info, "fqdn-rev");
    }
    string hostname;
    if (lease_info->contains("hostname")) {
        hostname = getString(lease_info, "hostname");
    }
    if (hostname.empty() && (fqdn_fwd || fqdn_rev)) {
        isc_throw(BadValue, "No hostname specified and either forward or reverse"
                  " fqdn was set to true.");
    }

    uint32_t state = 0;
    if (lease_info->contains("state")) {
        state = getUint8(lease_info, "state");
    }

    // Check if the state value is sane.
    if (state > Lease::STATE_EXPIRED_RECLAIMED) {
        isc_throw(BadValue, "Invalid state value: " << state << ", supported "
                  "values are: 0 (default), 1 (declined) and 2 (expired-reclaimed)");
    }

    if ((state == Lease::STATE_DECLINED) && (type == Lease::TYPE_PD)) {
        isc_throw(isc::InvalidOperation,
                  "Invalid declined state for PD prefix.");
    }

    // Handle user context.
    ConstElementPtr ctx = lease_info->get("user-context");
    if (ctx && (ctx->getType() != Element::map)) {
        isc_throw(BadValue, "Invalid user context '" << ctx->str()
                  << "' is not a JSON map.");
    }

    // Handle comment.
    ConstElementPtr comment = lease_info->get("comment");
    if (comment) {
        if (ctx && ctx->contains("comment")) {
            isc_throw(BadValue, "Duplicated comment entry '" << comment->str()
                      << "' in user context '" << ctx->str() << "'");
        }
        ElementPtr copied;
        if (ctx) {
            copied = copy(ctx, 0);
        } else {
            copied = Element::createMap();
        }
        copied->set("comment", comment);
        ctx = copied;
    }

    // Let's fabricate some data and we're ready to go.

    Lease6Ptr l(new Lease6(type, addr, duid_ptr, iaid, pref_lft, valid_lft,
                           subnet_id, fqdn_fwd, fqdn_rev, hostname,
                           hwaddr_ptr, prefix_len));
    l->cltt_ = cltt;
    l->state_ = state;
    l->setContext(ctx);

    // Retrieve the optional flag indicating if the lease must be created when it
    // doesn't exist during the update.
    force_create = false;
    if (lease_info->contains("force-create")) {
        force_create = getBoolean(lease_info, "force-create");
    }

    return (l);
}

} // end of namespace lease_cmds
} // end of namespace isc
