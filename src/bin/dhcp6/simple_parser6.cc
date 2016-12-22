// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp6/simple_parser6.h>
#include <cc/data.h>
#include <boost/foreach.hpp>

using namespace std;
using namespace isc::data;

namespace isc {
namespace dhcp {

/// This table defines default values for option definitions in DHCPv6
const SimpleDefaults SimpleParser6::OPTION6_DEF_DEFAULTS = {
    { "record-types", Element::string,  ""},
    { "space",        Element::string,  "dhcp6"},
    { "array",        Element::boolean, "false"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for options in DHCPv6
const SimpleDefaults SimpleParser6::OPTION6_DEFAULTS = {
    { "space",        Element::string,  "dhcp6"},
    { "csv-format",   Element::boolean, "true"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for both DHCPv4 and DHCPv6
const SimpleDefaults SimpleParser6::GLOBAL6_DEFAULTS = {
    { "renew-timer",        Element::integer, "900" },
    { "rebind-timer",       Element::integer, "1800" },
    { "preferred-lifetime", Element::integer, "3600" },
    { "valid-lifetime",     Element::integer, "7200" }
};

/// This list defines parameters that can be inherited from the global
/// scope to subnet6 scope.
const ParamsList SimpleParser6::INHERIT_GLOBAL_TO_SUBNET6 = {
    "renew-timer",
    "rebind-timer",
    "preferred-lifetime",
    "valid-lifetime"
};


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

    // Finally, set the defaults for option data
    ConstElementPtr options = global->get("option-data");
    if (options) {
        BOOST_FOREACH(ElementPtr single_option, options->listValue()) {
            cnt += SimpleParser::setDefaults(single_option, OPTION6_DEFAULTS);
        }
    }

    return (cnt);
}

};
};
