// Copyright (C) 2012-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include <dhcpsrv/database_connection.h>
#include <boost/scoped_ptr.hpp>
#include <mysql.h>
#include <vector>
#include <stdint.h>

namespace isc {
namespace dhcp {

/// @name MySQL constants.
///
//@{

/// @brief MySQL false value.
extern const my_bool MLM_FALSE;

/// @brief MySQL true value.
extern const my_bool MLM_TRUE;

/// @brief MySQL fetch success code.
extern const int MLM_MYSQL_FETCH_SUCCESS;

/// @brief MySQL fetch failure code.
extern const int MLM_MYSQL_FETCH_FAILURE;

//@}

/// @name Current database schema version values.
//@{
const uint32_t CURRENT_VERSION_VERSION = 4;
const uint32_t CURRENT_VERSION_MINOR = 2;

//@}

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
class MySqlConnection : public DatabaseConnection {
public:

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
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::InvalidParameter 'index' is not valid for the vector.
    void prepareStatement(uint32_t index, const char* text);

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the SQL statements used
    /// by the MySQL backend.
    /// @param tagged_statements an array of statements to be compiled
    /// @param num_statements number of statements in tagged_statements
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

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // MYSQL_CONNECTION_H
