// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/log_utils.h>
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
            cout << "Read line  :" << line << endl;
            cout << "Looking for:" << exp_line << endl;
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

void LogContentTest::remFile() {
    static_cast<void>(remove(LOG_FILE));
}

void LogContentTest::addString(const string& new_string) {
    exp_strings_.push_back(new_string);
}

// Set up the name of the LOG_FILE for use in checking
// the debug statements
const char *LogContentTest::LOG_FILE = "test.log";

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace
