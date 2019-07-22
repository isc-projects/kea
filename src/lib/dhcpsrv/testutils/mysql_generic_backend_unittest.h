// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_GENERIC_BACKEND_UNITTEST_H
#define MYSQL_GENERIC_BACKEND_UNITTEST_H

#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <mysql/mysql_connection.h>


namespace isc {
namespace dhcp {
namespace test {

/// @brief Generic test fixture class with utility functions for testing
/// MySQL database backends.
class MySqlGenericBackendTest : public GenericBackendTest {
public:

    /// @brief Constructor.
    MySqlGenericBackendTest();

    /// @brief Counts rows in a selected table in MySQL database.
    ///
    /// One of the common applications of this method is to check whether the
    /// expected number of rows were deleted from the specified table. In
    /// relational databases, a deletion of a raw in one table causes deletion of
    /// rows in other tables, e.g. via cascaded delete or triggers. This method
    /// can be used to verify that the deletion took place in the dependent
    /// tables.
    ///
    /// @param conn MySql connection to be used for the query.
    /// @param table Table name.
    /// @return Number of rows in the specified table.
    size_t countRows(db::MySqlConnection& conn, const std::string& table) const;
};

}
}
}

#endif
