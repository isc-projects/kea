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

#ifndef SUBNET_H
#define SUBNET_H

#include <boost/shared_ptr.hpp>
#include <asiolink/io_address.h>
#include <dhcp/pool.h>
#include <dhcp/triplet.h>

namespace isc {
namespace dhcp {

/// @brief a base class for Subnet4 and Subnet6
///
/// This class presents a common base for IPv4 and IPv6 subnets.
/// In a physical sense, a subnet defines a single network link with all devices
/// attached to it. In most cases all devices attached to a single link can
/// share the same parameters. Therefore Subnet holds several values that are
/// typically shared by all hosts: renew timer (T1), rebind timer (T2) and
/// leased addresses lifetime (valid-lifetime).
///
/// @todo: Implement support for options here


/// @brief Unique indentifier for a subnet (both v4 and v6)
typedef uint32_t SubnetID;

class Subnet {
public:
    /// @brief checks if specified address is in range
    bool inRange(const isc::asiolink::IOAddress& addr) const;

    /// @brief checks if the specified address is in pools
    ///
    /// Note the difference between inSubnet() and inPool(). For a given
    /// subnet (e.g. 2001::/64) there may be one or more pools defined
    /// that may or may not cover entire subnet, e.g. pool 2001::1-2001::10).
    /// inPool() returning true implies inSubnet(), but the reverse implication
    /// is not always true. For the given example, 2001::1234:abcd would return
    /// true for inSubnet(), but false for inPool() check.
    ///
    /// @param addr this address will be checked if it belongs to any pools in
    ///        that subnet
    /// @return true if the address is in any of the pools
    virtual bool inPool(const isc::asiolink::IOAddress& addr) const = 0;

    /// @brief return valid-lifetime for addresses in that prefix
    Triplet<uint32_t> getValid() const {
        return (valid_);
    }

    /// @brief returns T1 (renew timer), expressed in seconds
    Triplet<uint32_t> getT1() const {
        return (t1_);
    }

    /// @brief returns T2 (rebind timer), expressed in seconds
    Triplet<uint32_t> getT2() const {
        return (t2_);
    }

    /// @brief returns the last address that was tried from this pool
    ///
    /// This method returns the last address that was attempted to be allocated
    /// from this subnet. This is used as helper information for the next
    /// iteration of the allocation algorithm.
    ///
    /// @todo: Define map<SubnetID, IOAddress> somewhere in the
    ///        AllocEngine::IterativeAllocator and keep the data there
    ///
    /// @return address that was last tried from this pool
    isc::asiolink::IOAddress getLastAllocated() const {
        return (last_allocated_);
    }

    /// @brief sets the last address that was tried from this pool
    ///
    /// This method sets the last address that was attempted to be allocated
    /// from this subnet. This is used as helper information for the next
    /// iteration of the allocation algorithm.
    ///
    /// @todo: Define map<SubnetID, IOAddress> somewhere in the
    ///        AllocEngine::IterativeAllocator and keep the data there
    void setLastAllocated(const isc::asiolink::IOAddress& addr) {
        last_allocated_ = addr;
    }

    /// @brief returns unique ID for that subnet
    /// @return unique ID for that subnet
    SubnetID getID() const { return (id_); }

protected:
    /// @brief protected constructor
    //
    /// By making the constructor protected, we make sure that noone will
    /// ever instantiate that class. Pool4 and Pool6 should be used instead.
    Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len,
           const Triplet<uint32_t>& t1,
           const Triplet<uint32_t>& t2,
           const Triplet<uint32_t>& valid_lifetime);

    /// @brief virtual destructor
    virtual ~Subnet() {
    };

    /// @brief returns the next unique Subnet-ID
    ///
    /// @return the next unique Subnet-ID
    static SubnetID getNextID() {
        static SubnetID id = 0;
        return (id++);
    }

    /// @brief subnet-id
    ///
    /// Subnet-id is a unique value that can be used to find or identify
    /// a Subnet4 or Subnet6.
    SubnetID id_;

    /// @brief a prefix of the subnet
    isc::asiolink::IOAddress prefix_;

    /// @brief a prefix length of the subnet
    uint8_t prefix_len_;

    /// @brief a tripet (min/default/max) holding allowed renew timer values
    Triplet<uint32_t> t1_;

    /// @brief a tripet (min/default/max) holding allowed rebind timer values
    Triplet<uint32_t> t2_;

    /// @brief a tripet (min/default/max) holding allowed valid lifetime values
    Triplet<uint32_t> valid_;

    /// @brief last allocated address
    ///
    /// This is the last allocated address that was previously allocated from
    /// this particular subnet. Some allocation algorithms (e.g. iterative) use
    /// that value, others do not. It should be noted that although the value
    /// is usually correct, there are cases when it is invalid, e.g. after
    /// removing a pool, restarting or changing allocation algorithms. For
    /// that purpose it should be only considered a help that should not be
    /// fully trusted.
    isc::asiolink::IOAddress last_allocated_;
};

/// @brief A configuration holder for IPv4 subnet.
///
/// This class represents an IPv4 subnet.
class Subnet4 : public Subnet {
public:

    /// @brief Constructor with all parameters
    ///
    /// @param prefix Subnet4 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    Subnet4(const isc::asiolink::IOAddress& prefix, uint8_t length,
            const Triplet<uint32_t>& t1,
            const Triplet<uint32_t>& t2,
            const Triplet<uint32_t>& valid_lifetime);

    /// @brief Returns a pool that specified address belongs to
    ///
    /// @param hint address that the returned pool should cover (optional)
    /// @return Pointer to found pool4 (or NULL)
    Pool4Ptr getPool4(const isc::asiolink::IOAddress& hint =
                      isc::asiolink::IOAddress("0.0.0.0"));

    /// @brief Adds a new pool.
    /// @param pool pool to be added
    void addPool4(const Pool4Ptr& pool);

    /// @brief returns all pools
    ///
    /// The reference is only valid as long as the object that returned it.
    ///
    /// @return a collection of all pools
    const Pool4Collection& getPools() const {
        return pools_;
    }

    /// @brief checks if the specified address is in pools
    ///
    /// See the description in \ref Subnet::inPool().
    ///
    /// @param addr this address will be checked if it belongs to any pools in that subnet
    /// @return true if the address is in any of the pools
    bool inPool(const isc::asiolink::IOAddress& addr) const;

protected:
    /// @brief collection of pools in that list
    Pool4Collection pools_;
};

/// @brief A pointer to a Subnet4 object
typedef boost::shared_ptr<Subnet4> Subnet4Ptr;

/// @brief A collection of Subnet6 objects
typedef std::vector<Subnet4Ptr> Subnet4Collection;


/// @brief A configuration holder for IPv6 subnet.
///
/// This class represents an IPv6 subnet.
class Subnet6 : public Subnet {
public:

    /// @brief Constructor with all parameters
    ///
    /// @param prefix Subnet6 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param preferred_lifetime preferred lifetime of leases (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length,
            const Triplet<uint32_t>& t1,
            const Triplet<uint32_t>& t2,
            const Triplet<uint32_t>& preferred_lifetime,
            const Triplet<uint32_t>& valid_lifetime);

    /// @brief Returns preverred lifetime (in seconds)
    ///
    /// @return a triplet with preferred lifetime
    Triplet<uint32_t> getPreferred() const {
        return (preferred_);
    }

    /// @brief Returns a pool that specified address belongs to
    ///
    /// @param hint address that the returned pool should cover (optional)
    /// @return Pointer to found pool6 (or NULL)
    Pool6Ptr getPool6(const isc::asiolink::IOAddress& hint =
                      isc::asiolink::IOAddress("::"));

    /// @brief Adds a new pool.
    /// @param pool pool to be added
    void addPool6(const Pool6Ptr& pool);

    /// @brief returns all pools
    ///
    /// The reference is only valid as long as the object that
    /// returned it.
    ///
    /// @return a collection of all pools
    const Pool6Collection& getPools() const {
        return pools_;
    }

    /// @brief checks if the specified address is in pools
    ///
    /// See the description in \ref Subnet::inPool().
    ///
    /// @param addr this address will be checked if it belongs to any pools in that subnet
    /// @return true if the address is in any of the pools
    bool inPool(const isc::asiolink::IOAddress& addr) const;

protected:
    /// @brief collection of pools in that list
    Pool6Collection pools_;

    /// @brief a triplet with preferred lifetime (in seconds)
    Triplet<uint32_t> preferred_;
};

/// @brief A pointer to a Subnet6 object
typedef boost::shared_ptr<Subnet6> Subnet6Ptr;

/// @brief A collection of Subnet6 objects
typedef std::vector<Subnet6Ptr> Subnet6Collection;

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // SUBNET_T
