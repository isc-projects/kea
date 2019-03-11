// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

#include <database/database_connection.h>

#include <cassandra.h>

#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace isc {
namespace db {

/// @brief Pair containing major and minor versions
/// @todo: This is already defined in lease_mgr.h. Need to have one
/// definition. May need to move it if necessary.
typedef std::pair<uint32_t, uint32_t> VersionPair;

/// @brief Statement index representing the statement name
typedef char const* const StatementTag;

/// @brief Define CQL backend version. The CASS_VERSION_* constants
///        are defined in a header provided by cpp-driver.
/// @{
constexpr uint32_t CQL_DRIVER_VERSION_MAJOR = CASS_VERSION_MAJOR;
constexpr uint32_t CQL_DRIVER_VERSION_MINOR = CASS_VERSION_MINOR;
/// @}

/// Define CQL schema version: 3.0
/// @{
constexpr uint32_t CQL_SCHEMA_VERSION_MAJOR = 3u;
constexpr uint32_t CQL_SCHEMA_VERSION_MINOR = 0u;
/// @}

/// @brief Defines a single statement or query
struct CqlTaggedStatement {

    /// Short description of the query
    StatementTag name_;

    /// Text representation of the actual query
    char const* const text_;

    /// Internal Cassandra object representing the prepared statement
    const CassPrepared* prepared_statement_;

    /// Should the statement be executed raw or with binds?
    bool is_raw_;

    /// @brief Constructor
    /// @param name brief name of the query
    /// @param text text (CQL) representation of the query
    CqlTaggedStatement(StatementTag name, char const* const text)
        : name_(name), text_(text), prepared_statement_(NULL), is_raw_(false) {
    }

    /// @brief Constructor
    /// @param name brief name of the query
    /// @param text text (CQL) representation of the query
    /// @param is_raw should the statement be executed raw?
    CqlTaggedStatement(StatementTag name, char const* const text, bool const& is_raw)
        : name_(name), text_(text), prepared_statement_(NULL), is_raw_(is_raw) {
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

/// @brief A container for all statements.
typedef std::unordered_map<StatementTag, CqlTaggedStatement,
                           StatementTagHash, StatementTagEqual> StatementMap;

/// @brief A type for a single entry on the statements map
typedef std::pair<StatementTag, CqlTaggedStatement> StatementMapEntry;

/// @brief Common CQL connector pool
///
/// Provides common operations for the Cassandra database connection used by
/// CqlLeaseMgr, CqlHostDataSource and CqlSrvConfigMgr. Manages the connection
/// to the Cassandra database and preparing of compiled statements. Its fields
/// are public because they are used (both set and retrieved) in classes that
/// use instances of CqlConnection.
class CqlConnection : public db::DatabaseConnection {
public:
    /// @brief Constructor
    ///
    /// Initialize CqlConnection object with parameters needed for connection.
    /// @param parameters specify the connection details (username, ip addresses etc.)
    explicit CqlConnection(const ParameterMap& parameters);

    /// @brief Destructor
    virtual ~CqlConnection();

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the CQL statements used
    /// by the CQL backend.
    /// @param statements statements to be prepared
    ///
    /// @throw isc::db::DbOperationError if an operation on the open database
    ///     has failed
    /// @throw isc::InvalidParameter if there is an invalid access in the
    ///     vector. This represents an internal error within the code.
    void prepareStatements(StatementMap& statements);

    /// @brief Open database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor. If no parameters are supplied, the default
    /// values will be used. The parameters supported as as follows (default
    /// values specified in parentheses):
    /// - keyspace: name of the database to which to connect (keatest)
    /// - contact-points: IP addresses of the nodes to connect to (127.0.0.1)
    /// - consistency: consistency level (quorum)
    /// - serial-consistency: serial consistency level (serial)
    /// - port: The TCP port to use (9042)
    /// - user - credentials to use when connecting (no username)
    /// - password - credentials to use when connecting (no password)
    /// - reconnect-wait-time 2000
    /// - connect-timeout 5000
    /// - request-timeout 12000
    /// - tcp-keepalive no
    /// - tcp-nodelay no
    ///
    /// @throw DbOpenError error opening the database
    void openDatabase();

    /// @brief Set consistency
    void setConsistency(bool force,
                        CassConsistency consistency,
                        CassConsistency serial_consistency);

    /// @brief Start transaction
    void startTransaction();

    /// @brief Commit Transactions
    virtual void commit();

    /// @brief Rollback Transactions
    virtual void rollback();

    /// @brief parse Consistency value
    static CassConsistency parseConsistency(std::string value);

    /// @brief Check for errors
    ///
    /// Check for errors on the current database operation and returns text
    /// description of what happened. In case of success, also returns
    /// some logging friendly text.
    ///
    /// @param what text description of the operation
    /// @param future the structure that holds the status of operation
    /// @param statement_tag statement that was used (optional)
    /// @return text description of the error
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

    /// @brief CQL serial consistency
    CassConsistency serial_consistency_;

    // @brief Schema meta information, used for UDTs
    const CassSchemaMeta* schema_meta_;

    /// @brief Keyspace meta information, used for UDTs
    const CassKeyspaceMeta* keyspace_meta_;

    /// @brief CQL consistency enabled
    bool force_consistency_;
};

typedef std::shared_ptr<CqlConnection> CqlConnectionPtr;

}  // namespace db
}  // namespace isc

#endif  // CQL_CONNECTION_H
