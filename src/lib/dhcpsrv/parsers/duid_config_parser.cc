// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcpsrv/cfg_duid.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/duid_config_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <exceptions/exceptions.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <limits>
#include <string>

using namespace isc::data;

namespace isc {
namespace dhcp {

void
DUIDConfigParser::parse(const CfgDUIDPtr& cfg,
                        isc::data::ConstElementPtr duid_configuration) {
    if (!cfg) {
        // Sanity check
        isc_throw(DhcpConfigError, "Must provide valid pointer to cfg when parsing duid");
    }

    std::string param;
    try {
        param = "type";
        std::string duid_type = getString(duid_configuration, "type");
        // Map DUID type represented as text into numeric value.
        DUID::DUIDType numeric_type = DUID::DUID_UNKNOWN;
        if (duid_type == "LLT") {
            numeric_type = DUID::DUID_LLT;
        } else if (duid_type == "EN") {
            numeric_type = DUID::DUID_EN;
        } else if (duid_type == "LL") {
            numeric_type = DUID::DUID_LL;
        } else {
            isc_throw(BadValue, "unsupported DUID type '"
                      << duid_type << "'. Expected: LLT, EN or LL");
        }

        cfg->setType(static_cast<DUID::DUIDType>(numeric_type));

        param = "identifier";
        if (duid_configuration->contains(param)) {
            cfg->setIdentifier(getString(duid_configuration, param));
        }

        param = "htype";
        if (duid_configuration->contains(param)) {
            cfg->setHType(getUint16(duid_configuration, param));
        }

        param = "time";
        if (duid_configuration->contains(param)) {
            cfg->setTime(getUint32(duid_configuration, param));
        }

        param = "enterprise-id";
        if (duid_configuration->contains(param)) {
            cfg->setEnterpriseId(getUint32(duid_configuration, param));
        }

        param = "persist";
        if (duid_configuration->contains(param)) {
            cfg->setPersist(getBoolean(duid_configuration, param));
        }

        param = "user-context";
        ConstElementPtr user_context = duid_configuration->get("user-context");
        if (user_context) {
            cfg->setContext(user_context);
        }
    } catch (const DhcpConfigError&) {
        throw;
    } catch (const std::exception& ex) {
        // Append position.
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << getPosition(param, duid_configuration) << ")");
    }

    LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_CONFIGURE_SERVERID);
}

} // end of namespace isc::dhcp
} // end of namespace isc
