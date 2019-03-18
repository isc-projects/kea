// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <string>
#include <mysql.h>
#include <mysql/testutils/mysql_schema.h>
#include <mysql/mysql_connection.h>
#include <exceptions/exceptions.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

namespace isc {
namespace db {
namespace test {

const char* MYSQL_VALID_TYPE = "type=mysql";

string
validMySQLConnectionString() {
    return (connectionString(MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST,
                             VALID_USER, VALID_PASSWORD));
}

void destroyMySQLSchema(bool show_err, bool force) {
    // If force is true or wipeMySQLData() fails, destory the schema.
    if (force || (!softWipeEnabled()) || wipeMySQLData(show_err)) {
        runMySQLScript(DATABASE_SCRIPTS_DIR, "mysql/dhcpdb_drop.mysql", show_err);
    }
}

void createMySQLSchema(bool show_err, bool force) {
    // If force is true or wipeMySQLData() fails, recreate the schema.
    if (force || (!softWipeEnabled()) || wipeMySQLData(show_err)) {
        destroyMySQLSchema(show_err, true);
        runMySQLScript(DATABASE_SCRIPTS_DIR, "mysql/dhcpdb_create.mysql", show_err);
    }
}

bool wipeMySQLData(bool show_err) {
    std::ostringstream cmd;
    cmd << "sh " << DATABASE_SCRIPTS_DIR << "/";

    std::ostringstream version;
    version << MYSQL_SCHEMA_VERSION_MAJOR  << "." << MYSQL_SCHEMA_VERSION_MINOR;

    cmd << "mysql/wipe_data.sh" << " " << version.str()
        << " -N -B --user=keatest --password=keatest keatest";
    if (!show_err) {
        cmd << " 2>/dev/null ";
    }

    int retval = ::system(cmd.str().c_str());
    if (retval) {
        std::cerr << "wipeMySQLData failed:[" << cmd.str() << "]" << std::endl;
    }

    return(retval);
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
    if (retval) {
        std::cerr << "runMySQLSchema failed:" << cmd.str() << std::endl;
        isc_throw(Unexpected, "runMySQLSchema failed:" << cmd.str());
    }
}

}  // namespace test
}  // namespace db
}  // namespace isc
