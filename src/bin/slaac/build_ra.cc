// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <slaac/nd.h>
#include <slaac/nd_pkt_ra.h>
#include <slaac/nd_option_lladdr.h>
#include <slaac/nd_option_mtu.h>
#include <slaac/nd_option_pref_info.h>
#include <slaac/nd_option_univ_ra.h>
#include <slaac/slaac_cfg_mgr.h>
#include <slaac/json.hpp>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;

using json = nlohmann::json;

namespace isc {
namespace slaac {

RAPktPtr buildRA(const SlaacConfigPtr& config) {
    // Get the RA packet.
    RAPktPtr ra(new RAPkt(IOAddress::IPV6_ZERO_ADDRESS(),
                          IOAddress::IPV6_ZERO_ADDRESS()));

    // Fill the RA packet.
    ra->setHopLimit(config->getHopLimit());
    ra->setManagedFlag(config->getManagedFlag());
    ra->setOtherFlag(config->getOtherFlag());
    ra->setRouterLifetime(config->getRouterLifetime());
    ra->setReachableTime(config->getReachableTime());
    ra->setRetransTimer(config->getRetransTimer());

    // @todo: Add Source Link-Layer Address option.

    // Add MTU option.
    uint32_t mtu = config->getMtu();
    if (mtu > 0) {
        // Get the MTU option.
        OptionMtuPtr opt(new OptionMtu());

        // Fill the MTU option.
        opt->setMtu(mtu);

        // Add the MTU option to the RA packet.
        ra->addOption(opt);
    }

    // Add Prefix Info options.
    const PrefixInfosConfig& prefix_infos = config->getPrefixInfosConfig();
    for (auto prefix_info : prefix_infos) {
        // Get a Prefix Info option.
        OptionPrefInfoPtr opt(new OptionPrefInfo());

        // Fill Prefix Info option.
        opt->setPrefixLength(prefix_info->getPrefixLength());
        opt->setPrefix(prefix_info->getPrefix());
        opt->setOnLinkFlag(prefix_info->getOnLinkFlag());
        opt->setAddrConfigFlag(prefix_info->getAddrConfigFlag());
        opt->setValidLifetime(prefix_info->getValidLifetime());
        opt->setPreferredLifetime(prefix_info->getPreferredLifetime());

        // Add Prefix Info option to the RA packet.
        ra->addOption(opt);
    }

    // Add Universal IPv6 Router Advertisement option.
    const ConstElementPtr& universal_ra = config->getUnivRa();
    if (universal_ra) {
        // Prepare the universal RA option content.
        string text = universal_ra->str();
        json json = json::parse(text);
        vector<uint8_t> cbor = json::to_cbor(json);

        // Pad to 6 modulo 8.
        size_t round = ((cbor.size() + 1) | 7) - 1;
        if (round > cbor.size()) {
            cbor.resize(round, 0);
        }

        // Get the universal RA option.
        OptionUnivRaPtr opt(new OptionUnivRa(cbor));

        // Add the universal RA option o the RA packet.
        ra->addOption(opt);
    }

    // Pack the RA packet.
    ra->pack();

    return (ra);
}

} // namespace isc::slaac
} // namespace isc
