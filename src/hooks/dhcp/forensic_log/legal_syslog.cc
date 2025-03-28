// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfgmgr.h>
#include <legal_log_log.h>
#include <legal_syslog.h>
#include <log/logger_manager.h>
#include <log/message_initializer.h>
#include <log/macros.h>
#include <process/logging_info.h>

using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::log;
using namespace isc::process;
using namespace std;

namespace isc {
namespace legal_log {

LegalSyslog::LegalSyslog(const DatabaseConnection::ParameterMap& parameters)
    : LegalLogMgr(parameters) {
    LoggingInfo info;
    // Remove default destinations as we are going to replace them.
    info.clearDestinations();
    info.name_ = "legal-log-syslog-";
    info.name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    logger_.reset(new Logger(info.name_.c_str()));
    LoggingDestination dest;
    dest.output_ = "syslog:";
    if (parameters.find("facility") != parameters.end()) {
        dest.output_ += parameters.at("facility");
    } else {
        dest.output_ += "LOCAL0";
    }
    if (parameters.find("pattern") != parameters.end()) {
        dest.pattern_ = parameters.at("pattern");
    }
    info.destinations_.push_back(dest);
    CfgMgr::instance().getStagingCfg()->addLoggingInfo(info);
}

void
LegalSyslog::open() {
}

void
LegalSyslog::close() {
}

void
LegalSyslog::writeln(const string& text, const string&) {
    LOG_INFO(*logger_, LEGAL_SYSLOG_LOG)
        .arg(text);
}

string
LegalSyslog::getType() const {
    return ("syslog");
}

LegalLogMgrPtr
LegalSyslog::factory(const DatabaseConnection::ParameterMap& parameters) {
    LOG_INFO(legal_log_logger, LEGAL_SYSLOG_STORE_OPEN)
        .arg(DatabaseConnection::redactedAccessString(parameters));
    return (LegalLogMgrPtr(new LegalSyslog(parameters)));
}

} // namespace legal_log
} // namespace isc
