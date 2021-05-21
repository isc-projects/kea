// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
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
#include <http/basic_auth_config.h>
#include <exceptions/exceptions.h>

using namespace isc::config;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::data;

namespace isc {
namespace agent {

CtrlAgentCfgContext::CtrlAgentCfgContext()
    : http_host_(""), http_port_(0),
      trust_anchor_(""), cert_file_(""), key_file_(""), cert_required_(true) {
}

CtrlAgentCfgContext::CtrlAgentCfgContext(const CtrlAgentCfgContext& orig)
    : ConfigBase(), ctrl_sockets_(orig.ctrl_sockets_),
      http_host_(orig.http_host_), http_port_(orig.http_port_),
      trust_anchor_(orig.trust_anchor_), cert_file_(orig.cert_file_),
      key_file_(orig.key_file_), cert_required_(orig.cert_required_),
      hooks_config_(orig.hooks_config_), auth_config_(orig.auth_config_) {
}

CtrlAgentCfgMgr::CtrlAgentCfgMgr()
    : DCfgMgrBase(ConfigPtr(new CtrlAgentCfgContext())) {
}

CtrlAgentCfgMgr::~CtrlAgentCfgMgr() {
}

std::string
CtrlAgentCfgMgr::getConfigSummary(const uint32_t /*selection*/) {

    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();

    // First print the http stuff.
    std::ostringstream s;
    s << "listening on " << ctx->getHttpHost() << ", port "
      << ctx->getHttpPort();

    // When TLS is setup print its config.
    if (!ctx->getTrustAnchor().empty()) {
        s << ", trust anchor " << ctx->getTrustAnchor()
          << ", cert file " << ctx->getCertFile()
          << ", key file " << ctx->getKeyFile();
        if (ctx->getCertRequired()) {
            s << ", client certs are required";
        } else {
            s << ", client certs are optional";
        }
    }
    s << ", control sockets: ";

    // Then print the control-sockets
    s << ctx->getControlSocketInfoSummary();

    // Add something if authentication is required.
    const isc::http::HttpAuthConfigPtr& auth = ctx->getAuthConfig();
    if (auth && !auth->empty()) {
        s << ", requires basic HTTP authentication";
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
CtrlAgentCfgMgr::createNewContext() {
    return (ConfigPtr(new CtrlAgentCfgContext()));
}

ConstElementPtr
CtrlAgentCfgMgr::parse(ConstElementPtr config_set, bool check_only) {
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
        parser.checkTlsSetup(cfg);
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
            LOG_ERROR(agent_logger, CTRL_AGENT_CONFIG_CHECK_FAIL).arg(excuse);
        } else {
            LOG_ERROR(agent_logger, CTRL_AGENT_CONFIG_FAIL).arg(excuse);
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

std::list<std::list<std::string>>
CtrlAgentCfgMgr::jsonPathsToRedact() const {
    static std::list<std::list<std::string>> const list({
        {"authentication", "clients", "[]"},
        {"hooks-libraries", "[]", "parameters", "*"},
    });
    return list;
}

data::ConstElementPtr
CtrlAgentCfgContext::getControlSocketInfo(const std::string& service) const {
    auto si = ctrl_sockets_.find(service);
    return ((si != ctrl_sockets_.end()) ? si->second : ConstElementPtr());
}

void
CtrlAgentCfgContext::setControlSocketInfo(const ConstElementPtr& control_socket,
                                          const std::string& service) {
    ctrl_sockets_[service] = control_socket;
}

std::string
CtrlAgentCfgContext::getControlSocketInfoSummary() const {
    std::ostringstream s;
    for (auto si = ctrl_sockets_.cbegin(); si != ctrl_sockets_.end(); ++si) {
        if (s.tellp() != 0) {
            s << " ";
        }
        s << si->first;
    }

    if (s.tellp() == 0) {
        s << "none";
    }

    return (s.str());
}

ElementPtr
CtrlAgentCfgContext::toElement() const {
    ElementPtr ca = ConfigBase::toElement();
    // Set user-context
    contextToElement(ca);
    // Set http-host
    ca->set("http-host", Element::create(http_host_));
    // Set http-port
    ca->set("http-port", Element::create(static_cast<int64_t>(http_port_)));
    // Set TLS setup when enabled
    if (!trust_anchor_.empty()) {
        ca->set("trust-anchor", Element::create(trust_anchor_));
        ca->set("cert-file", Element::create(cert_file_));
        ca->set("key-file", Element::create(key_file_));
        ca->set("cert-required", Element::create(cert_required_));
    }
    // Set authentication
    if (auth_config_) {
        ca->set("authentication", auth_config_->toElement());
    }
    ca->set("hooks-libraries", hooks_config_.toElement());
    // Set control-sockets
    ElementPtr control_sockets = Element::createMap();
    for (auto si = ctrl_sockets_.cbegin(); si != ctrl_sockets_.cend(); ++si) {
        ConstElementPtr socket = UserContext::toElement(si->second);
        control_sockets->set(si->first, socket);
    }
    ca->set("control-sockets", control_sockets);
    // Set Control-agent
    ElementPtr result = Element::createMap();
    result->set("Control-agent", ca);

    return (result);
}

} // namespace isc::agent
} // namespace isc
