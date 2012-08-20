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
#include <stdlib.h>
#include <string.h>
#include <boost/lexical_cast.hpp>
#include "benchmark.h"

using namespace std;

uBenchmark::uBenchmark(uint32_t iterations, const std::string& dbname,
                       bool sync /*= false*/, bool verbose /*= true*/,
                       const std::string& host /* = "" */,
                       const std::string& user /* = "" */,
                       const std::string& pass /* = "" */)
    :num_(iterations), sync_(sync), verbose_(verbose),
     hostname_(host), user_(user), passwd_(pass), dbname_(dbname)
{
    /// @todo: convert this to user-configurable parameter
    hitratio_ = 0.9f;

    memset(ts_, 0, sizeof(ts_));
}

void uBenchmark::usage() {
    cout << "This is a benchmark designed to measure expected performance" << endl;
    cout << "of several backends. This backend identifies itself as:" << endl;
    printInfo();

    cout << endl << "Possible command-line parameters:" << endl;
    cout << " -h - help (you are reading this)" << endl;
    cout << " -m hostname - specifies MySQL server to connect (MySQL backend only)" << endl;
    cout << " -u username - specifies MySQL user name (MySQL backend only)" << endl;
    cout << " -p password - specifies MySQL passwod (MySQL backend only)" << endl;
    cout << " -f name - database or filename (MySQL, SQLite and memfile)" << endl;
    cout << " -n integer - number of test repetitions (MySQL, SQLite and memfile)" << endl;
    cout << " -s yes|no - synchronous/asynchronous operation (MySQL, SQLite and memfile)" << endl;
    cout << " -v yes|no - verbose mode (MySQL, SQLite and memfile)" << endl;

    exit(EXIT_FAILURE);
}

void uBenchmark::parseCmdline(int argc, char* const argv[]) {
    int ch;

    while ((ch = getopt(argc, argv, "hm:u:p:f:n:s:v:")) != -1) {
        switch (ch) {
        case 'h':
            usage();
        case 'm':
            hostname_ = string(optarg);
            break;
        case 'u':
            user_ = string(optarg);
            break;
        case 'p':
            passwd_ = string(optarg);
            break;
        case 'f':
            dbname_ = string(optarg);
            break;
        case 'n':
            try {
                num_ = boost::lexical_cast<int>(optarg);
            } catch (const boost::bad_lexical_cast &) {
                cerr << "Failed to iterations (-n option)." << endl;
                usage();
            }
            break;
        case 's':
            sync_ = !strcasecmp(optarg, "yes") || !strcmp(optarg, "1");
            break;
        case 'v':
            verbose_ = !strcasecmp(optarg, "yes") || !strcmp(optarg, "1");
            break;
        default:
            usage();
        }
    }
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

    if (tv_nsec < 0) {
        tv_sec--;
        tv_nsec += 1000000000; // 10^9
    }

    double oneoper = (tv_nsec/1000 + tv_sec*1000000)/num;

    cout << operation << " repeated " << num << " times took "
         << tv_sec << " s, " << tv_nsec/1000 << " us, 1 operation took "
         << oneoper << "us (or " << (1000000/oneoper) << " oper/sec)" << endl;

}

int uBenchmark::run() {

    cout << "Starting test. Parameters:" << endl
         << "Number of iterations : " << num_ << endl
         << "Sync/async           : " << (sync_ ? "sync" : "async") << endl
         << "Verbose              : " << (verbose_ ? "verbose" : "quiet") << endl
         << "Database name        : " << dbname_ << endl
         << "MySQL hostname       : " << hostname_ << endl
         << "MySQL username       : " << user_ << endl
         << "MySQL password       : " << passwd_ << endl << endl;


    srandom(time(NULL));

    try {
        connect();

        clock_gettime(CLOCK_REALTIME, &ts_[0]);

        createLease4Test();
        clock_gettime(CLOCK_REALTIME, &ts_[1]);

        searchLease4Test();
        clock_gettime(CLOCK_REALTIME, &ts_[2]);

        updateLease4Test();
        clock_gettime(CLOCK_REALTIME, &ts_[3]);

        deleteLease4Test();
        clock_gettime(CLOCK_REALTIME, &ts_[4]);

        disconnect();

    } catch (const std::string& e) {
        cout << "Failed: " << e << endl;
        return (-1);
    }

    print_clock("Create leases4", num_, ts_[0], ts_[1]);
    print_clock("Search leases4", num_, ts_[1], ts_[2]);
    print_clock("Update leases4", num_, ts_[2], ts_[3]);
    print_clock("Delete leases4", num_, ts_[3], ts_[4]);

    return (0);
}
