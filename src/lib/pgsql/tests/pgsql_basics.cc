// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <config.h>

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

PgSqlBasicsTest::PgSqlBasicsTest() : expected_col_names_(NUM_BASIC_COLS) {
    // Create database connection parameter list
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest";
    params["password"] = "keatest";

    // Create and open the database connection
    conn_.reset(new PgSqlConnection(params));
    conn_->openDatabase();

    // Create the list of expected column names
    expected_col_names_[ID_COL] = "id";
    expected_col_names_[BOOL_COL] = "bool_col";
    expected_col_names_[BYTEA_COL] = "bytea_col";
    expected_col_names_[BIGINT_COL] = "bigint_col";
    expected_col_names_[SMALLINT_COL] = "smallint_col";
    expected_col_names_[INT_COL] = "int_col";
    expected_col_names_[TEXT_COL] = "text_col";
    expected_col_names_[TIMESTAMP_COL] = "timestamp_col";
    expected_col_names_[VARCHAR_COL] = "varchar_col";
    expected_col_names_[INET4_COL] = "inet4_col";
    expected_col_names_[FLOAT_COL] = "float_col";
    expected_col_names_[JSON_COL] = "json_col";
    expected_col_names_[MIN_INT_COL] = "min_int_col";
    expected_col_names_[MAX_INT_COL] = "max_int_col";
    expected_col_names_[INET6_COL] = "inet6_col";
    expected_col_names_[LOCALTIME_COL] = "localtime_col";

    destroySchema();
    createSchema();
}

PgSqlBasicsTest::~PgSqlBasicsTest () {
    destroySchema();
}

const std::string&
PgSqlBasicsTest::expectedColumnName(int col) {
    if (col < 0 || col >= NUM_BASIC_COLS) {
        isc_throw(BadValue,
                  "definedColumnName: invalid column value" << col);
    }

    return (expected_col_names_[col]);
}

void
PgSqlBasicsTest::createSchema() {
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
        "    varchar_col VARCHAR(255), "
        "    inet4_col INET, "
        "    float_col FLOAT, "
        "    json_col JSON,"
        "    min_int_col INT, "
        "    max_int_col INT, "
        "    inet6_col INET, "
        "    localtime_col TIMESTAMP WITH TIME ZONE "
        "); ";

    PgSqlResult r(PQexec(*conn_, sql));
    ASSERT_EQ(PQresultStatus(r), PGRES_COMMAND_OK)
              << " create basics table failed: " << PQerrorMessage(*conn_);
}

void
PgSqlBasicsTest::destroySchema() {
    if (conn_) {
        PgSqlResult r(PQexec(*conn_, "DROP TABLE IF EXISTS basics;"));
        ASSERT_EQ(PQresultStatus(r), PGRES_COMMAND_OK)
                  << " drop basics table failed: " << PQerrorMessage(*conn_);
    }
}

void
PgSqlBasicsTest::runSql(PgSqlResultPtr& r, const std::string& sql,
                        int exp_outcome, int lineno) {
    r.reset(new PgSqlResult(PQexec(*conn_, sql.c_str())));
    ASSERT_EQ(PQresultStatus(*r), exp_outcome)
              << " runSql at line: " << lineno << " failed, sql:[" << sql
              << "]\n reason: " << PQerrorMessage(*conn_);
}

void
PgSqlBasicsTest::runPreparedStatement(PgSqlResultPtr& r,
                                      PgSqlTaggedStatement& statement,
                                      PsqlBindArrayPtr bind_array,
                                      int exp_outcome, int lineno) {
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

void
PgSqlBasicsTest::fetchRows(PgSqlResultPtr& r, int exp_rows, int line) {
    std::string sql =
        "SELECT"
        "   id, bool_col, bytea_col, bigint_col, smallint_col, "
        "   int_col, text_col,"
        "   extract(epoch from timestamp_col)::bigint as timestamp_col,"
        "   varchar_col, inet4_col, float_col, json_col,"
        "   min_int_col, max_int_col, inet6_col,"
        "   (extract(epoch from localtime_col) + extract(timezone from localtime_col))::bigint as localtime_col"
        " FROM basics";

    runSql(r, sql, PGRES_TUPLES_OK, line);
    ASSERT_EQ(r->getRows(), exp_rows) << "fetch at line: " << line
              << " wrong row count, expected: " << exp_rows
              << " , have: " << r->getRows();
}
