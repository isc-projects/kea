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

#include <config.h>

#include <dhcpsrv/pgsql_srv_config_mgr.h>

#include <time.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/pgsql_connection.h>
#include <dhcpsrv/pgsql_exchange.h>

#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/static_assert.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <array>
#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

namespace {

/// @brief Prepared statements
std::array<PgSqlTaggedStatement, PgSqlSrvConfigMgr::NUM_STATEMENTS> tagged_statements = {
    {//
     // GET_VERSION
     {0,
      {OID_NONE},
      "GET_VERSION",
      "SELECT version, minor"
      " FROM config_schema_version"},

     // GET_CONFIGURATION4_TIMESTAMP
     {0,
      {OID_NONE},
      "GET_CONFIGURATION4_TIMESTAMP",
      "SELECT config_id, extract(epoch from timestamp)::bigint"
      " FROM server_configuration4 LIMIT 1"},

     // GET_CONFIGURATION6_TIMESTAMP
     {0,
      {OID_NONE},
      "GET_CONFIGURATION6_TIMESTAMP",
      "SELECT config_id, extract(epoch from timestamp)::bigint"
      " FROM server_configuration6 LIMIT 1"},

     // GET_JSON_CONFIGURATION4
     {0,
      {OID_NONE},
      "GET_JSON_CONFIGURATION4",
      "SELECT config_id, extract(epoch from timestamp)::bigint, json_data"
      " FROM server_configuration4 LIMIT 1"},

     // GET_JSON_CONFIGURATION6
     {0,
      {OID_NONE},
      "GET_JSON_CONFIGURATION6",
      "SELECT config_id, extract(epoch from timestamp)::bigint, json_data"
      " FROM server_configuration6 LIMIT 1"},

     // GET_GENERIC_CONFIGURATION4
     {0,
      {OID_NONE},
      "GET_GENERIC_CONFIGURATION4",
      "SELECT config_id, extract(epoch from timestamp)::bigint, generic_data"
      " FROM server_configuration4 LIMIT 1"},

     // GET_GENERIC_CONFIGURATION6
     {0,
      {OID_NONE},
      "GET_GENERIC_CONFIGURATION6",
      "SELECT config_id, extract(epoch from timestamp)::bigint, generic_data"
      " FROM server_configuration6 LIMIT 1"},

     // INSERT_CONFIGURATION4
     {4,
      {OID_VARCHAR, OID_TIMESTAMP, OID_BYTEA, OID_BYTEA},
      "INSERT_CONFIGURATION4",
      "INSERT INTO server_configuration4"
      " (config_id, timestamp, json_data, generic_data)"
      " VALUES ($1, $2, $3, $4)"},

     // INSERT_CONFIGURATION6
     {4,
      {OID_VARCHAR, OID_TIMESTAMP, OID_BYTEA, OID_BYTEA},
      "INSERT_CONFIGURATION6",
      "INSERT INTO server_configuration6"
      " (config_id, timestamp, json_data, generic_data)"
      " VALUES ($1, $2, $3, $4)"},

     // UPDATE_CONFIGURATION4
     {4,
      {OID_TIMESTAMP, OID_BYTEA, OID_BYTEA, OID_VARCHAR},
      "UPDATE_CONFIGURATION4",
      "UPDATE server_configuration4"
      " SET timestamp = $1, json_data = $2, generic_data = $3"
      " WHERE config_id = $4"},

     // UPDATE_CONFIGURATION6
     {4,
      {OID_TIMESTAMP, OID_BYTEA, OID_BYTEA, OID_VARCHAR},
      "UPDATE_CONFIGURATION6",
      "UPDATE server_configuration6"
      " SET timestamp = $1, json_data = $2, generic_data = $3"
      " WHERE config_id = $4"}}};

}  // namespace

PgSqlSrvConfigMgr::PgSqlSrvConfigMgr(const DatabaseConnection::ParameterMap& parameters)
    : conn_(parameters) {

    // Open the database.
    conn_.openDatabase();
    int i = 0;
    for (auto const& it : tagged_statements) {
        conn_.prepareStatement(it);
        ++i;
    }

    // Check that all statements have been prepared.
    BOOST_ASSERT(i == NUM_STATEMENTS);
}

PgSqlSrvConfigMgr::~PgSqlSrvConfigMgr() {
}

std::string PgSqlSrvConfigMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "PostgreSQL backend " << PG_SCHEMA_VERSION_MAJOR;
    tmp << "." << PG_SCHEMA_VERSION_MINOR;
    tmp << ", library " << PQlibVersion();
    return (tmp.str());
}

VersionPair PgSqlSrvConfigMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_VERSION);
    const StatementIndex stindex = PgSqlSrvConfigMgr::GET_VERSION;

    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name, 0, NULL, NULL, NULL, 0));
    conn_.checkStatementError(r, tagged_statements[stindex]);

    std::istringstream tmp;
    uint32_t major;
    tmp.str(PQgetvalue(r, 0, 0));
    tmp >> major;
    tmp.str("");
    tmp.clear();

    uint32_t minor;
    tmp.str(PQgetvalue(r, 0, 1));
    tmp >> minor;

    return (std::make_pair(major, minor));
}

bool PgSqlSrvConfigMgr::updateConfig4(int64_t config_timestamp,
                                      const std::string& json_data,
                                      const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_REQUEST_UPDATE_SRV_CONFIG4);

    // Initiate PgSQL transaction as we will have to update the config
    // from two steps and we don't want anybody else to write another
    // config between these two steps:
    // Step 1: Read the current configuration timestamp from database.
    // Step 2: Check if the provided configuration timestamp is
    // the same with the existing one from database.
    // Step 3: Update the configuration on the server.
    // If there is no configuration on the server then insert a new one but
    // also using transactions because we don't want another user to insert also
    // a new configuration in the same time.

    // PgSqlTransaction rolls back the transaction on its destructor.

    // begin the transaction
    PgSqlTransaction transaction(conn_);

    SrvConfigInfoPtr current_config = getConfig4Timestamp();

    if (!current_config) {
        if (insertConfig4(json_data, generic_data)) {
            transaction.commit();
            return true;
        }
        return false;
    }

    if (!updateConfig4(current_config->config_id_, json_data, generic_data)) {
        // The configuration timestamp has been changed since the last
        // configuration read until this update.

        LOG_WARN(dhcpsrv_logger, DHCPSRV_PGSQL_UPDATE_SRV_CONFIG4_TIMESTAMP_CHANGED)
            .arg(config_timestamp)
            .arg(current_config->timestamp_);

        return false;
    }

    transaction.commit();
    return true;
}

bool PgSqlSrvConfigMgr::updateConfig6(int64_t config_timestamp,
                                      const std::string& json_data,
                                      const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_REQUEST_UPDATE_SRV_CONFIG6);

    // Initiate PgSQL transaction as we will have to update the config
    // from two steps and we don't want anybody else to write another
    // config between these two steps:
    // Step 1: Read the current configuration timestamp from database.
    // Step 2: Check if the provided configuration timestamp is
    // the same with the existing one from database.
    // Step 3: Update the configuration on the server.
    // If there is no configuration on the server then insert a new one but
    // also using transactions because we don't want another user to insert also
    // a new configuration in the same time.

    // PgSqlTransaction rolls back the transaction on its destructor.

    // begin the transaction
    PgSqlTransaction transaction(conn_);

    SrvConfigInfoPtr current_config = getConfig6Timestamp();

    if (!current_config) {
        if (insertConfig6(json_data, generic_data)) {
            transaction.commit();
            return true;
        }
        return false;
    }

    if (!updateConfig6(current_config->config_id_, json_data, generic_data)) {
        // The configuration timestamp has been changed since the last
        // configuration read until this update.

        LOG_WARN(dhcpsrv_logger, DHCPSRV_PGSQL_UPDATE_SRV_CONFIG6_TIMESTAMP_CHANGED)
            .arg(config_timestamp)
            .arg(current_config->timestamp_);

        return false;
    }

    transaction.commit();
    return true;
}

SrvConfigInfoPtr PgSqlSrvConfigMgr::getConfig4Timestamp() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SRV_CONFIG4_TIMESTAMP);

    const StatementIndex stindex = PgSqlSrvConfigMgr::GET_CONFIGURATION4_TIMESTAMP;
    return getConfigTimestampCommon(stindex);
}

SrvConfigInfoPtr PgSqlSrvConfigMgr::getConfig6Timestamp() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SRV_CONFIG6_TIMESTAMP);

    const StatementIndex stindex = PgSqlSrvConfigMgr::GET_CONFIGURATION6_TIMESTAMP;
    return getConfigTimestampCommon(stindex);
}

SrvConfigInfoPtr PgSqlSrvConfigMgr::getConfigTimestampCommon(StatementIndex stindex) const {
    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name, 0, NULL, NULL, NULL, 0));
    conn_.checkStatementError(r, tagged_statements[stindex]);

    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
    if (affected_rows < 1) {
        return SrvConfigInfoPtr();
    }

    std::istringstream tmp;
    std::string config_id;
    std::string db_timestamp;

    tmp.str(PQgetvalue(r, 0, 0));
    tmp >> config_id;
    tmp.str("");
    tmp.clear();

    tmp.str(PQgetvalue(r, 0, 1));
    tmp >> db_timestamp;

    time_t timestamp = PgSqlExchange::convertFromDatabaseTime(db_timestamp);

    SrvConfigInfoPtr srvConf = boost::make_shared<SrvConfigInfo>();
    srvConf->config_id_ = config_id;
    srvConf->timestamp_ = timestamp;

    return srvConf;
}

SrvConfigInfoPtr PgSqlSrvConfigMgr::getJsonConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SRV_CONFIG4_JSON);
    const StatementIndex stindex = PgSqlSrvConfigMgr::GET_JSON_CONFIGURATION4;
    SrvConfigInfoPtr result = getConfigCommon(stindex);
    result->json_data_ = result->generic_data_;
    result->generic_data_ = "";
    return result;
}

SrvConfigInfoPtr PgSqlSrvConfigMgr::getJsonConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SRV_CONFIG6_JSON);
    const StatementIndex stindex = PgSqlSrvConfigMgr::GET_JSON_CONFIGURATION6;
    SrvConfigInfoPtr result = getConfigCommon(stindex);
    result->json_data_ = result->generic_data_;
    result->generic_data_ = "";
    return result;
}

SrvConfigInfoPtr PgSqlSrvConfigMgr::getGenericConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SRV_CONFIG4_GENERIC);
    const StatementIndex stindex = PgSqlSrvConfigMgr::GET_GENERIC_CONFIGURATION4;
    return getConfigCommon(stindex);
}

SrvConfigInfoPtr PgSqlSrvConfigMgr::getGenericConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SRV_CONFIG6_GENERIC);
    const StatementIndex stindex = PgSqlSrvConfigMgr::GET_GENERIC_CONFIGURATION6;
    return getConfigCommon(stindex);
}

SrvConfigInfoPtr PgSqlSrvConfigMgr::getConfigCommon(StatementIndex stindex) const {
    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name, 0, NULL, NULL, NULL, 0));

    conn_.checkStatementError(r, tagged_statements[stindex]);
    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
    if (affected_rows < 1) {
        return SrvConfigInfoPtr();
    }

    std::istringstream tmp;
    std::string config_id;
    std::string db_timestamp;
    std::string config_data;

    tmp.str(PQgetvalue(r, 0, 0));
    tmp >> config_id;
    tmp.str("");
    tmp.clear();

    tmp.str(PQgetvalue(r, 0, 1));
    tmp >> db_timestamp;
    tmp.str("");
    tmp.clear();

    time_t timestamp = PgSqlExchange::convertFromDatabaseTime(db_timestamp);

    size_t bytes_converted;
    unsigned char* bytes = PQunescapeBytea(
        reinterpret_cast<const unsigned char*>(PQgetvalue(r, 0, 2)), &bytes_converted);

    if (bytes) {
        config_data.assign(bytes, bytes + bytes_converted);
    }
    PQfreemem(bytes);

    SrvConfigInfoPtr srvConf = boost::make_shared<SrvConfigInfo>();
    srvConf->config_id_ = config_id;
    srvConf->timestamp_ = timestamp;
    srvConf->generic_data_ = config_data;

    return srvConf;
}

bool PgSqlSrvConfigMgr::insertConfig4(const std::string& json_data,
                                      const std::string& generic_data) const {
    boost::uuids::random_generator gen;
    boost::uuids::uuid unique_id = gen();
    std::string config_id = boost::lexical_cast<std::string>(unique_id);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_INSERT_SRV_CONFIG4)
        .arg(config_id);

    const StatementIndex stindex = PgSqlSrvConfigMgr::INSERT_CONFIGURATION4;
    return insertConfigCommon(stindex, config_id, json_data, generic_data);
}

bool PgSqlSrvConfigMgr::insertConfig6(const std::string& json_data,
                                      const std::string& generic_data) const {
    boost::uuids::random_generator gen;
    boost::uuids::uuid unique_id = gen();
    std::string config_id = boost::lexical_cast<std::string>(unique_id);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_INSERT_SRV_CONFIG6)
        .arg(config_id);

    const StatementIndex stindex = PgSqlSrvConfigMgr::INSERT_CONFIGURATION6;
    return insertConfigCommon(stindex, config_id, json_data, generic_data);
}

bool PgSqlSrvConfigMgr::insertConfigCommon(StatementIndex stindex,
                                           const std::string& config_id,
                                           const std::string& json_data,
                                           const std::string& generic_data) const {
    PsqlBindArray bind_array;

    std::vector<uint8_t> json;
    json.assign(json_data.c_str(), json_data.c_str() + json_data.size());

    std::vector<uint8_t> generic;
    generic.assign(generic_data.c_str(), generic_data.c_str() + generic_data.size());
    std::string timestamp_str = PgSqlExchange::convertToDatabaseTime(time(NULL));

    try {
        bind_array.add(config_id);
        bind_array.add(timestamp_str);
        bind_array.add(json);
        bind_array.add(generic);
        PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name,
                                     tagged_statements[stindex].nbparams, &bind_array.values_[0],
                                     &bind_array.lengths_[0], &bind_array.formats_[0], 0));

        conn_.checkStatementError(r, tagged_statements[stindex]);
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Could not create bind array to insert configuration "
                                        << ", reason: " << ex.what());
    }
    return true;
}

bool PgSqlSrvConfigMgr::updateConfig4(const std::string& config_id,
                                      const std::string& json_data,
                                      const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_UPDATE_SRV_CONFIG4)
        .arg(config_id);

    const StatementIndex stindex = PgSqlSrvConfigMgr::UPDATE_CONFIGURATION4;
    return updateConfigCommon(stindex, config_id, json_data, generic_data);
}

bool PgSqlSrvConfigMgr::updateConfig6(const std::string& config_id,
                                      const std::string& json_data,
                                      const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_UPDATE_SRV_CONFIG6)
        .arg(config_id);

    const StatementIndex stindex = PgSqlSrvConfigMgr::UPDATE_CONFIGURATION6;
    return updateConfigCommon(stindex, config_id, json_data, generic_data);
}

bool PgSqlSrvConfigMgr::updateConfigCommon(StatementIndex stindex,
                                           const std::string& config_id,
                                           const std::string& json_data,
                                           const std::string& generic_data) const {
    PsqlBindArray bind_array;

    std::vector<uint8_t> json;
    json.assign(json_data.c_str(), json_data.c_str() + json_data.size());

    std::vector<uint8_t> generic;
    generic.assign(generic_data.c_str(), generic_data.c_str() + generic_data.size());

    std::string timestamp_str = PgSqlExchange::convertToDatabaseTime(time(NULL));

    try {
        bind_array.add(timestamp_str);
        bind_array.add(json);
        bind_array.add(generic);
        bind_array.add(config_id);
        PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name,
                                     tagged_statements[stindex].nbparams, &bind_array.values_[0],
                                     &bind_array.lengths_[0], &bind_array.formats_[0], 0));

        conn_.checkStatementError(r, tagged_statements[stindex]);
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Could not create bind array to insert configuration "
                                        << ", reason: " << ex.what());
    }
    return true;
}

bool PgSqlSrvConfigMgr::startTransaction() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_BEGIN_TRANSACTION);
    PGresult* r = PQexec(conn_, "START TRANSACTION");
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        PQclear(r);
        isc_throw(DbOperationError, "start transaction failed: " << error_message);
    }

    PQclear(r);

    return true;
}

void PgSqlSrvConfigMgr::commit() {
    conn_.commit();
}

void PgSqlSrvConfigMgr::rollback() {
    conn_.rollback();
}

}  // namespace dhcp
}  // namespace isc
