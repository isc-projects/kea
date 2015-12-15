// Copyright (C) 2011, 2014-2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <stdarg.h>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/algorithm/string.hpp>

#include <log4cplus/version.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

#include <log/logger.h>
#include <log/logger_impl.h>
#include <log/logger_level.h>
#include <log/logger_level_impl.h>
#include <log/logger_name.h>
#include <log/logger_manager.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/interprocess/interprocess_sync_file.h>
#include <log/interprocess/interprocess_sync_null.h>

#include <util/strutil.h>

// Note: as log4cplus and the Kea logger have many concepts in common, and
// thus many similar names, to disambiguate types we don't "use" the log4cplus
// namespace: instead, all log4cplus types are explicitly qualified.

using namespace std;

namespace isc {
namespace log {

/// @brief detects whether file locking is enabled or disabled
///
/// The lockfile is enabled by default. The only way to disable it is to
/// set KEA_LOCKFILE_DIR variable to 'none'.
/// @return true if lockfile is enabled, false otherwise
bool lockfileEnabled() {
    const char* const env = getenv("KEA_LOCKFILE_DIR");
    if (env && boost::iequals(string(env), string("none"))) {
        return (false);
    }

    return (true);
}

// Constructor.  The setting of logger_ must be done when the variable is
// constructed (instead of being left to the body of the function); at least
// one compiler requires that all member variables be constructed before the
// constructor is run, but log4cplus::Logger (the type of logger_) has no
// default constructor.
LoggerImpl::LoggerImpl(const string& name) :
    name_(expandLoggerName(name)),
    logger_(log4cplus::Logger::getInstance(name_))
{
    if (lockfileEnabled()) {
        sync_ = new interprocess::InterprocessSyncFile("logger");
    } else {
        sync_ = new interprocess::InterprocessSyncNull("logger");
    }
}

// Destructor. (Here because of virtual declaration.)

LoggerImpl::~LoggerImpl() {
    delete sync_;
}

/// \brief Version
std::string
LoggerImpl::getVersion() {
    std::ostringstream ver;
    ver << "log4plus ";
    ver << log4cplus::versionStr;
    return (ver.str());
}

// Set the severity for logging.
void
LoggerImpl::setSeverity(isc::log::Severity severity, int dbglevel) {
    Level level(severity, dbglevel);
    logger_.setLogLevel(LoggerLevelImpl::convertFromBindLevel(level));
}

// Return severity level
isc::log::Severity
LoggerImpl::getSeverity() {
    Level level = LoggerLevelImpl::convertToBindLevel(logger_.getLogLevel());
    return level.severity;
}

// Return current debug level (only valid if current severity level is DEBUG).
int
LoggerImpl::getDebugLevel() {
    Level level = LoggerLevelImpl::convertToBindLevel(logger_.getLogLevel());
    return level.dbglevel;
}

// Get effective severity.  Either the current severity or, if not set, the
// severity of the root level.
isc::log::Severity
LoggerImpl::getEffectiveSeverity() {
    Level level = LoggerLevelImpl::convertToBindLevel(logger_.getChainedLogLevel());
    return level.severity;
}

// Return effective debug level (only valid if current effective severity level
// is DEBUG).
int
LoggerImpl::getEffectiveDebugLevel() {
    Level level = LoggerLevelImpl::convertToBindLevel(logger_.getChainedLogLevel());
    return level.dbglevel;
}


// Output a general message
string*
LoggerImpl::lookupMessage(const MessageID& ident) {
    return (new string(string(ident) + " " +
                       MessageDictionary::globalDictionary()->getText(ident)));
}

// Replace the interprocess synchronization object

void
LoggerImpl::setInterprocessSync(isc::log::interprocess::InterprocessSync* sync)
{
    if (sync == NULL) {
        isc_throw(BadInterprocessSync,
                  "NULL was passed to setInterprocessSync()");
    }

    delete sync_;
    sync_ = sync;
}

void
LoggerImpl::outputRaw(const Severity& severity, const string& message) {
    // Use a mutex locker for mutual exclusion from other threads in
    // this process.
    isc::util::thread::Mutex::Locker mutex_locker(LoggerManager::getMutex());

    // Use an interprocess sync locker for mutual exclusion from other
    // processes to avoid log messages getting interspersed.
    interprocess::InterprocessSyncLocker locker(*sync_);

    if (!locker.lock()) {
        LOG4CPLUS_ERROR(logger_, "Unable to lock logger lockfile");
    }

    switch (severity) {
        case DEBUG:
            LOG4CPLUS_DEBUG(logger_, message);
            break;

        case INFO:
            LOG4CPLUS_INFO(logger_, message);
            break;

        case WARN:
            LOG4CPLUS_WARN(logger_, message);
            break;

        case ERROR:
            LOG4CPLUS_ERROR(logger_, message);
            break;

        case FATAL:
            LOG4CPLUS_FATAL(logger_, message);
            break;

        case NONE:
             break;

        default:
            LOG4CPLUS_ERROR(logger_,
                            "Unsupported severity in LoggerImpl::outputRaw(): "
                            << severity);
    }

    if (!locker.unlock()) {
        LOG4CPLUS_ERROR(logger_, "Unable to unlock logger lockfile");
    }
}

} // namespace log
} // namespace isc
