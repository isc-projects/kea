// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef LEASE_MGR_H
#define LEASE_MGR_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcpsrv/subnet.h>
#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>

/// @file dhcp/lease_mgr.h
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
/// draft-ietf-dhcpv6-dailover-design), but the work is not advanced enough
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

#include <iostream>

namespace isc {
namespace dhcp {

/// @brief Exception thrown if name of database is not specified
class NoDatabaseName : public Exception {
public:
    NoDatabaseName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception thrown on failure to open database
class DbOpenError : public Exception {
public:
    DbOpenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception thrown on failure to execute a database function
class DbOperationError : public Exception {
public:
    DbOperationError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Multiple lease records found where one expected
class MultipleRecords : public Exception {
public:
    MultipleRecords(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Attempt to update lease that was not there
class NoSuchLease : public Exception {
public:
    NoSuchLease(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Structure that holds a lease for IPv4 address
///
/// For performance reasons it is a simple structure, not a class. If we chose
/// make it a class, all fields would have to made private and getters/setters
/// would be required. As this is a critical part of the code that will be used
/// extensively, direct access is warranted.
struct Lease4 {

    /// @brief Constructor
    ///
    /// @param addr IPv4 address as unsigned 32-bit integer in network byte
    ///        order.
    /// @param hwaddr Hardware address buffer
    /// @param hwaddr_len Length of hardware address buffer
    /// @param clientid Client identification buffer
    /// @param clientid_len Length of client identification buffer
    /// @param valid_lft Lifetime of the lease
    /// @param cltt Client last transmission time
    /// @param subnet_id Subnet identification
    Lease4(uint32_t addr, const uint8_t* hwaddr, size_t hwaddr_len,
           const uint8_t* clientid, size_t clientid_len, uint32_t valid_lft,
           time_t cltt, uint32_t subnet_id)
        : addr_(addr), ext_(0), hwaddr_(hwaddr, hwaddr + hwaddr_len),
          client_id_(new ClientId(clientid, clientid_len)), t1_(0), t2_(0),
          valid_lft_(valid_lft), cltt_(cltt), subnet_id_(subnet_id),
          fixed_(false), hostname_(), fqdn_fwd_(false), fqdn_rev_(false),
          comments_()
    {}

    /// @brief Default Constructor
    ///
    /// Initialize fields that don't have a default constructor.
    Lease4() : addr_(0) {}


    /// IPv4 address
    isc::asiolink::IOAddress addr_;

    /// @brief Address extension
    ///
    /// It is envisaged that in some cases IPv4 address will be accompanied
    /// with some additional data. One example of such use are Address + Port
    /// solutions (or Port-restricted Addresses), where several clients may get
    /// the same address, but different port ranges. This feature is not
    /// expected to be widely used.  Under normal circumstances, the value
    /// should be 0.
    uint32_t ext_;

    /// @brief Hardware address
    std::vector<uint8_t> hwaddr_;

    /// @brief Client identifier
    ///
    /// @todo Should this be a pointer to a client ID or the ID itself?
    ///       Compare with the DUID in the Lease6 structure.
    boost::shared_ptr<ClientId> client_id_;

    /// @brief Renewal timer
    ///
    /// Specifies renewal time. Although technically it is a property of the
    /// IA container and not the address itself, since our data model does not
    /// define a separate IA entity, we are keeping it in the lease. In the
    /// case of multiple addresses/prefixes for the same IA, each must have
    /// consistent T1 and T2 values. This is specified in seconds since cltt.
    uint32_t t1_;

    /// @brief Rebinding timer
    ///
    /// Specifies rebinding time. Although technically it is a property of the
    /// IA container and not the address itself, since our data model does not
    /// define a separate IA entity, we are keeping it in the lease. In the
    /// case of multiple addresses/prefixes for the same IA, each must have
    /// consistent T1 and T2 values. This is pecified in seconds since cltt.
    uint32_t t2_;

    /// @brief Ralid lifetime
    ///
    /// Expressed as number of seconds since cltt.
    uint32_t valid_lft_;

    /// @brief Client last transmission time
    ///
    /// Specifies a timestamp giving the time when the last transmission from a
    /// client was received.
    time_t cltt_;

    /// @brief Subnet identifier
    ///
    /// Specifies the identification of the subnet to which the lease belongs.
    SubnetID subnet_id_;

    /// @brief Fixed lease?
    ///
    /// Fixed leases are kept after they are released/expired.
    bool fixed_;

    /// @brief Client hostname
    ///
    /// This field may be empty
    std::string hostname_;

    /// @brief Forward zone updated?
    ///
    /// Set true if the DNS AAAA record for this lease has been updated.
    bool fqdn_fwd_;

    /// @brief Reverse zone updated?
    ///
    /// Set true if the DNS PTR record for this lease has been updated.
    bool fqdn_rev_;

    /// @brief Lease comments
    ///
    /// Currently not used. It may be used for keeping comments made by the
    /// system administrator.
    std::string comments_;

    /// @todo: Add DHCPv4 failover related fields here
};

/// @brief Pointer to a Lease4 structure.
typedef boost::shared_ptr<Lease4> Lease4Ptr;

/// @brief A collection of IPv4 leases.
typedef std::vector<Lease4Ptr> Lease4Collection;



/// @brief Structure that holds a lease for IPv6 address and/or prefix
///
/// For performance reasons it is a simple structure, not a class. If we chose
/// make it a class, all fields would have to made private and getters/setters
/// would be required. As this is a critical part of the code that will be used
struct Lease6 {

    /// @brief Type of lease contents
    typedef enum {
        LEASE_IA_NA, /// the lease contains non-temporary IPv6 address
        LEASE_IA_TA, /// the lease contains temporary IPv6 address
        LEASE_IA_PD  /// the lease contains IPv6 prefix (for prefix delegation)
    } LeaseType;

    /// @brief Constructor
    Lease6(LeaseType type, const isc::asiolink::IOAddress& addr, DuidPtr duid,
           uint32_t iaid, uint32_t preferred, uint32_t valid, uint32_t t1,
           uint32_t t2, SubnetID subnet_id, uint8_t prefixlen_ = 0);

    /// @brief IPv6 address
    isc::asiolink::IOAddress addr_;

    /// @brief Lease type
    ///
    /// One of normal address, temporary address, or prefix.
    LeaseType type_;

    /// @brief IPv6 prefix length
    ///
    /// This is used only for prefix delegations and is ignored otherwise.
    uint8_t prefixlen_;

    /// @brief Identity Association Identifier (IAID)
    ///
    /// DHCPv6 stores all addresses and prefixes in IA containers (IA_NA,
    /// IA_TA, IA_PD). Most containers may appear more than once in a message.
    /// To differentiate between them, the IAID field is present
    uint32_t iaid_;

    /// @brief Client identifier
    boost::shared_ptr<DUID> duid_;

    /// @brief preferred lifetime
    ///
    /// This parameter specifies the preferred lifetime since the lease was
    /// assigned or renewed (cltt), expressed in seconds.
    uint32_t preferred_lft_;

    /// @brief valid lifetime
    ///
    /// This parameter specifies the valid lifetime since the lease waa
    /// assigned/renewed (cltt), expressed in seconds.
    uint32_t valid_lft_;

    /// @brief T1 timer
    ///
    /// Specifies renewal time. Although technically it is a property of the
    /// IA container and not the address itself, since our data model does not
    /// define a separate IA entity, we are keeping it in the lease. In the
    /// case of multiple addresses/prefixes for the same IA, each must have
    /// consistent T1 and T2 values. This is specified in seconds since cltt.
    /// The value will also be useful for failover to calculate the next
    /// expected client transmission time.
    uint32_t t1_;

    /// @brief T2 timer
    ///
    /// Specifies rebinding time. Although technically it is a property of the
    /// IA container and not the address itself, since our data model does not
    /// define a separate IA entity, we are keeping it in the lease. In the
    /// case of multiple addresses/prefixes for the same IA, each must have
    /// consistent T1 and T2 values. This is specified in seconds since cltt.
    uint32_t t2_;

    /// @brief Client last transmission time
    ///
    /// Specifies a timestamp giving the time when the last transmission from a
    /// client was received.
    time_t cltt_;

    /// @brief Subnet identifier
    ///
    /// Specifies the identification of the subnet to which the lease belongs.
    SubnetID subnet_id_;

    /// @brief Fixed lease?
    ///
    /// Fixed leases are kept after they are released/expired.
    bool fixed_;

    /// @brief Client hostname
    ///
    /// This field may be empty
    std::string hostname_;

    /// @brief Forward zone updated?
    ///
    /// Set true if the DNS AAAA record for this lease has been updated.
    bool fqdn_fwd_;

    /// @brief Reverse zone updated?
    ///
    /// Set true if the DNS PTR record for this lease has been updated.
    bool fqdn_rev_;

    /// @brief Lease comments
    ///
    /// Currently not used. It may be used for keeping comments made by the
    /// system administrator.
    std::string comments_;

    /// @todo: Add DHCPv6 failover related fields here

    /// @brief Constructor
    ///
    /// Initialize fields that don't have a default constructor.
    Lease6() : addr_("::") {}

    /// @brief Convert Lease6 to Printable Form
    ///
    /// @return String form of the lease
    std::string toText();

    /// @brief Compare two leases for equality
    ///
    /// @param other lease6 object with which to compare
    bool operator==(const Lease6& other) const;

    /// @brief Compare two leases for inequality
    ///
    /// @param other lease6 object with which to compare
    bool operator!=(const Lease6& other) const {
        return (!operator==(other));
    }

};

/// @brief Pointer to a Lease6 structure.
typedef boost::shared_ptr<Lease6> Lease6Ptr;

/// @brief Const pointer to a Lease6 structure.
typedef boost::shared_ptr<const Lease6> ConstLease6Ptr;

/// @brief A collection of IPv6 leases.
typedef std::vector<Lease6Ptr> Lease6Collection;

/// @brief Abstract Lease Manager
///
/// This is an abstract API for lease database backends. It provides unified
/// interface to all backends. As this is an abstract class, it should not
/// be used directly, but rather specialized derived class should be used
/// instead.
///
/// As all methods are virtual, this class throws no exceptions.  However,
/// methods in concrete implementations of this class may throw exceptions:
/// see the documentation of those classes for details.
class LeaseMgr {
public:
    /// Client hardware address
    typedef std::vector<uint8_t> HWAddr;

    /// Database configuration parameter map
    typedef std::map<std::string, std::string> ParameterMap;

    /// @brief Constructor
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    LeaseMgr(const ParameterMap& parameters) : parameters_(parameters)
    {}

    /// @brief Destructor
    virtual ~LeaseMgr()
    {}

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    virtual bool addLease(const Lease4Ptr& lease) = 0;

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    virtual bool addLease(const Lease6Ptr& lease) = 0;

    /// @brief Returns IPv4 lease for specified IPv4 address and subnet_id
    ///
    /// This method is used to get a lease for specific subnet_id. There can be
    /// at most one lease for any given subnet, so this method returns a single
    /// pointer.
    ///
    /// @param addr address of the searched lease
    /// @param subnet_id ID of the subnet the lease must belong to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr,
                                SubnetID subnet_id) const = 0;

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
    virtual Lease4Collection getLease4(const HWAddr& hwaddr) const = 0;

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
    virtual Lease4Ptr getLease4(const HWAddr& hwaddr,
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
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
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
    /// The assumtion here is that there will not be site or link-local
    /// addresses used, so there is no way of having address duplication.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const isc::asiolink::IOAddress& addr) const = 0;

    /// @brief Returns existing IPv6 leases for a given DUID+IA combination
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Collection getLease6(const DUID& duid,
                                       uint32_t iaid) const = 0;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id subnet id of the subnet the lease belongs to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const DUID& duid, uint32_t iaid,
                                SubnetID subnet_id) const = 0;

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
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease4(const isc::asiolink::IOAddress& addr) = 0;

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv6 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease6(const isc::asiolink::IOAddress& addr) = 0;

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

    /// @brief returns value of the parameter
    virtual std::string getParameter(const std::string& name) const;

private:
    /// @brief list of parameters passed in dbconfig
    ///
    /// That will be mostly used for storing database name, username,
    /// password and other parameters required for DB access. It is not
    /// intended to keep any DHCP-related parameters.
    ParameterMap parameters_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // LEASE_MGR_H
