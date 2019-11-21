// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <mysql/mysql_connection.h>
#include <mysql/testutils/mysql_schema.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <array>

using namespace isc::db;
using namespace isc::db::test;

namespace {

/// @brief Test fixture class for @c MySqlConnection class.
class MySqlConnectionTest : public ::testing::Test {
public:

    /// @brief Indexes of prepared statements used within the tests.
    enum StatementIndex {
        GET_BY_INT_VALUE,
        DELETE_BY_INT_VALUE,
        INSERT_VALUE,
        NUM_STATEMENTS
    };

    /// @brief Array of tagged MySQL statements.
    typedef std::array<TaggedStatement, NUM_STATEMENTS>
    TaggedStatementArray;

    /// @brief Prepared MySQL statements used in the tests.
    TaggedStatementArray tagged_statements = { {
            { GET_BY_INT_VALUE,
              "SELECT tinyint_value, int_value, bigint_value, string_value,"
              " blob_value, timestamp_value"
              " FROM mysql_connection_test WHERE int_value = ?" },

            { DELETE_BY_INT_VALUE,
              "DELETE FROM mysql_connection_test WHERE int_value = ?" },

            { INSERT_VALUE,
              "INSERT INTO mysql_connection_test (tinyint_value, int_value,"
              "bigint_value, string_value, blob_value, timestamp_value)"
              " VALUES (?, ?, ?, ?, ?, ?)" }
    }
    };


    /// @brief Constructor.
    ///
    /// Re-creates database schema, opens new database connection and creates
    /// prepared statements used in tests. Created schema contains a test
    /// table @c mysql_connection_test which includes 6 columns of various
    /// types.
    MySqlConnectionTest()
        : conn_(DatabaseConnection::parse(validMySQLConnectionString())) {

        try {
            // Open new connection.
            conn_.openDatabase();
            my_bool result = mysql_autocommit(conn_.mysql_, 1);
            if (result != 0) {
                isc_throw(DbOperationError, "failed to set autocommit option "
                          "for test MySQL connection");
            }

            // Create mysql_connection_test table.
            createTestTable();

            // Created prepared statements for basic queries to test table.
            conn_.prepareStatements(tagged_statements.begin(),
                                    tagged_statements.end());

        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }
    }

    /// @brief Destructor
    ///
    /// Removes test table from the database.
    virtual ~MySqlConnectionTest() {
        conn_.rollback();
        dropTestTable();
    }

    /// @brief Creates test table @c mysql_connection_test.
    ///
    /// The new table contains 6 columns of various data types. All of
    /// the columns accept null values.
    void createTestTable() {
        /// @todo TIMESTAMP value lacks sub second precision because
        /// it is supported since MySQL 5.6.4, which is still not a
        /// default version on some OSes. When the subsecond precision
        /// is available on all OSes that Kea supports, the timestamp
        /// column should be turned to TIMESTAMP(6). Until then, it
        /// must remain TIMESTAMP.
        runQuery("CREATE TABLE IF NOT EXISTS mysql_connection_test ("
                 "tinyint_value TINYINT NULL,"
                 "int_value INT NULL,"
                 "bigint_value BIGINT NULL,"
                 "string_value TEXT NULL,"
                 "blob_value BLOB NULL,"
                 "timestamp_value TIMESTAMP NULL"
                 ")");
    }

    /// @brief Drops test table.
    void dropTestTable() {
        runQuery("DROP TABLE IF EXISTS mysql_connection_test");
    }

    /// @brief Runs MySQL query on the opened connection.
    ///
    /// @param sql Query in the textual form.
    void runQuery(const std::string& sql) {
        MYSQL_STMT *stmt = mysql_stmt_init(conn_.mysql_);
        if (stmt == NULL) {
            isc_throw(DbOperationError, "unable to allocate MySQL prepared "
                  "statement structure, reason: " << mysql_error(conn_.mysql_));
        }

        int status = mysql_stmt_prepare(stmt, sql.c_str(), sql.length());
        if (status != 0) {
            isc_throw(DbOperationError, "unable to prepare MySQL statement <"
                      << sql << ">, reason: " << mysql_errno(conn_.mysql_));
        }

        // Execute the prepared statement.
        if (mysql_stmt_execute(stmt) != 0) {
            isc_throw(DbOperationError, "cannot execute MySQL query <"
                  << sql << ">, reason: " << mysql_errno(conn_.mysql_));
        }

        // Discard the statement and its resources
        mysql_stmt_close(stmt);
    }


    /// @brief Tests inserting and retrieving data from the database.
    ///
    /// In this test data carried in the bindings is inserted into the database.
    /// Then this data is retrieved from the database and compared with the
    /// orginal.
    ///
    /// @param in_bindings Collection of bindings encapsulating the data to
    /// be inserted into the database and then retrieved.
    void testInsertSelect(const MySqlBindingCollection& in_bindings) {
        // Expecting 6 bindings because we have 6 columns in our table.
        ASSERT_EQ(6, in_bindings.size());
        // We are going to select by int_value so this value must not be null.
        ASSERT_FALSE(in_bindings[1]->amNull());

        // Store data in the database.
        ASSERT_NO_THROW(conn_.insertQuery(MySqlConnectionTest::INSERT_VALUE,
                                          in_bindings));

        // Create input binding for select query.
        MySqlBindingCollection bindings =
            { MySqlBinding::createInteger<uint32_t>(in_bindings[1]->getInteger<uint32_t>()) };

        // Also, create output (placeholder) bindings for receiving data.
        MySqlBindingCollection out_bindings = {
            MySqlBinding::createInteger<uint8_t>(),
            MySqlBinding::createInteger<uint32_t>(),
            MySqlBinding::createInteger<int64_t>(),
            MySqlBinding::createString(512),
            MySqlBinding::createBlob(512),
            MySqlBinding::createTimestamp()
        };

        // Execute select statement. We expect one row to be returned. For this
        // returned row the lambda provided as 4th argument should be executed.
        ASSERT_NO_THROW(conn_.selectQuery(MySqlConnectionTest::GET_BY_INT_VALUE,
                                          bindings, out_bindings,
                                          [&](MySqlBindingCollection& out_bindings) {

            // Compare received data with input data assuming they are both non-null.

            if (!out_bindings[0]->amNull() && !in_bindings[0]->amNull()) {
                EXPECT_EQ(static_cast<int>(in_bindings[0]->getInteger<uint8_t>()),
                          static_cast<int>(out_bindings[0]->getInteger<uint8_t>()));
            }

            if (!out_bindings[1]->amNull() && !in_bindings[1]->amNull()) {
                EXPECT_EQ(in_bindings[1]->getInteger<uint32_t>(),
                          out_bindings[1]->getInteger<uint32_t>());
            }

            if (!out_bindings[2]->amNull() && !in_bindings[2]->amNull()) {
                EXPECT_EQ(in_bindings[2]->getInteger<int64_t>(),
                          out_bindings[2]->getInteger<int64_t>());
            }

            if (!out_bindings[3]->amNull() && !in_bindings[3]->amNull()) {
                EXPECT_EQ(in_bindings[3]->getString(),
                          out_bindings[3]->getString());
            }

            if (!out_bindings[4]->amNull() && !in_bindings[4]->amNull()) {
                EXPECT_EQ(in_bindings[4]->getBlob(),
                          out_bindings[4]->getBlob());
            }

            if (!out_bindings[5]->amNull() && !in_bindings[5]->amNull()) {
                EXPECT_TRUE(in_bindings[5]->getTimestamp() ==
                            out_bindings[5]->getTimestamp());
            }
        }));

        // Make sure that null values were returned for columns for which null
        // was set.
        ASSERT_EQ(in_bindings.size(), out_bindings.size());
        for (auto i = 0; i < in_bindings.size(); ++i) {
            EXPECT_EQ(in_bindings[i]->amNull(), out_bindings[i]->amNull())
                << "null value test failed for binding #" << i;
        }
    }

    /// @brief Test MySQL connection.
    MySqlConnection conn_;

};

// Test that non-null values of various types can be inserted and retrieved
// from the dataabse.
TEST_F(MySqlConnectionTest, select) {
    std::string blob = "myblob";
    MySqlBindingCollection in_bindings = {
        MySqlBinding::createInteger<uint8_t>(123),
        MySqlBinding::createInteger<uint32_t>(1024),
        MySqlBinding::createInteger<int64_t>(-4096),
        MySqlBinding::createString("shellfish"),
        MySqlBinding::createBlob(blob.begin(), blob.end()),
        /// @todo Change it to microsec_clock once we transition to subsecond
        /// precision.
        MySqlBinding::createTimestamp(boost::posix_time::second_clock::local_time())
    };

    testInsertSelect(in_bindings);
}

// Test that null value can be inserted to a column having numeric type and
// retrieved.
TEST_F(MySqlConnectionTest, selectNullInteger) {
    std::string blob = "myblob";
    MySqlBindingCollection in_bindings = {
        MySqlBinding::createNull(),
        MySqlBinding::createInteger<uint32_t>(1024),
        MySqlBinding::createInteger<int64_t>(-4096),
        MySqlBinding::createString("shellfish"),
        MySqlBinding::createBlob(blob.begin(), blob.end()),
        /// @todo Change it to microsec_clock once we transition to subsecond
        /// precision.
        MySqlBinding::createTimestamp(boost::posix_time::second_clock::local_time())
    };

    testInsertSelect(in_bindings);
}

// Test that null value can be inserted to a column having string type and
// retrieved.
TEST_F(MySqlConnectionTest, selectNullString) {
    std::string blob = "myblob";

    MySqlBindingCollection in_bindings = {
        MySqlBinding::createInteger<uint8_t>(123),
        MySqlBinding::createInteger<uint32_t>(1024),
        MySqlBinding::createInteger<int64_t>(-4096),
        MySqlBinding::createNull(),
        MySqlBinding::createBlob(blob.begin(), blob.end()),
        /// @todo Change it to microsec_clock once we transition to subsecond
        /// precision.
        MySqlBinding::createTimestamp(boost::posix_time::second_clock::local_time())
    };

    testInsertSelect(in_bindings);
}

// Test that null value can be inserted to a column having blob type and
// retrieved.
TEST_F(MySqlConnectionTest, selectNullBlob) {
    MySqlBindingCollection in_bindings = {
        MySqlBinding::createInteger<uint8_t>(123),
        MySqlBinding::createInteger<uint32_t>(1024),
        MySqlBinding::createInteger<int64_t>(-4096),
        MySqlBinding::createString("shellfish"),
        MySqlBinding::createNull(),
        /// @todo Change it to microsec_clock once we transition to subsecond
        /// precision.
        MySqlBinding::createTimestamp(boost::posix_time::second_clock::local_time())
    };

    testInsertSelect(in_bindings);
}

// Test that null value can be inserted to a column having timestamp type and
// retrieved.
TEST_F(MySqlConnectionTest, selectNullTimestamp) {
    std::string blob = "myblob";
    MySqlBindingCollection in_bindings = {
        MySqlBinding::createInteger<uint8_t>(123),
        MySqlBinding::createInteger<uint32_t>(1024),
        MySqlBinding::createInteger<int64_t>(-4096),
        MySqlBinding::createString("shellfish"),
        MySqlBinding::createBlob(blob.begin(), blob.end()),
        MySqlBinding::createNull()
    };

    testInsertSelect(in_bindings);
}

// Test that empty string and empty blob can be inserted to a database.
TEST_F(MySqlConnectionTest, selectEmptyStringBlob) {
    std::string blob = "";
    MySqlBindingCollection in_bindings = {
        MySqlBinding::createInteger<uint8_t>(123),
        MySqlBinding::createInteger<uint32_t>(1024),
        MySqlBinding::createInteger<int64_t>(-4096),
        MySqlBinding::createString(""),
        MySqlBinding::createBlob(blob.begin(), blob.end()),
        /// @todo Change it to microsec_clock once we transition to subsecond
        /// precision.
        MySqlBinding::createTimestamp(boost::posix_time::second_clock::local_time())
    };

    testInsertSelect(in_bindings);
}

// Test that a row can be deleted from the database.
TEST_F(MySqlConnectionTest, deleteByValue) {
    // Insert a row with numeric values.
    MySqlBindingCollection in_bindings = {
        MySqlBinding::createInteger<uint8_t>(123),
        MySqlBinding::createInteger<uint32_t>(1024),
        MySqlBinding::createInteger<int64_t>(-4096),
        MySqlBinding::createNull(),
        MySqlBinding::createNull(),
        MySqlBinding::createNull()
    };
    ASSERT_NO_THROW(conn_.insertQuery(MySqlConnectionTest::INSERT_VALUE,
                                      in_bindings));

    // This variable will be checked to see if the row has been deleted
    // from the database.
    bool deleted = false;

    // Execute delete query but use int_value of non existing row.
    // The row should not be deleted.
    in_bindings = { MySqlBinding::createInteger<uint32_t>(1) };
    ASSERT_NO_THROW(deleted = conn_.updateDeleteQuery(MySqlConnectionTest::DELETE_BY_INT_VALUE,
                                                      in_bindings));
    ASSERT_FALSE(deleted);

    // This time use the correct value.
    in_bindings = { MySqlBinding::createInteger<uint32_t>(1024) };
    ASSERT_NO_THROW(deleted = conn_.updateDeleteQuery(MySqlConnectionTest::DELETE_BY_INT_VALUE,
                                                      in_bindings));
    // The row should have been deleted.
    ASSERT_TRUE(deleted);

    // Let's confirm that it has been deleted by issuing a select query.
    MySqlBindingCollection out_bindings = {
        MySqlBinding::createInteger<uint8_t>(),
        MySqlBinding::createInteger<uint32_t>(),
        MySqlBinding::createInteger<int64_t>(),
        MySqlBinding::createString(512),
        MySqlBinding::createBlob(512),
        MySqlBinding::createTimestamp()
    };

    ASSERT_NO_THROW(conn_.selectQuery(MySqlConnectionTest::GET_BY_INT_VALUE,
                                      in_bindings, out_bindings,
                                      [&deleted](MySqlBindingCollection&) {
        // This will be executed if the row is returned as a result of
        // select query. We expect that this is not executed.
        deleted = false;
    }));
    // Make sure that select query returned nothing.
    EXPECT_TRUE(deleted);
}

/// @brief Test fixture class for @c MySqlConnection class methods.
class MySqlSchemaTest : public ::testing::Test {
public:
    /// @brief Constructor.
    MySqlSchemaTest() {
        // Ensure we have the proper schema.
        createMySQLSchema();
    }

    /// @brief Destructor.
    virtual ~MySqlSchemaTest() {
        destroyMySQLSchema();
    }
};

/// @brief Check that getVersion() returns the expected version.
TEST_F(MySqlSchemaTest, checkVersion) {
    // Check version
    auto parameters = DatabaseConnection::parse(validMySQLConnectionString());
    std::pair<uint32_t, uint32_t> version;
    ASSERT_NO_THROW(version = MySqlConnection::getVersion(parameters));
    EXPECT_EQ(MYSQL_SCHEMA_VERSION_MAJOR, version.first);
    EXPECT_EQ(MYSQL_SCHEMA_VERSION_MINOR, version.second);
}

}
