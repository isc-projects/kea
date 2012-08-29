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

/// @brief Micro-benchmark base class.
///
/// This class represents an abstract DHCP database backend benchmark.
/// It is not intended to be used directly, but serves as a common
/// denominator for specific backend benchmarks that are derived from
/// it. Currently there are at least 3 benchmarks implemented that
/// take advantage of it:
/// - MySQL (MySQL_uBenchmark)
/// - SQLite (SQLite_uBenchmark)
/// - memfile (memfile_uBenchmark)
class uBenchmark {
public:

    /// @brief the sole constructor, used by all derivated benchmarks
    ///
    /// @param iterations number of iterations of each step (insert, search,
    ///                   update, delete)
    /// @param dbname name of the database (that is backend-specific, either
    ///               filename or DB name)
    /// @param sync sync or async test mode
    /// @param verbose should extra logging be enabled?
    /// @param host some backends (currently only MySQL) need this (optional)
    /// @param username some backends (currently only MySQL) need this (optional)
    /// @param pass some backends (currently only MySQL) need this (optional)
    uBenchmark(uint32_t iterations, const std::string& dbname,
               bool sync, bool verbose,
               const std::string& host = "",
               const std::string& username = "",
               const std::string& pass = "");

    /// @brief Prints version information about specific backend.
    ///
    /// The implementation is provided by the DB-specific class.
    virtual void printInfo() = 0;

    /// @brief Opens a connection to the database.
    ///
    /// The implementation is provided by the DB-specific class.
    virtual void connect() = 0;

    /// @brief Closes connection to the database.
    ///
    /// The implementation is provided by the DB-specific class.
    virtual void disconnect() = 0;

    /// @brief Benchmarks IPv4 address lease creation.
    ///
    /// That benchmark method will be called first.
    /// It is expected to create specific number of leases,
    /// as specified by \ref num_ parameter. Following
    /// methods (searchLease4Test(), updateLease4Test(),
    /// and deleteLease4Test()) assume that lease creation
    /// is successful. The benchmark is expected to create leases
    /// starting from BASE_ADDR4 and ending on BASE_ADDR4 + num_.
    ///
    /// The implementation is provided by the DB-specific class.
    virtual void createLease4Test() = 0;

    /// @brief Benchmarks IPv4 address lease search.
    ///
    /// This is the second benchmark in a series of four.
    /// It is called after createLease4Test(), so it expects that the
    /// database is populated with at least \ref num_ leases.
    /// It repeats search for a lease num_ times.
    ///
    /// The algorithm randomly picks a lease with \ref hitratio_ (typically 90%)
    /// chance of finding a lease. During typical DHCP operation the server
    /// sometimes wants to check if specific lease is assigned or not and the
    /// lease is sometimes not present (e.g. when randomly trying to pick a new
    /// lease for a new client or doing confirm). Although rather unlikely,
    /// cases when searching for non-existing leases may be more costly,
    /// thus should be modelled.
    ///
    /// The implementation is provided by the DB-specific class.
    virtual void searchLease4Test() = 0;

    /// @brief Benchmarks IPv4 address lease update.
    ///
    /// This is the third benchmark in a series of four.
    /// It is called after createLease4Test(), so it expects that the
    /// database is populated with at least \ref num_ leases.
    ///
    /// In a normal DHCP operation, search and update operations are used
    /// together, but for the benchmarking purposes they are executed
    /// separately here. Once a lease is found, it is being updated. Typically
    /// the update is just changing lease expiration timers, so that is what
    /// the test does. It exploits the fact that there are num_ leases
    /// in the database, so it picks randomly an address from
    /// BASE_ADDR4 ... BASE_ADDR4 + num_ range and has a guarantee for the lease
    /// to be present.
    ///
    /// The implementation is provided by the DB-specific class.
    virtual void updateLease4Test() = 0;

    /// @brief Benchmarks IPv4 address lease removal.
    ///
    /// This is the last benchmark in a series of four.
    /// It is called after createLease4Test(), so it expects that the
    /// database is populated with at least \ref num_ leases.
    ///
    /// It is expected to iteratively delete all num_ leases from
    /// the database.
    ///
    /// The implementation is provided by the DB-specific class.
    virtual void deleteLease4Test() = 0;

    /// @brief Utility function for reporting errors.
    ///
    /// Benchmarks should call that function when something goes wrong.
    /// details of the problem must be passed as a parameter. As the benchmark
    /// is not designed to recover from errors, reporting an error aborts
    /// benchmark execution.
    ///
    /// @param operation description of the operation that caused failure
    virtual void failure(const char* operation);

    /// @brief Prints elapsed time of a specific operation
    ///
    /// This method prints out elapsed time of a specific benchmark, together
    /// with additional statistics.
    ///
    /// @param operation name of the operation (usually create, search, update, delete)
    /// @param num number or iterations (used for statistics)
    /// @param before timestamp before execution
    /// @param after timestamp after execution
    void printClock(const std::string& operation, uint32_t num,
                    const struct timespec& before,
                    const struct timespec& after);

    /// @brief Main benchmark execution routine
    ///
    /// This method calls create, search, update and delete benchmarks
    /// and measures appropriate timestamps in ts_ table.
    ///
    /// @return 0 if the run was successful, negative value if detected errors
    int run();

    /// @brief parses command-line parameters
    ///
    /// This method parses command-line parameters and sets up appropriate
    /// values. It is ok to pass argc, argv from main() here.
    ///
    /// This method may not return if -h (help) was specified or invalid
    /// arguments are passed. Appropriate error and help will be displayed
    /// and the program will terminate.
    ///
    /// @param argc number of arguments
    /// @param argv array to the arguments
    void parseCmdline(int argc, char* const argv[]);

protected:
    /// @brief prints out command-line help (list of parameters + version)
    void usage();

    /// @brief a wrapper around OS-specific method for getting time
    struct timespec getTime();

    /// Number of operations (e.g. insert lease num times)
    uint32_t num_;

    /// Synchronous or asynchonous mode?
    bool sync_;

    /// Should the test print out extra information?
    bool verbose_;

    // DB parameters
    std::string hostname_; // used by MySQL only
    std::string user_;     // used by MySQL only
    std::string passwd_;   // used by MySQL only
    std::string dbname_;   // used by MySQL, SQLite and memfile

    /// @brief hit ratio for search test (must be between 0.0 and 1.0)
    ///
    /// This parameter is used in search benchmark. The formula causes the
    /// search to find something a lease in 90% cases of hit ratio is 0.9.
    float hitratio_;

    /// benchmarks must generate the leases starting from 1.0.0.0 address
    const static uint32_t BASE_ADDR4 = 0x01000000;

    /// five timestamps (1 at the beginning and 4 after each step)
    struct timespec ts_[5];

    /// should compiled statements be used?
    bool compiled_stmt_;
};

#endif
