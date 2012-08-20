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

/// @brief SQLite benchmark
///
/// That is a specific backend implementation. See \ref uBenchmark class for
/// detailed explanation of its operations. This class uses SQLite as DB backend.
class SQLite_uBenchmark: public uBenchmark {
public:

    /// @brief The sole SQL benchmark constructor
    ///
    /// DB file must be present and appropriate database schema must
    /// be used. See sqlite.schema script and isc-dhcp-perf-guide.html
    /// for details.
    ///
    /// sync flag affects "PRAGMA synchronous" to be ON or OFF.
    ///
    /// @param filename name of the SQLite DB file. Must be present.
    /// @param num_iterations number of iterations of basic lease operations
    /// @param sync should the operations be synchronous or not?
    /// @param verbose would you like extra details be logged?
    SQLite_uBenchmark(const std::string& filename,
                      uint32_t num_iterations,
                      bool sync, bool verbose);

    /// @brief Prints SQLite version info.
    virtual void printInfo();

    /// @brief Opens connection to the SQLite database.
    virtual void connect();

    /// @brief Closes connection to the SQLite database.
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

    /// Handle to SQLite database connection.
    sqlite3 *DB_;
};
