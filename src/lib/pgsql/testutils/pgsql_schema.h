// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_PGSQL_SCHEMA_H
#define TEST_PGSQL_SCHEMA_H

#include <config.h>
#include <database/testutils/schema.h>
#include <string>

namespace isc {
namespace db {
namespace test {

extern const char* PGSQL_VALID_TYPE;

/// Return valid connection string
///
/// @return valid PgSQL connection string.
std::string validPgSQLConnectionString();

/// @brief Clear everything from the database
///
/// Submits the current schema drop script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/pgsql/dhcpdb_drop.pgsql
///
/// to the unit test Postgresql database. If the script fails, the invoking
/// test will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param show_err flag which governs whether or not stderr is suppressed.
void destroyPgSQLSchema(bool show_err = false);

/// @brief Create the Postgresql Schema
///
/// Submits the current schema creation script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/pgsql/dhcpdb_create.pgsql
///
/// to the unit test Postgresql database. If the script fails, the invoking
/// test will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param show_err flag which governs whether or not stderr is suppressed.
void createPgSQLSchema(bool show_err = false);

/// @brief Run a PgSQL SQL script against the Postgresql unit test database
///
/// Submits the given SQL script to Postgresql via psql CLI. The output of
/// stderr is suppressed unless the parameter, show_err is true.  The is done
/// to suppress warnings that might otherwise make test output needlessly
/// noisy.  A gtest assertion occurs if the script fails to execute.
///
/// @param path - path (if not blank) of the script to execute
/// @param script_name - file name of the path to execute
/// @param show_err flag which governs whether or not stderr is suppressed.
void runPgSQLScript(const std::string& path, const std::string& script_name,
                    bool show_err);

};
};
};

#endif
