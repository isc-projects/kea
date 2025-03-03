// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <exceptions/exceptions.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/callout_manager.h>
#include <dhcpsrv/backend_store_factory.h>
#include <util/reconnect_ctl.h>

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
using namespace dhcp;

namespace isc {
namespace dhcp {

static isc::asiolink::IOServicePtr local_io_service = isc::asiolink::IOServicePtr(new isc::asiolink::IOService());

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

/// @brief Test fixture for testing forensic log database backend connection recovery.
class LegalLogDbLostCallbackTest : public ::testing::Test {
public:

    /// @brief Constructor.
    LegalLogDbLostCallbackTest()
        : db_lost_callback_called_(0), db_recovered_callback_called_(0),
          db_failed_callback_called_(0),
          io_service_(local_io_service) {
        isc::db::DatabaseConnection::db_lost_callback_ = 0;
        isc::db::DatabaseConnection::db_recovered_callback_ = 0;
        isc::db::DatabaseConnection::db_failed_callback_ = 0;
        isc::db::DatabaseConnection::setIOService(io_service_);
        BackendStoreFactory::setIOService(io_service_);
        isc::dhcp::TimerMgr::instance()->setIOService(io_service_);
        BackendStoreFactory::delAllBackends();
    }

    /// @brief Destructor.
    virtual ~LegalLogDbLostCallbackTest() {
        isc::db::DatabaseConnection::db_lost_callback_ = 0;
        isc::db::DatabaseConnection::db_recovered_callback_ = 0;
        isc::db::DatabaseConnection::db_failed_callback_ = 0;
        isc::db::DatabaseConnection::setIOService(isc::asiolink::IOServicePtr());
        BackendStoreFactory::setIOService(isc::asiolink::IOServicePtr());
        isc::dhcp::TimerMgr::instance()->unregisterTimers();
        BackendStoreFactory::delAllBackends();
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

} // namespace dhcp
} // namespace isc

#endif // TEST_UTILS_H
