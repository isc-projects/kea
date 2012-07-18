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

#include <string>
#include <stdint.h>

#ifndef BENCHMARK_H
#define BENCHMARK_H

class uBenchmark {
public:
    uBenchmark(uint32_t iterations, const std::string& dbname,
               bool sync, bool verbose,
               const std::string& host = "",
               const std::string& username = "",
               const std::string& pass = "");

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

    bool parseCmdline(int args, char* const argv[]);

protected:
    void usage();

    uint32_t Num_; // number of operations (e.g. insert lease num times)

    bool Sync_;  // synchronous or asynchonous mode?
    bool Verbose_;
    std::string Hostname_;// used by MySQL only
    std::string User_;    // used by MySQL only
    std::string Passwd_;  // used by MySQL only
    std::string DBName_;  // used by MySQL, SQLite and memfile

    const static uint32_t BASE_ADDR4 = 0x01000000; // let's start from 1.0.0.0 address

    // five timestamps (1 at the beginning and 4 after each step)
    struct timespec ts[5];
};

#endif
