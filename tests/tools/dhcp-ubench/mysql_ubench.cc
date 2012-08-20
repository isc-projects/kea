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
     Conn_(NULL) {

}

void MySQL_uBenchmark::failure(const char* operation) {
    stringstream tmp;
    tmp << "Error " << mysql_errno(Conn_) << " during " << operation
        << ": " << mysql_error(Conn_);
    throw tmp.str();
}

void MySQL_uBenchmark::connect() {

    Conn_ = mysql_init(NULL);
    if (!Conn_) {
        failure("initializing MySQL library");
    } else {
        cout << "MySQL library init successful." << endl;
    }

    if (!mysql_real_connect(Conn_, hostname_.c_str(), user_.c_str(),
                            passwd_.c_str(), dbname_.c_str(), 0, NULL, 0)) {
        failure("connecting to MySQL server");
    } else {
        cout << "MySQL connection established." << endl;
    }

    string q = "delete from lease4;";
    if (mysql_real_query(Conn_, q.c_str(), strlen(q.c_str()))) {
        failure("dropping old lease4 entries.");
    }

    q = "ALTER TABLE lease4 engine=";
    if (sync_) {
        q += "InnoDB";
    } else {
        q += "MyISAM";
    }
    if (mysql_query(Conn_, q.c_str())) {
        q = "Failed to run query:" + q;
        failure(q.c_str());
    }
}

void MySQL_uBenchmark::disconnect() {
    if (!Conn_) {
        throw "NULL MySQL connection pointer.";
    }
    mysql_close(Conn_);
    Conn_ = NULL;
}

void MySQL_uBenchmark::createLease4Test() {
    if (!Conn_) {
        throw "Not connected to MySQL server.";
    }

    uint32_t addr = BASE_ADDR4; // Let's start with 1.0.0.0 address
    char hwaddr[20];
    uint8_t hwaddr_len = 20;    // Not a real field
    char client_id[128];
    uint8_t client_id_len = 128;
    uint32_t valid_lft = 1000;  // We can use the same value for all leases
    uint32_t recycle_time = 0;  //    not supported in any foresable future,
                                //    so keep this as 0
    string cltt = "now()";      // Timestamp
    uint32_t pool_id = 0;       // Let's use pools 0-99
    bool fixed = false;
    string hostname("foo");     // Will generate it dynamically
    bool fqdn_fwd = true;       // Let's pretend to do AAAA update
    bool fqdn_rev = true;       // Let's pretend to do PTR update

    printf("CREATE:   ");

    for (uint8_t i = 0; i < 20; i++) {
        hwaddr[i] = 65 + i;
    }

    for (uint8_t i = 0; i < 128; i++) {
        client_id[i] = 33 + i;
    }

    for (uint32_t i = 0; i < num_; i++) {

        stringstream cltt;
        cltt << "2012-07-11 15:43:" << (i % 60);

        addr++;

        // the first address is 1.0.0.0.
        char query[2000], * end;
        strcpy(query, "INSERT INTO lease4(addr,hwaddr,client_id,"
               "valid_lft,recycle_time,cltt,pool_id,fixed,hostname,"
               "fqdn_fwd,fqdn_rev) VALUES(");
        end = query + strlen(query);
        end += sprintf(end, "%u,\'", addr);
        end += mysql_real_escape_string(Conn_, end, hwaddr, hwaddr_len);
        end += sprintf(end,"\',\'");
        end += mysql_real_escape_string(Conn_, end, client_id, client_id_len);
        end += sprintf(end, "\',%d,%d,'%s',%d,%s,\'%s\',%s,%s);",
                       valid_lft, recycle_time, cltt.str().c_str(),
                       pool_id, (fixed?"true":"false"), hostname.c_str(),
                       (fqdn_fwd?"true":"false"), (fqdn_rev?"true":"false"));
        // lease_id field is set automatically
        // options and comments fields are not set

        unsigned int len = end - query;
        if (mysql_real_query(Conn_, query, len)) {
            // something failed.
            failure("INSERT query");
        } else {
            if (verbose_) {
                printf(".");
            }
        };
    }
    printf("\n");
}

void MySQL_uBenchmark::searchLease4Test() {
    if (!Conn_) {
        throw "Not connected to MySQL server.";
    }

    /* cout << "range=" << int(Num_ / hitRatio) << " minAddr=" << hex
         << BASE_ADDR4 << " maxAddr=" << BASE_ADDR4 + int(Num_ / hitRatio)
         << dec << endl; */

    printf("RETRIEVE: ");


    for (uint32_t i = 0; i < num_; i++) {

        uint32_t x = BASE_ADDR4 + random() % int(num_ / hitratio_);

        char query[2000];
        sprintf(query, "SELECT lease_id,addr,hwaddr,client_id,valid_lft,"
                "cltt,pool_id,fixed,hostname,fqdn_fwd,fqdn_rev "
                "FROM lease4 where addr=%d", x);
        mysql_real_query(Conn_, query, strlen(query));

        MYSQL_RES * result = mysql_store_result(Conn_);

        int num_rows = mysql_num_rows(result);
        int num_fields = mysql_num_fields(result);

        if ( (num_rows > 1) ) {
            stringstream tmp;
            tmp << "Search: DB returned " << num_rows << " leases for address "
                << hex << x << dec;
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
                printf(".");
            }

        } else {
            if (verbose_) {
                printf("x");
            }
        }
    }

    printf("\n");
}

void MySQL_uBenchmark::updateLease4Test() {
    if (!Conn_) {
        throw "Not connected to MySQL server.";
    }

    printf("UPDATE:   ");

    for (uint32_t i = 0; i < num_; i++) {

        uint32_t x = BASE_ADDR4 + random() % num_;

        char query[2000];
        sprintf(query, "UPDATE lease4 SET valid_lft=1002, cltt=now() WHERE addr=%d", x);
        mysql_real_query(Conn_, query, strlen(query));

        if (verbose_) {
            printf(".");
        }
    }

    printf("\n");
}

void MySQL_uBenchmark::deleteLease4Test() {
    if (!Conn_) {
        throw "Not connected to MySQL server.";
    }

    printf("DELETE:   ");

    for (uint32_t i = 0; i < num_; i++) {

        uint32_t x = BASE_ADDR4 + i;

        char query[2000];
        sprintf(query, "DELETE FROM lease4 WHERE addr=%d", x);
        mysql_real_query(Conn_, query, strlen(query));

        if (verbose_) {
            printf(".");
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
