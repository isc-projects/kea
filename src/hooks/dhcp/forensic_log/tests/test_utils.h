// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <asiolink/process_spawn.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/callout_manager.h>
#include <dhcpsrv/legal_log_mgr.h>
#include <rotating_file.h>
#include <util/reconnect_ctl.h>

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <time.h>

#include <errno.h>
#include <cstdio>
#include <locale>
#include <fstream>
#include <string>
#include <sys/stat.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace hooks;
using namespace legal_log;
using namespace std;

namespace isc {
namespace legal_log {

/// @brief Derivation of RotatingFile which provides an overridden date
/// mechanism.
///
/// This class overrides RotatingFile::now() with an implementation
/// that returns fixed value, rather than based on the actual system time.
/// This simplifies testing file rotation.
class TestableRotatingFile : public RotatingFile {
public:
    /// @brief Constructor
    ///
    /// Create a RotatingFile for the given file name without opening the file.
    /// @param time The date with which to override RotatingFile::now()
    /// @param unit The time unit used to rotate the file.
    /// @param count The number of time units used to rotate the file (0 means
    /// disabled).
    /// @param prerotate The script to be run before closing the old file.
    /// @param postrotate The script to be run after opening the new file.
    ///
    /// @throw LegalLogMgrError if given file name is empty.
    TestableRotatingFile(struct tm time,
                         const TimeUnit unit = TimeUnit::Day,
                         const uint32_t count = 1,
                         const string& prerotate = "",
                         const string& postrotate = "",
                         db::DatabaseConnection::ParameterMap map = db::DatabaseConnection::ParameterMap())
        : RotatingFile(map),  time_(time) {
        ElementPtr parameters = Element::createMap();
        parameters->set("count", Element::create(count));
        LegalLogMgr::parseFile(parameters, map);
        map["path"] = TEST_DATA_BUILDDIR;
        map["base-name"] = "legal";
        map["prerotate"] = prerotate;
        map["postrotate"] = postrotate;
        string time_unit = "day";
        switch (unit) {
            case RotatingFile::TimeUnit::Second:
                time_unit = "second";
                break;
            case RotatingFile::TimeUnit::Day:
                time_unit = "day";
                break;
            case RotatingFile::TimeUnit::Month:
                time_unit = "month";
                break;
            case RotatingFile::TimeUnit::Year:
                time_unit = "year";
                break;
            default:
                break;
        }
        map["time-unit"] = time_unit;
        apply(map);
    }

    /// @brief Destructor.
    ///
    /// The destructor does call the close method.
    virtual ~TestableRotatingFile() {
        for (auto const& file : file_list_) {
            ::remove(file.c_str());
        }
    }

    /// @brief Overrides RotatingFile::now()
    ///
    /// @return timestamp value since epoch
    virtual struct timespec now() const override {
        struct timespec ts = {mktime(&time_), 0};
        return (ts);
    }

    /// @brief Overrides RotatingFile::openInternal() and stores the name for
    /// removal after test ends
    ///
    /// @param time_info The current time info used to open log rotate file
    /// @param use_existing Flag which indicates if the name should be updated
    /// with previously created file name if the file can still be used
    virtual void openInternal(struct tm& time_info, bool use_existing) override {
        RotatingFile::openInternal(time_info, use_existing);
        file_list_.insert(getFileName());
    }

    /// @brief Sets the override date value
    ///
    /// @param new value for the override date
    void setNow(const struct tm& time) {
        time_ = time;
    }

    /// @brief Override date value
    mutable struct tm time_;

    /// @brief List of created files that need to be removed after test ends
    set<string> file_list_;

    /// @brief Make protected methods visible
    using RotatingFile::rotate;
    using RotatingFile::isOpen;
};

/// @brief Defines a pointer to a TestableRotatingFile
typedef boost::shared_ptr<TestableRotatingFile> TestableRotatingFilePtr;

/// @brief Test fixture for testing RotatingFile.
/// It provides tools for erasing test files, altering date values,
/// generating file names, checking file existence and content.
class RotatingFileTest : public ::testing::Test {
public:

    /// @brief Constructor
    RotatingFileTest() : time_(RotatingFileTest::getTime()) {
    }

    /// @brief Destructor
    virtual ~RotatingFileTest() {
        reset();
    }

    /// @brief Removes files that may be left over from previous tests
    void reset() {
        std::ostringstream stream;
        stream << "rm " << TEST_DATA_BUILDDIR << "/" << "*-legal"
               << ".*.txt 2>/dev/null";
        int result = ::system(stream.str().c_str());
        if (result != 0) {
            // Ignore the result, because it may well be non-zero value when
            // files to be removed don't exist.
            ;
        }
    }

    /// @brief Single instance of IOService.
    static asiolink::IOServicePtr getIOService() {
        static asiolink::IOServicePtr io_service(new asiolink::IOService());
        return (io_service);
    }

    /// @brief Wait for file to be created or exit with timeout after 3 seconds.
    void waitForFile(const string& name) {
        ifstream test_log;
        time_t now(time(0));
        while (true) {
            test_log.open(name);
            if (!test_log.fail()) {
                break;
            }
            ASSERT_LT(time(0), now + 3) << "timeout";
            usleep(100000);
        }
    }

    /// @brief Called before each test
    virtual void SetUp() override {
        // Clean up from past tests.
        LegalLogMgrFactory::instance().reset();
        db::DatabaseConnection::setIOService(getIOService());
        asiolink::ProcessSpawn::setIOService(getIOService());
    }

    /// @brief Returns a new date by adding given seconds to a given date
    ///
    /// @param org_second date to adjust
    /// @param seconds the number of seconds to add (may be negative)
    /// @return the new date
    struct tm adjustSecond(struct tm& org_second,
                           int seconds) {
        time_t timestamp = mktime(&org_second);
        timestamp += seconds;
        struct tm time_info;
        localtime_r(&timestamp, &time_info);
        return (time_info);
    }

    /// @brief Returns a new date by adding given days to a given date
    ///
    /// @param org_day date to adjust
    /// @param days the number of days to add (may be negative)
    /// @return the new date
    boost::gregorian::date adjustDay(const boost::gregorian::date& org_day,
                                     int days) {
        boost::gregorian::date_duration dd(days);
        return (org_day + dd);
    }

    /// @brief Returns a new date by adding given months to a given date
    ///
    /// @param org_month date to adjust
    /// @param months the number of days to add (may be negative)
    /// @return the new date
    boost::gregorian::date adjustMonth(const boost::gregorian::date& org_month,
                                       int months) {
        boost::gregorian::months mm(months);
        return (org_month + mm);
    }

    /// @brief Returns a new date by adding given years to a given date
    ///
    /// @param org_year date to adjust
    /// @param years the number of days to add (may be negative)
    /// @return the new date
    boost::gregorian::date adjustYear(const boost::gregorian::date& org_year,
                                      int years) {
        boost::gregorian::years yy(years);
        return (org_year + yy);
    }

    /// @brief Checks if the given file exists
    ///
    /// @return true if the file exists, false if it does not
    bool fileExists(const string& filename) {
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
    string genName(const boost::gregorian::date& day) {
        boost::gregorian::date::ymd_type ymd = day.year_month_day();
        ostringstream stream;
        stream << TEST_DATA_BUILDDIR << "/" << "legal" << "." << ymd.year
               << right << setfill('0') << setw(2)
               << ymd.month.as_number() << setw(2) << ymd.day << ".txt";
        return (stream.str());
    }

    /// @brief Generate a file name based on the given date
    ///
    /// Uses the same formatting as RotatingFile to build file names
    ///
    /// @param time - time to use in the file name
    /// @return - the generated file name
    string genName(struct tm& time) {
        time_t timestamp = mktime(&time);
        ostringstream stream;
        stream << TEST_DATA_BUILDDIR << "/" << "legal.T"
               << right << setfill('0') << setw(20)
               << static_cast<uint64_t>(timestamp) << ".txt";
        return (stream.str());
    }

    /// @brief Check a file's contents against an expected set of lines
    ///
    /// Passes if the given file's content matches. Fails otherwise.
    ///
    /// @param file_name name of the file to read
    /// @param expected_lines a vector of the lines expected to be found
    /// in the file (entries DO NOT include EOL)
    void checkFileLines(const string& file_name,
                        const string& now_string,
                        const vector<string>& expected_lines) {
        ifstream is;
        is.open(file_name.c_str());
        ASSERT_TRUE(is.good()) << "Could not open file: " << file_name;

        int i = 0;
        while (!is.eof()) {
            char buf[1024];

            is.getline(buf, sizeof(buf));
            if (is.gcount() > 0) {
                ASSERT_TRUE(i < expected_lines.size()) << "Too many entries in file: "
                                                       << file_name;

                string cmp_line = now_string + " " + expected_lines[i];
                ASSERT_EQ(cmp_line, buf) << "line mismatch in: " << file_name
                                         << " at line:" << i;

                ++i;
            }
        }

        ASSERT_EQ(i, expected_lines.size()) << "Not enough entries in file: "
                                            << file_name;
    }

    /// @brief Check that the file was not created.
    ///
    /// Passes if the given file does not exist. Fails otherwise.
    ///
    /// @param file_name name of the file to check
    void checkFileNotCreated(const string& file_name) {
        ifstream is;
        is.open(file_name.c_str());
        ASSERT_FALSE(is.good()) << "The file is present: " << file_name;
    }

    /// @brief Returns the current timezone abbreviate as a string
    ///
    /// @param use_time used instead of time() as the input time_t
    /// from which to derive the timezone
    /// @return The current timezone
    string getTimezone(time_t use_time = 0) {
        char buffer[16];

        struct tm time_info = RotatingFileTest::getTime(use_time);

        strftime(buffer, sizeof(buffer), "%Z", &time_info);

        return (string(buffer));
    }

    /// @brief Return current time
    ///
    /// @param use_time used instead of time() as the input time_t
    /// from which to derive the timezone (if required)
    /// @return The current time
    static struct tm getTime(time_t use_time = 0) {
        time_t curtime;
        struct tm time_info;

        if (use_time) {
            curtime = use_time;
        } else {
            time(&curtime);
        }

        localtime_r(&curtime, &time_info);

        return (time_info);
    }

    /// @brief Return current day
    ///
    /// @return The current day
    boost::gregorian::date today() {
        return (boost::gregorian::date_from_tm(time_));
    }

    /// @brief The testable rotating file instance
    TestableRotatingFilePtr rotating_file_;

    /// @brief The current date
    struct tm time_;

    /// @brief Initializer.
    RotatingFileInit init_;
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
        LegalLogMgrFactory::instance().reset();
        isc::dhcp::CfgMgr::instance().clear();
        isc::dhcp::CfgMgr::instance().setFamily(AF_INET);
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~CalloutTest() {
        LegalLogMgrFactory::instance().reset();
        isc::dhcp::CfgMgr::instance().clear();
        isc::dhcp::CfgMgr::instance().setFamily(AF_INET);
    }

    /// @brief Fetches the callout manager instance
    boost::shared_ptr<CalloutManager>getCalloutManager() {
        return (co_manager_);
    }

private:
    /// Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;
};

} // namespace legal_log
} // namespace isc

#endif // TEST_UTILS_H
