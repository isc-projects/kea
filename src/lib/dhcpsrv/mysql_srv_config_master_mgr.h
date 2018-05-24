// Copyright (C) 2016-2018 Deutsche Telekom AG.
//
// Author: Cristian Secareanu <cristian.secareanu@qualitance.com>
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

#ifndef MYSQL_CONFIGURATION_MASTER_MGR_H
#define MYSQL_CONFIGURATION_MASTER_MGR_H

#include <dhcpsrv/srv_config_master_mgr.h>

#include <boost/scoped_ptr.hpp>
#include <dhcpsrv/mysql_connection.h>
#include <mysql.h>

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Forward declaration to the exchange.
class MySqlMasterConfigExchange;

/// @brief Exchange used to interact with the master server configuration table
/// from the database
class MySqlSrvConfigMasterMgr : public SrvConfigMasterMgr {
public:
    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of SQL statements
    enum StatementIndex {
        // Insert DHCPv4 server configuration.
        INSERT_SERVER_CONFIG4,
        // Insert DHCPv6 server configuration.
        INSERT_SERVER_CONFIG6,
        // Retrieve DHCPv4 server configuration filtered by server ID.
        GET_CONFIGURATION4_BY_SRV_ID,
        // Retrieve DHCPv6 server configuration filtered by server ID.
        GET_CONFIGURATION6_BY_SRV_ID,
        // Retrieve DHCPv4 server configuration filtered by shard name.
        GET_CONFIGURATION4_BY_SHARD_DB,
        // Retrieve DHCPv6 server configuration filtered by shard name.
        GET_CONFIGURATION6_BY_SHARD_DB,
        // Retrieve DHCPv4 synchronization timestamp.
        GET_CONFIGURATION4_TIMESTAMP,
        // Retrieve DHCPv6 synchronization timestamp.
        GET_CONFIGURATION6_TIMESTAMP,
        // Delete DHCPv4 server configuration.
        DELETE_SERVER_CONFIG4,
        // Delete DHCPv6 server configuration.
        DELETE_SERVER_CONFIG6,
        // Retrieve DHCPv4 shard names.
        GET_SERVERS_CONFIG4_SHARDS_NAME,
        // Retrieve DHCPv6 shard names.
        GET_SERVERS_CONFIG6_SHARDS_NAME,
        // Retrieve schema version.
        GET_VERSION,
        // Number of statements
        NUM_STATEMENTS
    };

    /// @brief Constructor
    ///
    /// @param parameters database connection parameters
    explicit MySqlSrvConfigMasterMgr(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor
    virtual ~MySqlSrvConfigMasterMgr();

    /// @brief Inserts DHCPv4 server configuration into the master database
    ///
    /// @param instance_id instance identifier of the server whose configuration is being added
    /// @param server_config the configuration being added
    /// @param config_database configuration to be used on the shard
    /// @param config_database_name name of the shard whose configuration is being added
    ///
    /// @return true if server configuration has been added, false otherwise
    virtual bool addServerConfig4(const std::string& instance_id,
                                  const std::string& server_config,
                                  const std::string& config_database,
                                  const std::string& config_database_name) const override;

    /// @brief Inserts DHCPv6 server configuration into the master database
    ///
    /// @param instance_id instance identifier of the server whose configuration is being added
    /// @param server_config the configuration being added
    /// @param config_database configuration to be used on the shard
    /// @param config_database_name name of the shard whose configuration is being added
    ///
    /// @return true if server configuration has been added, false otherwise
    virtual bool addServerConfig6(const std::string& instance_id,
                                  const std::string& server_config,
                                  const std::string& config_database,
                                  const std::string& config_database_name) const override;

    /// @brief Clears all DHCPv4 shard configurations.
    ///
    /// @return true if shard configurations have been successfully deleted, false otherwise
    virtual bool clearServersConfig4() const override;

    /// @brief Clears all DHCPv6 shard configurations.
    ///
    /// @return true if shard configurations have been successfully deleted, false otherwise
    virtual bool clearServersConfig6() const override;

    /// @brief Returns DHCPv4 server configuration information from the database
    ///
    /// This method returns the server configuration.
    /// One database contains server configuration data only for one Kea server.
    ///
    /// @param instance_id the instance identifier of the server being retrieved
    ///
    /// @return smart pointer to the configuration (or NULL if a configuration is not found)
    virtual SrvConfigMasterInfoPtr getConfig4(const std::string& instance_id) const override;

    /// @brief Returns DHCPv6 server configuration information from the database
    ///
    /// This method returns the server configuration.
    /// One database contains server configuration data only for one Kea server.
    ///
    /// @param instance_id the instance identifier of the server being retrieved
    ///
    /// @return smart pointer to the configuration (or NULL if a configuration is not found)
    virtual SrvConfigMasterInfoPtr getConfig6(const std::string& instance_id) const override;

    /// @brief Retrieves configurations of DHCPv4 servers belonging to a given
    ///     shard.
    ///
    /// @param config_database_name name of the shard whose configuration is being retrieved
    /// @param[out] server_configurations a list of server configurations being retrieved
    ///
    /// @return true if server configuration has been successfully retrieved, false otherwise
    virtual bool getConfig4(const std::string& config_database_name,
               std::vector<SrvConfigMasterInfoPtr>& server_configurations) const override;

    /// @brief Retrieves configurations of DHCPv6 servers belonging to a given
    ///     shard.
    ///
    /// @param config_database_name name of the shard whose configuration is being retrieved
    /// @param[out] server_configurations a list of server configurations being retrieved
    ///
    /// @return true if server configuration has been successfully retrieved, false otherwise
    virtual bool getConfig6(const std::string& config_database_name,
               std::vector<SrvConfigMasterInfoPtr>& server_configurations) const override;

    /// @brief Retrieves timestamp for a DHCPv4 shard server configuration.
    ///
    /// There is one timestamp for each shard in the master database. They are
    /// updated on every write (including updates) to the master database.
    ///
    /// @param instance_id the instance identifier of the server for which the timestamp is being
    ///     retrieved
    ///
    /// @return pointer to the generic structure containing the timestamp
    virtual SrvConfigMasterInfoPtr
    getMasterConfig4Timestamp(const std::string& instance_id) const override;

    /// @brief Retrieves timestamp for a DHCPv6 shard server configuration.
    ///
    /// There is one timestamp for each shard in the master database. They are
    /// updated on every write (including updates) to the master database.
    ///
    /// @param instance_id the instance identifier of the server for which the timestamp is being
    ///     retrieved
    ///
    /// @return pointer to the generic structure containing the timestamp
    virtual SrvConfigMasterInfoPtr
    getMasterConfig6Timestamp(const std::string& instance_id) const override;

    /// @brief Retrieves all shard names containing DHCPv4 servers from the master database.
    ///
    /// @return true if shard names have been successfully retrieved, false otherwise
    virtual bool getServersConfig4ShardsName(std::set<std::string>& shards) const override;

    /// @brief Retrieves all shard names containing DHCPv6 servers from the master database.
    ///
    /// @return true if shard names have been successfully retrieved, false otherwise
    virtual bool getServersConfig6ShardsName(std::set<std::string>& shards) const override;

    /// @brief Start Transaction
    ///
    /// Start transaction for database operations. On databases that don't
    /// support transactions, this is a no-op.
    virtual bool startTransaction() override;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.
    ///
    /// @throw DbOperationError If the commit failed.
    virtual void commit() override;

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.
    ///
    /// @throw DbOperationError If the rollback failed.
    virtual void rollback() override;

    /// @brief Retrieves schema version.
    ///
    /// @return Version number stored in the database, as a pair of unsigned integers. "first" is
    /// the major version number, "second" is the minor version number.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has failed.
    VersionPair getVersion() const override;

    /// @brief Local version of getDBVersion() class method
    static std::string getDBVersion();

    /// @brief Returns the type of backend used, in this case "mysql". Useful
    ///     when called from the base class.
    virtual std::string getType() const override {
        return (std::string("mysql"));
    }

private:
    /// @brief Check Error and Throw Exception
    ///
    /// This method invokes @ref MySqlConnection::checkError.
    ///
    /// @param status Status code: non-zero implies an error
    /// @param index Index of statement that caused the error
    /// @param what High-level description of the error
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    void checkError(int status, StatementIndex statement_index, const char* what) const;

private:
    /// @brief Adds server configuration either for DHCPv4 or for DHCPv6.
    ///
    /// @param statement_index index of the prepared statement executed in the database
    /// @param instance_id the instance identifier of the server being added to the database
    /// @param server_config configuration of the server being added to the database
    /// @param config_database configuration to be used on the shard
    /// @param config_database_name name of the shard whose configuration is being added
    ///
    /// @return true, if configuration has been successfully added, false otherwise
    bool addCommonServerConfiguration(const StatementIndex statement_index,
                                      const std::string& instance_id,
                                      const std::string& server_config,
                                      const std::string& config_database,
                                      const std::string& config_database_name) const;

    /// @brief Retrieves a single server configuration either for DHCPv4 or for
    ///     DHCPv6 filtered by the instance ID of the server.
    ///
    /// @param statement_index index of the prepared statement executed in the database
    /// @param instance_id the instance identifier of the server being retrieved from the database
    ///
    /// @return the retrieved configuration
    SrvConfigMasterInfoPtr
    getCommonServerConfigurationByInstanceId(const StatementIndex statement_index,
                                             const std::string& instance_id) const;

    /// @brief Retrieves the configurations of the DHCPv4 or DHCPv6 servers
    ///     belonging to a given shard.
    ///
    /// @param statement_index index of the prepared statement executed in the database
    /// @param config_database_name name of the shard whose configuration is being retrieved
    /// @param[out] server_configurations the retrieved configurations
    ///
    /// @return true if configurations were found, false otherwise
    bool getCommonServerConfigurationByShardName(
        const StatementIndex statement_index,
        const std::string& config_database_name,
        std::vector<SrvConfigMasterInfoPtr>& server_configurations) const;

    /// @brief Retrieves synchronization timestamps from the master database for
    ///     a given server.
    //
    /// @param statement_index index of the prepared statement executed in the database
    /// @param instance_id the instance identifier of the server by which timestamps are filtered
    ///
    /// @return a configuration containing the timestamp in question
    SrvConfigMasterInfoPtr
    getCommonTimestampFromMasterServerConfiguration(const StatementIndex statement_index,
                                                    const std::string& instance_id) const;

    /// @brief Retrieves all the shard names from the master database.
    ///
    /// @param statement_index index of the prepared statement executed in the database
    /// @param[out] shards the whole set of shards from the master database
    bool getCommonShardNamesFromMasterServerConfiguration(const StatementIndex statement_index,
                                                          std::set<std::string>& shards) const;

    /// @brief Database connection object
    mutable MySqlConnection conn_;
    // @brief Exchange in charge of data conversion to and from MySQL types
    boost::scoped_ptr<MySqlMasterConfigExchange> exchange_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // MYSQL_CONFIGURATION_MASTER_MGR_H
