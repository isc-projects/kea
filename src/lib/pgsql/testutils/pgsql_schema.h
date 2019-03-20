// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Clear the unit test database
///
/// In order to reduce test execution time, this function
/// defaults to first attempting to delete transient data
/// from the database by calling @c wipePgSQLData.  If that
/// function fails it will then attempt to destroy the database
/// schema by running the SQL script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/pgsql/dhcpdb_drop.pgsql
///
/// The default behavior of wiping the data only may be overridden
/// in one of two ways:
///
/// -# Setting the force parameter to true
/// -# Defining the environment variable:
///    KEA_TEST_DB_WIPE_DATA_ONLY="false"
///
/// @param show_err flag which governs whether or not stderr is suppressed.
/// @param force if true, the function will skip deleting the data and
/// destroy the schema.
void destroyPgSQLSchema(bool show_err = false, bool force = false);

/// @brief Create the unit test PgSQL Schema
///
/// Ensures the unit test database is empty and version-correct.
/// Unless,the force parameter is true, it will first attempt
/// to wipe the data from the database by calling @c wipePgSQLData.
/// If this call succeeds the function returns, otherwise it will
/// call @c destroyPgSQLSchema to forcibly remove the existing
/// schema and then submits the SQL script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/pgsql/dhcpdb_create.pgsql
///
/// to the unit test PgSQL database.
///
/// The default behavior of wiping the data only may be overridden
/// in one of two ways:
///
/// -# Setting the force parameter to true
/// -# Defining the environment variable:
///    KEA_TEST_DB_WIPE_DATA_ONLY="false"
///
/// @param show_err flag which governs whether or not stderr is suppressed.
/// @param force flag when true, the function will recreate the database
/// schema.
void createPgSQLSchema(bool show_err = false, bool force = false);

/// @brief Attempts to wipe data from the PgSQL unit test database
///
/// Runs the shell script
///
///  <TEST_ADMIN_SCRIPTS_DIR>/pgsql/wipe_data.sh
///
/// This will fail if there is no schema, if the existing schema
/// version is incorrect (i.e. does not match PG_SCHEMA_VERSION_MAJOR
/// and PG_SCHEMA_VERSION_MINOR), or a SQL error occurs.  Otherwise,
/// the script is should delete all transient data, leaving intact
/// reference tables.
///
/// @param show_err flag which governs whether or not stderr is suppressed.
bool wipePgSQLData(bool show_err = false);

/// @brief Run a PgSQL SQL script against the Postgresql unit test database
///
/// Submits the given SQL script to Postgresql via psql CLI. The output of
/// stderr is suppressed unless the parameter, show_err is true.  The is done
/// to suppress warnings that might otherwise make test output needlessly
/// noisy.  An exception is thrown if the script fails to execute.
///
/// @param path - path (if not blank) of the script to execute
/// @param script_name - file name of the path to execute
/// @param show_err flag which governs whether or not stderr is suppressed.
/// @throw Unexpected when the script returns an error.
void runPgSQLScript(const std::string& path, const std::string& script_name,
                    bool show_err);

};
};
};

#endif
