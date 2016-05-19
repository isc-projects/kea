// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <string>
#include <cassandra.h>
#include <dhcpsrv/dscsql_connection.h>
#include <dhcpsrv/testutils/dscsql_schema.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

namespace isc {
namespace dhcp {
namespace test {

const char* DSCSQL_VALID_TYPE = "type=cassandra";

string
validDSCSQLConnectionString() {
    return (connectionString(DSCSQL_VALID_TYPE, VALID_NAME, VALID_HOST,
                             VALID_USER, VALID_PASSWORD));
}

void destroyDSCSQLSchema(bool show_err) {
    runDSCSQLScript(DATABASE_SCRIPTS_DIR, "dscsql/dhcpdb_drop.cql", show_err);
}

void createDSCSQLSchema(bool show_err) {
    runDSCSQLScript(DATABASE_SCRIPTS_DIR, "dscsql/dhcpdb_create.cql",
                   show_err);
}

void runDSCSQLScript(const std::string& path, const std::string& script_name,
                    bool show_err) {
    std::ostringstream cmd;
    cmd << "cqlsh -u keatest -p keatest -k keatest -f";
    if (!show_err) {
        cmd << " 2>/dev/null ";
    }

    if (!path.empty()) {
        cmd << " < " << path << "/";
    }

    cmd << script_name;

    int retval = ::system(cmd.str().c_str());
    ASSERT_EQ(0, retval) << "runDSCSQLSchema failed:" << cmd.str();
}


};
};
};
