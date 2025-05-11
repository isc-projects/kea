// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file Contains tests that exercise the basic functionality of the
// class MySqlStore.  These tests are independent of the hooks framework.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/testutils/forensic_test_utils.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <mysql/testutils/mysql_schema.h>
#include <mysql_legal_log.h>
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
using namespace isc::dhcp;
using namespace isc::test;
using namespace boost::posix_time;
namespace ph = std::placeholders;

namespace {

/// @brief Test fixture for testing MySQL database backend.
class MySqlTest : public isc::dhcp::test::LogContentTest, public runSQL {
public:
    /// @brief Store pointer
    typedef boost::shared_ptr<MySqlStore> MySqlStorePtr;

    /// @brief Constructor
    MySqlTest() {
        // Ensure we have the proper schema with no transient data.
        isc::db::test::createMySQLSchema();

        // Change this to true if you need extra information about logging
        // checks to be printed.
        logCheckVerbose(false);
    }

    /// @brief Destructor
    virtual ~MySqlTest() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        isc::db::test::destroyMySQLSchema();
    }

    /// @brief Check if SSL/TLS support is available and configured.
    bool hasMySQLTls() {
        std::string tls = getMySQLTlsEnv();
        if (tls.empty()) {
            tls = getMySQLTlsServer();
        }
        return (tls == "YES");
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
        ASSERT_NO_THROW_LOG(store_.reset(new MySqlStore(params)));

        // Open the database
        ASSERT_NO_THROW_LOG(store_->open());
    }

    /// @brief Close the store
    void closeStore() {
        // Close does nothing
        EXPECT_NO_THROW_LOG(store_->close());

        // Destructor close the database
        EXPECT_NO_THROW_LOG(store_.reset());
    }

    /// @brief Fill some log entries
    void fillStore() {
        ASSERT_EQ(samples_.size(), addresses_.size());
        for (size_t i = 0; i < samples_.size(); ++i) {
            store_->writeln(samples_[i], addresses_[i]);
        }
    }

    /// @brief The store
    MySqlStorePtr store_;

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

/// @brief Tests the MySqlStore constructor.
TEST_F(MySqlTest, invalidConstruction) {
    // Verify that a MySqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params;
    params["user"] = "keatest";
    params["password"] = "keatest";
    ASSERT_NO_THROW_LOG(store_.reset(new MySqlStore(params)));
    // Check params validity is done by open().
    EXPECT_THROW(store_->open(), NoDatabaseName);

    // Verify that a MySqlStore with an invalid connect-timeout is rejected.
    params["name"] = "keatest";
    // 2^64 should be greater than INT_MAX
    params["connect-timeout"] = "18446744073709551616";
    ASSERT_NO_THROW_LOG(store_.reset(new MySqlStore(params)));
    EXPECT_THROW(store_->open(), DbInvalidTimeout);
}

/// @brief Tests opening and closing MySqlStore
TEST_F(MySqlTest, open) {
    // Construct the store_
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest";
    params["password"] = "keatest";
    ASSERT_NO_THROW_LOG(store_.reset(new MySqlStore(params)));

    // Check the type is mysql
    EXPECT_EQ("mysql", store_->getType());

    // Open the database
    ASSERT_NO_THROW_LOG(store_->open());

    // Close does nothing
    EXPECT_NO_THROW_LOG(store_->close());

    // Destructor close the database
    EXPECT_NO_THROW_LOG(store_.reset());
}

/// @brief Tests opening MySqlStore with invalid SSL/TLS
TEST_F(MySqlTest, invalidTls) {
    // Construct the store_
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest_secure";
    params["password"] = "keatest";
    params["cert-file"] = TEST_CA_DIR "/kea-client.crt";
    params["key-file"] = TEST_CA_DIR "/kea-other.key";
    params["trust-anchor"] = TEST_CA_DIR ;
    params["cipher-list"] = "AES";
    ASSERT_NO_THROW_LOG(store_.reset(new MySqlStore(params)));

    // Check the type is mysql
    EXPECT_EQ("mysql", store_->getType());

    // Open the database
    EXPECT_THROW(store_->open(), DbOpenError);
}

/// @brief Tests opening and closing MySqlStore with SSL/TLS
TEST_F(MySqlTest, tls) {
    SKIP_IF(!hasMySQLTls());

    // Construct the store_
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest_secure";
    params["password"] = "keatest";
    // Some MySQL versions require to enforce TCP
    params["host"] = "127.0.0.1";
    params["cert-file"] = TEST_CA_DIR "/kea-client.crt";
    params["key-file"] = TEST_CA_DIR "/kea-client.key";
    params["trust-anchor"] = TEST_CA_DIR ;
    params["cipher-list"] = "AES";
    ASSERT_NO_THROW_LOG(store_.reset(new MySqlStore(params)));

    // Check the type is mysql
    EXPECT_EQ("mysql", store_->getType());

    // Open the database
    ASSERT_NO_THROW_LOG(store_->open());

    // Close does nothing
    EXPECT_NO_THROW_LOG(store_->close());

    // Destructor close the database
    EXPECT_NO_THROW_LOG(store_.reset());
}

/// @brief Check schema version
TEST_F(MySqlTest, version) {
    // Open the store
    openStore();

    // Check version using the API
    std::pair<uint32_t, uint32_t> version;
    EXPECT_NO_THROW_LOG(version = store_->getVersion());
    EXPECT_EQ(MYSQL_SCHEMA_VERSION_MAJOR, version.first);
    EXPECT_EQ(MYSQL_SCHEMA_VERSION_MINOR, version.second);

    // Close the store
    closeStore();

    // Check version using mysql command
    setQuery("SELECT version, minor FROM schema_version");
    setCommand("mysql -N -B --host=localhost --user=keatest "
               "--password=keatest --database=keatest --execute=");
    EXPECT_NO_THROW_LOG(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_FALSE(output.empty());
    EXPECT_EQ(1, output.size());
    ostringstream s;
    s << version.first << "\t" << version.second;
    EXPECT_EQ(s.str(), output[0]);

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("LEGAL_LOG_MYSQL_GET_VERSION "
              "obtaining schema version information");
    EXPECT_TRUE(checkFile());
}

/// @brief Check IDs
///
/// Test introduced with MySQL schema 9.6. The IDs are needed for Percona cluster.
/// Checks that each row has an ID column and that they are sequential.
TEST_F(MySqlTest, IDs) {
    // Open the store
    openStore();

    // Fill the store
    fillStore();

    // Close the store
    closeStore();

    setQuery("SELECT id FROM logs");
    setCommand("mysql -N -B --host=localhost --user=keatest --password=keatest "
               "--database=keatest --execute=");
    EXPECT_NO_THROW_LOG(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_EQ(samples_.size(), output.size());
    // Empirically, it seems that dropping the table doesn't reset the
    // auto-increment ID so we can't set first_id to a fixed value of 1.
    unsigned int const first_id(boost::lexical_cast<unsigned int>(output[0]));
    for (size_t i = 0; i < output.size(); ++i) {
        EXPECT_EQ(to_string(first_id + i), output[i]);
    }
}

/// @brief Check addresses
TEST_F(MySqlTest, addresses) {
    // Open the store
    openStore();

    // Fill the store
    fillStore();

    // Close the store
    closeStore();

    setQuery("SELECT address FROM logs");
    setCommand("mysql -N -B --host=localhost --user=keatest "
               "--password=keatest --database=keatest --execute=");
    EXPECT_NO_THROW_LOG(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_EQ(addresses_.size(), output.size());
    for (size_t i = 0; i < output.size(); ++i) {
        if (addresses_[i].empty()) {
            EXPECT_EQ("NULL", output[i]);
        } else {
            EXPECT_EQ(addresses_[i], output[i]);
        }
    }
}

/// @brief Check log entries
TEST_F(MySqlTest, entries) {
    // Open the store
    openStore();

    // Fill the store
    fillStore();

    // Close the store
    closeStore();

    setQuery("SELECT log FROM logs");
    setCommand("mysql -N -B --host=localhost --user=keatest "
               "--password=keatest --database=keatest --execute=");
    EXPECT_NO_THROW_LOG(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_EQ(samples_.size(), output.size());
    for (size_t i = 0; i < output.size(); ++i) {
        EXPECT_EQ(samples_[i], output[i]);
    }
}

/// @brief Check timestamps
TEST_F(MySqlTest, timestamps) {
    // Open the store
    openStore();

    // Get begin date
    ptime begin_p = second_clock::universal_time();

    // Fill the store
    fillStore();

    // Get end date
    ptime end_p = second_clock::universal_time();
    ASSERT_LE(begin_p, end_p);

    // Close the store
    closeStore();

    setQuery("SELECT UNIX_TIMESTAMP(timestamp) FROM logs");
    setCommand("mysql -N -B --host=localhost --user=keatest "
               "--password=keatest --database=keatest --execute=");
    EXPECT_NO_THROW_LOG(execute());
    EXPECT_EQ(0, getResult());
    vector<string> output;
    EXPECT_TRUE(getOutput(output));
    ASSERT_EQ(samples_.size(), output.size());
    ptime current = begin_p;
    for (size_t i = 0; i < output.size(); ++i) {
        time_t ts = 0;
        ASSERT_NO_THROW_LOG(ts = boost::lexical_cast<time_t>(output[i]));
        ptime ts_p = from_time_t(static_cast<time_t>(ts));
        EXPECT_LE(current, ts_p);
        current = ts_p;
    }
    EXPECT_LE(current, end_p);
}

/// @brief Check oversized address
TEST_F(MySqlTest, oversized) {
    // Open the store
    openStore();

    // Check what happen with an oversized address
    string address("2001:0db8:0001:0002:0123:4567:89ab:cdef/128!");
    EXPECT_THROW(store_->writeln("oversized address", address),
                 DbOperationError);
}

class MySqlLegalLogDbLostCallbackTest : public LegalLogDbLostCallbackTest {
public:

    /// @brief Constructor.
    MySqlLegalLogDbLostCallbackTest() {
        LegalLogMgrFactory::delAllBackends();
        io_service_->poll();
    }

    /// @brief Destructor.
    virtual ~MySqlLegalLogDbLostCallbackTest() {
        LegalLogMgrFactory::delAllBackends();
        io_service_->poll();
    }

    /// @brief Prepares the class for a test.
    ///
    /// Invoked by gtest prior test entry, we create the
    /// appropriate schema and create a basic DB manager to
    /// wipe out any prior instance
    virtual void SetUp() {
        // Ensure we have the proper schema with no transient data.
        createMySQLSchema();
    }

    /// @brief Pre-text exit clean up
    ///
    /// Invoked by gtest upon test exit, we destroy the schema
    /// we created.
    virtual void TearDown() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        destroyMySQLSchema();
    }

    /// @brief Method which returns the back end specific connection
    /// string
    virtual std::string validConnectString() {
        return (validMySQLConnectionString());
    }

    /// @brief Method which returns invalid back end specific connection
    /// string
    virtual std::string invalidConnectString() {
        return (connectionString(MYSQL_VALID_TYPE, INVALID_NAME, VALID_HOST,
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

    /// @brief Initializer.
    MySqlForensicBackendInit init_;
};

void
MySqlLegalLogDbLostCallbackTest::testRetryOpenDbLostAndRecoveredCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Verify that a MySqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(invalidConnectString());

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());
    params.emplace("retry-on-startup", "true");

    ASSERT_THROW(LegalLogMgrFactory::addBackend(params), DbOpenErrorWithRetry);

    // Verify there is no instance.
    ASSERT_FALSE(LegalLogMgrFactory::instance());

    dbr.reset();

    params = db::DatabaseConnection::parse(validConnectString());
    params.emplace("retry-on-startup", "true");
    LegalLogMgrFactory::setParameters(params);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(LegalLogMgrFactory::instance());
}

void
MySqlLegalLogDbLostCallbackTest::testRetryOpenDbLostAndFailedCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Verify that a MySqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(invalidConnectString());

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());
    params.emplace("retry-on-startup", "true");

    ASSERT_THROW(LegalLogMgrFactory::addBackend(params), DbOpenErrorWithRetry);

    // Verify there is no instance.
    ASSERT_FALSE(LegalLogMgrFactory::instance());

    dbr.reset();

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());
}

void
MySqlLegalLogDbLostCallbackTest::testRetryOpenDbLostAndRecoveredAfterTimeoutCallback() {
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

    // Verify that a MySqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(access);

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());
    params.emplace("retry-on-startup", "true");

    ASSERT_THROW(LegalLogMgrFactory::addBackend(params), DbOpenErrorWithRetry);

    // Verify there is no instance.
    ASSERT_FALSE(LegalLogMgrFactory::instance());

    dbr.reset();

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());

    access = validConnectString();
    access += extra;
    params = db::DatabaseConnection::parse(access);
    params.emplace("retry-on-startup", "true");
    LegalLogMgrFactory::setParameters(params);

    sleep(1);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    sleep(1);

    io_service_->poll();

    // No callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(LegalLogMgrFactory::instance());
}

void
MySqlLegalLogDbLostCallbackTest::testRetryOpenDbLostAndFailedAfterTimeoutCallback() {
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

    // Verify that a MySqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(access);

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());
    params.emplace("retry-on-startup", "true");

    ASSERT_THROW(LegalLogMgrFactory::addBackend(params), DbOpenErrorWithRetry);

    // Verify there is no instance.
    ASSERT_FALSE(LegalLogMgrFactory::instance());

    dbr.reset();

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());

    sleep(1);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());

    sleep(1);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(3, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());
}

void
MySqlLegalLogDbLostCallbackTest::testNoCallbackOnOpenFailure() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&LegalLogDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Verify that a MySqlStore with no database name is rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(invalidConnectString());

    ASSERT_THROW(LegalLogMgrFactory::addBackend(params), DbOpenError);

    io_service_->poll();

    EXPECT_EQ(0, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());
}

void
MySqlLegalLogDbLostCallbackTest::testDbLostAndRecoveredCallback() {
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

    // Verify that a MySqlStore with database name is not rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(validConnectString());

    ASSERT_NO_THROW(LegalLogMgrFactory::addBackend(params));

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ASSERT_NO_THROW_LOG(LegalLogMgrFactory::instance()->writeln("test", "192.2.1.100"));

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(LegalLogMgrFactory::instance()->writeln("test", "192.2.1.101");,
                 DbConnectionUnusable);

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(LegalLogMgrFactory::instance());
}

void
MySqlLegalLogDbLostCallbackTest::testDbLostAndFailedCallback() {
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

    // Verify that a MySqlStore with database name is not rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(validConnectString());

    ASSERT_NO_THROW(LegalLogMgrFactory::addBackend(params));

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ASSERT_NO_THROW_LOG(LegalLogMgrFactory::instance()->writeln("test", "192.2.1.100"));

    params = db::DatabaseConnection::parse(invalidConnectString());
    LegalLogMgrFactory::setParameters(params);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(LegalLogMgrFactory::instance()->writeln("test", "192.2.1.101"),
                 DbConnectionUnusable);

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());
}

void
MySqlLegalLogDbLostCallbackTest::testDbLostAndRecoveredAfterTimeoutCallback() {
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

    // Verify that a MySqlStore with database name is not rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(access);

    ASSERT_NO_THROW(LegalLogMgrFactory::addBackend(params));

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ASSERT_NO_THROW_LOG(LegalLogMgrFactory::instance()->writeln("test", "192.2.1.100"));

    access = invalidConnectString();
    access += extra;
    params = db::DatabaseConnection::parse(access);
    LegalLogMgrFactory::setParameters(params);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(LegalLogMgrFactory::instance()->writeln("test", "192.2.1.101"),
                 DbConnectionUnusable);

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());

    access = validConnectString();
    access += extra;
    params = db::DatabaseConnection::parse(access);
    LegalLogMgrFactory::setParameters(params);

    sleep(1);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    sleep(1);

    io_service_->poll();

    // No callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(LegalLogMgrFactory::instance());
}

void
MySqlLegalLogDbLostCallbackTest::testDbLostAndFailedAfterTimeoutCallback() {
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

    // Verify that a MySqlStore with database name is not rejected.
    DatabaseConnection::ParameterMap params = db::DatabaseConnection::parse(access);

    ASSERT_NO_THROW(LegalLogMgrFactory::addBackend(params));

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ASSERT_NO_THROW_LOG(LegalLogMgrFactory::instance()->writeln("test", "192.2.1.100"));

    access = invalidConnectString();
    access += extra;
    params = db::DatabaseConnection::parse(access);
    LegalLogMgrFactory::setParameters(params);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(LegalLogMgrFactory::instance()->writeln("test", "192.2.1.101"),
                 DbConnectionUnusable);

    ASSERT_TRUE(LegalLogMgrFactory::instance());

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());

    sleep(1);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());

    sleep(1);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(3, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(LegalLogMgrFactory::instance());
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testRetryOpenDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that db lost callback is not invoked on an open failure
TEST_F(MySqlLegalLogDbLostCallbackTest, testNoCallbackOnOpenFailure) {
    MultiThreadingTest mt(false);
    testNoCallbackOnOpenFailure();
}

/// @brief Verifies that db lost callback is not invoked on an open failure
TEST_F(MySqlLegalLogDbLostCallbackTest, testNoCallbackOnOpenFailureMultiThreading) {
    MultiThreadingTest mt(true);
    testNoCallbackOnOpenFailure();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLegalLogDbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedAfterTimeoutCallback();
}

} // end of anonymous namespace
