// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/log_utils.h>
#include <cstdlib>
#include <iostream>

namespace isc {
namespace dhcp {
namespace test {

LogContentTest::LogContentTest()
    :verbose_(false) {
    // Get rid of any old files
    remFile();

    // Set up the logger for use in checking the debug statements.
    // We send the debug statements to a file which we can
    // check after the evaluations have completed.  We also
    // set the log severity and debug levels so that the log
    // statements are executed.
    LoggerSpecification spec(getRootLoggerName(),
                             keaLoggerSeverity(isc::log::DEBUG),
                             keaLoggerDbglevel(isc::log::MAX_DEBUG_LEVEL));
    OutputOption option;
    option.destination = OutputOption::DEST_FILE;
    option.filename = string(LogContentTest::LOG_FILE);
    spec.addOutputOption(option);
    LoggerManager manager;
    manager.process(spec);

    // Overwrite the verbose_ default is the KEA_LOG_CHECK_VERBOSE
    // environment variable exists.
    if (getenv(KEA_LOG_CHECK_VERBOSE)) {
        verbose_ = true;
    }
}

LogContentTest:: ~LogContentTest() {
    remFile();
}

bool LogContentTest::checkFile() {
    ifstream file(LOG_FILE);
    EXPECT_TRUE(file.is_open());
    string line, exp_line;
    int i = 0;
    bool found = true;

    using namespace std;

    while (getline(file, line) && (i != exp_strings_.size())) {
        exp_line = exp_strings_[i];
        if (verbose_) {
            cout << "Read line  : " << line << endl;
            cout << "Looking for: " << exp_line << endl;
        }
        i++;
        if (string::npos == line.find(exp_line)) {
            if (verbose_) {
                cout << "Verdict    : not found" << endl;
            }
            found = false;
        }
    }

    file.close();

    if ((i != exp_strings_.size()) || (found == false)) {
        if (verbose_) {
            cout << "Final verdict: false" << endl;
        }
        return (false);
    }

    return (true);
}

size_t LogContentTest::countFile(const string& exp_string) {
    ifstream file(LOG_FILE);
    EXPECT_TRUE(file.is_open());
    string line;
    size_t cnt = 0;

    using namespace std;

    if (verbose_) {
        cout << "Looking for:" << exp_string << endl;
    }
    while (getline(file, line)) {
        if (verbose_) {
            cout << "Read line  :" << line << endl;
        }
        if (line.find(exp_string) != string::npos) {
            ++cnt;
        }
    }

    file.close();

    if (verbose_) {
        cout << "Final count: " << cnt << endl;
    }

    return (cnt);
}

void LogContentTest::remFile() {
    static_cast<void>(remove(LOG_FILE));
}

void LogContentTest::addString(const string& new_string) {
    exp_strings_.push_back(new_string);
}

// Set up the name of the LOG_FILE for use in checking
// the debug statements.
// Must not be the same file name used by test shell scripts.
const char* LogContentTest::LOG_FILE = "logtest.log";

// The environment variable to overwrite the verbose_ default value.
const char* LogContentTest::KEA_LOG_CHECK_VERBOSE = "KEA_LOG_CHECK_VERBOSE";

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
