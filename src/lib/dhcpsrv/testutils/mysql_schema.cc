// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <string>
#include <mysql.h>
#include <dhcpsrv/mysql_connection.h>
#include <dhcpsrv/testutils/mysql_schema.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

namespace isc {
namespace dhcp {
namespace test {

const char* MYSQL_VALID_TYPE = "type=mysql";

string
validMySQLConnectionString() {
    return (connectionString(MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST,
                             VALID_USER, VALID_PASSWORD));
}

void destroyMySQLSchema() {
    MySqlHolder mysql;
    // @todo - replace this with call to drop script once it exists
    const char* destroy_statement[] = {
        // Turning off referential integrity checks ensures tables get dropped
        "SET SESSION FOREIGN_KEY_CHECKS = 0",
        "DROP TABLE IF EXISTS lease4",
        "DROP TABLE IF EXISTS lease6",
        "DROP TABLE IF EXISTS lease6_types",
        "DROP TABLE IF EXISTS lease_hwaddr_source",
        "DROP TABLE IF EXISTS schema_version",
        "DROP TABLE IF EXISTS ipv6_reservations",
        "DROP TABLE IF EXISTS hosts",
        "DROP TABLE IF EXISTS dhcp4_options",
        "DROP TABLE IF EXISTS dhcp6_options",
        "DROP TABLE IF EXISTS host_identifier_type",
        "DROP TABLE IF EXISTS lease_state",
        "DROP TRIGGER IF EXISTS host_BDEL",
        "DROP PROCEDURE IF EXISTS lease4DumpHeader",
        "DROP PROCEDURE IF EXISTS lease4DumpData",
        "DROP PROCEDURE IF EXISTS lease6DumpHeader",
        "DROP PROCEDURE IF EXISTS lease6DumpData",
        NULL
    };

    // Open database
    (void) mysql_real_connect(mysql, "localhost", "keatest",
                              "keatest", "keatest", 0, NULL, 0);

    // Get rid of everything in it.
    for (int i = 0; destroy_statement[i] != NULL; ++i) {
        (void) mysql_query(mysql, destroy_statement[i]);
    }
}

void createMySQLSchema(bool show_err) {
    runMySQLScript(TEST_ADMIN_SCRIPTS_DIR, "mysql/dhcpdb_create.mysql",
                   show_err);
}

void runMySQLScript(const std::string& path, const std::string& script_name,
                    bool show_err) {
    std::ostringstream cmd;
    cmd << "mysql -N -B --user=keatest --password=keatest keatest";
    if (!show_err) {
        cmd << " 2>/dev/null ";
    }

    if (!path.empty()) {
        cmd << " < " << path << "/";
    }

    cmd << script_name;

    int retval = std::system(cmd.str().c_str());
    ASSERT_EQ(0, retval) << "runMySQLSchema failed:" << cmd.str();
}


};
};
};
