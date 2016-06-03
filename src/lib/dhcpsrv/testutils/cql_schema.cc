// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <string>
#include <cassandra.h>
#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/testutils/cql_schema.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

namespace isc {
namespace dhcp {
namespace test {

const char* CQL_VALID_TYPE = "type=cassandra";

string
validCqlConnectionString() {
    return (connectionString(CQL_VALID_TYPE, VALID_NAME, VALID_HOST,
                             VALID_USER, VALID_PASSWORD));
}

void destroyCqlSchema(bool show_err) {
    runCqlScript(DATABASE_SCRIPTS_DIR, "cql/dhcpdb_drop.cql", show_err);
}

void createCqlSchema(bool show_err) {
    runCqlScript(DATABASE_SCRIPTS_DIR, "cql/dhcpdb_create.cql",
                   show_err);
}

void runCqlScript(const std::string& path, const std::string& script_name,
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
    ASSERT_EQ(0, retval) << "runCqlSchema failed:" << cmd.str();
}


};
};
};
