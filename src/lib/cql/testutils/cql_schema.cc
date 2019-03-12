// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cassandra.h>

#include <cql/cql_connection.h>
#include <cql/testutils/cql_schema.h>
#include <exceptions/exceptions.h>

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace isc {
namespace db {
namespace test {

const char* CQL_VALID_TYPE = "type=cql";

std::string
validCqlConnectionString() {
    return (connectionString(CQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER,
                             VALID_PASSWORD));
}

void
destroyCqlSchema(bool show_err, bool force) {
    // If force is true or wipeCqlData() fails, destory the schema.
    if (force || (!softWipeEnabled()) || wipeCqlData(show_err)) {
        runCqlScript(DATABASE_SCRIPTS_DIR, "cql/dhcpdb_drop.cql", show_err);
    }
}

void
createCqlSchema(bool show_err, bool force) {
    // If force is true or wipeCqlData() fails, recreate the schema.
    if (force || (!softWipeEnabled()) || wipeCqlData(show_err)) {
        destroyCqlSchema(show_err, true);
        runCqlScript(DATABASE_SCRIPTS_DIR, "cql/dhcpdb_create.cql", show_err);
    }
}

void
runCqlScript(const std::string& path,
             const std::string& script_name,
             bool show_err) {
    std::ostringstream cmd;
    cmd << "cqlsh -u keatest -p keatest -k keatest --request-timeout=6000";
    if (!show_err) {
        cmd << " 2>/dev/null ";
    }

    cmd << " -f";

    if (!path.empty()) {
        cmd << path << "/";
    }

    cmd << script_name;

    int32_t retval = ::system(cmd.str().c_str());
    if (retval) {
        std::cerr << "runCqlSchema failed:" << cmd.str() << std::endl;
        isc_throw(Unexpected, "runCqlSchema failed:" << cmd.str());
    }
}

bool wipeCqlData(bool show_err) {
    std::ostringstream cmd;
    cmd << "sh " << DATABASE_SCRIPTS_DIR << "/";

    std::ostringstream version;
    version << CQL_SCHEMA_VERSION_MAJOR  << "." << CQL_SCHEMA_VERSION_MINOR;

    cmd << "cql/wipe_data.sh" << " " << version.str()
        << " -u keatest -p keatest -k keatest --request-timeout=6000";

    if (!show_err) {
        cmd << " 2>/dev/null ";
    }

    int retval = ::system(cmd.str().c_str());
    if (retval) {
        std::cerr << "wipeCqlData failed:[" << cmd.str() << "]" << std::endl;
    }

    return(retval);
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
