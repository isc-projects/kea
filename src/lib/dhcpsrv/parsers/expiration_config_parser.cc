// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <cc/data.h>
#include <dhcpsrv/cfg_expiration.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/expiration_config_parser.h>
#include <boost/foreach.hpp>

using namespace isc::data;

namespace isc {
namespace dhcp {

ExpirationConfigParser::ExpirationConfigParser()
    : DhcpConfigParser() {
}

void
ExpirationConfigParser::build(ConstElementPtr expiration_config) {
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

void
ExpirationConfigParser::commit() {
    // Nothing to do.
}

} // end of namespace isc::dhcp
} // end of namespace isc
