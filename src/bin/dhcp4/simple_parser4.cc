// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp4/simple_parser4.h>
#include <cc/data.h>
#include <boost/foreach.hpp>

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
    { "encapsulate",  Element::string,  "" }
};

/// @brief This table defines default global values for DHCPv4
///
/// Some of the global parameters defined in the global scope (i.e. directly
/// in Dhcp4) are optional. If not defined, the following values will be
/// used.
const SimpleDefaults SimpleParser4::GLOBAL4_DEFAULTS = {
    { "renew-timer",        Element::integer, "900" },
    { "rebind-timer",       Element::integer, "1800" },
    { "valid-lifetime",     Element::integer, "7200" }
};

/// @brief List of parameters that can be inherited from the global to subnet4 scope.
///
/// Some parameters may be defined on both global (directly in Dhcp4) and
/// subnet (Dhcp4/subnet4/...) scope. If not defined in the subnet scope,
/// the value is being inherited (derived) from the global scope. This
/// array lists all of such parameters.
const ParamsList SimpleParser4::INHERIT_GLOBAL_TO_SUBNET4 = {
    "renew-timer",
    "rebind-timer",
    "valid-lifetime"
};

/// @brief This table defines default values for D2 client configuration
///
const SimpleDefaults SimpleParser4::D2_CLIENT_CONFIG_DEFAULTS = {
    { "server-ip", Element::string, "127.0.0.1" },
    { "server-port", Element::integer, "53001" },
    // default sender-ip depends on server-ip family, so we leave default blank
    // parser knows to use the appropriate ZERO address based on server-ip
    { "sender-ip", Element::string, "" },
    { "sender-port", Element::integer, "0" },
    { "max-queue-size", Element::integer, "1024" },
    { "ncr-protocol", Element::string, "UDP" },
    { "ncr-format", Element::string, "JSON" },
    { "always-include-fqdn", Element::boolean, "false" },
    { "override-no-update", Element::boolean, "false" },
    { "override-client-update", Element::boolean, "false" },
    { "replace-client-name", Element::string, "NEVER" },
    { "generated-prefix", Element::string, "myhost" },
    { "qualifying-suffix", Element::string, "" }
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

    // Finally, set the defaults for option data
    ConstElementPtr options = global->get("option-data");
    if (options) {
        BOOST_FOREACH(ElementPtr single_option, options->listValue()) {
            cnt += SimpleParser::setDefaults(single_option, OPTION4_DEFAULTS);
        }
    }

    ConstElementPtr d2_client = global->get("dhcp-ddns");
    /// @todo - what if it's not in global? should we add it?
    if (d2_client) {
        // Get the mutable form of d2 client config
        ElementPtr mutable_d2 = boost::const_pointer_cast<Element>(d2_client);
        cnt += SimpleParser::setDefaults(mutable_d2, D2_CLIENT_CONFIG_DEFAULTS);
    }

    return (cnt);
}

};
};
