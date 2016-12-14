// Copyright (C) 2015 - 2016 Deutsche Telekom AG.
//
// Author: Razvan Becheriu <razvan.becheriu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CQL_CONNECTION_H
#define CQL_CONNECTION_H

#include <dhcpsrv/database_connection.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <cassandra.h>

#include <boost/scoped_ptr.hpp>

#include <inttypes.h>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Defines a single statement
///
/// @param params_ parameter names
/// @param name_ short description of the query
/// @param text_ text representation of the actual query
struct CqlTaggedStatement {
    const char** params_;
    const char* name_;
    const char* text_;
};

// Define CQL backend version: 2.3
const uint32_t CQL_DRIVER_VERSION_MAJOR = CASS_VERSION_MAJOR;
const uint32_t CQL_DRIVER_VERSION_MINOR = CASS_VERSION_MINOR;

/// Define CQL schema version: 2.0
const uint32_t CQL_SCHEMA_VERSION_MAJOR = 2;
const uint32_t CQL_SCHEMA_VERSION_MINOR = 0;

/// @brief Common CQL connector pool
///
/// Provides common operations for the Cassandra database connection used by
/// CqlLeaseMgr, CqlHostDataSource and CqlSrvConfigMgr. Manages the connection
/// to the Cassandra database and preparing of compiled statements. Its fields
/// are public because they are used (both set and retrieved) in classes that
/// use instances of CqlConnection.
class CqlConnection : public DatabaseConnection {
public:
    /// @brief Constructor
    ///
    /// Initialize CqlConnection object with parameters needed for connection.
    explicit CqlConnection(const ParameterMap& parameters);

    /// @brief Destructor
    virtual ~CqlConnection();

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the CQL statements used
    /// by the CQL backend.
    ///
    /// @throw isc::dhcp::DbOperationError if an operation on the open database
    ///     has failed
    /// @throw isc::InvalidParameter if there is an invalid access in the
    ///     vector. This represents an internal error within the code.
    void prepareStatements(CqlTaggedStatement* statements);

    /// @brief Open database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor. If no parameters are supplied, the default
    /// values will be used (e.g. keyspace 'keatest', port 9042).
    ///
    /// @throw DbOpenError error opening the database
    void openDatabase();

    /// @brief Set consistency
    void setConsistency(bool force, CassConsistency consistency);

    /// @brief Start transaction
    void startTransaction();

    /// @brief Commit Transactions
    ///
    /// This is a no-op for Cassandra.
    virtual void commit();

    /// @brief Rollback Transactions
    ///
    /// This is a no-op for Cassandra.
    virtual void rollback();

    /// @brief Check for errors
    ///
    /// Check for errors on the current database operation.
    void checkStatementError(std::string& error,
                             CassFuture* future,
                             uint32_t stindex,
                             const char* what) const;

    /// @brief Check for errors
    ///
    /// Check for errors on the current database operation.
    void checkStatementError(std::string& error,
                             CassFuture* future,
                             const char* what) const;

    /// @brief CQL connection handle
    CassCluster* cluster_;

    /// @brief CQL session handle
    CassSession* session_;

    /// @brief CQL consistency enabled
    bool force_consistency_;

    /// @brief CQL consistency
    CassConsistency consistency_;

    /// @brief CQL prepared statements - used for faster statement execution
    ///     using bind functionality
    std::vector<const CassPrepared*> statements_;

    /// @brief Pointer to external array of tagged statements containing
    ///     statement name, array of names of bind parameters and text query
    CqlTaggedStatement* tagged_statements_;
};

/// @brief RAII object representing CQL transaction.
///
/// An instance of this class should be created in a scope where multiple
/// INSERT statements should be executed within a single transaction. The
/// transaction is started when the constructor of this class is invoked.
/// The transaction is ended when the @ref CqlTransaction::commit is
/// explicitly called or when the instance of this class is destroyed.
/// The @ref CqlTransaction::commit commits changes to the database
/// and the changes remain in the database when the instance of the
/// class is destroyed. If the class instance is destroyed before the
/// @ref CqlTransaction::commit is called, the transaction is rolled
/// back. The rollback on destruction guarantees that partial data is
/// not stored in the database when there is an error during any
/// of the operations belonging to a transaction.
class CqlTransaction : public boost::noncopyable {
public:
    /// @brief Constructor
    ///
    /// Starts transaction by making a "START TRANSACTION" query.
    ///
    /// @param conn CQL connection to use for the transaction. This connection
    ///     will be later used to commit or rollback changes.
    ///
    /// @throw DbOperationError if "START TRANSACTION" query fails.
    explicit CqlTransaction(CqlConnection& conn);

    /// @brief Destructor
    ///
    /// Rolls back the transaction if changes haven't been committed.
    ~CqlTransaction();

    /// @brief Commits transaction
    ///
    /// Calls @ref CqlConnection::commit()..
    void commit();

private:
    /// @brief Holds reference to the CQL database connection.
    CqlConnection& conn_;

    /// @brief Boolean flag indicating if the transaction has been committed.
    ///
    /// This flag is used in the class destructor to assess if the
    /// transaction should be rolled back.
    bool committed_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // CQL_CONNECTION_H
