// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/data.h>
#include <dhcp/hwaddr.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/lease.h>
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
    SubnetID subnet_id = getUint32(lease_info, "subnet-id");

    if (!addr.isV4()) {
        isc_throw(BadValue, "Non-IPv4 address specified: " << addr);
    }

    // Not a most straightforward conversion, but it works.
    string hwaddr_txt = getString(lease_info, "hw-address");
    HWAddr hwaddr = HWAddr::fromText(hwaddr_txt);
    HWAddrPtr hwaddr_ptr = HWAddrPtr(new HWAddr(hwaddr));

    Subnet4Ptr subnet = cfg->getCfgSubnets4()->getSubnet(subnet_id);
    if (!subnet) {
        isc_throw(BadValue, "Invalid subnet-id: No IPv4 subnet with subnet-id="
                  << subnet_id << " currently configured.");
    }

    if (!subnet->inRange(addr)) {
        isc_throw(BadValue, "The address " << addr.toText() << " does not belong "
                  "to subnet " << subnet->toText() << ", subnet-id=" << subnet_id);
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
        int64_t tmp = getUint32(lease_info, "expire");
        cltt = static_cast<time_t>(tmp - valid_lft);
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

    // Let's fabricate some data and we're ready to go.
    uint32_t t1 = subnet->getT1();
    uint32_t t2 = subnet->getT2();

    Lease4Ptr l(new Lease4(addr, hwaddr_ptr, client_id, valid_lft, t1, t2,
                           cltt, subnet_id,
                           fqdn_fwd, fqdn_rev, hostname));
    l->state_ = state;

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
    SubnetID subnet_id = getUint32(lease_info, "subnet-id");

    if (addr.isV4()) {
        isc_throw(BadValue, "Non-IPv6 address specified: " << addr);
    }

    // Not a most straightforward conversion, but it works.
    string duid_txt = getString(lease_info, "duid");
    DUID duid = DUID::fromText(duid_txt);
    DuidPtr duid_ptr = DuidPtr(new DUID(duid));

    // Check if the subnet-id specified is sane.
    Subnet6Ptr subnet = cfg->getCfgSubnets6()->getSubnet(subnet_id);
    if (!subnet) {
        isc_throw(BadValue, "Invalid subnet-id: No IPv6 subnet with subnet-id="
                  << subnet_id << " currently configured.");
    }

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

    // Check if the address specified really belongs to the subnet.
    if ((type == Lease::TYPE_NA) && !subnet->inRange(addr)) {
        isc_throw(BadValue, "The address " << addr.toText() << " does not belong "
                  "to subnet " << subnet->toText() << ", subnet-id=" << subnet_id);
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
        int64_t tmp = getUint32(lease_info, "expire");
        cltt = static_cast<time_t>(tmp - valid_lft);
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

    // Let's fabricate some data and we're ready to go.
    uint32_t t1 = subnet->getT1();
    uint32_t t2 = subnet->getT2();

    Lease6Ptr l(new Lease6(type, addr, duid_ptr, iaid, pref_lft, valid_lft, t1, t2,
                           subnet_id, fqdn_fwd, fqdn_rev, hostname,
                           hwaddr_ptr, prefix_len));
    l->cltt_ = cltt;
    l->state_ = state;

    // Retrieve the optional flag indicating if the lease must be created when it
    // doesn't exist during the update.
    force_create = false;
    if (lease_info->contains("force-create")) {
        force_create = getBoolean(lease_info, "force-create");
    }

    return (l);
}

};
};
