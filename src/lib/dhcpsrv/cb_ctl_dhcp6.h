// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CTL_DHCP6_H
#define CB_CTL_DHCP6_H

#include <dhcpsrv/cb_ctl_dhcp.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/srv_config.h>

namespace isc {
namespace dhcp {

/// @brief Implementation of the mechanisms to control the use of
/// the Configuration Backends by the DHCPv6 server.
///
/// It implements fetching and merging DHCPv6 server configuration from
/// the database into the staging or current configuration.
///
/// @tparam ConfigBackendMgrType Type of the Config Backend Manager used
/// by the server implementing this class. For example, for the DHCPv6
/// server it will be @c ConfigBackendDHCPv6Mgr.
class CBControlDHCPv6 : public CBControlDHCP<ConfigBackendDHCPv6Mgr> {
protected:

    /// @brief DHCPv6 server specific method to fetch and apply back end
    /// configuration into the local configuration.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param lb_modification_time Lower bound modification time for the
    /// configuration elements to be fetched.
    /// @param audit_entries Audit entries fetched from the database since
    /// the last configuration update. This collection is empty if there
    /// were no updates.
    virtual void databaseConfigApply(const db::BackendSelector& backend_selector,
                                     const db::ServerSelector& server_selector,
                                     const boost::posix_time::ptime& lb_modification_time,
                                     const db::AuditEntryCollection& audit_entries);
};

typedef boost::shared_ptr<CBControlDHCPv6> CBControlDHCPv6Ptr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CB_CTL_DHCP6_H
