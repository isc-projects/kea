// Copyright (C) 2016 Deutsche Telekom AG.
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

#ifndef SRV_CONFIG_MASTER_MGR_FACTORY_H
#define SRV_CONFIG_MASTER_MGR_FACTORY_H

#include <dhcpsrv/database_connection.h>
#include <dhcpsrv/srv_config_master_mgr.h>
#include <exceptions/exceptions.h>

#include <boost/scoped_ptr.hpp>

#include <string>

namespace isc {
namespace dhcp {

/// @brief No configuration manager exception
///
/// Thrown if an attempt is made to get a reference to the current configuration
/// manager and none is currently available.
class NoServerConfigMasterManager : public Exception {
public:
    NoServerConfigMasterManager(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

/// @brief Server Configuration Manager Factory
///
/// This class comprises nothing but static methods used to create a server
/// configuration manager. It analyzes the database information passed to the
/// creation function and instantiates an appropriate server configuration
/// manager based on the type requested.
///
/// Strictly speaking these functions could be stand-alone functions.  However,
/// it is convenient to encapsulate them in a class for naming purposes.
///
/// @todo: Will need to develop some form of registration mechanism for
///        user-supplied backends (so that there is no need to modify the code).
class SrvConfigMasterMgrFactory {
public:
    /// @brief Create an instance of a server configuration manager.
    ///
    /// Each database backend has its own server configuration manager type.
    /// This static method sets the "current" server configuration manager
    /// to be a manager of the appropriate type.  The actual server
    /// configuration is returned by the "instance" method.
    ///
    /// @note When called, the current server configuration manager is
    ///       <b>always</b> destroyed and a new one created - even if
    ///       the parameters are the same.
    ///
    /// dbaccess is a generic way of passing parameters. Parameters are passed
    /// in the "name=value" format, separated by spaces.  The data MUST include
    /// a keyword/value pair of the form "type=dbtype" giving the database
    /// type, e.q. "mysql" or "sqlite3".
    ///
    /// @param dbaccess Database access parameters.  These are in the form of
    ///        "keyword=value" pairs, separated by spaces. They are backend-
    ///        -end specific, although must include the "type" keyword which
    ///        gives the backend in use.
    ///
    /// @throw isc::InvalidParameter dbaccess string does not contain the "type"
    ///        keyword.
    /// @throw isc::dhcp::InvalidType The "type" keyword in dbaccess does not
    ///        identify a supported backend.
    static void create(const std::string& dbaccess);

    /// @brief Destroy server configuration manager
    ///
    /// Destroys the current server configuration manager object.  This should
    /// have the effect of closing the database connection.  The method is a
    /// no-op if no server configuration manager is available.
    static void destroy();

    /// @brief Return current server configuration manager
    ///
    /// Returns an instance of the "current" server configuration manager.
    /// An exception will be thrown if none is available.
    ///
    /// @throw isc::dhcp::NoLeaseManager No lease manager is available: use
    ///        create() to create one before calling this method.
    static SrvConfigMasterMgr& instance();

    static bool initialized();

private:
    /// @brief Hold pointer to server configuration manager
    ///
    /// Holds a pointer to the singleton server configuration manager.
    /// The singleton is encapsulated in this method to avoid a "static
    /// initialization fiasco" if defined in an external static variable.
    static boost::scoped_ptr<SrvConfigMasterMgr>& getConfigurationMgrPtr();
};

}  // namespace dhcp
}  // namespace isc

#endif  // SRV_CONFIG_MASTER_MGR_FACTORY_H
