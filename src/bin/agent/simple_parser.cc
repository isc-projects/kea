// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <agent/simple_parser.h>
#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <hooks/hooks_parser.h>
#include <boost/foreach.hpp>

using namespace isc::data;

namespace isc {
namespace agent {
/// @brief This sets of arrays define the default values in various scopes
///        of the Control Agent Configuration.
///
/// Each of those is documented in @file agent/simple_parser.cc. This
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
/// These are global Control Agent parameters.
const SimpleDefaults AgentSimpleParser::AGENT_DEFAULTS = {
    { "http-host",    Element::string,  "127.0.0.1"},
    { "http-port",    Element::integer,  "8000"}
};

/// @brief This table defines default values for control sockets.
///
const SimpleDefaults AgentSimpleParser::SOCKET_DEFAULTS = {
    { "socket-type",  Element::string,  "unix"}
};

/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t AgentSimpleParser::setAllDefaults(const isc::data::ElementPtr& global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, AGENT_DEFAULTS);

    // Now set the defaults for control-sockets, if any.
    ConstElementPtr sockets = global->get("control-sockets");
    if (sockets) {
        ElementPtr d2 = boost::const_pointer_cast<Element>(sockets->get("d2"));
        if (d2) {
            cnt += SimpleParser::setDefaults(d2, SOCKET_DEFAULTS);
        }

        ElementPtr d4 = boost::const_pointer_cast<Element>(sockets->get("dhcp4"));
        if (d4) {
            cnt += SimpleParser::setDefaults(d4, SOCKET_DEFAULTS);
        }

        ElementPtr d6 = boost::const_pointer_cast<Element>(sockets->get("dhcp6"));
        if (d6) {
            cnt += SimpleParser::setDefaults(d6, SOCKET_DEFAULTS);
        }
    }

    return (cnt);
}

void
AgentSimpleParser::parse(const CtrlAgentCfgContextPtr& ctx,
                         const isc::data::ConstElementPtr& config,
                         bool check_only) {

    // Let's get the HTTP parameters first.
    ctx->setHttpHost(SimpleParser::getString(config, "http-host"));
    ctx->setHttpPort(SimpleParser::getIntType<uint16_t>(config, "http-port"));

    // Control sockets are second.
    ConstElementPtr ctrl_sockets = config->get("control-sockets");
    if (ctrl_sockets) {
        auto sockets_map = ctrl_sockets->mapValue();
        for (auto cs = sockets_map.cbegin(); cs != sockets_map.cend(); ++cs) {
            ctx->setControlSocketInfo(cs->second, cs->first);
        }
    }

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
