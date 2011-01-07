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
// PERFORMANCE OF THIS SOFTWAR

// $Id$

#include <iostream>

#include <log/root_logger_name.h>
#include <log/logger.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/strutil.h>
#include <log/xdebuglevel.h>

#include <log4cxx/basicconfigurator.h>

using namespace std;

namespace isc {
namespace log {

bool Logger::init_ = false;

// Constructor - create a logger as a child of the root logger.  With log4cxx
// this is assured by naming the logger <parent>.<child>.

Logger::Logger(const std::string& name) : loggerptr_()
{
    string root_name = RootLoggerName::getName();
    if (root_name.empty() || (name == root_name)) {
        fullname_ = name;
    }
    else {
        fullname_ = root_name + "." + name;
    }
    loggerptr_ = log4cxx::Logger::getLogger(fullname_);

    // Initialize basic logging if not already done
    if (! init_) {
        log4cxx::BasicConfigurator::configure();
        init_ = true;
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
// of level 10000 - 26 = 99974.  As 99974 !>= 99975, it is not logged.  A
// message of level 25 is, because 99975 >= 99975.
//
// The extended set of logging levels is implemented by the XDebugLevel class.

void Logger::setSeverity(Severity severity, int dbglevel) {
    switch (severity) {
        case NONE:
            loggerptr_->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::OFF_INT));
            break;

        case FATAL:
            loggerptr_->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::FATAL_INT));
            break;

        case ERROR:
            loggerptr_->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::ERROR_INT));
            break;

        case WARNING:
            loggerptr_->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::WARN_INT));
            break;

        case INFO:
            loggerptr_->setLevel(
                log4cxx::Level::toLevel(
                log4cxx::Level::INFO_INT));
            break;

        case DEBUG:
            loggerptr_->setLevel(
                log4cxx::XDebugLevel::getExtendedDebug(dbglevel));
            break;

        // Will get here for DEFAULT or any other value.  This disables the
        // logger's own severity and it defaults to the severity of the parent
        // logger.
        default:
            loggerptr_->setLevel(0);
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

int Logger::getDebugLevel() const {

    log4cxx::LevelPtr level = loggerptr_->getLevel();
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

// Return formatted message
// THIS IS A PLACE HOLDER

string
Logger::formatMessage(MessageID ident, vector<string>* args) {

    // Return the format string
    MessageDictionary* global = MessageDictionary::globalDictionary();
    string text = global->getText(ident);

    // Do argument substitution if there are any
    if (args) {
        text = isc::strutil::format(text, *args);
    }

    return ident + ", " + text;
}

string
Logger::formatMessage(MessageID ident, const string& composite) {
    vector<string> args = isc::strutil::tokens(composite, "\0");
    return formatMessage(ident, &args);
}


// Debug methods

void Logger::debugCommon(MessageID ident, const std::string* args) {
    if (args) {
        LOG4CXX_DEBUG(loggerptr_, formatMessage(ident, *args));
    } else {
        LOG4CXX_DEBUG(loggerptr_, formatMessage(ident));
    }
}

// Info

void Logger::infoCommon(MessageID ident, const std::string* args) {
    if (args) {
        LOG4CXX_INFO(loggerptr_, formatMessage(ident, *args));
    } else {
        LOG4CXX_INFO(loggerptr_, formatMessage(ident));
    }
}

// Warning

void Logger::warnCommon(MessageID ident, const std::string* args) {
    if (args) {
        LOG4CXX_WARN(loggerptr_, formatMessage(ident, *args));
    } else {
        LOG4CXX_WARN(loggerptr_, formatMessage(ident));
    }
}

// Error

void Logger::errorCommon(MessageID ident, const std::string* args) {
    if (args) {
        LOG4CXX_ERROR(loggerptr_, formatMessage(ident, *args));
    } else {
        LOG4CXX_ERROR(loggerptr_, formatMessage(ident));
    }
}

// Fatal

void Logger::fatalCommon(MessageID ident, const std::string* args) {
    if (args) {
        LOG4CXX_FATAL(loggerptr_, formatMessage(ident, *args));
    } else {
        LOG4CXX_FATAL(loggerptr_, formatMessage(ident));
    }
}


} // namespace log
} // namespace isc
