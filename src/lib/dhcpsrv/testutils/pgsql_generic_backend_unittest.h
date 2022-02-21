// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PGSQL_GENERIC_BACKEND_UNITTEST_H
#define PGSQL_GENERIC_BACKEND_UNITTEST_H

#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <pgsql/pgsql_connection.h>


namespace isc {
namespace dhcp {
namespace test {

/// @brief Generic test fixture class with utility functions for testing
/// PgSQL database backends.
class PgSqlGenericBackendTest : public GenericBackendTest {
public:

    /// @brief Constructor.
    PgSqlGenericBackendTest();

    /// @brief Counts rows in a selected table in PgSQL database.
    ///
    /// One of the common applications of this method is to check whether the
    /// expected number of rows were deleted from the specified table. In
    /// relational databases, a deletion of a raw in one table causes deletion of
    /// rows in other tables, e.g. via cascaded delete or triggers. This method
    /// can be used to verify that the deletion took place in the dependent
    /// tables.
    ///
    /// @param conn PgSql connection to be used for the query.
    /// @param table Table name.
    /// @return Number of rows in the specified table.
    static size_t countRows(db::PgSqlConnection& conn, const std::string& table);
};

}
}
}

#endif
