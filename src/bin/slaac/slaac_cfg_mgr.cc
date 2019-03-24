// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/slaac_cfg_mgr.h>
#include <slaac/slaac_log.h>
#include <slaac/simple_parser.h>
#include <cc/simple_parser.h>
#include <cc/command_interpreter.h>
#include <exceptions/exceptions.h>

using namespace isc::config;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::data;

namespace isc {
namespace slaac {

SlaacConfig::SlaacConfig() {
}

SlaacConfig::SlaacConfig(const SlaacConfig& orig)
    : ConfigBase(), ctrl_sockets_(orig.ctrl_sockets_),
      hooks_config_(orig.hooks_config_) {
}

SlaacCfgMgr::SlaacCfgMgr()
    : DCfgMgrBase(ConfigPtr(new SlaacConfig())) {
}

SlaacCfgMgr::~SlaacCfgMgr() {
}

std::string
SlaacCfgMgr::getConfigSummary(const uint32_t /*selection*/) {

    SlaacConfigPtr ctx = getSlaacConfig();

    // First print the http stuff.
    std::ostringstream s;
    s << "listening on TBD interface(s), control sockets: ";

    // Then print the control-sockets
    s << ctx->getControlSocketInfoSummary();

    // Finally, print the hook libraries names
    const isc::hooks::HookLibsCollection libs = ctx->getHooksConfig().get();
    s << ", " << libs.size() << " lib(s):";
    for (auto lib = libs.begin(); lib != libs.end(); ++lib) {
        s << lib->first << " ";
    }

    return (s.str());
}

ConfigPtr
SlaacCfgMgr::createNewContext() {
    return (ConfigPtr(new SlaacConfig()));
}

isc::data::ConstElementPtr
SlaacCfgMgr::parse(isc::data::ConstElementPtr config_set, bool check_only) {
    // Do a sanity check first.
    if (!config_set) {
        isc_throw(DhcpConfigError, "Mandatory config parameter not provided");
    }

    SlaacConfigPtr config = getSlaacConfig();

    // Set the defaults
    ElementPtr json_cfg = boost::const_pointer_cast<Element>(config_set);

    SlaacSimpleParser::setAllDefaults(json_cfg);

    // And parse the configuration.
    ConstElementPtr answer;
    std::string excuse;
    try {
        // Do the actual parsing
        SlaacSimpleParser parser;
        parser.parse(config, json_cfg, check_only);
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
            LOG_ERROR(slaac_logger, SLAAC_CONFIG_CHECK_FAIL).arg(excuse);
        } else {
            LOG_ERROR(slaac_logger, SLAAC_CONFIG_FAIL).arg(excuse);
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

data::ConstElementPtr
SlaacConfig::getControlSocketInfo(const std::string& service) const {
    auto si = ctrl_sockets_.find(service);
    return ((si != ctrl_sockets_.end()) ? si->second : ConstElementPtr());
}

void
SlaacConfig::setControlSocketInfo(const isc::data::ConstElementPtr& control_socket,
                                          const std::string& service) {
    ctrl_sockets_[service] = control_socket;
}

std::string
SlaacConfig::getControlSocketInfoSummary() const {
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
SlaacConfig::toElement() const {
    ElementPtr ca = Element::createMap();
    // Set user-context
    contextToElement(ca);
    // Set hooks-libraries
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

    // Set Logging (not yet)

    return (result);
}

} // namespace isc::agent
} // namespace isc
