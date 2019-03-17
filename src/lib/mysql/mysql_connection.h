// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <database/db_log.h>
#include <exceptions/exceptions.h>
#include <mysql/mysql_binding.h>
#include <mysql/mysql_constants.h>
#include <boost/scoped_ptr.hpp>
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>
#include <functional>
#include <vector>
#include <stdint.h>

namespace isc {
namespace db {


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
    /// Push a call to mysql_library_end() at exit time.
    /// Initialize MySql and store the associated context object.
    ///
    /// @throw DbOpenError Unable to initialize MySql handle.
    MySqlHolder() : mysql_(mysql_init(NULL)) {
        if (!atexit_) {
            atexit([]{ mysql_library_end(); });
            atexit_ = true;
        }
        if (mysql_ == NULL) {
            isc_throw(db::DbOpenError, "unable to initialize MySQL");
        }
    }

    /// @brief Destructor
    ///
    /// Frees up resources allocated by the initialization of MySql.
    ~MySqlHolder() {
        if (mysql_ != NULL) {
            mysql_close(mysql_);
        }
        // @note Moved the call to mysql_library_end() to atexit.
    }

    /// @brief Conversion Operator
    ///
    /// Allows the MySqlHolder object to be passed as the context argument to
    /// mysql_xxx functions.
    operator MYSQL*() const {
        return (mysql_);
    }

private:
    static bool atexit_; ///< Flag to call atexit once.

    MYSQL* mysql_;       ///< Initialization context
};

/// @brief Forward declaration to @ref MySqlConnection.
class MySqlConnection;

/// @brief RAII object representing MySQL transaction.
///
/// An instance of this class should be created in a scope where multiple
/// INSERT statements should be executed within a single transaction. The
/// transaction is started when the constructor of this class is invoked.
/// The transaction is ended when the @ref MySqlTransaction::commit is
/// explicitly called or when the instance of this class is destroyed.
/// The @ref MySqlTransaction::commit commits changes to the database
/// and the changes remain in the database when the instance of the
/// class is destroyed. If the class instance is destroyed before the
/// @ref MySqlTransaction::commit is called, the transaction is rolled
/// back. The rollback on destruction guarantees that partial data is
/// not stored in the database when there is an error during any
/// of the operations belonging to a transaction.
///
/// The default MySQL backend configuration enables 'autocommit'.
/// Starting a transaction overrides 'autocommit' setting for this
/// particular transaction only. It does not affect the global 'autocommit'
/// setting for the database connection, i.e. all modifications to the
/// database which don't use transactions will still be auto committed.
class MySqlTransaction : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// Starts transaction by making a "START TRANSACTION" query.
    ///
    /// @param conn MySQL connection to use for the transaction. This
    /// connection will be later used to commit or rollback changes.
    ///
    /// @throw DbOperationError if "START TRANSACTION" query fails.
    MySqlTransaction(MySqlConnection& conn);

    /// @brief Destructor.
    ///
    /// Rolls back the transaction if changes haven't been committed.
    ~MySqlTransaction();

    /// @brief Commits transaction.
    void commit();

private:

    /// @brief Holds reference to the MySQL database connection.
    MySqlConnection& conn_;

    /// @brief Boolean flag indicating if the transaction has been committed.
    ///
    /// This flag is used in the class destructor to assess if the
    /// transaction should be rolled back.
    bool committed_;
};


/// @brief Common MySQL Connector Pool
///
/// This class provides common operations for MySQL database connection
/// used by both MySqlLeaseMgr and MySqlHostDataSource. It manages connecting
/// to the database and preparing compiled statements. Its fields are
/// public, because they are used (both set and retrieved) in classes
/// that use instances of MySqlConnection.
class MySqlConnection : public db::DatabaseConnection {
public:

    /// @brief Function invoked to process fetched row.
    typedef std::function<void(MySqlBindingCollection&)> ConsumeResultFun;

    /// @brief Constructor
    ///
    /// Initialize MySqlConnection object with parameters needed for connection.
    MySqlConnection(const ParameterMap& parameters)
        : DatabaseConnection(parameters) {
    }

    /// @brief Destructor
    virtual ~MySqlConnection();

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
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::InvalidParameter 'index' is not valid for the vector.
    void prepareStatement(uint32_t index, const char* text);

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the SQL statements used
    /// by the MySQL backend.
    ///
    /// @param start_statement Pointer to the first statement in range of the
    /// statements to be compiled.
    /// @param end_statement Pointer to the statement marking end of the
    /// range of statements to be compiled. This last statement is not compiled.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::InvalidParameter 'index' is not valid for the vector.  This
    ///        represents an internal error within the code.
    void prepareStatements(const TaggedStatement* start_statement,
                           const TaggedStatement* end_statement);

    /// @brief Clears prepared statements and text statements.
    void clearStatements();

    /// @brief Open Database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor.
    ///
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbOpenError Error opening the database
    void openDatabase();

    ///@{
    /// The following methods are used to convert between times and time
    /// intervals stored in the Lease object, and the times stored in the
    /// database.  The reason for the difference is because in the DHCP server,
    /// the cltt (Client Time Since Last Transmission) is the natural data; in
    /// the lease file - which may be read by the user - it is the expiry time
    /// of the lease.

    /// @brief Convert time_t value to database time.
    ///
    /// @param input_time A time_t value representing time.
    /// @param output_time Reference to MYSQL_TIME object where converted time
    ///        will be put.
    static
    void convertToDatabaseTime(const time_t input_time, MYSQL_TIME& output_time);

    /// @brief Convert Lease Time to Database Times
    ///
    /// Within the DHCP servers, times are stored as client last transmit time
    /// and valid lifetime.  In the database, the information is stored as
    /// valid lifetime and "expire" (time of expiry of the lease).  They are
    /// related by the equation:
    ///
    /// - expire = client last transmit time + valid lifetime
    ///
    /// This method converts from the times in the lease object into times
    /// able to be added to the database.
    ///
    /// @param cltt Client last transmit time
    /// @param valid_lifetime Valid lifetime
    /// @param expire Reference to MYSQL_TIME object where the expiry time of
    ///        the lease will be put.
    ///
    /// @throw isc::BadValue if the sum of the calculated expiration time is
    /// greater than the value of @c LeaseMgr::MAX_DB_TIME.
    static
    void convertToDatabaseTime(const time_t cltt, const uint32_t valid_lifetime,
            MYSQL_TIME& expire);

    /// @brief Convert Database Time to Lease Times
    ///
    /// Within the database, time is stored as "expire" (time of expiry of the
    /// lease) and valid lifetime.  In the DHCP server, the information is
    /// stored client last transmit time and valid lifetime.  These are related
    /// by the equation:
    ///
    /// - client last transmit time = expire - valid_lifetime
    ///
    /// This method converts from the times in the database into times
    /// able to be inserted into the lease object.
    ///
    /// @param expire Reference to MYSQL_TIME object from where the expiry
    ///        time of the lease is taken.
    /// @param valid_lifetime lifetime of the lease.
    /// @param cltt Reference to location where client last transmit time
    ///        is put.
    static
    void convertFromDatabaseTime(const MYSQL_TIME& expire,
            uint32_t valid_lifetime, time_t& cltt);
    ///@}

    /// @brief Starts Transaction
    void startTransaction();

    /// @brief Executes SELECT query using prepared statement.
    ///
    /// The statement index must point to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement. The size of
    /// the @c out_bindings must match the number of selected columns. The
    /// output bindings must be created and must encapsulate values of
    /// the appropriate type, e.g. string, uint32_t etc.
    ///
    /// This method executes prepared statement using provided bindings and
    /// calls @c process_result function for each returned row. The
    /// @c process_result function is implemented by the caller and should
    /// gather and store each returned row in an external data structure prior
    /// to returning because the values in the @c out_bindings will be
    /// overwritten by the values of the next returned row when this function
    /// is called again.
    ///
    /// @tparam StatementIndex Type of the statement index enum.
    ///
    /// @param index Index of the query to be executed.
    /// @param in_bindings Input bindings holding values to substitue placeholders
    /// in the query.
    /// @param [out] out_bindings Output bindings where retrieved data will be
    /// stored.
    /// @param process_result Pointer to the function to be invoked for each
    /// retrieved row. This function consumes the retrieved data from the
    /// output bindings.
    template<typename StatementIndex>
    void selectQuery(const StatementIndex& index,
                     const MySqlBindingCollection& in_bindings,
                     MySqlBindingCollection& out_bindings,
                     ConsumeResultFun process_result) {
        // Extract native input bindings.
        std::vector<MYSQL_BIND> in_bind_vec;
        for (MySqlBindingPtr in_binding : in_bindings) {
            in_bind_vec.push_back(in_binding->getMySqlBinding());
        }

        int status = 0;
        if (!in_bind_vec.empty()) {
            // Bind parameters to the prepared statement.
            status = mysql_stmt_bind_param(statements_[index], &in_bind_vec[0]);
            checkError(status, index, "unable to bind parameters for select");
        }

        // Bind variables that will receive results as well.
        std::vector<MYSQL_BIND> out_bind_vec;
        for (MySqlBindingPtr out_binding : out_bindings) {
            out_bind_vec.push_back(out_binding->getMySqlBinding());
        }
        if (!out_bind_vec.empty()) {
            status = mysql_stmt_bind_result(statements_[index], &out_bind_vec[0]);
            checkError(status, index, "unable to bind result parameters for select");
        }

        // Execute query.
        status = mysql_stmt_execute(statements_[index]);
        checkError(status, index, "unable to execute");

        status = mysql_stmt_store_result(statements_[index]);
        checkError(status, index, "unable to set up for storing all results");

        // Fetch results.
        MySqlFreeResult fetch_release(statements_[index]);
        while ((status = mysql_stmt_fetch(statements_[index])) ==
               MLM_MYSQL_FETCH_SUCCESS) {
            try {
                // For each returned row call user function which should
                // consume the row and copy the data to a safe place.
                process_result(out_bindings);

            } catch (const std::exception& ex) {
                // Rethrow the exception with a bit more data.
                isc_throw(BadValue, ex.what() << ". Statement is <" <<
                          text_statements_[index] << ">");
            }
        }

        // How did the fetch end?
        // If mysql_stmt_fetch return value is equal to 1 an error occurred.
        if (status == MLM_MYSQL_FETCH_FAILURE) {
            // Error - unable to fetch results
            checkError(status, index, "unable to fetch results");

        } else if (status == MYSQL_DATA_TRUNCATED) {
            // Data truncated - throw an exception indicating what was at fault
            isc_throw(DataTruncated, text_statements_[index]
                      << " returned truncated data");
        }
    }

    /// @brief Executes INSERT prepared statement.
    ///
    /// The statement index must point to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement.
    ///
    /// This method executes prepared statement using provided bindings to
    /// insert data into the database.
    ///
    /// @tparam StatementIndex Type of the statement index enum.
    ///
    /// @param index Index of the query to be executed.
    /// @param in_bindings Input bindings holding values to substitue placeholders
    /// in the query.
    template<typename StatementIndex>
    void insertQuery(const StatementIndex& index,
                     const MySqlBindingCollection& in_bindings) {
        std::vector<MYSQL_BIND> in_bind_vec;
        for (MySqlBindingPtr in_binding : in_bindings) {
            in_bind_vec.push_back(in_binding->getMySqlBinding());
        }

        // Bind the parameters to the statement
        int status = mysql_stmt_bind_param(statements_[index], &in_bind_vec[0]);
        checkError(status, index, "unable to bind parameters");

        // Execute the statement
        status = mysql_stmt_execute(statements_[index]);

        if (status != 0) {
            // Failure: check for the special case of duplicate entry.
            if (mysql_errno(mysql_) == ER_DUP_ENTRY) {
                isc_throw(DuplicateEntry, "Database duplicate entry error");
            }
            checkError(status, index, "unable to execute");
        }
    }

    /// @brief Executes UPDATE or DELETE prepared statement and returns
    /// the number of affected rows.
    ///
    /// The statement index must point to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement.
    ///
    /// @tparam StatementIndex Type of the statement index enum.
    ///
    /// @param index Index of the query to be executed.
    /// @param in_bindings Input bindings holding values to substitue placeholders
    /// in the query.
    ///
    /// @return Number of affected rows.
    template<typename StatementIndex>
    uint64_t updateDeleteQuery(const StatementIndex& index,
                               const MySqlBindingCollection& in_bindings) {
        std::vector<MYSQL_BIND> in_bind_vec;
        for (MySqlBindingPtr in_binding : in_bindings) {
            in_bind_vec.push_back(in_binding->getMySqlBinding());
        }

        // Bind the parameters to the statement
        int status = mysql_stmt_bind_param(statements_[index], &in_bind_vec[0]);
        checkError(status, index, "unable to bind parameters");

        // Execute the statement
        status = mysql_stmt_execute(statements_[index]);

        if (status != 0) {
            // Failure: check for the special case of duplicate entry.
            if ((mysql_errno(mysql_) == ER_DUP_ENTRY)
#ifdef ER_FOREIGN_DUPLICATE_KEY
                || (mysql_errno(mysql_) == ER_FOREIGN_DUPLICATE_KEY)
#endif
#ifdef ER_FOREIGN_DUPLICATE_KEY_WITH_CHILD_INFO
                || (mysql_errno(mysql_) == ER_FOREIGN_DUPLICATE_KEY_WITH_CHILD_INFO)
#endif
#ifdef ER_FOREIGN_DUPLICATE_KEY_WITHOUT_CHILD_INFO
                || (mysql_errno(mysql_) == ER_FOREIGN_DUPLICATE_KEY_WITHOUT_CHILD_INFO)
#endif
                ) {
                isc_throw(DuplicateEntry, "Database duplicate entry error");
            }
            checkError(status, index, "unable to execute");
        }

        // Let's return how many rows were affected.
        return (static_cast<uint64_t>(mysql_stmt_affected_rows(statements_[index])));
    }


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

    /// @brief Check Error and Throw Exception
    ///
    /// Virtually all MySQL functions return a status which, if non-zero,
    /// indicates an error.  This function centralizes the error checking
    /// code.
    ///
    /// It is used to determine whether or not the function succeeded, and
    /// in the event of failures, decide whether or not those failures are
    /// recoverable.
    ///
    /// If the error is recoverable, the function will throw a DbOperationError.
    /// If the error is deemed unrecoverable, such as a loss of connectivity
    /// with the server, the function will call invokeDbLostCallback(). If the
    /// invocation returns false then either there is no callback registered
    /// or the callback has elected not to attempt to reconnect, and exit(-1)
    /// is called;
    ///
    /// If the invocation returns true, this indicates the calling layer will
    /// attempt recovery, and the function throws a DbOperationError to allow
    /// the caller to error handle the failed db access attempt.
    ///
    /// @param status Status code: non-zero implies an error
    /// @param index Index of statement that caused the error
    /// @param what High-level description of the error
    ///
    /// @tparam Enumeration representing index of a statement to which an
    /// error pertains.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    template<typename StatementIndex>
    void checkError(const int status, const StatementIndex& index,
                    const char* what) const {
        if (status != 0) {
            switch(mysql_errno(mysql_)) {
                // These are the ones we consider fatal. Remember this method is
                // used to check errors of API calls made subsequent to successfully
                // connecting.  Errors occurring while attempting to connect are
                // checked in the connection code. An alternative would be to call
                // mysql_ping() - assuming autoreconnect is off. If that fails
                // then we know connection is toast.
            case CR_SERVER_GONE_ERROR:
            case CR_SERVER_LOST:
            case CR_OUT_OF_MEMORY:
            case CR_CONNECTION_ERROR:
                DB_LOG_ERROR(db::MYSQL_FATAL_ERROR)
                    .arg(what)
                    .arg(text_statements_[static_cast<int>(index)])
                    .arg(mysql_error(mysql_))
                    .arg(mysql_errno(mysql_));

                // If there's no lost db callback or it returns false,
                // then we're not attempting to recover so we're done
                if (!invokeDbLostCallback()) {
                    exit (-1);
                }

                // We still need to throw so caller can error out of the current
                // processing.
                isc_throw(db::DbOperationError,
                          "fatal database errror or connectivity lost");
            default:
                // Connection is ok, so it must be an SQL error
                isc_throw(db::DbOperationError, what << " for <"
                          << text_statements_[static_cast<int>(index)]
                          << ">, reason: "
                          << mysql_error(mysql_) << " (error code "
                          << mysql_errno(mysql_) << ")");
            }
        }
    }

    /// @brief Prepared statements
    ///
    /// This field is public, because it is used heavily from MySqlConnection
    /// and will be from MySqlHostDataSource.
    std::vector<MYSQL_STMT*> statements_;

    /// @brief Raw text of statements
    ///
    /// This field is public, because it is used heavily from MySqlConnection
    /// and will be from MySqlHostDataSource.
    std::vector<std::string> text_statements_;

    /// @brief MySQL connection handle
    ///
    /// This field is public, because it is used heavily from MySqlConnection
    /// and will be from MySqlHostDataSource.
    MySqlHolder mysql_;
};

}; // end of isc::db namespace
}; // end of isc namespace

#endif // MYSQL_CONNECTION_H
