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

using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::data;

namespace isc {
namespace netconf {

NetconfCfgContext::NetconfCfgContext() {
}

NetconfCfgContext::NetconfCfgContext(const NetconfCfgContext& orig)
    : DCfgContextBase(), hooks_config_(orig.hooks_config_) {
}

NetconfCfgMgr::NetconfCfgMgr()
    : DCfgMgrBase(DCfgContextBasePtr(new NetconfCfgContext())) {
}

NetconfCfgMgr::~NetconfCfgMgr() {
}

std::string
NetconfCfgMgr::getConfigSummary(const uint32_t /*selection*/) {

    NetconfCfgContextPtr ctx = getNetconfCfgContext();

    std::ostringstream s;

    // Finally, print the hook libraries names
    const isc::hooks::HookLibsCollection libs = ctx->getHooksConfig().get();
    s << ", " << libs.size() << " lib(s):";
    for (auto lib = libs.begin(); lib != libs.end(); ++lib) {
        s << lib->first << " ";
    }

    return (s.str());
}

DCfgContextBasePtr
NetconfCfgMgr::createNewContext() {
    return (DCfgContextBasePtr(new NetconfCfgContext()));
}

isc::data::ConstElementPtr
NetconfCfgMgr::parse(isc::data::ConstElementPtr config_set,
                     bool check_only) {
    // Do a sanity check first.
    if (!config_set) {
        isc_throw(DhcpConfigError, "Mandatory config parameter not provided");
    }

    NetconfCfgContextPtr ctx = getNetconfCfgContext();

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
        answer = isc::config::createAnswer(2, excuse);
    } catch (...) {
        excuse = "undefined configuration parsing error";
        answer = isc::config::createAnswer(2, excuse);
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
        answer = isc::config::createAnswer(0, "Configuration check successful");
    } else {
        answer = isc::config::createAnswer(0, "Configuration applied successfully.");
    }

    return (answer);
}

ElementPtr
NetconfCfgContext::toElement() const {
    ElementPtr netconf = Element::createMap();
    // Set user-context
    contextToElement(netconf);
    // Set hooks-libraries
    netconf->set("hooks-libraries", hooks_config_.toElement());
    // Set Netconf
    ElementPtr result = Element::createMap();
    result->set("Netconf", netconf);

    // Set Logging (not yet)

    return (result);
}

} // namespace isc::netconf
} // namespace isc
