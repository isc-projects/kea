// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <netconf/netconf_cfg_mgr.h>
#include <netconf/netconf_log.h>
#include <netconf/simple_parser.h>
#include <cc/simple_parser.h>
#include <cc/command_interpreter.h>
#include <exceptions/exceptions.h>

using namespace isc::config;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::data;

namespace isc {
namespace netconf {

NetconfConfig::NetconfConfig()
    : servers_map_(new CfgServersMap()) {
}

NetconfConfig::NetconfConfig(const NetconfConfig& orig)
    : ConfigBase(), servers_map_(orig.servers_map_),
      hooks_config_(orig.hooks_config_) {
}

NetconfCfgMgr::NetconfCfgMgr()
    : DCfgMgrBase(ConfigPtr(new NetconfConfig())) {
}

NetconfCfgMgr::~NetconfCfgMgr() {
}

std::string
NetconfCfgMgr::getConfigSummary(const uint32_t /*selection*/) {

    NetconfConfigPtr ctx = getNetconfConfig();

    // No globals to print.
    std::ostringstream s;

    // Then print managed servers.
    for (auto serv : *ctx->getCfgServersMap()) {
        if (s.tellp() != 0) {
            s << " ";
        }
        s << serv.first;
    }

    if (s.tellp() == 0) {
        s << "none";
    }

    // Finally, print the hook libraries names
    const isc::hooks::HookLibsCollection libs = ctx->getHooksConfig().get();
    s << ", " << libs.size() << " lib(s):";
    for (auto lib = libs.begin(); lib != libs.end(); ++lib) {
        s << lib->first << " ";
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
        isc_throw(DhcpConfigError, "Mandatory config parameter not provided");
    }

    NetconfConfigPtr ctx = getNetconfConfig();

    // Set the defaults
    ElementPtr cfg = boost::const_pointer_cast<Element>(config_set);
    NetconfSimpleParser::setAllDefaults(cfg);

    // And parse the configuration.
    ConstElementPtr answer;
    std::string excuse;
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
        answer = createAnswer(CONTROL_RESULT_SUCCESS,
                              "Configuration check successful");
    } else {
        answer = createAnswer(CONTROL_RESULT_SUCCESS,
                              "Configuration applied successfully.");
    }

    return (answer);
}



ElementPtr
NetconfConfig::toElement() const {
    ElementPtr netconf = Element::createMap();
    // Set user-context
    contextToElement(netconf);
    // Set hooks-libraries
    netconf->set("hooks-libraries", hooks_config_.toElement());
    // Set managed-servers
    ElementPtr servers = Element::createMap();
    for (auto serv : *servers_map_) {
        ConstElementPtr server = serv.second->toElement();
        servers->set(serv.first, server);
    }
    netconf->set("managed-servers", servers);
    // Set Netconf
    ElementPtr result = Element::createMap();
    result->set("Netconf", netconf);

    // Set Logging (not yet)

    return (result);
}

} // namespace isc::netconf
} // namespace isc
