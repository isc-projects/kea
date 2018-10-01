// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <netconf/simple_parser.h>
#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <hooks/hooks_parser.h>
#include <boost/foreach.hpp>

using namespace isc::data;

namespace isc {
namespace netconf {
/// @brief This sets of arrays define the default values in various scopes
///        of the Netconf Configuration.
///
/// Each of those is documented in @file netconf/simple_parser.cc. This
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
/// These are global Netconf parameters.
const SimpleDefaults NetconfSimpleParser::NETCONF_DEFAULTS = {
};

/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t NetconfSimpleParser::setAllDefaults(const isc::data::ElementPtr& global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, NETCONF_DEFAULTS);

    return (cnt);
}

void
NetconfSimpleParser::parse(const NetconfCfgContextPtr& ctx,
                           const isc::data::ConstElementPtr& config,
                           bool check_only) {

    // User context can be done at anytime.
    ConstElementPtr user_context = config->get("user-context");
    if (user_context) {
        ctx->setContext(user_context);
    }

    // Finally, let's get the hook libs!
    using namespace isc::hooks;
    HooksConfig& libraries = ctx->getHooksConfig();
    ConstElementPtr hooks = config->get("hooks-libraries");
    if (hooks) {
        HooksLibrariesParser hooks_parser;
        hooks_parser.parse(libraries, hooks);
        libraries.verifyLibraries(hooks->getPosition());
    }

    if (!check_only) {
        // This occurs last as if it succeeds, there is no easy way
        // revert it.  As a result, the failure to commit a subsequent
        // change causes problems when trying to roll back.
        libraries.loadLibraries();
    }
}

};
};
