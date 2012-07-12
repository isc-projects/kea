#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <mysql/mysql.h>

using namespace std;

class uBenchmark {
public:
    uBenchmark(uint32_t numInterations);

    virtual void printInfo() = 0;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void createLease4Test() = 0;
    virtual void searchLease4Test() = 0;
    virtual void updateLease4Test() = 0;
    virtual void deleteLease4Test() = 0;

    virtual void failure(const char* operation);

    void print_clock(const std::string& operation, uint32_t num,
                     const struct timespec& before,
                     const struct timespec& after);

    int run();

protected:
    uint32_t Num_; // number of operations (e.g. insert lease num times)

    // five timestamps (1 at the beginning and 4 after each step)
    struct timespec ts[5];
};

uBenchmark::uBenchmark(uint32_t iterations)
 :Num_(iterations) {

}

void uBenchmark::failure(const char* operation) {
    cout << "Error during " << operation << endl;
    throw string(operation);
}

void uBenchmark::print_clock(const std::string& operation, uint32_t num,
                 const struct timespec& before,
                 const struct timespec& after) {
    long int tv_sec = after.tv_sec - before.tv_sec;

    long int tv_nsec = after.tv_nsec - before.tv_nsec;

    cout << "after.tv_nsec=" << after.tv_nsec
         << " before.tv_nsec=" << before.tv_nsec << endl;

    if (tv_nsec < 0) {
        tv_sec++;
        tv_nsec += 1000000000; // 10^9
    }

    double oneoper = (tv_nsec/1000 + tv_sec*1000000)/num;

    cout << "Operation " << operation << " repeated " << num << " times took "
         << tv_sec << " seconds, " << tv_nsec/1000 << " us, 1 operation took "
         << oneoper << "us (or " << (1000000/oneoper) << " oper/sec)" << endl;

}

int uBenchmark::run() {

    try {
        connect();

        clock_gettime(CLOCK_REALTIME, &ts[0]);

        createLease4Test();
        clock_gettime(CLOCK_REALTIME, &ts[1]);

        searchLease4Test();
        clock_gettime(CLOCK_REALTIME, &ts[2]);

        updateLease4Test();
        clock_gettime(CLOCK_REALTIME, &ts[3]);

        deleteLease4Test();
        clock_gettime(CLOCK_REALTIME, &ts[4]);

        disconnect();

    } catch (const std::string& e) {
        cout << "Failed: " << e << endl;
        return (-1);
    }

    print_clock("Create leases4 ", Num_, ts[0], ts[1]);
    // print_clock("Search leases4 ", num, ts[1], ts[2]);
    // print_clock("Update leases4 ", num, ts[2], ts[3]);
    // print_clock("Delete leases4 ", num, ts[3], ts[4]);

    return (0);
}

class MySQL_uBenchmark: public uBenchmark {
public:
    MySQL_uBenchmark(const string& hostname, const string& user,
                     const string& passwd, const string& db, 
                     uint32_t num_iterations);

    virtual void printInfo();
    virtual void connect();
    virtual void disconnect();
    virtual void createLease4Test();
    virtual void searchLease4Test();
    virtual void updateLease4Test();
    virtual void deleteLease4Test();

protected:
    void failure(const char* operation);

    std::string Hostname_;
    std::string User_;
    std::string Pass_;
    std::string DB_;
    MYSQL * Conn_;
};


MySQL_uBenchmark::MySQL_uBenchmark(const string& hostname, const string& user,
                                   const string& pass, const string& db,
                                   uint32_t num_iterations)
    :uBenchmark(num_iterations), Hostname_(hostname), User_(user), 
     Pass_(pass), DB_(db), Conn_(NULL) {

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

    cout << "hostname=" << Hostname_ << ", user=" << User_
         << "pass=" << Pass_ << " db=" << DB_ << endl;

    if (!mysql_real_connect(Conn_, Hostname_.c_str(), User_.c_str(), 
                            Pass_.c_str(), DB_.c_str(), 0, NULL, 0)) {
        failure("connecting to MySQL server");
    } else {
        cout << "MySQL connection established." << endl;
    }

    string q = "delete from lease4;";
    if (mysql_real_query(Conn_, q.c_str(), strlen(q.c_str()))) {
        failure("dropping old lease4 entries.");
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

    for (uint32_t i = 0; i < Num_; i++) {

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
            printf(".");
        };
    }
    printf("\n");
}

void MySQL_uBenchmark::searchLease4Test() {
    if (!Conn_) {
        throw "Not connected to MySQL server.";
    }
}

void MySQL_uBenchmark::updateLease4Test() {
    if (!Conn_) {
        throw "Not connected to MySQL server.";
    }
}

void MySQL_uBenchmark::deleteLease4Test() {
    if (!Conn_) {
        throw "Not connected to MySQL server.";
    }
}

void MySQL_uBenchmark::printInfo() {
    cout << "MySQL client version is " << mysql_get_client_info() << endl;
}


int main(int argc, const char * argv[]) {

    const char * hostname ="localhost";
    const char * user = "root";
    const char * passwd = "foobletch";
    const char * dbname = "kea";
    uint32_t num = 100;

    MySQL_uBenchmark bench(hostname, user, passwd, dbname, num);

    int result = bench.run();

    return (result);
}
