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
    ElementPtr slaac = Element::createMap();
    // Set user-context
    contextToElement(slaac);
    // No hooks-libraries
    // No control-sockets

    // Add hop limit
    slaac->set("hop-limit",
               Element::create(static_cast<int64_t>(getHopLimit())));
    // Add managed flag
    slaac->set("managed-flag", Element::create(getManagedFlag()));
    // Add other flag
    slaac->set("other-flag", Element::create(getOtherFlag()));
    // Add router lifetime
    slaac->set("router-lifetime",
               Element::create(static_cast<int64_t>(getRouterLifetime())));
    // Add reachable time
    slaac->set("reachable-time",
               Element::create(static_cast<int64_t>(getReachableTime())));
    // Add retrans timer
    slaac->set("retrans-timer",
               Element::create(static_cast<int64_t>(getRetransTimer())));

    // Add source ll address
    slaac->set("source-ll-address", Element::create(getSrcLlAddr()));
    // Add mtu
    slaac->set("mtu", Element::create(static_cast<int64_t>(getMtu())));
    // Add universal ra
    ConstElementPtr universal_ra = getUnivRa();
    if (universal_ra) {
        slaac->set("universal-ra", universal_ra);
    }

    // @todo add prefix infos
    // @todo add interfaces config

    // Set Slaac
    ElementPtr result = Element::createMap();
    result->set("Slaac", slaac);

    // Set Logging (not yet)

    return (result);
}

ElementPtr
PrefixInfoConfig::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context
    contextToElement(result);

    // Set prefix
    std::ostringstream pref;
    pref << getPrefix() << "/" << static_cast<unsigned>(getPrefixLength());
    result->set("prefix", Element::create(pref.str()));

    // Set on link (L) flag
    result->set("on-link-flag", Element::create(getOnLinkFlag()));
    // Set autonomous address configuration (A) flag
    result->set("address-config", Element::create(getAddrConfigFlag()));
    // Set valid lifetime
    result->set("valid-lifetime",
                Element::create(static_cast<int64_t>(getValidLifetime())));
    // Set preferred lifetime
    result->set("preferred-lifetime",
                Element::create(static_cast<int64_t>(getPreferredLifetime())));

    return (result);
}

} // namespace isc::agent
} // namespace isc
