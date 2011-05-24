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
/// These functions will be replaced once the code has been written to obtain
/// the logging parameters from the configuration database.

#include <iostream>
#include <algorithm>
#include <iostream>
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
        logger.info(MSG_RDLOCMES).arg(file);
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
            logger.error(ident);
            break;

        case 1:
            logger.error(ident).arg(args[0]);
            break;

        case 2:
            logger.error(ident).arg(args[0]).arg(args[1]);
            break;

        default:    // 3 or more (3 should be the maximum)
            logger.error(ident).arg(args[0]).arg(args[1]).arg(args[2]);
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
            logger.warn(MSG_DUPMSGID).arg(*i);
        }

    }

    // Replace any messages with local ones (if given)
    if (file) {
        readLocalMessageFile(file);
    }
}

/// Logger Run-Time Initialization via Environment Variables
void initLogger() {

    // Root logger name is defined by the environment variable B10_LOGGER_ROOT.
    // If not present, the name is "b10root".
    const char* DEFAULT_ROOT = "b10root";
    const char* root = getenv("B10_LOGGER_ROOT");
    if (! root) {
        root = DEFAULT_ROOT;
    }

    // Set the logging severity.  The environment variable is
    // B10_LOGGER_SEVERITY, and can be one of "DEBUG", "INFO", "WARN", "ERROR"
    // of "FATAL".  Note that the string must be in upper case with no leading
    // of trailing blanks.
    isc::log::Severity severity = isc::log::DEFAULT;
    const char* sev_char = getenv("B10_LOGGER_SEVERITY");
    if (sev_char) {
        string sev_string(sev_char);
        if (sev_string == "DEBUG") {
            severity = isc::log::DEBUG;
        } else if (sev_string == "INFO") {
            severity = isc::log::INFO;
        } else if (sev_string == "WARN") {
            severity = isc::log::WARN;
        } else if (sev_string == "ERROR") {
            severity = isc::log::ERROR;
        } else if (sev_string == "FATAL") {
            severity = isc::log::FATAL;
        } else {
            std::cerr << "**ERROR** unrecognised logger severity of '"
                      << sev_string << "' - default severity will be used\n";
        }
    }

    // If the severity is debug, get the debug level (environment variable
    // B10_LOGGER_DBGLEVEL), which should be in the range 0 to 99.
    int dbglevel = 0;
    if (severity == isc::log::DEBUG) {
        const char* dbg_char = getenv("B10_LOGGER_DBGLEVEL");
        if (dbg_char) {
            int level = 0;
            try {
                level = boost::lexical_cast<int>(dbg_char);
                if (level < MIN_DEBUG_LEVEL) {
                    std::cerr << "**ERROR** debug level of " << level
                              << " is invalid - a value of " << MIN_DEBUG_LEVEL
                              << " will be used\n";
                    level = MIN_DEBUG_LEVEL;
                } else if (level > MAX_DEBUG_LEVEL) {
                    std::cerr << "**ERROR** debug level of " << level
                              << " is invalid - a value of " << MAX_DEBUG_LEVEL
                              << " will be used\n";
                    level = MAX_DEBUG_LEVEL;
                }
            } catch (...) {
                // Error, but not fatal to the test
                std::cerr << "**ERROR** Unable to translate "
                             "B10_LOGGER_DBGLEVEL - a value of 0 will be used\n";
            }
            dbglevel = level;
        }
    }

    /// Set the local message file
    const char* localfile = getenv("B10_LOGGER_LOCALMSG");

    // Initialize logging
    initLogger(root, severity, dbglevel, localfile);
}

} // namespace log
} // namespace isc
