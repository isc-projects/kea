// Copyright (C) 2012-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_MGR_H
#define LEASE_MGR_H

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/db_exceptions.h>

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
///
/// Failover considerations:
/// There are no intermediate plans to implement DHCPv4 failover
/// (draft-ietf-dhc-failover-12.txt). Currently (Oct. 2012) the DHCPv6 failover
/// is being defined in DHC WG in IETF (draft-ietf-dhcpv6-failover-requirements,
/// draft-ietf-dhcpv6-failover-design), but the work is not advanced enough
/// for implementation plans yet. v4 failover requires additional parameters
/// to be kept with a lease. It is likely that v6 failover will require similar
/// fields. Such implementation will require database schema extension.
/// We have designed a way to expand/upgrade schemas during upgrades: a database
/// schema is versioned and sanity checks about required version will be done
/// upon start and/or upgrade. With this mechanism in place, we can add new
/// fields to the database. In particular we can use that capability to
/// introduce failover related fields.
///
/// However, there is another approach that can be reliably used to provide
/// failover, even without the actual failover protocol implemented. As the
/// first backend will use MySQL, we will be able to use Multi-Master capability
/// offered by MySQL and use two separatate Kea instances connecting to the
/// same database.
///
/// Nevertheless, we hope to have failover protocol eventually implemented in
/// the Kea.

namespace isc {
namespace dhcp {

/// @brief Used to map server data types with internal backend storage data
/// types.
enum ExchangeDataType {
    EXCHANGE_DATA_TYPE_NONE,
    EXCHANGE_DATA_TYPE_BOOL,
    EXCHANGE_DATA_TYPE_INT32,
    EXCHANGE_DATA_TYPE_INT64,
    EXCHANGE_DATA_TYPE_TIMESTAMP,
    EXCHANGE_DATA_TYPE_STRING,
    EXCHANGE_DATA_TYPE_BYTES
};

/// @brief Used to specify the direction of the data exchange between the
/// database and the server.
enum ExchangeDataTypeIO {
    EXCHANGE_DATA_TYPE_IO_IN,
    EXCHANGE_DATA_TYPE_IO_OUT,
    EXCHANGE_DATA_TYPE_IO_IN_OUT
};

/// @brief Used to map the column name with internal backend storage data types.
struct ExchangeColumnInfo {
    ExchangeColumnInfo () : name_(""), index_(0), type_io_(EXCHANGE_DATA_TYPE_IO_IN),
                            type_(EXCHANGE_DATA_TYPE_NONE) {};
    ExchangeColumnInfo (const char* name, const uint32_t index,
        const ExchangeDataTypeIO type_io, const ExchangeDataType type) :
        name_(name), index_(index), type_io_(type_io), type_(type) {};
    std::string name_;
    uint32_t index_;
    ExchangeDataTypeIO type_io_;
    ExchangeDataType type_;
};

typedef boost::shared_ptr<ExchangeColumnInfo> ExchangeColumnInfoPtr;

typedef boost::multi_index_container<
    // Container comprises elements of ExchangeColumnInfoPtr type.
    ExchangeColumnInfoPtr,
    // Here we start enumerating various indexes.
    boost::multi_index::indexed_by<
        // Sequenced index allows accessing elements in the same way as elements
        // in std::list.
        // Sequenced is an index #0.
        boost::multi_index::sequenced<>,
        // Start definition of index #1.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<
                ExchangeColumnInfo,
                std::string,
                &ExchangeColumnInfo::name_
             >
        >,
        // Start definition of index #2.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<
                ExchangeColumnInfo,
                uint32_t,
                &ExchangeColumnInfo::index_
            >
        >
    >
> ExchangeColumnInfoContainer;

/// Pointer to the ExchangeColumnInfoContainer object.
typedef boost::shared_ptr<ExchangeColumnInfoContainer> ExchangeColumnInfoContainerPtr;
/// Type of the index #1 - name.
typedef ExchangeColumnInfoContainer::nth_index<1>::type ExchangeColumnInfoContainerName;
/// Pair of iterators to represent the range of ExchangeColumnInfo having the
/// same name value. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<ExchangeColumnInfoContainerName::const_iterator,
                  ExchangeColumnInfoContainerName::const_iterator> ExchangeColumnInfoContainerNameRange;
/// Type of the index #2 - index.
typedef ExchangeColumnInfoContainer::nth_index<2>::type ExchangeColumnInfoContainerIndex;
/// Pair of iterators to represent the range of ExchangeColumnInfo having the
/// same index value. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<ExchangeColumnInfoContainerIndex::const_iterator,
                  ExchangeColumnInfoContainerIndex::const_iterator> ExchangeColumnInfoContainerIndexRange;

class SqlExchange {
public:
    SqlExchange () {};
    virtual ~SqlExchange() {};
    ExchangeColumnInfoContainer parameters_;   ///< Column names and types
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
/// upto date statistical lease data organized as rows of LeaseStatsRow
/// instances. The rows must be accessible in ascending order by subnet id.
class LeaseStatsQuery {
public:
    /// @brief Default constructor
    LeaseStatsQuery() {};

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
};

/// @brief Defines a pointer to an LeaseStatsQuery.
typedef boost::shared_ptr<LeaseStatsQuery> LeaseStatsQueryPtr;

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
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    virtual bool addLease(const isc::dhcp::Lease4Ptr& lease) = 0;

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
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

    /// @brief Deletes a lease.
    ///
    /// @param addr Address of the lease to be deleted. (This can be IPv4 or
    ///        IPv6.)
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease(const isc::asiolink::IOAddress& addr) = 0;

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
    /// adding to the approporate global statistic.
    void recountLeaseStats4();

    /// @brief Virtual method which creates and runs the IPv4 lease stats query
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with upto date IPv4 lease statistical data.  Each row of the
    /// result set is an LeaseStatRow which ordered ascending by subnet ID.
    ///
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery4();

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
    /// per subnet and adding to the approporate global statistic.
    void recountLeaseStats6();

    /// @brief Virtual method which creates and runs the IPv6 lease stats query
    ///
    /// LeaseMgr derivations implement this method such that it creates and
    /// returns an instance of an LeaseStatsQuery whose result set has been
    /// populated with upto date IPv6 lease statistical data.  Each row of the
    /// result set is an LeaseStatRow which ordered ascending by subnet ID.
    ///
    /// @return A populated LeaseStatsQuery
    virtual LeaseStatsQueryPtr startLeaseStatsQuery6();

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
    virtual std::pair<uint32_t, uint32_t> getVersion() const = 0;

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

    /// @todo: Add host management here
    /// As host reservation is outside of scope for 2012, support for hosts
    /// is currently postponed.
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // LEASE_MGR_H
