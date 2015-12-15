// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <algorithm>
#include <vector>

#include <log/logger.h>
#include <log/logger_manager.h>
#include <log/logger_manager_impl.h>
#include <log/logger_name.h>
#include <log/logger_support.h>
#include <log/log_messages.h>
#include <log/macros.h>
#include <log/message_dictionary.h>
#include <log/message_exception.h>
#include <log/message_initializer.h>
#include <log/message_initializer.h>
#include <log/message_reader.h>
#include <log/message_types.h>
#include <log/interprocess/interprocess_sync_null.h>

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
    static std::string root(isc::log::getDefaultRootLoggerName());
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
                    int dbglevel, const char* file, bool buffer)
{
    // Load in the messages declared in the program and registered by
    // statically-declared MessageInitializer objects.
    MessageInitializer::loadDictionary();

    // Save name, severity and debug level for later.  No need to save the
    // file name as once the local message file is read the messages will
    // not be lost.
    initRootName() = root;
    initSeverity() = severity;
    initDebugLevel() = dbglevel;

    // Create the Kea root logger and set the default severity and
    // debug level.  This is the logger that has the name of the application.
    // All other loggers created in this application will be its children.
    setRootLoggerName(root);

    // Initialize the implementation logging.  After this point, some basic
    // logging has been set up and messages can be logged.
    // However, they will not appear until a logging specification has been
    // processed (or the program exits), see TODO
    LoggerManagerImpl::init(severity, dbglevel, buffer);
    setLoggingInitialized();

    // Check if there were any duplicate message IDs in the default dictionary
    // and if so, log them.  Log using the logging facility logger.
    logDuplicatedMessages();

    // Replace any messages with local ones (if given)
    if (file) {
        readLocalMessageFile(file);
    }

    // Ensure that the mutex is constructed and ready at this point.
    (void) getMutex();
}

void
LoggerManager::logDuplicatedMessages() {
    const list<string>& duplicates = MessageInitializer::getDuplicates();
    if (!duplicates.empty()) {

        // There are duplicates present. This list itself may contain
        // duplicates; if so, the message ID is listed as many times as
        // there are duplicates.
        for (list<string>::const_iterator i = duplicates.begin();
             i != duplicates.end(); ++i) {
            LOG_WARN(logger, LOG_DUPLICATE_MESSAGE_ID).arg(*i);
        }
        MessageInitializer::clearDuplicates();
    }
}


// Read local message file
// TODO This should be done after the configuration has been read so that
// the file can be placed in the local configuration
void
LoggerManager::readLocalMessageFile(const char* file) {

    const MessageDictionaryPtr& dictionary = MessageDictionary::globalDictionary();
    MessageReader reader(dictionary.get());

    // Turn off use of any lock files. This is because this logger can
    // be used by standalone programs which may not have write access to
    // the local state directory (to create lock files). So we switch to
    // using a null interprocess sync object here.
    logger.setInterprocessSync(
        new isc::log::interprocess::InterprocessSyncNull("logger"));

    try {

        logger.info(LOG_READING_LOCAL_FILE).arg(file);
        reader.readFile(file, MessageReader::REPLACE);

        // File successfully read.  As each message in the file is supposed to
        // replace one in the dictionary, any ID read that can't be located in
        // the dictionary will not be used.  To aid problem diagnosis, the
        // unknown message IDs are listed.
        MessageReader::MessageIDCollection unknown = reader.getNotAdded();
        for (MessageReader::MessageIDCollection::const_iterator
            i = unknown.begin(); i != unknown.end(); ++i) {
            string message_id = boost::lexical_cast<string>(*i);
                logger.warn(LOG_NO_SUCH_MESSAGE).arg(message_id);
        }
    }
    catch (MessageException& e) {
        MessageID ident = e.id();
        vector<string> args = e.arguments();

        // Log the variable number of arguments.  The actual message will be
        // logged when the error_message variable is destroyed.
        Formatter<isc::log::Logger> error_message = logger.error(ident);
        for (vector<string>::size_type i = 0; i < args.size(); ++i) {
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

isc::util::thread::Mutex&
LoggerManager::getMutex() {
    static isc::util::thread::Mutex mutex;

    return (mutex);
}

} // namespace log
} // namespace isc
