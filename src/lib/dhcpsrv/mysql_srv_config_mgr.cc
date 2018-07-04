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

#include <dhcpsrv/mysql_srv_config_mgr.h>

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
#include <string>
#include <utility>
#include <vector>

using namespace isc;
using namespace isc::dhcp;

const size_t CONFIG_DATA_SIZE = 1073741824u;

namespace {

std::array<TaggedStatement, MySqlSrvConfigMgr::NUM_STATEMENTS> tagged_statements = {{
    {MySqlSrvConfigMgr::GET_VERSION,  //
     "SELECT version, minor"
     " FROM config_schema_version"},

    {MySqlSrvConfigMgr::GET_CONFIGURATION4_TIMESTAMP,  //
     "SELECT config_id, timestamp"
     " FROM server_configuration4 LIMIT 1"},

    {MySqlSrvConfigMgr::GET_CONFIGURATION6_TIMESTAMP,  //
     "SELECT config_id, timestamp"
     " FROM server_configuration6 LIMIT 1"},

    {MySqlSrvConfigMgr::GET_JSON_CONFIGURATION4,  //
     "SELECT config_id, timestamp, json_data"
     " FROM server_configuration4 LIMIT 1"},

    {MySqlSrvConfigMgr::GET_JSON_CONFIGURATION6,  //
     "SELECT config_id, timestamp, json_data"
     " FROM server_configuration6 LIMIT 1"},

    {MySqlSrvConfigMgr::GET_GENERIC_CONFIGURATION4,  //
     "SELECT config_id, timestamp, generic_data"
     " FROM server_configuration4 LIMIT 1"},

    {MySqlSrvConfigMgr::GET_GENERIC_CONFIGURATION6,  //
     "SELECT config_id, timestamp, generic_data"
     " FROM server_configuration6 LIMIT 1"},

    {MySqlSrvConfigMgr::INSERT_CONFIGURATION4,  //
     "INSERT INTO server_configuration4"
     " (config_id, timestamp, json_data, generic_data)"
     " VALUES (?, ?, ?, ?)"},

    {MySqlSrvConfigMgr::INSERT_CONFIGURATION6,  //
     "INSERT INTO server_configuration6"
     " (config_id, timestamp, json_data, generic_data)"
     " VALUES (?, ?, ?, ?)"},

    {MySqlSrvConfigMgr::UPDATE_CONFIGURATION4,  //
     "UPDATE server_configuration4"
     " SET timestamp=?, json_data=?, generic_data=?"
     " WHERE config_id=?"},

    {MySqlSrvConfigMgr::UPDATE_CONFIGURATION6,  //
     "UPDATE server_configuration6"
     " SET timestamp=?, json_data=?, generic_data=?"
     " WHERE config_id=?"}  //
}};

}  // namespace

namespace isc {
namespace dhcp {

MySqlSrvConfigMgr::MySqlSrvConfigMgr(const MySqlConnection::ParameterMap& parameters)
    : conn_(parameters) {

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

MySqlSrvConfigMgr::~MySqlSrvConfigMgr() {
    // There is no need to close the database in this destructor: it is
    // closed in the destructor of the mysql_ member variable.
}

std::string MySqlSrvConfigMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "MySQL backend " << MYSQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << MYSQL_SCHEMA_VERSION_MINOR;
    tmp << ", library " << mysql_get_client_info();
    return (tmp.str());
}

VersionPair MySqlSrvConfigMgr::getVersion() const {
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

bool MySqlSrvConfigMgr::updateConfig4(int64_t config_timestamp,
                                      const std::string& json_data,
                                      const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_REQUEST_UPDATE_SRV_CONFIG4);

    // Initiate MYSQL transaction as we will have to update the config
    // from two steps and we don't want anybody else to write another
    // config between these two steps:
    // Step 1: Read the current configuration timestamp from database.
    // Step 2: Check if the provided configuration timestamp is
    // the same with the existing one from database.
    // Step 3: Update the configuration on the server.
    // If there is no configuration on the server then insert a new one but
    // also using transactions because we don't want another user to insert also
    // a new configuration in the same time.

    // MySqlTransaction rolls back the transaction on its destructor.

    // begin the transaction
    MySqlTransaction transaction(conn_);

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

        LOG_WARN(dhcpsrv_logger, DHCPSRV_MYSQL_UPDATE_SRV_CONFIG4_TIMESTAMP_CHANGED)
            .arg(config_timestamp)
            .arg(current_config->timestamp_);

        return false;
    }

    transaction.commit();
    return true;
}

bool MySqlSrvConfigMgr::updateConfig6(int64_t config_timestamp,
                                      const std::string& json_data,
                                      const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_REQUEST_UPDATE_SRV_CONFIG6);

    // Initiate MYSQL transaction as we will have to update the config
    // from two steps and we don't want anybody else to write another
    // config between these two steps:
    // Step 1: Read the current configuration timestamp from database.
    // Step 2: Check if the provided configuration timestamp is
    // the same with the existing one from database.
    // Step 3: Update the configuration on the server.
    // If there is no configuration on the server then insert a new one but
    // also using transactions because we don't want another user to insert also
    // a new configuration in the same time.

    // MySqlTransaction rolls back the transaction on its destructor.

    // begin the transaction
    MySqlTransaction transaction(conn_);

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

        LOG_WARN(dhcpsrv_logger, DHCPSRV_MYSQL_UPDATE_SRV_CONFIG6_TIMESTAMP_CHANGED)
            .arg(config_timestamp)
            .arg(current_config->timestamp_);

        return false;
    }

    transaction.commit();
    return true;
}

SrvConfigInfoPtr MySqlSrvConfigMgr::getConfig4Timestamp() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SRV_CONFIG4_TIMESTAMP);

    const StatementIndex stindex = MySqlSrvConfigMgr::GET_CONFIGURATION4_TIMESTAMP;
    return getConfigTimestampCommon(stindex);
}

SrvConfigInfoPtr MySqlSrvConfigMgr::getConfig6Timestamp() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SRV_CONFIG6_TIMESTAMP);

    const StatementIndex stindex = MySqlSrvConfigMgr::GET_CONFIGURATION6_TIMESTAMP;
    return getConfigTimestampCommon(stindex);
}

SrvConfigInfoPtr MySqlSrvConfigMgr::getConfigTimestampCommon(StatementIndex stindex) const {
    char config_id[37];  // SQL type CHAR(36) + NULL character
    MYSQL_TIME db_timestamp;

    // Execute the statement
    int status = mysql_stmt_execute(conn_.statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    // Bind the output of the statement to the appropriate variables.
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    unsigned long config_id_length = sizeof(config_id);
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = &config_id[0];
    bind[0].buffer_length = config_id_length;
    bind[0].length = &config_id_length;

    bind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    bind[1].buffer = reinterpret_cast<char*>(&db_timestamp);
    bind[1].buffer_length = sizeof(db_timestamp);

    // overhead of going back and forth between client and server.
    // status = mysql_stmt_store_result(conn_.statements_[stindex]);
    status = mysql_stmt_bind_result(conn_.statements_[stindex], bind);
    checkError(status, stindex, "unable to set up for storing all results");

    // Fetch the data and set up the "release" object to release associated
    // resources when this method exits then retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[stindex]);
    status = mysql_stmt_fetch(conn_.statements_[stindex]);
    if (status == MYSQL_NO_DATA) {
        return SrvConfigInfoPtr();
    }
    checkError(status, stindex, "unable to obtain result set");

    time_t timestamp;
    MySqlConnection::convertFromDatabaseTime(db_timestamp, 0, timestamp);

    SrvConfigInfoPtr srvConf = boost::make_shared<SrvConfigInfo>();
    srvConf->config_id_ = std::string(&config_id[0], config_id_length);
    srvConf->timestamp_ = timestamp;

    return srvConf;
}

SrvConfigInfoPtr MySqlSrvConfigMgr::getJsonConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SRV_CONFIG4_JSON);
    const StatementIndex stindex = MySqlSrvConfigMgr::GET_JSON_CONFIGURATION4;
    SrvConfigInfoPtr result = getConfigCommon(stindex);
    result->json_data_ = result->generic_data_;
    result->generic_data_ = "";
    return result;
}

SrvConfigInfoPtr MySqlSrvConfigMgr::getJsonConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SRV_CONFIG6_JSON);
    const StatementIndex stindex = MySqlSrvConfigMgr::GET_JSON_CONFIGURATION6;
    SrvConfigInfoPtr result = getConfigCommon(stindex);
    result->json_data_ = result->generic_data_;
    result->generic_data_ = "";
    return result;
}

SrvConfigInfoPtr MySqlSrvConfigMgr::getGenericConfig4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SRV_CONFIG4_GENERIC);

    const StatementIndex stindex = MySqlSrvConfigMgr::GET_GENERIC_CONFIGURATION4;
    return getConfigCommon(stindex);
}

SrvConfigInfoPtr MySqlSrvConfigMgr::getGenericConfig6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SRV_CONFIG6_GENERIC);

    const StatementIndex stindex = MySqlSrvConfigMgr::GET_GENERIC_CONFIGURATION6;
    return getConfigCommon(stindex);
}

SrvConfigInfoPtr MySqlSrvConfigMgr::getConfigCommon(StatementIndex stindex) const {
    char config_id[37];  // SQL type CHAR(36) + NULL character
    MYSQL_TIME db_timestamp;
    // The configuration data is too big to keep it on the thread's stack
    std::vector<char> config_data(
        CONFIG_DATA_SIZE);  // SQL type: LONGTEXT(4 GiB) + NULL character
                            // We limit this data to 60 MB + NULL character

    // Execute the statement
    int status = mysql_stmt_execute(conn_.statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    // Bind the output of the statement to the appropriate variables.
    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));

    unsigned long config_id_length = sizeof(config_id);
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = &config_id[0];
    bind[0].buffer_length = config_id_length;
    bind[0].length = &config_id_length;

    bind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    bind[1].buffer = reinterpret_cast<char*>(&db_timestamp);
    bind[1].buffer_length = sizeof(db_timestamp);

    unsigned long config_data_length = config_data.size();
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = &config_data[0];
    bind[2].buffer_length = config_data_length;
    bind[2].length = &config_data_length;

    // overhead of going back and forth between client and server.
    // status = mysql_stmt_store_result(conn_.statements_[stindex]);
    status = mysql_stmt_bind_result(conn_.statements_[stindex], bind);
    checkError(status, stindex, "unable to set up for storing all results");

    // Fetch the data and set up the "release" object to release associated
    // resources when this method exits then retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[stindex]);
    status = mysql_stmt_fetch(conn_.statements_[stindex]);
    if (status == MYSQL_NO_DATA) {
        return SrvConfigInfoPtr();
    }
    checkError(status, stindex, "unable to obtain result set");

    time_t timestamp;
    MySqlConnection::convertFromDatabaseTime(db_timestamp, 0, timestamp);

    SrvConfigInfoPtr srvConf(boost::make_shared<SrvConfigInfo>());
    srvConf->config_id_ = std::string(&config_id[0], config_id_length);
    srvConf->timestamp_ = timestamp;
    srvConf->generic_data_ = std::string(&config_data[0], config_data_length);

    return srvConf;
}

bool MySqlSrvConfigMgr::insertConfig4(const std::string& json_data,
                                      const std::string& generic_data) const {
    boost::uuids::random_generator gen;
    boost::uuids::uuid unique_id = gen();
    std::string config_id = boost::lexical_cast<std::string>(unique_id);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_INSERT_SRV_CONFIG4)
        .arg(config_id);

    const StatementIndex stindex = MySqlSrvConfigMgr::INSERT_CONFIGURATION4;
    return insertConfigCommon(stindex, config_id, json_data, generic_data);
}

bool MySqlSrvConfigMgr::insertConfig6(const std::string& json_data,
                                      const std::string& generic_data) const {
    boost::uuids::random_generator gen;
    boost::uuids::uuid unique_id = gen();
    std::string config_id = boost::lexical_cast<std::string>(unique_id);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_INSERT_SRV_CONFIG6)
        .arg(config_id);

    const StatementIndex stindex = MySqlSrvConfigMgr::INSERT_CONFIGURATION6;
    return insertConfigCommon(stindex, config_id, json_data, generic_data);
}

bool MySqlSrvConfigMgr::insertConfigCommon(StatementIndex stindex,
                                           const std::string& config_id,
                                           const std::string& json_data,
                                           const std::string& generic_data) const {
    try {
        MYSQL_BIND bind[4];  // Bind array
        memset(bind, 0, sizeof(bind));

        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = const_cast<char*>(config_id.c_str());
        bind[0].buffer_length = config_id.length();
        bind[0].is_null = 0;

        MYSQL_TIME expire_time;
        conn_.convertToDatabaseTime(time(NULL), expire_time);
        bind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind[1].buffer = reinterpret_cast<char*>(&expire_time);
        bind[1].buffer_length = sizeof(expire_time);
        bind[1].is_null = 0;

        bind[2].buffer_type = MYSQL_TYPE_STRING;
        bind[2].buffer = const_cast<char*>(json_data.c_str());
        bind[2].buffer_length = json_data.length();
        bind[2].is_null = 0;

        bind[3].buffer_type = MYSQL_TYPE_STRING;
        bind[3].buffer = const_cast<char*>(generic_data.c_str());
        bind[3].buffer_length = generic_data.length();
        bind[3].is_null = 0;

        int status = mysql_stmt_bind_param(conn_.statements_[stindex], &bind[0]);
        checkError(status, stindex, "unable to bind parameters");

        // Execute the statement
        status = mysql_stmt_execute(conn_.statements_[stindex]);
        if (status != 0) {
            // Failure: check for the special case of duplicate entry.  If this is
            // the case, we return false to indicate that the row was not added.
            // Otherwise we throw an exception.
            if (mysql_errno(conn_.mysql_) == ER_DUP_ENTRY) {
                return (false);
            }
            checkError(status, stindex, "unable to execute");
        }
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Could not create bind array to insert configuration "
                                        << ", reason: " << ex.what());
    }

    // Insert succeeded
    return true;
}

bool MySqlSrvConfigMgr::updateConfig4(const std::string& config_id,
                                      const std::string& json_data,
                                      const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_UPDATE_SRV_CONFIG4)
        .arg(config_id);

    const StatementIndex stindex = MySqlSrvConfigMgr::UPDATE_CONFIGURATION4;
    return updateConfigCommon(stindex, config_id, json_data, generic_data);
}

bool MySqlSrvConfigMgr::updateConfig6(const std::string& config_id,
                                      const std::string& json_data,
                                      const std::string& generic_data) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_UPDATE_SRV_CONFIG6)
        .arg(config_id);

    const StatementIndex stindex = MySqlSrvConfigMgr::UPDATE_CONFIGURATION6;
    return updateConfigCommon(stindex, config_id, json_data, generic_data);
}

bool MySqlSrvConfigMgr::updateConfigCommon(StatementIndex stindex,
                                           const std::string& config_id,
                                           const std::string& json_data,
                                           const std::string& generic_data) const {
    try {
        MYSQL_BIND bind[4];  // Bind array
        memset(bind, 0, sizeof(bind));

        MYSQL_TIME expire_time;
        conn_.convertToDatabaseTime(time(NULL), expire_time);
        bind[0].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind[0].buffer = reinterpret_cast<char*>(&expire_time);
        bind[0].buffer_length = sizeof(expire_time);
        bind[0].is_null = 0;

        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = const_cast<char*>(json_data.c_str());
        bind[1].buffer_length = json_data.length();
        bind[1].is_null = 0;

        bind[2].buffer_type = MYSQL_TYPE_STRING;
        bind[2].buffer = const_cast<char*>(generic_data.c_str());
        bind[2].buffer_length = generic_data.length();
        bind[2].is_null = 0;

        bind[3].buffer_type = MYSQL_TYPE_STRING;
        bind[3].buffer = const_cast<char*>(config_id.c_str());
        bind[3].buffer_length = config_id.length();
        bind[3].is_null = 0;

        int status = mysql_stmt_bind_param(conn_.statements_[stindex], &bind[0]);
        checkError(status, stindex, "unable to bind parameters");

        // Execute the statement
        status = mysql_stmt_execute(conn_.statements_[stindex]);
        if (status != 0) {
            // Failure: check for the special case of duplicate entry.  If this is
            // the case, we return false to indicate that the row was not added.
            // Otherwise we throw an exception.
            if (mysql_errno(conn_.mysql_) == ER_DUP_ENTRY) {
                return (false);
            }
            checkError(status, stindex, "unable to execute");
        }
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Could not create bind to update configuration: "
                                        << ", reason: " << ex.what());
    }

    // Update succeeded
    return true;
}

void MySqlSrvConfigMgr::checkError(int status, StatementIndex index, const char* what) const {
    if (status != 0) {
        switch (mysql_errno(conn_.mysql_)) {
        // These are the ones we consider fatal. Remember this method is
        // used to check errors of API calls made subsequent to successfully
        // connecting.  Errors occuring while attempting to connect are
        // checked in the connection code. An alternative would be to call
        // mysql_ping() - assuming autoreconnect is off. If that fails
        // then we know connection is toast.
        case CR_SERVER_GONE_ERROR:
        case CR_SERVER_LOST:
        case CR_OUT_OF_MEMORY:
        case CR_CONNECTION_ERROR:
            // We're exiting on fatal
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_MYSQL_FATAL_ERROR)
                .arg(what)
                .arg(conn_.text_statements_[index])
                .arg(mysql_error(conn_.mysql_))
                .arg(mysql_errno(conn_.mysql_));
            exit(-1);

        default:
            // Connection is ok, so it must be an SQL error
            isc_throw(DbOperationError, what << " for <" << conn_.text_statements_[index]
                                             << ">, reason: " << mysql_error(conn_.mysql_)
                                             << " (error code " << mysql_errno(conn_.mysql_)
                                             << ")");
        }
    }
}

bool MySqlSrvConfigMgr::startTransaction() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_BEGIN_TRANSACTION);
    if (mysql_query(conn_.mysql_, "START TRANSACTION")) {
        isc_throw(DbOperationError, "start transaction failed: " << mysql_error(conn_.mysql_));
    }

    return true;
}

void MySqlSrvConfigMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_COMMIT);
    if (mysql_commit(conn_.mysql_) != 0) {
        isc_throw(DbOperationError, "commit failed: " << mysql_error(conn_.mysql_));
    }
}

void MySqlSrvConfigMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ROLLBACK);
    if (mysql_rollback(conn_.mysql_) != 0) {
        isc_throw(DbOperationError, "rollback failed: " << mysql_error(conn_.mysql_));
    }
}

}  // namespace dhcp
}  // namespace isc
