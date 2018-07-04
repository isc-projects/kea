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

#include <dhcpsrv/pgsql_srv_config_master_mgr.h>

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

namespace {

using namespace isc::dhcp;

/// @brief Prepared statements
std::array<PgSqlTaggedStatement, PgSqlSrvConfigMasterMgr::NUM_STATEMENTS> tagged_statements = {{
    // INSERT_SERVER_CONFIG4
    {5,
     {OID_VARCHAR, OID_TIMESTAMP, OID_BYTEA, OID_BYTEA, OID_VARCHAR},
     "INSERT_SERVER_CONFIG4",
     "INSERT INTO server_configuration4"
     " (instance_id, timestamp, server_config, config_database, config_database_name)"
     " VALUES ($1, $2, $3, $4, $5)"},

    // INSERT_SERVER_CONFIG6
    {5,
     {OID_VARCHAR, OID_TIMESTAMP, OID_BYTEA, OID_BYTEA, OID_VARCHAR},
     "INSERT_SERVER_CONFIG6",
     "INSERT INTO server_configuration6"
     " (instance_id, timestamp, server_config, config_database, config_database_name)"
     " VALUES ($1, $2, $3, $4, $5)"},

    // GET_CONFIGURATION4_BY_SRV_ID
    {1,
     {OID_VARCHAR},
     "GET_CONFIGURATION4_BY_SRV_ID",
     "SELECT instance_id, extract(epoch from timestamp)::bigint, server_config, config_database, "
     "config_database_name"
     " FROM server_configuration4"
     " WHERE instance_id = $1"},

    // GET_CONFIGURATION6_BY_SRV_ID
    {1,
     {OID_VARCHAR},
     "GET_CONFIGURATION6_BY_SRV_ID",
     "SELECT instance_id, extract(epoch from timestamp)::bigint, server_config, config_database, "
     "config_database_name"
     " FROM server_configuration6"
     " WHERE instance_id = $1"},

    // GET_CONFIGURATION4_BY_SHARD_DB
    {1,
     {OID_VARCHAR},
     "GET_CONFIGURATION4_BY_SHARD_DB",
     "SELECT instance_id, extract(epoch from timestamp)::bigint, server_config, config_database, "
     "config_database_name"
     " FROM server_configuration4"
     " WHERE config_database_name = $1"},

    // GET_CONFIGURATION6_BY_SHARD_DB
    {1,
     {OID_VARCHAR},
     "GET_CONFIGURATION6_BY_SHARD_DB",
     "SELECT instance_id, extract(epoch from timestamp)::bigint, server_config, config_database, "
     "config_database_name"
     " FROM server_configuration6"
     " WHERE config_database_name = $1"},

    // GET_CONFIGURATION4_TIMESTAMP
    {1,
     {OID_VARCHAR},
     "GET_CONFIGURATION4_TIMESTAMP",
     "SELECT extract(epoch from timestamp)::bigint"
     " FROM server_configuration4"
     " WHERE instance_id = $1"},

    // GET_CONFIGURATION6_TIMESTAMP
    {1,
     {OID_VARCHAR},
     "GET_CONFIGURATION6_TIMESTAMP",
     "SELECT extract(epoch from timestamp)::bigint"
     " FROM server_configuration6"
     " WHERE instance_id = $1"},

    // DELETE_SERVER_CONFIG4
    {0, {OID_NONE}, "DELETE_SERVER_CONFIG4", "TRUNCATE server_configuration4"},

    // DELETE_SERVER_CONFIG6,
    {0, {OID_NONE}, "DELETE_SERVER_CONFIG6", "TRUNCATE server_configuration6"},

    // GET_SERVERS_CONFIG4_SHARDS_NAME
    {0,
     {OID_NONE},
     "GET_SERVERS_CONFIG4_SHARDS_NAME",
     "SELECT config_database_name"
     " FROM server_configuration4"},

    // GET_SERVERS_CONFIG6_SHARDS_NAME
    {0,
     {OID_NONE},
     "GET_SERVERS_CONFIG6_SHARDS_NAME",
     "SELECT config_database_name"
     " FROM server_configuration6"},

    // GET_VERSION
    {0,
     {OID_NONE},
     "GET_VERSION",
     "SELECT version, minor"
     " FROM master_schema_version"},
}};

}  // namespace

namespace isc {
namespace dhcp {

/// @brief Manages exchanging of master configurations with PostgreSQL.
class PgSqlMasterConfigExchange : public PgSqlExchange {
public:
    /// @brief Default constructor
    PgSqlMasterConfigExchange() : config_(boost::make_shared<SrvConfigMasterInfo>()) {
        BOOST_STATIC_ASSERT(COLUMN_COUNT == 5);

        // Set column names (for error reporting).
        columns_.push_back("instance_id");
        columns_.push_back("timestamp");
        columns_.push_back("server_config");
        columns_.push_back("config_database");
        columns_.push_back("config_database_name");
    }

    virtual ~PgSqlMasterConfigExchange() {
    }

    /// @brief Creates the bind array for sending @ref SrvConfigMasterInfo data
    ///     to the database.
    ///
    /// Converts each @ref SrvConfigMasterInfo member into a
    /// PostgreSQL-compatible type and adds it to the bind array. Note that the
    /// array additions must occur in the same order that the SQL statement
    /// specifies. By convention all columns in the table are explicitly listed
    /// in the SQL statements in the same order as they occur in the table.
    ///
    /// @param instance_id ID of the server that has it's configuration written to the database
    /// @param server_config actual configuration of the server that is written to the database
    /// @param config_database configuration to be used on the shard
    /// @param config_database_name name of the shard whose configuration is being added
    /// @param[out] bind_array array to populate with the configuration data
    ///
    /// @throw DbOperationError if bind_array cannot be populated
    void createBindForSend(const std::string& instance_id,
                           const std::string& server_config,
                           const std::string& config_database,
                           const std::string& config_database_name,
                           PsqlBindArray& bind_array) {
        // Convert to PostgreSQL-compatible types.
        config_->instance_id_ = instance_id;
        timestamp_ = PgSqlExchange::convertToDatabaseTime(time(NULL));
        server_config_.assign(server_config.c_str(), server_config.c_str() + server_config.size());
        config_database_.assign(config_database.c_str(),
                                config_database.c_str() + config_database.size());
        config_->config_database_name_ = config_database_name;

        try {
            // Bind to array.
            bind_array.add(config_->instance_id_);
            bind_array.add(timestamp_);
            bind_array.add(server_config_);
            bind_array.add(config_database_);
            bind_array.add(config_->config_database_name_);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Could not create bind array for "
                                        "server_configuration[4|6] with server ID: "
                                            << instance_id
                                            << ", shard name: " << config_database_name
                                            << ", server configuration: " << server_config
                                            << ", reason: " << ex.what());
        }
    }

    /// @brief Creates a @ref SrvConfigMasterInfo object from a given row in a
    ///     result set.
    ///
    /// @param r result set containing one or rows from the server_configuration[4|6] table
    /// @param row row number within the result set from to create the @ref SrvConfigMasterInfo
    ///     object
    ///
    /// @return SrvConfigMasterInfoPtr to the newly created @ref SrvConfigMasterInfo object
    ///
    /// @throw DbOperationError if the server configuration object cannot be created
    SrvConfigMasterInfoPtr convertFromDatabase(const PgSqlResult& r, const int row) {
        SrvConfigMasterInfoPtr config = boost::make_shared<SrvConfigMasterInfo>();
        try {
            // Retrieve column values.
            size_t converted_bytes;
            unsigned char* bytes;

            // instance_id
            getColumnValue(r, row, INSTANCE_ID, config->instance_id_);

            // timestamp
            std::string timestamp_s = getRawColumnValue(r, row, TIME_STAMP);
            config->timestamp_ = convertFromDatabaseTime(timestamp_s);

            // server_config
            bytes = PQunescapeBytea(
                reinterpret_cast<const unsigned char*>(PQgetvalue(r, row, SERVER_CONFIG)),
                &converted_bytes);

            if (bytes) {
                config->server_config_.assign(bytes, bytes + converted_bytes);
            }
            PQfreemem(bytes);

            // config_database
            bytes = PQunescapeBytea(
                reinterpret_cast<const unsigned char*>(PQgetvalue(r, row, CONFIG_DATABASE)),
                &converted_bytes);

            if (bytes) {
                config->config_database_.assign(bytes, bytes + converted_bytes);
            }
            PQfreemem(bytes);

            // config_database_name
            getColumnValue(r, row, CONFIG_DATABASE_NAME, config->config_database_name_);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Could not convert data to server "
                                        "configuration object, reason: "
                                            << ex.what());
        }
        return config;
    }

    // C++98 standard ensures enum values are consecutive starting with 0.
    // Don't add ordinal numbers in order to facilitate further addition of enum
    // values. N_OF_COLUMNS is always last.
    enum Columns {
        INSTANCE_ID,
        TIME_STAMP,
        SERVER_CONFIG,
        CONFIG_DATABASE,
        CONFIG_DATABASE_NAME,
        COLUMN_COUNT
    };

    /// @brief Configuration object used when sending to the database.
    /// Being a class member ensures that it remains in scope while any bindings
    /// that refer to its contents are in use.
    SrvConfigMasterInfoPtr config_;

    /// @brief Configuration specific members used for binding and conversion.
    /// @{
    std::vector<uint8_t> config_database_;
    std::vector<uint8_t> server_config_;
    std::string timestamp_;
    /// @}
};

PgSqlSrvConfigMasterMgr::PgSqlSrvConfigMasterMgr(const DatabaseConnection::ParameterMap& parameters)
    : conn_(parameters), exchange_(new PgSqlMasterConfigExchange()) {

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

PgSqlSrvConfigMasterMgr::~PgSqlSrvConfigMasterMgr() {
}

std::string PgSqlSrvConfigMasterMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "PostgreSQL backend " << PG_SCHEMA_VERSION_MAJOR << "." << PG_SCHEMA_VERSION_MINOR;
    return tmp.str();
}

VersionPair PgSqlSrvConfigMasterMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_VERSION);
    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_VERSION;

    PgSqlResult r(
        PQexecPrepared(conn_, tagged_statements[statement_index].name, 0, NULL, NULL, NULL, 0));
    conn_.checkStatementError(r, tagged_statements[statement_index]);

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

bool PgSqlSrvConfigMasterMgr::addServerConfig4(const std::string& instance_id,
                                               const std::string& server_config,
                                               const std::string& config_database,
                                               const std::string& config_database_name) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_INSERT_SRV_MASTER_CONFIG4)
        .arg(instance_id)
        .arg(config_database_name);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::INSERT_SERVER_CONFIG4;
    return addCommonServerConfiguration(statement_index, instance_id, server_config,
                                        config_database, config_database_name);
}

bool PgSqlSrvConfigMasterMgr::addServerConfig6(const std::string& instance_id,
                                               const std::string& server_config,
                                               const std::string& config_database,
                                               const std::string& config_database_name) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_INSERT_SRV_MASTER_CONFIG6)
        .arg(instance_id)
        .arg(config_database_name);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::INSERT_SERVER_CONFIG6;
    return addCommonServerConfiguration(statement_index, instance_id, server_config,
                                        config_database, config_database_name);
}

bool PgSqlSrvConfigMasterMgr::clearServersConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_CLEAR_SRV_MASTER_CONFIG4);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::DELETE_SERVER_CONFIG4;
    PgSqlResult r(
        PQexecPrepared(conn_, tagged_statements[statement_index].name, 0, NULL, NULL, NULL, 0));
    conn_.checkStatementError(r, tagged_statements[statement_index]);

    return true;
}

bool PgSqlSrvConfigMasterMgr::clearServersConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_CLEAR_SRV_MASTER_CONFIG6);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::DELETE_SERVER_CONFIG6;
    PgSqlResult r(
        PQexecPrepared(conn_, tagged_statements[statement_index].name, 0, NULL, NULL, NULL, 0));
    conn_.checkStatementError(r, tagged_statements[statement_index]);

    return true;
}

SrvConfigMasterInfoPtr PgSqlSrvConfigMasterMgr::getConfig4(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SRV_MASTER_CONFIG4)
        .arg(instance_id);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_CONFIGURATION4_BY_SRV_ID;
    return getCommonServerConfigurationByInstanceId(statement_index, instance_id);
}

SrvConfigMasterInfoPtr PgSqlSrvConfigMasterMgr::getConfig6(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SRV_MASTER_CONFIG6)
        .arg(instance_id);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_CONFIGURATION6_BY_SRV_ID;
    return getCommonServerConfigurationByInstanceId(statement_index, instance_id);
}

bool PgSqlSrvConfigMasterMgr::getConfig4(
    const std::string& config_database_name,
    std::vector<SrvConfigMasterInfoPtr>& server_configurations) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SRV_MASTER_CONFIG4_SHARD_DB)
        .arg(config_database_name);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_CONFIGURATION4_BY_SHARD_DB;
    return getCommonServerConfigurationByShardName(statement_index, config_database_name,
                                                   server_configurations);
}

bool PgSqlSrvConfigMasterMgr::getConfig6(
    const std::string& config_database_name,
    std::vector<SrvConfigMasterInfoPtr>& server_configurations) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SRV_MASTER_CONFIG6_SHARD_DB)
        .arg(config_database_name);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_CONFIGURATION6_BY_SHARD_DB;
    return getCommonServerConfigurationByShardName(statement_index, config_database_name,
                                                   server_configurations);
}

SrvConfigMasterInfoPtr
PgSqlSrvConfigMasterMgr::getMasterConfig4Timestamp(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SRV_MASTER_CONFIG4_TIMESTAMP)
        .arg(instance_id);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_CONFIGURATION4_TIMESTAMP;
    return getCommonTimestampFromMasterServerConfiguration(statement_index, instance_id);
}

SrvConfigMasterInfoPtr
PgSqlSrvConfigMasterMgr::getMasterConfig6Timestamp(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SRV_MASTER_CONFIG6_TIMESTAMP)
        .arg(instance_id);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_CONFIGURATION6_TIMESTAMP;
    return getCommonTimestampFromMasterServerConfiguration(statement_index, instance_id);
}

bool PgSqlSrvConfigMasterMgr::getServersConfig4ShardsName(
    std::set<std::string>& shards_list) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SRV_MASTER_CONFIG4_SHARDS_NAME);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_SERVERS_CONFIG4_SHARDS_NAME;
    return getCommonShardNamesFromMasterServerConfiguration(statement_index, shards_list);
}

bool PgSqlSrvConfigMasterMgr::getServersConfig6ShardsName(
    std::set<std::string>& shards_list) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SRV_MASTER_CONFIG6_SHARDS_NAME);

    const StatementIndex statement_index = PgSqlSrvConfigMasterMgr::GET_SERVERS_CONFIG6_SHARDS_NAME;
    return getCommonShardNamesFromMasterServerConfiguration(statement_index, shards_list);
}

bool PgSqlSrvConfigMasterMgr::startTransaction() {
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

void PgSqlSrvConfigMasterMgr::commit() {
    conn_.commit();
}

void PgSqlSrvConfigMasterMgr::rollback() {
    conn_.rollback();
}

bool PgSqlSrvConfigMasterMgr::addCommonServerConfiguration(
    const StatementIndex statement_index,
    const std::string& instance_id,
    const std::string& server_config,
    const std::string& config_database,
    const std::string& config_database_name) const {
    try {
        // Bind to array.
        PsqlBindArray bind_array;
        exchange_->createBindForSend(instance_id, server_config, config_database,
                                     config_database_name, bind_array);

        // Execute query.
        PgSqlResult r(PQexecPrepared(conn_, tagged_statements[statement_index].name,
                                     tagged_statements[statement_index].nbparams,
                                     &bind_array.values_[0], &bind_array.lengths_[0],
                                     &bind_array.formats_[0], 0));

        // Check for errors.
        conn_.checkStatementError(r, tagged_statements[statement_index]);
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Cannot add server configuration into the "
                                    "master database, reason: "
                                        << ex.what());
    }

    return true;
}

SrvConfigMasterInfoPtr PgSqlSrvConfigMasterMgr::getCommonServerConfigurationByInstanceId(
    const StatementIndex statement_index, const std::string& instance_id) const {
    SrvConfigMasterInfoPtr config;
    try {
        // Bind to array.
        PsqlBindArray bind_array;
        bind_array.add(instance_id);

        // Execute query.
        PgSqlResult r(PQexecPrepared(conn_, tagged_statements[statement_index].name,
                                     tagged_statements[statement_index].nbparams,
                                     &bind_array.values_[0], &bind_array.lengths_[0],
                                     &bind_array.formats_[0], 0));

        // Check for errors.
        conn_.checkStatementError(r, tagged_statements[statement_index]);

        // Populate shard configurations.
        int rows = PQntuples(r);
        for (int i = 0; i < rows; ++i) {
            config = exchange_->convertFromDatabase(r, i);
        }
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Cannot retrieve server configuration from "
                                    "the master database, reason: "
                                        << ex.what());
    }

    return config;
}

bool PgSqlSrvConfigMasterMgr::getCommonServerConfigurationByShardName(
    const StatementIndex statement_index,
    const std::string& config_database_name,
    std::vector<SrvConfigMasterInfoPtr>& server_configurations) const {

    server_configurations.clear();

    try {
        // Bind to array.
        PsqlBindArray bind_array;
        bind_array.add(config_database_name);

        // Execute query.
        PgSqlResult r(PQexecPrepared(conn_, tagged_statements[statement_index].name,
                                     tagged_statements[statement_index].nbparams,
                                     &bind_array.values_[0], &bind_array.lengths_[0],
                                     &bind_array.formats_[0], 0));

        // Check for errors.
        conn_.checkStatementError(r, tagged_statements[statement_index]);

        // Populate configuration object.
        int rows = PQntuples(r);
        for (int i = 0; i < rows; ++i) {
            server_configurations.push_back(exchange_->convertFromDatabase(r, i));
        }
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Cannot retrieve server configuration from "
                                    "the master database, reason: "
                                        << ex.what());
    }

    return true;
}

SrvConfigMasterInfoPtr PgSqlSrvConfigMasterMgr::getCommonTimestampFromMasterServerConfiguration(
    const StatementIndex statement_index, const std::string& instance_id) const {
    SrvConfigMasterInfoPtr config = boost::make_shared<SrvConfigMasterInfo>();
    try {
        // Bind to array.
        PsqlBindArray bind_array;
        bind_array.add(instance_id);

        // Execute query.
        PgSqlResult r(PQexecPrepared(conn_, tagged_statements[statement_index].name,
                                     tagged_statements[statement_index].nbparams,
                                     &bind_array.values_[0], &bind_array.lengths_[0],
                                     &bind_array.formats_[0], 0));

        // Check for errors.
        conn_.checkStatementError(r, tagged_statements[statement_index]);
        int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
        if (affected_rows < 1) {
            return config;
        }

        // Populate timestamp.
        std::istringstream tmp;
        std::string timestamp_s;

        tmp.str(PQgetvalue(r, 0, 0));
        tmp >> timestamp_s;

        time_t timestamp = PgSqlExchange::convertFromDatabaseTime(timestamp_s);

        config->timestamp_ = timestamp;
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError,
                  "Cannot retrieve timestamp from the master database, reason: " << ex.what());
    }

    return config;
}

bool PgSqlSrvConfigMasterMgr::getCommonShardNamesFromMasterServerConfiguration(
    const StatementIndex statement_index, std::set<std::string>& shards) const {
    shards.clear();

    try {
        // Execute query.
        PgSqlResult r(
            PQexecPrepared(conn_, tagged_statements[statement_index].name, 0, NULL, NULL, NULL, 0));

        // Check for errors.
        conn_.checkStatementError(r, tagged_statements[statement_index]);
        int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
        if (affected_rows < 1) {
            return false;
        }

        // Populate shard names.
        int rows = PQntuples(r);
        for (int i = 0; i < rows; ++i) {
            std::string config_database_name;
            exchange_->getColumnValue(r, i, 0, config_database_name);
            shards.insert(config_database_name);
        }
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError,
                  "Cannot retrieve shard names from the master database, reason: " << ex.what());
    }

    return true;
}

}  // namespace dhcp
}  // namespace isc
