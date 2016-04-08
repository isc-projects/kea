// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <string>
#include <mysql.h>
#include <dhcpsrv/mysql_connection.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

namespace isc {
namespace dhcp {
namespace test {

// Connection strings.
// Database: keatest
// Host: localhost
// Username: keatest
// Password: keatest
const char* VALID_TYPE = "type=mysql";
const char* INVALID_TYPE = "type=unknown";
const char* VALID_NAME = "name=keatest";
const char* INVALID_NAME = "name=invalidname";
const char* VALID_HOST = "host=localhost";
const char* INVALID_HOST = "host=invalidhost";
const char* VALID_USER = "user=keatest";
const char* INVALID_USER = "user=invaliduser";
const char* VALID_PASSWORD = "password=keatest";
const char* INVALID_PASSWORD = "password=invalid";

string connectionString(const char* type, const char* name, const char* host,
                        const char* user, const char* password) {
    const string space = " ";
    string result = "";

    if (type != NULL) {
        result += string(type);
    }
    if (name != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(name);
    }

    if (host != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(host);
    }

    if (user != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(user);
    }

    if (password != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(password);
    }

    return (result);
}

// Return valid connection string
string
validMySQLConnectionString() {
    return (connectionString(VALID_TYPE, VALID_NAME, VALID_HOST,
                             VALID_USER, VALID_PASSWORD));
}

// @brief Clear everything from the database
//
// There is no error checking in this code: if something fails, one of the
// tests will (should) fall over.
void destroyMySQLSchema() {
    MySqlHolder mysql;
    // @todo - replace this with list gleaned from create script
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

// @brief Create the Schema
//
// Creates all the tables in what is assumed to be an empty database. If the
// script fails, the invoking test will fail.  The output of stderr is 
// suppressed unless the parameter, show_err is true.  The is done to 
// suppress the mysql warning about passing the password in on the command
// line, which otherwise mkes test output rather noisy.
//
// @param show_err flag which governs whether or not stderr is suppressed.
void createMySQLSchema(bool show_err) {
    std::ostringstream cmd;
    cmd << "mysql -N -B --user=keatest --password=keatest keatest";
    if (!show_err) {
        cmd << " 2>/dev/null ";
    }
    cmd << " < " << TEST_ADMIN_SCRIPTS_DIR << "/mysql/dhcpdb_create.mysql";

    int retval = std::system(cmd.str().c_str());
    ASSERT_EQ(0, retval) << "createMySQLSchema failed";
}

};
};
};
