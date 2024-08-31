// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/testutils/pgsql_generic_backend_unittest.h>
#include <pgsql/testutils/pgsql_schema.h>

using namespace isc::db;
using namespace isc::db::test;

namespace isc {
namespace dhcp {
namespace test {

PgSqlGenericBackendTest::PgSqlGenericBackendTest()
    : GenericBackendTest() {
    createPgSQLSchema();
}

size_t
PgSqlGenericBackendTest::countRows(PgSqlConnection& conn, const std::string& table) {
    // Execute a simple select query on all rows.
    std::string query = "SELECT * FROM " + table;
    PGresult* result = PQexec(conn.conn_, query.c_str());
    if (!result) {
        ADD_FAILURE() << "Query failed and no status returned";
        return (0);
    }

    ExecStatusType status = PQresultStatus(result);
    if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK) {
        ADD_FAILURE() << "The query returned status " << status;
    }

    // Get the number of rows returned.
    // We don't care about the content, just the number of rows.
    unsigned numrows = PQntuples(result);

    // Free the result allocated.
    PQclear(result);

    return (numrows);
}


} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
