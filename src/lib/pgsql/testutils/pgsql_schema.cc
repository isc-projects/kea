// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <string>
#include <pgsql/testutils/pgsql_schema.h>

#include <libpq-fe.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

namespace isc {
namespace db {
namespace test {

const char* PGSQL_VALID_TYPE = "type=postgresql";

string
validPgSQLConnectionString() {
    return (connectionString(PGSQL_VALID_TYPE, VALID_NAME, VALID_HOST,
                             VALID_USER, VALID_PASSWORD));
}

void destroyPgSQLSchema(bool show_err) {
    runPgSQLScript(DATABASE_SCRIPTS_DIR, "pgsql/dhcpdb_drop.pgsql", show_err);
}

void createPgSQLSchema(bool show_err) {
    runPgSQLScript(DATABASE_SCRIPTS_DIR, "pgsql/dhcpdb_create.pgsql", show_err);
}

void runPgSQLScript(const std::string& path, const std::string& script_name,
                    bool show_err) {
    std::ostringstream cmd;

    cmd << "export PGPASSWORD=keatest; cat ";
    if (!path.empty()) {
        cmd << " < " << path << "/";
    }

    cmd << script_name
        << " | psql --set ON_ERROR_STOP=1 -A -t -h localhost -q -U keatest -d keatest";

    if (!show_err) {
        cmd << " 2>/dev/null ";
    }

    int retval = ::system(cmd.str().c_str());
    if (retval) {
        std::cerr << "runPgSQLSchema failed:" << cmd.str() << std::endl;
    }
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
