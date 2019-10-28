// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
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
MySqlGenericBackendTest::countRows(MySqlConnection& conn, const std::string& table) const {
    MySqlHolder& holderHandle = conn.handle();

    // Execute a simple select query on all rows.
    std::string query = "SELECT * FROM " + table;
    auto status = mysql_query(holderHandle, query.c_str());
    if (status != 0) {
        ADD_FAILURE() << "Query failed: " << mysql_error(holderHandle);
        return (0);
    }

    // Get the number of rows returned and free the result.
    MYSQL_RES * res = mysql_store_result(holderHandle);
    unsigned numrows = static_cast<unsigned>(mysql_num_rows(res));
    mysql_free_result(res);

    return (numrows);
}


} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
