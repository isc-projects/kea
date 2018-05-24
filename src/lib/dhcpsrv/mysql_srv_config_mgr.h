// Copyright (C) 2016-2018 Deutsche Telekom AG.
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

#ifndef MYSQL_CONFIGURATION_MGR_H
#define MYSQL_CONFIGURATION_MGR_H

#include <dhcpsrv/mysql_connection.h>
#include <dhcpsrv/srv_config_mgr.h>

#include <mysql.h>

namespace isc {
namespace dhcp {

class MySqlSrvConfigMgr : public SrvConfigMgr {
public:
    /// @brief Constructor
    ///
    /// Uses the following keywords in the parameters passed to it to
    /// connect to the database:
    /// - name - Name of the database to which to connect (mandatory)
    /// - host - Host to which to connect (optional, defaults to "localhost")
    /// - user - Username under which to connect (optional)
    /// - password - Password for "user" on the database (optional)
    ///
    /// If the database is successfully opened, the version number in the
    /// schema_version table will be checked against hard-coded value in
    /// the implementation file.
    ///
    /// Finally, all the SQL commands are pre-compiled.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @throw isc::dhcp::NoDatabaseName Mandatory database name not given
    /// @throw isc::dhcp::DbOpenError Error opening the database
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    MySqlSrvConfigMgr(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor (closes database)
    virtual ~MySqlSrvConfigMgr();

    /// @brief Local version of getDBVersion() class method
    static std::string getDBVersion();

    /// @brief Adds if not exists or updates and existing DHCP V4 server
    /// configuration
    ///
    /// One database contains server configuration data only for one kea server.
    ///
    /// @param old_config_timestamp If there is already a server configuration in
    /// the database
    ///        then the configuration's timestamp from database is compared with
    ///        the provided
    ///        one. The update takes place only if the timestamps are the same.
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be an
    /// SQL error.
    ///
    /// @result true if the configuration was added/updated, false if not.
    virtual bool updateConfig4(int64_t old_config_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const;

    /// @brief Adds if not exists or updates and existing DHCP V6 server
    /// configuration
    ///
    /// One database contains server configuration data only for one kea server.
    ///
    /// @param old_config_timestamp If there is already a server configuration in
    /// the database
    ///        then the configuration's timestamp from database is compared with
    ///        the provided
    ///        one. The update takes place only if the timestamps are the same.
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be an
    /// SQL error.
    ///
    /// @return true if the configuration was added/updated, false if not.
    virtual bool updateConfig6(int64_t old_config_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const;

    /// @brief Retrieves timestamp for the DHCPv4 shard server configuration.
    ///
    /// @return pointer to the generic structure containing the timestamp
    virtual SrvConfigInfoPtr getConfig4Timestamp() const;

    /// @brief Retrieves timestamp for the DHCPv6 shard server configuration.
    ///
    /// @return pointer to the generic structure containing the timestamp
    virtual SrvConfigInfoPtr getConfig6Timestamp() const;

    /// @brief Retrieves the configuration of the DHCPv4 server belonging to the
    ///     current shard in JSON format.
    ///
    /// @return server configuration being retrieved
    virtual SrvConfigInfoPtr getJsonConfig4() const;

    /// @brief Retrieves the configuration of the DHCPv6 server belonging to the
    ///     current shard in JSON format.
    ///
    /// @return server configuration being retrieved
    virtual SrvConfigInfoPtr getJsonConfig6() const;

    /// @brief Retrieves the configuration of the DHCPv4 server belonging to the
    ///     current shard in generic format (e.g. YAML).
    ///
    /// @return server configuration being retrieved
    virtual SrvConfigInfoPtr getGenericConfig4() const;

    /// @brief Retrieves the configuration of the DHCPv6 server belonging to the
    ///     current shard in generic format (e.g. YAML).
    ///
    /// @return server configuration being retrieved
    virtual SrvConfigInfoPtr getGenericConfig6() const;

    /// @brief Start Transaction
    ///
    /// Start transaction for database operations. On databases that don't
    /// support transactions, this is a no-op.
    virtual bool startTransaction();

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// @throw DbOperationError If the commit failed.
    virtual void commit();

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// @throw DbOperationError If the rollback failed.
    virtual void rollback();

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual VersionPair getVersion() const;

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("mysql"));
    }

    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of SQL statements
    enum StatementIndex {
        GET_VERSION,                   // Obtain version number
        GET_CONFIGURATION4_TIMESTAMP,  // Get the timestamp of the v4 stored
                                       // configuration
        GET_CONFIGURATION6_TIMESTAMP,  // Get the timestamp of the v6 stored
                                       // configuration
        GET_JSON_CONFIGURATION4,       // Get only JSON server configuration v4
        GET_JSON_CONFIGURATION6,       // Get only JSON server configuration v6
        GET_GENERIC_CONFIGURATION4,    // Get only GENERIC server configuration v4
        GET_GENERIC_CONFIGURATION6,    // Get only GENERIC server configuration v6
        INSERT_CONFIGURATION4,         // Add server configuration v4
        INSERT_CONFIGURATION6,         // Add server configuration v6
        UPDATE_CONFIGURATION4,         // Update server configuration v4
        UPDATE_CONFIGURATION6,         // Update server configuration v6
        NUM_STATEMENTS                 // Number of statements
    };

private:
    /// @brief Inserts a new DHCPv4 server configuration.
    ///
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be an
    /// SQL error.
    ///
    /// @return true if the configuration was added, false if not.
    bool insertConfig4(const std::string& json_data, const std::string& generic_data) const;

    /// @brief Inserts a new DHCPv6 server configuration.
    ///
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be an
    /// SQL error.
    ///
    /// @return true if the configuration was added, false if not.
    bool insertConfig6(const std::string& json_data, const std::string& generic_data) const;

    /// @brief Updates an existing DHCPv4 server configuration.
    ///
    ///
    /// @param version The new configuration's version.
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    ///     format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be an
    ///     SQL error.
    ///
    /// @return true if the configuration was added/updated, false if not.
    bool updateConfig4(const std::string& config_id,
                       const std::string& json_data,
                       const std::string& generic_data) const;

    /// @brief Updates an existing DHCPv6 server configuration.
    ///
    ///
    /// @param version The new configuration's version.
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    ///     format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be an
    ///     SQL error.
    ///
    /// @return true if the configuration was added/updated, false if not.
    bool updateConfig6(const std::string& config_id,
                       const std::string& json_data,
                       const std::string& generic_data) const;

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
    /// @param status Status code: non-zero implies an error
    /// @param index Index of statement that caused the error
    /// @param what High-level description of the error
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    void checkError(int status, StatementIndex index, const char* what) const;

    /// @brief Retrieves synchronization timestamps from the shard database.
    ///
    /// @param statement_index index of the prepared statement being executed in
    ///     the database
    ///
    /// @return a configuration containing the timestamp in question
    SrvConfigInfoPtr getConfigTimestampCommon(StatementIndex stindex) const;

    /// @brief Retrieves a single server configuration either for DHCPv4 or for
    ///     DHCPv6 from the current shard.
    ///
    /// @param statement_index index of the prepared statement being executed in
    ///     the database
    ///
    /// @return the single retrieved configuration
    SrvConfigInfoPtr getConfigCommon(StatementIndex stindex) const;

    /// @brief Adds server configuration either for DHCPv4 or for DHCPv6.
    ///
    /// @param statement_index index of the prepared statement being executed in
    ///     the database
    /// @param config_id unique ID for configuration
    /// @param json_data JSON configuration being inserted
    /// @param generic_data generic configuration (e.g. YAML) being inserted
    ///
    /// @return true, if configuration has been successfully added, false
    ///     otherwise
    bool insertConfigCommon(StatementIndex stindex,
                            const std::string& config_id,
                            const std::string& json_data,
                            const std::string& generic_data) const;

    /// @brief Updates server configuration either for DHCPv4 or for DHCPv6.
    ///
    /// @param statement_index index of the prepared statement being executed in
    ///     the database
    /// @param config_id unique ID for configuration
    /// @param json_data JSON configuration to update the current configuration
    /// @param generic_data generic configuration (e.g. YAML) to update the
    ///     current configuration
    ///
    /// @return true, if configuration has been successfully updated, false
    ///     otherwise
    bool updateConfigCommon(StatementIndex stindex,
                            const std::string& config_id,
                            const std::string& json_data,
                            const std::string& generic_data) const;

    // Members
    /// @brief MySQL connection
    mutable MySqlConnection conn_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // MYSQL_CONFIGURATION_MGR_H
