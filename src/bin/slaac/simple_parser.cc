// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <slaac/simple_parser.h>
#include <slaac/slaac_cfg_mgr.h>
#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <hooks/hooks_parser.h>
#include <boost/foreach.hpp>

using namespace isc::data;

namespace isc {
namespace slaac {
/// @brief This sets of arrays define the default values in various scopes
///        of the Slaac Configuration.
///
/// Each of those is documented in @file slaac/simple_parser.cc. This
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

/// @brief This table defines default values for global options.
///
/// These are global Slaac parameters.
const SimpleDefaults SlaacSimpleParser::SLAAC_DEFAULTS = {
    { "hop-limit",       Element::integer, "0" },
    { "managed-flag",    Element::boolean, "true" },
    { "other-flag",      Element::boolean, "false" },
    { "router-lifetime", Element::integer, "0" },
    { "reachable-time",  Element::integer, "0" },
    { "retranb-timer",   Element::integer, "0" }
};

/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t SlaacSimpleParser::setAllDefaults(const ElementPtr& global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, SLAAC_DEFAULTS);

    return (cnt);
}

size_t SlaacSimpleParser::deriveParameters(ConstElementPtr /*global*/) {
    size_t cnt = 0;

    return (cnt);
}

void
SlaacSimpleParser::parseExperimental(const SlaacConfigPtr& config,
                                     const ConstElementPtr& json) {
    if (!json) {
        return;
    }

    /// @todo: parse experimental structure
}

void
SlaacSimpleParser::parseInterfaces(const SlaacConfigPtr& config,
                                   const ConstElementPtr& json) {
    if (!json) {
        return;
    }

    /// @todo: parse interfaces
}

void
SlaacSimpleParser::parse(const SlaacConfigPtr& config,
                         const ConstElementPtr& json,
                         bool /*check_only*/) {

    config->setHopLimit(getUint8(json, "hop-limit"));
    config->setManagedFlag(getBoolean(json, "managed-flag"));
    config->setRouterLifetime(getUint32(json, "router-lifetime"));
    config->setReachableTime(getUint32(json, "reachable-time"));
    config->setRetransTime(getUint32(json, "retrans-timer"));

    parseExperimental(config, json->get("experimental"));

    parseInterfaces(config, json->get("interfaces-list"));

    // User context can be done at anytime.
    ConstElementPtr user_context = json->get("user-context");
    if (user_context) {
        config->setContext(user_context);
    }
}

};
};
