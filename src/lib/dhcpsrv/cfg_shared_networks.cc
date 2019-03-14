// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_shared_networks.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

bool
CfgSharedNetworks4::hasNetworkWithServerId(const IOAddress& server_id) const {
    const auto& index = networks_.get<SharedNetworkServerIdIndexTag>();
    auto network_it = index.find(server_id);
    return (network_it != index.cend());
}



void
CfgSharedNetworks4::merge(CfgOptionDefPtr cfg_def, CfgSharedNetworks4& other) {
    auto& index = networks_.get<SharedNetworkNameIndexTag>();

    // Iterate over the subnets to be merged. They will replace the existing
    // subnets with the same id. All new subnets will be inserted into this
    // configuration.
    auto other_networks = other.getAll();
    for (auto other_network = other_networks->begin();
         other_network != other_networks->end(); ++other_network) {

        // In theory we should drop subnet assignments from "other". The
        // idea being  those that come from the CB should not have subnets_
        // populated.  We will quietly throw them away, just in case.
        (*other_network)->delAll();

        // Check if the other network exists in this config.
        auto existing_network = index.find((*other_network)->getName());
        if (existing_network != index.end()) {

            // Somehow the same instance is in both, skip it.
            if (*existing_network == *other_network) {
                continue;
            }

            // Network exists, which means we're updating it.
            // First we need to move its subnets to the new
            // version of the network.
            const Subnet4Collection* subnets = (*existing_network)->getAllSubnets();

            Subnet4Collection copy_subnets(*subnets);
            for (auto subnet = copy_subnets.cbegin(); subnet != copy_subnets.cend(); ++subnet) {
                (*existing_network)->del((*subnet)->getID());
                (*other_network)->add(*subnet);
            }

            // Now we discard the existing copy of the network.
            index.erase(existing_network);
        }

        // Create the network's options based on the given definitions.
        (*other_network)->getCfgOption()->createOptions(cfg_def);

        // Add the new/updated nework.
        networks_.push_back(*other_network);
    }

}

} // end of namespace isc::dhcp
} // end of namespace isc
