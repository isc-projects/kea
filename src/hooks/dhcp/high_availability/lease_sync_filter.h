// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_LEASE_SYNC_FILTER_H
#define HA_LEASE_SYNC_FILTER_H

#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <ha_config.h>
#include <ha_server_type.h>
#include <string>
#include <unordered_set>

namespace isc {
namespace ha {

/// @brief Checks if a lease fetched from the other server should be
/// synchronized into the local lease database.
///
/// In a simple case when a pair of the servers has only one relationship,
/// a server recovering from a crash fetches all leases from the partner
/// during the database synchronization. If a server participates in more
/// than one relationship or the server is connected to a server having
/// more relationships a decision whether a received lease should be stored
/// in a database has to be made based on the filtering rules implemented
/// in this class.
///
/// Suppose there are two relationships configured for the server and
/// each relationship runs the DHCP service for a subset of subnets. When
/// the server is synchronizing the lease database for one of the relationships
/// it receives all leases from its partner. Some of them belong to this
/// relationship and some belong to the other relationship. The server must
/// only accept the leases belonging to the former relationship and discard
/// the remaining ones. Accepting all leases could affect lease database
/// integrity for the second relationship.
///
/// This class implements a simple mechanism to determine whether a lease
/// should be accepted or discarded during the synchronization. It iterates
/// over the configured subnets and checks which of them belong to the
/// current relationship. It next records their IDs. For each received lease
/// it compares the subnet identifier with the recorded list. If the lease
/// matches the list it is accepted, otherwise it is discarded by the
/// @c HAService.
///
/// If none of the configured subnets contain associations with the HA
/// relationships the class accepts all leases. It helps to simplify
/// HA configurations with only one relationship. Such configurations
/// typically lack subnet/HA associations in the subnet specification.
class LeaseSyncFilter {
public:

    /// @brief Constructor.
    ///
    /// @param server_type specified whether it is a DHCPv4 or DHCPv6 server.
    /// @param config HA service configuration.
    LeaseSyncFilter(const HAServerType& server_type, const HAConfigPtr& config);

    /// @brief Applies filtering rules based on the current server configuration.
    ///
    /// This function should be called before each synchronization in case
    /// any subnets have been added or removed. It ensures that the filter
    /// is using the most up-to-date configuration.
    void apply();

    /// @brief Checks if the lease should be accepted or discarded.
    ///
    /// The lease is accepted when the lease subnet belongs to this relationship
    /// or when none of the subnets have explicit associations with the
    /// configured HA relationships.
    ///
    /// @param lease lease instance.
    /// @return true if the lease should be accepted, false otherwise.
    bool shouldSync(const dhcp::LeasePtr& lease) const;

private:

    /// @brief Conditionally applies filtering for a subnet.
    ///
    /// This function is called internally by the @c apply() function. It
    /// checks if the subnet is associated with the relationship and adds
    /// its ID to the list, if so.
    ///
    /// @param subnet subnet instance.
    void conditionallyApplySubnetFilter(const dhcp::SubnetPtr& subnet);

    /// Server type (i.e., DHCPv4 or DHCPv6).
    HAServerType server_type_;

    /// Relationship configuration.
    HAConfigPtr config_;

    /// IDs of the subnets belonging to this relationship.
    std::unordered_set<uint32_t> subnet_ids_;
};


} // end of namespace isc::ha
} // end of namespace isc

#endif // HA_LEASE_SYNC_FILTER_H
