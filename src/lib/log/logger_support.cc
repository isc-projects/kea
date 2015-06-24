// Copyright (C) 2011,2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>

using namespace std;

namespace {

// Flag to hold logging initialization state.
bool logging_init_state = false;

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
           const char* file, bool buffer) {
    LoggerManager::init(root, severity, dbglevel, file, buffer);
}

// Reset characteristics of the root logger to that set by the environment
// variables KEA_LOGGER_SEVERITY, KEA_LOGGER_DBGLEVEL and KEA_LOGGER_DESTINATION.

void
setDefaultLoggingOutput(bool verbose) {

    using namespace isc::log;

    // Constants: not declared static as this is function is expected to be
    // called once only
    const string DEVNULL = "/dev/null";
    const string STDOUT = "stdout";
    const string STDERR = "stderr";
    const string SYSLOG = "syslog";
    const string SYSLOG_COLON = "syslog:";

    // Get the destination.  If not specified, assume /dev/null. (The default
    // severity for unit tests is DEBUG, which generates a lot of output.
    // Routing the logging to /dev/null will suppress that, whilst still
    // ensuring that the code paths are tested.)
    const char* destination = getenv("KEA_LOGGER_DESTINATION");
    const string dest((destination == NULL) ? DEVNULL : destination);

    // Prepare the objects to define the logging specification
    LoggerSpecification spec(getRootLoggerName(),
                             keaLoggerSeverity(verbose ? isc::log::DEBUG :
                                               isc::log::INFO),
                             keaLoggerDbglevel(isc::log::MAX_DEBUG_LEVEL));
    OutputOption option;

    // Set up output option according to destination specification
    if (dest == STDOUT) {
        option.destination = OutputOption::DEST_CONSOLE;
        option.stream = OutputOption::STR_STDOUT;

    } else if (dest == STDERR) {
        option.destination = OutputOption::DEST_CONSOLE;
        option.stream = OutputOption::STR_STDERR;

    } else if (dest == SYSLOG) {
        option.destination = OutputOption::DEST_SYSLOG;
        // Use default specified in OutputOption constructor for the
        // syslog destination

    } else if (dest.find(SYSLOG_COLON) == 0) {
        option.destination = OutputOption::DEST_SYSLOG;
        // Must take account of the string actually being "syslog:"
        if (dest == SYSLOG_COLON) {
            cerr << "**ERROR** value for KEA_LOGGER_DESTINATION of " <<
                    SYSLOG_COLON << " is invalid, " << SYSLOG <<
                    " will be used instead\n";
            // Use default for logging facility

        } else {
            // Everything else in the string is the facility name
            option.facility = dest.substr(SYSLOG_COLON.size());
        }

    } else {
        // Not a recognized destination, assume a file.
        option.destination = OutputOption::DEST_FILE;
        option.filename = dest;
    }

    // ... and set the destination
    spec.addOutputOption(option);
    LoggerManager manager;
    manager.process(spec);
}

} // namespace log
} // namespace isc
