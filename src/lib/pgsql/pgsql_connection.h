// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef PGSQL_CONNECTION_H
#define PGSQL_CONNECTION_H

#include <database/database_connection.h>

#include <libpq-fe.h>
#include <boost/scoped_ptr.hpp>

#include <vector>
#include <stdint.h>

namespace isc {
namespace db {

/// @brief Define PostgreSQL backend version: 6.0
const uint32_t PG_SCHEMA_VERSION_MAJOR = 6;
const uint32_t PG_SCHEMA_VERSION_MINOR = 0;

// Maximum number of parameters that can be used a statement
// @todo This allows us to use an initializer list (since we can't
// require C++11).  It's unlikely we'd go past this many a single
// statement.
const size_t PGSQL_MAX_PARAMETERS_IN_QUERY = 32;

/// @brief Define a PostgreSQL statement.
///
/// Each statement is associated with an index, which is used to reference the
/// associated prepared statement.
struct PgSqlTaggedStatement {
    /// Number of parameters for a given query
    int nbparams;

    /// @brief OID types
    ///
    /// Specify parameter types. See /usr/include/postgresql/catalog/pg_type.h.
    /// For some reason that header does not export those parameters.
    /// Those OIDs must match both input and output parameters.
    const Oid types[PGSQL_MAX_PARAMETERS_IN_QUERY];

    /// Short name of the query.
    const char* name;

    /// Text representation of the actual query.
    const char* text;
};

/// @{
/// @brief Constants for PostgreSQL data types
/// These are defined by PostgreSQL in <catalog/pg_type.h>, but including
/// this file is extraordinarily convoluted, so we'll use these to fill-in.
/// @{
const size_t OID_NONE = 0;   // PostgreSQL infers proper type
const size_t OID_BOOL = 16;
const size_t OID_BYTEA = 17;
const size_t OID_INT8 = 20;  // 8 byte int
const size_t OID_INT2 = 21;  // 2 byte int
const size_t OID_INT4 = 23;  // 4 byte int
const size_t OID_TEXT = 25;
const size_t OID_VARCHAR = 1043;
const size_t OID_TIMESTAMP = 1114;
/// @}

/// @brief RAII wrapper for PostgreSQL Result sets
///
/// When a Postgresql statement is executed, the results are returned
/// in pointer allocated structure, PGresult*. Data and status information
/// are accessed via calls to functions such as PQgetvalue() which require
/// the results pointer.  In order to ensure this structure is freed, any
/// invocation of Psql function which returns a PGresult* (e.g. PQexec and

/// class. Examples:
/// {{{
///       PgSqlResult r(PQexec(conn_, "ROLLBACK"));
/// }}}
///
/// This eliminates the need for an explicit release via, PQclear() and
/// guarantees that the resources are released even if the an exception is
/// thrown.

class PgSqlResult : public boost::noncopyable {
public:
    /// @brief Constructor
    ///
    /// Store the pointer to the result set to being fetched.  Set row
    /// and column counts for convenience.
    ///
    /// @param result - pointer to the Postgresql client layer result
    /// If the value of is NULL, row and col values will be set to -1.
    /// This allows PgSqlResult to be passed into statement error
    /// checking.
    PgSqlResult(PGresult *result);

    /// @brief Destructor
    ///
    /// Frees the result set
    ~PgSqlResult();

    /// @brief Returns the number of rows in the result set.
    int getRows() const {
        return (rows_);
    }

    /// @brief Returns the number of columns in the result set.
    int getCols() const {
        return (cols_);
    }

    /// @brief Determines if a row index is valid
    ///
    /// @param row index to range check
    ///
    /// @throw DbOperationError if the row index is out of range
    void rowCheck(int row) const;

    /// @brief Determines if a column index is valid
    ///
    /// @param col index to range check
    ///
    /// @throw DbOperationError if the column index is out of range
    void colCheck(int col) const;

    /// @brief Determines if both a row and column index are valid
    ///
    /// @param row index to range check
    /// @param col index to range check
    ///
    /// @throw DbOperationError if either the row or column index
    /// is out of range
    void rowColCheck(int row, int col) const;

    /// @brief Fetches the name of the column in a result set
    ///
    /// Returns the column name of the column from the result set.
    /// If the column index is out of range it will return the
    /// string "Unknown column:<index>"
    ///
    /// @param col index of the column name to fetch
    /// @return string containing the name of the column
    /// This method is exception safe.
    std::string getColumnLabel(const int col) const;

    /// @brief Conversion Operator
    ///
    /// Allows the PgSqlResult object to be passed as the result set argument to
    /// PQxxxx functions.
    operator PGresult*() const {
        return (result_);
    }

    /// @brief Boolean Operator
    ///
    /// Allows testing the PgSqlResult object for emptiness: "if (result)"
    operator bool() const {
        return (result_);
    }

private:
    PGresult*     result_;     ///< Result set to be freed
    int rows_;   ///< Number of rows in the result set
    int cols_;   ///< Number of columns in the result set
};


/// @brief Postgresql connection handle Holder
///
/// Small RAII object for safer initialization, will close the database
/// connection upon destruction.  This means that if an exception is thrown
/// during database initialization, resources allocated to the database are
/// guaranteed to be freed.
///
/// It makes no sense to copy an object of this class.  After the copy, both
/// objects would contain pointers to the same PgSql context object.  The
/// destruction of one would invalid the context in the remaining object.
/// For this reason, the class is declared noncopyable.
class PgSqlHolder : public boost::noncopyable {
public:

    /// @brief Constructor
    ///
    /// Sets the Postgresql API connector handle to NULL.
    ///
    PgSqlHolder() : pgconn_(NULL) {
    }

    /// @brief Destructor
    ///
    /// Frees up resources allocated by the connection.
    ~PgSqlHolder() {
        if (pgconn_ != NULL) {
            PQfinish(pgconn_);
        }
    }

    /// @brief Sets the connection to the value given
    ///
    /// @param connection - pointer to the Postgresql connection instance
    void setConnection(PGconn* connection) {
        if (pgconn_ != NULL) {
            // Already set? Release the current connection first.
            // Maybe this should be an error instead?
            PQfinish(pgconn_);
        }

        pgconn_ = connection;
    }

    /// @brief Conversion Operator
    ///
    /// Allows the PgSqlHolder object to be passed as the context argument to
    /// PQxxxx functions.
    operator PGconn*() const {
        return (pgconn_);
    }

    /// @brief Boolean Operator
    ///
    /// Allows testing the connection for emptiness: "if (holder)"
    operator bool() const {
        return (pgconn_);
    }

private:
    PGconn* pgconn_;      ///< Postgresql connection
};

/// @brief Forward declaration to @ref PgSqlConnection.
class PgSqlConnection;

/// @brief RAII object representing a PostgreSQL transaction.
///
/// An instance of this class should be created in a scope where multiple
/// INSERT statements should be executed within a single transaction. The
/// transaction is started when the constructor of this class is invoked.
/// The transaction is ended when the @ref PgSqlTransaction::commit is
/// explicitly called or when the instance of this class is destroyed.
/// The @ref PgSqlTransaction::commit commits changes to the database.
/// If the class instance is destroyed before @ref PgSqlTransaction::commit
/// has been called, the transaction is rolled back. The rollback on
/// destruction guarantees that partial data is not stored in the database
/// when an error occurs during any of the operations within a transaction.
///
/// By default PostgreSQL performs a commit following each statement which
/// alters the database (i.e. "autocommit"). Starting a transaction
/// stops autocommit for the connection until the transaction is ended by
/// either commit or rollback. Other connections are unaffected.
class PgSqlTransaction : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// Starts transaction by executing the SQL statement: "START TRANSACTION"
    ///
    /// @param conn PostgreSQL connection to use for the transaction. This
    /// connection will be later used to commit or rollback changes.
    ///
    /// @throw DbOperationError if statement execution fails
    PgSqlTransaction(PgSqlConnection& conn);

    /// @brief Destructor.
    ///
    /// If the transaction has not been committed, it is rolled back
    /// by executing the SQL statement: "ROLLBACK"
    ///
    /// @throw DbOperationError if statement execution fails
    ~PgSqlTransaction();

    /// @brief Commits transaction.
    ///
    /// Commits all changes made during the transaction by executing the
    /// SQL statement: "COMMIT"
    ///
    /// @throw DbOperationError if statement execution fails
    void commit();

private:

    /// @brief Holds reference to the PostgreSQL database connection.
    PgSqlConnection& conn_;

    /// @brief Boolean flag indicating if the transaction has been committed.
    ///
    /// This flag is used in the class destructor to assess if the
    /// transaction should be rolled back.
    bool committed_;
};

/// @brief Common PgSql Connector Pool
///
/// This class provides common operations for PgSql database connection
/// used by both PgSqlLeaseMgr and PgSqlHostDataSource. It manages connecting
/// to the database and preparing compiled statements. Its fields are
/// public, because they are used (both set and retrieved) in classes
/// that use instances of PgSqlConnection.
class PgSqlConnection : public db::DatabaseConnection {
public:
    /// @brief Define the PgSql error state for a duplicate key error.
    static const char DUPLICATE_KEY[];

    /// @brief Constructor
    ///
    /// Initialize PgSqlConnection object with parameters needed for connection.
    PgSqlConnection(const ParameterMap& parameters)
        : DatabaseConnection(parameters) {
    }

    /// @brief Destructor
    virtual ~PgSqlConnection();

    /// @brief Get the schema version.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    static std::pair<uint32_t, uint32_t>
    getVersion(const ParameterMap& parameters);

    /// @brief Prepare Single Statement
    ///
    /// Creates a prepared statement from the text given and adds it to the
    /// statements_ vector at the given index.
    ///
    /// @param statement SQL statement to be prepared.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    void prepareStatement(const PgSqlTaggedStatement& statement);

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the SQL statements used
    /// by the PostgreSQL backend.
    ///
    /// @param start_statement Pointer to the first statement in range of the
    /// statements to be compiled.
    /// @param end_statement Pointer to the statement marking end of the
    /// range of statements to be compiled. This last statement is not compiled.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    void prepareStatements(const PgSqlTaggedStatement* start_statement,
                           const PgSqlTaggedStatement* end_statement);

    /// @brief Open Database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor.
    ///
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbOpenError Error opening the database
    void openDatabase();

    /// @brief Start a transaction
    ///
    /// Starts a transaction.
    ///
    /// @throw DbOperationError If the transaction start failed.
    void startTransaction();

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.
    ///
    /// @throw DbOperationError If the commit failed.
    void commit();

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.
    ///
    /// @throw DbOperationError If the rollback failed.
    void rollback();

    /// @brief Checks a result set's SQL state against an error state.
    ///
    /// @param r result set to check
    /// @param error_state error state to compare against
    ///
    /// @return True if the result set's SQL state equals the error_state,
    /// false otherwise.
    bool compareError(const PgSqlResult& r, const char* error_state);

    /// @brief Checks result of the r object
    ///
    /// This function is used to determine whether or not the SQL statement
    /// execution succeeded, and in the event of failures, decide whether or
    /// not the failures are recoverable.
    ///
    /// If the error is recoverable, the function will throw a DbOperationError.
    /// If the error is deemed unrecoverable, such as a loss of connectivity
    /// with the server, the function will call invokeDbLostCallback(). If the
    /// invocation returns false then either there is no callback registered
    /// or the callback has elected not to attempt to reconnect, and a
    /// DbUnrecoverableError is thrown.
    ///
    /// If the invocation returns true, this indicates the calling layer will
    /// attempt recovery, and the function throws a DbOperationError to allow
    /// the caller to error handle the failed db access attempt.
    ///
    /// @param r result of the last PostgreSQL operation
    /// @param statement - tagged statement that was executed
    ///
    /// @throw isc::db::DbOperationError Detailed PostgreSQL failure
    void checkStatementError(const PgSqlResult& r,
                             PgSqlTaggedStatement& statement) const;

    /// @brief PgSql connection handle
    ///
    /// This field is public, because it is used heavily from PgSqlLeaseMgr
    /// and from PgSqlHostDataSource.
    PgSqlHolder conn_;

    /// @brief Conversion Operator
    ///
    /// Allows the PgConnection object to be passed as the context argument to
    /// PQxxxx functions.
    operator PGconn*() const {
        return (conn_);
    }

    /// @brief Boolean Operator
    ///
    /// Allows testing the PgConnection for initialized connection
    operator bool() const {
        return (conn_);
    }

};

}; // end of isc::db namespace
}; // end of isc namespace

#endif // PGSQL_CONNECTION_H
