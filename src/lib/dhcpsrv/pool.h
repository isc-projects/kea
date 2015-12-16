// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef POOL_H
#define POOL_H

#include <asiolink/io_address.h>
#include <boost/shared_ptr.hpp>
#include <dhcpsrv/lease.h>

#include <vector>

namespace isc {
namespace dhcp {

/// @brief base class for Pool4 and Pool6
///
/// Stores information about pool of IPv4 or IPv6 addresses.
/// That is a basic component of a configuration.
class Pool {

public:
    /// @note:
    /// PoolType enum was removed. Please use Lease::Type instead

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

    /// @brief Returns pool type (v4, v6 non-temporary, v6 temp, v6 prefix)
    /// @return returns pool type
    Lease::Type getType() const {
        return (type_);
    }

    /// @brief returns textual representation of the pool
    ///
    /// @return textual representation
    virtual std::string toText() const;

    /// @brief virtual destructor
    ///
    /// We need Pool to be a polymorphic class, so we could dynamic cast
    /// from PoolPtr to Pool6Ptr if we need to. A class becomes polymorphic,
    /// when there is at least one virtual method.
    virtual ~Pool() {
    }

    /// @brief Returns the number of all leases in this pool.
    ///
    /// Note that this is the upper bound, assuming that no leases are used
    /// and there are no host reservations. This is just a theoretical calculation.
    /// @return number of possible leases in this pool
    uint64_t getCapacity() const {
        return (capacity_);
    }
protected:

    /// @brief protected constructor
    ///
    /// This constructor is protected to prevent anyone from instantiating
    /// Pool class directly. Instances of Pool4 and Pool6 should be created
    /// instead.
    ///
    /// @param type type of lease that will be served from this pool
    /// @param first first address of a range
    /// @param last last address of a range
    Pool(Lease::Type type,
         const isc::asiolink::IOAddress& first,
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

    /// @brief defines a lease type that will be served from this pool
    Lease::Type type_;

    /// @brief Stores number of possible leases.
    ///
    /// This could be calculated on the fly, but the calculations are somewhat
    /// involved, so it is more efficient to calculate it once and just store
    /// the result. Note that for very large pools, the number is capped at
    /// max value of uint64_t.
    uint64_t capacity_;
};

/// @brief Pool information for IPv4 addresses
///
/// It holds information about pool4, i.e. a range of IPv4 address space that
/// is configured for DHCP allocation.
class Pool4 : public Pool {
public:
    /// @brief the constructor for Pool4 "min-max" style definition
    ///
    /// @param first the first address in a pool
    /// @param last the last address in a pool
    Pool4(const isc::asiolink::IOAddress& first,
          const isc::asiolink::IOAddress& last);

    /// @brief the constructor for Pool4 "prefix/len" style definition
    ///
    /// @param prefix specifies prefix of the pool
    /// @param prefix_len specifies length of the prefix of the pool
    Pool4(const isc::asiolink::IOAddress& prefix,
          uint8_t prefix_len);
};

/// @brief a pointer an IPv4 Pool
typedef boost::shared_ptr<Pool4> Pool4Ptr;

/// @brief Pool information for IPv6 addresses and prefixes
///
/// It holds information about pool6, i.e. a range of IPv6 address space that
/// is configured for DHCP allocation.
class Pool6 : public Pool {
public:

    /// @brief the constructor for Pool6 "min-max" style definition
    ///
    /// @throw BadValue if PD is define (PD can be only prefix/len)
    ///
    /// @param type type of the pool (IA or TA)
    /// @param first the first address in a pool
    /// @param last the last address in a pool
    Pool6(Lease::Type type, const isc::asiolink::IOAddress& first,
          const isc::asiolink::IOAddress& last);

    /// @brief the constructor for Pool6 "prefix/len" style definition
    ///
    /// For addressed, this is just a prefix/len definition. For prefixes,
    /// there is one extra additional parameter delegated_len. It specifies
    /// a size of delegated prefixes that the pool will be split into. For
    /// example pool 2001:db8::/56, delegated_len=64 means that there is a
    /// pool 2001:db8::/56. It will be split into 256 prefixes of length /64,
    /// e.g. 2001:db8:0:1::/64, 2001:db8:0:2::/64 etc.
    ///
    /// Naming convention:
    /// A smaller prefix length yields a shorter prefix which describes a larger
    /// set of addresses. A larger length yields a longer prefix which describes
    /// a smaller set of addresses.
    ///
    /// Obviously, prefix_len must define shorter or equal prefix length than
    /// delegated_len, so prefix_len <= delegated_len. Note that it is slightly
    /// confusing: bigger (larger) prefix actually has smaller prefix length,
    /// e.g. /56 is a bigger prefix than /64, but has shorter (smaller) prefix
    /// length.
    ///
    /// @throw BadValue if delegated_len is defined for non-PD types or
    ///        when delegated_len < prefix_len
    ///
    /// @param type type of the pool (IA, TA or PD)
    /// @param prefix specifies prefix of the pool
    /// @param prefix_len specifies prefix length of the pool
    /// @param delegated_len specifies lenght of the delegated prefixes
    Pool6(Lease::Type type, const isc::asiolink::IOAddress& prefix,
          uint8_t prefix_len, uint8_t delegated_len = 128);

    /// @brief returns pool type
    ///
    /// @return pool type
    Lease::Type getType() const {
        return (type_);
    }

    /// @brief returns delegated prefix length
    ///
    /// This may be useful for "prefix/len" style definition for
    /// addresses, but is mostly useful for prefix pools.
    /// @return prefix length (1-128)
    uint8_t getLength() {
        return (prefix_len_);
    }

    /// @brief returns textual representation of the pool
    ///
    /// @return textual representation
    virtual std::string toText() const;

private:
    /// @brief Defines prefix length (for TYPE_PD only)
    uint8_t prefix_len_;
};

/// @brief a pointer an IPv6 Pool
typedef boost::shared_ptr<Pool6> Pool6Ptr;

/// @brief a pointer to either IPv4 or IPv6 Pool
typedef boost::shared_ptr<Pool> PoolPtr;

/// @brief a container for either IPv4 or IPv6 Pools
typedef std::vector<PoolPtr> PoolCollection;


} // end of isc::dhcp namespace
} // end of isc namespace


#endif // POOL_H
