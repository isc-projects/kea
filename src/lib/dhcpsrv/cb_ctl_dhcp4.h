// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CTL_DHCP4_H
#define CB_CTL_DHCP4_H

#include <dhcpsrv/cb_ctl_dhcp.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/srv_config.h>

namespace isc {
namespace dhcp {

/// @brief Implementation of the mechanisms to control the use of
/// the Configuration Backends by the DHCPv4 server.
///
/// It implements fetching and merging DHCPv4 server configuration from
/// the database into the staging or current configuration.
///
/// @tparam ConfigBackendMgrType Type of the Config Backend Manager used
/// by the server implementing this class. For example, for the DHCPv4
/// server it will be @c ConfigBackendDHCPv4Mgr.
class CBControlDHCPv4 : public CBControlDHCP<ConfigBackendDHCPv4Mgr> {
protected:

    /// @brief Fetches the entire or partial configuration from the database.
    ///
    /// This method is called by the starting up server to fetch and merge
    /// the entire configuration from the database or to fetch configuration
    /// updates periodically, e.g. as a result of triggering an interval
    /// timer callback.
    ///
    /// @param srv_cfg pointer to the staging configuration that should
    /// hold the config backends list and other partial configuration read
    /// from the file in case the method is called upon the server's start
    /// up. It is a pointer to the current server configuration if the
    /// method is called to fetch configuration updates.
    /// @param fetch_updates_only boolean value indicating if the method is
    /// called upon the server start up (false) or it is called to fetch
    /// configuration updates (true).
    virtual void databaseConfigApply(const process::ConfigPtr& srv_cfg,
                                     const db::BackendSelector& backend_selector,
                                     const db::ServerSelector& server_selector,
                                     const boost::posix_time::ptime& lb_modification_time,
                                     const db::AuditEntryCollection& audit_entries);
};

typedef boost::shared_ptr<CBControlDHCPv4> CBControlDHCPv4Ptr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CB_CTL_DHCP4_H
