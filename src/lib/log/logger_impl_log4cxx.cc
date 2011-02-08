// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE

// $Id$

#include <iostream>

#include <stdarg.h>
#include <stdio.h>

#include <log4cxx/appender.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/consoleappender.h>

#include <log/root_logger_name.h>
#include <log/logger.h>
#include <log/logger_impl.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/strutil.h>
#include <log/xdebuglevel.h>

using namespace std;

namespace isc {
namespace log {

// Static initializations

bool LoggerImpl::init_ = false;

// Destructor.  Delete log4cxx stuff if "don't delete" is clear.

LoggerImpl::~LoggerImpl() {
    if (exit_delete_) {
        delete loggerptr_;
    }
}

// Initialize logger - create a logger as a child of the root logger.  With
// log4cxx this is assured by naming the logger <parent>.<child>.

void
LoggerImpl::initLogger() {

    // Initialize basic logging if not already done.  This is a one-off for
    // all loggers.
    if (!init_) {

        // TEMPORARY
        // Add a suitable console logger to the log4cxx root logger.  (This
        // is the logger at the root of the log4cxx tree, not the BIND-10 root
        // logger, which is one level down.)  The chosen format is:
        //
        // YYYY-MM-DD hh:mm:ss.sss [logger] SEVERITY: text
        //
        // As noted, this is a temporary hack: it is done here to ensure that
        // a suitable output and output pattern is set.  Future versions of the
        // software will set this based on configuration data.

        log4cxx::LayoutPtr layout(
            new log4cxx::PatternLayout(
                "%d{yyyy-MM-DD HH:mm:ss.SSS} %-5p [%c] %m\n"));
        log4cxx::AppenderPtr console(
            new log4cxx::ConsoleAppender(layout));
        log4cxx::LoggerPtr sys_root_logger = log4cxx::Logger::getRootLogger();
        sys_root_logger->addAppender(console);

        // Set the default logging to INFO
        sys_root_logger->setLevel(log4cxx::Level::getInfo());

        // All static stuff initialized
        init_ = true;
    }

    // Initialize this logger.  Name this as to whether the BIND-10 root logger
    // name has been set.  (If not, this mucks up the hierarchy :-( ).
    string root_name = RootLoggerName::getName();
    if (root_name.empty() || (name_ == root_name)) {
        loggerptr_ = new log4cxx::LoggerPtr(log4cxx::Logger::getLogger(name_));
    }
    else {
        loggerptr_ = new log4cxx::LoggerPtr(
            log4cxx::Logger::getLogger(root_name + "." + name_)
        );
    }
}


// Set the severity for logging.  There is a 1:1 mapping between the logging
// severity and the log4cxx logging levels, apart from DEBUG.
//
// In log4cxx, each of the logging levels (DEBUG, INFO, WARN etc.) has a numeric
// value.  The level is set to one of these and any numeric level equal to or
// above it that is reported.  For example INFO has a value of 20000 and ERROR
// a value of 40000. So if a message of WARN severity (= 30000) is logged, it is
// not logged when the logger's severity level is ERROR (as 30000 !>= 40000).
// It is reported if the logger's severity level is set to WARN (as 30000 >=
/// 30000) or INFO (30000 >= 20000).
//
// This gives a simple system for handling different debug levels.  The debug
// level is a number between 0 and 99, with 0 being least verbose and 99 the
// most.  To implement this seamlessly, when DEBUG is set, the numeric value
// of the logging level is actually set to (DEBUG - debug-level).  Similarly
// messages of level "n" are logged at a logging level of (DEBUG - n).  Thus if
// the logging level is set to DEBUG and the debug level set to 25, the actual
// level set is 10000 - 25 = 99975.
//
// Attempting to log a debug message of level 26 is an attempt to log a message
// of level 10000 - 26 = 9974.  As 9974 !>= 9975, it is not logged.  A
// message of level 25 is, because 9975 >= 9975.
//
// The extended set of logging levels is implemented by the XDebugLevel class.

void
LoggerImpl::setSeverity(isc::log::Severity severity, int dbglevel) {
    switch (severity) {
        case NONE:
            getLogger()->setLevel(log4cxx::Level::getOff());
            break;

        case FATAL:
            getLogger()->setLevel(log4cxx::Level::getFatal());
            break;

        case ERROR:
            getLogger()->setLevel(log4cxx::Level::getError());
            break;

        case WARN:
            getLogger()->setLevel(log4cxx::Level::getWarn());
            break;

        case INFO:
            getLogger()->setLevel(log4cxx::Level::getInfo());
            break;

        case DEBUG:
            getLogger()->setLevel(
                log4cxx::XDebugLevel::getExtendedDebug(dbglevel));
            break;

        // Will get here for DEFAULT or any other value.  This disables the
        // logger's own severity and it defaults to the severity of the parent
        // logger.
        default:
            getLogger()->setLevel(0);
    }
}

// Convert between numeric log4cxx logging level and BIND-10 logging severity.

isc::log::Severity
LoggerImpl::convertLevel(int value) {

    // The order is optimised.  This is only likely to be called when testing
    // for writing debug messages, so the check for DEBUG_INT is first.
    if (value <= log4cxx::Level::DEBUG_INT) {
        return (DEBUG);
    } else if (value <= log4cxx::Level::INFO_INT) {
        return (INFO);
    } else if (value <= log4cxx::Level::WARN_INT) {
        return (WARN);
    } else if (value <= log4cxx::Level::ERROR_INT) {
        return (ERROR);
    } else if (value <= log4cxx::Level::FATAL_INT) {
        return (FATAL);
    } else {
        return (NONE);
    }
}


// Return the logging severity associated with this logger.

isc::log::Severity
LoggerImpl::getSeverityCommon(const log4cxx::LoggerPtr& ptrlogger,
    bool check_parent) {

    log4cxx::LevelPtr level = ptrlogger->getLevel();
    if (level == log4cxx::LevelPtr()) {

        // Null level returned, logging should be that of the parent.

        if (check_parent) {
            log4cxx::LoggerPtr parent = ptrlogger->getParent();
            if (parent == log4cxx::LoggerPtr()) {

                // No parent, so reached the end of the chain.  Return INFO
                // severity.
                return (INFO);
            }
            else {
                return getSeverityCommon(parent, check_parent);
            }
        }
        else {
            return (DEFAULT);
        }
    } else {
        return convertLevel(level->toInt());
    }
}


// Get the debug level.  This returns 0 unless the severity is DEBUG.

int
LoggerImpl::getDebugLevel() {

    log4cxx::LevelPtr level = getLogger()->getLevel();
    if (level == log4cxx::LevelPtr()) {

        // Null pointer returned, logging should be that of the parent.
        return (0);

    } else {
        int severity = level->toInt();
        if (severity <= log4cxx::Level::DEBUG_INT) {
            return (log4cxx::Level::DEBUG_INT - severity);
        }
        else {
            return (0);
        }
    }
}



} // namespace log
} // namespace isc
