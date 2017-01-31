// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <d2/d2_config.h>
#include <d2/d2_simple_parser.h>
#include <cc/data.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

using namespace isc::data;

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
    { "ip-address",         Element::string, D2Params::DFT_IP_ADDRESS },
    { "port",               Element::integer, D2Params::DFT_PORT_STR },
    { "dns-server-timeout", Element::integer, D2Params::DFT_DNS_SERVER_TIMEOUT_STR },
    { "ncr-protocol",       Element::string, D2Params::DFT_NCR_PROTOCOL },
    { "ncr-format",         Element::string, D2Params::DFT_NCR_FORMAT }
};

const SimpleDefaults D2SimpleParser::TSIG_KEY_DEFAULTS = {
    { "digest-bits",    Element::integer, "0" }
};

const SimpleDefaults D2SimpleParser::DDNS_DOMAIN_MGR_DEFAULTS = {
    // none yet
};

const SimpleDefaults D2SimpleParser::DDNS_DOMAIN_DEFAULTS = {
    { "key-name",    Element::string, "" }
};

const SimpleDefaults D2SimpleParser::DNS_SERVER_DEFAULTS = {
    { "hostname", Element::string, "" },
    { "port",     Element::integer, DnsServerInfo::STANDARD_DNS_PORT_STR },
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

};
};
