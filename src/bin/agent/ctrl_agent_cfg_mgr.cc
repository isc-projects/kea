// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ctrl_agent_cfg_mgr.h>
#include <agent/ctrl_agent_log.h>
#include <agent/simple_parser.h>
#include <cc/simple_parser.h>
#include <cc/command_interpreter.h>

using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::data;

namespace isc {
namespace agent {

CtrlAgentCfgContext::CtrlAgentCfgContext()
    :http_host_(""), http_port_(0) {

}

CtrlAgentCfgMgr::CtrlAgentCfgMgr()
    : DCfgMgrBase(DCfgContextBasePtr(new CtrlAgentCfgContext())) {
}

CtrlAgentCfgMgr::~CtrlAgentCfgMgr() {
}

std::string
CtrlAgentCfgMgr::getConfigSummary(const uint32_t /*selection*/) {

    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();

    // First print the http stuff.
    std::ostringstream s;
    s << "listening on " << ctx->getHost() << ", port " << ctx->getPort()
      << ", control sockets: ";

    // Then print the control-sockets
    bool socks = false;
    if (ctx->getControlSocketInfo(CtrlAgentCfgContext::TYPE_D2)) {
        s << "d2 ";
        socks = true;
    }
    if (ctx->getControlSocketInfo(CtrlAgentCfgContext::TYPE_DHCP4)) {
        s << "dhcp4 ";
        socks = true;
    }
    if (ctx->getControlSocketInfo(CtrlAgentCfgContext::TYPE_DHCP6)) {
        s << "dhcp6 ";
        socks = true;
    }
    if (!socks) {
        // That's weird
        s << "none";
    }

    // Finally, print the hook libraries names
    const hooks::HookLibsCollection libs = ctx->getLibraries();
    s << ", " << libs.size() << " lib(s):";
    for (auto lib = libs.begin(); lib != libs.end(); ++lib) {
        s << lib->first << " ";
    }

    return (s.str());
}

isc::dhcp::ParserPtr
CtrlAgentCfgMgr::createConfigParser(const std::string& /*element_id*/,
                                    const isc::data::Element::Position& /*pos*/) {
    isc_throw(NotImplemented, "We don't use parser pointers anymore");
}

DCfgContextBasePtr
CtrlAgentCfgMgr::createNewContext() {
    return (DCfgContextBasePtr(new CtrlAgentCfgContext()));
}

isc::data::ConstElementPtr
CtrlAgentCfgMgr::parse(isc::data::ConstElementPtr config_set, bool check_only) {
    if (!config_set) {
        isc_throw(DhcpConfigError, "Mandatory config parameter not provided");
    }

    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();

    // Set the defaults
    ElementPtr cfg = boost::const_pointer_cast<Element>(config_set);
    AgentSimpleParser::setAllDefaults(cfg);

    ConstElementPtr answer;
    std::string excuse;
    try {
        // Do the actual parsing
        AgentSimpleParser parser;
        parser.parse(ctx, cfg, check_only);
    } catch (const isc::Exception& ex) {
        excuse = ex.what();
        answer = isc::config::createAnswer(2, excuse);
    } catch (...) {
        excuse = "undefined configuration parsing error";
        answer = isc::config::createAnswer(2, excuse);
    }

    if (answer) {
        if (check_only) {
            LOG_ERROR(agent_logger, CTRL_AGENT_CONFIG_CHECK_FAIL).arg(excuse);
        } else {
            LOG_ERROR(agent_logger, CTRL_AGENT_CONFIG_FAIL).arg(excuse);
        }
        return (answer);
    }

    if (check_only) {
        answer = isc::config::createAnswer(0, "Configuration check successful");
        LOG_INFO(agent_logger, CTRL_AGENT_CONFIG_CHECK_COMPLETE)
            .arg(getConfigSummary(0));
    } else {
        answer = isc::config::createAnswer(0, "Configuration applied successfully.");
        LOG_INFO(agent_logger, CTRL_AGENT_CONFIG_COMPLETE)
            .arg(getConfigSummary(0));
    }

    return (answer);
}

} // namespace isc::agent
} // namespace isc
