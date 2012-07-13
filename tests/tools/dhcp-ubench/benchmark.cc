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
#include "benchmark.h"

using namespace std;

uBenchmark::uBenchmark(uint32_t iterations)
 :Num_(iterations) {
    memset(ts, 0, sizeof(ts));
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

    cout << "Operation " << operation << " repeated " << num << " times took "
         << tv_sec << " seconds, " << tv_nsec/1000 << " us, 1 operation took "
         << oneoper << "us (or " << (1000000/oneoper) << " oper/sec)" << endl;

}

int uBenchmark::run() {

    srandom(time(NULL));

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

    print_clock("Create leases4", Num_, ts[0], ts[1]);
    print_clock("Search leases4", Num_, ts[1], ts[2]);
    print_clock("Update leases4", Num_, ts[2], ts[3]);
    print_clock("Delete leases4", Num_, ts[3], ts[4]);

    return (0);
}
