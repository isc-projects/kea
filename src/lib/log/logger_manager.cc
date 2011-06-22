// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
// PERFORMANCE OF THIS SOFTWARE.

#include <algorithm>
#include <vector>

#include <log/logger.h>
#include <log/logger_manager.h>
#include <log/logger_manager_impl.h>
#include <log/logger_name.h>
#include <log/log_messages.h>
#include <log/macros.h>
#include <log/message_dictionary.h>
#include <log/message_exception.h>
#include <log/message_initializer.h>
#include <log/message_initializer.h>
#include <log/message_reader.h>
#include <log/message_types.h>

using namespace std;

namespace {

// Logger used for logging messages within the logging code itself.
isc::log::Logger logger("log");

// Static stores for the initialization severity and debug level.
// These are put in methods to avoid a "static initialization fiasco".

isc::log::Severity& initSeverity() {
    static isc::log::Severity severity = isc::log::INFO;
    return (severity);
}

int& initDebugLevel() {
    static int dbglevel = 0;
    return (dbglevel);
}

std::string& initRootName() {
    static std::string root("bind10");
    return (root);
}

} // Anonymous namespace


namespace isc {
namespace log {

// Constructor - create the implementation  class.
LoggerManager::LoggerManager() {
    impl_ = new LoggerManagerImpl();
}

// Destructor - get rid of the implementation class
LoggerManager::~LoggerManager() {
    delete impl_;
}

// Initialize processing
void
LoggerManager::processInit() {
    impl_->processInit();
}

// Process logging specification
void
LoggerManager::processSpecification(const LoggerSpecification& spec) {
    impl_->processSpecification(spec);
}

// End Processing
void
LoggerManager::processEnd() {
    impl_->processEnd();
}


/// Logging system initialization

void
LoggerManager::init(const std::string& root, isc::log::Severity severity,
                    int dbglevel, const char* file)
{
    // Save name, severity and debug level for later.  No need to save the
    // file name as once the local message file is read the messages will
    // not be lost.
    initRootName() = root;
    initSeverity() = severity;
    initDebugLevel() = dbglevel;

    // Create the BIND 10 root logger and set the default severity and
    // debug level.  This is the logger that has the name of the application.
    // All other loggers created in this application will be its children.
    setRootLoggerName(root);

    // Initialize the implementation logging.  After this point, some basic
    // logging has been set up and messages can be logged.
    LoggerManagerImpl::init(severity, dbglevel);

    // Check if there were any duplicate message IDs in the default dictionary
    // and if so, log them.  Log using the logging facility logger.
    vector<string>& duplicates = MessageInitializer::getDuplicates();
    if (!duplicates.empty()) {

        // There are duplicates present.  This will be listed in alphabetic
        // order of message ID, so they need to be sorted.  This list itself may
        // contain duplicates; if so, the message ID is listed as many times as
        // there are duplicates.
        sort(duplicates.begin(), duplicates.end());
        for (vector<string>::iterator i = duplicates.begin();
             i != duplicates.end(); ++i) {
            LOG_WARN(logger, MSG_DUPMSGID).arg(*i);
        }

    }

    // Replace any messages with local ones (if given)
    if (file) {
        readLocalMessageFile(file);
    }
}


// Read local message file
// TODO This should be done after the configuration has been read so that
// the file can be placed in the local configuration
void
LoggerManager::readLocalMessageFile(const char* file) {

    MessageDictionary& dictionary = MessageDictionary::globalDictionary();
    MessageReader reader(&dictionary);
    try {

        logger.info(MSG_RDLOCMES).arg(file);
        reader.readFile(file, MessageReader::REPLACE);

        // File successfully read.  As each message in the file is supposed to
        // replace one in the dictionary, any ID read that can't be located in
        // the dictionary will not be used.  To aid problem diagnosis, the
        // unknown message IDs are listed.
        MessageReader::MessageIDCollection unknown = reader.getNotAdded();
        for (MessageReader::MessageIDCollection::const_iterator
            i = unknown.begin(); i != unknown.end(); ++i) {
            string message_id = boost::lexical_cast<string>(*i);
                logger.warn(MSG_IDNOTFND).arg(message_id);
        }
    }
    catch (MessageException& e) {
        MessageID ident = e.id();
        vector<string> args = e.arguments();

        // Log the variable number of arguments.  The actual message will be
        // logged when the error_message variable is destroyed.
        Formatter<isc::log::Logger> error_message = logger.error(ident);
        for (int i = 0; i < args.size(); ++i) {
            error_message = error_message.arg(args[i]);
        }
    }
}

// Reset logging to settings passed to init()
void
LoggerManager::reset() {
    setRootLoggerName(initRootName());
    LoggerManagerImpl::reset(initSeverity(), initDebugLevel());
}

} // namespace log
} // namespace isc
