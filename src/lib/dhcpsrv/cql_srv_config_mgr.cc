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

#include <dhcpsrv/cql_srv_config_mgr.h>

#include <dhcpsrv/cql_transaction.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <stddef.h>     // for NULL
#include <sys/types.h>  // for int32_t, int64_t

#include <boost/assert.hpp>                 // for BOOST_ASSERT
#include <boost/uuid/random_generator.hpp>  // for boost::uuids::random_generator
#include <boost/uuid/uuid.hpp>              // for boost::uuid
#include <boost/uuid/uuid_io.hpp>

#include <string>  // for std::string

namespace isc {
namespace dhcp {

StatementMap CqlConfigVersionExchange::tagged_statements_ = {
    {GET_VERSION,   //
     {GET_VERSION,  //
      "SELECT "
      "version, minor "
      "FROM config_schema_version "}}  //
};

class CqlConfigExchange : public virtual CqlExchange {
public:
    /// @brief Statement tags definitions
    /// @{
    // Get the timestamp of the v4 stored configuration
    static constexpr StatementTag GET_CONFIGURATION4_TIMESTAMP =
        "GET_CONFIGURATION4_TIMESTAMP";
    // Get the timestamp of the v6 stored configuration
    static constexpr StatementTag GET_CONFIGURATION6_TIMESTAMP =
        "GET_CONFIGURATION6_TIMESTAMP";
    // Get only GENERIC server configuration v4
    static constexpr StatementTag GET_GENERIC_CONFIGURATION4 =
        "GET_GENERIC_CONFIGURATION4";
    // Get only GENERIC server configuration v6
    static constexpr StatementTag GET_GENERIC_CONFIGURATION6 =
        "GET_GENERIC_CONFIGURATION6";
    // Get only JSON server configuration v4
    static constexpr StatementTag GET_JSON_CONFIGURATION4 =
        "GET_JSON_CONFIGURATION4";
    // Get only JSON server configuration v6
    static constexpr StatementTag GET_JSON_CONFIGURATION6 =
        "GET_JSON_CONFIGURATION6";
    // Add server configuration v4
    static constexpr StatementTag INSERT_CONFIGURATION4 =
        "INSERT_CONFIGURATION4";
    // Add server configuration v6
    static constexpr StatementTag INSERT_CONFIGURATION6 =
        "INSERT_CONFIGURATION6";
    // Update server configuration v4
    static constexpr StatementTag UPDATE_CONFIGURATION4 =
        "UPDATE_CONFIGURATION4";
    // Update server configuration v6
    static constexpr StatementTag UPDATE_CONFIGURATION6 =
        "UPDATE_CONFIGURATION6";
    /// @}

    /// @brief Constructor
    ///
    /// Specifies table columns.
    CqlConfigExchange();

    /// @brief Destructor
    virtual ~CqlConfigExchange();

    /// @brief Create BIND array to receive server configuration data.
    ///
    /// Used in executeSelect() to retrieve server configuration
    /// from database
    ///
    /// @param data array of bound objects representing data to be retrieved.
    /// @param statement_tag prepared statement being executed; defaults to an
    /// invalid index
    void createBindForSelect(AnyArray& data,
                             StatementTag statement_tag = NULL) override;

    /// @brief Copy received data into @ref SrvConfigInfo object
    ///
    /// Copies information about the shard configuration into a newly created
    /// @ref SrvConfigInfo object. Called in @ref executeSelect().
    ///
    /// @return pointer to a @ref SrvConfigInfoPtr object holding a
    /// pointer to the @ref SrvConfigInfo object returned.
    boost::any retrieve() override;

    /// @brief Generates a random UUID.
    ///
    /// @return string containing random UUID
    std::string generateUuid();

    /// @brief Common method of executing SELECT statements for the Cassandra
    ///     database.
    ///
    /// @param connection connection used to communicate with the Cassandra
    ///     database
    /// @param statement_tag prepared Cassandra statement being executed
    ///
    /// @return true if statement has been [applied], false otherwise.
    SrvConfigInfoCollection getCommon(CqlConnection& connection,
                                      StatementTag statement_tag);

    /// @brief Common method of executing INSERT statements for the shard
    ///     database in the Cassandra database.
    ///
    /// @param connection connection used to communicate with the Cassandra
    ///     database
    /// @param config_id identifier of the configuration being inserted
    /// @param json_data JSON being inserted
    /// @param generic_data generic data being inserted (e.g. yaml)
    /// @param statement_tag prepared Cassandra statement being executed
    ///
    /// @return true if statement has been [applied], false otherwise.
    bool insertCommon(CqlConnection& connection,
                      const std::string& config_id,
                      const std::string& json_data,
                      const std::string& generic_data,
                      StatementTag statement_tag);

    /// @brief Common method of executing SELECT statements for the Cassandra
    ///     database.
    /// @param connection connection used to communicate with the Cassandra
    ///     database
    /// @param config_id identifier of the configuration being inserted
    /// @param old_timestamp old time stamp
    /// @param json_data JSON being inserted
    /// @param generic_data generic data being inserted (e.g. yaml)
    /// @param statement_tag prepared Cassandra statement being executed
    ///
    /// @return true if statement has been [applied], false otherwise.
    bool updateCommon(CqlConnection& connection,
                      const std::string& config_id,
                      const int64_t old_timestamp,
                      const std::string& json_data,
                      const std::string& generic_data,
                      StatementTag statement_tag);

    /// @brief Cassandra statements
    static StatementMap tagged_statements_;

private:
    /// @brief Structure containing configuration data
    SrvConfigInfoPtr config_data_;
};  // CqlConfigExchange

constexpr StatementTag CqlConfigExchange::GET_CONFIGURATION4_TIMESTAMP;
constexpr StatementTag CqlConfigExchange::GET_CONFIGURATION6_TIMESTAMP;
constexpr StatementTag CqlConfigExchange::GET_GENERIC_CONFIGURATION4;
constexpr StatementTag CqlConfigExchange::GET_GENERIC_CONFIGURATION6;
constexpr StatementTag CqlConfigExchange::GET_JSON_CONFIGURATION4;
constexpr StatementTag CqlConfigExchange::GET_JSON_CONFIGURATION6;
constexpr StatementTag CqlConfigExchange::INSERT_CONFIGURATION4;
constexpr StatementTag CqlConfigExchange::INSERT_CONFIGURATION6;
constexpr StatementTag CqlConfigExchange::UPDATE_CONFIGURATION4;
constexpr StatementTag CqlConfigExchange::UPDATE_CONFIGURATION6;

StatementMap CqlConfigExchange::tagged_statements_ = {
    {GET_CONFIGURATION4_TIMESTAMP,   //
     {GET_CONFIGURATION4_TIMESTAMP,  //
      "SELECT config_id, timestamp "
      "FROM server_configuration4 "
      "LIMIT 1 "
     }},

    // GET_CONFIGURATION6_TIMESTAMP
    {GET_CONFIGURATION6_TIMESTAMP,   //
     {GET_CONFIGURATION6_TIMESTAMP,  //
      "SELECT config_id, timestamp "
      "FROM server_configuration6 "
      "LIMIT 1 "
     }},

    // GET_GENERIC_CONFIGURATION4
    {GET_GENERIC_CONFIGURATION4,   //
     {GET_GENERIC_CONFIGURATION4,  //
      "SELECT config_id, timestamp, generic_data "
      "FROM server_configuration4 "
      "LIMIT 1 "
     }},

    // GET_GENERIC_CONFIGURATION6
    {GET_GENERIC_CONFIGURATION6,   //
     {GET_GENERIC_CONFIGURATION6,  //
      "SELECT config_id, timestamp, generic_data "
      "FROM server_configuration6 LIMIT 1 "
     }},

    // GET_JSON_CONFIGURATION4
    {GET_JSON_CONFIGURATION4,   //
     {GET_JSON_CONFIGURATION4,  //
      "SELECT config_id, timestamp, json_data "
      "FROM server_configuration4 "
      "LIMIT 1 "
     }},

    // GET_JSON_CONFIGURATION6
    {GET_JSON_CONFIGURATION6,   //
     {GET_JSON_CONFIGURATION6,  //
      "SELECT config_id, timestamp, json_data "
      "FROM server_configuration6 "
      "LIMIT 1 "
     }},

    // INSERT_CONFIGURATION4
    {INSERT_CONFIGURATION4,   //
     {INSERT_CONFIGURATION4,  //
      "INSERT INTO server_configuration4 "
      "(config_id, timestamp, json_data, generic_data) "
      "VALUES (?, ?, ?, ?) IF NOT EXISTS "
     }},

    // INSERT_CONFIGURATION6
    {INSERT_CONFIGURATION6,   //
     {INSERT_CONFIGURATION6,  //
      "INSERT INTO server_configuration6 "
      "(config_id, timestamp, json_data, generic_data) "
      "VALUES (?, ?, ?, ?) IF NOT EXISTS "
     }},

    // UPDATE_CONFIGURATION4
    {UPDATE_CONFIGURATION4,   //
     {UPDATE_CONFIGURATION4,  //
      "UPDATE server_configuration4 "
      "SET timestamp = ?, json_data = ?, "
      "generic_data = ? WHERE config_id = ? "
      "IF timestamp = ? "
     }},

    // UPDATE_CONFIGURATION6
    {UPDATE_CONFIGURATION6,   //
     {UPDATE_CONFIGURATION6,  //
      "UPDATE server_configuration6 "
      "SET timestamp = ?, json_data = ?, "
      "generic_data = ? WHERE config_id = ? "
      "IF timestamp = ? "
     }}  //
};

CqlConfigExchange::CqlConfigExchange() : config_data_(new SrvConfigInfo()) {
}

CqlConfigExchange::~CqlConfigExchange() {
}

void
CqlConfigExchange::createBindForSelect(
    AnyArray& data, StatementTag statement_tag /* = NULL */) {
    // Start with a fresh array.
    data.clear();

    data.add(&config_data_->config_id_);
    data.add(&config_data_->timestamp_);
    if (statement_tag == CqlConfigExchange::GET_JSON_CONFIGURATION4 ||
        statement_tag == CqlConfigExchange::GET_JSON_CONFIGURATION6) {
        data.add(&config_data_->json_data_);
    } else if (statement_tag == CqlConfigExchange::GET_GENERIC_CONFIGURATION4 ||
               statement_tag == CqlConfigExchange::GET_GENERIC_CONFIGURATION6) {
        data.add(&config_data_->generic_data_);
    }
}

boost::any
CqlConfigExchange::retrieve() {
    SrvConfigInfoPtr config(new SrvConfigInfo(*config_data_));
    return config;
}

std::string
CqlConfigExchange::generateUuid() {
    boost::uuids::random_generator gen;
    boost::uuids::uuid unique_id = gen();
    std::string config_id = boost::lexical_cast<std::string>(unique_id);
    return config_id;
}

SrvConfigInfoCollection
CqlConfigExchange::getCommon(CqlConnection& connection,
                             StatementTag statement_tag) {

    // Bind to array.
    AnyArray where_values;

    AnyArray collection =
        executeSelect(connection, where_values, statement_tag, true);

    SrvConfigInfoCollection result;

    if (collection.empty()) {
        return result;
    }

    for (boost::any& element : collection) {
        SrvConfigInfoPtr item(boost::any_cast<SrvConfigInfoPtr>(element));
        result.push_back(item);
    }

    return result;
}

bool
CqlConfigExchange::insertCommon(CqlConnection& connection,
                                const std::string& config_id,
                                const std::string& json_data,
                                const std::string& generic_data,
                                StatementTag statement_tag) {

    cass_int64_t config_timestamp = static_cast<cass_int64_t>(time(NULL));

    // Bind to array.
    AnyArray assigned_values;
    assigned_values.add(const_cast<std::string*>(&config_id));
    assigned_values.add(&config_timestamp);
    assigned_values.add(const_cast<std::string*>(&json_data));
    assigned_values.add(const_cast<std::string*>(&generic_data));

    executeMutation(connection, assigned_values, statement_tag);

    return true;
}

bool
CqlConfigExchange::updateCommon(CqlConnection& connection,
                                const std::string& config_id,
                                const int64_t old_timestamp,
                                const std::string& json_data,
                                const std::string& generic_data,
                                StatementTag statement_tag) {

    // config_timestamp
    cass_int64_t config_timestamp = static_cast<cass_int64_t>(time(NULL));
    cass_int64_t old_config_timestamp =
        static_cast<cass_int64_t>(old_timestamp);

    // Bind to array.
    AnyArray data;
    data.add(&config_timestamp);
    data.add(const_cast<std::string*>(&json_data));
    data.add(const_cast<std::string*>(&generic_data));
    data.add(const_cast<std::string*>(&config_id));
    data.add(&old_config_timestamp);

    executeMutation(connection, data, statement_tag);

    return true;
}

CqlSrvConfigMgr::CqlSrvConfigMgr(
    const DatabaseConnection::ParameterMap& parameters)
    : SrvConfigMgr(), dbconn_(parameters) {
    dbconn_.openDatabase();
    dbconn_.prepareStatements(CqlConfigExchange::tagged_statements_);
    dbconn_.prepareStatements(CqlConfigVersionExchange::tagged_statements_);
}

CqlSrvConfigMgr::~CqlSrvConfigMgr() {
}

SrvConfigInfoPtr
CqlSrvConfigMgr::getConfig4Timestamp() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_CONFIG4_TIMESTAMP);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    SrvConfigInfoCollection collection = config_exchange->getCommon(
        dbconn_, CqlConfigExchange::GET_CONFIGURATION4_TIMESTAMP);

    transaction.commit();

    SrvConfigInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

SrvConfigInfoPtr
CqlSrvConfigMgr::getConfig6Timestamp() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_CONFIG6_TIMESTAMP);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    SrvConfigInfoCollection collection = config_exchange->getCommon(
        dbconn_, CqlConfigExchange::GET_CONFIGURATION6_TIMESTAMP);

    transaction.commit();

    SrvConfigInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

SrvConfigInfoPtr
CqlSrvConfigMgr::getGenericConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_CONFIG4_GENERIC);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    SrvConfigInfoCollection collection = config_exchange->getCommon(
        dbconn_, CqlConfigExchange::GET_GENERIC_CONFIGURATION4);

    transaction.commit();

    SrvConfigInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

SrvConfigInfoPtr
CqlSrvConfigMgr::getGenericConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_CONFIG6_GENERIC);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    SrvConfigInfoCollection collection = config_exchange->getCommon(
        dbconn_, CqlConfigExchange::GET_GENERIC_CONFIGURATION6);

    transaction.commit();

    SrvConfigInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

SrvConfigInfoPtr
CqlSrvConfigMgr::getJsonConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_CONFIG4_JSON);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    SrvConfigInfoCollection collection = config_exchange->getCommon(
        dbconn_, CqlConfigExchange::GET_JSON_CONFIGURATION4);

    transaction.commit();

    SrvConfigInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

SrvConfigInfoPtr
CqlSrvConfigMgr::getJsonConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SRV_CONFIG6_JSON);

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    SrvConfigInfoCollection collection = config_exchange->getCommon(
        dbconn_, CqlConfigExchange::GET_JSON_CONFIGURATION6);

    transaction.commit();

    SrvConfigInfoPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return result;
}

std::string
CqlSrvConfigMgr::getType() const {
    return std::string("cql");
}

VersionPair
CqlSrvConfigMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_VERSION);

    std::unique_ptr<CqlVersionExchange> version_exchange(
        new CqlVersionExchange());
    return version_exchange->retrieveVersion(dbconn_);
}

std::string
CqlSrvConfigMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "CQL backend " << CQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << CQL_SCHEMA_VERSION_MINOR;
    tmp << ", library cassandra_static " << CASS_VERSION_MAJOR;
    tmp << "." << CASS_VERSION_MINOR;
    tmp << "." << CASS_VERSION_PATCH;
    return tmp.str();
}

bool
CqlSrvConfigMgr::updateConfig4(const int64_t config_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_REQUEST_UPDATE_SRV_CONFIG4);

    // Initiate CQL transaction as we will have to update the config
    // from two steps and we don't want anybody else to write another
    // config between these two steps:
    // Step 1: Read the current configuration timestamp from database.
    // Step 2: Check if the provided configuration timestamp is
    // the same with the existing one from database.
    // Step 3: Update the configuration on the server.
    // If there is no configuration on the server then insert a new one but
    // also using transactions because we don't want another user to insert also
    // a new configuration in the same time.

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    SrvConfigInfoPtr current_config = getConfig4Timestamp();

    if (!current_config) {
        if (insertConfig4(json_data, generic_data)) {
            transaction.commit();
            return true;
        }
        return false;
    }

    if (!updateConfig4(current_config->config_id_, config_timestamp, json_data,
                       generic_data)) {
        // The configuration timestamp has been changed since the last
        // configuration read until this update.

        LOG_WARN(dhcpsrv_logger,
                 DHCPSRV_CQL_UPDATE_SRV_CONFIG4_TIMESTAMP_CHANGED)
            .arg(config_timestamp)
            .arg(current_config->timestamp_);

        return false;
    }

    transaction.commit();

    return true;
}

bool
CqlSrvConfigMgr::updateConfig6(const int64_t config_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_REQUEST_UPDATE_SRV_CONFIG6);

    // Initiate CQL transaction as we will have to update the config
    // from two steps and we don't want anybody else to write another
    // config between these two steps:
    // Step 1: Read the current configuration timestamp from database.
    // Step 2: Check if the provided configuration timestamp is
    // the same with the existing one from database.
    // Step 3: Update the configuration on the server.
    // If there is no configuration on the server then insert a new one but
    // also using transactions because we don't want another user to insert also
    // a new configuration in the same time.

    // CqlTransaction rolls back the transaction on its destructor.

    // Begin the transaction.
    CqlTransaction transaction(dbconn_);

    SrvConfigInfoPtr current_config = getConfig6Timestamp();

    if (!current_config) {
        if (insertConfig6(json_data, generic_data)) {
            transaction.commit();
            return true;
        }
        return false;
    }

    if (!updateConfig6(current_config->config_id_, config_timestamp, json_data,
                       generic_data)) {
        // The configuration timestamp has been changed since the last
        // configuration read until this update.
        LOG_WARN(dhcpsrv_logger,
                 DHCPSRV_CQL_UPDATE_SRV_CONFIG6_TIMESTAMP_CHANGED)
            .arg(config_timestamp)
            .arg(current_config->timestamp_);

        return false;
    }

    transaction.commit();

    return true;
}

bool
CqlSrvConfigMgr::insertConfig4(const std::string& json_data,
                               const std::string& generic_data) const {
    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    const std::string config_id = config_exchange->generateUuid();

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_INSERT_SRV_CONFIG4)
        .arg(config_id);

    try {

        config_exchange->insertCommon(dbconn_, config_id, json_data,
                                      generic_data,
                                      CqlConfigExchange::INSERT_CONFIGURATION4);

    } catch (const Exception&) {
        return false;
    }

    return true;
}

bool
CqlSrvConfigMgr::insertConfig6(const std::string& json_data,
                               const std::string& generic_data) const {
    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    const std::string config_id = config_exchange->generateUuid();

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_INSERT_SRV_CONFIG6)
        .arg(config_id);

    try {
        config_exchange->insertCommon(dbconn_, config_id, json_data,
                                      generic_data,
                                      CqlConfigExchange::INSERT_CONFIGURATION6);
    } catch (const Exception&) {
        return false;
    }

    return true;
}

bool
CqlSrvConfigMgr::updateConfig4(const std::string& config_id,
                               const int64_t old_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_UPDATE_SRV_CONFIG4)
        .arg(config_id);

    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    try {
        config_exchange->updateCommon(dbconn_, config_id, old_timestamp,
                                      json_data, generic_data,
                                      CqlConfigExchange::UPDATE_CONFIGURATION4);
    } catch (const Exception&) {
        return false;
    }

    return true;
}

bool
CqlSrvConfigMgr::updateConfig6(const std::string& config_id,
                               const int64_t old_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_UPDATE_SRV_CONFIG6)
        .arg(config_id);

    std::unique_ptr<CqlConfigExchange> config_exchange(new CqlConfigExchange());
    try {
        config_exchange->updateCommon(dbconn_, config_id, old_timestamp,
                                      json_data, generic_data,
                                      CqlConfigExchange::UPDATE_CONFIGURATION6);
    } catch (const Exception&) {
        return false;
    }

    return true;
}

bool
CqlSrvConfigMgr::startTransaction() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_BEGIN_TRANSACTION);
    dbconn_.startTransaction();
    return true;
}

void
CqlSrvConfigMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_COMMIT);
    dbconn_.commit();
}

void
CqlSrvConfigMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ROLLBACK);
    dbconn_.rollback();
}

}  // namespace dhcp
}  // namespace isc
