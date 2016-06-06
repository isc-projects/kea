// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_CQL_SCHEMA_H
#define TEST_CQL_SCHEMA_H

#include <config.h>
#include <dhcpsrv/testutils/schema.h>
#include <string>

namespace isc {
namespace dhcp {
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
/// @param show_err flag which governs whether or not stderr is suppressed.
void destroyCqlSchema(bool show_err = false);

/// @brief Create the CQL Schema
///
/// Submits the current schema creation script:
///
///  <TEST_ADMIN_SCRIPTS_DIR>/cql/dhcpdb_create.cql
///
/// to the unit test CQL database. If the script fails, the invoking test
/// will fail. The output of stderr is suppressed unless the parameter,
/// show_err is true.
///
/// @param show_err flag which governs whether or not stderr is suppressed.
void createCqlSchema(bool show_err = false);

/// @brief Run a CQL SQL script against the CQL unit test database
///
/// Submits the given SQL script to CQL via cqlsh CLI. The output of
/// stderr is suppressed unless the parameter, show_err is true.  The is done
/// to suppress warnings that might otherwise make test output needlessly
/// noisy.  A gtest assertion occurs if the script fails to execute.
///
/// @param path - path (if not blank) of the script to execute
/// @param script_name - file name of the path to execute
/// @param show_err flag which governs whether or not stderr is suppressed.
void runCqlScript(const std::string& path, const std::string& script_name,
                    bool show_err);

};
};
};

#endif
