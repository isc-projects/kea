// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include <dhcp/hwaddr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/data_source.h>
#include <boost/scoped_ptr.hpp>
#include <mysql.h>

#include <time.h>

namespace isc {
namespace dhcp {

/// @brief MySQL True/False constants
///
/// Declare typed values so as to avoid problems of data conversion.  These
/// are local to the file but are given the prefix MLM (MySql Lease Manager) to
/// avoid any likely conflicts with variables in header files named TRUE or
/// FALSE.
extern const my_bool MLM_FALSE;
extern const my_bool MLM_TRUE;

/// @brief Fetch and Release MySQL Results
///
/// When a MySQL statement is expected, to fetch the results the function
/// mysql_stmt_fetch() must be called.  As well as getting data, this
/// allocates internal state.  Subsequent calls to mysql_stmt_fetch can be
/// made, but when all the data is retrieved, mysql_stmt_free_result must be
/// called to free up the resources allocated.
///
/// Created prior to the first fetch, this class's destructor calls
/// mysql_stmt_free_result, so eliminating the need for an explicit release
/// in the method calling mysql_stmt_free_result.  In this way, it guarantees
/// that the resources are released even if the MySqlLeaseMgr method concerned
/// exits via an exception.

class MySqlFreeResult {
public:

    /// @brief Constructor
    ///
    /// Store the pointer to the statement for which data is being fetched.
    ///
    /// Note that according to the MySQL documentation, mysql_stmt_free_result
    /// only releases resources if a cursor has been allocated for the
    /// statement.  This implies that it is a no-op if none have been.  Either
    /// way, any error from mysql_stmt_free_result is ignored. (Generating
    /// an exception is not much help, as it will only confuse things if the
    /// method calling mysql_stmt_fetch is exiting via an exception.)
    MySqlFreeResult(MYSQL_STMT* statement) : statement_(statement)
    {}

    /// @brief Destructor
    ///
    /// Frees up fetch context if a fetch has been successfully executed.
    ~MySqlFreeResult() {
        (void) mysql_stmt_free_result(statement_);
    }

private:
    MYSQL_STMT*     statement_;     ///< Statement for which results are freed
};

/// @brief MySQL Selection Statements
///
/// Each statement is associated with an index, which is used to reference the
/// associated prepared statement.

struct TaggedStatement {
    uint32_t index;
    const char* text;
};

/// @brief MySQL Handle Holder
///
/// Small RAII object for safer initialization, will close the database
/// connection upon destruction.  This means that if an exception is thrown
/// during database initialization, resources allocated to the database are
/// guaranteed to be freed.
///
/// It makes no sense to copy an object of this class.  After the copy, both
/// objects would contain pointers to the same MySql context object.  The
/// destruction of one would invalid the context in the remaining object.
/// For this reason, the class is declared noncopyable.
class MySqlHolder : public boost::noncopyable {
public:

    /// @brief Constructor
    ///
    /// Initialize MySql and store the associated context object.
    ///
    /// @throw DbOpenError Unable to initialize MySql handle.
    MySqlHolder() : mysql_(mysql_init(NULL)) {
        if (mysql_ == NULL) {
            isc_throw(DbOpenError, "unable to initialize MySQL");
        }
    }

    /// @brief Destructor
    ///
    /// Frees up resources allocated by the initialization of MySql.
    ~MySqlHolder() {
        if (mysql_ != NULL) {
            mysql_close(mysql_);
        }
        // The library itself shouldn't be needed anymore
        mysql_library_end();
    }

    /// @brief Conversion Operator
    ///
    /// Allows the MySqlHolder object to be passed as the context argument to
    /// mysql_xxx functions.
    operator MYSQL*() const {
        return (mysql_);
    }

private:
    MYSQL* mysql_;      ///< Initialization context
};

/// @brief Common MySQL Connector Pool
///
///	This class provides common operations for MySQL database connection
///	used by both MySqlLeaseMgr and MySqlHostDataSource. It manages connecting
///	to the database and preparing compiled statements.

class MySqlConnection : public DataSource {
public:

    /// @brief Constructor
    ///
    /// Initialize MySqlConnection object with parameters needed for connection.
    MySqlConnection(const ParameterMap& parameters)
        : DataSource(parameters) {
    }

    /// @brief Destructor
    virtual ~MySqlConnection() {
    }

    /// @brief Prepare Single Statement
    ///
    /// Creates a prepared statement from the text given and adds it to the
    /// statements_ vector at the given index.
    ///
    /// @param index Index into the statements_ vector into which the text
    ///        should be placed.  The vector must be big enough for the index
    ///        to be valid, else an exception will be thrown.
    /// @param text Text of the SQL statement to be prepared.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::InvalidParameter 'index' is not valid for the vector.
    void prepareStatement(uint32_t index, const char* text);

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the SQL statements used
    /// by the MySQL backend.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::InvalidParameter 'index' is not valid for the vector.  This
    ///        represents an internal error within the code.
    void prepareStatements(const TaggedStatement tagged_statements[],
                           size_t num_statements);

    /// @brief Open Database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor.
    ///
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbOpenError Error opening the database
    void openDatabase();

    std::vector<MYSQL_STMT*> statements_;       ///< Prepared statements
    std::vector<std::string> text_statements_;  ///< Raw text of statements

protected:

    MySqlHolder mysql_;

};



}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // MYSQL_CONNECTION_H
