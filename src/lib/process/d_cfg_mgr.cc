// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <dhcp/libdhcp++.h>
#include <process/d_log.h>
#include <process/d_cfg_mgr.h>
#include <process/daemon.h>
#include <process/redact_config.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <limits>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace process {

// *********************** DCfgMgrBase  *************************

DCfgMgrBase::DCfgMgrBase(ConfigPtr context) {
    setContext(context);
}

DCfgMgrBase::~DCfgMgrBase() {
}

void
DCfgMgrBase::resetContext() {
    ConfigPtr context = createNewContext();
    setContext(context);
}

void
DCfgMgrBase::setContext(ConfigPtr& context) {
    if (!context) {
        isc_throw(DCfgMgrBaseError, "DCfgMgrBase: context cannot be NULL");
    }

    context_ = context;
}

ConstElementPtr
DCfgMgrBase::redactConfig(ConstElementPtr const& config) const {
    ConstElementPtr result(config);
    for (std::list<std::string>& json_path : jsonPathsToRedact()) {
        result = isc::process::redactConfig(result, json_path);
    }
    return result;
}

list<list<string>> DCfgMgrBase::jsonPathsToRedact() const {
    static list<list<string>> const list;
    return list;
}

isc::data::ConstElementPtr
DCfgMgrBase::simpleParseConfig(isc::data::ConstElementPtr config_set,
                               bool check_only,
                               const std::function<void()>& post_config_cb) {
    if (!config_set) {
        return (isc::config::createAnswer(1,
                                    std::string("Can't parse NULL config")));
    }
    LOG_DEBUG(dctl_logger, isc::log::DBGLVL_COMMAND, DCTL_CONFIG_START)
        .arg(redactConfig(config_set)->str());

    // The parsers implement data inheritance by directly accessing
    // configuration context. For this reason the data parsers must store
    // the parsed data into context immediately. This may cause data
    // inconsistency if the parsing operation fails after the context has been
    // modified. We need to preserve the original context here
    // so as we can rollback changes when an error occurs.
    ConfigPtr original_context = context_;
    resetContext();
    bool rollback = false;

    // Answer will hold the result returned to the caller.
    ConstElementPtr answer;

    try {
        // Logging is common so factor it.
        Daemon::configureLogger(config_set, context_);

        // Let's call the actual implementation
        answer = parse(config_set, check_only);

        // and check the response returned.
        int code = 0;
        isc::config::parseAnswer(code, answer);

        // Everything was fine. Configuration set processed successfully.
        if (!check_only) {
            if (code == 0) {
                // Call the callback only when parsing was successful.
                if (post_config_cb) {
                    post_config_cb();
                }
                LOG_INFO(dctl_logger, DCTL_CONFIG_COMPLETE).arg(getConfigSummary(0));
                // Set the last commit timestamp.
                auto now = boost::posix_time::second_clock::universal_time();
                context_->setLastCommitTime(now);
            } else {
                rollback = true;
            }

            // Use the answer provided.
            //answer = isc::config::createAnswer(0, "Configuration committed.");
        } else {
            LOG_INFO(dctl_logger, DCTL_CONFIG_CHECK_COMPLETE)
                .arg(getConfigSummary(0))
                .arg(config::answerToText(answer));
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(dctl_logger, DCTL_PARSER_FAIL).arg(ex.what());
        answer = isc::config::createAnswer(1, ex.what());
        rollback = true;
    }

    if (check_only) {
        // If this is a configuration check only, then don't actually apply
        // the configuration and reverse to the previous one.
        context_ = original_context;
    }

    if (rollback) {
        // An error occurred, so make sure that we restore original context.
        context_ = original_context;
    }

    return (answer);
}


void
DCfgMgrBase::setCfgDefaults(isc::data::ElementPtr) {
}

isc::data::ConstElementPtr
DCfgMgrBase::parse(isc::data::ConstElementPtr, bool) {
    isc_throw(DCfgMgrBaseError, "This class does not implement simple parser paradigm yet");
}

} // end of isc::dhcp namespace
} // end of isc namespace
