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

#include <iostream>
#include <algorithm>
#include <string>

#include <log/logger_level.h>
#include <log/logger_name.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <log/logger_unittest_support.h>
#include <log/logger_support.h>
#include <log/output_option.h>

using namespace std;

namespace isc {
namespace log {

// Get the logging severity.  This is defined by the environment variable
// KEA_LOGGER_SEVERITY, and can be one of "DEBUG", "INFO", "WARN", "ERROR"
// of "FATAL".  (Note that the string must be in upper case with no leading
// of trailing blanks.)  If not present, the default severity passed to the
// function is returned.
isc::log::Severity
keaLoggerSeverity(isc::log::Severity defseverity) {
    const char* sev_char = getenv("KEA_LOGGER_SEVERITY");
    if (sev_char) {
        return (isc::log::getSeverity(sev_char));
    }
    return (defseverity);
}

// Get the debug level.  This is defined by the environment variable
// KEA_LOGGER_DBGLEVEL.  If not defined, a default value passed to the function
// is returned.
int
keaLoggerDbglevel(int defdbglevel) {
    const char* dbg_char = getenv("KEA_LOGGER_DBGLEVEL");
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
                         "KEA_LOGGER_DBGLEVEL - a value of 0 will be used\n";
        }
        return (level);
    }

    return (defdbglevel);
}


// Reset characteristics of the root logger to that set by the environment
// variables KEA_LOGGER_SEVERITY, KEA_LOGGER_DBGLEVEL and KEA_LOGGER_DESTINATION.

void
resetUnitTestRootLogger() {

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
                             keaLoggerSeverity(isc::log::DEBUG),
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
        // Not a recognised destination, assume a file.
        option.destination = OutputOption::DEST_FILE;
        option.filename = dest;
    }

    // ... and set the destination
    spec.addOutputOption(option);
    LoggerManager manager;
    manager.process(spec);
}


// Logger Run-Time Initialization via Environment Variables
void initLogger(isc::log::Severity severity, int dbglevel) {

    // Root logger name is defined by the environment variable KEA_LOGGER_ROOT.
    // If not present, the name is "kea".
    const char* DEFAULT_ROOT = "kea";
    const char* root = getenv("KEA_LOGGER_ROOT");
    if (! root) {
        // If not present, the name is "kea".
        root = isc::log::getDefaultRootLoggerName().c_str();
    }

    // Set the local message file
    const char* localfile = getenv("KEA_LOGGER_LOCALMSG");

    // Set a directory for creating lockfiles when running tests
    setenv("KEA_LOCKFILE_DIR", TOP_BUILDDIR, 0);

    // Initialize logging
    initLogger(root, isc::log::DEBUG, isc::log::MAX_DEBUG_LEVEL, localfile);

    // Now set reset the output destination of the root logger, overriding
    // the default severity, debug level and destination with those specified
    // in the environment variables.  (The two-step approach is used as the
    // setUnitTestRootLoggerCharacteristics() function is used in several
    // places in the Kea tests, and it avoid duplicating code.)
    resetUnitTestRootLogger();
} 

} // namespace log
} // namespace isc
