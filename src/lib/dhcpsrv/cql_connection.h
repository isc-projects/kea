// Copyright (C) 2015-2017 Deutsche Telekom AG.
//
// Authors: Razvan Becheriu <razvan.becheriu@qualitance.com>
//          Andrei Pavel <andrei.pavel@qualitance.com>
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

#include <cassandra.h>

#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Pair containing major and minor versions
typedef std::pair<uint32_t, uint32_t> VersionPair;

/// @brief Statement index representing the statement name
typedef char const* const StatementTag;

/// @brief Define CQL backend version: 2.3
/// @{
constexpr uint32_t CQL_DRIVER_VERSION_MAJOR = CASS_VERSION_MAJOR;
constexpr uint32_t CQL_DRIVER_VERSION_MINOR = CASS_VERSION_MINOR;
/// @}

/// Define CQL schema version: 2.0
/// @{
constexpr uint32_t CQL_SCHEMA_VERSION_MAJOR = 2u;
constexpr uint32_t CQL_SCHEMA_VERSION_MINOR = 0u;
/// @}

/// @brief Defines a single statement or query
///
/// @param name_ short description of the query
/// @param text_ text representation of the actual query
/// @param prepared_statement_ internal Cassandra object representing the
///     prepared statement
/// @param is_raw_statement_ shows if statement should be executed rawly or with
///     binds
struct CqlTaggedStatement {
    StatementTag name_;
    char const* const text_;
    const CassPrepared* prepared_statement_;
    bool is_raw_statement_;

    /// @brief Constructor
    CqlTaggedStatement(StatementTag name, char const* const text)
        : name_(name), text_(text), prepared_statement_(NULL),
          is_raw_statement_(false) {
    }

    /// @brief Constructor
    CqlTaggedStatement(StatementTag name,
                       char const* const text,
                       bool const& is_raw_statement)
        : name_(name), text_(text), prepared_statement_(NULL),
          is_raw_statement_(is_raw_statement) {
    }
};

/// @brief Hash function for StatementMap keys
///
/// Delegates to std::hash<std::string>.
struct StatementTagHash {
    size_t operator()(StatementTag const& key) const {
        return std::hash<std::string>{}(std::string(key));
    }
};

/// @brief Equality function for StatementMap keys
struct StatementTagEqual {
    bool operator()(StatementTag const& lhs, StatementTag const& rhs) const {
        return std::strcmp(lhs, rhs) == 0;
    }
};

/// @brief Contains all statements.
typedef std::unordered_map<StatementTag,
                           CqlTaggedStatement,
                           StatementTagHash,
                           StatementTagEqual>
    StatementMap;

typedef std::pair<StatementTag, CqlTaggedStatement> StatementMapEntry;

/// @brief Common CQL connector pool
///
/// Provides common operations for the Cassandra database connection used by
/// CqlLeaseMgr, CqlHostDataSource and CqlSrvConfigMgr. Manages the
/// connection
/// to the Cassandra database and preparing of compiled statements. Its
/// fields
/// are public because they are used (both set and retrieved) in classes
/// that
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
    void prepareStatements(StatementMap& statements);

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
    virtual void commit();

    /// @brief Rollback Transactions
    virtual void rollback();

    /// @brief Check for errors
    ///
    /// Check for errors on the current database operation.
    static const std::string
    checkFutureError(const std::string& what,
                     CassFuture* future,
                     StatementTag statement_tag = NULL);

    /// @brief Pointer to external array of tagged statements containing
    ///     statement name, array of names of bind parameters and text query
    StatementMap statements_;

    /// @brief CQL connection handle
    CassCluster* cluster_;

    /// @brief CQL session handle
    CassSession* session_;

    /// @brief CQL consistency
    CassConsistency consistency_;

    // @brief Schema meta information, used for UDTs
    const CassSchemaMeta* schema_meta_;

    /// @brief Keyspace meta information, used for UDTs
    const CassKeyspaceMeta* keyspace_meta_;

    /// @brief CQL consistency enabled
    bool force_consistency_;
};

typedef std::shared_ptr<CqlConnection> CqlConnectionPtr;

}  // namespace dhcp
}  // namespace isc

#endif  // CQL_CONNECTION_H
