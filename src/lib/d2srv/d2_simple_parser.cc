// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2srv/d2_config.h>
#include <d2srv/d2_simple_parser.h>
#include <cc/data.h>
#include <hooks/hooks_manager.h>
#include <hooks/hooks_parser.h>
#include <boost/foreach.hpp>

using namespace isc::data;
using namespace isc::d2;
using namespace isc;

namespace {

dhcp_ddns::NameChangeProtocol
getProtocol(ConstElementPtr map, const std::string& name) {
    ConstElementPtr value = map->get(name);
    if (!value) {
        isc_throw(D2CfgError, "Mandatory parameter " << name
                  << " not found (" << map->getPosition() << ")");
    }
    std::string str = value->stringValue();
    try {
        return (dhcp_ddns::stringToNcrProtocol(str));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError,
                  "invalid NameChangeRequest protocol (" << str
                  << ") specified for parameter '" << name
                  << "' (" << value->getPosition() << ")");
    }
}

dhcp_ddns::NameChangeFormat
getFormat(ConstElementPtr map, const std::string& name) {
    ConstElementPtr value = map->get(name);
    if (!value) {
        isc_throw(D2CfgError, "Mandatory parameter " << name
                  << " not found (" << map->getPosition() << ")");
    }
    std::string str = value->stringValue();
    try {
        return (dhcp_ddns::stringToNcrFormat(str));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError,
                  "invalid NameChangeRequest format (" << str
                  << ") specified for parameter '" << name
                  << "' (" << value->getPosition() << ")");
    }
}

} // anon

namespace isc {
namespace d2 {
/// @brief This sets of arrays define the default values and
///        values inherited (derived) between various scopes.
///
/// Each of those is documented in @file d2_simple_parser.cc. This
/// is different than most other comments in Kea code. The reason
/// for placing those in .cc rather than .h file is that it
/// is expected to be one centralized place to look at for
/// the default values. This is expected to be looked at also by
/// people who are not skilled in C or C++, so they may be
/// confused with the differences between declaration and definition.
/// As such, there's one file to look at that hopefully is readable
/// without any C or C++ skills.
///
/// @{

/// @brief This table defines default global values for D2
///
/// Some of the global parameters defined in the global scope (i.e. directly
/// in DhcpDdns) are optional. If not defined, the following values will be
/// used.
const SimpleDefaults D2SimpleParser::D2_GLOBAL_DEFAULTS = {
    { "ip-address",         Element::string, "127.0.0.1" },
    { "port",               Element::integer, "53001" },
    { "dns-server-timeout", Element::integer, "500" }, // in milliseconds
    { "ncr-protocol",       Element::string, "UDP" },
    { "ncr-format",         Element::string, "JSON" }
};

/// Supplies defaults for ddns-domains list elements (i.e. DdnsDomains)
const SimpleDefaults D2SimpleParser::TSIG_KEY_DEFAULTS = {
    { "digest-bits", Element::integer, "0" }
};

/// Supplies defaults for optional values in DDNS domain managers
/// (e.g. "forward-ddns" and "reverse-ddns").
/// @note  While there are none yet defined, it is highly likely
/// there will be domain manager defaults added in the future.
/// This code to set defaults already uses this list, so supporting
/// values will simply require adding them to this list.
const SimpleDefaults D2SimpleParser::DDNS_DOMAIN_MGR_DEFAULTS = {
};

/// Supplies defaults for ddns-domains list elements (i.e. DdnsDomains)
const SimpleDefaults D2SimpleParser::DDNS_DOMAIN_DEFAULTS = {
    { "key-name", Element::string, "" }
};

/// Supplies defaults for optional values DdnsDomain entries.
const SimpleDefaults D2SimpleParser::DNS_SERVER_DEFAULTS = {
    { "hostname", Element::string, "" },
    { "port",     Element::integer, "53" },
    { "key-name", Element::string, "" }
};

/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t
D2SimpleParser::setAllDefaults(isc::data::ElementPtr global) {
    size_t cnt = 0;
    // Set global defaults first.
    cnt = setDefaults(global, D2_GLOBAL_DEFAULTS);

    // If the key list is present, set its members' defaults
    if (global->find("tsig-keys")) {
        ConstElementPtr keys = global->get("tsig-keys");
        cnt += setListDefaults(keys, TSIG_KEY_DEFAULTS);
    } else {
        // Not present, so add an empty list.
        ConstElementPtr list(new ListElement());
        global->set("tsig-keys", list);
        cnt++;
    }

    // Set the forward domain manager defaults.
    cnt += setManagerDefaults(global, "forward-ddns", DDNS_DOMAIN_MGR_DEFAULTS);

    // Set the reverse domain manager defaults.
    cnt += setManagerDefaults(global, "reverse-ddns", DDNS_DOMAIN_MGR_DEFAULTS);
    return (cnt);
}

size_t
D2SimpleParser::setDdnsDomainDefaults(ElementPtr domain,
                                      const SimpleDefaults& domain_defaults) {
    size_t cnt = 0;

    // Set the domain's scalar defaults
    cnt += setDefaults(domain, domain_defaults);
    if (domain->find("dns-servers")) {
        // Now add the defaults to its server list.
        ConstElementPtr servers = domain->get("dns-servers");
        cnt += setListDefaults(servers, DNS_SERVER_DEFAULTS);
    }

    return (cnt);
}


size_t
D2SimpleParser::setManagerDefaults(ElementPtr global,
                                   const std::string& mgr_name,
                                   const SimpleDefaults& mgr_defaults) {
    size_t cnt = 0;

    if (!global->find(mgr_name)) {
        // If it's not present, then default is an empty map
        ConstElementPtr map(new MapElement());
        global->set(mgr_name, map);
        ++cnt;
    } else {
        // Get a writable copy of the manager element map
        ElementPtr mgr =
            boost::const_pointer_cast<Element>(global->get(mgr_name));

        // Set the manager's scalar defaults first
        cnt += setDefaults(mgr, mgr_defaults);

        // Get the domain list and set defaults for them.
        // The domain list may not be present ddns for this
        // manager is disabled.
        if (mgr->find("ddns-domains")) {
            ConstElementPtr domains = mgr->get("ddns-domains");
            BOOST_FOREACH(ElementPtr domain, domains->listValue()) {
                // Set the domain's defaults.  We can't use setListDefaults()
                // as this does not handle sub-lists or maps, like server list.
                cnt += setDdnsDomainDefaults(domain, DDNS_DOMAIN_DEFAULTS);
            }
        }

    }

    return (cnt);
}

void D2SimpleParser::parse(const D2CfgContextPtr& ctx,
                           const isc::data::ConstElementPtr& config,
                           bool check_only) {
    // TSIG keys need to parse before the Domains, so we can catch Domains
    // that specify undefined keys. Create the necessary parsing order now.
    // addToParseOrder("tsig-keys");
    // addToParseOrder("forward-ddns");
    // addToParseOrder("reverse-ddns");

    ConstElementPtr keys = config->get("tsig-keys");
    if (keys) {
        TSIGKeyInfoListParser parser;
        ctx->setKeys(parser.parse(keys));
    }

    ConstElementPtr fwd = config->get("forward-ddns");
    if (fwd) {
        DdnsDomainListMgrParser parser;
        DdnsDomainListMgrPtr mgr = parser.parse(fwd, "forward-ddns",
                                                ctx->getKeys());
        ctx->setForwardMgr(mgr);
    }

    ConstElementPtr rev = config->get("reverse-ddns");
    if (rev) {
        DdnsDomainListMgrParser parser;
        DdnsDomainListMgrPtr mgr = parser.parse(rev, "reverse-ddns",
                                                ctx->getKeys());
        ctx->setReverseMgr(mgr);
    }

    // Fetch the parameters in the config, performing any logical
    // validation required.
    asiolink::IOAddress ip_address(0);
    uint32_t port = 0;
    uint32_t dns_server_timeout = 0;
    dhcp_ddns::NameChangeProtocol ncr_protocol = dhcp_ddns::NCR_UDP;
    dhcp_ddns::NameChangeFormat ncr_format = dhcp_ddns::FMT_JSON;

    ip_address = SimpleParser::getAddress(config, "ip-address");

    if ((ip_address.toText() == "0.0.0.0") ||
        (ip_address.toText() == "::")) {
        isc_throw(D2CfgError, "IP address cannot be \""
                  << ip_address << "\""
                  << " (" << config->get("ip-address")->getPosition() << ")");
    }

    port = SimpleParser::getUint32(config, "port");

    dns_server_timeout = SimpleParser::getUint32(config, "dns-server-timeout");

    ncr_protocol = getProtocol(config, "ncr-protocol");
    if (ncr_protocol != dhcp_ddns::NCR_UDP) {
        isc_throw(D2CfgError, "ncr-protocol : "
                  << dhcp_ddns::ncrProtocolToString(ncr_protocol)
                  << " is not yet supported ("
                  << config->get("ncr-protocol")->getPosition() << ")");
    }

    ncr_format = getFormat(config, "ncr-format");
    if (ncr_format != dhcp_ddns::FMT_JSON) {
        isc_throw(D2CfgError, "NCR Format:"
                  << dhcp_ddns::ncrFormatToString(ncr_format)
                  << " is not yet supported"
                  << " (" << config->get("ncr-format")->getPosition() << ")");
    }

    ConstElementPtr user = config->get("user-context");
    if (user) {
        ctx->setContext(user);
    }

    ConstElementPtr socket = config->get("control-socket");
    if (socket) {
        if (socket->getType() != Element::map) {
            isc_throw(D2CfgError, "Specified control-socket is expected to be a map"
                      ", i.e. a structure defined within { }");
        }
        ctx->setControlSocketInfo(socket);
    }

    // Finally, let's get the hook libs!
    using namespace isc::hooks;
    HooksConfig& libraries = ctx->getHooksConfig();
    ConstElementPtr hooks = config->get("hooks-libraries");
    if (hooks) {
        HooksLibrariesParser hooks_parser;
        hooks_parser.parse(libraries, hooks);
        libraries.verifyLibraries(hooks->getPosition(), false);
    }

    // Attempt to create the new client config. This ought to fly as
    // we already validated everything.
    D2ParamsPtr params(new D2Params(ip_address, port, dns_server_timeout,
                                    ncr_protocol, ncr_format));

    ctx->getD2Params() = params;

    if (!check_only) {
        // This occurs last as if it succeeds, there is no easy way
        // revert it.  As a result, the failure to commit a subsequent
        // change causes problems when trying to roll back.
        HooksManager::prepareUnloadLibraries();
        static_cast<void>(HooksManager::unloadLibraries());
        libraries.loadLibraries(false);
    }
}

}
}
