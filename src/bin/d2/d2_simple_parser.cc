// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <d2/d2_simple_parser.h>
#include <cc/data.h>
#include <boost/foreach.hpp>

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
    { "ip-address",         Element::string, "127.0.0.1" },
    { "port",               Element::integer, "53001" },
    { "dns-server-timeout", Element::integer, "100" },
    { "ncr-protocol",       Element::string, "UDP" },
    { "ncr-format",         Element::string, "JSON" }
};

/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t D2SimpleParser::setAllDefaults(isc::data::ElementPtr global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, D2_GLOBAL_DEFAULTS);
    return (cnt);
}

};
};
