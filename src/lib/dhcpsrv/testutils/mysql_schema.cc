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

void destroyMySQLSchema(bool show_err) {
    runMySQLScript(DATABASE_SCRIPTS_DIR, "mysql/dhcpdb_drop.mysql", show_err);
}

void createMySQLSchema(bool show_err) {
    runMySQLScript(DATABASE_SCRIPTS_DIR, "mysql/dhcpdb_create.mysql",
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

    int retval = ::system(cmd.str().c_str());
    ASSERT_EQ(0, retval) << "runMySQLSchema failed:" << cmd.str();
}


};
};
};
