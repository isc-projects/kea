// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <boost/foreach.hpp>

using namespace isc::data;

namespace isc {
namespace dhcp {
/// @brief This sets of arrays define the default values and
///        values inherited (derived) between various scopes.
///
/// Each of those is documented in @file simple_parser6.cc. This
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

/// @brief This table defines all global parameters in DHCPv6.
///
/// Boolean, integer, real and string types are for scalar parameters,
/// list and map types for entries.
/// Order follows global_param rule in bison grammar.
const SimpleKeywords SimpleParser6::GLOBAL6_PARAMETERS = {
    { "data-directory",               Element::string },
    { "preferred-lifetime",           Element::integer },
    { "valid-lifetime",               Element::integer },
    { "renew-timer",                  Element::integer },
    { "rebind-timer",                 Element::integer },
    { "decline-probation-period",     Element::integer },
    { "subnet6",                      Element::list },
    { "shared-networks",              Element::list },
    { "interfaces-config",            Element::map },
    { "lease-database",               Element::map },
    { "hosts-database",               Element::map },
    { "hosts-databases",              Element::list },
    { "mac-sources",                  Element::list },
    { "relay-supplied-options",       Element::list },
    { "host-reservation-identifiers", Element::list },
    { "client-classes",               Element::list },
    { "option-def",                   Element::list },
    { "option-data",                  Element::list },
    { "hooks-libraries",              Element::list },
    { "expired-leases-processing",    Element::map },
    { "server-id",                    Element::map },
    { "dhcp4o6-port",                 Element::integer },
    { "control-socket",               Element::map },
    { "dhcp-queue-control",           Element::map },
    { "dhcp-ddns",                    Element::map },
    { "user-context",                 Element::map },
    { "comment",                      Element::string },
    { "sanity-checks",                Element::map },
    { "reservations",                 Element::list },
    { "config-control",               Element::map },
    { "server-tag",                   Element::string },
    { "reservation-mode",             Element::string }
};

/// @brief This table defines default values for option definitions in DHCPv6.
///
/// Dhcp6 may contain an array called option-def that enumerates new option
/// definitions. This array lists default values for those option definitions.
const SimpleDefaults SimpleParser6::OPTION6_DEF_DEFAULTS = {
    { "record-types", Element::string,  ""},
    { "space",        Element::string,  "dhcp6"},
    { "array",        Element::boolean, "false"},
    { "encapsulate",  Element::string,  "" }
};

/// @brief This table defines default values for options in DHCPv6.
///
/// Dhcp6 usually contains option values (option-data) defined in global,
/// subnet, class or host reservations scopes. This array lists default values
/// for those option-data declarations.
const SimpleDefaults SimpleParser6::OPTION6_DEFAULTS = {
    { "space",        Element::string,  "dhcp6"},
    { "csv-format",   Element::boolean, "true"},
    { "always-send",  Element::boolean, "false"}
};

/// @brief This table defines default global values for DHCPv6
///
/// Some of the global parameters defined in the global scope (i.e. directly
/// in Dhcp6) are optional. If not defined, the following values will be
/// used.
const SimpleDefaults SimpleParser6::GLOBAL6_DEFAULTS = {
    { "renew-timer",              Element::integer, "900" },
    { "rebind-timer",             Element::integer, "1800" },
    { "preferred-lifetime",       Element::integer, "3600" },
    { "valid-lifetime",           Element::integer, "7200" },
    { "decline-probation-period", Element::integer, "86400" }, // 24h
    { "dhcp4o6-port",             Element::integer, "0" },
    { "server-tag",               Element::string,  "" },
    { "reservation-mode",         Element::string,  "all" }
};

/// @brief This table defines default values for each IPv6 subnet.
const SimpleDefaults SimpleParser6::SUBNET6_DEFAULTS = {
    { "id",               Element::integer, "0" }, // 0 means autogenerate
    { "interface",        Element::string,  "" },
    { "client-class",     Element::string,  "" },
    { "rapid-commit",     Element::boolean, "false" }, // rapid-commit disabled by default
    { "interface-id",     Element::string,  "" }
};

/// @brief This table defines default values for each IPv6 subnet.
const SimpleDefaults SimpleParser6::SHARED_SUBNET6_DEFAULTS = {
    { "id",               Element::integer, "0" } // 0 means autogenerate
};

/// @brief This table defines default values for each IPv6 shared network.
const SimpleDefaults SimpleParser6::SHARED_NETWORK6_DEFAULTS = {
    { "client-class",     Element::string,  "" },
    { "interface",        Element::string,  "" },
    { "interface-id",     Element::string,  "" },
    { "rapid-commit",     Element::boolean, "false" } // rapid-commit disabled by default
};


/// @brief This table defines default values for interfaces for DHCPv6.
const SimpleDefaults SimpleParser6::IFACE6_DEFAULTS = {
    { "re-detect", Element::boolean, "true" }
};

/// @brief List of parameters that can be inherited from the global to subnet6 scope.
///
/// Some parameters may be defined on both global (directly in Dhcp6) and
/// subnet (Dhcp6/subnet6/...) scope. If not defined in the subnet scope,
/// the value is being inherited (derived) from the global scope. This
/// array lists all of such parameters.
///
/// This list is also used for inheriting from global to shared networks
/// and from shared networks to subnets within it.
const ParamsList SimpleParser6::INHERIT_TO_SUBNET6 = {
    "client-class",
    "interface",
    "interface-id",
    "preferred-lifetime",
    "rapid-commit",
    "rebind-timer",
    "relay",
    "renew-timer",
    "reservation-mode",
    "valid-lifetime"
};

/// @brief This table defines default values for dhcp-queue-control in DHCPv4.
const SimpleDefaults SimpleParser6::DHCP_QUEUE_CONTROL6_DEFAULTS = {
    { "enable-queue",   Element::boolean, "false"},
    { "queue-type", Element::string,  "kea-ring6"},
    { "capacity",  Element::integer, "500"}
};


/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t SimpleParser6::setAllDefaults(isc::data::ElementPtr global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, GLOBAL6_DEFAULTS);

    // Now set the defaults for each specified option definition
    ConstElementPtr option_defs = global->get("option-def");
    if (option_defs) {
        BOOST_FOREACH(ElementPtr option_def, option_defs->listValue()) {
            cnt += SimpleParser::setDefaults(option_def, OPTION6_DEF_DEFAULTS);
        }
    }

    // Set the defaults for option data
    ConstElementPtr options = global->get("option-data");
    if (options) {
        BOOST_FOREACH(ElementPtr single_option, options->listValue()) {
            cnt += SimpleParser::setDefaults(single_option, OPTION6_DEFAULTS);
        }
    }

    // Now set the defaults for defined subnets
    ConstElementPtr subnets = global->get("subnet6");
    if (subnets) {
        cnt += setListDefaults(subnets, SUBNET6_DEFAULTS);
    }

    // Set the defaults for interfaces config
    ConstElementPtr ifaces_cfg = global->get("interfaces-config");
    if (ifaces_cfg) {
        ElementPtr mutable_cfg = boost::const_pointer_cast<Element>(ifaces_cfg);
        cnt += setDefaults(mutable_cfg, IFACE6_DEFAULTS);
    }

    // Set defaults for shared networks
    ConstElementPtr shared = global->get("shared-networks");
    if (shared) {
        BOOST_FOREACH(ElementPtr net, shared->listValue()) {

            cnt += setDefaults(net, SHARED_NETWORK6_DEFAULTS);

            ConstElementPtr subs = net->get("subnet6");
            if (subs) {
                cnt += setListDefaults(subs, SHARED_SUBNET6_DEFAULTS);
            }
        }
    }

    // Set the defaults for dhcp-queue-control.  If the element isn't there
    // we'll add it.
    ConstElementPtr queue_control = global->get("dhcp-queue-control");
    ElementPtr mutable_cfg;
    if (queue_control) {
        mutable_cfg = boost::const_pointer_cast<Element>(queue_control);
    } else {
        mutable_cfg = Element::createMap();
        global->set("dhcp-queue-control", mutable_cfg);
    }

    cnt += setDefaults(mutable_cfg, DHCP_QUEUE_CONTROL6_DEFAULTS);

    return (cnt);
}

size_t SimpleParser6::deriveParameters(isc::data::ElementPtr global) {
    size_t cnt = 0;
    // Now derive global parameters into subnets.
    ConstElementPtr subnets = global->get("subnet6");
    if (subnets) {
        BOOST_FOREACH(ElementPtr single_subnet, subnets->listValue()) {
            cnt += SimpleParser::deriveParams(global, single_subnet,
                                              INHERIT_TO_SUBNET6);
        }
    }

    // Deriving parameters for shared networks is a bit more involved.
    // First, the shared-network level derives from global, and then
    // subnets within derive from it.
    ConstElementPtr shared = global->get("shared-networks");
    if (shared) {
        BOOST_FOREACH(ElementPtr net, shared->listValue()) {
            // First try to inherit the parameters from shared network,
            // if defined there.
            // Then try to inherit them from global.
            cnt += SimpleParser::deriveParams(global, net,
                                              INHERIT_TO_SUBNET6);

            // Now we need to go thrugh all the subnets in this net.
            subnets = net->get("subnet6");
            if (subnets) {
                BOOST_FOREACH(ElementPtr single_subnet, subnets->listValue()) {
                    cnt += SimpleParser::deriveParams(net, single_subnet,
                                                      INHERIT_TO_SUBNET6);
                }
            }
        }
    }

    return (cnt);
}

};
};
