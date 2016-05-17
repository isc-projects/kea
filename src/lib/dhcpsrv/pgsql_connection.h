// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef PGSQL_CONNECTION_H
#define PGSQL_CONNECTION_H

#include <dhcpsrv/database_connection.h>

#include <libpq-fe.h>
#include <boost/scoped_ptr.hpp>

#include <vector>


namespace isc {
namespace dhcp {

// Maximum number of parameters that can be used a statement
// @todo This allows us to use an initializer list (since we don't
// require C++11).  It's unlikely we'd go past in a single statement.
const size_t PGSQL_MAX_PARAMETERS_IN_QUERY = 32;

/// @brief  Defines a Postgresql SQL statement
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

/// @brief Constants for PostgreSQL data types
/// This are defined by PostreSQL in <catalog/pg_type.h>, but including
/// this file is extrordinarily convoluted, so we'll use these to fill-in.
const size_t OID_NONE = 0;   // PostgreSQL infers proper type
const size_t OID_BOOL = 16;
const size_t OID_BYTEA = 17;
const size_t OID_INT8 = 20;  // 8 byte int
const size_t OID_INT2 = 21;  // 2 byte int
const size_t OID_TIMESTAMP = 1114;
const size_t OID_VARCHAR = 1043;

//@}

/// @brief RAII wrapper for Posgtresql Result sets
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

class PgSqlResult {
public:
    /// @brief Constructor
    ///
    /// Store the pointer to the result set to being fetched.
    ///
    PgSqlResult(PGresult *result) : result_(result)
    {}

    /// @brief Destructor
    ///
    /// Frees the result set
    ~PgSqlResult() {
        if (result_)  {
            PQclear(result_);
        }
    }

    /// @brief Conversion Operator
    ///
    /// Allows the PgSqlResult object to be passed as the context argument to
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
};


/// @brief PgSql Handle Holder
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
    /// Initialize PgSql
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

/// @brief Common PgSql Connector Pool
///
/// This class provides common operations for PgSql database connection
/// used by both PgSqlLeaseMgr and PgSqlHostDataSource. It manages connecting
/// to the database and preparing compiled statements. Its fields are
/// public, because they are used (both set and retrieved) in classes
/// that use instances of PgSqlConnection.
class PgSqlConnection : public DatabaseConnection {
public:
    /// @brief Defines the PgSql error state for a duplicate key error
    static const char DUPLICATE_KEY[];

    /// @brief Constructor
    ///
    /// Initialize PgSqlConnection object with parameters needed for connection.
    PgSqlConnection(const ParameterMap& parameters)
        : DatabaseConnection(parameters) {
    }

    /// @brief Destructor
    virtual ~PgSqlConnection();

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
    void prepareStatement(const PgSqlTaggedStatement& statement);

    /// @brief Open Database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor.
    ///
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbOpenError Error opening the database
    void openDatabase();

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations. On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// @throw DbOperationError If the commit failed.
    void commit();

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations. On databases that don't
    /// support transactions, this is a no-op.
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
    bool compareError(PGresult*& r, const char* error_state);

    /// @brief Checks result of the r object
    ///
    /// This function is used to determine whether or not the SQL statement
    /// execution succeeded, and in the event of failures, decide whether or
    /// not the failures are recoverable.
    ///
    /// If the error is recoverable, the method will throw a DbOperationError.
    /// In the error is deemed unrecoverable, such as a loss of connectivity
    /// with the server, this method will log the error and call exit(-1);
    ///
    /// @todo Calling exit() is viewed as a short term solution for Kea 1.0.
    /// Two tickets are likely to alter this behavior, first is #3639, which
    /// calls for the ability to attempt to reconnect to the database. The
    /// second ticket, #4087 which calls for the implementation of a generic,
    /// FatalException class which will propagate outward.
    ///
    /// @param r result of the last PostgreSQL operation
    /// @param statement - tagged statement that was executed
    ///
    /// @throw isc::dhcp::DbOperationError Detailed PostgreSQL failure
    void checkStatementError(PGresult*& r, PgSqlTaggedStatement& statement) const;

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



}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // PGSQL_CONNECTION_H
