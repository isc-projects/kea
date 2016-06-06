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

bool softWipeEnabled() {
    const char* const env = getenv("KEA_TEST_CASSANDRA_WIPE");
    if (env && (string(env) == string("soft"))) {
        return (true);
    }

    return (false);
}

void destroyDSCSQLSchema(bool force_wipe, bool show_err) {
    if (force_wipe || !softWipeEnabled()) {
        // Do full wipe
        runDSCSQLScript(DATABASE_SCRIPTS_DIR, "dscsql/dhcpdb_drop.cql", show_err);
    } else {

        // do soft wipe (just remove the data, not the structures)
        runDSCSQLScript(DATABASE_SCRIPTS_DIR, "dscsql/soft_wipe.cql", show_err);
    }
}

void createDSCSQLSchema(bool force_wipe, bool show_err) {
    if (force_wipe || !softWipeEnabled()) {
        runDSCSQLScript(DATABASE_SCRIPTS_DIR, "dscsql/dhcpdb_create.cql",
                        show_err);
    }
}

void runDSCSQLScript(const std::string& path, const std::string& script_name,
                    bool show_err) {
    std::ostringstream cmd;
    cmd << "cqlsh -u keatest -p keatest -k keatest";
    if (!show_err) {
        cmd << " 2>/dev/null ";
    }

    cmd << " -f ";

    if (!path.empty()) {
        cmd << path << "/";
    }
    cmd << script_name;

    /// @todo: Remove this once the unit-tests are in better shape.
    ///
    /// This print is here only temporary. We will remove it once all of the
    /// Cassandra unit-tests will be passing.
    std::cout << "cmdline:" << cmd.str() << endl;

    int retval = ::system(cmd.str().c_str());
    ASSERT_EQ(0, retval) << "runDSCSQLSchema failed:" << cmd.str();
}


};
};
};
