// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
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
    cmd << " sh " << DATABASE_WIPE_DIR << "/pgsql/wipe_data.sh";

    // Add expected schema version as the wipe script's first argument.
    cmd  << " " << PGSQL_SCHEMA_VERSION_MAJOR  << "." << PGSQL_SCHEMA_VERSION_MINOR;

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
        std::cerr << "runPgSQLSchema failed: " << cmd.str() << std::endl;
        isc_throw(Unexpected, "runPgSQLSchema failed: " << cmd.str());
    }
}

string getPgSQLTlsEnv() {
    const string name("KEA_PGSQL_HAVE_SSL");
    const char* val = getenv(name.c_str());
    return (val ? string(val) : "");
}

string getPgSQLTlsServerVariable(string variable) {
    DatabaseConnection::ParameterMap parameters =
        DatabaseConnection::parse(validPgSQLConnectionString());
    PgSqlConnection conn(parameters);
    conn.openDatabase();
    string sql("select name, setting from pg_settings where name like '");
    sql += variable;
    sql += "';";
    PgSqlResult r(PQexec(conn, sql.c_str()));
    if (PQresultStatus(r) != PGRES_TUPLES_OK) {
        isc_throw(DbOperationError, sql << ": " << PQerrorMessage(conn));
    }
    if (r.getRows() != 1) {
        isc_throw(DbOperationError, sql << " returned " << r.getRows() << " rows, expected one row");
    }
    string fetched_str;
    PgSqlExchange::getColumnValue(r, 0, 0, fetched_str);
    // first column is variable name e.g. 'ssl', second is the value.
    if (fetched_str != variable) {
        isc_throw(DbOperationError,
                  sql << " returned a wrong name '" << fetched_str
                  << "', expected '" << variable << "'");
    }
    PgSqlExchange::getColumnValue(r, 0, 1, fetched_str);
    return (fetched_str);
}

bool isPgSQLTlsConfigured() {
    if (getPgSQLTlsServerVariable("ssl_ca_file").find("kea-ca.crt") == string::npos) {
        return (false);
    }
    if (getPgSQLTlsServerVariable("ssl_cert_file").find("kea-server.crt") == string::npos) {
        return (false);
    }
    if (getPgSQLTlsServerVariable("ssl_key_file").find("kea-server.key") == string::npos) {
        return (false);
    }
    return (true);
}

string getPgSQLTlsServer() {
    string value = getPgSQLTlsServerVariable("ssl");
    if (value == "on") {
        if (!isPgSQLTlsConfigured()) {
            value = "UNCONFIGURED";
        } else {
            value = "YES";
        }
    }
    const string env("KEA_PGSQL_HAVE_SSL");
    static_cast<void>(setenv(env.c_str(), value.c_str(), 1));
    return (value);
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
