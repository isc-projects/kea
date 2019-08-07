// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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

    std::string param;

    try {
        param = "reclaim-timer-wait-time";
        if (expiration_config->contains(param)) {
            cfg->setReclaimTimerWaitTime(getInteger(expiration_config, param));
        }

        param = "flush-reclaimed-timer-wait-time";
        if (expiration_config->contains(param)) {
            cfg->setFlushReclaimedTimerWaitTime(getInteger(expiration_config,
                                                           param));
        }

        param = "hold-reclaimed-time";
        if (expiration_config->contains(param)) {
            cfg->setHoldReclaimedTime(getInteger(expiration_config, param));
        }

        param = "max-reclaim-leases";
        if (expiration_config->contains(param)) {
            cfg->setMaxReclaimLeases(getInteger(expiration_config, param));
        }

        param = "max-reclaim-time";
        if (expiration_config->contains(param)) {
            cfg->setMaxReclaimTime(getInteger(expiration_config, param));
        }

        param = "unwarned-reclaim-cycles";
        if (expiration_config->contains(param)) {
            cfg->setUnwarnedReclaimCycles(
                getInteger(expiration_config, param));
        }
    } catch (const DhcpConfigError&) {
        throw;
    } catch (const std::exception& ex) {
        // Append position of the configuration parameter to the error message.
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << getPosition(param, expiration_config) << ")");
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
