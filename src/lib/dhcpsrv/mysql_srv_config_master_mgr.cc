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

#include <dhcpsrv/mysql_srv_config_master_mgr.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/mysql_connection.h>

#include <errmsg.h>
#include <mysql.h>
#include <mysqld_error.h>

#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/static_assert.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <array>

namespace {

using namespace isc::dhcp;

constexpr size_t INSTANCE_ID_MAX_LEN = 128;
constexpr size_t SERVER_CONFIG_MAX_LEN = 65535;
constexpr size_t CONFIG_DATABASE_MAX_LEN = 65535;
constexpr size_t CONFIG_DATABASE_NAME_MAX_LEN = 128;

std::array<TaggedStatement, MySqlSrvConfigMasterMgr::NUM_STATEMENTS> tagged_statements = {{
    {MySqlSrvConfigMasterMgr::INSERT_SERVER_CONFIG4,
     "INSERT INTO server_configuration4"
     " (instance_id, timestamp, server_config, config_database, config_database_name)"
     " VALUES (?, ?, ?, ?, ?)"},

    {MySqlSrvConfigMasterMgr::INSERT_SERVER_CONFIG6,
     "INSERT INTO server_configuration6"
     " (instance_id, timestamp, server_config, config_database, config_database_name)"
     " VALUES (?, ?, ?, ?, ?)"},

    {MySqlSrvConfigMasterMgr::GET_CONFIGURATION4_BY_SRV_ID,
     "SELECT instance_id, timestamp, server_config, config_database, config_database_name"
     " FROM server_configuration4"
     " WHERE instance_id = ? "},

    {MySqlSrvConfigMasterMgr::GET_CONFIGURATION6_BY_SRV_ID,
     "SELECT instance_id, timestamp, server_config, config_database, config_database_name"
     " FROM server_configuration6"
     " WHERE instance_id = ? "},

    {MySqlSrvConfigMasterMgr::GET_CONFIGURATION4_BY_SHARD_DB,
     "SELECT instance_id, timestamp, server_config, config_database, config_database_name"
     " FROM server_configuration4"
     " WHERE config_database_name = ?"},

    {MySqlSrvConfigMasterMgr::GET_CONFIGURATION6_BY_SHARD_DB,
     "SELECT instance_id, timestamp, server_config, config_database, config_database_name"
     " FROM server_configuration6"
     " WHERE config_database_name = ?"},

    {MySqlSrvConfigMasterMgr::GET_CONFIGURATION4_TIMESTAMP, "SELECT instance_id, timestamp"
                                                            " FROM server_configuration4"
                                                            " WHERE instance_id = ? "},

    {MySqlSrvConfigMasterMgr::GET_CONFIGURATION6_TIMESTAMP, "SELECT instance_id, timestamp"
                                                            " FROM server_configuration6"
                                                            " WHERE instance_id = ? "},

    {MySqlSrvConfigMasterMgr::DELETE_SERVER_CONFIG4, "TRUNCATE server_configuration4 "},

    {MySqlSrvConfigMasterMgr::DELETE_SERVER_CONFIG6, "TRUNCATE server_configuration6 "},

    {MySqlSrvConfigMasterMgr::GET_SERVERS_CONFIG4_SHARDS_NAME, "SELECT config_database_name"
                                                               " FROM server_configuration4"},

    {MySqlSrvConfigMasterMgr::GET_SERVERS_CONFIG6_SHARDS_NAME, "SELECT config_database_name"
                                                               " FROM server_configuration6"},

    {MySqlSrvConfigMasterMgr::GET_VERSION, "SELECT version, minor"
                                           " FROM master_schema_version"},
}};

}  // namespace

namespace isc {
namespace dhcp {

/// @brief Exchange MySQL and SrvConfigMasterInfo data
///
/// On any MySQL operation, arrays of MYSQL_BIND structures must be built to
/// describe the parameters in the prepared statements.  Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical.  This class handles the creation of that array.
///
/// Owing to the MySQL API, the process requires some intermediate variables
/// to hold things like data length etc.  This object holds those variables.
///
/// @note There are no unit tests for this class.  It is tested indirectly
/// in all MySqlSrvConfigMasterMgr::xxx() calls where it is used.
class MySqlMasterConfigExchange {
    /// @brief Set number of database columns to send data for
    /// the server configuration structure
    static const size_t SERVER_CONFIG_SEND_COLUMNS = 5;

    /// @brief Set number of database columns to read data for
    /// the server configuration structure
    static const size_t SERVER_CONFIG_RECEIVE_COLUMNS = 5;

public:
    MySqlMasterConfigExchange() : config_master_(boost::make_shared<SrvConfigMasterInfo>()) {
        size_t i = 0;
        for (std::string const& column : {"instance_id", "timestamp", "server_config",
                                          "config_database", "config_database_name"}) {
            send_columns_[i] = column;
            receive_columns_[i] = column;
            BOOST_ASSERT(i < SERVER_CONFIG_SEND_COLUMNS);
            BOOST_ASSERT(i < SERVER_CONFIG_RECEIVE_COLUMNS);
            ++i;
        }

        std::fill(&error_receive[0], &error_receive[SERVER_CONFIG_RECEIVE_COLUMNS], MLM_FALSE);
        std::fill(&error_send[0], &error_send[SERVER_CONFIG_SEND_COLUMNS], MLM_FALSE);
    }

    virtual ~MySqlMasterConfigExchange() {
    }

    /// @brief Create MYSQL_BIND objects for SrvConfigMasterInfo Pointer
    ///
    /// Fills in the MYSQL_BIND array for sending data in the
    /// SrvConfigMasterInfo object to the database.
    ///
    /// @param instance_id the instance identifier of the server being added to the database
    /// @param server_config configuration of the server being added to the database
    /// @param config_database configuration to be used on the shard
    /// @param config_database_name name of the shard whose configuration is being added
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const std::string& instance_id,
                                              const std::string& server_config,
                                              const std::string& config_database,
                                              const std::string& config_database_name) {
        // Store configuration object to ensure it remains valid.
        config_master_->instance_id_ = instance_id;
        config_master_->timestamp_ = static_cast<int64_t>(time(NULL));
        config_master_->server_config_ = server_config;
        config_master_->config_database_ = config_database;
        config_master_->config_database_name_ = config_database_name;

        // Initialize prior to constructing the array of MYSQL_BIND structures.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_send, 0, sizeof(bind_send));

        // Set up the structures for the various components of the
        // server configuration structure.
        try {
            // instance_id: VARCHAR(128)
            bind_send[0].buffer_type = MYSQL_TYPE_STRING;
            bind_send[0].buffer = const_cast<char*>(config_master_->instance_id_.c_str());
            bind_send[0].buffer_length = config_master_->instance_id_.length();
            // bind_send[0].is_null = &MLM_FALSE; // commented out for performance
            // reasons, see memset() above

            // timestamp: TIMESTAMP
            MySqlConnection::convertToDatabaseTime(config_master_->timestamp_, timestamp_buffer_);
            bind_send[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
            bind_send[1].buffer = reinterpret_cast<char*>(&timestamp_buffer_);
            bind_send[1].buffer_length = sizeof(timestamp_buffer_);
            // bind_send[1].is_null = &MLM_FALSE; // commented out for performance
            // reasons, see memset() above

            // server_config: TEXT
            bind_send[2].buffer_type = MYSQL_TYPE_STRING;
            bind_send[2].buffer = const_cast<char*>(config_master_->server_config_.c_str());
            bind_send[2].buffer_length = config_master_->server_config_.length();
            // bind_send[2].is_null = &MLM_FALSE; // commented out for performance
            // reasons, see memset() above

            // config_database: TEXT
            bind_send[3].buffer_type = MYSQL_TYPE_STRING;
            bind_send[3].buffer = const_cast<char*>(config_master_->config_database_.c_str());
            bind_send[3].buffer_length = config_master_->config_database_.length();
            // bind_send[3].is_null = &MLM_FALSE; // commented out for performance
            // reasons, see memset() above

            // config_database_name: VARCHAR(128)
            bind_send[4].buffer_type = MYSQL_TYPE_STRING;
            bind_send[4].buffer = const_cast<char*>(config_master_->config_database_name_.c_str());
            bind_send[4].buffer_length = config_master_->config_database_name_.length();
            // bind_send[4].is_null = &MLM_FALSE; // commented out for performance
            // reasons, see memset() above

            // Add the error flags
            setErrorIndicators(bind_send, error_send, SERVER_CONFIG_SEND_COLUMNS);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Could not create bind array from master configuration."
                                            << "Reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_send[0], &bind_send[SERVER_CONFIG_SEND_COLUMNS]));
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a MYSQL_BIND array to receive SrvConfigMasterInfo data
    /// from the database.
    /// After data is successfully received, getServerConfigurationData()
    /// can be used to copy it to a Lease6 object.
    ///
    std::vector<MYSQL_BIND> createBindForReceive() {
        // Initialize MYSQL_BIND array.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_receive, 0, sizeof(bind_receive));

        // instance_id: VARCHAR(128)
        instance_id_length_ = sizeof(instance_id_buffer_);
        bind_receive[0].buffer_type = MYSQL_TYPE_STRING;
        bind_receive[0].buffer = reinterpret_cast<char*>(instance_id_buffer_);
        bind_receive[0].buffer_length = instance_id_length_;
        bind_receive[0].length = &instance_id_length_;
        // bind_receive[0].is_null = &MLM_FALSE; // commented out for performance
        // reasons, see memset() above

        // expire: timestamp
        bind_receive[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind_receive[1].buffer = reinterpret_cast<char*>(&timestamp_);
        bind_receive[1].buffer_length = sizeof(timestamp_);
        // bind_receive[1].is_null = &MLM_FALSE; // commented out for performance
        // reasons, see memset() above

        // server_config: TEXT
        server_config_length_ = sizeof(server_config_buffer_);
        bind_receive[2].buffer_type = MYSQL_TYPE_STRING;
        bind_receive[2].buffer = reinterpret_cast<char*>(server_config_buffer_);
        bind_receive[2].buffer_length = server_config_length_;
        bind_receive[2].length = &server_config_length_;
        // bind_receive[2].is_null = &MLM_FALSE; // commented out for performance
        // reasons, see memset() above

        // config_database: TEXT
        config_database_length_ = sizeof(config_database_buffer_);
        bind_receive[3].buffer_type = MYSQL_TYPE_STRING;
        bind_receive[3].buffer = reinterpret_cast<char*>(config_database_buffer_);
        bind_receive[3].buffer_length = config_database_length_;
        bind_receive[3].length = &config_database_length_;
        // bind_receive[3].is_null = &MLM_FALSE; // commented out for performance
        // reasons, see memset() above

        // config_database_name: VARCHAR(128)
        config_database_name_length_ = sizeof(config_database_name_buffer_);
        bind_receive[4].buffer_type = MYSQL_TYPE_STRING;
        bind_receive[4].buffer = reinterpret_cast<char*>(config_database_name_buffer_);
        bind_receive[4].buffer_length = config_database_name_length_;
        bind_receive[4].length = &config_database_name_length_;
        // bind_receive[4].is_null = &MLM_FALSE; // commented out for performance
        // reasons, see memset() above

        // Add the error flags
        setErrorIndicators(bind_receive, error_receive, SERVER_CONFIG_RECEIVE_COLUMNS);

        // .. and check that we have the numbers correct at compile time.
        BOOST_STATIC_ASSERT(4 < SERVER_CONFIG_RECEIVE_COLUMNS);

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_receive[0],
                                        &bind_receive[SERVER_CONFIG_RECEIVE_COLUMNS]));
    }

    /// @brief Copy Received Data into SrvConfigMasterInfo Object
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive()
    /// has been used, this copies data from the internal member variables
    /// into a SrvConfigMasterInfo object.
    ///
    /// @return SrvConfigMasterInfoPtr Pointer to a SrvConfigMasterInfo
    ///         object holding the relevant data.
    SrvConfigMasterInfoPtr getServerConfigData() {
        SrvConfigMasterInfoPtr config_ptr = boost::make_shared<SrvConfigMasterInfo>();
        config_ptr->instance_id_ = std::string(instance_id_buffer_, instance_id_length_);
        config_ptr->timestamp_ = timestamp_;
        config_ptr->server_config_ = std::string(server_config_buffer_, server_config_length_);
        config_ptr->config_database_ =
            std::string(config_database_buffer_, config_database_length_);
        config_ptr->config_database_name_ =
            std::string(config_database_name_buffer_, config_database_name_length_);

        return (config_ptr);
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @return Comma-separated list of columns in error, or the string
    ///         "(None)".
    std::string getErrorSendColumns() {
        return (getColumnsInError(error_send, send_columns_, SERVER_CONFIG_SEND_COLUMNS));
    }

    std::string getErrorReceiveColumns() {
        return (getColumnsInError(error_receive, receive_columns_, SERVER_CONFIG_RECEIVE_COLUMNS));
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @param error Array of error elements.  An element is set to MLM_TRUE
    ///        if the corresponding column in the database is the source of
    ///        the error.
    /// @param names Array of column names, the same size as the error array.
    /// @param count Size of each of the arrays.
    static std::string getColumnsInError(my_bool* error, std::string* names, size_t count) {
        std::string result = "";

        // Accumulate list of column names
        for (size_t i = 0; i < count; ++i) {
            if (error[i] == MLM_TRUE) {
                if (!result.empty()) {
                    result += ", ";
                }
                result += names[i];
            }
        }

        if (result.empty()) {
            result = "(None)";
        }

        return (result);
    }

protected:
    /// @brief Set error indicators
    ///
    /// Sets the error indicator for each of the MYSQL_BIND elements.  It points
    /// the "error" field within an element of the input array to the
    /// corresponding element of the passed error array.
    ///
    /// @param bind Array of BIND elements
    /// @param error Array of error elements.  If there is an error in getting
    ///        data associated with one of the "bind" elements, the
    ///        corresponding element in the error array is set to MLM_TRUE.
    /// @param count Size of each of the arrays.
    static void setErrorIndicators(MYSQL_BIND* bind, my_bool* error, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            error[i] = MLM_FALSE;
            bind[i].error = reinterpret_cast<char*>(&error[i]);
        }
    }

private:
    // Bind arays
    MYSQL_BIND bind_send[SERVER_CONFIG_SEND_COLUMNS];
    MYSQL_BIND bind_receive[SERVER_CONFIG_RECEIVE_COLUMNS];

    // Send column names
    std::string send_columns_[SERVER_CONFIG_SEND_COLUMNS];
    // Receive column names
    std::string receive_columns_[SERVER_CONFIG_RECEIVE_COLUMNS];

    // Error indicators
    my_bool error_send[SERVER_CONFIG_SEND_COLUMNS];
    my_bool error_receive[SERVER_CONFIG_RECEIVE_COLUMNS];

    // Pointer to the master configuration object
    SrvConfigMasterInfoPtr config_master_;

    // Instance identifier buffer and length
    char instance_id_buffer_[INSTANCE_ID_MAX_LEN];
    unsigned long instance_id_length_;  ///< Instance identifier length

    // Timestamp buffer and length
    MYSQL_TIME timestamp_buffer_;
    int64_t timestamp_;

    // Server configuration buffer and length
    char server_config_buffer_[SERVER_CONFIG_MAX_LEN];
    unsigned long server_config_length_;

    // Configuration buffer and length
    char config_database_buffer_[CONFIG_DATABASE_MAX_LEN];
    unsigned long config_database_length_;

    // Database name buffer and length
    char config_database_name_buffer_[CONFIG_DATABASE_NAME_MAX_LEN];
    unsigned long config_database_name_length_;
};

MySqlSrvConfigMasterMgr::MySqlSrvConfigMasterMgr(const MySqlConnection::ParameterMap& parameters)
    : conn_(parameters), exchange_(new MySqlMasterConfigExchange()) {

    // Open the database.
    conn_.openDatabase();

    // Enable autocommit.  To avoid a flush to disk on every commit, the global
    // parameter innodb_flush_log_at_trx_commit should be set to 2.  This will
    // cause the changes to be written to the log, but flushed to disk in the
    // background every second.  Setting the parameter to that value will speed
    // up the system, but at the risk of losing data if the system crashes.
    my_bool result = mysql_autocommit(conn_.mysql_, 1);
    if (result != 0) {
        isc_throw(DbOperationError, mysql_error(conn_.mysql_));
    }

    // Prepare all statements likely to be used.
    conn_.prepareStatements(tagged_statements.begin(), tagged_statements.end());
}

MySqlSrvConfigMasterMgr::~MySqlSrvConfigMasterMgr() {
    // There is no need to close the database in this destructor: it is
    // closed in the destructor of the mysql_ member variable.
}

std::string MySqlSrvConfigMasterMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "MySQL backend " << MYSQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << MYSQL_SCHEMA_VERSION_MINOR;
    tmp << ", library " << mysql_get_client_info();
    return (tmp.str());
}

VersionPair MySqlSrvConfigMasterMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_VERSION);

    const StatementIndex stindex = GET_VERSION;

    uint32_t major;  // Major version number
    uint32_t minor;  // Minor version number

    // Execute the prepared statement
    int status = mysql_stmt_execute(conn_.statements_[stindex]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to execute <"
                                        << conn_.text_statements_[stindex]
                                        << "> - reason: " << mysql_error(conn_.mysql_));
    }

    // Bind the output of the statement to the appropriate variables.
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].is_unsigned = 1;
    bind[0].buffer = &major;
    bind[0].buffer_length = sizeof(major);

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].is_unsigned = 1;
    bind[1].buffer = &minor;
    bind[1].buffer_length = sizeof(minor);

    status = mysql_stmt_bind_result(conn_.statements_[stindex], bind);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to bind result set: " << mysql_error(conn_.mysql_));
    }

    // Fetch the data and set up the "release" object to release associated
    // resources when this method exits then retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[stindex]);
    status = mysql_stmt_fetch(conn_.statements_[stindex]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to obtain result set: " << mysql_error(conn_.mysql_));
    }

    return (std::make_pair(major, minor));
}

bool MySqlSrvConfigMasterMgr::addServerConfig4(const std::string& instance_id,
                                               const std::string& server_config,
                                               const std::string& config_database,
                                               const std::string& config_database_name) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_INSERT_SRV_MASTER_CONFIG4)
        .arg(instance_id)
        .arg(config_database_name);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::INSERT_SERVER_CONFIG4;
    return addCommonServerConfiguration(statement_index, instance_id, server_config,
                                        config_database, config_database_name);
}

bool MySqlSrvConfigMasterMgr::addServerConfig6(const std::string& instance_id,
                                               const std::string& server_config,
                                               const std::string& config_database,
                                               const std::string& config_database_name) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_INSERT_SRV_MASTER_CONFIG6)
        .arg(instance_id)
        .arg(config_database_name);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::INSERT_SERVER_CONFIG6;
    return addCommonServerConfiguration(statement_index, instance_id, server_config,
                                        config_database, config_database_name);
}

bool MySqlSrvConfigMasterMgr::clearServersConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_CLEAR_SRV_MASTER_CONFIG4);

    const StatementIndex stindex = DELETE_SERVER_CONFIG4;

    // Execute the prepared statement
    int status = mysql_stmt_execute(conn_.statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    return true;
}

bool MySqlSrvConfigMasterMgr::clearServersConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_CLEAR_SRV_MASTER_CONFIG6);

    const StatementIndex stindex = DELETE_SERVER_CONFIG6;

    // Execute the prepared statement
    int status = mysql_stmt_execute(conn_.statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    return true;
}

SrvConfigMasterInfoPtr MySqlSrvConfigMasterMgr::getConfig4(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SRV_MASTER_CONFIG4)
        .arg(instance_id);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::GET_CONFIGURATION4_BY_SRV_ID;
    return getCommonServerConfigurationByInstanceId(statement_index, instance_id);
}

SrvConfigMasterInfoPtr MySqlSrvConfigMasterMgr::getConfig6(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SRV_MASTER_CONFIG6)
        .arg(instance_id);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::GET_CONFIGURATION6_BY_SRV_ID;
    return getCommonServerConfigurationByInstanceId(statement_index, instance_id);
}

bool MySqlSrvConfigMasterMgr::getConfig4(
    const std::string& config_database_name,
    std::vector<SrvConfigMasterInfoPtr>& server_configurations) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_SRV_MASTER_CONFIG4_SHARD_DB)
        .arg(config_database_name);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::GET_CONFIGURATION4_BY_SHARD_DB;
    return getCommonServerConfigurationByShardName(statement_index, config_database_name,
                                                   server_configurations);
}

bool MySqlSrvConfigMasterMgr::getConfig6(
    const std::string& config_database_name,
    std::vector<SrvConfigMasterInfoPtr>& server_configurations) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_SRV_MASTER_CONFIG6_SHARD_DB)
        .arg(config_database_name);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::GET_CONFIGURATION6_BY_SHARD_DB;
    return getCommonServerConfigurationByShardName(statement_index, config_database_name,
                                                   server_configurations);
}

SrvConfigMasterInfoPtr
MySqlSrvConfigMasterMgr::getMasterConfig4Timestamp(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_SRV_MASTER_CONFIG4_TIMESTAMP)
        .arg(instance_id);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::GET_CONFIGURATION4_TIMESTAMP;
    return getCommonTimestampFromMasterServerConfiguration(statement_index, instance_id);
}

SrvConfigMasterInfoPtr
MySqlSrvConfigMasterMgr::getMasterConfig6Timestamp(const std::string& instance_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_SRV_MASTER_CONFIG6_TIMESTAMP)
        .arg(instance_id);
    ;

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::GET_CONFIGURATION6_TIMESTAMP;
    return getCommonTimestampFromMasterServerConfiguration(statement_index, instance_id);
}

bool MySqlSrvConfigMasterMgr::getServersConfig4ShardsName(
    std::set<std::string>& shards_list) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_SRV_MASTER_CONFIG4_SHARDS_NAME);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::GET_SERVERS_CONFIG4_SHARDS_NAME;
    return getCommonShardNamesFromMasterServerConfiguration(statement_index, shards_list);
}

bool MySqlSrvConfigMasterMgr::getServersConfig6ShardsName(
    std::set<std::string>& shards_list) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_SRV_MASTER_CONFIG6_SHARDS_NAME);

    const StatementIndex statement_index = MySqlSrvConfigMasterMgr::GET_SERVERS_CONFIG6_SHARDS_NAME;
    return getCommonShardNamesFromMasterServerConfiguration(statement_index, shards_list);
}

bool MySqlSrvConfigMasterMgr::startTransaction() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_BEGIN_TRANSACTION);
    if (mysql_query(conn_.mysql_, "START TRANSACTION")) {
        isc_throw(DbOperationError, "start transaction failed: " << mysql_error(conn_.mysql_));
    }

    return true;
}

void MySqlSrvConfigMasterMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_COMMIT);
    if (mysql_commit(conn_.mysql_) != 0) {
        isc_throw(DbOperationError, "commit failed: " << mysql_error(conn_.mysql_));
    }
}

void MySqlSrvConfigMasterMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ROLLBACK);
    if (mysql_rollback(conn_.mysql_) != 0) {
        isc_throw(DbOperationError, "rollback failed: " << mysql_error(conn_.mysql_));
    }
}

void MySqlSrvConfigMasterMgr::checkError(int status,
                                         StatementIndex statement_index,
                                         const char* what) const {
    conn_.checkError(status, statement_index, what);
}

bool MySqlSrvConfigMasterMgr::addCommonServerConfiguration(
    const StatementIndex statement_index,
    const std::string& instance_id,
    const std::string& server_config,
    const std::string& config_database,
    const std::string& config_database_name) const {

    std::vector<MYSQL_BIND> bind = exchange_->createBindForSend(
        instance_id, server_config, config_database, config_database_name);
    try {
        int status = mysql_stmt_bind_param(conn_.statements_[statement_index], &bind[0]);
        checkError(status, statement_index, "unable to bind parameters");

        // Execute the statement
        status = mysql_stmt_execute(conn_.statements_[statement_index]);
        if (status != 0) {
            // Failure: check for the special case of duplicate entry.  If this is
            // the case, we return false to indicate that the row was not added.
            // Otherwise we throw an exception.
            if (mysql_errno(conn_.mysql_) == ER_DUP_ENTRY) {
                return (false);
            }
            checkError(status, statement_index, "unable to execute");
        }
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Could not create bind array to insert configuration "
                                        << ", reason: " << ex.what());
    }

    // Insert succeeded
    return true;
}

SrvConfigMasterInfoPtr MySqlSrvConfigMasterMgr::getCommonServerConfigurationByInstanceId(
    const StatementIndex statement_index, const std::string& instance_id) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(instance_id.c_str());
    inbind[0].buffer_length = instance_id.length();
    inbind[0].is_null = 0;

    SrvConfigMasterInfoPtr result;

    // Bind the selection parameters to the statement
    int status = mysql_stmt_bind_param(conn_.statements_[statement_index], inbind);
    checkError(status, statement_index, "unable to bind WHERE clause parameter");

    // Set up the MYSQL_BIND array for the data being returned and bind it to
    // the statement.
    std::vector<MYSQL_BIND> outbind = exchange_->createBindForReceive();
    status = mysql_stmt_bind_result(conn_.statements_[statement_index], &outbind[0]);
    checkError(status, statement_index, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = mysql_stmt_execute(conn_.statements_[statement_index]);
    checkError(status, statement_index, "unable to execute");

    // Ensure that all the lease information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(conn_.statements_[statement_index]);
    checkError(status, statement_index, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[statement_index]);
    int count = 0;
    while ((status = mysql_stmt_fetch(conn_.statements_[statement_index])) == 0) {
        try {
            result = exchange_->getServerConfigData();
        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <"
                                          << conn_.text_statements_[statement_index] << ">");
        }

        if (++count > 1) {
            isc_throw(MultipleRecords, "multiple records were found in the "
                                       "database where only one was expected for query "
                                           << conn_.text_statements_[statement_index]);
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fetch results
        checkError(status, statement_index, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault
        isc_throw(DataTruncated, conn_.text_statements_[statement_index]
                                     << " returned truncated data: columns affected are "
                                     << exchange_->getErrorReceiveColumns());
    }

    return result;
}

bool MySqlSrvConfigMasterMgr::getCommonServerConfigurationByShardName(
    const StatementIndex statement_index,
    const std::string& config_database_name,
    std::vector<SrvConfigMasterInfoPtr>& server_configurations) const {

    server_configurations.clear();

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(config_database_name.c_str());
    inbind[0].buffer_length = config_database_name.length();
    inbind[0].is_null = 0;

    // Bind the selection parameters to the statement
    int status = mysql_stmt_bind_param(conn_.statements_[statement_index], inbind);
    checkError(status, statement_index, "unable to bind WHERE clause parameter");

    // Set up the MYSQL_BIND array for the data being returned and bind it to
    // the statement.
    std::vector<MYSQL_BIND> outbind = exchange_->createBindForReceive();
    status = mysql_stmt_bind_result(conn_.statements_[statement_index], &outbind[0]);
    checkError(status, statement_index, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = mysql_stmt_execute(conn_.statements_[statement_index]);
    checkError(status, statement_index, "unable to execute");

    // Ensure that all the lease information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(conn_.statements_[statement_index]);
    checkError(status, statement_index, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[statement_index]);

    while ((status = mysql_stmt_fetch(conn_.statements_[statement_index])) == 0) {
        try {
            server_configurations.push_back(exchange_->getServerConfigData());
        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <"
                                          << conn_.text_statements_[statement_index] << ">");
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fetch results
        checkError(status, statement_index, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault
        isc_throw(DataTruncated, conn_.text_statements_[statement_index]
                                     << " returned truncated data: columns affected are "
                                     << exchange_->getErrorReceiveColumns());
    }

    return true;
}

SrvConfigMasterInfoPtr MySqlSrvConfigMasterMgr::getCommonTimestampFromMasterServerConfiguration(
    const StatementIndex statement_index, const std::string& instance_id) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(instance_id.c_str());
    inbind[0].buffer_length = instance_id.length();
    inbind[0].is_null = 0;

    // Bind the selection parameters to the statement
    int status = mysql_stmt_bind_param(conn_.statements_[statement_index], inbind);
    checkError(status, statement_index, "unable to bind WHERE clause parameter");

    MYSQL_BIND outbind[2];
    memset(outbind, 0, sizeof(outbind));

    char instance_id_buffer[INSTANCE_ID_MAX_LEN];
    unsigned long instance_id_length = sizeof(instance_id_buffer);

    // Server Id: VARCHAR(128)
    outbind[0].buffer_type = MYSQL_TYPE_STRING;
    outbind[0].buffer = reinterpret_cast<char*>(instance_id_buffer);
    outbind[0].buffer_length = instance_id_length;
    outbind[0].length = &instance_id_length;
    // outbind[0].is_null = &MLM_FALSE; // commented out for performance
    // reasons, see memset() above

    // Timestamp
    int64_t timestamp = 0;
    outbind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    outbind[1].buffer = reinterpret_cast<char*>(&timestamp);
    outbind[1].is_unsigned = MLM_TRUE;
    outbind[1].buffer_length = instance_id_length;
    // outbind[1].is_null = &MLM_FALSE; // commented out for performance
    // reasons, see memset() above

    status = mysql_stmt_bind_result(conn_.statements_[statement_index], &outbind[0]);
    checkError(status, statement_index, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = mysql_stmt_execute(conn_.statements_[statement_index]);
    checkError(status, statement_index, "unable to execute");

    // Ensure that all the information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(conn_.statements_[statement_index]);
    checkError(status, statement_index, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[statement_index]);

    int count = 0;
    SrvConfigMasterInfoPtr result;
    while ((status = mysql_stmt_fetch(conn_.statements_[statement_index])) == 0) {
        try {
            std::string instance_id(instance_id_buffer, instance_id_length);
            result.reset(new SrvConfigMasterInfo());
            result->instance_id_ = instance_id;
            result->timestamp_ = timestamp;

            if (++count > 1) {
                isc_throw(MultipleRecords, "multiple records were found in the "
                                           "database where only one was expected for query "
                                               << conn_.text_statements_[statement_index]);
            }
        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <"
                                          << conn_.text_statements_[statement_index] << ">");
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fetch results
        checkError(status, statement_index, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault
        isc_throw(DataTruncated,
                  conn_.text_statements_[statement_index] << " returned truncated data.");
    }

    return result;
}

bool MySqlSrvConfigMasterMgr::getCommonShardNamesFromMasterServerConfiguration(
    const StatementIndex statement_index, std::set<std::string>& shards) const {
    shards.clear();

    MYSQL_BIND outbind[1];
    memset(outbind, 0, sizeof(outbind));

    char config_database_name_buffer[CONFIG_DATABASE_NAME_MAX_LEN];
    unsigned long config_database_name_length;

    // config_database_name: VARCHAR(128)
    config_database_name_length = sizeof(config_database_name_buffer);
    outbind[0].buffer_type = MYSQL_TYPE_STRING;
    outbind[0].buffer = reinterpret_cast<char*>(config_database_name_buffer);
    outbind[0].buffer_length = config_database_name_length;
    outbind[0].length = &config_database_name_length;
    // outbind[0].is_null = &MLM_FALSE; // commented out for performance
    // reasons, see memset() above

    int status = mysql_stmt_bind_result(conn_.statements_[statement_index], &outbind[0]);
    checkError(status, statement_index, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = mysql_stmt_execute(conn_.statements_[statement_index]);
    checkError(status, statement_index, "unable to execute");

    // Ensure that all the information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(conn_.statements_[statement_index]);
    checkError(status, statement_index, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[statement_index]);

    while ((status = mysql_stmt_fetch(conn_.statements_[statement_index])) == 0) {
        try {
            std::string config_database(config_database_name_buffer, config_database_name_length);
            shards.insert(config_database);
        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <"
                                          << conn_.text_statements_[statement_index] << ">");
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fetch results
        checkError(status, statement_index, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault

        isc_throw(DataTruncated,
                  conn_.text_statements_[statement_index] << " returned truncated data.");
    }

    return true;
}

}  // namespace dhcp
}  // namespace isc
