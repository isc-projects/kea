// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_cfg_mgr.h>
#include <agent/ca_log.h>
#include <agent/simple_parser.h>
#include <cc/simple_parser.h>
#include <cc/command_interpreter.h>
#include <exceptions/exceptions.h>

using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::data;

namespace isc {
namespace agent {

CtrlAgentCfgContext::CtrlAgentCfgContext()
    :http_host_(""), http_port_(0) {
}

CtrlAgentCfgContext::CtrlAgentCfgContext(const CtrlAgentCfgContext& orig)
    : DCfgContextBase(),http_host_(orig.http_host_), http_port_(orig.http_port_),
      hooks_config_(orig.hooks_config_) {

    // We're copying pointers here only. The underlying data will be shared by
    // old and new context. That's how shared pointers work and I see no reason
    // why it would be different in this particular here.
    ctrl_sockets_[TYPE_D2] = orig.ctrl_sockets_[TYPE_D2];
    ctrl_sockets_[TYPE_DHCP4] = orig.ctrl_sockets_[TYPE_DHCP4];
    ctrl_sockets_[TYPE_DHCP6] = orig.ctrl_sockets_[TYPE_DHCP6];
}

CtrlAgentCfgContext::ServerType
CtrlAgentCfgContext::toServerType(const std::string& service) {
    if (service == "dhcp4") {
        return (CtrlAgentCfgContext::TYPE_DHCP4);

    } else if (service == "dhcp6") {
        return (CtrlAgentCfgContext::TYPE_DHCP6);

    } else if (service == "d2") {
        return (CtrlAgentCfgContext::TYPE_D2);
    }

    isc_throw(isc::BadValue, "invalid service value " << service);
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
    s << "listening on " << ctx->getHttpHost() << ", port "
      << ctx->getHttpPort() << ", control sockets: ";

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
        // That's uncommon, but correct scenario. CA can respond to some
        // commands on its own. Further down the road we will possibly get the
        // capability to tell CA to start other servers.
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
    // Do a sanity check first.
    if (!config_set) {
        isc_throw(DhcpConfigError, "Mandatory config parameter not provided");
    }

    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();

    // Set the defaults
    ElementPtr cfg = boost::const_pointer_cast<Element>(config_set);
    AgentSimpleParser::setAllDefaults(cfg);

    // And parse the configuration.
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

    // At this stage the answer was created only in case of exception.
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
    } else {
        answer = isc::config::createAnswer(0, "Configuration applied successfully.");
    }

    return (answer);
}

const data::ConstElementPtr
CtrlAgentCfgContext::getControlSocketInfo(ServerType type) const {
    if (type > MAX_TYPE_SUPPORTED) {
        isc_throw(BadValue, "Invalid server type");
    }
    return (ctrl_sockets_[static_cast<uint8_t>(type)]);
}

void
CtrlAgentCfgContext::setControlSocketInfo(const isc::data::ConstElementPtr& control_socket,
                                          ServerType type) {
    if (type > MAX_TYPE_SUPPORTED) {
        isc_throw(BadValue, "Invalid server type");
    }
    ctrl_sockets_[static_cast<uint8_t>(type)] = control_socket;
}

ElementPtr
CtrlAgentCfgContext::toElement() const {
    ElementPtr ca = Element::createMap();
    // Set http-host
    ca->set("http-host", Element::create(http_host_));
    // Set http-port
    ca->set("http-port", Element::create(static_cast<int64_t>(http_port_)));
    // Set hooks-libraries
    ca->set("hooks-libraries", hooks_config_.toElement());
    // Set control-sockets
    ElementPtr control_sockets = Element::createMap();
    // Set dhcp4-server
    if (ctrl_sockets_[TYPE_DHCP4]) {
        control_sockets->set("dhcp4-server", ctrl_sockets_[TYPE_DHCP4]);
    }
    // Set dhcp6-server
    if (ctrl_sockets_[TYPE_DHCP6]) {
        control_sockets->set("dhcp6-server", ctrl_sockets_[TYPE_DHCP6]);
    }
    // Set d2-server
    if (ctrl_sockets_[TYPE_D2]) {
        control_sockets->set("d2-server", ctrl_sockets_[TYPE_D2]);
    }
    ca->set("control-sockets", control_sockets);
    // Set Control-agent
    ElementPtr result = Element::createMap();
    result->set("Control-agent", ca);

    // Set Logging (not yet)

    return (result);
}

} // namespace isc::agent
} // namespace isc
