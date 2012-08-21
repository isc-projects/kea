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
#include "benchmark.h"

/// @brief MySQL micro-benchmark.
///
/// That is a specific backend implementation. See \ref uBenchmark class for
/// detailed explanation of its operations. This class uses MySQL as database
/// backend.
class MySQL_uBenchmark: public uBenchmark {
public:

    /// @brief The sole MySQL micro-benchmark constructor
    ///
    /// To avoid influence of network performance, it is highly recommended
    /// to run MySQL engine on the same host as benchmark. Thus hostname
    /// is likely to be "localhost". Make sure that the selected database
    /// is already created and that it follows expected schema. See mysql.schema
    /// and isc-dhcp-perf-guide.html for details.
    ///
    /// Synchronous operation means using InnDB, async is MyISAM.
    ///
    /// @param hostname Name of the hostname to connect to
    /// @param user usename used during MySQL connection
    /// @param pass password used during MySQL connection
    /// @param db name of the database to connect to
    /// @param num_iterations number of iterations for basic operations
    /// @param sync synchronous or asynchronous database writes
    /// @param verbose should extra information be logged?
    MySQL_uBenchmark(const std::string& hostname, const std::string& user,
                     const std::string& pass, const std::string& db,
                     uint32_t num_iterations, bool sync,
                     bool verbose);

    /// @brief Prints MySQL version info.
    virtual void printInfo();

    /// @brief Opens connection to the MySQL database.
    virtual void connect();

    /// @brief Closes connection to the MySQL database.
    virtual void disconnect();

    /// @brief Creates new leases.
    ///
    /// See uBenchmark::createLease4Test() for detailed explanation.
    virtual void createLease4Test();

    /// @brief Searches for existing leases.
    ///
    /// See uBenchmark::searchLease4Test() for detailed explanation.
    virtual void searchLease4Test();

    /// @brief Updates existing leases.
    ///
    /// See uBenchmark::updateLease4Test() for detailed explanation.
    virtual void updateLease4Test();

    /// @brief Deletes existing leases.
    ///
    /// See uBenchmark::deleteLease4Test() for detailed explanation.
    virtual void deleteLease4Test();

protected:
    /// @brief Used to report any database failures.
    ///
    /// Compared to its base version in uBenchmark class, this one logs additional
    /// MySQL specific information using mysql_errno() and mysql_error() functions.
    /// The outcome is the same: exception is thrown.
    void failure(const char* operation);

    /// Handle to MySQL database connection.
    MYSQL* conn_;
};
