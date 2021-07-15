// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <netconf/simple_parser.h>
#include <netconf/netconf_config.h>
#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <hooks/hooks_manager.h>
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
    { "boot-update",       Element::boolean, "true" },
    { "subscribe-changes", Element::boolean, "true" },
    { "validate-changes",  Element::boolean, "true" }
};

/// @brief Supplies defaults for control-socket elements
const SimpleDefaults NetconfSimpleParser::CTRL_SOCK_DEFAULTS = {
    { "socket-type", Element::string, "stdout" },
    { "socket-name", Element::string, "" },
    { "socket-url" , Element::string, "http://127.0.0.1:8000/" }
};

/// @brief Supplies defaults for dhcp4 managed server
const SimpleDefaults NetconfSimpleParser::DHCP4_DEFAULTS = {
    { "model", Element::string, "kea-dhcp4-server" }
};

/// @brief Supplies defaults for dhcp6 managed server
const SimpleDefaults NetconfSimpleParser::DHCP6_DEFAULTS = {
    { "model", Element::string, "kea-dhcp6-server" }
};

/// @brief Supplies defaults for d2 managed server
const SimpleDefaults NetconfSimpleParser::D2_DEFAULTS = {
    { "model", Element::string, "kea-dhcp-ddns" }
};

/// @brief Supplies defaults for ca managed server
const SimpleDefaults NetconfSimpleParser::CA_DEFAULTS = {
    { "model", Element::string, "kea-ctrl-agent" }
};

/// @brief List of parameters that can be inherited to managed-servers scope.
///
/// Some parameters may be defined on both global (directly in Netconf) and
/// servers (Netconf/managed-servers/...) scope. If not defined in the
/// managed-servers scope, the value is being inherited (derived) from
/// the global scope. This array lists all of such parameters.
const ParamsList NetconfSimpleParser::INHERIT_TO_SERVERS = {
    "boot-update",
    "subscribe-changes",
    "validate-changes"
};

/// @}

/// ---------------------------------------------------------------------------
/// --- end of default values -------------------------------------------------
/// ---------------------------------------------------------------------------

size_t NetconfSimpleParser::setAllDefaults(const ElementPtr& global) {
    size_t cnt = 0;

    // Set global defaults first.
    cnt = setDefaults(global, NETCONF_DEFAULTS);

    ConstElementPtr servers = global->get("managed-servers");
    if (servers) {
        for (auto it : servers->mapValue()) {
            cnt += setServerDefaults(it.first, it.second);
        }
    }

    return (cnt);
}

size_t NetconfSimpleParser::deriveParameters(ConstElementPtr global) {
    size_t cnt = 0;

    // Now derive global parameters into managed-servers.
    ConstElementPtr servers = global->get("managed-servers");
    if (servers) {
        for (auto it : servers->mapValue()) {
            ElementPtr mutable_server =
                boost::const_pointer_cast<Element>(it.second);
            cnt += SimpleParser::deriveParams(global,
                                              mutable_server,
                                              INHERIT_TO_SERVERS);
        }
    }

    return (cnt);
}

size_t
NetconfSimpleParser::setServerDefaults(const std::string name,
                                       ConstElementPtr server) {
    size_t cnt = 0;

    ElementPtr mutable_server =
        boost::const_pointer_cast<Element>(server);
    if (name == "dhcp4") {
        cnt += setDefaults(mutable_server, DHCP4_DEFAULTS);
    } else if (name == "dhcp6") {
        cnt += setDefaults(mutable_server, DHCP6_DEFAULTS);
    } else if (name == "d2") {
        cnt += setDefaults(mutable_server, D2_DEFAULTS);
    } else if (name == "ca") {
        cnt += setDefaults(mutable_server, CA_DEFAULTS);
    }

    ConstElementPtr ctrl_sock = server->get("control-socket");
    if (!ctrl_sock) {
        return (cnt);
    }
    ElementPtr mutable_ctrl_sock =
        boost::const_pointer_cast<Element>(ctrl_sock);
    cnt += setDefaults(mutable_ctrl_sock, CTRL_SOCK_DEFAULTS);

    return (cnt);
}

void
NetconfSimpleParser::parse(const NetconfConfigPtr& ctx,
                           const ConstElementPtr& config,
                           bool check_only) {

    // User context can be done at anytime.
    ConstElementPtr user_context = config->get("user-context");
    if (user_context) {
        ctx->setContext(user_context);
    }

    // get managed servers.
    ConstElementPtr servers = config->get("managed-servers");
    if (servers) {
        for (auto it : servers->mapValue()) {
            ServerConfigParser server_parser;
            CfgServerPtr server = server_parser.parse(it.second);
            ctx->getCfgServersMap()->insert(make_pair(it.first, server));
        }
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
        HooksManager::prepareUnloadLibraries();
        static_cast<void>(HooksManager::unloadLibraries());
        libraries.loadLibraries();
    }
}

}  // namespace netconf
}  // namespace isc
