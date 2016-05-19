// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_DSCSQL_SCHEMA_H
#define TEST_DSCSQL_SCHEMA_H

#include <config.h>
#include <dhcpsrv/testutils/schema.h>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

extern const char* DSCSQL_VALID_TYPE;

/// Return valid connection string
///
/// @return valid DSCSQL connection string.
std::string validDSCSQLConnectionString();

/// @brief Clear everything from the database
///
/// Submits the current schema drop script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/dscsql/dhcpdb_drop.cql
///
/// to the unit test DSCSQL database. If the script fails, the invoking test
/// will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param show_err flag which governs whether or not stderr is suppressed.
void destroyDSCSQLSchema(bool show_err = false);

/// @brief Create the DSCSQL Schema
///
/// Submits the current schema creation script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/dscsql/dhcpdb_create.cql
///
/// to the unit test DSCSQL database. If the script fails, the invoking test
/// will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param show_err flag which governs whether or not stderr is suppressed.
void createDSCSQLSchema(bool show_err = false);

/// @brief Run a DSCSQL SQL script against the DSCSQL unit test database
///
/// Submits the given SQL script to DSCSQL via cqlsh CLI. The output of
/// stderr is suppressed unless the parameter, show_err is true.  The is done
/// to suppress warnings that might otherwise make test output needlessly
/// noisy.  A gtest assertion occurs if the script fails to execute.
///
/// @param path - path (if not blank) of the script to execute
/// @param script_name - file name of the path to execute
/// @param show_err flag which governs whether or not stderr is suppressed.
void runDSCSQLScript(const std::string& path, const std::string& script_name,
                    bool show_err);

};
};
};

#endif
