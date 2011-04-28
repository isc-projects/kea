// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <stdlib.h>

#include <string>
#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <log/logger_support.h>

using namespace std;

// Initialize the logging.
void init_logging() {

    const char* DEFAULT_ROOT = "b10root";

    // Root logger name is defined by the environment variable B10_LOGGER_ROOT.
    // If not present, the name is "b10root".
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
            } catch (...) {
                // Error, but not fatal to the test
                std::cerr << "***ERROR*** Unable to translate "
                             "B10_LOGGER_DBGLEVEL \n";
            }
            dbglevel = level;
        }
    }

    // Initialize logging
    isc::log::initLogger(root, severity, dbglevel, NULL);
}

int
main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    init_logging();

    return (RUN_ALL_TESTS());
}
