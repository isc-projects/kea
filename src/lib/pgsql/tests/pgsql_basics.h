// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef TEST_PGSQL_BASICS_H
#define TEST_PGSQL_BASICS_H

#include <config.h>

#include <pgsql/pgsql_connection.h>
#include <pgsql/pgsql_exchange.h>
#include <pgsql/testutils/pgsql_schema.h>
#include <testutils/gtest_utils.h>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <vector>

namespace isc {
namespace db {
namespace test {

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
        TIMESTAMP_COL,  // Used when epoch coming back is GMT (e.g. lease mgr)
        VARCHAR_COL,
        INET4_COL,
        FLOAT_COL,
        JSON_COL,
        MIN_INT_COL,
        MAX_INT_COL,
        INET6_COL,
        LOCALTIME_COL,  // Used when epoch coming back is LOCAL (e.g. CB)
        NUM_BASIC_COLS
    };

    /// @brief Constructor
    ///
    /// Creates the database connection, opens the database, and destroys
    /// the table (if present) and then recreates it.
    PgSqlBasicsTest();

    /// @brief Destructor
    ///
    /// Destroys the table. The database resources are freed and the connection
    /// closed by the destruction of conn_.
    virtual ~PgSqlBasicsTest ();

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
    const std::string& expectedColumnName(int col);

    /// @brief Creates the basics table
    /// Asserts if the creation step fails
    void createSchema();

    /// @brief Destroys the basics table
    /// Asserts if the destruction fails
    void destroySchema();

    /// @brief Executes a SQL statement and tests for an expected outcome
    ///
    /// @param r pointer which will contain the result set returned by the
    /// statement's execution.
    /// @param sql string containing the SQL statement text.  Note that
    /// PostgreSQL supports executing text which contains more than one SQL
    /// statement separated by semicolons.
    /// @param exp_outcome expected status value returned with within the
    /// result set such as PGRES_COMMAND_OK, PGRES_TUPLES_OK.
    /// @param lineno line number from where the call was invoked
    ///
    /// Asserts if the result set status does not equal the expected outcome.
    void runSql(PgSqlResultPtr& r, const std::string& sql, int exp_outcome,
                int lineno);

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
    /// @param lineno line number from where the call was invoked
    ///
    /// Asserts if the result set status does not equal the expected outcome.
    void runPreparedStatement(PgSqlResultPtr& r,
                              PgSqlTaggedStatement& statement,
                              PsqlBindArrayPtr bind_array, int exp_outcome,
                              int lineno);

    /// @brief Fetches all of the rows currently in the table
    ///
    /// Executes a select statement which returns all of the rows in the
    /// basics table, in their order of insertion.   Each row contains all
    /// of the defined columns, in the order they are defined.
    ///
    /// @param r pointer which will contain the result set returned by the
    /// statement's execution.
    /// @param exp_rows expected number of rows fetched. (This can be 0).
    /// @param lineno line number from where the call was invoked
    ///
    /// Asserts if the result set status does not equal the expected outcome.
    void fetchRows(PgSqlResultPtr& r, int exp_rows, int line);

    /// @brief Database connection
    PgSqlConnectionPtr conn_;

    /// @brief List of column names as we expect them to be in fetched rows
    std::vector<std::string> expected_col_names_;
};

// Macros defined to ease passing invocation line number for output tracing
// (Yes I could have used scoped tracing but that's so ugly in code...)
#define RUN_SQL(a,b,c) (runSql(a,b,c, __LINE__))
#define RUN_PREP(a,b,c,d) (runPreparedStatement(a,b,c,d, __LINE__))
#define FETCH_ROWS(a,b) (fetchRows(a,b,__LINE__))
#define WIPE_ROWS(a) (RUN_SQL(a, "DELETE FROM BASICS", PGRES_COMMAND_OK))

}
}
}

#endif
