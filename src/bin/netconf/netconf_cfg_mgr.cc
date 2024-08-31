// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <cc/simple_parser.h>
#include <exceptions/exceptions.h>
#include <netconf/netconf_cfg_mgr.h>
#include <netconf/netconf_log.h>
#include <netconf/simple_parser.h>

#include <map>
#include <sstream>

using namespace isc::config;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::data;
using namespace isc::hooks;

using namespace std;

namespace isc {
namespace netconf {

NetconfConfig::NetconfConfig()
    : configured_globals_(Element::createMap()),
      servers_map_(new CfgServersMap()) {
}

NetconfConfig::NetconfConfig(const NetconfConfig& orig)
    : ConfigBase(), configured_globals_(orig.configured_globals_),
      servers_map_(orig.servers_map_), hooks_config_(orig.hooks_config_) {
}

void
NetconfConfig::extractConfiguredGlobals(ConstElementPtr config) {
    if (config->getType() != Element::map) {
        isc_throw(BadValue,
                  "extractConfiguredGlobals must be given a map element");
    }

    for (auto const& value : config->mapValue()) {
        if (value.second->getType() != Element::list &&
            value.second->getType() != Element::map) {
            addConfiguredGlobal(value.first, value.second);
        }
    }
}

NetconfCfgMgr::NetconfCfgMgr()
    : DCfgMgrBase(ConfigPtr(new NetconfConfig())) {
}

string
NetconfCfgMgr::getConfigSummary(const uint32_t /*selection*/) {

    NetconfConfigPtr ctx = getNetconfConfig();

    // No globals to print.
    ostringstream s;

    // Then print managed servers.
    for (auto const& serv : *ctx->getCfgServersMap()) {
        if (s.tellp() != 0) {
            s << " ";
        }
        s << serv.first;
    }

    if (s.tellp() == 0) {
        s << "none";
    }

    // Finally, print the hook libraries names
    const HookLibsCollection libs = ctx->getHooksConfig().get();
    s << ", " << libs.size() << " lib(s):";
    for (HookLibInfo const& lib : libs) {
        s << lib.first << " ";
    }

    return (s.str());
}

ConfigPtr
NetconfCfgMgr::createNewContext() {
    return (ConfigPtr(new NetconfConfig()));
}

isc::data::ConstElementPtr
NetconfCfgMgr::parse(isc::data::ConstElementPtr config_set,
                     bool check_only) {
    // Do a sanity check first.
    if (!config_set) {
        isc_throw(ConfigError, "Mandatory config parameter not provided");
    }

    NetconfConfigPtr ctx = getNetconfConfig();

    // Preserve all scalar global parameters.
    ctx->extractConfiguredGlobals(config_set);

    // Set the defaults and derive parameters.
    ElementPtr cfg = copy(config_set, 0);
    NetconfSimpleParser::setAllDefaults(cfg);
    NetconfSimpleParser::deriveParameters(cfg);

    // And parse the configuration.
    ConstElementPtr answer;
    string excuse;
    try {
        // Do the actual parsing
        NetconfSimpleParser parser;
        parser.parse(ctx, cfg, check_only);
    } catch (const isc::Exception& ex) {
        excuse = ex.what();
        answer = createAnswer(CONTROL_RESULT_ERROR, excuse);
    } catch (...) {
        excuse = "undefined configuration parsing error";
        answer = createAnswer(CONTROL_RESULT_ERROR, excuse);
    }

    // At this stage the answer was created only in case of exception.
    if (answer) {
        if (check_only) {
            LOG_ERROR(netconf_logger, NETCONF_CONFIG_CHECK_FAIL).arg(excuse);
        } else {
            LOG_ERROR(netconf_logger, NETCONF_CONFIG_FAIL).arg(excuse);
        }
        return (answer);
    }

    if (check_only) {
        answer = createAnswer(CONTROL_RESULT_SUCCESS, "Configuration check successful");
    } else {
        answer = createAnswer(CONTROL_RESULT_SUCCESS, "Configuration applied successfully.");
    }

    return (answer);
}

ElementPtr
NetconfConfig::toElement() const {
    ElementPtr netconf = ConfigBase::toElement();
    // Set user-context
    contextToElement(netconf);
    // Add in explicitly configured globals.
    netconf->setValue(configured_globals_->mapValue());
    // Set hooks-libraries
    netconf->set("hooks-libraries", hooks_config_.toElement());
    // Set managed-servers
    ElementPtr servers = Element::createMap();
    for (auto const& serv : *servers_map_) {
        ElementPtr server = serv.second->toElement();
        servers->set(serv.first, server);
    }
    netconf->set("managed-servers", servers);
    // Set Netconf
    ElementPtr result = Element::createMap();
    result->set("Netconf", netconf);
    return (result);
}

list<list<string>>
NetconfCfgMgr::jsonPathsToRedact() const {
    static list<list<string>> const list({
        {"hooks-libraries", "[]", "parameters", "*"},
    });
    return list;
}

}  // namespace netconf
}  // namespace isc
