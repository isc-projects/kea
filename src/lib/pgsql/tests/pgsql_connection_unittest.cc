// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/db_exceptions.h>
#include <pgsql/pgsql_connection.h>
#include <pgsql/pgsql_exchange.h>
#include <pgsql/testutils/pgsql_schema.h>
#include <pgsql/tests/pgsql_basics.h>
#include <testutils/gtest_utils.h>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <vector>

using namespace isc;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::util;

namespace {

// A small extension of PgSqlBasicsTest that instantiates the actual Kea schema.
// Those tests tend to be a bit heavy (especially with the CB and its tables),
// so please consider adding your tests in PgSqlBasicsTest, unless you really need
// the full schema.
class PgSqlSchemaTest: public PgSqlBasicsTest {
public:
    PgSqlSchemaTest() : PgSqlBasicsTest() {
        destroySchema(); // We don't need this fake schema with just "basics" table.

        // Create the actual full Kea schema.
        isc::db::test::createPgSQLSchema(true, true);
    }

    virtual ~PgSqlSchemaTest() {
        // Clean up after ourselves.
        isc::db::test::destroyPgSQLSchema(true, true);
    }
};

/// @brief Checks if the schema version is really as expected.
TEST_F(PgSqlSchemaTest, schemaVersion) {

    PgSqlResultPtr r;
    std::string sql = "SELECT version, minor FROM schema_version";
    RUN_SQL(r, sql, PGRES_TUPLES_OK);
    // There should be one row with 7,0 returned or whatever the latest schema is.
    ASSERT_EQ(r->getRows(), 1) << "failed to check schema version, expected 1 row, have: "
        << r->getRows();

    int value = 0;
    // Get row 0, column 0 (i.e. version field)
    ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, 0, 0));
    ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, 0, 0, value));
    EXPECT_EQ(value, PGSQL_SCHEMA_VERSION_MAJOR)
        << "invalid schema version reported, major expected " << PGSQL_SCHEMA_VERSION_MAJOR
        << ", actual:" << value;

    // Get row 0, column 1 (i.e. minor field)
    ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, 0, 1));
    ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, 0, 1, value));
    EXPECT_EQ(value, PGSQL_SCHEMA_VERSION_MINOR)
        << "invalid schema version reported, minor expected " << PGSQL_SCHEMA_VERSION_MINOR
        << ", actual:" << value;

}

/// @brief Test fixture for exercising higher order PgSqlConnection functions
/// selectQuery, insertQuery, updateDeleteQuery.  These tests only use two of
/// the columns in the BASICS table: int_col and text_col.  Inserting rows with
/// varying types and values are tested above.  These tests focus on the higher
/// order function mechanics.
class PgSqlConnectionTest : public PgSqlBasicsTest {
public:

    /// @brief Indexes of prepared statements used within the tests.
    enum StatementIndex {
        GET_BY_INT_VALUE,
        GET_BY_INT_RANGE,
        DELETE_BY_INT_RANGE,
        INSERT_VALUE,
        UPDATE_BY_INT_VALUE,
        GET_ALL_ROWS,
        DELETE_ALL_ROWS,
        NUM_STATEMENTS
    };

    /// @brief Array of tagged PgSql statements.
    typedef std::array<PgSqlTaggedStatement, NUM_STATEMENTS> TaggedStatementArray;

    /// @brief Prepared PgSql statements used in the tests.
    TaggedStatementArray tagged_statements = {{
        { 1, { OID_INT4 }, "GET_BY_INT_VALUE",
          "SELECT int_col, text_col"
          " FROM basics WHERE int_col = $1" },

        { 2, { OID_INT4, OID_INT4 }, "GET_BY_INT_RANGE",
          "SELECT int_col, text_col"
          " FROM basics WHERE int_col >= $1 and int_col <= $2" },

        { 2, { OID_INT4, OID_INT4 }, "DEL_BY_INT_RANGE",
          "DELETE FROM basics WHERE int_col >= $1 and int_col <= $2" },

        { 2, { OID_INT4, OID_TEXT }, "INSERT_INT_TEXT",
          "INSERT INTO basics (int_col,text_col)"
          " VALUES ($1, $2)" },

        { 2, { OID_INT4, OID_TEXT }, "UPDATE_BY_INT_VALUE",
          "UPDATE basics SET text_col = $2"
          " WHERE int_col = $1" },

        { 0, { OID_NONE }, "GET_ALL_ROWS",
          "SELECT int_col, text_col FROM basics" },

        { 0, { OID_NONE }, "DELETE_ALL_ROWS",
          "DELETE FROM basics" }
    }};

    /// @brief Structure for holding data values describing a single
    /// row. These tests only use two of the columns in the BASICS table:
    /// int_col and text_col.  Inserting rows with varying types and values
    /// are tested above.  These tests focus on the higher order mechanics.
    struct TestRow {
        int int_col;
        std::string text_col;

        bool operator==(const TestRow& other) const {
            return (int_col == other.int_col &&
                    text_col == other.text_col);
        }
    };

    /// @brief Defines a set of test rows.
    typedef std::vector<TestRow> TestRowSet;

    /// @brief Constructor.
    PgSqlConnectionTest() : PgSqlBasicsTest() {};

    /// @brief Destructor.
    virtual ~PgSqlConnectionTest() {
        if (conn_->isTransactionStarted()) {
            conn_->rollback();
        }
    };

    /// @brief SetUp function which prepares the tagged statements.
    virtual void SetUp() {
        ASSERT_NO_THROW_LOG(conn_->prepareStatements(tagged_statements.begin(),
                                                     tagged_statements.end()));
    }

    /// @brief Tests inserting data into the database.
    ///
    /// @param insert_rows Collection of rows of data to insert. Note that
    /// each row is inserted as a separate statement execution.
    void testInsert(const TestRowSet& insert_rows) {
        for (auto row : insert_rows ) {
            // Set the insert parameters based on the current insert row.
            PsqlBindArray in_bindings;
            in_bindings.add(row.int_col);
            in_bindings.add(row.text_col);

            // Insert the row into the database.
            conn_->insertQuery(tagged_statements[INSERT_VALUE], in_bindings);
        }
    }

    /// @brief Tests fetching data using PgSqlConnection::selectQuery()
    ///
    /// Selects rows from the BASICS table whose int_col value falls within
    /// an inclusive range.
    ///
    /// @param expected_rows Collection of rows of data that we expect to be
    /// fetched. Note the rows should be in the order you expect them to be
    /// returned from the database.
    /// @param begin_int beginning of the range to include.
    /// @param end_int end fo the range to include.
    void testSelect(const TestRowSet& expected_rows, const int begin_int, const int end_int) {
        // Set the where clause parameters to the desired range values.
        PsqlBindArray in_bindings;
        in_bindings.add(begin_int);
        in_bindings.add(end_int);

        // Row set that will receive the fetched rows.
        TestRowSet fetched_rows;

        // Run the select.  The row consumption lambda should populate
        // fetched_rows based on the the result set returned by the select.
        conn_->selectQuery(tagged_statements[GET_BY_INT_RANGE], in_bindings,
                           [&](PgSqlResult& r, int row) {
            TestRow fetched_row;
            if (row >= expected_rows.size()) {
                // We have too many rows.
                isc_throw(Unexpected, "row index exceeded expected row count of "
                          << expected_rows.size());
            }

            // First column should be int_col and not NULL.
            if (PgSqlExchange::isColumnNull(r, row, 0)) {
                isc_throw(Unexpected, "first column is null!");
            }

            // Fetch the int_col value.
            PgSqlExchange::getColumnValue(r, row, 0, fetched_row.int_col);

            // Second column should be text and not NULL.
            if (PgSqlExchange::isColumnNull(r, row, 1)) {
                isc_throw(Unexpected, "second column is null!");
            }

            // Fetch the text_col value.
            PgSqlExchange::getColumnValue(r, row, 1, fetched_row.text_col);

            // Add the fetched row into set of fetched rows.
            fetched_rows.push_back(fetched_row);
        });

        // Make sure fetched rows match the expected rows.
        ASSERT_EQ(fetched_rows, expected_rows);
    }

    /// @brief Tests updating data using PgSqlConnection::updateDeleteQuery()
    ///
    /// In this test, the input data is a set of rows that describe
    /// which rows in the database to update and how. For each row
    /// in the set we find the record in the database with matching
    /// int_col value and replace its text_col value with the the
    /// text value from the input the row.
    ///
    /// @param update_rows Collection of rows of data to update.
    void testUpdate(const TestRowSet& update_rows) {
        size_t update_count = 0;
        for (auto row : update_rows ) {
            // Set the text value and where clause parameters based on the
            // this row's values.
            PsqlBindArray in_bindings;
            in_bindings.add(row.int_col);
            in_bindings.add(row.text_col);

            // Update the database.
            update_count += conn_->updateDeleteQuery(tagged_statements[UPDATE_BY_INT_VALUE],
                                                     in_bindings);
        }

        // Number of rows updated should match rows we passed in.
        ASSERT_EQ(update_count, update_rows.size());
    }

    /// @brief Tests deleting data using PgSqlConnection::updateDeleteQuery()
    ///
    /// Deletes rows from the BASICS table whose int_col value falls within
    /// an inclusive range.
    ///
    /// @param begin_int beginning of the range to include.
    /// @param end_int end of the range to include.
    /// @param expected_delete_count number of rows of data we expect to be
    /// deleted.
    void testDelete(const int begin_int, const int end_int, size_t expected_delete_count) {
        // Set the where clause parameters to the desired range values.
        PsqlBindArray in_bindings;
        in_bindings.add(begin_int);
        in_bindings.add(end_int);

        // Execute the delete statement.
        size_t delete_count = 0;
        delete_count = conn_->updateDeleteQuery(tagged_statements[DELETE_BY_INT_RANGE],
                                                in_bindings);

        // Verify the number of records deleted is as expected.
        ASSERT_EQ(delete_count, expected_delete_count);
    }
};

/// @brief Verifies basics of input parameter sanity checking and statement
/// execution enforced by executePreparedStatement.  Higher order tests
/// verify actual data CRUD results.
TEST_F(PgSqlConnectionTest, executePreparedStatement) {

    // Executing with no parameters when they are required should throw.
    // First we'll omit the bindings (defaults to empty).
    PgSqlResultPtr r;
    ASSERT_THROW_MSG(r = conn_->executePreparedStatement(tagged_statements[INSERT_VALUE]),
                     InvalidOperation,
                     "executePreparedStatement: expected: 2 parameters, given: 0,"
                     " statement: INSERT_INT_TEXT, SQL: INSERT INTO basics "
                     "(int_col,text_col) VALUES ($1, $2)");

    // Now we'll pass in an empty array.
    PsqlBindArray in_bindings;
    ASSERT_THROW_MSG(r = conn_->executePreparedStatement(tagged_statements[INSERT_VALUE],
                                                         in_bindings),
                     InvalidOperation,
                     "executePreparedStatement: expected: 2 parameters, given: 0,"
                     " statement: INSERT_INT_TEXT, SQL: INSERT INTO basics "
                     "(int_col,text_col) VALUES ($1, $2)");

    // Executing without parameters when none are expected should be fine.
    // First we'll simply omit the array.
    ASSERT_NO_THROW(r = conn_->executePreparedStatement(tagged_statements[GET_ALL_ROWS]));

    // Now with an empty array.
    ASSERT_NO_THROW(r = conn_->executePreparedStatement(tagged_statements[GET_ALL_ROWS], in_bindings));

    // Executing with parameters when none are required should throw.
    in_bindings.add(1);
    in_bindings.add(2);
    ASSERT_THROW_MSG(r = conn_->executePreparedStatement(tagged_statements[GET_ALL_ROWS],
                                                         in_bindings),
                     InvalidOperation,
                     "executePreparedStatement: expected: 0 parameters, given: 2,"
                     " statement: GET_ALL_ROWS, SQL: SELECT int_col, text_col FROM basics");

    // Executing with the correct number of parameters should work.
    ASSERT_NO_THROW(r = conn_->executePreparedStatement(tagged_statements[GET_BY_INT_RANGE],
                                                        in_bindings));

    // Executing with too many parameters should fail.
    in_bindings.add(3);
    ASSERT_THROW_MSG(r = conn_->executePreparedStatement(tagged_statements[GET_BY_INT_RANGE],
                                                         in_bindings),
                     InvalidOperation,
                     "executePreparedStatement: expected: 2 parameters, given: 3,"
                     " statement: GET_BY_INT_RANGE, SQL: SELECT int_col, text_col"
                     " FROM basics WHERE int_col >= $1 and int_col <= $2");
}

/// @brief Verify that we can insert rows with
/// PgSqlConnection::insertQuery() and fetch
/// them using PgSqlConnection::selectQuery().
TEST_F(PgSqlConnectionTest, insertSelectTest) {

    // Define the list of rows we want to insert.
    TestRowSet insert_rows = {
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
    };

    // Insert the rows.
    ASSERT_NO_THROW_LOG(testInsert(insert_rows));

    // Make sure we can fetch a single row.
    ASSERT_NO_THROW_LOG(testSelect(TestRowSet({{ 8, "eight" }}), 8, 8));

    // Make sure we can fetch all the rows.
    ASSERT_NO_THROW_LOG(testSelect(insert_rows, 7, 9));
}

/// @brief Verify that we can update rows with
/// PgSqlConnection::updateDeleteQuery()
TEST_F(PgSqlConnectionTest, updateTest) {

    // Define the list of rows we want to insert.
    TestRowSet insert_rows = {
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
    };

    // Insert the rows.
    ASSERT_NO_THROW_LOG(testInsert(insert_rows));

    // Define the list of updates.
    TestRowSet update_rows = {
        { 8, "ate" },
        { 9, "mine" }
    };

    // Update the rows.
    ASSERT_NO_THROW_LOG(testUpdate(update_rows));

    // Fetch the updated rows.
    ASSERT_NO_THROW_LOG(testSelect(update_rows, 8, 9));
}

/// @brief Verify that we can delete rows with
/// PgSqlConnection::updateDeleteQuery()
TEST_F(PgSqlConnectionTest, deleteTest) {

    // Define the list of rows we want to insert.
    TestRowSet insert_rows = {
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
    };

    // Insert the rows.
    ASSERT_NO_THROW_LOG(testInsert(insert_rows));

    // Fetch the all rows.
    ASSERT_NO_THROW_LOG(testSelect(insert_rows, 0, 10));

    // Delete rows 7 and 8.
    ASSERT_NO_THROW_LOG(testDelete(7, 8, 2));

    // Fetch the all rows.
    ASSERT_NO_THROW_LOG(testSelect(TestRowSet({{6, "six"}, {9, "nine"}}), 0, 10));
}

// Verifies that transaction nesting and operations: start, commit,
// and rollback work correctly.
TEST_F(PgSqlConnectionTest, transactions) {
    ASSERT_FALSE(conn_->isTransactionStarted());

    // Two inserts within a transaction and successful commit.
    TestRowSet two_rows = {{1, "one"}, {2, "two"}};
    conn_->startTransaction();
    ASSERT_TRUE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testInsert(two_rows));
    conn_->commit();

    // Should not be in a transaction and we should have both
    // rows we inserted.
    ASSERT_FALSE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testSelect(two_rows, 0, 10));

    // Add third row but roll back the transaction. We should still have
    // two rows in the table.
    conn_->startTransaction();
    ASSERT_TRUE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testInsert({{ 3, "three"}}));
    conn_->rollback();

    // We should not be in a transaction and should still have
    // only the first two rows.
    ASSERT_FALSE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testSelect(two_rows, 0, 10));

    // Nested transaction. The inner transaction should be ignored and the outer
    // transaction rolled back. We should have only the original two rows in the
    // database.
    conn_->startTransaction();
    EXPECT_TRUE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testInsert({{ 3, "three"}}));

    conn_->startTransaction();
    EXPECT_TRUE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testInsert({{ 4, "four"}}));

    // First commit should do nothing other than decrement
    // the transaction ref count.
    conn_->commit();
    ASSERT_TRUE(conn_->isTransactionStarted());

    // Rollback should end the transaction without committing changes.
    conn_->rollback();
    ASSERT_FALSE(conn_->isTransactionStarted());

    // We should still have only the first two rows.
    ASSERT_NO_THROW_LOG(testSelect(two_rows, 0, 10));

    // Nested transaction. The inner transaction is rolled back but this should
    // be ignored because nested transactions are not supported. We should
    // have two new rows.

    // Insert five row.
    conn_->startTransaction();
    ASSERT_TRUE(conn_->isTransactionStarted());
    TestRow row_five({ 5, "five" });
    ASSERT_NO_THROW_LOG(testInsert(TestRowSet({ row_five })));
    two_rows.push_back(row_five);

    // Insert six row.
    conn_->startTransaction();
    ASSERT_TRUE(conn_->isTransactionStarted());
    TestRow row_six({ 6, "six" });
    ASSERT_NO_THROW_LOG(testInsert(TestRowSet({ row_six })));
    two_rows.push_back(row_six);

    // Rollback should do nothing other than decrement the
    // reference count.
    conn_->rollback();
    EXPECT_TRUE(conn_->isTransactionStarted());

    // Commit should complete the transaction and commit the inserts.
    conn_->commit();
    EXPECT_FALSE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testSelect(two_rows, 0, 10));

    // Committing or rolling back a not started transaction is a coding error.
    EXPECT_THROW(conn_->commit(), isc::Unexpected);
    EXPECT_THROW(conn_->rollback(), isc::Unexpected);
}

// Verifies that savepoints operate correctly.
TEST_F(PgSqlConnectionTest, savepoints) {
    // We want to trigger DuplicateEntry errors so let's
    // add a unique constraint to the table.
    ASSERT_NO_THROW(conn_->executeSQL("ALTER TABLE basics ADD CONSTRAINT"
                                      " unique_int_col UNIQUE (int_col);"));
    // Verify we are not in a transaction.
    ASSERT_FALSE(conn_->isTransactionStarted());

    // Creating or rollback to savepoints outside of transactions
    // should throw.
    ASSERT_THROW_MSG(conn_->createSavepoint("rubbish"), InvalidOperation,
                     "no transaction, cannot create savepoint: rubbish");
    ASSERT_THROW_MSG(conn_->rollbackToSavepoint("rubbish"), InvalidOperation,
                     "no transaction, cannot rollback to savepoint: rubbish");

    // Test that we can create and rollback to a savepoint, then
    // committing only the pre savepoint work.
    TestRowSet first_row = {{1, "one"}};
    ASSERT_NO_THROW_LOG(conn_->startTransaction());
    ASSERT_TRUE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testInsert(first_row));

    // Create a savepoint.
    ASSERT_NO_THROW_LOG(conn_->createSavepoint("sp_one"));

    // Insert a second row, without committing it.
    TestRowSet second_row = {{2, "two"}};
    ASSERT_NO_THROW_LOG(testInsert(second_row));

    // Rollback to the savepoint.
    ASSERT_NO_THROW_LOG(conn_->rollbackToSavepoint("sp_one"));

    // Commit the transaction.
    conn_->commit();

    // We should not be in a transaction but we should
    // only have the first row.
    ASSERT_FALSE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testSelect(first_row, 0, 10));

    // Now we'll test that we can create and rollback to a
    // savepoint after Postgresql aborts an insert due to
    // duplicate key error.  We should still be able to
    // commit the pre-savepoint and post rollback work.
    ASSERT_NO_THROW_LOG(conn_->startTransaction());
    ASSERT_TRUE(conn_->isTransactionStarted());
    ASSERT_NO_THROW_LOG(testInsert(second_row));

    // Create a savepoint.
    ASSERT_NO_THROW_LOG(conn_->createSavepoint("sp_two"));

    // Attempt to insert a duplicate first row.
    ASSERT_THROW(testInsert(first_row), DuplicateEntry);

    // Rollback to the savepoint.
    ASSERT_NO_THROW_LOG(conn_->rollbackToSavepoint("sp_two"));

    // Now insert a third row.
    TestRowSet third_row = {{3, "three"}};
    ASSERT_NO_THROW_LOG(testInsert(third_row));

    // Commit the transaction.
    conn_->commit();

    // We should not be in a transaction and we should
    // two rows.
    ASSERT_FALSE(conn_->isTransactionStarted());
    TestRowSet three_rows{{1, "one"}, {2, "two"}, {3, "three"}};
    ASSERT_NO_THROW_LOG(testSelect(three_rows, 0, 10));
}
}; // namespace
