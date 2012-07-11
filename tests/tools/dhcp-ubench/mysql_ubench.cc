#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <mysql/mysql.h>

using namespace std;

const char * hostname ="localhost";
const char * user = "root";
const char * passwd = "foobletch";
const char * dbname = "kea";

void failure(MYSQL* conn, const char* operation) {
    stringstream tmp;
    tmp << "Error " << mysql_errno(conn) << " during " << operation
        << ": " << mysql_error(conn);
    throw tmp.str();
}

MYSQL * connect() {
    MYSQL *conn = NULL;

    conn = mysql_init(NULL);
    if (!conn) {
        failure(conn, "initializing MySQL library");
    } else {
        cout << "MySQL library init successful." << endl;
    }

    if (!mysql_real_connect(conn, hostname, user, passwd, dbname, 0, NULL, 0)) {
        failure(conn, "connecting to MySQL server");
    } else {
        cout << "MySQL connection established." << endl;
    }

    string q = "delete from lease4";
    if (mysql_real_query(conn, q.c_str(), strlen(q.c_str()))) {
        failure(conn, "dropping old lease4 entries.");
    }

    return (conn);
}

bool disconnect(MYSQL * conn) {
    if (!conn) {
        throw "NULL MySQL connection pointer.";
    }
    mysql_close(conn);
}



bool createLease4Test(MYSQL * conn, uint32_t num) {
    if (!conn) {
        throw "NULL MySQL connection pointer.";
    }

    uint32_t addr = 0x01000000; // Let's start with 1.0.0.0 address
    char hwaddr[20];
    uint8_t hwaddr_len = 20; // not a real field
    char client_id[128];
    uint8_t client_id_len = 128;
    uint32_t valid_lft = 1000;  // we can use the same value for all leases
    uint32_t recycle_time = 0;  // not supported in any foresable future,
                                // so keep this as 0
    string cltt = "now()"; // timestamp
    uint32_t pool_id = 0; // let's use pools 0-99
    bool fixed = false;   //
    string hostname("foo");      // will generate it dynamically
    bool fqdn_fwd = true; // let's pretend to do AAAA update
    bool fqdn_rev = true; // let's pretend to do PTR update

    for (uint8_t i = 0; i < 20; i++) {
        hwaddr[i] = 65 + i;
    }

    for (uint8_t i = 0; i < 128; i++) {
        client_id[i] = 33 + i;
    }

    for (uint32_t i = 0; i < num; i++) {

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
        end += mysql_real_escape_string(conn, end, hwaddr, hwaddr_len);
        end += sprintf(end,"\',\'");
        end += mysql_real_escape_string(conn, end, client_id, client_id_len);
        end += sprintf(end, "\',%d,%d,'%s',%d,%s,\'%s\',%s,%s);",
                       valid_lft, recycle_time, cltt.str().c_str(),
                       pool_id, (fixed?"true":"false"), hostname.c_str(),
                       (fqdn_fwd?"true":"false"), (fqdn_rev?"true":"false"));
        // lease_id field is set automatically
        // options and comments fields are not set

        unsigned int len = end - query;
        if (mysql_real_query(conn, query, len)) {
            // something failed.
            failure(conn, "INSERT query");
        } else {
            printf(".");
            fflush(stdout);
        };
    }
    printf("\n");
    fflush(stdout);
}

bool searchLease4Test(MYSQL * conn, uint32_t num) {
    if (!conn) {
        throw "NULL MySQL connection pointer.";
    }
}

bool updateLease4Test(MYSQL* conn, uint32_t num) {
    if (!conn) {
        throw "NULL MySQL connection pointer.";
    }
}

bool deleteLease4Test(MYSQL* conn, uint32_t num) {
    if (!conn) {
        throw "NULL MySQL connection pointer.";
    }
}

int main(int argc, const char * argv[]) {

    cout << "MySQL client version is " << mysql_get_client_info() << endl;

    uint32_t num = 100;

    try {
        MYSQL *conn = connect();

        createLease4Test(conn, num);
        searchLease4Test(conn, num);
        updateLease4Test(conn, num);
        deleteLease4Test(conn, num);

        disconnect(conn);

    } catch (const std::string& e) {
        cout << "Failed: " << e << endl;
        return (-1);
    }

    return (0);
}
