// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
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
    // If force is true or wipeMySQLData() fails, destroy the schema.
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

    cmd << "mysql/wipe_data.sh " << version.str()
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
        std::cerr << "runMySQLSchema failed: " << cmd.str() << std::endl;
        isc_throw(Unexpected, "runMySQLSchema failed: " << cmd.str());
    }
}

string getMySQLTlsEnv() {
    const string name("KEA_MYSQL_HAVE_SSL");
    const char* val = getenv(name.c_str());
    return (val ? string(val) : "");
}

string getMySQLTlsServerVariable(string variable) {
    MYSQL_RES* result(0);
    try {
        DatabaseConnection::ParameterMap parameters =
            DatabaseConnection::parse(validMySQLConnectionString());
        MySqlConnection conn(parameters);
        conn.openDatabase();
        string sql("SHOW GLOBAL VARIABLES LIKE '");
        sql += variable;
        sql += "'";
        if (mysql_query(conn.mysql_, sql.c_str())) {
            isc_throw(DbOperationError,
                      sql << ": " << mysql_error(conn.mysql_));
        }
        result = mysql_use_result(conn.mysql_);
        size_t count = mysql_num_fields(result);
        if (count != 2) {
            isc_throw(DbOperationError,
                      sql << " returned " << count << " rows, expecting 2");
        }
        MYSQL_ROW row = mysql_fetch_row(result);
        if (!row) {
            isc_throw(DbOperationError, sql << " returned row is null");
        }
        // first column is 'have_ssl', second is the status.
        string name(row[0]);
        if (name != variable) {
            isc_throw(DbOperationError,
                      sql << " returned a wrong name '" << name
                      << "', expected '" << variable << "'");
        }
        string value(row[1]);
        mysql_free_result(result);
        return (value);
    } catch (...) {
        if (result) {
            mysql_free_result(result);
        }
        throw;
    }
}

bool isMySQLTlsConfigured() {
    if (getMySQLTlsServerVariable("ssl_ca").find("kea-ca.crt") == string::npos) {
        return (false);
    }
    if (getMySQLTlsServerVariable("ssl_cert").find("kea-server.crt") == string::npos) {
        return (false);
    }
    if (getMySQLTlsServerVariable("ssl_key").find("kea-server.key") == string::npos) {
        return (false);
    }
    return (true);
}

string getMySQLTlsServer() {
    string value = getMySQLTlsServerVariable("have_ssl");
    if (value == "YES" && !isMySQLTlsConfigured()) {
        value = "UNCONFIGURED";
    }
    const string env("KEA_MYSQL_HAVE_SSL");
    static_cast<void>(setenv(env.c_str(), value.c_str(), 1));
    return (value);
}

}  // namespace test
}  // namespace db
}  // namespace isc
