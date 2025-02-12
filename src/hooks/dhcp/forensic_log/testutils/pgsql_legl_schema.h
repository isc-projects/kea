// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_PGSQL_LEGL_SCHEMA_H
#define TEST_PGSQL_LEGL_SCHEMA_H

#include <pgsql/testutils/pgsql_schema.h>

namespace isc {
namespace legal_log {
namespace test {

/// @brief Clear everything from the database
///
/// Submits the current schema drop script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/pgsql/legldb_drop.pgsql
///
/// to the unit test Postgresql database. If the script fails, the invoking
/// test will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param show_err flag which governs whether or not stderr is suppressed.
void destroyPgSQLLegLSchema(bool show_err = false) {
    isc::db::test::runPgSQLScript(DATABASE_SCRIPTS_DIR,
                                  "pgsql/legldb_drop.pgsql",
                                  show_err);
}

/// @brief Create the Postgresql Schema
///
/// Submits the current schema creation script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/pgsql/legldb_create.pgsql
///
/// to the unit test Postgresql database. If the script fails, the invoking
/// test will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param show_err flag which governs whether or not stderr is suppressed.
void createPgSQLLegLSchema(bool show_err = false) {
    isc::db::test::runPgSQLScript(DATABASE_SCRIPTS_DIR,
                                  "pgsql/legldb_create.pgsql",
                                  show_err);
}

};
};
};

#endif
