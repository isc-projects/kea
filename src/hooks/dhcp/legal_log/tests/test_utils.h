// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <exceptions/exceptions.h>
#include <hooks/callout_manager.h>
#include <rotating_file.h>

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <errno.h>
#include <locale>
#include <sys/stat.h>

using namespace isc;
using namespace hooks;
using namespace legal_log;

extern RotatingFilePtr legal_file;

namespace isc {
namespace legal_log {

/// @brief Derivation of RotatingFile which provides an overridden date mechanism
/// This class overrides RotatingFile::today() with an implementation that returns
/// fixed value, rather than based on the actual system time.  This simplifies
/// testing file rotation.
class TestableRotatingFile : public RotatingFile {
public:
    /// @brief Constructor
    ///
    /// Create a RotatingFile for the given file name without opening the file.
    /// @param today The date with which to override RotatingFile::today()
    ///
    /// @throw RotatingFileError if given file name is empty.
    TestableRotatingFile(boost::gregorian::date today)
        : RotatingFile(TEST_DATA_BUILDDIR, "legal"), today_(today) {
    }

    /// @brief Destructor.
    ////
    /// The destructor does call the close method.
    virtual ~TestableRotatingFile() {};

    /// @brief Overrides RotatingFile::today()
    /// @return value of member variable today_
    virtual boost::gregorian::date today() const {
        return (today_);
    }

    /// @brief Overrides RotatingFile::now()
    /// @return
    virtual time_t now() const {
        struct tm now_tm = boost::gregorian::to_tm(today_);
        return (mktime(&now_tm));
    }

    /// @brief Sets the override date value
    /// @param new value for the override date
    void setToday(boost::gregorian::date day) {
        today_ = day;
    }
    /// @brief Override date value
    boost::gregorian::date today_;
};

/// @brief Defines a pointer to a TestableRotatingFile
typedef boost::shared_ptr<TestableRotatingFile> TestableRotatingFilePtr;

/// @brief Test fixture for testing RotatingFile.
/// It provides tools for erasing test files, altering date values,
/// generating file names, checking file existance and content.
class RotatingFileTest : public ::testing::Test {
public:
    /// @brief Constructor
    /// Fetches the current day and removes files that may be left
    /// over from previous tests
    RotatingFileTest() : today_(boost::gregorian::day_clock::local_day()) {
        wipeFiles();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~RotatingFileTest() {
        wipeFiles();
    }

    /// @brief Removes files that may be left over from previous tests
    void wipeFiles() {
        ::remove((genName(today_)).c_str());
        ::remove((genName(adjustDay(today_, 1))).c_str());
    }

    /// @brief Returns a new date by adding given days to a given date
    /// @param org_day date to adjust
    /// @param days the number of days to add (may be negative)
    /// @return the new date
    boost::gregorian::date adjustDay(const boost::gregorian::date& org_day,
                                       int days) {
        boost::gregorian::date_duration dd(days);
        return (org_day + dd);
    }

    /// @brief Checks if the given file exists
    ///
    /// @return true if the file exists, false if it does not
    bool fileExists(const std::string& filename) {
        struct stat statbuf;
        if (stat(filename.c_str(), &statbuf) == 0) {
            return (true);
        }

        int sav_error = errno;
        if (errno == ENOENT) {
            return (false);
        }

        ADD_FAILURE() << "fileExists error - filename: " << filename
            << " error: " << strerror(sav_error);
        return (false);
    }

    /// @brief Generate a file name based on the given date
    ///
    /// Uses the same formatting as RotatingFile to build file names
    ///
    /// @param day date to use in the file name
    /// @return the generated file name
    std::string genName(const boost::gregorian::date& day)  {
        boost::gregorian::date::ymd_type ymd = day.year_month_day();
        std::ostringstream stream;
        stream << TEST_DATA_BUILDDIR << "/" << "legal" << "." << ymd.year
               << std::right << std::setfill('0') << std::setw(2)
               << ymd.month.as_number()
               << ymd.day << ".txt";
        return(stream.str());
    }

    /// @brief Check a file's contents against an expected set of lines
    ///
    /// Passes if the given file's content matches. Fails otherwise.
    ///
    /// @param file_name name of the file to read
    /// @param expected_lines a vector of the lines expected to be found
    /// in the file (entries DO NOT include EOL)
    void checkFileLines(const std::string& file_name,
                        const std::string& now_string,
                        const std::vector<std::string>& expected_lines) {
        std::ifstream is;
        is.open(file_name.c_str());
        ASSERT_TRUE(is.good()) << "Could not open file: " << file_name;

        int i = 0;
        while (!is.eof()) {
            char buf[1024];

            is.getline(buf, sizeof(buf));
            if (is.gcount() > 0) {
                ASSERT_TRUE(i < expected_lines.size())
                        << "Too many entries in file: " << file_name;

                std::string cmp_line = now_string + " " + expected_lines[i];
                ASSERT_EQ(cmp_line, buf)
                        << "line mismatch in: " << file_name
                        << " at line:" << i;

                ++i;
            }
        }

        ASSERT_EQ(i, expected_lines.size())
                    << "Not enough entries in file: " << file_name;
    }

    /// @brief Returns the current timezone abbreviate as a string
    std::string getTimezone()  {
        char buffer[16];
        time_t curtime;
        time(&curtime);
        struct tm* timeinfo;
        timeinfo = localtime(&curtime);

        strftime(buffer, sizeof(buffer), "%Z", timeinfo);
        return (std::string(buffer));
    }

    /// @brief The current date
    boost::gregorian::date today_;
};

/// @brief Test fixture for exercising Legal library callouts
/// It fetches the CalloutManager and cleans up any legal files
/// that may be created.
class CalloutTest : public RotatingFileTest {
public:
    /// @brief Constructor
    /// Fetches the current day and removes files that may be left
    /// over from previous tests
    CalloutTest() : RotatingFileTest(),
        co_manager_(new CalloutManager(1)) {
        legal_file.reset();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~CalloutTest() {
        legal_file.reset();
    }

    /// @brief Fetches the callout manager instance
    boost::shared_ptr<CalloutManager>getCalloutManager() {
        return(co_manager_);
    }

private:
    /// Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;
};

}; // namespace legal_log
}; // namespace isc

#endif // TEST_UTILS_H
