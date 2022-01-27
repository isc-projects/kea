// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/testutils/mysql_generic_backend_unittest.h>

using namespace isc::db;

namespace isc {
namespace dhcp {
namespace test {

MySqlGenericBackendTest::MySqlGenericBackendTest()
    : GenericBackendTest() {
}

size_t
MySqlGenericBackendTest::countRows(MySqlConnection& conn, const std::string& table) {
    // Execute a simple select query on all rows.
    std::string query = "SELECT * FROM " + table;
    auto status = mysql_query(conn.mysql_, query.c_str());
    if (status != 0) {
        ADD_FAILURE() << "Query failed: " << mysql_error(conn.mysql_);
        return (0);
    }

    // Get the number of rows returned.
    MYSQL_RES* res = mysql_store_result(conn.mysql_);
    unsigned numrows = static_cast<unsigned>(mysql_num_rows(res));

    // Free the result allocated.
    mysql_free_result(res);

    return (numrows);
}


} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
