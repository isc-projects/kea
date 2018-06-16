// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/parsers/simple_parser4.h>
#include <cc/data.h>
#include <boost/foreach.hpp>
#include <iostream>

using namespace isc::data;

namespace isc {
namespace dhcp {
/// @brief This sets of arrays define the default values and
///        values inherited (derived) between various scopes.
///
/// Each of those is documented in @file simple_parser4.cc. This
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

/// @brief This table defines default values for option definitions in DHCPv4.
///
/// Dhcp4 may contain an array called option-def that enumerates new option
/// definitions. This array lists default values for those option definitions.
const SimpleDefaults SimpleParser4::OPTION4_DEF_DEFAULTS = {
    { "record-types", Element::string,  ""},
    { "space",        Element::string,  "dhcp4"},
    { "array",        Element::boolean, "false"},
    { "encapsulate",  Element::string,  "" }
};

/// @brief This table defines default values for options in DHCPv4.
///
/// Dhcp4 usually contains option values (option-data) defined in global,
/// subnet, class or host reservations scopes. This array lists default values
/// for those option-data declarations.
const SimpleDefaults SimpleParser4::OPTION4_DEFAULTS = {
    { "space",        Element::string,  "dhcp4"},
    { "csv-format",   Element::boolean, "true"},
    { "always-send",  Element::boolean, "false"}
};

/// @brief This table defines default global values for DHCPv4
///
/// Some of the global parameters defined in the global scope (i.e. directly
/// in Dhcp4) are optional. If not defined, the following values will be
/// used.
const SimpleDefaults SimpleParser4::GLOBAL4_DEFAULTS = {
    { "valid-lifetime",           Element::integer, "7200" },
    { "decline-probation-period", Element::integer, "86400" }, // 24h
    { "dhcp4o6-port",             Element::integer, "0" },
    { "echo-client-id",           Element::boolean, "true" },
    { "match-client-id",          Element::boolean, "true" },
    { "next-server",              Element::string,  "0.0.0.0" },
    { "server-hostname",          Element::string,  "" },
    { "boot-file-name",           Element::string,  "" }
};

/// @brief This table defines default values for each IPv4 subnet.
///
/// Note: When updating this array, please also update SHARED_SUBNET4_DEFAULTS
/// below. In most cases, those two should be kept in sync, except cases
/// where a parameter can be derived from shared-networks, but is not
/// defined on global level. Currently there are two such parameters:
/// interface and reservation-mode
const SimpleDefaults SimpleParser4::SUBNET4_DEFAULTS = {
    { "id",               Element::integer, "0" }, // 0 means autogenerate
    { "interface",        Element::string,  "" },
    { "client-class",     Element::string,  "" },
    { "reservation-mode", Element::string,  "all" },
    { "4o6-interface",    Element::string,  "" },
    { "4o6-interface-id", Element::string,  "" },
    { "4o6-subnet",       Element::string,  "" },
};

/// @brief This table defines default values for each IPv4 subnet that is
///        part of a shared network
///
/// This is mostly the same as @ref SUBNET4_DEFAULTS, except two parameters
/// that can be derived from shared-network, but cannot from global scope.
/// Those are: interface and reservation-mode.
const SimpleDefaults SimpleParser4::SHARED_SUBNET4_DEFAULTS = {
    { "id",               Element::integer, "0" }, // 0 means autogenerate
    { "4o6-interface",    Element::string,  "" },
    { "4o6-interface-id", Element::string,  "" },
    { "4o6-subnet",       Element::string,  "" },
};

/// @brief This table defines default values for each IPv4 shared network.
const SimpleDefaults SimpleParser4::SHARED_NETWORK4_DEFAULTS = {
    { "client-class",     Element::string, "" },
    { "interface",        Element::string, "" },
    { "reservation-mode", Element::string, "all" }
};

/// @brief This table defines default values for interfaces for DHCPv4.
const SimpleDefaults SimpleParser4::IFACE4_DEFAULTS = {
    { "re-detect", Element::boolean, "true" }
};

/// @brief List of parameters that can be inherited to subnet4 scope.
///
/// Some parameters may be defined on both global (directly in Dhcp4) and
/// subnet (Dhcp4/subnet4/...) scope. If not defined in the subnet scope,
/// the value is being inherited (derived) from the global scope. This
/// array lists all of such parameters.
///
/// This list is also used for inheriting from global to shared networks
/// and from shared networks to subnets within it.
const ParamsList SimpleParser4::INHERIT_TO_SUBNET4 = {
    "boot-file-name",
    "client-class",
    "interface",
    "match-client-id",
    "next-server",
    "rebind-timer",
    "relay",
    "renew-timer",
    "reservation-mode",
    "server-hostname",
    "valid-lifetime"
};

/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t SimpleParser4::setAllDefaults(isc::data::ElementPtr global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, GLOBAL4_DEFAULTS);

    // Now set option definition defaults for each specified option definition
    ConstElementPtr option_defs = global->get("option-def");
    if (option_defs) {
        BOOST_FOREACH(ElementPtr option_def, option_defs->listValue()) {
            cnt += SimpleParser::setDefaults(option_def, OPTION4_DEF_DEFAULTS);
        }
    }

    // Set the defaults for option data
    ConstElementPtr options = global->get("option-data");
    if (options) {
        cnt += setListDefaults(options, OPTION4_DEFAULTS);
    }

    // Now set the defaults for defined subnets
    ConstElementPtr subnets = global->get("subnet4");
    if (subnets) {
        cnt += setListDefaults(subnets, SUBNET4_DEFAULTS);
    }

    // Set the defaults for interfaces config
    ConstElementPtr ifaces_cfg = global->get("interfaces-config");
    if (ifaces_cfg) {
        ElementPtr mutable_cfg = boost::const_pointer_cast<Element>(ifaces_cfg);
        cnt += setDefaults(mutable_cfg, IFACE4_DEFAULTS);
    }

    // Set defaults for shared networks
    ConstElementPtr shared = global->get("shared-networks");
    if (shared) {
        BOOST_FOREACH(ElementPtr net, shared->listValue()) {

            cnt += setDefaults(net, SHARED_NETWORK4_DEFAULTS);

            ConstElementPtr subs = net->get("subnet4");
            if (subs) {
                cnt += setListDefaults(subs, SHARED_SUBNET4_DEFAULTS);
            }
        }
    }

    return (cnt);
}

size_t SimpleParser4::deriveParameters(isc::data::ElementPtr global) {
    size_t cnt = 0;

    // Now derive global parameters into subnets.
    ConstElementPtr subnets = global->get("subnet4");
    if (subnets) {
        BOOST_FOREACH(ElementPtr single_subnet, subnets->listValue()) {
            cnt += SimpleParser::deriveParams(global, single_subnet,
                                              INHERIT_TO_SUBNET4);
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
                                              INHERIT_TO_SUBNET4);

            // Now we need to go thrugh all the subnets in this net.
            subnets = net->get("subnet4");
            if (subnets) {
                BOOST_FOREACH(ElementPtr single_subnet, subnets->listValue()) {
                    cnt += SimpleParser::deriveParams(net, single_subnet,
                                                      INHERIT_TO_SUBNET4);
                }
            }

        }
    }

    return (cnt);
}

};
};
