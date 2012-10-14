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

#ifndef POOL_H
#define POOL_H

#include <vector>
#include <asiolink/io_address.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

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

/// @brief a container for IPv4 Pools
typedef std::vector<Pool4Ptr> Pool4Collection;

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

} // end of isc::dhcp namespace
} // end of isc namespace


#endif // POOL_H
