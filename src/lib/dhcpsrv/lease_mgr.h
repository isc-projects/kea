// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_MGR_H
#define LEASE_MGR_H

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <cc/data.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfg_consistency.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

/// @file lease_mgr.h
/// @brief An abstract API for lease database
///
/// This file contains declarations of Lease4, Lease6 and LeaseMgr classes.
/// They are essential components of the interface to any database backend.
/// Each concrete database backend (e.g. MySQL) will define a class derived
/// from LeaseMgr class.
namespace isc {
namespace dhcp {

/// @brief Pair containing major and minor versions
typedef std::pair<uint32_t, uint32_t> VersionPair;

/// @brief Wraps value holding size of the page with leases.
class LeasePageSize {
public:

    /// @brief Constructor.
    ///
    /// @param page_size page size value.
    /// @throw OutOfRange if page size is 0 or greater than uint32_t numeric
    /// limit.
    explicit LeasePageSize(const size_t page_size);

    const size_t page_size_; ///< Holds page size.
};

/// @brief Contains a single row of lease statistical data
///
/// The contents of the row consist of a subnet ID, a lease
/// type, a lease state, and the number of leases in that state
/// for that type for that subnet ID.
struct LeaseStatsRow {
    /// @brief Default constructor
    LeaseStatsRow() :
        subnet_id_(0), pool_id_(0), lease_type_(Lease::TYPE_NA),
        lease_state_(Lease::STATE_DEFAULT), state_count_(0) {
    }

    /// @brief Constructor
    ///
    /// Constructor which defaults the type to TYPE_NA.
    ///
    /// @param subnet_id The subnet id to which this data applies
    /// @param lease_state The lease state counted
    /// @param state_count The count of leases in the lease state
    /// @param pool_id The pool id to which this data applies or 0 if it is not
    /// used
    LeaseStatsRow(const SubnetID& subnet_id, const uint32_t lease_state,
                  const int64_t state_count, uint32_t pool_id = 0)
        : subnet_id_(subnet_id), pool_id_(pool_id), lease_type_(Lease::TYPE_NA),
          lease_state_(lease_state), state_count_(state_count) {
    }

    /// @brief Constructor
    ///
    /// @param subnet_id The subnet id to which this data applies
    /// @param lease_type The lease type for this state count
    /// @param lease_state The lease state counted
    /// @param state_count The count of leases in the lease state
    /// @param pool_id The pool id to which this data applies or 0 if it is not
    /// used
    LeaseStatsRow(const SubnetID& subnet_id, const Lease::Type& lease_type,
                  const uint32_t lease_state, const int64_t state_count,
                  uint32_t pool_id = 0)
        : subnet_id_(subnet_id), pool_id_(pool_id), lease_type_(lease_type),
          lease_state_(lease_state), state_count_(state_count) {
    }

    /// @brief Less-than operator
    bool operator<(const LeaseStatsRow &rhs) const {
        if (subnet_id_ < rhs.subnet_id_) {
            return (true);
        }

        if (subnet_id_ == rhs.subnet_id_ &&
            pool_id_ < rhs.pool_id_) {
            return (true);
        }

        if (subnet_id_ == rhs.subnet_id_ &&
            pool_id_ == rhs.pool_id_ &&
            lease_type_ < rhs.lease_type_) {
            return (true);
        }

        if (subnet_id_ == rhs.subnet_id_ &&
            pool_id_ == rhs.pool_id_ &&
            lease_type_ == rhs.lease_type_ &&
            lease_state_ < rhs.lease_state_) {
            return (true);
        }

        return (false);
    }

    /// @brief The subnet ID to which this data applies
    SubnetID subnet_id_;

    /// @brief The pool ID to which this data applies
    uint32_t pool_id_;

    /// @brief The lease_type to which the count applies
    Lease::Type lease_type_;

    /// @brief The lease_state to which the count applies
    uint32_t lease_state_;

    /// @brief state_count The count of leases in the lease state
    int64_t state_count_;
};

/// @brief Base class for fulfilling a statistical lease data query
///
/// LeaseMgr derivations implement this class such that it provides
/// up to date statistical lease data organized as rows of LeaseStatsRow
/// instances. The rows must be accessible in ascending order by subnet id.
class LeaseStatsQuery {
public:
    /// @brief Defines the types of selection criteria supported
    typedef enum {
        ALL_SUBNETS,
        SINGLE_SUBNET,
        SUBNET_RANGE,
        ALL_SUBNET_POOLS
    } SelectMode;

    /// @brief Constructor to query statistics for all subnets
    ///
    /// The query created will return statistics for all subnets
    ///
    /// @param select_mode The selection criteria which is either ALL_SUBNETS or
    /// ALL_SUBNET_POOLS
    LeaseStatsQuery(const SelectMode& select_mode = ALL_SUBNETS);

    /// @brief Constructor to query for a single subnet's stats
    ///
    /// The query created will return statistics for a single subnet
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @throw BadValue if subnet_id given is 0.
    LeaseStatsQuery(const SubnetID& subnet_id);

    /// @brief Constructor to query for the stats for a range of subnets
    ///
    /// The query created will return statistics for the inclusive range of
    /// subnets described by first and last subnet IDs.
    ///
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    /// @throw BadValue if either value given is 0 or if last <= first.
    LeaseStatsQuery(const SubnetID& first_subnet_id, const SubnetID& last_subnet_id);

    /// @brief virtual destructor
    virtual ~LeaseStatsQuery() {};

    /// @brief Executes the query
    ///
    /// This method should conduct whatever steps are required to
    /// calculate the lease statistical data by examining the
    /// lease data and making that results available row by row.
    virtual void start() {};

    /// @brief Fetches the next row of data
    ///
    /// @param[out] row Storage into which the row is fetched
    ///
    /// @return True if a row was fetched, false if there are no
    /// more rows.
    virtual bool getNextRow(LeaseStatsRow& row);

    /// @brief Returns the value of first subnet ID specified (or zero)
    SubnetID getFirstSubnetID() const {
        return (first_subnet_id_);
    };

    /// @brief Returns the value of last subnet ID specified (or zero)
    SubnetID getLastSubnetID() const {
        return (last_subnet_id_);
    };

    /// @brief Returns the selection criteria mode
    /// The value returned is based upon the constructor variant used
    /// and it indicates which query variant will be executed.
    SelectMode getSelectMode() const {
        return (select_mode_);
    };

protected:
    /// @brief First (or only) subnet_id in the selection criteria
    SubnetID first_subnet_id_;

    /// @brief Last subnet_id in the selection criteria when a range is given
    SubnetID last_subnet_id_;

private:
    /// @brief Indicates the type of selection criteria specified
    SelectMode select_mode_;
};

/// @brief Defines a pointer to a LeaseStatsQuery.
typedef boost::shared_ptr<LeaseStatsQuery> LeaseStatsQueryPtr;

/// @brief Defines a pointer to a LeaseStatsRow.
typedef boost::shared_ptr<LeaseStatsRow> LeaseStatsRowPtr;

/// @brief Abstract Lease Manager
///
/// This is an abstract API for lease database backends. It provides unified
/// interface to all backends. As this is an abstract class, it should not
/// be used directly, but rather specialized derived class should be used
/// instead.
///
/// This class throws no exceptions.  However, methods in concrete
/// implementations of this class may throw exceptions: see the documentation
/// of those classes for details.
class LeaseMgr {
public:
    /// @brief Constructor
    ///
    LeaseMgr() : extended_info_tables_enabled_(false)
    {}

    /// @brief Destructor
    virtual ~LeaseMgr()
    {}

    /// @brief Class method to return extended version info
    /// This class method must be redeclared and redefined in derived classes
    static std::string getDBVersion();

    /// @brief Adds an IPv4 lease.
    ///
    /// The lease may be modified due to sanity checks setting (see
    /// LeaseSanityChecks in CfgConsistency) before being inserted. For
    /// performance reasons, the sanity checks do not make a copy, but rather
    /// modify lease in place if needed.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there or failed sanity checks)
    virtual bool addLease(const Lease4Ptr& lease) = 0;

    /// @brief Adds an IPv6 lease.
    ///
    /// The lease may be modified due to sanity checks setting (see
    /// LeaseSanityChecks in CfgConsistency) before being inserted. For
    /// performance reasons, the sanity checks do not make a copy, but rather
    /// modify lease in place if needed.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there or failed sanity checks)
    virtual bool addLease(const Lease6Ptr& lease) = 0;

    /// @brief Returns an IPv4 lease for specified IPv4 address
    ///
    /// This method return a lease that is associated with a given address.
    /// For other query types (by hardware addr, by client-id) there can be
    /// several leases in different subnets (e.g. for mobile clients that
    /// got address in different subnets). However, for a single address
    /// there can be only one lease, so this method returns a pointer to
    /// a single lease, not a container of leases.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr) const = 0;

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
    virtual Lease4Collection getLease4(const isc::dhcp::HWAddr& hwaddr) const = 0;

    /// @brief Returns existing IPv4 leases for specified hardware address
    ///        and a subnet
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method will either return a single lease or NULL.
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::dhcp::HWAddr& hwaddr,
                                SubnetID subnet_id) const = 0;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param clientid client identifier
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const ClientId& clientid) const = 0;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given client-id in a single
    /// pool, so this method will either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const = 0;

    /// @brief Returns all IPv4 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(SubnetID subnet_id) const = 0;

    /// @brief Returns all IPv4 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4(const std::string& hostname) const = 0;

    /// @brief Returns all IPv4 leases.
    ///
    /// @return Lease collection (may be empty if no IPv4 lease found).
    virtual Lease4Collection getLeases4() const = 0;

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
               const LeasePageSize& page_size) const = 0;

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
    virtual Lease6Ptr getLease6(Lease::Type type,
                                const isc::asiolink::IOAddress& addr) const = 0;

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
    /// @return Lease collection (may be empty if no lease is found)
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
                                        uint32_t iaid) const = 0;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// There may be more than one address, temp. address or prefix
    /// for specified duid/iaid/subnet-id tuple.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id subnet id of the subnet the lease belongs to
    ///
    /// @return Lease collection (may be empty if no lease is found)
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
                                        uint32_t iaid, SubnetID subnet_id) const = 0;

    /// @brief returns zero or one IPv6 lease for a given duid+iaid+subnet_id
    ///
    /// This function is mostly intended to be used in unit-tests during the
    /// transition from single to multi address per IA. It may also be used
    /// in other cases where at most one lease is expected in the database.
    ///
    /// It is a wrapper around getLeases6(), which returns a collection of
    /// leases. That collection can be converted into a single pointer if
    /// there are no leases (NULL pointer) or one lease (use that single lease).
    /// If there are more leases in the collection, the function will
    /// throw MultipleRecords exception.
    ///
    /// Note: This method is not virtual on purpose. It is common for all
    /// backends.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id subnet id of the subnet the lease belongs to
    ///
    /// @throw MultipleRecords if there is more than one lease matching
    ///
    /// @return Lease pointer (or NULL if none is found)
    Lease6Ptr getLease6(Lease::Type type, const DUID& duid,
                        uint32_t iaid, SubnetID subnet_id) const;

    /// @brief Returns all IPv6 leases for the particular subnet identifier.
    ///
    /// @param subnet_id subnet identifier.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(SubnetID subnet_id) const = 0;

    /// @brief Returns all IPv6 leases for the particular hostname.
    ///
    /// @param hostname hostname in lower case.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6(const std::string& hostname) const = 0;

    /// @brief Returns all IPv6 leases.
    ///
    /// @return Lease collection (may be empty if no IPv6 lease found).
    virtual Lease6Collection getLeases6() const = 0;

    /// @brief Returns collection of leases for matching DUID
    ///
    /// @return Lease collection
    /// (may be empty if no IPv6 lease found for the DUID).
    virtual Lease6Collection getLeases6(const DUID& duid) const = 0;

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
               const LeasePageSize& page_size) const = 0;

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
                                   const size_t max_leases) const = 0;

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
                                   const size_t max_leases) const = 0;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(const Lease4Ptr& lease4) = 0;

    /// @brief Updates IPv6 lease.
    ///
    /// @param lease6 The lease to be updated.
    virtual void updateLease6(const Lease6Ptr& lease6) = 0;

    /// @brief Deletes an IPv4 lease.
    ///
    /// @param lease IPv4 lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual bool deleteLease(const Lease4Ptr& lease) = 0;

    /// @brief Deletes an IPv6 lease.
    ///
    /// @param lease IPv6 lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    virtual bool deleteLease(const Lease6Ptr& lease) = 0;

    /// @brief Deletes all expired and reclaimed DHCPv4 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases4(const uint32_t secs) = 0;

    /// @brief Deletes all expired and reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases6(const uint32_t secs) = 0;

    /// @brief Recalculates per-subnet and global stats for IPv4 leases
    ///
    /// This method recalculates the following statistics:
    /// per-subnet:
    /// - assigned-addresses
    /// - declined-addresses
    /// global:
    /// - declined-addresses
    ///
    /// It invokes the virtual method, startLeaseStatsQuery4(), which
    /// returns an instance of an LeaseStatsQuery.  The query
    /// query contains a "result set"  where each row is an LeaseStatRow
    /// that contains a subnet id, a lease type (currently always TYPE_NA),
    /// a lease state, and the number of leases of that type, in that state
    /// and is ordered by subnet id.  The method iterates over the
    /// result set rows, setting the appropriate statistic per subnet and
    /// adding to the appropriate global statistic.
    void recountLeaseStats4();

    /// @brief Creates and runs the IPv4 lease stats query for all subnets
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv4 lease statistical data for all subnets.
    /// Each row of the result set is an LeaseStatRow which ordered ascending
    /// by subnet ID.
    ///
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery4();

    /// @brief Creates and runs the IPv4 lease stats query for all subnets and
    /// pools
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv4 lease statistical data for all subnets
    /// and pools.
    /// Each row of the result set is an LeaseStatRow which ordered ascending
    /// by subnet ID and pool ID.
    ///
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startPoolLeaseStatsQuery4();

    /// @brief Creates and runs the IPv4 lease stats query for a single subnet
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv4 lease statistical data for a single
    /// subnet.  Each row of the result set is an LeaseStatRow.
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetLeaseStatsQuery4(const SubnetID& subnet_id);

    /// @brief Creates and runs the IPv4 lease stats query for a single subnet
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv4 lease statistical data for an inclusive
    /// range of subnets. Each row of the result set is an LeaseStatRow which
    /// ordered ascending by subnet ID.
    ///
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetRangeLeaseStatsQuery4(const SubnetID& first_subnet_id,
                                                                const SubnetID& last_subnet_id);

    /// @brief Recalculates per-subnet and global stats for IPv6 leases
    ///
    /// This method recalculates the following statistics:
    /// per-subnet:
    /// - assigned-nas
    /// - declined-addresses
    /// - assigned-pds
    /// global:
    /// - assigned-nas
    /// - declined-addresses
    /// - assigned-pds
    ///
    /// It invokes the virtual method, startLeaseStatsQuery6(), which
    /// returns an instance of an LeaseStatsQuery.  The query contains
    /// a "result set" where each row is an LeaseStatRow that contains
    /// a subnet id, a lease type, a lease state, and the number of leases
    /// of that type, in that state and is ordered by subnet id. The method
    /// iterates over the result set rows, setting the appropriate statistic
    /// per subnet and adding to the appropriate global statistic.
    void recountLeaseStats6();

    /// @brief Creates and runs the IPv6 lease stats query for all subnets
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv6 lease statistical data for all subnets.
    /// Each row of the result set is an LeaseStatRow which ordered ascending
    /// by subnet ID.
    ///
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery6();

    /// @brief Creates and runs the IPv6 lease stats query for all subnets and
    /// pools
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv6 lease statistical data for all subnets
    /// and pools.
    /// Each row of the result set is an LeaseStatRow which ordered ascending
    /// by subnet ID and pool ID.
    ///
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startPoolLeaseStatsQuery6();

    /// @brief Creates and runs the IPv6 lease stats query for a single subnet
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv6 lease statistical data for a single
    /// subnet.  Each row of the result set is an LeaseStatRow.
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetLeaseStatsQuery6(const SubnetID& subnet_id);

    /// @brief Creates and runs the IPv6 lease stats query for a single subnet
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with up to date IPv6 lease statistical data for an inclusive
    /// range of subnets. Each row of the result set is an LeaseStatRow which
    /// ordered ascending by subnet ID.
    ///
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startSubnetRangeLeaseStatsQuery6(const SubnetID& first_subnet_id,
                                                                const SubnetID& last_subnet_id);

    /// @brief Virtual method which removes specified leases.
    ///
    /// This rather dangerous method is able to remove all leases from specified
    /// subnet.
    ///
    /// @param subnet_id identifier of the subnet (or 0 for all subnets)
    /// @return number of leases removed.
    virtual size_t wipeLeases4(const SubnetID& subnet_id) = 0;

    /// @brief Virtual method which removes specified leases.
    ///
    /// This rather dangerous method is able to remove all leases from specified
    /// subnet.
    ///
    /// @param subnet_id identifier of the subnet (or 0 for all subnets)
    /// @return number of leases removed.
    virtual size_t wipeLeases6(const SubnetID& subnet_id) = 0;

    /// @brief Checks if the IPv4 lease limits set in the given user context are exceeded.
    /// Abstract method.
    ///
    /// @param user_context all or part of the lease's user context which, for the intents and
    /// purposes of lease limiting should have the following format
    /// (not all nodes are mandatory and values are given only as examples):
    /// { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2 } ],
    ///                        "subnet": { "id": 1, "address-limit": 2 } } } }
    ///
    /// @return a string describing a limit that is being exceeded, or an empty
    /// string if no limits are exceeded
    virtual std::string checkLimits4(isc::data::ConstElementPtr const& user_context) const = 0;

    /// @brief Checks if the IPv6 lease limits set in the given user context are exceeded.
    /// Abstract method.
    ///
    /// @param user_context all or part of the lease's user context which, for the intents and
    /// purposes of lease limiting should have the following format
    /// (not all nodes are mandatory and values are given only as examples):
    /// { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2, "prefix-limit": 1 } ],
    ///                        "subnet": { "id": 1, "address-limit": 2, "prefix-limit": 1 } } } }
    ///
    /// @return a string describing a limit that is being exceeded, or an empty
    /// string if no limits are exceeded
    virtual std::string checkLimits6(isc::data::ConstElementPtr const& user_context) const = 0;

    /// @brief Checks if JSON support is enabled in the database.
    /// Abstract method.
    ///
    /// @return true if there is JSON support, false otherwise
    virtual bool isJsonSupported() const = 0;

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const = 0;

    /// @brief Returns backend name.
    ///
    /// If the backend is a database, this is the name of the database or the
    /// file.  Otherwise it is just the same as the type.
    ///
    /// @return Name of the backend.
    virtual std::string getName() const = 0;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const = 0;

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

    /// @brief Sets IO service to be used by the Lease Manager.
    ///
    /// @param io_service IOService object, used for all ASIO operations.
    static void setIOService(const isc::asiolink::IOServicePtr& io_service) {
        io_service_ = io_service;
    }

    /// @brief Returns pointer to the IO service.
    static isc::asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

    // -- The following are memfile only, but defined in the base LeaseMgr for convenience. --

    /// @brief Returns the class lease count for a given class and lease type.
    ///
    /// @param client_class client class for which the count is desired
    /// @param ltype type of lease for which the count is desired. Defaults to
    /// Lease::TYPE_V4.
    ///
    /// @return number of leases
    virtual size_t getClassLeaseCount(const ClientClass& client_class,
                                      const Lease::Type& ltype = Lease::TYPE_V4) const = 0;

    /// @brief Recount the leases per class for V4 leases.
    virtual void recountClassLeases4() = 0;

    /// @brief Recount the leases per class for V6 leases.
    virtual void recountClassLeases6() = 0;

    /// @brief Clears the class-lease count map.
    virtual void clearClassLeaseCounts() = 0;

    /// The following queries are used to fulfill Bulk Lease Query
    /// queries. They rely on relay data contained in lease's
    /// user-context when the extended-store-info flag is enabled.

    /// @brief Upgrade a V4 lease user context to the new extended info entry.
    ///
    /// In details:
    ///  - perform sanity checks according to check level.
    ///  - change the "ISC" / "relay-agent-info" to a map.
    ///  - move the "relay-agent-info" string to the "sub-options" entry of
    ///    the map.
    ///  - decode remote-id and relay-id from the RAI option content and
    ///    add the raw value in hexadecimal in "remote-id" and/or "relay-id"
    ///    entries of the map.
    ///
    /// @param lease Pointer to the lease to be updated.
    /// @param check Sanity/consistency check level.
    /// @return True if the lease user context was updated, false otherwise.
    static bool
    upgradeLease4ExtendedInfo(const Lease4Ptr& lease,
                              CfgConsistency::ExtendedInfoSanity check =
                              CfgConsistency::EXTENDED_INFO_CHECK_FIX);

    /// @brief Upgrade a V6 lease user context to the new extended info entry.
    ///
    /// In details:
    ///  - perform sanity checks according to check level.
    ///  - change the "ISC" / "relays" list entry to "relay-info".
    ///  - decode remote-id and relay-id from each relay options and
    ///    add the raw value in hexadecimal in "remote-id" and/or "relay-id"
    ///    in the relay item of the list.
    ///
    /// @param lease Pointer to the lease to be updated.
    /// @param check Sanity/consistency check level.
    /// @return True if the lease user context was updated, false otherwise.
    static bool
    upgradeLease6ExtendedInfo(const Lease6Ptr& lease,
                              CfgConsistency::ExtendedInfoSanity check =
                              CfgConsistency::EXTENDED_INFO_CHECK_FIX);

    /// @brief Extract relay and remote identifiers from the extended info.
    ///
    /// @param lease Pointer to the lease to be updated.
    /// @param ignore_errors When true (the default) ignore errors,
    /// when false throw an exception.
    static void extractLease4ExtendedInfo(const Lease4Ptr& lease,
                                          bool ignore_errors = true);

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
                        const time_t& qry_end_time = 0) = 0;

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
                         const time_t& qry_end_time = 0) = 0;

    /// @brief Returns existing IPv6 leases with a given relay-id.
    ///
    /// @param relay_id DUID for relay_id of interest.
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv6 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByRelayId(const DUID& relay_id,
                        const asiolink::IOAddress& link_addr,
                        uint8_t link_len,
                        const asiolink::IOAddress& lower_bound_address,
                        const LeasePageSize& page_size) = 0;

    /// @brief Returns existing IPv6 leases with a given remote-id.
    ///
    /// @param remote_id remote-id option data of interest.
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv6 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByRemoteId(const OptionBuffer& remote_id,
                         const asiolink::IOAddress& link_addr,
                         uint8_t link_len,
                         const asiolink::IOAddress& lower_bound_address,
                         const LeasePageSize& page_size) = 0;

    /// @brief Returns existing IPv6 leases with on a given link.
    ///
    /// @param link_addr limit results to leases on this link (prefix).
    /// @param link_len limit results to leases on this link (length).
    /// @param lower_bound_address IPv6 address used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection
    getLeases6ByLink(const asiolink::IOAddress& link_addr,
                     uint8_t link_len,
                     const asiolink::IOAddress& lower_bound_address,
                     const LeasePageSize& page_size) = 0;

    /// @brief Write V4 leases to a file.
    ///
    /// @param filename File name to write leases.
    virtual void writeLeases4(const std::string& filename) = 0;

    /// @brief Write V6 leases to a file.
    ///
    /// @param filename File name to write leases.
    virtual void writeLeases6(const std::string& filename) = 0;

    /// @brief Upgrade extended info (v4).
    ///
    /// On SQL backends for all leases with a not null user context.
    ///  - sanitize the user context
    ///  - update relay and remote ids
    ///  - when the lease was modified update it in the database
    /// On memfile backend a similar action is done when the database is
    /// loaded from the file. This function implements the new BLQ hook
    /// command named "extended-info4-upgrade".
    ///
    /// @param page_size The page size used for retrieval.
    /// @return The number of updates in the database.
    virtual size_t upgradeExtendedInfo4(const LeasePageSize& page_size) = 0;

    /// @brief Returns the setting indicating if lease extended info tables
    /// are enabled.
    ///
    /// @return true if lease extended info tables are enabled or false
    /// if they are disabled.
    bool getExtendedInfoTablesEnabled() const {
        return (extended_info_tables_enabled_);
    }

    /// @brief Build extended info v6 tables.
    ///
    /// @param update Update extended info in database.
    /// @param current specify whether to use current (true) or staging
    /// (false) config.
    /// @return The number of updates in the database or 0.
    virtual size_t buildExtendedInfoTables6(bool update, bool current) = 0;

protected:

    /// Extended information / Bulk Lease Query shared interface.

    /// @brief Modifies the setting whether the lease extended info tables
    /// are enabled.
    ///
    /// @note This method is virtual so backend doing specific action
    /// on value changes can intercept it by redefining it.
    ///
    /// @param enabled new setting.
    virtual void setExtendedInfoTablesEnabled(const bool enabled) {
        extended_info_tables_enabled_ = enabled;
    }

    /// @brief Decode parameters to set whether the lease extended info tables
    /// are enabled.
    ///
    /// @note: common code in constructors.
    ///
    /// @param parameters The parameter map.
    virtual void setExtendedInfoTablesEnabled(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Extract extended info from a lease6 and add it into tables.
    ///
    /// @param lease IPv6 lease to process.
    /// @return true if something was added, false otherwise.
    virtual bool addExtendedInfo6(const Lease6Ptr& lease);

    /// @brief Delete lease6 extended info from tables.
    ///
    /// @param addr The address of the lease.
    virtual void deleteExtendedInfo6(const isc::asiolink::IOAddress& addr) = 0;

    /// @brief Add lease6 extended info into by-relay-id table.
    ///
    /// @param lease_addr The address of the lease.
    /// @param relay_id The relay id from the relay header options.
    virtual void addRelayId6(const isc::asiolink::IOAddress& lease_addr,
                             const std::vector<uint8_t>& relay_id) = 0;

    /// @brief Add lease6 extended info into by-remote-id table.
    ///
    /// @param lease_addr The address of the lease.
    /// @param remote_id The remote id from the relay header options.
    virtual void addRemoteId6(const isc::asiolink::IOAddress& lease_addr,
                              const std::vector<uint8_t>& remote_id) = 0;

private:
    /// The IOService object, used for all ASIO operations.
    static isc::asiolink::IOServicePtr io_service_;

    /// @brief Holds the setting whether the lease extended info tables
    /// are enabled or disabled. The default is disabled.
    bool extended_info_tables_enabled_;
};

}  // namespace dhcp
}  // namespace isc

#endif // LEASE_MGR_H
