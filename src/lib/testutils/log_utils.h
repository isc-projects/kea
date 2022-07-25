// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_LOG_UTILS_H
#define TEST_LOG_UTILS_H

#include <string>
#include <fstream>

//#include <config.h>

#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <log/logger_support.h>

//#include <boost/shared_ptr.hpp>
//#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::log;

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test class for testing things that emit log entries
///
/// This class provides a convenient method for testing out
/// things that emit log entries.  The class sets up the logging
/// to log everything into a file and provides a routine to
/// check the expected strings vs the actual log entries.
/// The user needs to call the addString function for each of
/// the strings they expect in the output in the order they
/// will be emitted.

class LogContentTest : public ::testing::Test {
public:

    /// @brief Initializes the logger setup for using
    /// in checking log statements
    ///
    /// @todo add support to adjust the severity and debug level
    /// to allow for better control over the statements that
    /// get logged.
    LogContentTest();

    virtual ~LogContentTest();

    /// @brief check that the requested strings are in the
    /// test log file in the requested order.
    ///
    /// This routine expects that the caller has properly
    /// set up the vector of expected strings by calling
    /// addString() with the necessary strings.
    ///
    /// @return true if all of the strings match
    bool checkFile();

    /// @brief check that the requested string is in the
    /// test log file.
    ///
    /// @param exp_string the string to be searched
    /// @return count of matching lines
    size_t countFile(const string& exp_string);

    /// @brief remove the test log file
    void remFile();

    /// @brief Enables or disables verbose mode.
    ///
    /// See @ref verbose_ for details.
    ///
    /// @param talk_a_lot (true - as the name says, false - shut up)
    void logCheckVerbose(bool talk_a_lot) {
        verbose_ = talk_a_lot;
    }

    /// @brief Add a string to the vector of expected strings
    ///
    /// @param new_string the string to add to the end of the vector
    void addString(const string& new_string);

    vector<string> exp_strings_;
    static const char* LOG_FILE;
    static const char* KEA_LOG_CHECK_VERBOSE;

    /// @brief controls whether the checkFile() should print more details.
    ///
    /// If set to true, checkFile() will print each expected line, each
    /// logged line and will print out a failure message if those two do
    /// not match. Also, a final verdict is printed. Everything is printed
    /// on stdout.
    /// The default is false but can be overwritten by setting the
    /// KEA_LOG_CHECK_VERBOSE environment variable.
    bool verbose_;
};

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
#endif // TEST_LOG_UTILS_H
