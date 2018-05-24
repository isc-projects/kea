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

#ifndef SRV_CONFIG_MASTER_MGR_H
#define SRV_CONFIG_MASTER_MGR_H

#include <dhcpsrv/db_exceptions.h>
#include <dhcpsrv/sql_common.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <stdint.h>

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Holds server configuration data from the master database.
///
/// Holds server configuration data from the master database.
///
struct SrvConfigMasterInfo {
    std::string instance_id_;
    int64_t timestamp_;
    std::string server_config_;
    std::string config_database_;
    std::string config_database_name_;
};

/// @brief Shared pointer to server configuration string.
typedef boost::shared_ptr<SrvConfigMasterInfo> SrvConfigMasterInfoPtr;
typedef std::vector<SrvConfigMasterInfoPtr> SrvConfigMasterInfoCollection;

/// @brief Abstract Server Configuration Manager
///
/// This is an abstract API for server configuration database backends.
/// It provides unified interface to all backends. As this is an abstract class,
/// it should not be used directly, but rather specialized derived class should
/// be used instead.
///
/// This class throws no exceptions. However, methods in concrete
/// implementations of this class may throw exceptions: see the documentation
/// of those classes for details.
class SrvConfigMasterMgr {
public:
    /// @brief Constructor
    ///
    SrvConfigMasterMgr();

    /// @brief Destructor
    virtual ~SrvConfigMasterMgr();

    /// @brief Class method to return extended version info
    /// This class method must be redeclared and redefined in derived classes
    static std::string getDBVersion();

    virtual bool clearServersConfig4() const = 0;

    virtual bool clearServersConfig6() const = 0;

    virtual bool addServerConfig4(const std::string& instance_id,
                                  const std::string& server_config,
                                  const std::string& config_database,
                                  const std::string& config_database_name) const = 0;

    virtual bool addServerConfig6(const std::string& instance_id,
                                  const std::string& server_config,
                                  const std::string& config_database,
                                  const std::string& config_database_name) const = 0;

    /// @brief Returns DHCPv4 instance configuration information
    ///
    /// This method returns the instance configuration.
    ///
    /// @return smart pointer to the configuration (or NULL if a configuration
    /// is not found)
    virtual SrvConfigMasterInfoPtr
    getConfig4(const std::string& instance_id) const = 0;

    /// @brief Returns DHCPv6 instance configuration information
    ///
    /// This method returns the instance configuration.
    ///
    /// @return smart pointer to the configuration (or NULL if a configuration
    /// is not found)
    virtual SrvConfigMasterInfoPtr
    getConfig6(const std::string& instance_id) const = 0;

    virtual bool
    getConfig4(const std::string& config_database_name,
               std::vector<SrvConfigMasterInfoPtr>& serverInfo) const = 0;

    virtual bool
    getConfig6(const std::string& config_database_name,
               std::vector<SrvConfigMasterInfoPtr>& serverInfo) const = 0;

    virtual SrvConfigMasterInfoPtr
    getMasterConfig4Timestamp(const std::string& instance_id) const = 0;

    virtual SrvConfigMasterInfoPtr
    getMasterConfig6Timestamp(const std::string& instance_id) const = 0;

    virtual bool
    getServersConfig4ShardsName(std::set<std::string>& shards_list) const = 0;

    virtual bool
    getServersConfig6ShardsName(std::set<std::string>& shards_list) const = 0;

    /// @brief Start Transaction
    ///
    /// Start transaction for database operations. On databases that don't
    /// support transactions, this is a no-op.
    virtual bool startTransaction() = 0;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    virtual void commit() = 0;

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    virtual void rollback() = 0;

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @todo: We will need to implement 3 version functions eventually:
    /// A. abstract API version
    /// B. backend version
    /// C. database version (stored in the database scheme)
    ///
    /// and then check that:
    /// B>=A and B=C (it is ok to have newer backend, as it should be backward
    /// compatible)
    /// Also if B>C, some database upgrade procedure may be triggered
    virtual VersionPair getVersion() const = 0;

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const = 0;
};

}  // namespace dhcp
}  // namespace isc

#endif  // SRV_CONFIG_MASTER_MGR_H
