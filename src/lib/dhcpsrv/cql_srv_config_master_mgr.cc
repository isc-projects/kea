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

#include <config.h>

#include <dhcpsrv/cql_srv_config_master_mgr.h>

#include <dhcpsrv/cql_transaction.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <boost/smart_ptr/make_shared.hpp>

#include <sys/types.h>        // for int32_t

namespace isc {
namespace dhcp {

StatementMap CqlMasterConfigVersionExchange::tagged_statements_ = {
    {GET_VERSION,   //
     {GET_VERSION,  //
      "SELECT "
      "version, minor "
      "FROM master_schema_version "}}  //
};

/// @brief Exchange used to interact with the master server configuration table
/// from the database
class CqlMasterConfigExchange : public virtual CqlExchange {
public:
    /// @brief Statement tags definitions
    /// @{
    // Insert DHCPv4 server configuration.
    static constexpr StatementTag INSERT_SERVER_CONFIG4 = "INSERT_SERVER_CONFIG4";
    // Insert DHCPv6 server configuration.
    static constexpr StatementTag INSERT_SERVER_CONFIG6 = "INSERT_SERVER_CONFIG6";
    // Retrieve DHCPv4 server configuration filtered by server ID.
    static constexpr StatementTag GET_CONFIGURATION4_BY_SRV_ID = "GET_CONFIGURATION4_BY_SRV_ID";
    // Retrieve DHCPv6 server configuration filtered by server ID.
    static constexpr StatementTag GET_CONFIGURATION6_BY_SRV_ID = "GET_CONFIGURATION6_BY_SRV_ID";
    // Retrieve DHCPv4 server configuration filtered by shard name.
    static constexpr StatementTag GET_CONFIGURATION4_BY_SHARD_DB = "GET_CONFIGURATION4_BY_SHARD_DB";
    // Retrieve DHCPv6 server configuration filtered by shard name.
    static constexpr StatementTag GET_CONFIGURATION6_BY_SHARD_DB = "GET_CONFIGURATION6_BY_SHARD_DB";
    // Retrieve DHCPv4 synchronization timestamp.
    static constexpr StatementTag GET_CONFIGURATION4_TIMESTAMP = "GET_CONFIGURATION4_TIMESTAMP";
    // Retrieve DHCPv6 synchronization timestamp.
    static constexpr StatementTag GET_CONFIGURATION6_TIMESTAMP = "GET_CONFIGURATION6_TIMESTAMP";
    // Retrieve DHCPv4 server configurations.
    static constexpr StatementTag GET_SERVERS_CONFIG4 = "GET_SERVERS_CONFIG4";
    // Retrieve DHCPv6 server configurations.
    static constexpr StatementTag GET_SERVERS_CONFIG6 = "GET_SERVERS_CONFIG6";
    // Delete DHCPv4 server configuration.
    static constexpr StatementTag DELETE_SERVER_CONFIG4 = "DELETE_SERVER_CONFIG4";
    // Delete DHCPv6 server configuration.
    static constexpr StatementTag DELETE_SERVER_CONFIG6 = "DELETE_SERVER_CONFIG6";
    // Retrieve DHCPv4 shard names.
    static constexpr StatementTag GET_SERVERS_CONFIG4_SHARDS_NAME =
        "GET_SERVERS_CONFIG4_SHARDS_NAME";
    // Retrieve DHCPv6 shard names.
    static constexpr StatementTag GET_SERVERS_CONFIG6_SHARDS_NAME =
        "GET_SERVERS_CONFIG6_SHARDS_NAME";
    /// @}

    /// @brief Constructor
    ///
    /// Specifies table columns.
    CqlMasterConfigExchange();

    /// @brief Destructor
    virtual ~CqlMasterConfigExchange();

    /// @brief Create BIND array to receive master configuration data.
    ///
    /// Method used in executeSelect() to retrieve SrvConfigMasterInfoPtr object
    /// from database
    ///
    /// @param data array of bound objects representing data to be retrieved.
    /// @param statement_tag prepared statement being executed; defaults to an
    /// invalid index
    virtual void createBindForSelect(AnyArray& data, StatementTag statement_tag = NULL) override;

    /// @brief Copy received data into @ref SrvConfigMasterInfo object
    ///
    /// This method copies information about the master server configuration
    /// into a newly created @ref SrvConfigMasterInfo object. This method is
    /// called in @ref executeSelect().
    ///
    /// @return pointer to a @ref SrvConfigMasterInfoPtr object holding a
    /// pointer to the @ref SrvConfigMasterInfo object returned.
    virtual boost::any retrieve() override;

    /// @brief Common method for inserting configuration information into the
    ///     database.
    ///
    /// @param connection connection used to communicate with the Cassandra
    /// database
    /// @param instance_id table column - unique instance identifier
    /// @param server_config table column - JSON server configuration
    /// @param config_database configuration to be used on the shard
    /// @param config_database_name name of the shard whose configuration is being added
    /// @param statement_tag prepared statement being executed
    ///
    /// @return true if insertion succeeded, false otherwise
    bool insertCommon(CqlConnection& connection,
                      const std::string& instance_id,
                      const std::string& server_config,
                      const std::string& config_database,
                      const std::string& config_database_name,
                      StatementTag statement_tag);

    /// @brief Common method for retrieving configuration information from the
    /// database.
    SrvConfigMasterInfoCollection getCommon(CqlConnection& connection,
                                            const AnyArray& data,
                                            StatementTag statement_tag,
                                            bool single = true);

    /// @brief Cassandra statements
    static StatementMap tagged_statements_;

private:
    /// @brief Object that this exchange reads from when writing to the database
    /// and writes to when reading from the database.
    SrvConfigMasterInfoPtr master_config_info_;
};  // CqlMasterConfigExchange

constexpr StatementTag CqlMasterConfigExchange::INSERT_SERVER_CONFIG4;
constexpr StatementTag CqlMasterConfigExchange::INSERT_SERVER_CONFIG6;
constexpr StatementTag CqlMasterConfigExchange::GET_CONFIGURATION4_BY_SRV_ID;
constexpr StatementTag CqlMasterConfigExchange::GET_CONFIGURATION6_BY_SRV_ID;
constexpr StatementTag CqlMasterConfigExchange::GET_CONFIGURATION4_BY_SHARD_DB;
constexpr StatementTag CqlMasterConfigExchange::GET_CONFIGURATION6_BY_SHARD_DB;
constexpr StatementTag CqlMasterConfigExchange::GET_CONFIGURATION4_TIMESTAMP;
constexpr StatementTag CqlMasterConfigExchange::GET_CONFIGURATION6_TIMESTAMP;
constexpr StatementTag CqlMasterConfigExchange::GET_SERVERS_CONFIG4;
constexpr StatementTag CqlMasterConfigExchange::GET_SERVERS_CONFIG6;
constexpr StatementTag CqlMasterConfigExchange::DELETE_SERVER_CONFIG4;
constexpr StatementTag CqlMasterConfigExchange::DELETE_SERVER_CONFIG6;
constexpr StatementTag CqlMasterConfigExchange::GET_SERVERS_CONFIG4_SHARDS_NAME;
constexpr StatementTag CqlMasterConfigExchange::GET_SERVERS_CONFIG6_SHARDS_NAME;

StatementMap CqlMasterConfigExchange::tagged_statements_ = {
    {INSERT_SERVER_CONFIG4,   //
     {INSERT_SERVER_CONFIG4,  //
      "INSERT INTO server_configuration4 "
      "(instance_id, timestamp, server_config, config_database, config_database_name) "
      "VALUES (?, ?, ?, ?, ?) "
      "IF NOT EXISTS "
     }},

    {INSERT_SERVER_CONFIG6,   //
     {INSERT_SERVER_CONFIG6,  //
      "INSERT INTO server_configuration6 "
      "(instance_id, timestamp, server_config, config_database, config_database_name) "
      "VALUES (?, ?, ?, ?, ?) "
      "IF NOT EXISTS "
     }},

    {GET_CONFIGURATION4_BY_SRV_ID,   //
     {GET_CONFIGURATION4_BY_SRV_ID,  //
      "SELECT instance_id, timestamp, server_config, config_database, config_database_name "
      "FROM server_configuration4 "
      "WHERE instance_id = ? "
     }},

    {GET_CONFIGURATION6_BY_SRV_ID,   //
     {GET_CONFIGURATION6_BY_SRV_ID,  //
      "SELECT instance_id, timestamp, server_config, config_database, config_database_name "
      "FROM server_configuration6 "
      "WHERE instance_id = ? "
     }},

    {GET_CONFIGURATION4_BY_SHARD_DB,   //
     {GET_CONFIGURATION4_BY_SHARD_DB,  //
      "SELECT instance_id, timestamp, server_config, config_database, config_database_name "
      "FROM server_configuration4 "
      "WHERE config_database_name = ? ALLOW FILTERING "
     }},

    {GET_CONFIGURATION6_BY_SHARD_DB,   //
     {GET_CONFIGURATION6_BY_SHARD_DB,  //
      "SELECT instance_id, timestamp, server_config, config_database, config_database_name "
      "FROM server_configuration6 "
      "WHERE config_database_name = ? ALLOW FILTERING "
     }},

    {GET_CONFIGURATION4_TIMESTAMP,   //
     {GET_CONFIGURATION4_TIMESTAMP,  //
      "SELECT instance_id, timestamp "
      "FROM server_configuration4 "
      "WHERE instance_id = ? "
     }},

    {GET_CONFIGURATION6_TIMESTAMP,   //
     {GET_CONFIGURATION6_TIMESTAMP,  //
      "SELECT instance_id, timestamp "
      "FROM server_configuration6 "
      "WHERE instance_id = ? "
     }},

    {GET_SERVERS_CONFIG4,   //
     {GET_SERVERS_CONFIG4,  //
      "SELECT instance_id "
      "FROM server_configuration4 "
     }},

    {GET_SERVERS_CONFIG6,   //
     {GET_SERVERS_CONFIG6,  //
      "SELECT instance_id "
      "FROM server_configuration6 "
     }},

    {DELETE_SERVER_CONFIG4,   //
     {DELETE_SERVER_CONFIG4,  //
      "DELETE FROM server_configuration4 "
      "WHERE instance_id = ? "
      "IF EXISTS "
     }},

    {DELETE_SERVER_CONFIG6,   //
     {DELETE_SERVER_CONFIG6,  //
      "DELETE FROM server_configuration6 "
      "WHERE instance_id = ? "
      "IF EXISTS "
     }},

    {GET_SERVERS_CONFIG4_SHARDS_NAME,   //
     {GET_SERVERS_CONFIG4_SHARDS_NAME,  //
      "SELECT config_database_name "
      "FROM server_configuration4 "
     }},

    {GET_SERVERS_CONFIG6_SHARDS_NAME,   //
     {GET_SERVERS_CONFIG6_SHARDS_NAME,  //
      "SELECT config_database_name "
      "FROM server_configuration6 "
     }}  //
};

CqlMasterConfigExchange::CqlMasterConfigExchange()
    : master_config_info_(boost::make_shared<SrvConfigMasterInfo>()) {
}

CqlMasterConfigExchange::~CqlMasterConfigExchange() {
}

void CqlMasterConfigExchange::createBindForSelect(AnyArray& data,
                                                  StatementTag statement_tag /* = NULL */) {
    // Start with a fresh array.
    data.clear();

    if (statement_tag == GET_CONFIGURATION4_TIMESTAMP ||
        statement_tag == GET_CONFIGURATION6_TIMESTAMP) {
        data.add(&master_config_info_->instance_id_);
        data.add(&master_config_info_->timestamp_);
    } else if (statement_tag == GET_SERVERS_CONFIG4_SHARDS_NAME ||
               statement_tag == GET_SERVERS_CONFIG6_SHARDS_NAME) {
        data.add(&master_config_info_->config_database_name_);
    } else if (statement_tag == GET_SERVERS_CONFIG4 || statement_tag == GET_SERVERS_CONFIG6) {
        data.add(&master_config_info_->instance_id_);
    } else {
        data.add(&master_config_info_->instance_id_);
        data.add(&master_config_info_->timestamp_);
        data.add(&master_config_info_->server_config_);
        data.add(&master_config_info_->config_database_);
        data.add(&master_config_info_->config_database_name_);
    }
}

boost::any CqlMasterConfigExchange::retrieve() {
    SrvConfigMasterInfoPtr config(new SrvConfigMasterInfo(*master_config_info_));
    return config;
}

SrvConfigMasterInfoCollection CqlMasterConfigExchange::getCommon(CqlConnection& connection,
                                                                 const AnyArray& data,
                                                                 StatementTag statement_tag,
                                                                 bool single /* = true */) {
    AnyArray collection = executeSelect(connection, data, statement_tag, single);

    SrvConfigMasterInfoCollection result;

    if (collection.empty()) {
        return result;
    }

    for (boost::any& element : collection) {
        SrvConfigMasterInfoPtr item(boost::any_cast<SrvConfigMasterInfoPtr>(element));
        result.push_back(item);
    }

    return result;
}

bool CqlMasterConfigExchange::insertCommon(CqlConnection& connection,
                                           const std::string& instance_id,
                                           const std::string& server_config,
                                           const std::string& config_database,
                                           const std::string& config_database_name,
                                           StatementTag statement_tag) {
    cass_int64_t config_timestamp = static_cast<cass_int64_t>(time(NULL));

    AnyArray assigned_values;
    assigned_values.add(const_cast<std::string*>(&instance_id));
    assigned_values.add(&config_timestamp);
    assigned_values.add(const_cast<std::string*>(&server_config));
    assigned_values.add(const_cast<std::string*>(&config_database));
    assigned_values.add(const_cast<std::string*>(&config_database_name));

    executeMutation(connection, assigned_values, statement_tag);

    return true;
}

CqlSrvConfigMasterMgr::CqlSrvConfigMasterMgr(const DatabaseConnection::ParameterMap& parameters)
    : SrvConfigMasterMgr(), dbconn_(parameters) {
    dbconn_.openDatabase();
    dbconn_.prepareStatements(CqlMasterConfigExchange::tagged_statements_);
    dbconn_.prepareStatements(CqlMasterConfigVersionExchange::tagged_statements_);
}

CqlSrvConfigMasterMgr::~CqlSrvConfigMasterMgr() {
}

bool CqlSrvConfigMasterMgr::addServerConfig4(const std::string& instance_id,
                                             const std::string& server_config,
                                             const std::string& config_database,
                                             const std::string& config_database_name) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_INSERT_SRV_MASTER_CONFIG4)
        .arg(instance_id)
        .arg(config_database_name);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    master_config_exchange->insertCommon(dbconn_, instance_id, server_config, config_database,
                                         config_database_name,
                                         CqlMasterConfigExchange::INSERT_SERVER_CONFIG4);

    transaction.commit();

    return true;
}

bool CqlSrvConfigMasterMgr::addServerConfig6(const std::string& instance_id,
                                             const std::string& server_config,
                                             const std::string& config_database,
                                             const std::string& config_database_name) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_INSERT_SRV_MASTER_CONFIG6)
        .arg(instance_id)
        .arg(config_database_name);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    master_config_exchange->insertCommon(dbconn_, instance_id, server_config, config_database,
                                         config_database_name,
                                         CqlMasterConfigExchange::INSERT_SERVER_CONFIG6);

    transaction.commit();

    return true;
}

SrvConfigMasterInfoPtr CqlSrvConfigMasterMgr::getConfig4(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_SRV_MASTER_CONFIG4)
        .arg(instance_id);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray where_values;
    where_values.add(const_cast<std::string*>(&instance_id));

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    SrvConfigMasterInfoCollection collection = master_config_exchange->getCommon(
        dbconn_, where_values, CqlMasterConfigExchange::GET_CONFIGURATION4_BY_SRV_ID);

    transaction.commit();

    SrvConfigMasterInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

SrvConfigMasterInfoPtr CqlSrvConfigMasterMgr::getConfig6(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_SRV_MASTER_CONFIG6)
        .arg(instance_id);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray where_values;
    where_values.add(const_cast<std::string*>(&instance_id));

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    SrvConfigMasterInfoCollection collection = master_config_exchange->getCommon(
        dbconn_, where_values, CqlMasterConfigExchange::GET_CONFIGURATION6_BY_SRV_ID);

    transaction.commit();

    SrvConfigMasterInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

bool CqlSrvConfigMasterMgr::getConfig4(
    const std::string& config_database_name,
    std::vector<SrvConfigMasterInfoPtr>& server_configurations) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_SRV_MASTER_CONFIG4_SHARD_DB)
        .arg(config_database_name);

    server_configurations.clear();

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray where_values;
    where_values.add(const_cast<std::string*>(&config_database_name));

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    SrvConfigMasterInfoCollection collection_data = master_config_exchange->getCommon(
        dbconn_, where_values, CqlMasterConfigExchange::GET_CONFIGURATION4_BY_SHARD_DB, false);

    transaction.commit();

    server_configurations = collection_data;

    return true;
}

bool CqlSrvConfigMasterMgr::getConfig6(
    const std::string& config_database_name,
    std::vector<SrvConfigMasterInfoPtr>& server_configurations) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_SRV_MASTER_CONFIG6_SHARD_DB)
        .arg(config_database_name);

    server_configurations.clear();

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray where_values;
    where_values.add(const_cast<std::string*>(&config_database_name));

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    SrvConfigMasterInfoCollection collection_data = master_config_exchange->getCommon(
        dbconn_, where_values, CqlMasterConfigExchange::GET_CONFIGURATION6_BY_SHARD_DB, false);

    transaction.commit();

    server_configurations = collection_data;

    return true;
}

SrvConfigMasterInfoPtr
CqlSrvConfigMasterMgr::getMasterConfig4Timestamp(const std::string& instance_id) const {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_MASTER_CONFIG4_TIMESTAMP)
        .arg(instance_id);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray where_values;

    where_values.add(const_cast<std::string*>(&instance_id));

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    SrvConfigMasterInfoCollection collection = master_config_exchange->getCommon(
        dbconn_, where_values, CqlMasterConfigExchange::GET_CONFIGURATION4_TIMESTAMP);

    transaction.commit();

    SrvConfigMasterInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

SrvConfigMasterInfoPtr
CqlSrvConfigMasterMgr::getMasterConfig6Timestamp(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_MASTER_CONFIG6_TIMESTAMP)
        .arg(instance_id);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray where_values;

    where_values.add(const_cast<std::string*>(&instance_id));

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    SrvConfigMasterInfoCollection collection = master_config_exchange->getCommon(
        dbconn_, where_values, CqlMasterConfigExchange::GET_CONFIGURATION6_TIMESTAMP);

    transaction.commit();

    SrvConfigMasterInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

bool CqlSrvConfigMasterMgr::clearServersConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_CLEAR_SRV_MASTER_CONFIG4);

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::vector<std::string> servers_id;
    getServersConfig4(servers_id);
    for (std::string const& server_id : servers_id) {
        deleteServerConfig4(server_id);
    }

    transaction.commit();

    return true;
}

bool CqlSrvConfigMasterMgr::clearServersConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_CLEAR_SRV_MASTER_CONFIG6);

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::vector<std::string> servers_id;
    getServersConfig6(servers_id);
    for (std::string const& server_id : servers_id) {
        deleteServerConfig6(server_id);
    }

    transaction.commit();

    return true;
}

bool CqlSrvConfigMasterMgr::getServersConfig4ShardsName(std::set<std::string>& shards_list) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_MASTER_CONFIG4_SHARDS_NAME);

    shards_list.clear();

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray data;

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    SrvConfigMasterInfoCollection collection_data = master_config_exchange->getCommon(
        dbconn_, data, CqlMasterConfigExchange::GET_SERVERS_CONFIG4_SHARDS_NAME, false);

    transaction.commit();

    for (SrvConfigMasterInfoPtr const& srvInfo : collection_data) {
        shards_list.insert(srvInfo->config_database_name_);
    }

    return true;
}

bool CqlSrvConfigMasterMgr::getServersConfig6ShardsName(std::set<std::string>& shards_list) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_MASTER_CONFIG6_SHARDS_NAME);

    shards_list.clear();

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray data;

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    SrvConfigMasterInfoCollection collection_data = master_config_exchange->getCommon(
        dbconn_, data, CqlMasterConfigExchange::GET_SERVERS_CONFIG6_SHARDS_NAME, false);

    transaction.commit();

    for (SrvConfigMasterInfoPtr const& srvInfo : collection_data) {
        shards_list.insert(srvInfo->config_database_name_);
    }

    return true;
}

std::string CqlSrvConfigMasterMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "CQL backend " << CQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << CQL_SCHEMA_VERSION_MINOR;
    tmp << ", library cassandra_static " << CASS_VERSION_MAJOR;
    tmp << "." << CASS_VERSION_MINOR;
    tmp << "." << CASS_VERSION_PATCH;
    return tmp.str();
}

std::string CqlSrvConfigMasterMgr::getType() const {
    return (std::string("cql"));
}

VersionPair CqlSrvConfigMasterMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_VERSION);

    std::unique_ptr<CqlVersionExchange> version_exchange(new CqlVersionExchange());
    return version_exchange->retrieveVersion(dbconn_);
}

bool CqlSrvConfigMasterMgr::startTransaction() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_BEGIN_TRANSACTION);
    dbconn_.startTransaction();
    return true;
}

void CqlSrvConfigMasterMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_COMMIT);
    dbconn_.commit();
}

void CqlSrvConfigMasterMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ROLLBACK);
    dbconn_.rollback();
}

/////////////////////////////////////////////////////////
// Protected methods

bool CqlSrvConfigMasterMgr::getServersConfig4(std::vector<std::string>& servers_id) const {
    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.

    servers_id.clear();
    CqlTransaction transaction(dbconn_);

    AnyArray data;

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    AnyArray collection = master_config_exchange->executeSelect(
        dbconn_, data, CqlMasterConfigExchange::GET_SERVERS_CONFIG4);

    transaction.commit();

    if (collection.empty()) {
        return true;
    }

    for (boost::any& element : collection) {
        SrvConfigMasterInfoPtr item(boost::any_cast<SrvConfigMasterInfoPtr>(element));
        servers_id.push_back(item->instance_id_);
    }

    return true;
}

bool CqlSrvConfigMasterMgr::getServersConfig6(std::vector<std::string>& servers_id) const {
    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.

    servers_id.clear();
    CqlTransaction transaction(dbconn_);

    AnyArray data;

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    AnyArray collection = master_config_exchange->executeSelect(
        dbconn_, data, CqlMasterConfigExchange::GET_SERVERS_CONFIG6);

    transaction.commit();

    if (collection.empty()) {
        return true;
    }

    for (boost::any& element : collection) {
        SrvConfigMasterInfoPtr item(boost::any_cast<SrvConfigMasterInfoPtr>(element));
        servers_id.push_back(item->instance_id_);
    }

    return true;
}

bool CqlSrvConfigMasterMgr::deleteServerConfig4(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_DELETE_SRV_MASTER_CONFIG4)
        .arg(instance_id);

    // CqlTransaction rolls back the transaction on its destructor.
    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray data;
    data.add(const_cast<std::string*>(&instance_id));

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    master_config_exchange->executeMutation(dbconn_, data,
                                            CqlMasterConfigExchange::DELETE_SERVER_CONFIG4);

    transaction.commit();

    return true;
}

bool CqlSrvConfigMasterMgr::deleteServerConfig6(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_DELETE_SRV_MASTER_CONFIG6)
        .arg(instance_id);

    // CqlTransaction rolls back the transaction on its destructor.
    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    AnyArray data;
    data.add(const_cast<std::string*>(&instance_id));

    std::unique_ptr<CqlMasterConfigExchange> master_config_exchange(new CqlMasterConfigExchange());
    master_config_exchange->executeMutation(dbconn_, data,
                                            CqlMasterConfigExchange::DELETE_SERVER_CONFIG6);

    transaction.commit();

    return true;
}

}  // namespace dhcp
}  // namespace isc
