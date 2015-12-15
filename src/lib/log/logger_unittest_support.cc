// Copyright (C) 2011,2014,2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

// Logger Run-Time Initialization via Environment Variables
void initLogger(isc::log::Severity severity, int dbglevel) {

    // Root logger name is defined by the environment variable KEA_LOGGER_ROOT.
    // If not present, the name is "kea".
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
    isc::log::setDefaultLoggingOutput();
} 

} // namespace log
} // namespace isc
