// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_CQL_SCHEMA_H
#define TEST_CQL_SCHEMA_H

#include <config.h>

#include <database/testutils/schema.h>

#include <string>

namespace isc {
namespace db {
namespace test {

extern const char* CQL_VALID_TYPE;

/// Return valid connection string
///
/// @return valid CQL connection string.
std::string validCqlConnectionString();

/// @brief Clear everything from the database
///
/// Submits the current schema drop script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/cql/dhcpdb_drop.cql
///
/// to the unit test CQL database. If the script fails, the invoking test
/// will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param force_wipe forces wipe of the database, even if
/// KEA_TEST_CASSANDRA_WIPE is set.
/// @param show_err flag which governs whether or not stderr is suppressed.
void destroyCqlSchema(bool force_wipe, bool show_err = true);

/// @brief Create the CQL Schema
///
/// Submits the current schema creation script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/cql/dhcpdb_create.cql
///
/// and the configuration upgrade script:
///
/// <TEST_ADMIN_SCRIPTS_DIR>/cql/configdb_create.cql
///
/// to the unit test CQL database. If the script fails, the invoking test
/// will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param force_wipe forces wipe of the database, even if
/// KEA_TEST_CASSANDRA_WIPE is set.
/// @param show_err flag which governs whether or not stderr is suppressed.
void createCqlSchema(bool force_wipe, bool show_err = true);

/// @brief Run a CQL script against the CQL unit test database
///
/// Submits the given CQL script to CQL via cqlsh CLI. The output of
/// stderr is suppressed unless the parameter, show_err is true. The is done
/// to suppress warnings that might otherwise make test output needlessly
/// noisy. A gtest assertion occurs if the script fails to execute.
///
/// @param path - path (if not blank) of the script to execute
/// @param script_name - file name of the path to execute
/// @param show_err flag which governs whether or not stderr is suppressed.
void runCqlScript(const std::string& path, const std::string& script_name, bool show_err);

/// @brief Returns status if the soft-wipe is enabled or not.
///
/// In some deployments (In case of Tomek's dev system) Cassandra tests take
/// a very long time to execute. This was traced back to slow table/indexes
/// creation/deletion. With full wipe and recreation of all structures, it
/// took over 60 seconds for each test to execute. To avoid this problem, a
/// feature called soft-wipe has been implemented. If enabled, it does not
/// remove the structures, just the data from essential tables. To enable
/// it set KEA_TEST_CASSANDRA_WIPE environment variable to 'soft'. Make sure
/// that the database schema is set up properly before running in soft-wipe
/// mode.
///
/// For example to use soft-wipe mode, you can:
///
/// $ cqlsh -u keatest -p keatest -k keatest
///         -f src/share/database/scripts/cql/dhcpdb_create.cql
/// $ export KEA_TEST_CASSANDRA_WIPE=soft
/// $ cd src/lib/dhcpsrv
/// $ make -j9
/// $ tests/libdhcpsrv_unittests --gtest_filter=CqlLeaseMgrTest.*
///
/// @return true if soft-wipe is enabled, false otherwise
bool softWipeEnabled();

}  // namespace test
}  // namespace db
}  // namespace isc

#endif  // TEST_CQL_SCHEMA_H
