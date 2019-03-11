// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2015-2018 Deutsche Telekom AG.
//
// Authors: Razvan Becheriu <razvan.becheriu@qualitance.com>
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

#ifndef CQL_LEASE_MGR_H
#define CQL_LEASE_MGR_H

#include <cql/cql_connection.h>
#include <cql/cql_exchange.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/dhcpsrv_exceptions.h>
#include <dhcpsrv/lease_mgr.h>

#include <boost/scoped_ptr.hpp>

#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Cassandra Lease Manager
///
/// This class provides the @ref isc::dhcp::LeaseMgr interface to the Cassandra
/// database. Use of this backend implies that a CQL database is available
/// and that the Kea schema has been created within it.
class CqlLeaseMgr : public LeaseMgr {
public:
    /// @brief Constructor
    ///
    /// Uses the following keywords in the parameters passed to it to
    /// connect to the Cassandra cluster (if omitted, defaults specified in
    /// parentheses):
    /// - keyspace: name of the database to which to connect (keatest)
    /// - contact-points: IP addresses of the nodes to connect to (127.0.0.1)
    /// - consistency: consistency level (quorum)
    /// - serial-consistency: serial consistency level (serial)
    /// - port: The TCP port to use (9042)
    /// - user - credentials to use when connecting (no username)
    /// - password - credentials to use when connecting (no password)
    /// - reconnect-wait-time 2000
    /// - connect-timeout 5000
    /// - request-timeout 12000
    /// - tcp-keepalive no
    /// - tcp-nodelay no
    ///
    /// Finally, all the CQL commands are pre-compiled.
    ///
    /// @param parameters a data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @throw isc::db::NoDatabaseName Mandatory database name not given
    /// @throw isc::db::DbOpenError Error opening the database or the schema
    /// version is invalid.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    explicit CqlLeaseMgr(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor (closes database)
    virtual ~CqlLeaseMgr();

    /// @brief Local version of getDBVersion() class method
    static std::string getDBVersion();

    /// @brief Adds an IPv4 lease
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual bool addLease(const Lease4Ptr& lease) override;

    /// @brief Adds an IPv6 lease
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual bool addLease(const Lease6Ptr& lease) override;

    /// @brief Basic lease access methods. Obtain leases from the database using
    ///     various criteria.
    /// @{

    /// @brief Returns an IPv4 lease for specified IPv4 address
    ///
    /// This method return a lease that is associated with a given address.
    /// For other query types (by hardware addr, by Client ID) there can be
    /// several leases in different subnets (e.g. for mobile clients that
    /// got address in different subnets). However, for a single address
    /// there can be only one lease, so this method returns a pointer to
    /// a single lease, not a container of leases.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Ptr
    getLease4(const isc::asiolink::IOAddress& addr) const override;

    /// @brief Returns existing IPv4 leases for specified hardware address.
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param hwaddr hardware address of the client
    ///
    /// @return lease collection
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Collection
    getLease4(const isc::dhcp::HWAddr& hwaddr) const override;

    /// @brief Returns existing IPv4 leases for specified hardware address
    ///        and a subnet
    ///
    /// There can be at most one lease for a given HW address in a single
    /// subnet, so this method with either return a single lease or NULL.
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Ptr getLease4(const isc::dhcp::HWAddr& hwaddr,
                                SubnetID subnet_id) const override;

    /// @brief Returns existing IPv4 leases for specified client-id
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param clientid client identifier
    ///
    /// @return lease collection
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Collection getLease4(const ClientId& clientid) const override;

    /// @brief Returns IPv4 lease for the specified client identifier, HW
    /// address and subnet identifier.
    ///
    /// @param client_id A client identifier.
    /// @param hwaddr hardware address.
    /// @param subnet_id A subnet identifier.
    ///
    /// @return A pointer to the lease or NULL if the lease is not found.
    ///
    /// @throw isc::NotImplemented On every call as this method is currently
    /// not implemented for the CQL backend.
    virtual Lease4Ptr getLease4(const ClientId& client_id,
                                const HWAddr& hwaddr,
                                SubnetID subnet_id) const override;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const override;

    /// @brief Returns all IPv4 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    /// @throw NotImplemented because this method is currently not implemented for
    /// this backend.
    virtual Lease4Collection getLeases4(SubnetID subnet_id) const override;

    /// @brief Returns all IPv4 leases.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    /// @throw NotImplemented because this method is currently not implemented for
    /// this backend.
    virtual Lease4Collection getLeases4() const override;

    /// @brief Returns range of IPv4 leases using paging.
    ///
    /// This method implements paged browsing of the lease database. The first
    /// parameter specifies a page size. The second parameter is optional and
    /// specifies the starting address of the range. This address is excluded
    /// from the returned range. The IPv4 zero address (default) denotes that
    /// the first page should be returned. There is no guarantee about the
    /// order of returned leases.
    ///
    /// The typical usage of this method is as follows:
    /// - Get the first page of leases by specifying IPv4 zero address as the
    ///   beginning of the range.
    /// - Last address of the returned range should be used as a starting
    ///   address for the next page in the subsequent call.
    /// - If the number of leases returned is lower than the page size, it
    ///   indicates that the last page has been retrieved.
    /// - If there are no leases returned it indicates that the previous page
    ///   was the last page.
    ///
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection
    getLeases4(const asiolink::IOAddress& lower_bound_address,
               const LeasePageSize& page_size) const override;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// For a given address, we assume that there will be only one lease.
    /// The assumption here is that there will not be site or link-local
    /// addresses used, so there is no way of having address duplication.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::BadValue record retrieved from database had an invalid
    ///        lease type field.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Ptr
    getLease6(Lease::Type type,
              const isc::asiolink::IOAddress& addr) const override;

    /// @brief Returns existing IPv6 leases for a given DUID+IA combination
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::BadValue record retrieved from database had an invalid
    ///        lease type field.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Collection getLeases6(Lease::Type type,
                                        const DUID& duid,
                                        uint32_t iaid) const override;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id subnet id of the subnet the lease belongs to
    ///
    /// @return lease collection (may be empty if no lease is found)
    ///
    /// @throw isc::BadValue record retrieved from database had an invalid
    ///        lease type field.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Collection getLeases6(Lease::Type type,
                                        const DUID& duid,
                                        uint32_t iaid,
                                        SubnetID subnet_id) const override;

    /// @brief Returns all IPv6 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    /// @throw NotImplemented because this method is currently not implemented for
    /// this backend.
    virtual Lease6Collection getLeases6(SubnetID subnet_id) const override;

    /// @brief Returns all IPv6 leases.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    /// @throw NotImplemented because this method is currently not implemented for
    /// this backend.
    virtual Lease6Collection getLeases6() const override;

    /// @brief Returns all IPv6 leases.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(const DUID& duid) const override;
    
    /// @brief Returns range of IPv6 leases using paging.
    ///
    /// This method implements paged browsing of the lease database. The first
    /// parameter specifies a page size. The second parameter is optional and
    /// specifies the starting address of the range. This address is excluded
    /// from the returned range. The IPv6 zero address (default) denotes that
    /// the first page should be returned. There is no guarantee about the
    /// order of returned leases.
    ///
    /// The typical usage of this method is as follows:
    /// - Get the first page of leases by specifying IPv6 zero address as the
    ///   beginning of the range.
    /// - Last address of the returned range should be used as a starting
    ///   address for the next page in the subsequent call.
    /// - If the number of leases returned is lower than the page size, it
    ///   indicates that the last page has been retrieved.
    /// - If there are no leases returned it indicates that the previous page
    ///   was the last page.
    ///
    /// @param lower_bound_address IPv6 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @warning This method is currently not implemented. Cassandra doesn't
    /// support conversions from text to inet. Therefore, we're unable to
    /// compare the IPv6 addresses to find the desired range. A solution for
    /// this might be to store the IPv6 address as INET type rather than
    /// text, but this is currently low priority.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    ///
    /// @throw isc::NotImplemented
    virtual Lease6Collection
    getLeases6(const asiolink::IOAddress& lower_bound_address,
               const LeasePageSize& page_size) const override;

    /// @brief Returns a collection of expired DHCPv4 leases.
    ///
    /// This method returns at most @c max_leases expired leases. The leases
    /// returned haven't been reclaimed, i.e. the database query must exclude
    /// reclaimed leases from the results returned.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    virtual void getExpiredLeases4(Lease4Collection& expired_leases,
                                   const size_t max_leases) const override;

    /// @brief Returns a collection of expired DHCPv6 leases.
    ///
    /// This method returns at most @c max_leases expired leases. The leases
    /// returned haven't been reclaimed, i.e. the database query must exclude
    /// reclaimed leases from the results returned.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    virtual void getExpiredLeases6(Lease6Collection& expired_leases,
                                   const size_t max_leases) const override;
    /// @}

    /// @brief Updates IPv4 lease.
    ///
    /// Updates the record of the lease in the database (as identified by the
    /// address) with the data in the passed lease object.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// @throw isc::dhcp::NoSuchLease Attempt to update a lease that did not
    ///        exist.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual void updateLease4(const Lease4Ptr& lease4) override;

    /// @brief Updates IPv6 lease.
    ///
    /// Updates the record of the lease in the database (as identified by the
    /// address) with the data in the passed lease object.
    ///
    /// @param lease6 The lease to be updated.
    ///
    /// @throw isc::dhcp::NoSuchLease Attempt to update a lease that did not

    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual void updateLease6(const Lease6Ptr& lease6) override;

    /// @brief Deletes a lease.
    ///
    /// @param addr Address of the lease to be deleted. This can be an IPv4
    ///             address or an IPv6 address.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual bool deleteLease(const isc::asiolink::IOAddress& addr) override;

    /// @brief Deletes all expired and reclaimed DHCPv4 leases.
    ///
    /// @param secs number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t
    deleteExpiredReclaimedLeases4(const uint32_t secs) override;

    /// @brief Deletes all expired and reclaimed DHCPv6 leases.
    ///
    /// @param secs number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t
    deleteExpiredReclaimedLeases6(const uint32_t secs) override;

    /// @brief Creates and runs the IPv4 lease stats query
    ///
    /// It creates an instance of a CqlLeaseStatsQuery4 and then
    /// invokes its start method, which fetches its statistical data
    /// result set by executing the ALL_LEASE_STATS4 query.
    /// The query object is then returned.
    ///
    /// @return The populated query as a pointer to an LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery4() override;

    /// @brief Creates and runs the IPv4 lease stats query for a single subnet
    ///
    /// It creates an instance of a CqlLeaseStatsQuery4 for a single subnet
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetLeaseStatsQuery4(const SubnetID& subnet_id) override;

    /// @brief Creates and runs the IPv4 lease stats query for a single subnet
    ///
    /// It creates an instance of a CqlLeaseStatsQuery4 for a subnet range
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetRangeLeaseStatsQuery4(const SubnetID& first_subnet_id,
                                                                const SubnetID& last_subnet_id) override;
    /// @brief Creates and runs the IPv6 lease stats query
    ///
    /// It creates an instance of a CqlLeaseStatsQuery and then
    /// invokes its start method, which fetches its statistical data
    /// result set by executing the ALL_LEASE_STATS6 query.
    /// The query object is then returned.
    ///
    /// @return The populated query as a pointer to an LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery6() override;

    /// @brief Creates and runs the IPv6 lease stats query for a single subnet
    ///
    /// It creates an instance of a CqlLeaseStatsQuery6 for a single subnet
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetLeaseStatsQuery6(const SubnetID& subnet_id) override;

    /// @brief Creates and runs the IPv6 lease stats query for a single subnet
    ///
    /// It creates an instance of a CqlLeaseStatsQuery6 for a subnet range
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetRangeLeaseStatsQuery6(const SubnetID& first_subnet_id,
                                                                const SubnetID& last_subnet_id) override;
    /// @brief Removes specified IPv4 leases.
    ///
    /// This rather dangerous method is able to remove all leases from specified
    /// subnet.
    ///
    /// @todo: Not implemented yet.
    ///
    /// @param subnet_id identifier of the subnet
    /// @return number of leases removed.
    virtual size_t wipeLeases4(const SubnetID& subnet_id) override;

    /// @brief Removed specified IPv6 leases.
    ///
    /// This rather dangerous method is able to remove all leases from specified
    /// subnet.
    ///
    /// @todo: Not implemented yet.
    ///
    /// @param subnet_id identifier of the subnet
    /// @return number of leases removed.
    virtual size_t wipeLeases6(const SubnetID& subnet_id) override;

    /// @brief Return backend type
    ///
    /// @return Type of the backend.
    virtual std::string getType() const override {
        return (std::string("cql"));
    }

    /// @brief Returns name of the database.
    ///
    /// @return database name
    virtual std::string getName() const override;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const override;

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers. "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual VersionPair getVersion() const override;

    /// @brief Commit Transactions
    ///
    /// This is a no-op for Cassandra.
    virtual void commit() override;

    /// @brief Rollback Transactions
    ///
    /// This is a no-op for Cassandra.
    virtual void rollback() override;

private:
    /// @brief Database connection object
    mutable db::CqlConnection dbconn_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // CQL_LEASE_MGR_H
