// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/data.h>
#include <dhcpsrv/cfg_expiration.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/expiration_config_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <boost/foreach.hpp>

using namespace isc::data;

namespace isc {
namespace dhcp {

void
ExpirationConfigParser::parse(ConstElementPtr expiration_config) {
    CfgExpirationPtr cfg = CfgMgr::instance().getStagingCfg()->getCfgExpiration();

    BOOST_FOREACH(ConfigPair config_element, expiration_config->mapValue()) {

        // Get parameter name and value.
        std::string param_name = config_element.first;
        ConstElementPtr param_value = config_element.second;

        try {
            // Set configuration parameters.
            if (param_name == "reclaim-timer-wait-time") {
                cfg->setReclaimTimerWaitTime(param_value->intValue());

            } else if (param_name == "flush-reclaimed-timer-wait-time") {
                cfg->setFlushReclaimedTimerWaitTime(param_value->intValue());

            } else if (param_name == "hold-reclaimed-time") {
                cfg->setHoldReclaimedTime(param_value->intValue());

            } else if (param_name == "max-reclaim-leases") {
                cfg->setMaxReclaimLeases(param_value->intValue());

            } else if (param_name == "max-reclaim-time") {
                cfg->setMaxReclaimTime(param_value->intValue());

            } else if (param_name == "unwarned-reclaim-cycles") {
                cfg->setUnwarnedReclaimCycles(param_value->intValue());

            } else {
                isc_throw(DhcpConfigError, "unsupported parameter '"
                          << param_name << "'");
            }

        } catch (const std::exception& ex) {
            // Append position of the configuration parameter to the error
            // message.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << param_value->getPosition() << ")");
        }
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
