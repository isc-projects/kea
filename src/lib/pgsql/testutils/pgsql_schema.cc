// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <string>
#include <pgsql//pgsql_connection.h>
#include <pgsql/testutils/pgsql_schema.h>
#include <exceptions/exceptions.h>

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

void destroyPgSQLSchema(bool show_err, bool force) {
    // If force is true or wipePgSQLData() fails, destroy the schema.
    if (force || (!softWipeEnabled()) || wipePgSQLData(show_err)) {
        runPgSQLScript(DATABASE_SCRIPTS_DIR, "pgsql/dhcpdb_drop.pgsql", show_err);
    }
}

void createPgSQLSchema(bool show_err, bool force) {
    // If force is true or wipePgSQLData() fails, recreate the schema.
    if (force || (!softWipeEnabled()) || wipePgSQLData(show_err)) {
        destroyPgSQLSchema(show_err, true);
        runPgSQLScript(DATABASE_SCRIPTS_DIR, "pgsql/dhcpdb_create.pgsql", show_err);
    }
}

bool wipePgSQLData(bool show_err) {
    std::ostringstream cmd;

    // Pass psql the password via environment variable.
    cmd << "export PGPASSWORD=keatest;";

    // Add in the wipe shell script invocation.
    cmd << " sh " << DATABASE_SCRIPTS_DIR << "/pgsql/wipe_data.sh";

    // Add expected schema version as the wipe script's first argument.
    cmd  << " " << PG_SCHEMA_VERSION_MAJOR  << "." << PG_SCHEMA_VERSION_MINOR;

    // Now add command line arguments for psql.
    cmd  << " --set ON_ERROR_STOP=1 -A -t -h localhost -q -U keatest -d keatest";

    // Suppress error output.
    if (!show_err) {
        cmd << " 2>/dev/null ";
    }

    // Execute the command string.
    int retval = ::system(cmd.str().c_str());
    if (retval) {
        std::cerr << "wipePgSQLData failed:[" << cmd.str() << "]" << std::endl;
    }

    return(retval);
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
        isc_throw(Unexpected, "runPgSQLSchema failed:" << cmd.str());
    }
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
