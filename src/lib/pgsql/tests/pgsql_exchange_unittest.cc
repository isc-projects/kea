// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <pgsql/pgsql_connection.h>
#include <pgsql/pgsql_exchange.h>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <vector>

using namespace isc;
using namespace isc::db;

namespace {

/// @brief Verifies the ability to add various data types to
/// the bind array.
TEST(PsqlBindArray, addDataTest) {

    PsqlBindArray b;

    // Declare a vector to add. Vectors are not currently duplicated
    // So they will go out of scope, unless caller ensures it.
    std::vector<uint8_t> bytes;
    for (int i = 0; i < 10; i++) {
        bytes.push_back(i+1);
    }

    // Declare a string
    std::string not_temp_str("just a string");

    // Now add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        // Add a const char*
        b.add("booya!");

        // Add the non temporary string
        b.add(not_temp_str);

        // Add a temporary string
        b.addTempString("walah walah washington");

        // Add a one byte int
        uint8_t small_int = 25;
        b.add(small_int);

        // Add a four byte int
        int reg_int = 376;
        b.add(reg_int);

        // Add a eight byte unsigned int
        uint64_t big_int = 48786749032;
        b.add(big_int);

        // Add boolean true and false
        b.add((bool)(1));
        b.add((bool)(0));

        // Add IP addresses
        b.add(isc::asiolink::IOAddress("192.2.15.34"));
        b.add(isc::asiolink::IOAddress("3001::1"));

        // Add the vector
        b.add(bytes);
    }

    // We've left bind scope, everything should be intact.
    std::string expected =
        "0 : \"booya!\"\n"
        "1 : \"just a string\"\n"
        "2 : \"walah walah washington\"\n"
        "3 : \"25\"\n"
        "4 : \"376\"\n"
        "5 : \"48786749032\"\n"
        "6 : \"TRUE\"\n"
        "7 : \"FALSE\"\n"
        "8 : \"3221360418\"\n"
        "9 : \"3001::1\"\n"
        "10 : 0x0102030405060708090a\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Defines a pointer to a PgSqlConnection
typedef boost::shared_ptr<PgSqlConnection> PgSqlConnectionPtr;
/// @brief Defines a pointer to a PgSqlResult
typedef boost::shared_ptr<PgSqlResult> PgSqlResultPtr;

/// @brief Fixture for exercising basic PostgreSQL operations and data types
///
/// This class is intended to be used to verify basic operations and to
/// verify that each PostgreSQL  data type currently used by Kea, can be
/// correctly written to and read from PostgreSQL.  Rather than use tables
/// that belong to Kea the schema proper,  it creates its own. Currently it
/// consists of a single table, called "basics" which contains one column for
/// each of the supported data types.
///
/// It creates the schema during construction, deletes it upon destruction, and
/// provides functions for executing SQL statements, executing prepared
/// statements, fetching all rows in the table, and deleting all the rows in
/// the table.
class PgSqlBasicsTest : public ::testing::Test {
public:
    /// @brief Column index for each column
    enum BasicColIndex {
        ID_COL,
        BOOL_COL,
        BYTEA_COL,
        BIGINT_COL,
        SMALLINT_COL,
        INT_COL,
        TEXT_COL,
        TIMESTAMP_COL,
        VARCHAR_COL,
        NUM_BASIC_COLS
    };

    /// @brief Constructor
    ///
    /// Creates the database connection, opens the database, and destroys
    /// the table (if present) and then recreates it.
    PgSqlBasicsTest() : expectedColNames_(NUM_BASIC_COLS) {
        // Create database connection parameter list
        DatabaseConnection::ParameterMap params;
        params["name"] = "keatest";
        params["user"] = "keatest";
        params["password"] = "keatest";

        // Create and open the database connection
        conn_.reset(new PgSqlConnection(params));
        conn_->openDatabase();

        // Create the list of expected column names
        expectedColNames_[ID_COL] = "id";
        expectedColNames_[BOOL_COL] = "bool_col";
        expectedColNames_[BYTEA_COL] = "bytea_col";
        expectedColNames_[BIGINT_COL] = "bigint_col";
        expectedColNames_[SMALLINT_COL] = "smallint_col";
        expectedColNames_[INT_COL] = "int_col";
        expectedColNames_[TEXT_COL] = "text_col";
        expectedColNames_[TIMESTAMP_COL] = "timestamp_col";
        expectedColNames_[VARCHAR_COL] = "varchar_col";

        destroySchema();
        createSchema();
    }

    /// @brief Destructor
    ///
    /// Destroys the table. The database resources are freed and the connection
    /// closed by the destruction of conn_.
    virtual ~PgSqlBasicsTest () {
        destroySchema();
    }

    /// @brief Gets the expected name of the column for a given column index
    ///
    /// Returns the name of column as we expect it to be when the column is
    /// fetched from the database.
    ///
    /// @param col index of the desired column
    ///
    /// @return string containing the column name
    ///
    /// @throw BadValue if the index is out of range
    const std::string& expectedColumnName(int col) {
        if (col < 0 || col >= NUM_BASIC_COLS) {
            isc_throw(BadValue,
                      "definedColumnName: invalid column value" << col);
        }

        return (expectedColNames_[col]);
    }

    /// @brief Creates the basics table
    /// Asserts if the creation step fails
    void createSchema() {
        // One column for OID type, plus an auto-increment
        const char* sql =
            "CREATE TABLE basics ( "
            "    id SERIAL PRIMARY KEY NOT NULL, "
            "    bool_col BOOLEAN, "
            "    bytea_col BYTEA, "
            "    bigint_col  BIGINT, "
            "    smallint_col  SMALLINT, "
            "    int_col INT, "
            "    text_col TEXT, "
            "    timestamp_col TIMESTAMP WITH TIME ZONE, "
            "    varchar_col VARCHAR(255) "
            "); ";

        PgSqlResult r(PQexec(*conn_, sql));
        ASSERT_EQ(PQresultStatus(r), PGRES_COMMAND_OK)
                 << " create basics table failed: " << PQerrorMessage(*conn_);
    }

    /// @brief Destroys the basics table
    /// Asserts if the destruction fails
    void destroySchema() {
        if (conn_) {
            PgSqlResult r(PQexec(*conn_, "DROP TABLE IF EXISTS basics;"));
            ASSERT_EQ(PQresultStatus(r), PGRES_COMMAND_OK)
                 << " drop basics table failed: " << PQerrorMessage(*conn_);
        }
    }

    /// @brief Executes a SQL statement and tests for an expected outcome
    ///
    /// @param r pointer which will contain the result set returned by the
    /// statement's execution.
    /// @param sql string containing the SQL statement text.  Note that
    /// PostgreSQL supports executing text which contains more than one SQL
    /// statement separated by semicolons.
    /// @param exp_outcome expected status value returned with within the
    /// result set such as PGRES_COMMAND_OK, PGRES_TUPLES_OK.
    /// @lineno line number from where the call was invoked
    ///
    /// Asserts if the result set status does not equal the expected outcome.
    void runSql(PgSqlResultPtr& r, const std::string& sql, int exp_outcome,
                int lineno) {
        r.reset(new PgSqlResult(PQexec(*conn_, sql.c_str())));
        ASSERT_EQ(PQresultStatus(*r), exp_outcome)
                  << " runSql at line: " << lineno << " failed, sql:[" << sql
                  << "]\n reason: " << PQerrorMessage(*conn_);
    }

    /// @brief Executes a SQL statement and tests for an expected outcome
    ///
    /// @param r pointer which will contain the result set returned by the
    /// statement's execution.
    /// @param statement statement descriptor of the prepared statement
    /// to execute.
    /// @param bind_array bind array containing the input values to submit
    /// along with the statement
    /// @param exp_outcome expected status value returned with within the
    /// result set such as PGRES_COMMAND_OK, PGRES_TUPLES_OK.
    /// @lineno line number from where the call was invoked
    ///
    /// Asserts if the result set status does not equal the expected outcome.
    void runPreparedStatement(PgSqlResultPtr& r,
                              PgSqlTaggedStatement& statement,
                              PsqlBindArrayPtr bind_array, int exp_outcome,
                              int lineno) {
        r.reset(new PgSqlResult(PQexecPrepared(*conn_, statement.name,
                                statement.nbparams,
                                &bind_array->values_[0],
                                &bind_array->lengths_[0],
                                &bind_array->formats_[0], 0)));
        ASSERT_EQ(PQresultStatus(*r), exp_outcome)
                  << " runPreparedStatement at line: " << lineno
                  << " statement name:[" << statement.name
                  << "]\n reason: " << PQerrorMessage(*conn_);
    }

    /// @brief Fetches all of the rows currently in the table
    ///
    /// Executes a select statement which returns all of the rows in the
    /// basics table, in their order of insertion.   Each row contains all
    /// of the defined columns, in the order they are defined.
    ///
    /// @param r pointer which will contain the result set returned by the
    /// statement's execution.
    /// @param exp_rows expected number of rows fetched. (This can be 0).
    /// @lineno line number from where the call was invoked
    ///
    /// Asserts if the result set status does not equal the expected outcome.
    void fetchRows(PgSqlResultPtr& r, int exp_rows, int line) {
        std::string sql =
            "SELECT"
            "   id, bool_col, bytea_col, bigint_col, smallint_col, "
            "   int_col, text_col,"
            "   extract(epoch from timestamp_col)::bigint as timestamp_col,"
            "   varchar_col FROM basics";

        runSql(r, sql, PGRES_TUPLES_OK, line);
        ASSERT_EQ(r->getRows(), exp_rows) << "fetch at line: " << line
                  << " wrong row count, expected: " << exp_rows
                  << " , have: " << r->getRows();

    }

    /// @brief Database connection
    PgSqlConnectionPtr conn_;

    /// @brief List of column names as we expect them to be in fetched rows
    std::vector<std::string> expectedColNames_;
};

// Macros defined to ease passing invocation line number for output tracing
// (Yes I could have used scoped tracing but that's so ugly in code...)
#define RUN_SQL(a,b,c) (runSql(a,b,c, __LINE__))
#define RUN_PREP(a,b,c,d) (runPreparedStatement(a,b,c,d, __LINE__))
#define FETCH_ROWS(a,b) (fetchRows(a,b,__LINE__))
#define WIPE_ROWS(a) (RUN_SQL(a, "DELETE FROM BASICS", PGRES_COMMAND_OK))

/// @brief Verifies that PgResultSet row and column meta-data is correct
TEST_F(PgSqlBasicsTest, rowColumnBasics) {
    // We fetch the table contents, which at this point should be no rows.
    PgSqlResultPtr r;
    FETCH_ROWS(r, 0);

    // Column meta-data is determined by the select statement and is
    // present whether or not any rows were returned.
    EXPECT_EQ(r->getCols(), NUM_BASIC_COLS);

    // Negative indexes should be out of range.  We test negative values
    // as PostgreSQL functions accept column values as type int.
    EXPECT_THROW(r->colCheck(-1), DbOperationError);

    // Iterate over the column indexes verifying:
    // 1. the column is valid
    // 2. the result set column name matches the expected column name
    for (int i = 0; i < NUM_BASIC_COLS; i++) {
        EXPECT_NO_THROW(r->colCheck(i));
        EXPECT_EQ(r->getColumnLabel(i), expectedColumnName(i));
    }

    // Verify above range column value is detected.
    EXPECT_THROW(r->colCheck(NUM_BASIC_COLS), DbOperationError);

    // Verify the fetching a column label for out of range columns
    // do NOT throw.
    std::string label;
    ASSERT_NO_THROW(label = r->getColumnLabel(-1));
    EXPECT_EQ(label, "Unknown column:-1");
    ASSERT_NO_THROW(label = r->getColumnLabel(NUM_BASIC_COLS));
    std::ostringstream os;
    os << "Unknown column:" << NUM_BASIC_COLS;
    EXPECT_EQ(label, os.str());

    // Verify row count and checking. With an empty result set all values of
    // row are invalid.
    EXPECT_EQ(r->getRows(), 0);
    EXPECT_THROW(r->rowCheck(-1), DbOperationError);
    EXPECT_THROW(r->rowCheck(0), DbOperationError);
    EXPECT_THROW(r->rowCheck(1), DbOperationError);

    // Verify Row-column check will always fail with an empty result set.
    EXPECT_THROW(r->rowColCheck(-1, 1), DbOperationError);
    EXPECT_THROW(r->rowColCheck(0, 1), DbOperationError);
    EXPECT_THROW(r->rowColCheck(1, 1), DbOperationError);

    // Insert three minimal rows.  We don't really care about column content
    // for this test.
    int num_rows = 3;
    for (int i = 0; i < num_rows; i++) {
        RUN_SQL(r, "INSERT INTO basics (bool_col) VALUES ('t')",
                PGRES_COMMAND_OK);
    }

    // Fetch the newly created rows.
    FETCH_ROWS(r, num_rows);

    // Verify we row count and checking
    EXPECT_EQ(r->getRows(), num_rows);
    EXPECT_THROW(r->rowCheck(-1), DbOperationError);

    // Iterate over the row count, verifying that expected rows are valid
    for (int i = 0; i < num_rows; i++) {
        EXPECT_NO_THROW(r->rowCheck(i));
        EXPECT_NO_THROW(r->rowColCheck(i, 0));
    }

    // Verify an above range row is detected.
    EXPECT_THROW(r->rowCheck(num_rows), DbOperationError);
}

/// @brief Verify that we can read and write BOOL columns
TEST_F(PgSqlBasicsTest, boolTest) {
    // Create a prepared statement for inserting bool_col
    const char* st_name = "bool_insert";
    PgSqlTaggedStatement statement[] = {
     {1, { OID_BOOL }, st_name,
      "INSERT INTO BASICS (bool_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    bool bools[] = { true, false };
    PsqlBindArrayPtr bind_array(new PsqlBindArray());
    PgSqlResultPtr r;

    // Insert bool rows
    for (int i = 0; i < 2; ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(bools[i]);
        RUN_PREP(r,statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, 2);

    // Verify the fetched bool values are what we expect.
    bool fetched_bool;
    int row = 0;
    for ( ; row  < 2; ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, BOOL_COL));

        // Fetch and verify the column value
        fetched_bool = !bools[row];
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, BOOL_COL,
                                                      fetched_bool));
        EXPECT_EQ(fetched_bool, bools[row]);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, 1, fetched_bool),
                 DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL boolean
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();

    // Run the insert with the bind array.
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, 1));
}

/// @brief Verify that we can read and write BYTEA columns
TEST_F(PgSqlBasicsTest, byteaTest) {
    const char* st_name = "bytea_insert";
    PgSqlTaggedStatement statement[] = {
     {1, { OID_BYTEA }, st_name,
      "INSERT INTO BASICS (bytea_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    const uint8_t bytes[] = {
        0x01, 0x02, 0x03, 0x04
    };
    std::vector<uint8_t> vbytes(bytes, bytes + sizeof(bytes));

    // Verify we can insert bytea from a vector
    PsqlBindArrayPtr bind_array(new PsqlBindArray());
    PgSqlResultPtr r;
    bind_array->add(vbytes);
    RUN_PREP(r,statement[0], bind_array, PGRES_COMMAND_OK);

    // Verify we can insert bytea from a buffer.
    bind_array.reset(new PsqlBindArray());
    bind_array->add(bytes, sizeof(bytes));
    RUN_PREP(r,statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows.
    int num_rows = 2;
    FETCH_ROWS(r, num_rows);

    uint8_t fetched_bytes[sizeof(bytes)];
    size_t byte_count;
    int row = 0;
    for ( ; row < num_rows; ++row) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, BYTEA_COL));

        // Extract the data into a correctly sized buffer
        memset(fetched_bytes, 0, sizeof(fetched_bytes));
        ASSERT_NO_THROW(PgSqlExchange::convertFromBytea(*r, row, BYTEA_COL,
                                                        fetched_bytes,
                                                        sizeof(fetched_bytes),
                                                        byte_count));

        // Verify the data is correct
        ASSERT_EQ(byte_count, sizeof(bytes));
        for (int i = 0; i < sizeof(bytes); i++) {
            ASSERT_EQ(bytes[i], fetched_bytes[i]);
        }
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::convertFromBytea(*r, row, BYTEA_COL,
                                                 fetched_bytes,
                                                 sizeof(fetched_bytes),
                                                 byte_count), DbOperationError);

    // Verify that too small of a buffer throws
    ASSERT_THROW(PgSqlExchange::convertFromBytea(*r, 0, BYTEA_COL,
                                                 fetched_bytes,
                                                 sizeof(fetched_bytes) - 1,
                                                 byte_count), DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL for a bytea column
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull(PsqlBindArray::BINARY_FMT);
    RUN_PREP(r,statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, BYTEA_COL));

    // Verify that fetching a NULL bytea, returns 0 byte count
    ASSERT_NO_THROW(PgSqlExchange::convertFromBytea(*r, 0, BYTEA_COL,
                                                    fetched_bytes,
                                                    sizeof(fetched_bytes),
                                                    byte_count));
    EXPECT_EQ(byte_count, 0);
}

/// @brief Verify that we can read and write BIGINT columns
TEST_F(PgSqlBasicsTest, bigIntTest) {
    // Create a prepared statement for inserting BIGINT
    const char* st_name = "bigint_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_INT8 }, st_name,
          "INSERT INTO BASICS (bigint_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<int64_t> ints;
    ints.push_back(-1);
    ints.push_back(0);
    ints.push_back(0x7fffffffffffffff);
    ints.push_back(0xffffffffffffffff);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < ints.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(ints[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, ints.size());

    // Iterate over the rows, verifying each value against its reference
    int64_t fetched_int;
    int row = 0;
    for ( ; row  < ints.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, BIGINT_COL));

        // Fetch and verify the column value
        fetched_int = 777;
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, BIGINT_COL,
                                                      fetched_int));
        EXPECT_EQ(fetched_int, ints[row]);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, BIGINT_COL,
                                               fetched_int), DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, BIGINT_COL));
}

/// @brief Verify that we can read and write SMALLINT columns
TEST_F(PgSqlBasicsTest, smallIntTest) {
    // Create a prepared statement for inserting a SMALLINT
    const char* st_name = "smallint_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_INT2 }, st_name,
          "INSERT INTO BASICS (smallint_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<int16_t>ints;
    ints.push_back(-1);
    ints.push_back(0);
    ints.push_back(0x7fff);
    ints.push_back(0xffff);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < ints.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(ints[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, ints.size());

    // Iterate over the rows, verifying each value against its reference
    int16_t fetched_int;
    int row = 0;
    for ( ; row  < ints.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, SMALLINT_COL));

        // Fetch and verify the column value
        fetched_int = 777;
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, SMALLINT_COL,
                                                      fetched_int));
        EXPECT_EQ(fetched_int, ints[row]);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, SMALLINT_COL,
                                               fetched_int),
                 DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, SMALLINT_COL));
}

/// @brief Verify that we can read and write INT columns
TEST_F(PgSqlBasicsTest, intTest) {
    // Create a prepared statement for inserting an  INT
    const char* st_name = "int_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_INT4 }, st_name,
          "INSERT INTO BASICS (int_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<int32_t> ints;
    ints.push_back(-1);
    ints.push_back(0);
    ints.push_back(0x7fffffff);
    ints.push_back(0xffffffff);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < ints.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(ints[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, ints.size());

    // Iterate over the rows, verifying each value against its reference
    int32_t fetched_int;
    int row = 0;
    for ( ; row  < ints.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, INT_COL));

        // Fetch and verify the column value
        fetched_int = 777;
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, INT_COL,
                                                      fetched_int));
        EXPECT_EQ(fetched_int, ints[row]);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, INT_COL, fetched_int),
                 DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, INT_COL));
}

/// @brief Verify that we can read and write TEXT columns
TEST_F(PgSqlBasicsTest, textTest) {
    // Create a prepared statement for inserting TEXT
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TEXT }, "text_insert",
          "INSERT INTO BASICS (text_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Our reference string.
    std::string ref_string = "This is a text string";

    // Insert the reference from std::string
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    bind_array.reset(new PsqlBindArray());
    bind_array->add(ref_string);
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Insert the reference from a buffer
    bind_array.reset(new PsqlBindArray());
    bind_array->add(ref_string.c_str());
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, 2);

    // Iterate over the rows, verifying the value against the reference
    std::string fetched_str;
    int row = 0;
    for ( ; row  < 2; ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, TEXT_COL));

        // Fetch and verify the column value
        fetched_str = "";
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, TEXT_COL,
                                                      fetched_str));
        EXPECT_EQ(fetched_str, ref_string);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, TEXT_COL, fetched_str),
                 DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, TEXT_COL));
}

/// @brief Verify that we can read and write VARCHAR columns
TEST_F(PgSqlBasicsTest, varcharTest) {
    // Create a prepared statement for inserting a VARCHAR
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_VARCHAR }, "varchar_insert",
          "INSERT INTO BASICS (varchar_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Our reference string.
    std::string ref_string = "This is a varchar string";

    // Insert the reference from std::string
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    bind_array.reset(new PsqlBindArray());
    bind_array->add(ref_string);
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Insert the reference from a buffer
    bind_array.reset(new PsqlBindArray());
    bind_array->add(ref_string.c_str());
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, 2);

    // Iterate over the rows, verifying the value against the reference
    std::string fetched_str;
    int row = 0;
    for ( ; row  < 2; ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, VARCHAR_COL));

        // Fetch and verify the column value
        fetched_str = "";
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, VARCHAR_COL,
                                                      fetched_str));
        EXPECT_EQ(fetched_str, ref_string);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, VARCHAR_COL,
                                               fetched_str), DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, VARCHAR_COL));
}

/// @brief Verify that we can read and write TIMESTAMP columns
TEST_F(PgSqlBasicsTest, timeStampTest) {
    // Create a prepared statement for inserting a TIMESTAMP
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TIMESTAMP }, "timestamp_insert",
          "INSERT INTO BASICS (timestamp_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our list of reference times
    time_t now;
    time(&now);
    std::vector<time_t> times;
    times.push_back(now);
    times.push_back(DatabaseConnection::MAX_DB_TIME);
    // Note on a 32-bit OS this value is really -1. PosgreSQL will store it
    // and return it intact.
    times.push_back(0xFFFFFFFF);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    std::string time_str;
    for (int i = 0; i < times.size(); ++i) {
        // Timestamps are inserted as strings so convert them first
        ASSERT_NO_THROW(time_str =
                        PgSqlExchange::convertToDatabaseTime(times[i]));

        // Add it to the bind array and insert it
        bind_array.reset(new PsqlBindArray());
        bind_array->add(time_str);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Insert a row with ref time plus one day
    times.push_back(now + 24*3600);
    ASSERT_NO_THROW(time_str =
                    PgSqlExchange::convertToDatabaseTime(times[0], 24*3600));

    bind_array.reset(new PsqlBindArray());
    bind_array->add(time_str);
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, times.size());

    // Iterate over the rows, verifying the value against its reference
    std::string fetched_str;
    int row = 0;
    for ( ; row  < times.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, TIMESTAMP_COL));

        // Fetch and verify the column value
        fetched_str = "";
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, TIMESTAMP_COL,
                                                      fetched_str));

        time_t fetched_time;
        ASSERT_NO_THROW(fetched_time =
                        PgSqlExchange::convertFromDatabaseTime(fetched_str));
        EXPECT_EQ(fetched_time, times[row]) << " row: " << row;
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, TIMESTAMP_COL,
                                               fetched_str), DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, TIMESTAMP_COL));

    // Verify exceeding max time throws
    ASSERT_THROW(PgSqlExchange::convertToDatabaseTime(times[0],
                                                      DatabaseConnection::
                                                      MAX_DB_TIME), BadValue);
}

}; // namespace
