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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <sqlite3.h>
#include "sqlite_ubench.h"

using namespace std;

SQLite_uBenchmark::SQLite_uBenchmark(const string& filename,
                                     uint32_t num_iterations,
                                     bool sync, bool verbose)
    :uBenchmark(num_iterations, filename, sync, verbose),
     db_(NULL) {

}

void SQLite_uBenchmark::connect() {
    int result = sqlite3_open(dbname_.c_str(), &db_);
    if (result != SQLITE_OK) {
        failure("Failed to open DB file");
    }

    result = sqlite3_exec(db_, "DELETE FROM lease4", NULL, NULL, NULL);
    if (result != SQLITE_OK) {
        failure("Failed to delete old entries");
    }

    if (sync_) {
        sqlite3_exec(db_, "PRAGMA synchronous = ON", NULL, NULL, NULL);
    } else {
        sqlite3_exec(db_, "PRAGMA synchronous = OFF", NULL, NULL, NULL);
    }

    // see http://www.sqlite.org/pragma.html#pragma_journal_mode
    // for detailed explanation. Available modes: DELETE, TRUNCATE,
    // PERSIST, MEMORY, WAL, OFF
    sqlite3_exec(db_, "PRAGMA journal_mode = OFF", NULL, NULL, NULL);
}

void SQLite_uBenchmark::disconnect() {
    if (db_) {
        sqlite3_close(db_);
        db_ = NULL;
    }
}

void SQLite_uBenchmark::createLease4Test() {
    if (!db_) {
        throw "SQLite connection is closed.";
    }

    uint32_t addr = BASE_ADDR4;     // Let's start with 1.0.0.0 address
    const uint8_t hwaddr_len = 20;  // Not a real field
    char hwaddr[hwaddr_len];
    const uint8_t client_id_len = 128;
    char client_id[client_id_len];
    uint32_t valid_lft = 1000;      // We can use the same value for all leases
    uint32_t recycle_time = 0;      // Not supported in any foresable future,
                                    //     so keep this as 0
    char cltt[48];                  // Timestamp
    uint32_t pool_id = 0;           // Let's use pools 0-99
    bool fixed = false;
    string hostname("foo");         // Will generate it dynamically
    bool fqdn_fwd = true;           // Let's pretend to do AAAA update
    bool fqdn_rev = true;           // Let's pretend to do PTR update

    printf("CREATE:   ");

    for (uint8_t i = 0; i < hwaddr_len; i++) {
        hwaddr[i] = 65 + i;
    }
    hwaddr[19] = 0; // workaround

    for (uint8_t i = 0; i < client_id_len; i++) {
        client_id[i] = 33 + i;
    }
    client_id[6] = 'X'; // there's apostrophe here. It would confuse
                        // query formatting, let's get rid of it
    client_id[127] = 0; // workaround


    sqlite3_stmt *stmt = NULL;
    if (compiled_stmt_) {
        char query[] = "INSERT INTO lease4(addr,hwaddr,client_id,"
            "valid_lft,recycle_time,cltt,pool_id,fixed,hostname,"
            "fqdn_fwd,fqdn_rev) VALUES(?001,?002,?003,?004,?005,?006,?007,?008,?009,?010,?011);";
        int result = sqlite3_prepare_v2(db_, query, strlen(query), &stmt, NULL);
        if (result != SQLITE_OK) {
            failure("Failed to compile statement");
        }
    }



    for (uint32_t i = 0; i < num_; i++) {

        sprintf(cltt, "2012-07-11 15:43:%02d", i % 60);

        addr++;
        char* errorMsg = NULL;

        if (!compiled_stmt_) {
            // the first address is 1.0.0.0.
            char query[2000];
            /// @todo: Encode HWADDR and CLIENT-ID properly
            sprintf(query, "INSERT INTO lease4(addr,hwaddr,client_id,"
                    "valid_lft,recycle_time,cltt,pool_id,fixed,hostname,"
                    "fqdn_fwd,fqdn_rev) VALUES(%u,'%s','%s',%d,%d,'%s',%d,'%s','%s','%s','%s');",
                    addr, hwaddr, client_id, valid_lft, recycle_time,
                    cltt, pool_id, (fixed?"true":"false"),
                    hostname.c_str(), (fqdn_fwd?"true":"false"), (fqdn_rev?"true":"false"));
            // printf("QUERY=[%s]\n", query);

            int result = sqlite3_exec(db_, query, NULL, 0, &errorMsg);

            if (result != SQLITE_OK) {
                stringstream tmp;
                tmp << "INSERT error:" << errorMsg;
                failure(tmp.str().c_str());
            }
        } else {
            // compiled statement
            int result = sqlite3_bind_int(stmt, 1, addr);
            if (result != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 1");
            }

            result = sqlite3_bind_blob(stmt, 2, hwaddr, hwaddr_len, NULL);
            if (result != SQLITE_OK) {
                failure("sqlite3_bind_blob() for column 2");
            }

            result = sqlite3_bind_blob(stmt, 3, client_id, client_id_len, NULL);
            if (result != SQLITE_OK) {
                failure("sqlite3_bind_blob() for column 3");
            }

            if (sqlite3_bind_int(stmt, 4, valid_lft) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 4");
            }

            if (sqlite3_bind_int(stmt, 5, recycle_time) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 5");
            }

            if (sqlite3_bind_text(stmt, 6, cltt, strlen(cltt), NULL) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 6");
            }

            if (sqlite3_bind_int(stmt, 7, pool_id) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 7");
            }

            if (sqlite3_bind_int(stmt, 7, pool_id) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 7");
            }

            if (sqlite3_bind_int(stmt, 8, fixed) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 8");
            }

            if (sqlite3_bind_text(stmt, 9, hostname.c_str(), hostname.length(), NULL) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 9");
            }

            if (sqlite3_bind_int(stmt, 10, fqdn_fwd) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 10");
            }

            if (sqlite3_bind_int(stmt, 11, fqdn_rev) != SQLITE_OK) {
                failure("sqlite3_bind_int() for column 11");
            }

            result = sqlite3_step(stmt);

            if (result != SQLITE_DONE) {
                failure("Failed to execute INSERT clause");
            }

            // let's reset the compiled statement, so it can be used in the
            // next iteration
            result = sqlite3_reset(stmt);
            if (result != SQLITE_OK) {
                failure("Failed to execute sqlite3_reset()");
            }

        }

        if (verbose_) {
            printf(".");
        }
    }

    int result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        failure("sqlite3_finalize() failed");
    }

    printf("\n");
}

static int search_callback(void *counter, int /*argc*/, char** /*argv*/,
                           char** /*azColName*/){

    int* cnt = static_cast<int*>(counter);
    (*cnt)++;

#if 0
    int i;
    for(i=0; i<argc; i++){
        printf("%s=%s ", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
#endif
    return 0;
}

void SQLite_uBenchmark::searchLease4Test() {
    if (!db_) {
        throw "SQLite connection is closed.";
    }

    printf("RETRIEVE: ");

    for (uint32_t i = 0; i < num_; i++) {

        uint32_t x = BASE_ADDR4 + random() % int(num_ / hitratio_);

        char* errorMsg = NULL;

        int cnt = 0;

        char query[2000];
        sprintf(query, "SELECT lease_id,addr,hwaddr,client_id,valid_lft,"
                "cltt,pool_id,fixed,hostname,fqdn_fwd,fqdn_rev "
                "FROM lease4 where addr=%d", x);
        int result = sqlite3_exec(db_, query, search_callback, &cnt, &errorMsg);
        if (result != SQLITE_OK) {
            stringstream tmp;
            tmp << "SELECT failed: " << errorMsg;
            failure(tmp.str().c_str());
        }

        if (cnt) {
            if (verbose_) {
                printf(".");
            }
        } else {
            if (verbose_) {
                printf("X");
            }
        }

    }

    printf("\n");
}

void SQLite_uBenchmark::updateLease4Test() {
    if (!db_) {
        throw "SQLite connection is closed.";
    }

    printf("UPDATE:   ");

    for (uint32_t i = 0; i < num_; i++) {

        uint32_t x = BASE_ADDR4 + random() % num_;

        char* errorMsg = NULL;
        char query[2000];
        sprintf(query, "UPDATE lease4 SET valid_lft=1002, cltt='now' WHERE addr=%d", x);

        int result = sqlite3_exec(db_, query, NULL /* no callback here*/, 0, &errorMsg);
        if (result != SQLITE_OK) {
            stringstream tmp;
            tmp << "UPDATE error:" << errorMsg;
            failure(tmp.str().c_str());
        }
        if (verbose_) {
            printf(".");
        }
    }

    printf("\n");
}

void SQLite_uBenchmark::deleteLease4Test() {
    if (!db_) {
        throw "SQLite connection is closed.";
    }

    printf("DELETE:   ");

    for (uint32_t i = 0; i < num_; i++) {

        uint32_t x = BASE_ADDR4 + i;
        char* errorMsg = NULL;

        char query[2000];
        sprintf(query, "DELETE FROM lease4 WHERE addr=%d", x);
        int result = sqlite3_exec(db_, query, NULL /* no callback here*/, 0, &errorMsg);
        if (result != SQLITE_OK) {
            stringstream tmp;
            tmp << "DELETE error:" << errorMsg;
            failure(tmp.str().c_str());
        }
        if (verbose_) {
            printf(".");
        }
    }

    printf("\n");
}

void SQLite_uBenchmark::printInfo() {
    cout << "SQLite version is " << sqlite3_libversion()
         << "sourceid version is " << sqlite3_sourceid() << endl;
}



int main(int argc, char* const argv[]) {

    const char* filename = "sqlite.db";
    uint32_t num = 100;
    bool sync = true;
    bool verbose = true;

    SQLite_uBenchmark bench(filename, num, sync, verbose);

    bench.parseCmdline(argc, argv);

    int result = bench.run();

    return (result);
}
