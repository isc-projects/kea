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

#ifndef CQL_CONFIGURATION_MGR_H
#define CQL_CONFIGURATION_MGR_H

#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/cql_exchange.h>
#include <dhcpsrv/srv_config_mgr.h>

#include <boost/scoped_ptr.hpp>

#include <string>
#include <utility>

namespace isc {
namespace dhcp {

class CqlConfigExchange;

class CqlSrvConfigMgr : public SrvConfigMgr {
public:
    /// @brief Constructor
    explicit CqlSrvConfigMgr(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor
    virtual ~CqlSrvConfigMgr();

    /// @brief Retrieves IPv4 timestamp.
    virtual SrvConfigInfoPtr getConfig4Timestamp() const override;

    /// @brief Retrieves IPv6 timestamp.
    virtual SrvConfigInfoPtr getConfig6Timestamp() const override;

    /// @brief Retrieves IPv4 configuration in generic format (e.g. yaml).
    virtual SrvConfigInfoPtr getGenericConfig4() const override;

    /// @brief Retrieves IPv6 configuration in generic format (e.g. yaml).
    virtual SrvConfigInfoPtr getGenericConfig6() const override;

    /// @brief Retrieves IPv4 configuration in JSON format.
    virtual SrvConfigInfoPtr getJsonConfig4() const override;

    /// @brief Retrieves IPv6 configuration in JSON format.
    virtual SrvConfigInfoPtr getJsonConfig6() const override;

    /// @brief Retrieves database type
    virtual std::string getType() const override;

    /// @brief Retrieves schema version
    virtual VersionPair getVersion() const override;

    /// @brief Local version of getDBVersion() class method
    static std::string getDBVersion();

    /// @brief Adds if not exists or updates an existing DHCP V4 server
    /// configuration
    ///
    /// One database contains server configuration data only for one Kea server.
    ///
    /// @param old_config_timestamp If there is already a server configuration
    /// in the database then the configuration's timestamp from database is
    /// compared with the provided one. The update takes place only if the
    /// timestamps are the same.
    /// @param json_data The server configuration to be written in json format
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @result true if the configuration was added/updated, false if not.
    virtual bool updateConfig4(const int64_t old_config_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const override;

    /// @brief Adds if not exists or updates an existing DHCP V6 server
    /// configuration
    ///
    /// One database contains server configuration data only for one Kea server.
    ///
    /// @param old_config_timestamp If there is already a server configuration
    /// in the database then the configuration's timestamp from database is
    /// compared with the provided one. The update takes place only if the
    /// timestamps are the same.
    /// @param json_data The server configuration to be written in json format
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @result true if the configuration was added/updated, false if not.
    virtual bool updateConfig6(const int64_t old_config_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const override;

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

private:
    /// @brief Inserts a new DHCPv4 server configuration.
    ///
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be a
    /// CQL error.
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
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be a
    /// CQL error.
    ///
    /// @return true if the configuration was added, false if not.
    bool insertConfig6(const std::string& json_data, const std::string& generic_data) const;

    /// @brief Updates an existing DHCPv4 server configuration.
    ///
    ///
    /// @param version the new configuration's version.
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be a
    /// CQL error.
    ///
    /// @return true if the configuration was added/updated, false if not.
    bool updateConfig4(const std::string& config_id,
                       const int64_t timestamp,
                       const std::string& json_data,
                       const std::string& generic_data) const;

    /// @brief Updates an existing DHCPv6 server configuration.
    ///
    ///
    /// @param version the new configuration's version.
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @throw isc::dhcp::DbOperationError Connection is ok, so it must be a
    /// CQL error.
    ///
    /// @return true if the configuration was added/updated, false if not.
    bool updateConfig6(const std::string& config_id,
                       const int64_t timestamp,
                       const std::string& json_data,
                       const std::string& generic_data) const;

    /// @brief Server configuration specific tagged statements
    static CqlTaggedStatement tagged_statements_[];
    /// @brief Database connection object
    mutable CqlConnection dbconn_;
};

class CqlConfigVersionExchange : public CqlVersionExchange {
public:
    /// @brief Cassandra statements
    static StatementMap tagged_statements_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // CQL_CONFIGURATION_MGR_H
