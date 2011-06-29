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

#include <log/logger_level.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <log/logger_support.h>
#include <log/output_option.h>

using namespace std;

namespace {

// Flag to hold logging initialization state.
bool logging_init_state = false;


// Set logging destination according to the setting of B10_LOGGER_DESTINATION.
// (See header for initLogger() for more details.)
void
setDestination(const char* root, const isc::log::Severity severity,
               const int dbglevel) {

    using namespace isc::log;

    // Constants:
    static const string STDOUT = "stdout";
    static const string STDERR = "stderr";
    static const string SYSLOG = "syslog";
    static const string SYSLOG_COLON = "syslog:";


    const char* destination = getenv("B10_LOGGER_DESTINATION");
    if (destination != NULL) {

        // Destination is present, adjust root logger destination to it.
        LoggerSpecification spec(root, severity, dbglevel);
        OutputOption option;

        const string dest = destination;
        if (dest == STDOUT) {
            option.destination = OutputOption::DEST_CONSOLE;
            option.stream = OutputOption::STR_STDOUT;

        } else if (dest == STDERR) {
            option.destination = OutputOption::DEST_CONSOLE;
            option.stream = OutputOption::STR_STDERR;

        } else if (dest == SYSLOG) {
            option.destination = OutputOption::DEST_SYSLOG;
            option.facility = "local0";

        } else if (dest.find(SYSLOG_COLON) == 0) {
            option.destination = OutputOption::DEST_SYSLOG;
            // Must take account of the string actually being "syslog:".
            if (dest == SYSLOG_COLON) {
                cerr << "**ERROR** value for B10_LOGGER_DESTINATION of " <<
                        SYSLOG_COLON << " is invalid, " << SYSLOG <<
                        " will be used instead\n";
                option.facility = "local0";
            } else {
                // Everything else is the facility name
                option.facility = dest.substr(SYSLOG_COLON.size());
            }

        } else {
            // Not a recognised destination, assume a file.
            option.destination = OutputOption::DEST_FILE;
            option.filename = dest;
        }

        // ... and set it.
        spec.addOutputOption(option);
        LoggerManager manager;
        manager.process(spec);
    }
}

} // Anonymous namespace

namespace isc {
namespace log {

// Return initialization state.
bool
isLoggingInitialized() {
    return (logging_init_state);
}

// Set initialization state.  (Note: as logging can be initialized via a direct
// call to LoggerManager::init(), this function is called from there, not from
// the initialization functions in this file.
void
setLoggingInitialized(bool state) {
    logging_init_state = state;
}

// Logger Run-Time Initialization.

void
initLogger(const string& root, isc::log::Severity severity, int dbglevel,
    const char* file) {
    LoggerManager::init(root, severity, dbglevel, file);
}

// Logger Run-Time Initialization via Environment Variables
void initLogger(isc::log::Severity severity, int dbglevel) {

    // Root logger name is defined by the environment variable B10_LOGGER_ROOT.
    // If not present, the name is "bind10".
    const char* DEFAULT_ROOT = "bind10";
    const char* root = getenv("B10_LOGGER_ROOT");
    if (! root) {
        root = DEFAULT_ROOT;
    }

    // Set the logging severity.  The environment variable is
    // B10_LOGGER_SEVERITY, and can be one of "DEBUG", "INFO", "WARN", "ERROR"
    // of "FATAL".  Note that the string must be in upper case with no leading
    // of trailing blanks.
    const char* sev_char = getenv("B10_LOGGER_SEVERITY");
    if (sev_char) {
        severity = isc::log::getSeverity(sev_char);
    }

    // If the severity is debug, get the debug level (environment variable
    // B10_LOGGER_DBGLEVEL), which should be in the range 0 to 99.
    if (severity == isc::log::DEBUG) {
        const char* dbg_char = getenv("B10_LOGGER_DBGLEVEL");
        if (dbg_char) {
            int level = 0;
            try {
                level = boost::lexical_cast<int>(dbg_char);
                if (level < MIN_DEBUG_LEVEL) {
                    cerr << "**ERROR** debug level of " << level
                         << " is invalid - a value of " << MIN_DEBUG_LEVEL
                         << " will be used\n";
                    level = MIN_DEBUG_LEVEL;
                } else if (level > MAX_DEBUG_LEVEL) {
                    cerr << "**ERROR** debug level of " << level
                         << " is invalid - a value of " << MAX_DEBUG_LEVEL
                         << " will be used\n";
                    level = MAX_DEBUG_LEVEL;
                }
            } catch (...) {
                // Error, but not fatal to the test
                cerr << "**ERROR** Unable to translate "
                        "B10_LOGGER_DBGLEVEL - a value of 0 will be used\n";
            }
            dbglevel = level;
        }
    }

    // Set the local message file
    const char* localfile = getenv("B10_LOGGER_LOCALMSG");

    // Initialize logging
    initLogger(root, severity, dbglevel, localfile);

    // Now set the destination
    setDestination(root, severity, dbglevel);
}

} // namespace log
} // namespace isc
