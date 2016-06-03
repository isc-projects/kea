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
struct CqlTaggedStatement {
    /// Param name.
    const char** params_;

    /// Short name of the query.
    const char* name_;

    /// Text representation of the actual query.
    const char* text_;
};

/// Defines CQL backend version: 1.0
const uint32_t CQL_CURRENT_VERSION = 1;
const uint32_t CQL_CURRENT_MINOR = 0;

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
    /// Creates the prepared statements for all of the SQL statements used
    /// by the CQL backend.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::InvalidParameter 'index' is not valid for the vector.  This
    ///        represents an internal error within the code.
    void prepareStatements(CqlTaggedStatement *statements);

    /// @brief Open Database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor.
    ///
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbOpenError Error opening the database
    void openDatabase();

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("cassandra"));
    }

    /// @brief Returns name of the database.
    ///
    /// @return database name
    virtual std::string getName() const;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const;

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual std::pair<uint32_t, uint32_t> getVersion() const;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.
    ///
    /// @throw DbOperationError If the commit failed.
    virtual void commit();

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.
    ///
    /// @throw DbOperationError If the rollback failed.
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

    /// CQL connection handle
    CassCluster* cluster_;
    CassSession* session_;
    std::vector<const CassPrepared*> statements_;       ///< Prepared statements
    CqlTaggedStatement *tagged_statements_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // CQL_CONNECTION_H
