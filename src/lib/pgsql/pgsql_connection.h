// Copyright (C) 2016-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef PGSQL_CONNECTION_H
#define PGSQL_CONNECTION_H

#include <asiolink/io_service.h>
#include <pgsql/pgsql_exchange.h>

#include <boost/scoped_ptr.hpp>

#include <vector>
#include <stdint.h>

namespace isc {
namespace db {

/// @brief Define the PostgreSQL backend version.
const uint32_t PGSQL_SCHEMA_VERSION_MAJOR = 14;
const uint32_t PGSQL_SCHEMA_VERSION_MINOR = 0;

// Maximum number of parameters that can be used a statement
// @todo This allows us to use an initializer list (since we can't
// require C++11).  It's unlikely we'd go past this many a single
// statement.
const size_t PGSQL_MAX_PARAMETERS_IN_QUERY = 128;

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
    /// @brief Define the PgSql error state for a null foreign key error.
    static const char NULL_KEY[];

    /// @brief Function invoked to process fetched row.
    typedef std::function<void(PgSqlResult&, int)> ConsumeResultRowFun;

    /// @brief Emit the TLS support warning only once.
    static bool warned_about_tls;

    /// @brief Constructor
    ///
    /// Initialize PgSqlConnection object with parameters needed for connection.
    ///
    /// @param parameters Specify the connection details.
    /// @param io_accessor The IOService accessor function.
    /// @param callback The connection recovery callback.
    PgSqlConnection(const ParameterMap& parameters,
                    IOServiceAccessorPtr io_accessor = IOServiceAccessorPtr(),
                    DbCallback callback = DbCallback())
        : DatabaseConnection(parameters, callback),
          io_service_accessor_(io_accessor), io_service_(),
          transaction_ref_count_(0) {
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

    /// @brief Creates connection string from specified parameters.
    ///
    /// This function is called from the unit tests.
    ///
    /// @return connection string for @c openDatabase.
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbInvalidTimeout when the database timeout is wrong.
    std::string getConnParameters();

private:

    /// @brief Creates connection string from the specified parameters.
    ///
    /// This is an internal implemenation of the @c getConnParameters that
    /// allows for controlling logging. In some cases, a caller can disable
    /// logging warnings to avoid duplication of the log messages emitted
    /// when the invocation is a result of calling  @c getVersion before
    /// opening the connection for the normal server operation.
    ///
    /// @param logging boolean parameter controlling if logging should be
    /// enabled (when true) or disabled (when false).
    ///
    /// @return connection string for @c openDatabase.
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbInvalidTimeout when the database timeout is wrong.
    std::string getConnParametersInternal(bool logging);

public:

    /// @brief Open database with logging.
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor. It logs warnings resulting from the
    /// @c getConnParameters.
    ///
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbOpenError Error opening the database
    void openDatabase();

private:

    /// @brief Internal implementation of the database opening.
    ///
    /// It allows for controlling if the @c getConnParameterInternal function
    /// should log the warnings.
    ///
    /// @param logging boolean parameter controlling if logging should be
    /// enabled (when true) or disabled (when false).
    ///
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbOpenError Error opening the database
    void openDatabaseInternal(bool logging);

public:

    /// @brief Starts new transaction
    ///
    /// This function begins a new transaction by sending the START TRANSACTION
    /// statement to the database. The transaction should be explicitly committed
    /// by calling @c commit() or rolled back by calling @c rollback().
    ///
    /// PostgreSQL does not support nested transactions directly. Issuing a
    /// START TRANSACTION while already in a transaction will cause a warning to
    /// be emitted but otherwise does not alter the state of the current transaction.
    /// In other words, the transaction will still end upon the next COMMIT or
    /// ROLLBACK statement.
    ///
    /// Therefore, this function checks if a transaction has already started and
    /// does not start a new transaction. However, it increments a transaction
    /// reference counter which is later decremented when @c commit() or @c
    /// rollback() is called. When this mechanism is used properly, it
    /// guarantees that nested transactions are not attempted, thus avoiding
    /// unexpected commits or rollbacks of the pending transaction.
    void startTransaction();

    /// @brief Checks if there is a transaction in progress.
    ///
    /// @return true if a transaction has been started, false otherwise.
    bool isTransactionStarted() const;

    /// @brief Commits current transaction
    ///
    /// Commits all pending database operations. On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// When this method is called for a nested transaction it decrements the
    /// transaction reference counter incremented during the call to
    /// @c startTransaction.
    ///
    /// @throw DbOperationError If the commit failed.
    void commit();

    /// @brief Rollbacks current transaction
    ///
    /// Rolls back all pending database operations. On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// When this method is called for a nested transaction it decrements the
    /// transaction reference counter incremented during the call to
    /// @c startTransaction.
    ///
    /// @throw DbOperationError If the rollback failed.
    void rollback();

    /// @brief Creates a savepoint within the current transaction
    ///
    /// Creates a named savepoint within the current transaction.
    ///
    /// @param name name of the savepoint to create.
    ///
    /// @throw InvalidOperation if called outside a transaction.
    /// @throw DbOperationError If the savepoint cannot be created.
    void createSavepoint(const std::string& name);

    /// @brief Rollbacks to the given savepoint
    ///
    /// Rolls back all pending database operations made after the
    /// named savepoint.
    ///
    /// @param name name of the savepoint to which to rollback.
    ///
    /// @throw InvalidOperation if called outside a transaction.
    /// @throw DbOperationError if the rollback failed.
    void rollbackToSavepoint(const std::string& name);

    /// @brief Executes the an SQL statement.
    ///
    /// It executes the given SQL text after first checking the
    /// connection for usability. After the statement is executed
    /// @c checkStatementError() is invoked to ensure we detect
    /// connectivity issues properly.
    /// It is intended to be used to execute utility statements such
    /// as commit, rollback et al, which have no parameters, return no
    /// results, and are not pre-compiled.
    ///
    /// @param sql SQL statement to execute.
    void executeSQL(const std::string& sql);

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
    /// with the server, the function will call startRecoverDbConnection() which
    /// will start the connection recovery.
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
                             PgSqlTaggedStatement& statement);

    /// @brief The recover connection
    ///
    /// This function starts the recover process of the connection.
    ///
    /// @note The recover function must be run on the IO Service thread.
    void startRecoverDbConnection() {
        if (callback_) {
            if (!io_service_ && io_service_accessor_) {
                io_service_ = (*io_service_accessor_)();
                io_service_accessor_.reset();
            }

            if (io_service_) {
                io_service_->post(std::bind(callback_, reconnectCtl()));
            }
        }
    }

    /// @brief Executes a prepared SQL statement.
    ///
    /// It executes the given prepared SQL statement, after checking
    /// for usability and input parameter sanity.  After the statement
    /// is executed @c checkStatementError() is invoked to ensure we detect
    /// connectivity issues properly. Upon successful execution, the
    /// the result set is returned.  It may be used for any form of
    /// prepared SQL statement (e.g query, insert, update, delete...),
    /// with or without input parameters.
    ///
    /// @param statement PgSqlTaggedStatement describing the prepared
    /// statement to execute.
    /// @param in_bindings array of input parameter bindings. If the SQL
    /// statement requires no input arguments, this parameter should either
    /// be omitted or an empty PsqlBindArray should be supplied.
    /// @throw InvalidOperation if the number of parameters expected
    /// by the statement does not match the size of the input bind array.
    PgSqlResultPtr executePreparedStatement(PgSqlTaggedStatement& statement,
                                            const PsqlBindArray& in_bindings
                                            = PsqlBindArray());

    /// @brief Executes SELECT query using prepared statement.
    ///
    /// The statement parameter refers to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement.
    ///
    /// This method executes prepared statement using provided input bindings and
    /// calls @c process_result_row function for each returned row. The
    /// @c process_result_row function is implemented by the caller and should
    /// gather and store each returned row in an external data structure prior.
    ///
    /// @param statement reference to the precompiled tagged statement to execute
    /// @param in_bindings input bindings holding values to substitue placeholders
    /// in the query.
    /// @param process_result_row Pointer to the function to be invoked for each
    /// retrieved row. This function consumes the retrieved data from the
    /// result set.
    void selectQuery(PgSqlTaggedStatement& statement,
                     const PsqlBindArray& in_bindings,
                     ConsumeResultRowFun process_result_row);

    /// @brief Executes INSERT prepared statement.
    ///
    /// The @c statement must refer to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement.
    ///
    /// This method executes prepared statement using provided bindings to
    /// insert data into the database.
    ///
    /// @param statement reference to the precompiled tagged statement to execute
    /// @param in_bindings input bindings holding values to substitue placeholders
    /// in the query.
    void insertQuery(PgSqlTaggedStatement& statement,
                     const PsqlBindArray& in_bindings);


    /// @brief Executes UPDATE or DELETE prepared statement and returns
    /// the number of affected rows.
    ///
    /// The @c statement must refer to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement.
    ///
    /// @param statement reference to the precompiled tagged statement to execute
    /// @param in_bindings Input bindings holding values to substitute placeholders
    /// in the query.
    ///
    /// @return Number of affected rows.
    uint64_t updateDeleteQuery(PgSqlTaggedStatement& statement,
                               const PsqlBindArray& in_bindings);

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

private:

    /// @brief Convenience function parsing and setting an integer parameter,
    /// if it exists.
    ///
    /// If the parameter is not present, this function doesn't change the @c value.
    /// Otherwise, it tries to convert the parameter to the type @c T. Finally,
    /// it checks if the converted number is within the specified range.
    ///
    /// @param name Parameter name.
    /// @param min Expected minimal value.
    /// @param max Expected maximal value.
    /// @param [out] value Reference to a value returning the parsed parameter.
    /// @tparam T Parameter type.
    /// @throw BadValue if the parameter is not a valid number or if it is out
    /// of range.
    template<typename T>
    void setIntParameterValue(const std::string& name, int64_t min, int64_t max, T& value);

public:

    /// @brief Accessor function which returns the IOService that can be used to
    /// recover the connection.
    ///
    /// This accessor is used to lazy retrieve the IOService when the connection
    /// is lost. It is useful to retrieve it at a later time to support hook
    /// libraries which create managers on load and set IOService later on by
    /// using the dhcp4_srv_configured and dhcp6_srv_configured hooks.
    IOServiceAccessorPtr io_service_accessor_;

    /// @brief IOService object, used for all ASIO operations.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief Reference counter for transactions.
    ///
    /// It precludes starting and committing nested transactions. PostgreSQL
    /// logs but ignores START TRANSACTIONs (or BEGINs) issued from within an
    /// ongoing transaction. We do not want to start new transactions when one
    /// is already in progress.
    int transaction_ref_count_;
};

/// @brief Defines a pointer to a PgSqlConnection
typedef boost::shared_ptr<PgSqlConnection> PgSqlConnectionPtr;

} // end of isc::db namespace
} // end of isc namespace

#endif // PGSQL_CONNECTION_H
