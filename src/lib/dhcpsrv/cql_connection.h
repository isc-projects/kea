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
#include <inttypes.h>
#include <cassandra.h>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief  Defines a single query
///
/// @param params_ Bind parameter names
/// @param name_ Short name of the query.
/// @param text_ Text representation of the actual query.
struct CqlTaggedStatement {
    const char** params_;
    const char* name_;
    const char* text_;
};

// Defines CQL backend version: 2.3
const uint32_t CQL_DRIVER_VERSION_MAJOR = CASS_VERSION_MAJOR;
const uint32_t CQL_DRIVER_VERSION_MINOR = CASS_VERSION_MINOR;

/// Defines CQL schema version: 1.0
const uint32_t CQL_SCHEMA_VERSION_MAJOR = 1;
const uint32_t CQL_SCHEMA_VERSION_MINOR = 0;

class CqlConnection : public DatabaseConnection {
public:

    /// @brief Constructor
    ///
    /// Initialize CqlConnection object with parameters needed for connection.
    CqlConnection(const ParameterMap& parameters);

    /// @brief Destructor
    virtual ~CqlConnection();

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the CQL statements used
    /// by the CQL backend.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::InvalidParameter 'index' is not valid for the vector. This
    ///        represents an internal error within the code.
    void prepareStatements(CqlTaggedStatement *statements);

    /// @brief Open Database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor. If no parameters are supplied, the default
    /// values will be used (keyspace keatest).
    ///
    /// @throw DbOpenError Error opening the database
    void openDatabase();

    /// @brief Commit Transactions
    ///
    /// This is a no-op for Cassandra.
    virtual void commit();

    /// @brief Rollback Transactions
    ///
    /// This is a no-op for Cassandra.
    virtual void rollback();

    /// @brief Check Error
    ///
    /// Chech error for current database operation.
    void checkStatementError(std::string& error, CassFuture* future,
        uint32_t stindex, const char* what) const;

    /// @brief Check Error
    ///
    /// Chech error for current database operation.
    void checkStatementError(std::string& error, CassFuture* future,
        const char* what) const;

    /// @brief CQL connection handle
    CassCluster* cluster_;

    /// @brief CQL session handle
    CassSession* session_;

    /// @brief CQL prepared statements - used for faster statement execution using
    /// bind functionality
    std::vector<const CassPrepared*> statements_;

    /// @brief Pointer to external array of tagged statements containing statement
    /// name, array of names of bind parameters and text query
    CqlTaggedStatement* tagged_statements_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // CQL_CONNECTION_H
