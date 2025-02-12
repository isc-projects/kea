// Copyright (C) 2016-2024 Internet Systems Consortium, Inc. ("ISC")
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
#include <backend_store.h>
#include <rotating_file.h>
#include <util/reconnect_ctl.h>
#ifdef HAVE_MYSQL
#include <mysql_legal_log.h>
#endif
#ifdef HAVE_PGSQL
#include <pgsql_legal_log.h>
#endif

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <time.h>

#include <errno.h>
#include <cstdio>
#include <locale>
#include <fstream>
#include <sys/stat.h>

using namespace isc;
using namespace hooks;
using namespace legal_log;

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
    /// @throw BackendStoreError if given file name is empty.
    TestableRotatingFile(struct tm time,
                         const TimeUnit unit = TimeUnit::Day,
                         const uint32_t count = 1,
                         const std::string& prerotate = "",
                         const std::string& postrotate = "")
        : RotatingFile(TEST_DATA_BUILDDIR, "legal", unit, count, prerotate,
                       postrotate), time_(time) {
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
    std::set<std::string> file_list_;

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
    virtual ~RotatingFileTest() = default;

    /// @brief Single instance of IOService.
    static asiolink::IOServicePtr getIOService() {
        static asiolink::IOServicePtr io_service(new asiolink::IOService());
        return (io_service);
    }

    /// @brief Wait for file to be created or exit with timeout after 3 seconds.
    void waitForFile(const std::string& name) {
        std::ifstream test_log;
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
        BackendStore::instance().reset();
        BackendStore::setIOService(getIOService());
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
    std::string genName(const boost::gregorian::date& day) {
        boost::gregorian::date::ymd_type ymd = day.year_month_day();
        std::ostringstream stream;
        stream << TEST_DATA_BUILDDIR << "/" << "legal" << "." << ymd.year
               << std::right << std::setfill('0') << std::setw(2)
               << ymd.month.as_number() << std::setw(2) << ymd.day << ".txt";
        return (stream.str());
    }

    /// @brief Generate a file name based on the given date
    ///
    /// Uses the same formatting as RotatingFile to build file names
    ///
    /// @param time - time to use in the file name
    /// @return - the generated file name
    std::string genName(struct tm& time) {
        time_t timestamp = mktime(&time);
        std::ostringstream stream;
        stream << TEST_DATA_BUILDDIR << "/" << "legal.T"
               << std::right << std::setfill('0') << std::setw(20)
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
                ASSERT_TRUE(i < expected_lines.size()) << "Too many entries in file: "
                                                       << file_name;

                std::string cmp_line = now_string + " " + expected_lines[i];
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
    void checkFileNotCreated(const std::string& file_name) {
        std::ifstream is;
        is.open(file_name.c_str());
        ASSERT_FALSE(is.good()) << "The file is present: " << file_name;
    }

    /// @brief Returns the current timezone abbreviate as a string
    ///
    /// @param use_time used instead of time() as the input time_t
    /// from which to derive the timezone
    /// @return The current timezone
    std::string getTimezone(time_t use_time = 0) {
        char buffer[16];

        struct tm time_info = RotatingFileTest::getTime(use_time);

        strftime(buffer, sizeof(buffer), "%Z", &time_info);

        return (std::string(buffer));
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
        BackendStore::instance().reset();
        isc::dhcp::CfgMgr::instance().clear();
        isc::dhcp::CfgMgr::instance().setFamily(AF_INET);
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~CalloutTest() {
        BackendStore::instance().reset();
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

/// @brief Helper class to execute a SQL tool and get results
class runSQL {
public:
    /// @brief Constructor
    runSQL() {
        reset();
    }

    /// @brief Destructor
    virtual ~runSQL() = default;

    /// @brief Reset everything
    void reset() {
        command_ = "";
        query_ = "";
        result_ = 0;
        output_.clear();
    }

    /// @brief Get command
    /// @return the command
    const std::string& getCommand() const {
        return (command_);
    }

    /// @brief Set command
    /// @param the command
    void setCommand(const std::string& command) {
        command_ = command;
    }

    /// @brief Get query
    /// @return the query
    const std::string& getQuery() const {
        return (query_);
    }

    /// @brief Set query
    /// @param the query
    void setQuery(const std::string& query) {
        query_ = query;
    }

    /// @brief Get result
    /// @return the exit code
    int getResult() const {
        return (result_);
    }

    /// @brief Get raw output
    /// @return the unprocessed output
    std::vector<std::string> getRawOutput() {
        return (output_);
    }

    /// @brief Process output
    /// @param output reference to the string vector to fill with output
    /// @return true if processing was successful
    virtual bool getOutput(std::vector<std::string>& output) = 0;

    /// @brief Execute
    /// @throw std::system_error according to boost documentation
    void execute() {
        // Reading stream
        FILE* istream;
        size_t buffer_size = 1024;
        char buffer[buffer_size + 1];

        // Child process
        std::string cmd = command_ + "\"" + query_ + "\"";
        istream = popen(cmd.c_str(), "r");

        // Check errors
        if (!istream) {
            result_ = -1;
            return;
        } else {
            result_ = ferror(istream);
            if (result_) {
                return;
            }
        }

        // Read output
        while (!feof(istream) && fgets(buffer, buffer_size, istream)) {
            output_.push_back(std::string(buffer));
        }

        // Wait for children to terminate and get its exit code
        result_ = pclose(istream);
    }

private:
    // @brief command
    std::string command_;

    // @brief query
    std::string query_;

    // @brief exit code aka result
    int result_;

    // @brief output
    std::vector<std::string> output_;
};

/// @brief Test fixture for testing database backend connection recovery.
class LegalLogDbLostCallbackTest : public ::testing::Test {
public:

    /// @brief Constructor.
    LegalLogDbLostCallbackTest()
        : db_lost_callback_called_(0), db_recovered_callback_called_(0),
          db_failed_callback_called_(0),
          io_service_(boost::make_shared<isc::asiolink::IOService>()) {
        isc::db::DatabaseConnection::db_lost_callback_ = 0;
        isc::db::DatabaseConnection::db_recovered_callback_ = 0;
        isc::db::DatabaseConnection::db_failed_callback_ = 0;
        isc::db::DatabaseConnection::setIOService(io_service_);
        BackendStore::setIOService(io_service_);
        isc::asiolink::ProcessSpawn::setIOService(io_service_);
        isc::dhcp::TimerMgr::instance()->setIOService(io_service_);
        BackendStore::instance().reset();
    }

    /// @brief Destructor.
    virtual ~LegalLogDbLostCallbackTest() {
        isc::db::DatabaseConnection::db_lost_callback_ = 0;
        isc::db::DatabaseConnection::db_recovered_callback_ = 0;
        isc::db::DatabaseConnection::db_failed_callback_ = 0;
        isc::db::DatabaseConnection::setIOService(isc::asiolink::IOServicePtr());
        BackendStore::setIOService(isc::asiolink::IOServicePtr());
        isc::asiolink::ProcessSpawn::setIOService(isc::asiolink::IOServicePtr());
        isc::dhcp::TimerMgr::instance()->unregisterTimers();
        BackendStore::instance().reset();
    }

    /// @brief Prepares the class for a test.
    ///
    /// Invoked by gtest prior test entry, we create the
    /// appropriate schema and create a basic DB manager to
    /// wipe out any prior instance
    virtual void SetUp() = 0;

    /// @brief Pre-text exit clean up
    ///
    /// Invoked by gtest upon test exit, we destroy the schema
    /// we created.
    virtual void TearDown() = 0;

    /// @brief Method which returns the back end specific connection
    /// string
    virtual std::string validConnectString() = 0;

    /// @brief Method which returns invalid back end specific connection
    /// string
    virtual std::string invalidConnectString() = 0;

    /// @brief Verifies the Backend Store behavior if DB connection can not be
    /// established but succeeds on retry
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies that connectivity is unavailable
    /// and then recovered on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked
    virtual void testRetryOpenDbLostAndRecoveredCallback() = 0;

    /// @brief Verifies the Backend Store behavior if DB connection can not be
    /// established but fails on retry
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies that connectivity is unavailable
    /// and then fails again on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked
    virtual void testRetryOpenDbLostAndFailedCallback() = 0;

    /// @brief Verifies the Backend Store behavior if DB connection can not be
    /// established but succeeds on retry
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies that connectivity is unavailable
    /// and then recovered on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    virtual void testRetryOpenDbLostAndRecoveredAfterTimeoutCallback() = 0;

    /// @brief Verifies the Backend Store behavior if DB connection can not be
    /// established but fails on retry
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies that connectivity is unavailable
    /// and then fails again on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    virtual void testRetryOpenDbLostAndFailedAfterTimeoutCallback() = 0;

    /// @brief Verifies open failures do NOT invoke db lost callback
    ///
    /// The db lost callback should only be invoked after successfully
    /// opening the DB and then subsequently losing it. Failing to
    /// open should be handled directly by the application layer.
    virtual void testNoCallbackOnOpenFailure() = 0;

    /// @brief Verifies the Backend Store behavior if DB connection is lost
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies connectivity by issuing a known
    /// valid query. Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the Backend Store. It then reissues the
    /// query and verifies that:
    /// -# The Query throws DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked
    virtual void testDbLostAndRecoveredCallback() = 0;

    /// @brief Verifies the Backend Store behavior if DB connection is lost
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies connectivity by issuing a known
    /// valid query. Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the Backend Store. It then reissues the
    /// query and verifies that:
    /// -# The Query throws DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked
    virtual void testDbLostAndFailedCallback() = 0;

    /// @brief Verifies the Backend Store behavior if DB connection is lost
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies connectivity by issuing a known
    /// valid query. Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the Backend Store. It then reissues the
    /// query and verifies that:
    /// -# The Query throws DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    virtual void testDbLostAndRecoveredAfterTimeoutCallback() = 0;

    /// @brief Verifies the Backend Store behavior if DB connection is lost
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies connectivity by issuing a known
    /// valid query. Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the Backend Store. It then reissues the
    /// query and verifies that:
    /// -# The Query throws DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    virtual void testDbLostAndFailedAfterTimeoutCallback() = 0;

    /// @brief Callback function registered with the Backend Store
    bool db_lost_callback(util::ReconnectCtlPtr /* not_used */) {
        return (++db_lost_callback_called_);
    }

    /// @brief Flag used to detect calls to db_lost_callback function
    uint32_t db_lost_callback_called_;

    /// @brief Callback function registered with the Backend Store
    bool db_recovered_callback(util::ReconnectCtlPtr /* not_used */) {
        return (++db_recovered_callback_called_);
    }

    /// @brief Flag used to detect calls to db_recovered_callback function
    uint32_t db_recovered_callback_called_;

    /// @brief Callback function registered with the Backend Store
    bool db_failed_callback(util::ReconnectCtlPtr /* not_used */) {
        return (++db_failed_callback_called_);
    }

    /// @brief Flag used to detect calls to db_failed_callback function
    uint32_t db_failed_callback_called_;

    /// The IOService object, used for all ASIO operations.
    isc::asiolink::IOServicePtr io_service_;
};

} // namespace legal_log
} // namespace isc

#endif // TEST_UTILS_H
