// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file lease_expire_co.cc Defines the lease4_send and lease6_send callout functions.

#include <config.h>
#include <asiolink/io_address.h>
#include <hooks/hooks.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_string.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcpsrv/lease.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <scripts_cfg.h>
#include <scripts.h>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace hooks::scripts;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "lease6_expire" hook.
///
/// @return 0 upon success, non-zero otherwise.
int lease6_expire(CalloutHandle& handle) {
    try {
        Lease6Ptr lease;
        handle.getArgument("lease6", lease);

        if (!lease) {
            // Something is very wrong here.
            return (1);
        }
        
        Variables vars;

        stringstream tmp;
        switch (lease->type_) {
        case Lease::TYPE_NA:
        case Lease::TYPE_TA:
        case Lease::TYPE_V4:
            tmp << "ADDRESS1=" << lease->addr_.toText();
            break;
        case Lease::TYPE_PD:
            tmp << "PREFIX1=" << lease->addr_.toText() << "/" << static_cast<int>(lease->prefixlen_);
            break;
        default:
            // Unknown lease type.
            return (1);
        }
        vars.push_back(tmp.str());

        if (lease->duid_) {
            tmp.str("");
            tmp << "DUID=" << lease->duid_->toText();
            vars.push_back(tmp.str());
        }

        tmp.str("");
        tmp << "HOSTNAME=" << lease->hostname_;
        vars.push_back(tmp.str());

        callScript(vars);
        
    } catch (const std::exception& ex) {
        std::cout << "DHCP Scripts Hook : lease6_expire unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

} // extern C


