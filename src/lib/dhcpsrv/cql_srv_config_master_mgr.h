// Copyright (C) 2016-2018 Deutsche Telekom AG.
//
// Authors: Cristian Secareanu <cristian.secareanu@qualitance.com>
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

#ifndef CQL_CONFIGURATION_MASTER_MGR_H
#define CQL_CONFIGURATION_MASTER_MGR_H

#include <dhcpsrv/srv_config_master_mgr.h>

#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/cql_exchange.h>

#include <boost/scoped_ptr.hpp>  // for std::scoped_ptr

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Forward declaration to the exchange.
class CqlMasterConfigExchange;

/// @brief Exchange used to interact with the master server configuration table
/// from the database
class CqlSrvConfigMasterMgr : public SrvConfigMasterMgr {
public:
    /// @brief Constructor
    ///
    /// @param parameters database connection parameters
    explicit CqlSrvConfigMasterMgr(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor
    virtual ~CqlSrvConfigMasterMgr();

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
    /// This is a no-op for Cassandra.
    virtual void commit() override;

    /// @brief Rollback Transactions
    ///
    /// This is a no-op for Cassandra.
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

    /// @brief Returns the type of backend used, in this case "cql". Useful
    ///     when called from the base class.
    virtual std::string getType() const override;

protected:
    /// @brief Generic method for retrieving DHCPv4 shard configurations.
    ///
    /// @param servers_id list of shard configurations being populated
    ///
    /// @return true if shard configurations have been successfully retrieved,
    ///     false otherwise
    bool getServersConfig4(std::vector<std::string>& servers_id) const;

    /// @brief Generic method for retrieving DHCPv6 shard configurations.
    ///
    /// @param servers_id list of shard configurations being populated
    ///
    /// @return true if shard configurations have been successfully retrieved,
    ///     false otherwise
    bool getServersConfig6(std::vector<std::string>& servers_id) const;

    /// @brief Deletes a single DHCPv4 shard configuration.
    ///
    /// @param instance_id identifier of server whose configuration is being
    ///     deleted
    ///
    /// @return true if the shard configuration has been successfully deleted,
    ///     false otherwise
    bool deleteServerConfig4(const std::string& instance_id) const;

    /// @brief Deletes a single DHCPv6 shard configuration.
    ///
    /// @param instance_id identifier of server whose configuration is being
    ///     deleted
    ///
    /// @return true if the shard configuration has been successfully deleted,
    ///     false otherwise
    bool deleteServerConfig6(const std::string& instance_id) const;

    /// @brief Server configuration specific tagged statements
    static StatementMap tagged_statements_;

private:
    /// Database connection object
    mutable CqlConnection dbconn_;
};  // CqlSrvConfigMasterMgr

class CqlMasterConfigVersionExchange : public CqlVersionExchange {
public:
    /// @brief Cassandra statements
    static StatementMap tagged_statements_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // CQL_CONFIGURATION_MASTER_MGR_H
