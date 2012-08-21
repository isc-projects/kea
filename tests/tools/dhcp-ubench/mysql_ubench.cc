// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>

#include "benchmark.h"
#include "mysql_ubench.h"

using namespace std;

MySQL_uBenchmark::MySQL_uBenchmark(const string& hostname, const string& user,
                                   const string& pass, const string& db,
                                   uint32_t num_iterations, bool sync,
                                   bool verbose)
    :uBenchmark(num_iterations, db, sync, verbose, hostname, user, pass),
     conn_(NULL) {

}

void MySQL_uBenchmark::failure(const char* operation) {
    stringstream tmp;
    tmp << "Error " << mysql_errno(conn_) << " during " << operation
        << ": " << mysql_error(conn_);
    throw tmp.str();
}

void MySQL_uBenchmark::connect() {

    conn_ = mysql_init(NULL);
    if (!conn_) {
        failure("initializing MySQL library");
    } else {
        cout << "MySQL library init successful." << endl;
    }

    if (!mysql_real_connect(conn_, hostname_.c_str(), user_.c_str(),
                            passwd_.c_str(), dbname_.c_str(), 0, NULL, 0)) {
        failure("connecting to MySQL server");
    } else {
        cout << "MySQL connection established." << endl;
    }

    string q = "delete from lease4;";
    if (mysql_real_query(conn_, q.c_str(), strlen(q.c_str()))) {
        failure("dropping old lease4 entries.");
    }

    q = "ALTER TABLE lease4 engine=";
    if (sync_) {
        q += "InnoDB";
    } else {
        q += "MyISAM";
    }
    if (mysql_query(conn_, q.c_str())) {
        q = "Failed to run query:" + q;
        failure(q.c_str());
    }
}

void MySQL_uBenchmark::disconnect() {
    if (!conn_) {
        throw "NULL MySQL connection pointer.";
    }
    mysql_close(conn_);
    conn_ = NULL;
}

void MySQL_uBenchmark::createLease4Test() {
    if (!conn_) {
        throw "Not connected to MySQL server.";
    }

    uint32_t addr = BASE_ADDR4; // Let's start with 1.0.0.0 address
    char hwaddr[20];
    size_t hwaddr_len = 20;    // Not a real field
    char client_id[128];
    size_t client_id_len = 128;
    uint32_t valid_lft = 1000;  // We can use the same value for all leases
    uint32_t recycle_time = 7;  //    not supported in any foresable future,

    char cltt[48];              // timestamp (specified as text)
    size_t cltt_len;

    sprintf(cltt, "2012-07-11 15:43:00");
    cltt_len = strlen(cltt);

    uint32_t pool_id = 1000;       // Let's use pools 0-99
    bool fixed = false;

    char hostname[] = "foo";    // Will generate it dynamically
    size_t hostname_len;
    hostname_len = strlen(hostname);

    bool fqdn_fwd = true;       // Let's pretend to do AAAA update
    bool fqdn_rev = true;       // Let's pretend to do PTR update

    printf("CREATE:   ");

    for (uint8_t i = 0; i < 20; i++) {
        hwaddr[i] = 65 + i;
    }
    hwaddr[19] = 0;

    for (uint8_t i = 0; i < 128; i++) {
        client_id[i] = 33 + i;
    }
    client_id[127] = 0;

    MYSQL_STMT * stmt = NULL;
    MYSQL_BIND bind[11]; // 11 parameters in the insert statement

    if (compiled_stmt_) {
        // create a statement once
        stmt = mysql_stmt_init(conn_);
        if (!stmt) {
            failure("Unable to create compiled statement, mysql_stmt_init() failed");
        }

        const char * statement = "INSERT INTO lease4(addr,hwaddr,client_id,"
            "valid_lft,recycle_time,cltt,pool_id,fixed,hostname,"
            "fqdn_fwd,fqdn_rev) VALUES(?,?,?,?,?,?,?,?,?,?,?)";

        if (mysql_stmt_prepare(stmt, statement, strlen(statement) )) {
            failure("Failed to prepare statement, mysql_stmt_prepare() returned non-zero");
        }
        int param_cnt = mysql_stmt_param_count(stmt);
        if (param_cnt != 11) {
            failure("Parameter count sanity check failed.");
        }

        memset(bind, 0, sizeof(bind));

        // 1st parameter: IPv4 address
        bind[0].buffer_type = MYSQL_TYPE_LONG;
        bind[0].buffer = (&addr);
        bind[0].is_null = 0;
        bind[0].length = 0;

        // 2nd parameter: Hardware address
        bind[1].buffer_type = MYSQL_TYPE_VARCHAR;
        bind[1].buffer = hwaddr;
        bind[1].buffer_length = hwaddr_len;
        bind[1].is_null = 0;
        bind[1].length = &hwaddr_len;

        // 3rd parameter: Client-id
        bind[2].buffer_type = MYSQL_TYPE_VARCHAR;
        bind[2].buffer = client_id;
        bind[2].buffer_length = client_id_len;
        bind[2].is_null = 0;
        bind[2].length = &client_id_len;

        // 4th parameter: valid-lifetime
        bind[3].buffer_type = MYSQL_TYPE_LONG;
        bind[3].buffer = (&valid_lft);
        bind[3].is_null = 0;
        bind[3].length = 0;

        // 5th parameter: recycle-time
        bind[4].buffer_type = MYSQL_TYPE_LONG;
        bind[4].buffer = (&recycle_time);
        bind[4].is_null = 0;
        bind[4].length = 0;

        // 6th parameter: cltt
        bind[5].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind[5].buffer = cltt;
        bind[2].buffer_length = cltt_len;
        bind[5].is_null = 0;
        bind[5].length = &cltt_len;

        // 7th parameter: pool-id
        bind[6].buffer_type = MYSQL_TYPE_LONG;
        bind[6].buffer = &pool_id;
        bind[6].is_null = 0;
        bind[6].length = 0;

        // 8th parameter: fixed
        bind[7].buffer_type = MYSQL_TYPE_TINY;
        bind[7].buffer = &fixed;
        bind[7].is_null = 0;
        bind[7].length = 0;

        // 9th parameter: hostname
        bind[8].buffer_type = MYSQL_TYPE_VARCHAR;
        bind[8].buffer = hostname;
        bind[8].buffer_length = strlen(hostname);
        bind[8].is_null = 0;
        bind[8].length = &hostname_len;

        // 10th parameter: fqdn_fwd
        bind[9].buffer_type = MYSQL_TYPE_TINY;
        bind[9].buffer = &fqdn_fwd;
        bind[9].is_null = 0;
        bind[9].length = 0;

        // 11th parameter: fqdn_rev
        bind[10].buffer_type = MYSQL_TYPE_TINY;
        bind[10].buffer = &fqdn_rev;
        bind[10].is_null = 0;
        bind[10].length = 0;
    }

    for (uint32_t i = 0; i < num_; i++) {

        sprintf(cltt, "2012-07-11 15:43:%02d", i % 60);


        addr++;

        if (!compiled_stmt_) {
            // the first address is 1.0.0.0.
            char query[2000], * end;
            strcpy(query, "INSERT INTO lease4(addr,hwaddr,client_id,"
                   "valid_lft,recycle_time,cltt,pool_id,fixed,hostname,"
                   "fqdn_fwd,fqdn_rev) VALUES(");
            end = query + strlen(query);
            end += sprintf(end, "%u,\'", addr);
            end += mysql_real_escape_string(conn_, end, hwaddr, hwaddr_len);
            end += sprintf(end,"\',\'");
            end += mysql_real_escape_string(conn_, end, client_id, client_id_len);
            end += sprintf(end, "\',%d,%d,'%s',%d,%s,\'%s\',%s,%s);",
                           valid_lft, recycle_time, cltt,
                           pool_id, (fixed?"true":"false"), hostname,
                           (fqdn_fwd?"true":"false"), (fqdn_rev?"true":"false"));
            // lease_id field is set automatically
            // options and comments fields are not set

            unsigned int len = end - query;
            if (mysql_real_query(conn_, query, len)) {
                // something failed.
                failure("INSERT query");
            }
        } else {
            // compiled statement

            if (mysql_stmt_bind_param(stmt, bind)) {
                failure("Failed to bind parameters: mysql_stmt_bind_param() returned non-zero");
            }

            if (mysql_stmt_execute(stmt)) {
                failure("Failed to execute statement: mysql_stmt_execute() returned non-zero");
            }

        }

        if (verbose_) {
            printf(".");
        }
    }

    if (compiled_stmt_) {
        if (mysql_stmt_close(stmt)) {
            failure("Failed to close compiled statement, mysql_stmt_close returned non-zero");
        }
    }

    printf("\n");
}

void MySQL_uBenchmark::searchLease4Test() {
    if (!conn_) {
        throw "Not connected to MySQL server.";
    }

    printf("RETRIEVE: ");

    uint32_t addr = 0;

    MYSQL_STMT * stmt = NULL;
    MYSQL_BIND bind[1]; // just a single element
    if (compiled_stmt_) {
        stmt = mysql_stmt_init(conn_);
        if (!stmt) {
            failure("Unable to create compiled statement");
        }
        const char * statement = "SELECT lease_id,addr,hwaddr,client_id,"
            "valid_lft, cltt,pool_id,fixed,hostname,fqdn_fwd,fqdn_rev "
            "FROM lease4 where addr=?";
        if (mysql_stmt_prepare(stmt, statement, strlen(statement))) {
           failure("Failed to prepare statement, mysql_stmt_prepare() returned non-zero");
        }
        int param_cnt = mysql_stmt_param_count(stmt);
        if (param_cnt != 1) {
            failure("Parameter count sanity check failed.");
        }

        memset(bind, 0, sizeof(bind));

        // 1st parameter: IPv4 address
        bind[0].buffer_type = MYSQL_TYPE_LONG;
        bind[0].buffer = (&addr);
        bind[0].is_null = 0;
        bind[0].length = 0;
    }

    for (uint32_t i = 0; i < num_; i++) {

        addr = BASE_ADDR4 + random() % int(num_ / hitratio_);

        if (!compiled_stmt_) {
            char query[512];
            sprintf(query, "SELECT lease_id,addr,hwaddr,client_id,valid_lft,"
                    "cltt,pool_id,fixed,hostname,fqdn_fwd,fqdn_rev "
                    "FROM lease4 where addr=%d", addr);
            mysql_real_query(conn_, query, strlen(query));

            MYSQL_RES * result = mysql_store_result(conn_);

            int num_rows = mysql_num_rows(result);
            int num_fields = mysql_num_fields(result);

            if ( (num_rows > 1) ) {
                stringstream tmp;
                tmp << "Search: DB returned " << num_rows << " leases for address "
                    << hex << addr << dec;
                failure(tmp.str().c_str());
            }

            if (num_rows) {
                if (num_fields == 0) {
                    failure("Query returned empty set");
                }

                MYSQL_ROW row = mysql_fetch_row(result);

                // pretend to do something with it
                if (row[0] == NULL) {
                    failure("SELECT returned NULL data.");
                }
                mysql_free_result(result);

                if (verbose_) {
                    printf("."); // hit
                }

            } else {
                if (verbose_) {
                    printf("x"); // miss
                }
            }
        } else {
            // compiled statement

            if (mysql_stmt_bind_param(stmt, bind)) {
                failure("Failed to bind parameters: mysql_stmt_bind_param() returned non-zero");
            }

            if (mysql_stmt_execute(stmt)) {
                failure("Failed to execute statement: mysql_stmt_execute() returned non-zero");
            }

            MYSQL_BIND response[11];

            size_t length[11];
            my_bool is_null[11];
            my_bool error[11];

            uint32_t lease_id;
            uint32_t lease_addr;
            char hwaddr[20];
            char client_id[128];
            uint32_t valid_lft;  // We can use the same value for all leases
            MYSQL_TIME cltt;
            uint32_t pool_id;
            my_bool fixed;
            char hostname[255];
            my_bool fqdn_fwd;
            my_bool fqdn_rev;

            for (int j = 0; j < 11; j++) {
                response[j].is_null = &is_null[j];
                response[j].length = &length[j];
                response[j].error = &error[j];
            }

            // 1th parameter: lease_id
            response[0].buffer_type = MYSQL_TYPE_LONG;
            response[0].buffer = (&lease_id);

            // 2nd parameter: IPv4 address
            response[1].buffer_type = MYSQL_TYPE_LONG;
            response[1].buffer = (&lease_addr);

            // 3rd parameter: Hardware address
            response[2].buffer_type = MYSQL_TYPE_STRING;
            response[2].buffer = hwaddr;
            response[2].buffer_length = sizeof(hwaddr);

            // 4th parameter: Client-id
            response[3].buffer_type = MYSQL_TYPE_STRING;
            response[3].buffer = &client_id;

            // 5th parameter: valid-lifetime
            response[4].buffer_type = MYSQL_TYPE_LONG;
            response[4].buffer = &valid_lft;

            // 6th parameter: cltt
            response[5].buffer_type = MYSQL_TYPE_TIMESTAMP;
            response[5].buffer = &cltt;

            // 7th parameter: pool-id
            response[6].buffer_type = MYSQL_TYPE_LONG;
            response[6].buffer = &pool_id;

            // 8th parameter: fixed
            response[7].buffer_type = MYSQL_TYPE_TINY;
            response[7].buffer = &fixed;

            // 9th parameter: hostname
            response[8].buffer_type = MYSQL_TYPE_STRING;
            response[8].buffer = &hostname;

            // 10th parameter: fqdn_fwd
            response[9].buffer_type = MYSQL_TYPE_TINY;
            response[9].buffer = &fqdn_fwd;

            // 11th parameter: fqdn_rev
            response[10].buffer_type = MYSQL_TYPE_TINY;
            response[10].buffer = &fqdn_rev;

            if (mysql_stmt_bind_result(stmt, response))
            {
                printf("Error: %s\n", mysql_stmt_error(stmt));
                failure("mysql_stmt_bind_result() failed");
            }
            int num_rows = 0;

            if (!mysql_stmt_fetch(stmt)) {
                if (lease_addr != addr) {
                    failure("Returned data is bogus!");
                }
                num_rows++;
            }

            // we could call mysql_stmt_fetch again to check that there are no
            // other data for us. But there should be exactly one row of data
            // with specified address.

            if (num_rows) {
                if (verbose_) {
                    printf("."); // hit
                }
            } else {
                if (verbose_) {
                    printf("x"); // miss
                }
            }

        }
    }

    if (compiled_stmt_) {
        if (mysql_stmt_close(stmt)) {
            failure("Failed to close compiled statement, mysql_stmt_close returned non-zero");
        }
    }

    printf("\n");
}

void MySQL_uBenchmark::updateLease4Test() {
    if (!conn_) {
        throw "Not connected to MySQL server.";
    }

    printf("UPDATE:   ");

    uint32_t valid_lft = 1002; // just some dummy value
    char cltt[] = "now()";
    size_t cltt_len = strlen(cltt);
    uint32_t addr = 0;

    MYSQL_STMT * stmt = NULL;
    MYSQL_BIND bind[3];
    if (compiled_stmt_) {
        stmt = mysql_stmt_init(conn_);
        if (!stmt) {
            failure("Unable to create compiled statement");
        }
        const char * statement = "UPDATE lease4 SET valid_lft=?, cltt=? WHERE addr=?";
        if (mysql_stmt_prepare(stmt, statement, strlen(statement))) {
           failure("Failed to prepare statement, mysql_stmt_prepare() returned non-zero");
        }
        int param_cnt = mysql_stmt_param_count(stmt);
        if (param_cnt != 3) {
            failure("Parameter count sanity check failed.");
        }

        memset(bind, 0, sizeof(bind));

        // 1st parameter: valid lifetime
        bind[0].buffer_type = MYSQL_TYPE_LONG;
        bind[0].buffer = &valid_lft;

        // 2nd parameter: cltt
        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = &cltt;
        bind[1].buffer_length = cltt_len;

        bind[2].buffer_type = MYSQL_TYPE_LONG;
        bind[2].buffer = &addr;
    }


    for (uint32_t i = 0; i < num_; i++) {

        addr = BASE_ADDR4 + random() % num_;

        if (!compiled_stmt_) {
            char query[128];
            sprintf(query, "UPDATE lease4 SET valid_lft=1002, cltt=now() WHERE addr=%d", addr);
            mysql_real_query(conn_, query, strlen(query));

        } else {
            // compiled statement
            if (mysql_stmt_bind_param(stmt, bind)) {
                failure("Failed to bind parameters: mysql_stmt_bind_param() returned non-zero");
            }

            if (mysql_stmt_execute(stmt)) {
                failure("Failed to execute statement: mysql_stmt_execute() returned non-zero");
            }
        }

        if (verbose_) {
            printf(".");
        }
    }

    if (compiled_stmt_) {
        if (mysql_stmt_close(stmt)) {
            failure("Failed to close compiled statement, mysql_stmt_close returned non-zero");
        }
    }

    printf("\n");
}

void MySQL_uBenchmark::deleteLease4Test() {
    if (!conn_) {
        throw "Not connected to MySQL server.";
    }

    printf("DELETE:   ");

    uint32_t addr = 0;

    MYSQL_STMT * stmt = NULL;
    MYSQL_BIND bind[1]; // just a single element
    if (compiled_stmt_) {

        stmt = mysql_stmt_init(conn_);
        if (!stmt) {
            failure("Unable to create compiled statement, mysql_stmt_init() failed");
        }

        const char * statement = "DELETE FROM lease4 WHERE addr=?";

        if (mysql_stmt_prepare(stmt, statement, strlen(statement) )) {
            failure("Failed to prepare statement, mysql_stmt_prepare() returned non-zero");
        }
        int param_cnt = mysql_stmt_param_count(stmt);
        if (param_cnt != 1) {
            failure("Parameter count sanity check failed.");
        }

        memset(bind, 0, sizeof(bind));

        // 1st parameter: IPv4 address
        bind[0].buffer_type = MYSQL_TYPE_LONG;
        bind[0].buffer = (&addr);
        bind[0].is_null = 0;
        bind[0].length = 0;
    }


    for (uint32_t i = 0; i < num_; i++) {

        addr = BASE_ADDR4 + i;

        if (!compiled_stmt_) {
            char query[128];
            sprintf(query, "DELETE FROM lease4 WHERE addr=%d", addr);
            mysql_real_query(conn_, query, strlen(query));
        } else {
            // compiled statement
            if (mysql_stmt_bind_param(stmt, bind)) {
                failure("Failed to bind parameters: mysql_stmt_bind_param() returned non-zero");
            }

            if (mysql_stmt_execute(stmt)) {
                failure("Failed to execute statement: mysql_stmt_execute() returned non-zero");
            }
        }

        if (verbose_) {
            printf(".");
        }
    }

    if (compiled_stmt_) {
        if (mysql_stmt_close(stmt)) {
            failure("Failed to close compiled statement, mysql_stmt_close returned non-zero");
        }
    }

    printf("\n");
}

void MySQL_uBenchmark::printInfo() {
    cout << "MySQL client version is " << mysql_get_client_info() << endl;
}


int main(int argc, char * const argv[]) {

    const char* hostname ="localhost";  // -m (MySQL server)
    const char* user = "root";          // -u
    const char* passwd = "secret";      // -p
    const char* dbname = "kea";         // -f
    uint32_t num = 100;                 // -n
    bool sync = true;                   // -s
    bool verbose = true;                // -v

    MySQL_uBenchmark bench(hostname, user, passwd, dbname, num, sync, verbose);

    bench.parseCmdline(argc, argv);

    int result = bench.run();

    return (result);
}
