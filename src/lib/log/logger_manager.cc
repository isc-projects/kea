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
#include <log/logger_manager_impl.h>
#include <log/logger_manager.h>
#include <log/messagedef.h>
#include <log/message_dictionary.h>
#include <log/message_exception.h>
#include <log/message_initializer.h>
#include <log/message_reader.h>
#include <log/message_types.h>
#include <log/root_logger_name.h>
#include <log/macros.h>
#include <log/messagedef.h>
#include <log/message_initializer.h>

using namespace std;

namespace isc {
namespace log {

void LoggerManagerImpl::processEnd() {}

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
LoggerManager::init(const std::string& root, const char* file,
                    isc::log::Severity severity, int dbglevel)
{
    // Create the BIND 10 root logger and set the default severity and
    // debug level.  This is the logger that has the name of the application.
    // All other loggers created in this application will be its children.
    setRootLoggerName(root);

    // Initialize the implementation logging.
    LoggerManagerImpl::init(severity, dbglevel);

    // TODO: sort out the names.
    Logger logger("log");

    // Check if there were any duplicate message IDs in the default dictionary
    // and if so, log them.  Log using the logging facility root logger.
    vector<string>& duplicates = MessageInitializer::getDuplicates();
    if (!duplicates.empty()) {

        // There are - sort and remove any duplicates.
        sort(duplicates.begin(), duplicates.end());
        vector<string>::iterator new_end =
            unique(duplicates.begin(), duplicates.end());
        for (vector<string>::iterator i = duplicates.begin(); i != new_end; ++i) {
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

    Logger logger("log");

    MessageDictionary& dictionary = MessageDictionary::globalDictionary();
    MessageReader reader(&dictionary);
    try {

        // FIXME: commented out for testing
        // logger.info(MSG_RDLOCMES).arg(file);
        reader.readFile(file, MessageReader::REPLACE);

        // File successfully read, list the duplicates
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
        switch (args.size()) {
        case 0:
            LOG_ERROR(logger, ident);
            break;

        case 1:
            LOG_ERROR(logger, ident).arg(args[0]);
            break;

        case 2:
            LOG_ERROR(logger, ident).arg(args[0]).arg(args[1]);
            break;

        default:    // 3 or more (3 should be the maximum)
            LOG_ERROR(logger, ident).arg(args[0]).arg(args[1]).arg(args[2]);
        }
    }
}

} // namespace log
} // namespace isc
