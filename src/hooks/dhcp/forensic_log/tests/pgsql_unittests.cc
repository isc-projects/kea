// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file Contains tests that exercise the basic functionality of the
// class PgSqlStore.  These tests are independent of the hooks framework.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <pgsql/testutils/pgsql_schema.h>
#include <test_utils.h>
#include <testutils/gtest_utils.h>
#include <testutils/log_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

#include <cmath>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::dhcp::test;
using namespace isc::legal_log;
using namespace isc::test;
using namespace boost::posix_time;
namespace ph = std::placeholders;

namespace {

/// @brief Test fixture for testing PostgreSQL database backend.
class PgSqlTest : public isc::dhcp::test::LogContentTest, public runSQL {
public:
    /// @brief Store pointer
    typedef boost::shared_ptr<PgSqlStore> PgSqlStorePtr;

    /// @brief Constructor
    PgSqlTest() {
        // Ensure we have the proper schema with no transient data.
        isc::db::test::createPgSQLSchema();

        // Change this to true if you need extra information about logging
        // checks to be printed.
        logCheckVerbose(false);
    }

    /// @brief Destructor
    virtual ~PgSqlTest() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        isc::db::test::destroyPgSQLSchema();
    }

    /// @brief Process output
    ///
    /// Remove heading and trailing lines, trim column, etc
    ///
    /// @param output reference to the string vector to fill with output
    /// @return true if processing was successful
    virtual bool getOutput(vector<string>& output) {
        const vector<string>& raw = getRawOutput();
        for (auto const& it : raw) {
            if (it.empty()) {
                continue;
            }
            if (*(it.crbegin()) == '\n') {
                output.push_back(it.substr(0, it.length() - 1));
            } else {
                output.push_back(string(it));
            }
        }
#if 0
        cerr << "OUTPUT" << endl;
        for (auto const& it : output) {
            cerr << it << endl;
        }
#endif
        return (true);
    }

    /// @brief Open the store
    void openStore() {
        // Construct the store
        DatabaseConnection::ParameterMap params;
        params["name"] = "keatest";
        params["user"] = "keatest";
        params["password"] = "keatest";
        ASSERT_NO_THROW(store_.reset(new PgSqlStore(params)));

        // Open the database
        ASSERT_NO_THROW(store_->open());
    }

    /// @brief Close the store
    void closeStore() {
        // Close does nothing
        EXPECT_NO_THROW(store_->close());

        // Destructor close the database
        EXPECT_NO_THROW(store_.reset());
    }

    /// @brief Fill some log entries
    void fillStore() {
        ASSERT_EQ(samples_.size(), addresses_.size());
        for (size_t i = 0; i < samples_.size(); ++i) {
            store_->writeln(samples_[i], addresses_[i]);
        }
    }

    /// @brief The store
    PgSqlStorePtr store_;

    /// @brief Addresses samples
    const vector<string> addresses_ = {
        "foo",
        "bar",
        "",
        "192.2.1.100",
        "192.2.1.100",
        "2001:db8:1::",
        "2001:db8:1::",
        "2001:0db8:0001:0002:0123:4567:89ab:cdef/128"
    };

    /// @brief Log entry samples
    const vector<string> samples_ = {
        "first log",
        "another log",
        "again a log",
        "Address: 192.2.1.100 has been renewed",
        "Address: 192.2.1.100 has been renewed "
        "for 1 hrs 52 min 15 secs to a device with hardware address: "
        "hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 "
        "connected via relay at address: 192.2.16.33, identified by "
        "circuit-id: 68:6f:77:64:79 (howdy) and remote-id: 87:f6:79:77:ef",
        "Address: 2001:db8:1:: has been assigned",
        "Address: 2001:db8:1:: has been assigned "
        "for 0 hrs 11 mins 53 secs to a device with DUID: "
        "17:34:e2:ff:09:92:54 and hardware address: hwtype=1 "
        "08:00:2b:02:3f:4e (from Raw Socket) connected via relay at "
        "address: fe80::abcd for client on link address: 3001::1, hop "
        "count: 1, identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f "
        "and subscriber-id: 1a:2b:3c:4d:5e:6f",
        "last log"
    };
};

/// @brief Tests the PgSqlStore constructor.
TEST_F(PgSqlTest, invalidConstruction) {
    // Verify that a PgSqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params;
    params["user"] = "keatest";
    params["password"] = "keatest";
    ASSERT_NO_THROW(store_.reset(new PgSqlStore(params)));
    // Check params validity is done by open().
    EXPECT_THROW(store_->open(), NoDatabaseName);

    // Verify that a PgSqlStore with an invalid connect-timeout is rejected.
    params["name"] = "keatest";
    // 2^64 should be greater than INT_MAX
    params["connect-timeout"] = "18446744073709551616";
    ASSERT_NO_THROW(store_.reset(new PgSqlStore(params)));
    EXPECT_THROW(store_->open(), DbInvalidTimeout);
}

/// @brief Tests opening and closing PgSqlStore
TEST_F(PgSqlTest, open) {
    // Construct the store_
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest";
    params["password"] = "keatest";
    ASSERT_NO_THROW(store_.reset(new PgSqlStore(params)));

    // Check the type is postgresql
    EXPECT_EQ("postgresql", store_->getType());

    // Open the database
    ASSERT_NO_THROW(store_->open());

    // Close does nothing
    EXPECT_NO_THROW(store_->close());

    // Destructor close the database
    EXPECT_NO_THROW(store_.reset());
}

/// @brief Check schema version
TEST_F(PgSqlTest, version) {
    // Open the store
    openStore();

    // Check version using the API
    std::pair<uint32_t, uint32_t> version;
    EXPECT_NO_THROW(version = store_->getVersion());
    EXPECT_EQ(PGSQL_SCHEMA_VERSION_MAJOR, version.first);
    EXPECT_EQ(PGSQL_SCHEMA_VERSION_MINOR, version.second);

    // Close the store
    closeStore();

    // Check version using pgsql command
    setenv("PGPASSWORD", "keatest", 0);
    setQuery("SELECT version, minor FROM schema_version");
    setCommand("psql --set ON_ERROR_STOP=1 -A -t -h localhost -q "
               "-U keatest -d keatest -c ");
    EXPECT_NO_THROW(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_FALSE(output.empty());
    EXPECT_EQ(1, output.size());
    ostringstream s;
    s << version.first << "|" << version.second;
    EXPECT_EQ(s.str(), output[0]);

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("LEGAL_LOG_PGSQL_GET_VERSION "
              "obtaining schema version information");
    EXPECT_TRUE(checkFile());
}

/// @brief Check addresses
TEST_F(PgSqlTest, addresses) {
    // Open the store
    openStore();

    // Fill the store
    fillStore();

    // Close the store
    closeStore();

    setenv("PGPASSWORD", "keatest", 0);
    setQuery("SELECT address FROM logs");
    setCommand("psql --set ON_ERROR_STOP=1 -A -t -h localhost -q "
               "-U keatest -d keatest -c ");
    EXPECT_NO_THROW(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_EQ(addresses_.size(), output.size());
    for (size_t i = 0; i < output.size(); ++i) {
        EXPECT_EQ(addresses_[i], output[i]);
    }
}

/// @brief Check log entries
TEST_F(PgSqlTest, entries) {
    // Open the store
    openStore();

    // Fill the store
    fillStore();

    // Close the store
    closeStore();

    setenv("PGPASSWORD", "keatest", 0);
    setQuery("SELECT log FROM logs");
    setCommand("psql --set ON_ERROR_STOP=1 -A -t -h localhost -q "
               "-U keatest -d keatest -c ");
    EXPECT_NO_THROW(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_EQ(samples_.size(), output.size());
    for (size_t i = 0; i < output.size(); ++i) {
        EXPECT_EQ(samples_[i], output[i]);
    }
}

/// @brief Check timestamps
TEST_F(PgSqlTest, timestamps) {
    // Open the store
    openStore();

    // Get begin date
    ptime begin_p = microsec_clock::universal_time();

    // Fill the store
    fillStore();

    // Get end date
    ptime end_p = microsec_clock::universal_time();
    ASSERT_LE(begin_p, end_p);

    // Close the store
    closeStore();

    setenv("PGPASSWORD", "keatest", 0);
    setQuery("SELECT EXTRACT(epoch FROM timestamp) FROM logs");
    setCommand("psql --set ON_ERROR_STOP=1 -A -t -h localhost -q "
               "-U keatest -d keatest -c ");
    EXPECT_NO_THROW(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_EQ(samples_.size(), output.size());
    ptime current = begin_p;
    for (size_t i = 0; i < output.size(); ++i) {
        // Get the timestamp as a double from epoch
        double ts_d = 0.0;
        ASSERT_NO_THROW(ts_d = boost::lexical_cast<double>(output[i]));
        // Extract seconds and microseconds;
        double ts_s;
        double ts_ms = modf(ts_d, &ts_s) * 1000000.;
        // Get the timestamp in posix time format (will work after 20138?)
        ptime ts_p = from_time_t(static_cast<time_t>(ts_s)) +
            microseconds(static_cast<long>(ts_ms));
        EXPECT_LE(current, ts_p);
        current = ts_p;
    }
    EXPECT_LE(current, end_p);
}

/// @brief Check oversized address
TEST_F(PgSqlTest, oversized) {
    // Open the store
    openStore();

    // Check what happen with an oversized address
    string address("2001:0db8:0001:0002:0123:4567:89ab:cdef/128!");
    EXPECT_THROW(store_->writeln("oversized address", address),
                 DbOperationError);
}

class PgSqlLegalLogDbLostCallbackTest : public LegalLogDbLostCallbackTest {
public:

    /// @brief Constructor.
    PgSqlLegalLogDbLostCallbackTest() { }

    /// @brief Destructor.
    virtual ~PgSqlLegalLogDbLostCallbackTest() { }

    /// @brief Prepares the class for a test.
    ///
    /// Invoked by gtest prior test entry, we create the
    /// appropriate schema and create a basic DB manager to
    /// wipe out any prior instance
    virtual void SetUp() {
        // Ensure we have the proper schema with no transient data.
        createPgSQLSchema();
    }

    /// @brief Pre-text exit clean up
    ///
    /// Invoked by gtest upon test exit, we destroy the schema
    /// we created.
    virtual void TearDown() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        destroyPgSQLSchema();
    }

    /// @brief Method which returns the back end specific connection
    /// string
    virtual std::string validConnectString() {
        return (validPgSQLConnectionString());
    }

    /// @brief Method which returns invalid back end specific connection
    /// string
    virtual std::string invalidConnectString() {
        return (connectionString(PGSQL_VALID_TYPE, INVALID_NAME, VALID_HOST,
                                 VALID_USER, VALID_PASSWORD));
    }

    /// @brief Verifies the Backend Store behavior if DB connection can not be
    /// established but succeeds on retry
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies that connectivity is unavailable
    /// and then recovered on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked
    virtual void testRetryOpenDbLostAndRecoveredCallback();

    /// @brief Verifies the Backend Store behavior if DB connection can not be
    /// established but fails on retry
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies that connectivity is unavailable
    /// and then fails again on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked
    virtual void testRetryOpenDbLostAndFailedCallback();

    /// @brief Verifies the Backend Store behavior if DB connection can not be
    /// established but succeeds on retry
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies that connectivity is unavailable
    /// and then recovered on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    virtual void testRetryOpenDbLostAndRecoveredAfterTimeoutCallback();

    /// @brief Verifies the Backend Store behavior if DB connection can not be
    /// established but fails on retry
    ///
    /// This function creates a Backend Store with a back end that supports
    /// connectivity lost callback. It verifies that connectivity is unavailable
    /// and then fails again on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    virtual void testRetryOpenDbLostAndFailedAfterTimeoutCallback();

    /// @brief Verifies open failures do NOT invoke db lost callback
    ///
    /// The db lost callback should only be invoked after successfully
    /// opening the DB and then subsequently losing it. Failing to
    /// open should be handled directly by the application layer.
    virtual void testNoCallbackOnOpenFailure();

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
    virtual void testDbLostAndRecoveredCallback();

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
    virtual void testDbLostAndFailedCallback();

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
    virtual void testDbLostAndRecoveredAfterTimeoutCallback();

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
    virtual void testDbLostAndFailedAfterTimeoutCallback();
};

void
PgSqlLegalLogDbLostCallbackTest::testRetryOpenDbLostAndRecoveredCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Verify that a PgSqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(invalidConnectString());

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());
    params.emplace("retry-on-startup", "true");

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_THROW(BackendStore::instance()->open(), DbOpenErrorWithRetry);

    // Verify there is no instance.
    ASSERT_FALSE(BackendStore::instance());

    dbr.reset();

    params = db::DatabaseConnection::parse(validConnectString());
    params.emplace("retry-on-startup", "true");
    BackendStore::setParameters(params);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(BackendStore::instance());
}

void
PgSqlLegalLogDbLostCallbackTest::testRetryOpenDbLostAndFailedCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Verify that a PgSqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(invalidConnectString());

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());
    params.emplace("retry-on-startup", "true");

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_THROW(BackendStore::instance()->open(), DbOpenErrorWithRetry);

    // Verify there is no instance.
    ASSERT_FALSE(BackendStore::instance());

    dbr.reset();

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());
}

void
PgSqlLegalLogDbLostCallbackTest::testRetryOpenDbLostAndRecoveredAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = invalidConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;

    // Verify that a PgSqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(access);

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());
    params.emplace("retry-on-startup", "true");

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_THROW(BackendStore::instance()->open(), DbOpenErrorWithRetry);

    // Verify there is no instance.
    ASSERT_FALSE(BackendStore::instance());

    dbr.reset();

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());

    access = validConnectString();
    access += extra;
    params = db::DatabaseConnection::parse(access);
    params.emplace("retry-on-startup", "true");
    BackendStore::setParameters(params);

    sleep(1);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(BackendStore::instance());

    sleep(1);

    io_service_->poll();

    // No callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(BackendStore::instance());
}

void
PgSqlLegalLogDbLostCallbackTest::testRetryOpenDbLostAndFailedAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = invalidConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;

    // Verify that a PgSqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(access);

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());
    params.emplace("retry-on-startup", "true");

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_THROW(BackendStore::instance()->open(), DbOpenErrorWithRetry);

    // Verify there is no instance.
    ASSERT_FALSE(BackendStore::instance());

    dbr.reset();

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());

    sleep(1);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());

    sleep(1);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(3, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());
}

void
PgSqlLegalLogDbLostCallbackTest::testNoCallbackOnOpenFailure() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Verify that a PgSqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(invalidConnectString());

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_THROW(BackendStore::instance()->open(), DbOpenError);

    io_service_->poll();

    EXPECT_EQ(0, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());
}

void
PgSqlLegalLogDbLostCallbackTest::testDbLostAndRecoveredCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Verify that a PgSqlStore with database name is not rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(validConnectString());

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_NO_THROW(BackendStore::instance()->open());

    ASSERT_TRUE(BackendStore::instance());

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ASSERT_NO_THROW(BackendStore::instance()->writeln("test", "192.2.1.100"));

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(BackendStore::instance()->writeln("test", "192.2.1.101");,
                 DbConnectionUnusable);

    ASSERT_TRUE(BackendStore::instance());

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(BackendStore::instance());
}

void
PgSqlLegalLogDbLostCallbackTest::testDbLostAndFailedCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Verify that a PgSqlStore with database name is not rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(validConnectString());

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_NO_THROW(BackendStore::instance()->open());

    ASSERT_TRUE(BackendStore::instance());

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ASSERT_NO_THROW(BackendStore::instance()->writeln("test", "192.2.1.100"));

    params = db::DatabaseConnection::parse(invalidConnectString());
    BackendStore::setParameters(params);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(BackendStore::instance()->writeln("test", "192.2.1.101"),
                 DbConnectionUnusable);

    ASSERT_TRUE(BackendStore::instance());

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());
}

void
PgSqlLegalLogDbLostCallbackTest::testDbLostAndRecoveredAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Verify that a PgSqlStore with database name is not rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(access);

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_NO_THROW(BackendStore::instance()->open());

    ASSERT_TRUE(BackendStore::instance());

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ASSERT_NO_THROW(BackendStore::instance()->writeln("test", "192.2.1.100"));

    access = invalidConnectString();
    access += extra;
    params = db::DatabaseConnection::parse(access);
    BackendStore::setParameters(params);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(BackendStore::instance()->writeln("test", "192.2.1.101"),
                 DbConnectionUnusable);

    ASSERT_TRUE(BackendStore::instance());

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());

    access = validConnectString();
    access += extra;
    params = db::DatabaseConnection::parse(access);
    BackendStore::setParameters(params);

    sleep(1);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(BackendStore::instance());

    sleep(1);

    io_service_->poll();

    // No callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(BackendStore::instance());
}

void
PgSqlLegalLogDbLostCallbackTest::testDbLostAndFailedAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Verify that a PgSqlStore with database name is not rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(access);

    ASSERT_NO_THROW(BackendStore::instance().reset(new PgSqlStore(params)));

    // Check params validity is done by open().
    EXPECT_NO_THROW(BackendStore::instance()->open());

    ASSERT_TRUE(BackendStore::instance());

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ASSERT_NO_THROW(BackendStore::instance()->writeln("test", "192.2.1.100"));

    access = invalidConnectString();
    access += extra;
    params = db::DatabaseConnection::parse(access);
    BackendStore::setParameters(params);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(BackendStore::instance()->writeln("test", "192.2.1.101"),
                 DbConnectionUnusable);

    ASSERT_TRUE(BackendStore::instance());

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());

    sleep(1);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());

    sleep(1);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(3, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(BackendStore::instance());
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that db lost callback is not invoked on an open failure
TEST_F(PgSqlLegalLogDbLostCallbackTest, testNoCallbackOnOpenFailure) {
    MultiThreadingTest mt(false);
    testNoCallbackOnOpenFailure();
}

/// @brief Verifies that db lost callback is not invoked on an open failure
TEST_F(PgSqlLegalLogDbLostCallbackTest, testNoCallbackOnOpenFailureMultiThreading) {
    MultiThreadingTest mt(true);
    testNoCallbackOnOpenFailure();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PgSqlLegalLogDbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedAfterTimeoutCallback();
}

} // end of anonymous namespace
