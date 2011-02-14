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
// PERFORMANCE OF THIS SOFTWARE

/// \brief Temporary Logger Support
///
/// Performs run-time initialization of the logger system.  In particular, it
/// is passed information from the command line and:
///
/// a) Sets the severity of the messages being logged (and debug level if
/// appropriate).
/// b) Reads in the local message file is one has been supplied.
///
/// These functions will be replaced once the code has bneen written to obtain
/// the logging parameters from the configuration database.

#include <algorithm>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

#include <log/logger.h>
#include <log/logger_support.h>
#include <log/messagedef.h>
#include <log/message_dictionary.h>
#include <log/message_exception.h>
#include <log/message_initializer.h>
#include <log/message_reader.h>
#include <log/message_types.h>
#include <log/root_logger_name.h>

namespace isc {
namespace log {

using namespace std;

// Declare a logger for the logging subsystem.  This is a sub-logger of the
// root logger and is used in all functions in this file.
Logger logger("log");


/// \brief Reads Local Message File
///
/// Reads the local message file into the global dictionary, overwriting
/// existing messages.  If the file contained any message IDs not in the
/// dictionary, they are listed in a warning message.
///
/// \param file Name of the local message file
static void
readLocalMessageFile(const char* file) {
    
    MessageDictionary& dictionary = MessageDictionary::globalDictionary();
    MessageReader reader(&dictionary);
    try {
        logger.info(MSG_RDLOCMES, file);
        reader.readFile(file, MessageReader::REPLACE);

        // File successfully read, list the duplicates
        MessageReader::MessageIDCollection unknown = reader.getNotAdded();
        for (MessageReader::MessageIDCollection::const_iterator
            i = unknown.begin(); i != unknown.end(); ++i) {
            string message_id = boost::lexical_cast<string>(*i);
                logger.warn(MSG_IDNOTFND, message_id.c_str());
        }
    }
    catch (MessageException& e) {
        MessageID ident = e.id();
        vector<string> args = e.arguments();
        switch (args.size()) {
        case 0:
            logger.error(ident);
            break;

        case 1:
            logger.error(ident, args[0].c_str());
            break;

        default:    // 2 or more (2 should be the maximum)
            logger.error(ident, args[0].c_str(), args[1].c_str());
        }
    }
}

/// Logger Run-Time Initialization

void
initLogger(const string& root, isc::log::Severity severity, int dbglevel,
    const char* file) {

    // Create the application root logger and set the default severity and
    // debug level.  This is the logger that has the name of the application.
    // All other loggers created in this application will be its children.
    setRootLoggerName(root);
    Logger root_logger(isc::log::getRootLoggerName(), true);

    // Set the severity associated with it.  If no other logger has a severity,
    // this will be the default.
    root_logger.setSeverity(severity, dbglevel);

    // Check if there were any duplicate message IDs in the default dictionary
    // and if so, log them.  Log using the logging facility root logger.
    vector<string>& duplicates = MessageInitializer::getDuplicates();
    if (!duplicates.empty()) {

        // There are - sort and remove any duplicates.
        sort(duplicates.begin(), duplicates.end());
        vector<string>::iterator new_end =
            unique(duplicates.begin(), duplicates.end());
        for (vector<string>::iterator i = duplicates.begin(); i != new_end; ++i) {
            logger.warn(MSG_DUPMSGID, i->c_str());
        }

    }

    // Replace any messages with local ones (if given)
    if (file) {
        readLocalMessageFile(file);
    }
}

} // namespace log
} // namespace isc
