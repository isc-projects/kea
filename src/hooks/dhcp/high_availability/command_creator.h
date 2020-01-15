// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_COMMAND_CREATOR_H
#define HA_COMMAND_CREATOR_H

#include <ha_server_type.h>
#include <cc/data.h>
#include <dhcpsrv/lease.h>
#include <string>

namespace isc {
namespace ha {

/// @brief Holds a collection of functions which generate commands
/// used for High Availability.
class CommandCreator {
public:

    /// @brief Creates dhcp-disable command for DHCP server.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createDHCPDisable(const unsigned int max_period,
                      const HAServerType& server_type);

    /// @brief Creates dhcp-enable command for DHCP server.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createDHCPEnable(const HAServerType& server_type);

    /// @brief Creates ha-heartbeat command for DHCP server.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createHeartbeat(const HAServerType& server_type);

    /// @brief Creates lease4-update command.
    ///
    /// It adds "force-create" parameter to the lease information to force
    /// the remote server to create the lease if it doesn't exist in its
    /// lease database.
    ///
    /// @param lease4 Reference to a lease for which the command should
    /// be created.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease4Update(const dhcp::Lease4& lease4);

    /// @brief Creates lease4-del command.
    ///
    /// @param lease4 Reference to a lease for which the command should
    /// be created.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease4Delete(const dhcp::Lease4& lease4);

    /// @brief Creates lease4-get-all command.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease4GetAll();

    /// @brief Creates lease4-get-page command.
    ///
    /// @param lease4 Pointer to the last lease returned on the previous
    /// page of leases. This lease is used to set the value of the "from"
    /// parameter in the lease4-get-page command. If this command is sent
    /// to fetch the first page, the @c lease4 parameter should be set to
    /// null.
    /// @param limit Limit of leases on the page.
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease4GetPage(const dhcp::Lease4Ptr& lease4,
                        const uint32_t limit);

    /// @brief Creates lease6-bulk-update command.
    ///
    /// @param leases Pointer to the collection of leases to be created
    /// or/and updated.
    /// @param deleted_leases Pointer to the collection of leases to be
    /// deleted.
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease6BulkApply(const dhcp::Lease6CollectionPtr& leases,
                          const dhcp::Lease6CollectionPtr& deleted_leases);

    /// @brief Creates lease6-update command.
    ///
    /// It adds "force-create" parameter to the lease information to force
    /// the remote server to create the lease if it doesn't exist in its
    /// lease database.
    ///
    /// @param lease6 Reference to a lease for which the command should
    /// be created.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease6Update(const dhcp::Lease6& lease6);

    /// @brief Creates lease6-del command.
    ///
    /// @param lease6 Reference to a lease for which the command should
    /// be created.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease6Delete(const dhcp::Lease6& lease6);

    /// @brief Creates lease6-get-all command.
    ///
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease6GetAll();

    /// @brief Creates lease6-get-page command.
    ///
    /// @param lease6 Pointer to the last lease returned on the previous
    /// page of leases. This lease is used to set the value of the "from"
    /// parameter in the lease6-get-page command. If this command is sent
    /// to fetch the first page, the @c lease6 parameter should be set to
    /// null.
    /// @param limit Limit of leases on the page.
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createLease6GetPage(const dhcp::Lease6Ptr& lease6,
                        const uint32_t limit);

    /// @brief Creates ha-maintenance-notify command.
    ///
    /// @param cancel boolean value indicating if the maintenance
    /// is being cancelled (true) or requested (false).
    /// @param server_type type of the DHCP server, i.e. v4 or v6.
    /// @return Pointer to the JSON representation of the command.
    static data::ConstElementPtr
    createMaintenanceNotify(const bool cancel, const HAServerType& server_type);

private:

    /// @brief Replaces "cltt" with "expire" value within the lease.
    ///
    /// The "lease_cmds" hooks library expects "expire" time to be provided
    /// for a lease rather than "cltt". If the "expire" is not provided
    /// it will use the current time for a cltt. We want to make sure that
    /// the lease is inserted into the lease database untouched.
    /// Hence, this method is used to replace "cltt" with "expire" time in
    /// the lease.
    ///
    /// @param lease in the JSON format created using @c Lease::toElement
    /// method.
    static void insertLeaseExpireTime(data::ElementPtr& lease);

    /// @brief Sets "service" parameter for the command.
    ///
    /// Commands generated by the HA hooks library are always sent to
    /// DHCPv4 or DHCPv6 server via Control Agent. The Control Agent
    /// requires a "service" parameter which provides the list of servers
    /// to which the command should be forwarded. In our case, we always
    /// send commands to a single server so this method appends a single
    /// element list to the command.
    ///
    /// @todo We should consider moving this functionality to the main
    /// Kea code.
    ///
    /// @param [out] command command to which the service parameter must
    /// be inserted.
    /// @param server_type DHCP server type, i.e. DHCPv4 or DHCPv6.
    ///
    /// @return Pointer to the command with service parameter inserted.
    static void
    insertService(data::ConstElementPtr& command,
                  const HAServerType& server_type);
};

} // end of namespace ha
} // end of namespace isc

#endif
