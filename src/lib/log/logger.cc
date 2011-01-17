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
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/strutil.h>
#include <log/xdebuglevel.h>

using namespace std;

namespace isc {
namespace log {

// Static initializations

bool Logger::init_ = false;

// Destructor.  Delete log4cxx stuff if "don't delete" is clear.

Logger::~Logger() {
    if (exit_delete_) {
        delete loggerptr_;
    }
}

// Initialize logger - create a logger as a child of the root logger.  With
// log4cxx this is assured by naming the logger <parent>.<child>.

void Logger::initLogger() {

    // Initialize basic logging if not already done.  This is a one-off for
    // all loggers.
    if (! init_) {

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
        
        // All static stuff initialized
        init_ = true;
    }

    // Initialize this logger.  Name this as to whether the BIND-10 root logger
    // name has beens set.
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
// In log4cxx, each of the logging levels (DEBUG, INFO, WARNING etc.) has a
// numeric value.  The level is set to one of these and any numeric level equal
// to or above it that is reported.  For example INFO has a value of 20000 and
// ERROR a value of 40000. So if a message of WARNING severity (= 30000) is
// logged, it is not logged when the logger's severity level is ERROR (as
// 30000 !>= 40000).  It is reported if the logger's severity level is set to
// WARNING (as 30000 >= 30000) or INFO (30000 >= 20000).
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

void Logger::setSeverity(Severity severity, int dbglevel) {
    switch (severity) {
        case NONE:
            getLogger()->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::OFF_INT));
            break;

        case FATAL:
            getLogger()->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::FATAL_INT));
            break;

        case ERROR:
            getLogger()->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::ERROR_INT));
            break;

        case WARNING:
            getLogger()->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::WARN_INT));
            break;

        case INFO:
            getLogger()->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::INFO_INT));
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

Logger::Severity Logger::convertLevel(int value) const {

    // The order is optimised.  This is only likely to be called when testing
    // for writing debug messages, so the check for DEBUG_INT is first.
    if (value <= log4cxx::Level::DEBUG_INT) {
        return (DEBUG);
    } else if (value <= log4cxx::Level::INFO_INT) {
        return (INFO);
    } else if (value <= log4cxx::Level::WARN_INT) {
        return (WARNING);
    } else if (value <= log4cxx::Level::ERROR_INT) {
        return (ERROR);
    } else if (value <= log4cxx::Level::FATAL_INT) {
        return (FATAL);
    } else {
        return (NONE);
    }
}


// Return the logging severity associated with this logger.

Logger::Severity Logger::getSeverityCommon(const log4cxx::LoggerPtr& ptrlogger,
    bool check_parent) const {

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

int Logger::getDebugLevel() {

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

// Log an error message:
// Common code.  Owing to the use of variable arguments, this must be inline
// (hence the definition of the macro).  Also note that it expects that the
// message buffer "message" is declared in the compilation unit.

#define MESSAGE_SIZE (256)

#define FORMAT_MESSAGE(message) \
    { \
    MessageDictionary* global = MessageDictionary::globalDictionary(); \
    string format = global->getText(ident); \
    va_list ap; \
    va_start(ap, ident); \
    vsnprintf(message, sizeof(message), format.c_str(), ap); \
    message[sizeof(message) - 1] = '\0'; \
    va_end(ap); \
    }
    

// Output methods

void Logger::debug(int dbglevel, isc::log::MessageID ident, ...) {
    if (isDebugEnabled(dbglevel)) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        LOG4CXX_DEBUG(getLogger(), message);
    }
}

void Logger::info(isc::log::MessageID ident, ...) {
    if (isInfoEnabled()) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        LOG4CXX_INFO(getLogger(), message);
    }
}

void Logger::warn(isc::log::MessageID ident, ...) {
    if (isWarnEnabled()) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        LOG4CXX_WARN(getLogger(), message);
    }
}

void Logger::error(isc::log::MessageID ident, ...) {
    if (isErrorEnabled()) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        LOG4CXX_ERROR(getLogger(), message);
    }
}

void Logger::fatal(isc::log::MessageID ident, ...) {
    if (isFatalEnabled()) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        LOG4CXX_FATAL(getLogger(), message);
    }
}


} // namespace log
} // namespace isc
