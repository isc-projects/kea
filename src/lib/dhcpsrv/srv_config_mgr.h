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

#ifndef SRV_CONFIG_MGR_H
#define SRV_CONFIG_MGR_H

#include <dhcpsrv/db_exceptions.h>
#include <dhcpsrv/sql_common.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <stdint.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Holds server configuration data
///
/// Holds server configuration data in order to read/write the configuration
/// from/to the database.
///
struct SrvConfigInfo {
    std::string config_id_;
    int64_t timestamp_;
    std::string json_data_;
    std::string generic_data_;
};

/// @brief Shared pointer to server configuration string.
typedef boost::shared_ptr<SrvConfigInfo> SrvConfigInfoPtr;
typedef std::vector<SrvConfigInfoPtr> SrvConfigInfoCollection;

/// @brief Abstract Server Configuration Manager
///
/// This is an abstract API for server configuration database backends.
/// It provides unified interface to all backends. As this is an abstract class,
/// it should not be used directly, but rather specialized derived class should
/// be used
/// instead.
///
/// This class throws no exceptions.  However, methods in concrete
/// implementations of this class may throw exceptions: see the documentation
/// of those classes for details.
class SrvConfigMgr {
public:
    /// @brief Constructor
    ///
    SrvConfigMgr();

    /// @brief Destructor
    virtual ~SrvConfigMgr();

    /// @brief Class method to return extended version info
    /// This class method must be redeclared and redefined in derived classes
    static std::string getDBVersion();

    /// @brief Adds if not exists or updates and existing DHCP V4 server
    /// configuration
    ///
    /// One database contains server configuration data only for one kea server.
    ///
    /// @param old_config_timestamp If there is already a server configuration
    /// in the database
    ///        then the configuration's timestamp from database is compared with
    ///        the provided
    ///        one. The update takes place only if the timestamps are the same.
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @result true if the configuration was added/updated, false if not.
    virtual bool updateConfig4(int64_t old_config_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const = 0;

    /// @brief Adds if not exists or updates and existing DHCP V6 server
    /// configuration
    ///
    /// One database contains server configuration data only for one kea server.
    ///
    /// @param old_config_timestamp If there is already a server configuration
    /// in the database
    ///        then the configuration's timestamp from database is compared with
    ///        the provided
    ///        one. The update takes place only if the timestamps are the same.
    ///
    /// @param json_data The server configuration to be written in json format
    ///
    /// @param generic_data The server configuration to be written in GENERIC
    /// format
    ///
    /// @result true if the configuration was added/updated, false if not.
    virtual bool updateConfig6(int64_t old_config_timestamp,
                               const std::string& json_data,
                               const std::string& generic_data) const = 0;

    virtual SrvConfigInfoPtr getConfig4Timestamp() const = 0;

    virtual SrvConfigInfoPtr getConfig6Timestamp() const = 0;

    /// @brief Returns server configuration information
    ///
    /// This method returns the server configuration.
    /// One database contains server configuration data only for one kea server.
    ///
    /// @return smart pointer to the configuration (or NULL if a configuration
    /// is not found)
    virtual SrvConfigInfoPtr getJsonConfig4() const = 0;

    virtual SrvConfigInfoPtr getGenericConfig4() const = 0;

    /// @brief Returns server configuration information
    ///
    /// This method returns the server configuration.
    /// One database contains server configuration data only for one kea server.
    ///
    /// @return smart pointer to the configuration (or NULL if a configuration
    /// is not found)
    virtual SrvConfigInfoPtr getJsonConfig6() const = 0;

    virtual SrvConfigInfoPtr getGenericConfig6() const = 0;

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
    /// If we ever have 3 version functions:
    /// A. abstract API version
    /// B. backend version
    /// C. database version (stored in the database scheme)
    /// we could check that:
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

#endif // SRV_CONFIG_MGR_H
