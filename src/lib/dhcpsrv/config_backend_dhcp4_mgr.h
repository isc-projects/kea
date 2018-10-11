// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_BACKEND_DHCP4_MGR_H
#define CONFIG_BACKEND_DHCP4_MGR_H

#include <config_backend/base_config_backend_mgr.h>
#include <dhcpsrv/config_backend_pool_dhcp4.h>

#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Configuration Backend Manager for DHPCv4 servers.
///
/// Implements the "manager" class which holds information about the
/// supported and configured backends and provides access to those
/// backends. This is similar to @c HostMgr and @c LeaseMgr singletons
/// being used by the DHCP servers.
///
/// It is implemented as a singleton that can be accessed from any place
/// within the server code. This includes server configuration, data
/// fetching during normal server operation and data management, including
/// processing of control commands implemented within hooks libraries.
///
/// Unlike @c HostMgr, the it does not directly expose the API to fetch and
/// manipulate the data in the database. This is done via, the Configuration
/// Backend Pool, see @c ConfigBackendPoolDHCPv4 for details.
class ConfigBackendDHCPv4Mgr : public cb::BaseConfigBackendMgr<ConfigBackendPoolDHCPv4>,
                               public boost::noncopyable {
public:
    /// @brief Creates new instance of the @c ConfigBackendDHCPv4Mgr.
    ///
    /// If an instance of the @c ConfigBackendDHCPv4Mgr already exists,
    /// it will be replaced by the new instance. Thus, all factories
    /// will be unregistered and config databases will be dropped.
    static void create();

    /// @brief Destroys the instance of the @c ConfigBackendDHCPv4Mgr.
    ///
    /// If an instance of the @c ConfigBackendDHCPv4Mgr exists,
    /// it will be destroyed.  Thus, all factories will be unregistered
    /// and config databases will be dropped.
    static void destroy();

    /// @brief Returns a sole instance of the @c ConfigBackendDHCPv4Mgr.
    ///
    /// This method should be used to retrieve an instance of the @c ConfigBackendDHCPv4Mgr
    /// to be used to gather/manage config backends. It returns an instance
    /// of the @c ConfigBackendDHCPv4Mgr created by the @c create method. If
    /// the instance doesn't exist yet, it is created using the @c create method
    /// with the an empty set of configuration databases.
    static ConfigBackendDHCPv4Mgr& instance();

private:
    /// @brief Private default constructor.
    ConfigBackendDHCPv4Mgr() {}

    /// @brief Returns a pointer to the currently used instance of the
    /// @c ConfigBackendDHCPv4Mgr.
    static boost::scoped_ptr<ConfigBackendDHCPv4Mgr>& getConfigBackendDHCPv4MgrPtr();
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CONFIG_BACKEND_DHCP4_MGR_H
