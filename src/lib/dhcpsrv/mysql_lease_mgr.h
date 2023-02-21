// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_LEASE_MGR_H
#define MYSQL_LEASE_MGR_H

#include <asiolink/io_service.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/dhcpsrv_exceptions.h>
#include <dhcpsrv/tracking_lease_mgr.h>
#include <mysql/mysql_connection.h>

#include <boost/scoped_ptr.hpp>
#include <boost/utility.hpp>
#include <mysql.h>

#include <time.h>
#include <vector>
#include <mutex>

namespace isc {
namespace dhcp {

// Forward declaration of the Lease exchange objects.  These classes are defined
// in the .cc file.
class MySqlLease4Exchange;
class MySqlLease6Exchange;

/// @brief MySQL Lease Context
///
/// This class stores the thread context for the manager pool.
/// The class is needed by all get/update/delete functions which must use one
/// or more exchanges to perform database operations.
/// Each context provides a set of such exchanges for each thread.
/// The context instances are lazy initialized by the requesting thread by using
/// the manager's createContext function and are destroyed when the manager's
/// pool instance is destroyed.
class MySqlLeaseContext {
public:

    /// @brief Constructor
    ///
    /// @param parameters See MySqlLeaseMgr constructor.
    /// @param io_service_accessor The IOService accessor function.
    /// @param db_reconnect_callback The connection recovery callback.
    MySqlLeaseContext(const db::DatabaseConnection::ParameterMap& parameters,
                      db::IOServiceAccessorPtr io_service_accessor,
                      db::DbCallback db_reconnect_callback);

    /// The exchange objects are used for transfer of data to/from the database.
    /// They are pointed-to objects as the contents may change in "const" calls,
    /// while the rest of this object does not.  (At alternative would be to
    /// declare them as "mutable".)
    boost::scoped_ptr<MySqlLease4Exchange> exchange4_; ///< Exchange object
    boost::scoped_ptr<MySqlLease6Exchange> exchange6_; ///< Exchange object

    /// @brief MySQL connection
    db::MySqlConnection conn_;
};

/// @brief Type of pointers to contexts.
typedef boost::shared_ptr<MySqlLeaseContext> MySqlLeaseContextPtr;

/// @brief MySQL Lease Context Pool
///
/// This class provides a pool of contexts.
/// The manager will use this class to handle available contexts.
/// There is only one ContextPool per manager per back-end, which is created
/// and destroyed by the respective manager factory class.
class MySqlLeaseContextPool {
public:

    /// @brief The vector of available contexts.
    std::vector<MySqlLeaseContextPtr> pool_;

    /// @brief The mutex to protect pool access.
    std::mutex mutex_;
};

/// @brief Type of pointers to context pools.
typedef boost::shared_ptr<MySqlLeaseContextPool> MySqlLeaseContextPoolPtr;

/// @brief MySQL Lease Manager
///
/// This class provides the \ref isc::dhcp::LeaseMgr interface to the MySQL
/// database.  Use of this backend presupposes that a MySQL database is
/// available and that the Kea schema has been created within it.

class MySqlLeaseMgr : public TrackingLeaseMgr {
public:

    /// @brief Constructor
    ///
    /// Uses the following keywords in the parameters passed to it to
    /// connect to the database:
    /// - name - Name of the database to which to connect (mandatory)
    /// - host - Host to which to connect (optional, defaults to "localhost")
    /// - user - Username under which to connect (optional)
    /// - password - Password for "user" on the database (optional)
    ///
    /// Check the schema version and create an initial context.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @throw isc::dhcp::NoDatabaseName Mandatory database name not given
    /// @throw isc::db::DbOpenError Error opening the database or the schema
    /// version is incorrect.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    MySqlLeaseMgr(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor (closes database)
    virtual ~MySqlLeaseMgr();

    /// @brief Create a new context.
    ///
    /// The database is opened with all the SQL commands pre-compiled.
    ///
    /// @return A new (never null) context.
    /// @throw isc::dhcp::NoDatabaseName Mandatory database name not given.
    /// @throw isc::db::DbOperationError An operation on the open database has
    /// failed.
    MySqlLeaseContextPtr createContext() const;

    /// @brief Attempts to reconnect the server to the lease DB backend manager.
    ///
    /// This is a self-rescheduling function that attempts to reconnect to the
    /// server's lease DB backends after connectivity to one or more have been
    /// lost. Upon entry it will attempt to reconnect via
    /// @ref LeaseMgrFactory::create.
    /// If this is successful, DHCP servicing is re-enabled and server returns
    /// to normal operation.
    ///
    /// If reconnection fails and the maximum number of retries has not been
    /// exhausted, it will schedule a call to itself to occur at the
    /// configured retry interval. DHCP service remains disabled.
    ///
    /// If the maximum number of retries has been exhausted an error is logged
    /// and the server shuts down.
    ///
    /// This function is passed to the connection recovery mechanism. It will be
    /// invoked when a connection loss is detected.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters.
    /// @return true if connection has been recovered, false otherwise.
    static bool dbReconnect(util::ReconnectCtlPtr db_reconnect_ctl);

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
    /// @throw isc::dhcp::DataTruncation Data was truncated on retrieval to
    ///        fit into the space allocated for the result.  This indicates a
    ///        programming error.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr) const override;

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
    /// @throw isc::dhcp::DataTruncation Data was truncated on retrieval to
    ///        fit into the space allocated for the result.  This indicates a
    ///        programming error.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Collection getLease4(const isc::dhcp::HWAddr& hwaddr) const override;

    /// @brief Returns existing IPv4 leases for specified hardware address
    ///        and a subnet
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::dhcp::DataTruncation Data was truncated on retrieval to
    ///        fit into the space allocated for the result.  This indicates a
    ///        programming error.
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
    /// @throw isc::dhcp::DataTruncation Data was truncated on retrieval to
    ///        fit into the space allocated for the result.  This indicates a
    ///        programming error.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Collection getLease4(const ClientId& clientid) const override;

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
    /// @throw isc::dhcp::DataTruncation Data was truncated on retrieval to
    ///        fit into the space allocated for the result.  This indicates a
    ///        programming error.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const override;

    /// @brief Returns all IPv4 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(SubnetID subnet_id) const override;

    /// @brief Returns all IPv4 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(const std::string& hostname) const override;

    /// @brief Returns all IPv4 leases.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
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
    /// @throw isc::dhcp::DataTruncation Data was truncated on retrieval to
    ///        fit into the space allocated for the result.  This indicates a
    ///        programming error.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Ptr getLease6(Lease::Type type,
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
    /// @throw isc::dhcp::DataTruncation Data was truncated on retrieval to
    ///        fit into the space allocated for the result.  This indicates a
    ///        programming error.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
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
    /// @throw isc::dhcp::DataTruncation Data was truncated on retrieval to
    ///        fit into the space allocated for the result.  This indicates a
    ///        programming error.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
                                        uint32_t iaid, SubnetID subnet_id) const override;

    /// @brief Returns all IPv6 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(SubnetID subnet_id) const override;

    /// @brief Returns all IPv6 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(const std::string& hostname) const override;

    /// @brief Returns all IPv6 leases.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6() const override;

    /// @brief Returns all IPv6 leases for the DUID.
    ///
    /// @todo: implement an optimised of the query using index.
    /// @return Lease collection (may be empty if no IPv6 lease found)
    /// for the DUID.
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
    /// @return Lease collection (may be empty if no IPv6 lease found).
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
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note The UPDATE query uses WHERE expire = ? to update the lease only if
    /// the value matches the one received on the SELECT query, effectively
    /// enforcing no update on the lease between SELECT and UPDATE with
    /// different expiration time.
    virtual void updateLease4(const Lease4Ptr& lease4) override;

    /// @brief Updates IPv6 lease.
    ///
    /// Updates the record of the lease in the database (as identified by the
    /// address) with the data in the passed lease object.
    ///
    /// @param lease6 The lease to be updated.
    ///
    /// @throw isc::dhcp::NoSuchLease Attempt to update a lease that did not
    ///        exist.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note The UPDATE query uses WHERE expire = ? to update the lease only if
    /// the value matches the one received on the SELECT query, effectively
    /// enforcing no update on the lease between SELECT and UPDATE with
    /// different expiration time.
    virtual void updateLease6(const Lease6Ptr& lease6) override;

    /// @brief Deletes an IPv4 lease.
    ///
    /// @param lease IPv4 lease being deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note The DELETE query uses WHERE expire = ? to delete the lease only if
    /// the value matches the one received on the SELECT query, effectively
    /// enforcing no update on the lease between SELECT and DELETE with
    /// different expiration time.
    virtual bool deleteLease(const Lease4Ptr& lease) override;

    /// @brief Deletes an IPv6 lease.
    ///
    /// @param lease IPv6 lease being deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    ///
    /// @note The current_cltt_ and current_valid_lft_ are used to maximize the
    /// chance that only one thread or process performs an update or delete
    /// operation on the lease by matching these values with the expiration time
    /// data in the database.
    /// @note The DELETE query uses WHERE expire = ? to delete the lease only if
    /// the value matches the one received on the SELECT query, effectively
    /// enforcing no update on the lease between SELECT and DELETE with
    /// different expiration time.
    virtual bool deleteLease(const Lease6Ptr& lease) override;

    /// @brief Deletes all expired-reclaimed DHCPv4 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases4(const uint32_t secs) override;

    /// @brief Deletes all expired-reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases6(const uint32_t secs) override;

    /// @brief Creates and runs the IPv4 lease stats query
    ///
    /// It creates an instance of a MySqlLeaseStatsQuery4 and then
    /// invokes its start method, which fetches its statistical data
    /// result set by executing the ALL_LEASE_STATS4 query.
    /// The query object is then returned.
    ///
    /// @return The populated query as a pointer to an LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery4() override;

    /// @brief Creates and runs the IPv4 lease stats query for a single subnet
    ///
    /// It creates an instance of a MySqlLeaseStatsQuery4 for a single subnet
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetLeaseStatsQuery4(const SubnetID& subnet_id) override;

    /// @brief Creates and runs the IPv4 lease stats query for a single subnet
    ///
    /// It creates an instance of a MySqlLeaseStatsQuery4 for a subnet range
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
    /// It creates an instance of a MySqlLeaseStatsQuery6 and then
    /// invokes its start method, which fetches its statistical data
    /// result set by executing the ALL_LEASE_STATS6 query.
    /// The query object is then returned.
    ///
    /// @return The populated query as a pointer to an LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery6() override;

    /// @brief Creates and runs the IPv6 lease stats query for a single subnet
    ///
    /// It creates an instance of a MySqlLeaseStatsQuery6 for a single subnet
    /// query and then invokes its start method in which the query constructs its
    /// statistical data result set.  The query object is then returned.
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetLeaseStatsQuery6(const SubnetID& subnet_id) override;

    /// @brief Creates and runs the IPv6 lease stats query for a single subnet
    ///
    /// It creates an instance of a MySqlLeaseStatsQuery6 for a subnet range
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
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const override {
        return (std::string("mysql"));
    }

    /// @brief Returns backend name.
    ///
    /// Each backend have specific name.
    ///
    /// @return Name of the backend.
    virtual std::string getName() const override;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const override;

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual std::pair<uint32_t, uint32_t> getVersion() const override;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// MySQL supports transactions but this manager does not use them.
    virtual void commit() override;

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// MySQL supports transactions but this manager does not use them.
    virtual void rollback() override;

    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of compiled SQL
    /// statements
    enum StatementIndex {
        DELETE_LEASE4,               // Delete from lease4 by address
        DELETE_LEASE4_STATE_EXPIRED, // Delete expired lease4 in a given state
        DELETE_LEASE6,               // Delete from lease6 by address
        DELETE_LEASE6_STATE_EXPIRED, // Delete expired lease6 in a given state
        GET_LEASE4,                  // Get all IPv4 leases
        GET_LEASE4_ADDR,             // Get lease4 by address
        GET_LEASE4_CLIENTID,         // Get lease4 by client ID
        GET_LEASE4_CLIENTID_SUBID,   // Get lease4 by client ID & subnet ID
        GET_LEASE4_HWADDR,           // Get lease4 by HW address
        GET_LEASE4_HWADDR_SUBID,     // Get lease4 by HW address & subnet ID
        GET_LEASE4_PAGE,             // Get page of leases beginning with an address
        GET_LEASE4_SUBID,            // Get IPv4 leases by subnet ID
        GET_LEASE4_HOSTNAME,         // Get IPv4 leases by hostname
        GET_LEASE4_EXPIRE,           // Get lease4 by expiration.
        GET_LEASE6,                  // Get all IPv6 leases
        GET_LEASE6_ADDR,             // Get lease6 by address
        GET_LEASE6_DUID_IAID,        // Get lease6 by DUID and IAID
        GET_LEASE6_DUID_IAID_SUBID,  // Get lease6 by DUID, IAID and subnet ID
        GET_LEASE6_PAGE,             // Get page of leases beginning with an address
        GET_LEASE6_SUBID,            // Get IPv6 leases by subnet ID
        GET_LEASE6_DUID,             // Get IPv6 leases by DUID
        GET_LEASE6_HOSTNAME,         // Get IPv6 leases by hostname
        GET_LEASE6_EXPIRE,           // Get lease6 by expiration.
        INSERT_LEASE4,               // Add entry to lease4 table
        INSERT_LEASE6,               // Add entry to lease6 table
        UPDATE_LEASE4,               // Update a Lease4 entry
        UPDATE_LEASE6,               // Update a Lease6 entry
        ALL_LEASE4_STATS,            // Fetches IPv4 lease statistics
        SUBNET_LEASE4_STATS,         // Fetched IPv4 lease stats for a single subnet.
        SUBNET_RANGE_LEASE4_STATS,   // Fetched IPv4 lease stats for a subnet range.
        ALL_LEASE6_STATS,            // Fetches IPv6 lease statistics
        SUBNET_LEASE6_STATS,         // Fetched IPv6 lease stats for a single subnet.
        SUBNET_RANGE_LEASE6_STATS,   // Fetched IPv6 lease stats for a subnet range.
        CHECK_LEASE4_LIMITS,         // Check if allocated IPv4 leases are inside the set limits.
        CHECK_LEASE6_LIMITS,         // Check if allocated IPv6 leases are inside the set limits.
        IS_JSON_SUPPORTED,           // Checks if JSON support is enabled in the database.
        GET_LEASE4_COUNT_BY_CLASS,   // Fetches the IPv4 lease count for a given class.
        GET_LEASE6_COUNT_BY_CLASS,   // Fetches the IPv6 lease count for given class and lease type.
        NUM_STATEMENTS               // Number of statements
    };

private:

    /// @brief Add Lease Common Code
    ///
    /// This method performs the common actions for both flavours (V4 and V6)
    /// of the addLease method.  It binds the contents of the lease object to
    /// the prepared statement and adds it to the database.
    ///
    /// @param ctx Context
    /// @param stindex Index of statement being executed
    /// @param bind MYSQL_BIND array that has been created for the type
    ///        of lease in question.
    ///
    /// @return true if the lease was added, false if it was not added because
    ///         a lease with that address already exists in the database.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    bool addLeaseCommon(MySqlLeaseContextPtr& ctx,
                        StatementIndex stindex, std::vector<MYSQL_BIND>& bind);

    /// @brief Get Lease Collection Common Code
    ///
    /// This method performs the common actions for obtaining multiple leases
    /// from the database.
    ///
    /// @param ctx Context
    /// @param stindex Index of statement being executed
    /// @param bind MYSQL_BIND array for input parameters
    /// @param exchange Exchange object to use
    /// @param result Returned collection of leases. Note that any leases in
    ///        the collection when this method is called are not erased: the
    ///        new data is appended to the end.
    /// @param single If true, only a single data item is to be retrieved.
    ///        If more than one is present, a MultipleRecords exception will
    ///        be thrown.
    ///
    /// @throw isc::dhcp::BadValue Data retrieved from the database was invalid.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::db::MultipleRecords Multiple records were retrieved
    ///        from the database where only one was expected.
    template <typename Exchange, typename LeaseCollection>
    void getLeaseCollection(MySqlLeaseContextPtr& ctx,
                            StatementIndex stindex,
                            MYSQL_BIND* bind,
                            Exchange& exchange, LeaseCollection& result,
                            bool single = false) const;

    /// @brief Get Lease4 Collection
    ///
    /// Gets a collection of Lease4 objects.  This is just an interface to
    /// the get lease collection common code.
    ///
    /// @param ctx Context
    /// @param stindex Index of statement being executed
    /// @param bind MYSQL_BIND array for input parameters
    /// @param result LeaseCollection object returned.  Note that any leases in
    ///        the collection when this method is called are not erased: the
    ///        new data is appended to the end.
    ///
    /// @throw isc::dhcp::BadValue Data retrieved from the database was invalid.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::db::MultipleRecords Multiple records were retrieved
    ///        from the database where only one was expected.
    void getLeaseCollection(MySqlLeaseContextPtr& ctx,
                            StatementIndex stindex,
                            MYSQL_BIND* bind,
                            Lease4Collection& result) const {
        getLeaseCollection(ctx, stindex, bind, ctx->exchange4_, result);
    }

    /// @brief Get Lease6 Collection
    ///
    /// Gets a collection of Lease6 objects.  This is just an interface to
    /// the get lease collection common code.
    ///
    /// @param ctx Context
    /// @param stindex Index of statement being executed
    /// @param bind MYSQL_BIND array for input parameters
    /// @param result LeaseCollection object returned.  Note that any existing
    ///        data in the collection is erased first.
    ///
    /// @throw isc::dhcp::BadValue Data retrieved from the database was invalid.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::db::MultipleRecords Multiple records were retrieved
    ///        from the database where only one was expected.
    void getLeaseCollection(MySqlLeaseContextPtr& ctx,
                            StatementIndex stindex,
                            MYSQL_BIND* bind,
                            Lease6Collection& result) const {
        getLeaseCollection(ctx, stindex, bind, ctx->exchange6_, result);
    }

    /// @brief Get Lease4 Common Code
    ///
    /// This method performs the common actions for the various getLease4()
    /// methods.  It acts as an interface to the getLeaseCollection() method,
    /// but retrieving only a single lease.
    ///
    /// @param ctx Context
    /// @param stindex Index of statement being executed
    /// @param bind MYSQL_BIND array for input parameters
    /// @param result Lease4 object returned
    void getLease(MySqlLeaseContextPtr& ctx,
                  StatementIndex stindex,
                  MYSQL_BIND* bind,
                  Lease4Ptr& result) const;

    /// @brief Get Lease6 Common Code
    ///
    /// This method performs the common actions for the various getLease6()
    /// methods.  It acts as an interface to the getLeaseCollection() method,
    /// but retrieving only a single lease.
    ///
    /// @param ctx Context
    /// @param stindex Index of statement being executed
    /// @param bind MYSQL_BIND array for input parameters
    /// @param result Lease6 object returned
    void getLease(MySqlLeaseContextPtr& ctx,
                  StatementIndex stindex,
                  MYSQL_BIND* bind,
                  Lease6Ptr& result) const;

    /// @brief Get expired leases common code.
    ///
    /// This method retrieves expired and not reclaimed leases from the
    /// lease database. The returned leases are ordered by the expiration
    /// time. The maximum number of leases to be returned is specified
    /// as an argument.
    ///
    /// @param [out] expired_leases Reference to the container where the
    ///        retrieved leases are put.
    /// @param max_leases Maximum number of leases to be returned.
    /// @param statement_index One of the @c GET_LEASE4_EXPIRE or
    ///        @c GET_LEASE6_EXPIRE.
    ///
    /// @tparam One of the @c Lease4Collection or @c Lease6Collection.
    template<typename LeaseCollection>
    void getExpiredLeasesCommon(LeaseCollection& expired_leases,
                                const size_t max_leases,
                                StatementIndex statement_index) const;

    /// @brief Update lease common code
    ///
    /// Holds the common code for updating a lease.  It binds the parameters
    /// to the prepared statement, executes it, then checks how many rows
    /// were affected.
    ///
    /// @param ctx Context
    /// @param stindex Index of prepared statement to be executed
    /// @param bind Array of MYSQL_BIND objects representing the parameters.
    ///        (Note that the number is determined by the number of parameters
    ///        in the statement.)
    /// @param lease Pointer to the lease object whose record is being updated.
    ///
    /// @throw NoSuchLease Could not update a lease because no lease matches
    ///        the address given.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    template <typename LeasePtr>
    void updateLeaseCommon(MySqlLeaseContextPtr& ctx,
                           StatementIndex stindex,
                           MYSQL_BIND* bind,
                           const LeasePtr& lease);

    /// @brief Delete lease common code
    ///
    /// Holds the common code for deleting a lease.  It binds the parameters
    /// to the prepared statement, executes the statement and checks to
    /// see how many rows were deleted.
    ///
    /// @param ctx Context
    /// @param stindex Index of prepared statement to be executed
    /// @param bind Array of MYSQL_BIND objects representing the parameters.
    ///        (Note that the number is determined by the number of parameters
    ///        in the statement.)
    ///
    /// @return Number of deleted leases.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    uint64_t deleteLeaseCommon(MySqlLeaseContextPtr& ctx,
                               StatementIndex stindex,
                               MYSQL_BIND* bind);

    /// @brief Delete expired-reclaimed leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    /// @param statement_index One of the @c DELETE_LEASE4_STATE_EXPIRED or
    ///        @c DELETE_LEASE6_STATE_EXPIRED.
    ///
    /// @return Number of leases deleted.
    uint64_t deleteExpiredReclaimedLeasesCommon(const uint32_t secs,
                                                StatementIndex statement_index);

    /// @brief Checks if the lease limits set in the given user context are exceeded.
    /// Contains common logic used by @ref checkLimits4 and @ref checkLimits6.
    ///
    /// @param user_context all or part of the lease's user context which, for the intents and
    /// purposes of lease limiting should have the following format
    /// (not all nodes are mandatory and values are given only as examples):
    /// { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2, "prefix-limit": 1 } ],
    ///                        "subnet": { "id": 1, "address-limit": 2, "prefix-limit": 1 } } } }
    ///
    /// @return a string describing a limit that is being exceeded, or an empty
    /// string if no limits are exceeded
    std::string
    checkLimits(isc::data::ConstElementPtr const& user_context, StatementIndex const stindex) const;

    /// @brief Checks if the IPv4 lease limits set in the given user context are exceeded.
    /// MySQL implementation.
    ///
    /// @param user_context all or part of the lease's user context which, for the intents and
    /// purposes of lease limiting should have the following format
    /// (not all nodes are mandatory and values are given only as examples):
    /// { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2 } ],
    ///                        "subnet": { "id": 1, "address-limit": 2 } } } }
    ///
    /// @return a string describing a limit that is being exceeded, or an empty
    /// string if no limits are exceeded
    virtual std::string
    checkLimits4(isc::data::ConstElementPtr const& user_context) const override;

    /// @brief Checks if the IPv6 lease limits set in the given user context are exceeded.
    /// MySQL implementation.
    ///
    /// @param user_context all or part of the lease's user context which, for the intents and
    /// purposes of lease limiting should have the following format
    /// (not all nodes are mandatory and values are given only as examples):
    /// { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2, "prefix-limit": 1 } ],
    ///                        "subnet": { "id": 1, "address-limit": 2, "prefix-limit": 1 } } } }
    ///
    /// @return a string describing a limit that is being exceeded, or an empty
    /// string if no limits are exceeded
    virtual std::string
    checkLimits6(isc::data::ConstElementPtr const& user_context) const override;

    /// @brief Checks if JSON support is enabled in the database.
    /// MySQL implementation.
    ///
    /// @return true if there is JSON support, false otherwise
    virtual bool isJsonSupported() const override;

    /// @brief Returns the class lease count for a given class and lease type.
    ///
    /// @param client_class client class for which the count is desired
    /// @param ltype type of lease for which the count is desired. Defaults to
    /// Lease::TYPE_V4.
    ///
    /// @return number of leases
    virtual size_t getClassLeaseCount(const ClientClass& client_class,
                                      const Lease::Type& ltype = Lease::TYPE_V4) const override;

    /// @brief Recount the leases per class for V4 leases.
    virtual void recountClassLeases4() override;

    /// @brief Recount the leases per class for V6 leases.
    virtual void recountClassLeases6() override;

    /// @brief Clears the class-lease count map.
    virtual void clearClassLeaseCounts() override;

    /// @brief Write V4 leases to a file.
    virtual void writeLeases4(const std::string& /*filename*/) override;

    /// @brief Write V6 leases to a file.
    virtual void writeLeases6(const std::string& /*filename*/) override;

    /// @brief Check Error and Throw Exception
    ///
    /// This method invokes @ref MySqlConnection::checkError.
    ///
    /// @param ctx Context
    /// @param status Status code: non-zero implies an error
    /// @param index Index of statement that caused the error
    /// @param what High-level description of the error
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    void checkError(MySqlLeaseContextPtr& ctx,
                    int status, StatementIndex index,
                    const char* what) const;

    /// The following queries are used to fulfill Bulk Lease Query
    /// queries. They rely on relay data contained in lease's
    /// user-context when the extended-store-info flag is enabled.

    /// @brief Returns existing IPv4 leases with a given relay-id.
    ///
    /// @param relay_id RAI Relay-ID sub-option value for relay_id of interest
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @param qry_start_time when not zero, only leases whose CLTT is greater than
    /// or equal to this value will be included
    /// @param qry_end_time when not zero, only leases whose CLTT is less than
    /// or equal to this value will be included
    ///
    /// @return collection of IPv4 leases
    virtual Lease4Collection
    getLeases4ByRelayId(const OptionBuffer& relay_id,
                        const asiolink::IOAddress& lower_bound_address,
                        const LeasePageSize& page_size,
                        const time_t& qry_start_time = 0,
                        const time_t& qry_end_time = 0) override;

    /// @brief Returns existing IPv4 leases with a given remote-id.
    ///
    /// @param remote_id RAI Remote-ID sub-option value for remote-id of interest
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @param qry_start_time when not zero, only leases whose CLTT is greater than
    /// or equal to this value will be included. Defaults to zero.
    /// @param qry_end_time when not zero, only leases whose CLTT is less than
    /// or equal to this value will be included. Defaults to zero.
    ///
    /// @return collection of IPv4 leases
    virtual Lease4Collection
    getLeases4ByRemoteId(const OptionBuffer& remote_id,
                         const asiolink::IOAddress& lower_bound_address,
                         const LeasePageSize& page_size,
                         const time_t& qry_start_time = 0,
                         const time_t& qry_end_time = 0) override;

    /// @brief Returns existing IPv6 leases with a given relay-id.
    ///
    /// @param relay_id DUID for relay_id of interest.
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByRelayId(const DUID& relay_id,
                        const asiolink::IOAddress& link_addr,
                        uint8_t link_len,
                        const asiolink::IOAddress& lower_bound_address,
                        const LeasePageSize& page_size) override;

    /// @brief Returns existing IPv6 leases with a given remote-id.
    ///
    /// @param remote_id remote-id option data of interest.
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByRemoteId(const OptionBuffer& remote_id,
                         const asiolink::IOAddress& link_addr,
                         uint8_t link_len,
                         const asiolink::IOAddress& lower_bound_address,
                         const LeasePageSize& page_size) override;

    /// @brief Returns existing IPv6 leases with on a given link.
    ///
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv4 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByLink(const asiolink::IOAddress& link_addr,
                     uint8_t link_len,
                     const asiolink::IOAddress& lower_bound_address,
                     const LeasePageSize& page_size) override;

    /// @brief Build extended info v6 tables.
    ///
    /// @param update Update extended info in database.
    /// @param current specify whether to use current (true) or staging
    /// (false) config.
    /// @return The number of updates in the database or 0.
    virtual size_t buildExtendedInfoTables6(bool update, bool current) override;

    /// @brief Context RAII allocator.
    class MySqlLeaseContextAlloc {
    public:

        /// @brief Constructor
        ///
        /// This constructor takes a context of the pool if one is available
        /// or creates a new one.
        ///
        /// @param mgr A parent instance
        MySqlLeaseContextAlloc(const MySqlLeaseMgr& mgr);

        /// @brief Destructor
        ///
        /// This destructor puts back the context in the pool.
        ~MySqlLeaseContextAlloc();

        /// @brief The context
        MySqlLeaseContextPtr ctx_;

    private:

        /// @brief The manager
        const MySqlLeaseMgr& mgr_;
    };

    /// @brief Context RAII allocator for lease tracking.
    ///
    /// This context should be used in the non-const calls that
    /// may trigger callbacks for lease tracking.
    class MySqlLeaseTrackingContextAlloc {
    public:

        /// @brief Constructor
        ///
        /// This constructor takes a context of the pool if one is available
        /// or creates a new one.
        ///
        /// @param mgr A parent instance
        /// @param lease allocated or deallocated lease instance.
        MySqlLeaseTrackingContextAlloc(MySqlLeaseMgr& mgr, const LeasePtr& lease);

        /// @brief Destructor
        ///
        /// This destructor puts back the context in the pool.
        ~MySqlLeaseTrackingContextAlloc();

        /// @brief The context
        MySqlLeaseContextPtr ctx_;

    private:

        /// @brief The manager
        MySqlLeaseMgr& mgr_;

        /// @brief Tracked lease instance.
        LeasePtr lease_;
    };

protected:

    /// Extended information / Bulk Lease Query shared interface.

    /// @brief Modifies the setting whether the lease extended info tables
    /// are enabled.
    ///
    /// Transient redefine to refuse the enable setting.
    /// @param enabled new setting.
    virtual void setExtendedInfoTablesEnabled(const bool enabled) override {
        if (enabled) {
            isc_throw(isc::NotImplemented,
                      "extended info tables are not yet supported by mysql");
        }
    }

    /// @brief Decode parameters to set whether the lease extended info tables
    /// are enabled.
    ///
    /// @note: common code in constructors.
    ///
    /// @param parameters The parameter map.
    virtual void setExtendedInfoTablesEnabled(const db::DatabaseConnection::ParameterMap& parameters) override;

    /// @brief Delete lease6 extended info from tables.
    ///
    /// @param addr The address of the lease.
    virtual void deleteExtendedInfo6(const isc::asiolink::IOAddress& addr) override;

    /// @brief Add lease6 extended info into by-relay-id table.
    ///
    /// @param lease_addr The address of the lease.
    /// @param relay_id The relay id from the relay header options.
    virtual void addRelayId6(const isc::asiolink::IOAddress& lease_addr,
                             const std::vector<uint8_t>& relay_id) override;

    /// @brief Add lease6 extended info into by-remote-id table.
    ///
    /// @param lease_addr The address of the lease.
    /// @param remote_id The remote id from the relay header options.
    virtual void addRemoteId6(const isc::asiolink::IOAddress& lease_addr,
                              const std::vector<uint8_t>& remote_id) override;

private:

    // Members

    /// @brief The parameters
    db::DatabaseConnection::ParameterMap parameters_;

    /// @brief The pool of contexts
    MySqlLeaseContextPoolPtr pool_;

    /// @brief Timer name used to register database reconnect timer.
    std::string timer_name_;
};

}  // namespace dhcp
}  // namespace isc

#endif // MYSQL_LEASE_MGR_H
