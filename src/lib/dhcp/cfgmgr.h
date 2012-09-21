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

#ifndef CFGMGR_H
#define CFGMGR_H

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <asiolink/io_address.h>
#include <util/buffer.h>
#include <dhcp/option.h>

namespace isc {
namespace dhcp {

class Pool6;

class Subnet6;

/// @brief this template specifies a parameter value
///
/// This template class is used to store configuration parameters, like lifetime or T1.
/// It defines 3 parameters: min, default, and max value. There are 2 constructors:
/// - simple (just one value that sets all parameters)
/// - extended (that sets default value and two thresholds)
/// It will be used with integer types. It provides necessary operators, so
/// it can be assigned to a plain integer or integer assigned to a Triplet.
/// See TripletTest.operator test for details on an easy Triplet usage.
template <class T>
class Triplet {
public:

    /// @brief base type to Triple conversion
    ///
    /// Typically: uint32_t to Triplet assignment. It is very convenient
    /// to be able to simply write Triplet<uint32_t> x = 7;
    Triplet<T> operator=(T other) {
        min_ = other;
        default_ = other;
        max_ = other;
        return *this;
    }

    /// @brief triplet to base type conversion
    ///
    /// Typically: Triplet to uint32_t assignment. It is very convenient
    /// to be able to simply write uint32_t z = x; (where x is a Triplet)
    operator T() const {
        return (default_);
    }

    /// @brief sets a fixed value
    ///
    /// This constructor assigns a fixed (i.e. no range, just a single value)
    /// value.
    Triplet(T value)
        :min_(value), default_(value), max_(value) {
    }

    /// @brief sets the default value and thresholds
    ///
    /// @throw BadValue if min <= def <= max rule is violated
    Triplet(T min, T def, T max)
        :min_(min), default_(def), max_(max) {
        if ( (min_ > def) || (def > max_) ) {
            isc_throw(BadValue, "Invalid triplet values.");
        }
    }

    /// @brief returns a minimum allowed value
    T getMin() const { return min_;}

    /// @brief returns the default value
    T get() const { return default_;}

    /// @brief returns value with a hint
    ///
    /// DHCP protocol treats any values sent by a client as hints.
    /// This is a method that implements that. We can assign any value
    /// from configured range that client asks.
    T get(T hint) const {
        if (hint <= min_) {
            return (min_);
        }

        if (hint >= max_) {
            return (max_);
        }

        return (hint);
    }

    /// @brief returns a maximum allowed value
    T getMax() const { return max_; }

protected:

    /// @brief the minimum value
    T min_;

    /// @brief the default value
    T default_;

    /// @brief the maximum value
    T max_;
};


/// @brief base class for Pool4 and Pool6
///
/// Stores information about pool of IPv4 or IPv6 addresses.
/// That is a basic component of a configuration.
class Pool {

public:

    /// @brief returns Pool-id
    ///
    /// @return pool-id value
    /// Pool-id is an unique value that can be used to identify a pool.
    uint32_t getId() const {
        return (id_);
    }

    /// @brief Returns the first address in a pool.
    ///
    /// @return first address in a pool
    const isc::asiolink::IOAddress& getFirstAddress() const {
        return (first_);
    }

    /// @brief Returns the last address in a pool.
    /// @return last address in a pool
    const isc::asiolink::IOAddress& getLastAddress() const {
        return (last_);
    }

    /// @brief Checks if a given address is in the range.
    ///
    /// @return true, if the address is in pool
    bool inRange(const isc::asiolink::IOAddress& addr) const;

protected:

    /// @brief protected constructor
    ///
    /// This constructor is protected to prevent anyone from instantiating
    /// Pool class directly. Instances of Pool4 and Pool6 should be created
    /// instead.
    Pool(const isc::asiolink::IOAddress& first,
         const isc::asiolink::IOAddress& last);

    /// @brief returns the next unique Pool-ID
    ///
    /// @return the next unique Pool-ID
    static uint32_t getNextID() {
        static uint32_t id = 0;
        return (id++);
    }

    /// @brief pool-id
    ///
    /// This ID is used to identify this specific pool.
    uint32_t id_;

    /// @brief The first address in a pool
    isc::asiolink::IOAddress first_;

    /// @brief The last address in a pool
    isc::asiolink::IOAddress last_;

    /// @brief Comments field
    ///
    /// @todo: This field is currently not used.
    std::string comments_;
};

/// @brief Pool information for IPv6 addresses and prefixes
///
/// It holds information about pool6, i.e. a range of IPv6 address space that
/// is configured for DHCP allocation.
class Pool6 : public Pool {
public:

    /// @brief specifies Pool type
    ///
    /// Currently there are 3 pool types defined in DHCPv6:
    /// - Non-temporary addresses (conveyed in IA_NA)
    /// - Temporary addresses (conveyed in IA_TA)
    /// - Delegated Prefixes (conveyed in IA_PD)
    /// There is a new one being worked on (IA_PA, see draft-ietf-dhc-host-gen-id), but
    /// support for it is not planned for now.
    typedef enum {
        TYPE_IA,
        TYPE_TA,
        TYPE_PD
    }  Pool6Type;

    /// @brief the constructor for Pool6 "min-max" style definition
    ///
    /// @param first the first address in a pool
    /// @param last the last address in a pool
    Pool6(Pool6Type type, const isc::asiolink::IOAddress& first,
          const isc::asiolink::IOAddress& last);

    /// @brief the constructor for Pool6 "prefix/len" style definition
    ///
    /// @param prefix specifies prefix of the pool
    /// @param prefix_len specifies length of the prefix of the pool
    Pool6(Pool6Type type, const isc::asiolink::IOAddress& prefix,
          uint8_t prefix_len);

    /// @brief returns pool type
    ///
    /// @return pool type
    Pool6Type getType() const {
        return (type_);
    }

private:
    /// @brief defines a pool type
    Pool6Type type_;

    /// @brief prefix length
    /// used by TYPE_PD only (zeroed for other types)
    uint8_t prefix_len_;
};

/// @brief a pointer an IPv6 Pool
typedef boost::shared_ptr<Pool6> Pool6Ptr;

/// @brief a container for IPv6 Pools
typedef std::vector<Pool6Ptr> Pool6Collection;

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
class Subnet {
public:
    /// @brief checks if specified address is in range
    bool inRange(const isc::asiolink::IOAddress& addr) const;

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

protected:
    /// @brief protected constructor
    //
    /// By making the constructor protected, we make sure that noone will
    /// ever instantiate that class. Pool4 and Pool6 should be used instead.
    Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len,
           const Triplet<uint32_t>& t1,
           const Triplet<uint32_t>& t2,
           const Triplet<uint32_t>& valid_lifetime);

    /// @brief returns the next unique Subnet-ID
    ///
    /// @return the next unique Subnet-ID
    static uint32_t getNextID() {
        static uint32_t id = 0;
        return (id++);
    }

    /// @brief subnet-id
    ///
    /// Subnet-id is a unique value that can be used to find or identify
    /// a Subnet4 or Subnet6.
    uint32_t id_;

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
};

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

/// @brief Configuration Manager
///
/// This singleton class holds the whole configuration for DHCPv4 and DHCPv6
/// servers. It currently holds information about zero or more subnets6.
/// Each subnet may contain zero or more pools. Pool4 and Pool6 is the most
/// basic "chunk" of configuration. It contains a range of assigneable
/// addresses.
///
/// Below is a sketch of configuration inheritance (not implemented yet).
/// Let's investigate the following configuration:
///
/// preferred-lifetime 500;
/// valid-lifetime 1000;
/// subnet6 2001:db8:1::/48 {
///     pool6 2001::db8:1::1 - 2001::db8:1::ff;
/// };
/// subnet6 2001:db8:2::/48 {
///     valid-lifetime 2000;
///     pool6 2001::db8:2::1 - 2001::db8:2::ff;
/// };
/// Parameters defined in a global scope are applicable to everything until
/// they are overwritten in a smaller scope, in this case subnet6.
/// In the example above, the first subnet6 has preferred lifetime of 500s
/// and a valid lifetime of 1000s. The second subnet has preferred lifetime
/// of 500s, but valid lifetime of 2000s.
///
/// Parameter inheritance is likely to be implemented in configuration handling
/// routines, so there is no storage capability in a global scope for
/// subnet-specific parameters.
///
/// @todo: Implement Subnet4 support (ticket #2237)
/// @todo: Implement option definition support
/// @todo: Implement parameter inheritance
class CfgMgr : public boost::noncopyable {
public:

    /// @brief returns a single instance of Configuration Manager
    ///
    /// CfgMgr is a singleton and this method is the only way of
    /// accessing it.
    static CfgMgr& instance();

    /// @brief get subnet by address
    ///
    /// Finds a matching subnet, based on an address. This can be used
    /// in two cases: when trying to find an appropriate lease based on
    /// a) relay link address (that must be the address that is on link)
    /// b) our global address on the interface the message was received on
    ///    (for directly connected clients)
    ///
    /// @param hint an address that belongs to a searched subnet
    Subnet6Ptr getSubnet6(const isc::asiolink::IOAddress& hint);

    /// @brief get subnet by interface-id
    ///
    /// Another possibility to find a subnet is based on interface-id.
    ///
    /// @param interface_id content of interface-id option returned by a relay
    /// @todo This method is not currently supported.
    Subnet6Ptr getSubnet6(OptionPtr interface_id);

    /// @brief adds a subnet6
    void addSubnet6(const Subnet6Ptr& subnet);

    /// @todo: Add subnet6 removal routines. Currently it is not possible
    /// to remove subnets. The only case where subnet6 removal would be
    /// needed is a dynamic server reconfiguration - a use case that is not
    /// planned to be supported any time soon.
protected:

    /// @brief Protected constructor.
    ///
    /// This constructor is protected for 2 reasons. First, it forbids any
    /// instantiations of this class (CfgMgr is a singleton). Second, it
    /// allows derived class to instantiate it. That is useful for testing
    /// purposes.
    CfgMgr();

    /// @brief virtual desctructor
    virtual ~CfgMgr();

    /// @brief a container for Subnet6
    ///
    /// That is a simple vector of pointers. It does not make much sense to
    /// optimize access time (e.g. using a map), because typical search
    /// pattern will use calling inRange() method on each subnet until
    /// a match is found.
    Subnet6Collection subnets6_;
};

} // namespace isc::dhcp
} // namespace isc

#endif
