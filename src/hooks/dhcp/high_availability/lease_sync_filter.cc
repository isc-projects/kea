// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfgmgr.h>
#include <ha_config.h>
#include <lease_sync_filter.h>

using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace ha {

LeaseSyncFilter::LeaseSyncFilter(const HAServerType& server_type, const HAConfigPtr& config)
    : server_type_(server_type), config_(config), subnet_ids_() {
}

void
LeaseSyncFilter::apply() {
    subnet_ids_.clear();
    if (server_type_ == HAServerType::DHCPv4) {
        for (auto const& subnet : *CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll()) {
            conditionallyApplySubnetFilter(subnet);
        }
    } else {
        for (auto const& subnet : *CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll()) {
            conditionallyApplySubnetFilter(subnet);
        }
    }
}

bool
LeaseSyncFilter::shouldSync(const LeasePtr& lease) const {
    return (subnet_ids_.empty() || subnet_ids_.count(lease->subnet_id_));
}

void
LeaseSyncFilter::conditionallyApplySubnetFilter(const SubnetPtr& subnet) {
    try {
        auto server_name = HAConfig::getSubnetServerName(subnet);
        if (!server_name.empty()) {
            for (auto const& peer : config_->getAllServersConfig()) {
                if (peer.first == server_name) {
                    subnet_ids_.insert(subnet->getID());
                    return;
                }
            }
        }
    } catch (...) {
        // Don't add ID when there was no way to fetch
        // the server name.
    }
}

} // end of namespace isc::ha
} // end of namespace isc
