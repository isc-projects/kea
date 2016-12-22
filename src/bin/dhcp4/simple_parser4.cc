// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp4/simple_parser4.h>
#include <cc/data.h>
#include <boost/foreach.hpp>

using namespace std;
using namespace isc::data;

namespace isc {
namespace dhcp {

/// This table defines default values for option definitions in DHCPv4
const SimpleDefaults SimpleParser4::OPTION4_DEF_DEFAULTS = {
    { "record-types", Element::string,  ""},
    { "space",        Element::string,  "dhcp4"},
    { "array",        Element::boolean, "false"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for options in DHCPv4
const SimpleDefaults SimpleParser4::OPTION4_DEFAULTS = {
    { "space",        Element::string,  "dhcp4"},
    { "csv-format",   Element::boolean, "true"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for DHCPv4
const SimpleDefaults SimpleParser4::GLOBAL4_DEFAULTS = {
    { "renew-timer",        Element::integer, "900" },
    { "rebind-timer",       Element::integer, "1800" },
    { "valid-lifetime",     Element::integer, "7200" }
};

/// This list defines parameters that can be inherited from the global
/// scope to subnet6 scope.
const ParamsList SimpleParser4::INHERIT_GLOBAL_TO_SUBNET4 = {
    "renew-timer",
    "rebind-timer",
    "valid-lifetime"
};

size_t SimpleParser4::setAllDefaults(isc::data::ElementPtr global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, GLOBAL4_DEFAULTS);

    // Now set option defintion defaults for each specified option definition
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

    return (cnt);
}

};
};
