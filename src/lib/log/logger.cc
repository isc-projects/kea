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

#include <log/logger.h>
#include <log/logger_impl.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/root_logger_name.h>
#include <log/strutil.h>

using namespace std;

namespace isc {
namespace log {

// Constructor

Logger::Logger(const std::string& name, bool infunc) :
    loggerptr_(new LoggerImpl(name, infunc))
{}

// Destructor.

Logger::~Logger() {
    delete loggerptr_;
}

// Get Name of Logger

std::string
Logger::getName() {
    return (loggerptr_->getName());
}

// Set the severity for logging.

void
Logger::setSeverity(isc::log::Severity severity, int dbglevel) {
    loggerptr_->setSeverity(severity, dbglevel);
}

// Return the severity of the logger.

isc::log::Severity
Logger::getSeverity() {
    return (loggerptr_->getSeverity());
}

// Get Effective Severity Level for Logger

isc::log::Severity
Logger::getEffectiveSeverity() {
    return (loggerptr_->getEffectiveSeverity());
}

// Debug level (only relevant if messages of severity DEBUG are being logged).

int
Logger::getDebugLevel() {
    return (loggerptr_->getDebugLevel());
}

// Check on the current severity settings

bool
Logger::isDebugEnabled(int dbglevel) {
    return (loggerptr_->isDebugEnabled(dbglevel));
}

bool
Logger::isInfoEnabled() {
    return (loggerptr_->isInfoEnabled());
}

bool
Logger::isWarnEnabled() {
    return (loggerptr_->isWarnEnabled());
}

bool
Logger::isErrorEnabled() {
    return (loggerptr_->isErrorEnabled());
}

bool
Logger::isFatalEnabled() {
    return (loggerptr_->isFatalEnabled());
}

// Format a message: looks up the message text in the dictionary and formats
// it, replacing tokens with arguments.
//
// Owing to the use of variable arguments, this must be inline (hence the
// definition of the macro).  Also note that it expects that the message buffer
// "message" is declared in the compilation unit.

#define MESSAGE_SIZE (512)

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

void
Logger::debug(int dbglevel, isc::log::MessageID ident, ...) {
    if (isDebugEnabled(dbglevel)) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        loggerptr_->debug(ident, message);
    }
}

void
Logger::info(isc::log::MessageID ident, ...) {
    if (isInfoEnabled()) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        loggerptr_->info(ident, message);
    }
}

void
Logger::warn(isc::log::MessageID ident, ...) {
    if (isWarnEnabled()) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        loggerptr_->warn(ident, message);
    }
}

void
Logger::error(isc::log::MessageID ident, ...) {
    if (isErrorEnabled()) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        loggerptr_->error(ident, message);
    }
}

void
Logger::fatal(isc::log::MessageID ident, ...) {
    if (isFatalEnabled()) {
        char message[MESSAGE_SIZE];
        FORMAT_MESSAGE(message);
        loggerptr_->fatal(ident, message);
    }
}

// Protected methods (used for testing)

bool Logger::operator==(const Logger& other) {
    return (*loggerptr_ == *other.loggerptr_);
}

bool Logger::isInitialized() {
    return loggerptr_->isInitialized();
}


} // namespace log
} // namespace isc
