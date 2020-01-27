// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_MGR_H
#define LEASE_MGR_H

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <database/db_exceptions.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/hwaddr.h>
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
        subnet_id_(0), lease_type_(Lease::TYPE_NA),
        lease_state_(Lease::STATE_DEFAULT), state_count_(0) {
    }

    /// @brief Constructor
    ///
    /// Constructor which defaults the type to TYPE_NA.
    ///
    /// @param subnet_id The subnet id to which this data applies
    /// @param lease_state The lease state counted
    /// @param state_count The count of leases in the lease state
    LeaseStatsRow(const SubnetID& subnet_id, const uint32_t lease_state,
                  const int64_t state_count)
        : subnet_id_(subnet_id), lease_type_(Lease::TYPE_NA),
          lease_state_(lease_state), state_count_(state_count) {
    }

    /// @brief Constructor
    ///
    /// @param subnet_id The subnet id to which this data applies
    /// @param lease_type The lease type for this state count
    /// @param lease_state The lease state counted
    /// @param state_count The count of leases in the lease state
    LeaseStatsRow(const SubnetID& subnet_id, const Lease::Type& lease_type,
                  const uint32_t lease_state, const int64_t state_count)
        : subnet_id_(subnet_id), lease_type_(lease_type),
          lease_state_(lease_state), state_count_(state_count) {
    }

    /// @brief Less-than operator
    bool operator< (const LeaseStatsRow &rhs) const {
        if (subnet_id_ < rhs.subnet_id_) {
            return (true);
        }

        if (subnet_id_ == rhs.subnet_id_ &&
            lease_type_ < rhs.lease_type_) {
                return (true);
        }

        if (subnet_id_ == rhs.subnet_id_ &&
            lease_type_ == rhs.lease_type_ &&
            lease_state_ < rhs.lease_state_) {
                return (true);
        }

        return (false);
    }

    /// @brief The subnet ID to which this data applies
    SubnetID subnet_id_;
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
        SUBNET_RANGE
    } SelectMode;

    /// @brief Default constructor
    /// The query created will return statistics for all subnets
    LeaseStatsQuery();

    /// @brief Constructor to query for a single subnet's stats
    ///
    /// The query created will return statistics for a single subnet
    ///
    /// @param subnet_id id of the subnet for which stats are desired
    /// @throw BadValue if sunbet_id given is 0.
    LeaseStatsQuery(const SubnetID& subnet_id);

    /// @brief Constructor to query for the stats for a range of subnets
    ///
    /// The query created will return statistics for the inclusive range of
    /// subnets described by first and last sunbet IDs.
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
    LeaseMgr()
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

    /// @brief Returns existing IPv4 lease for a given client identifier,
    /// HW address and subnet identifier.
    ///
    /// @todo Consider whether this function is needed or not. In the basic
    /// DHCPv4 server implementation it is not used by the allocation engine.
    ///
    /// @param client_id A client identifier.
    /// @param hwaddr Hardware address.
    /// @param subnet_id A subnet identifier.
    ///
    /// @return A pointer to the lease or NULL if the lease is not found.
    virtual Lease4Ptr getLease4(const ClientId& client_id, const HWAddr& hwaddr,
                                SubnetID subnet_id) const = 0;

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
    /// - declined-reclaimed-addresses (reset to zero)
    /// global:
    /// - declined-addresses
    /// - declined-reclaimed-addresses (reset to zero)
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
    /// - assigned-addresses
    /// - declined-addresses
    /// - declined-reclaimed-addresses (reset to zero)
    /// - assigned-pds
    /// global:
    /// - declined-addresses
    /// - declined-reclaimed-addresses (reset to zero)
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

};

}  // namespace dhcp
}  // namespace isc

#endif // LEASE_MGR_H
