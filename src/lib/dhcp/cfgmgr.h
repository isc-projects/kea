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
#include <asiolink/io_address.h>
#include <util/buffer.h>

namespace isc {
namespace dhcp {

class Pool6;
class Subnet6;

/// @brief this class specifes parameter value
///
/// This class is used to store configuration parameters, like lifetime or T1.
/// It defines 3 parameters: min/default/max values. There are 2 constructors:
/// - simple (just one value that sets all parameters)
/// - extended (that sets default value and two thresholds)
template <class T>
class Triplet {
public:

    /// @brief base type to Triple conversion
    ///
    /// Typically: uint32_t to Triplet assignment. It is very convenient
    /// to be able to simply write Triplet<uint32_t> x = 7;
    Triplet<T>& operator = (T base_type) {
        return Triplet<T>(base_type);
    }

    /// @brief triplet to base type conversion
    ///
    /// Typically: Triplet to uint32_t assignment. It is very convenient
    /// to be able to simply write uint32_t z = x; (where x is a Triplet)
    operator T () const {
        return (default_);
    }

    /// @brief sets a fixed value
    Triplet(T value)
        :min_(value), default_(value), max_(value) {
    }

    /// @brief sets the default value and thresholds
    ///
    /// @throw BadValue if min <= def <= max rule is violated
    Triplet(T min, T def, T max)
        :min_(min), default_(def), max_(max) {
        if ( (min_>def) || (def > max_) ) {
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

class Pool {

public:
    uint32_t getId() const {
        return (id_);
    }

    Triplet<uint32_t> getValid() const {
        return (valid_);
    }

    const isc::asiolink::IOAddress& getFirstAddress() const {
        return (first_);
    }

    const isc::asiolink::IOAddress& getLastAddress() const {
        return (last_);
    }

    Triplet<uint32_t> getT1() const {
        return (t1_);
    }

    Triplet<uint32_t> getT2() const {
        return (t2_);
    }

    /// @brief checks if specified address is in range
    bool inRange(const isc::asiolink::IOAddress& addr);

protected:

    /// @brief protected constructor
    Pool(const isc::asiolink::IOAddress& first,
         const isc::asiolink::IOAddress& last,
         const Triplet<uint32_t>& t1,
         const Triplet<uint32_t>& t2,
         const Triplet<uint32_t>& valid_lifetime);

    static uint32_t getNextID() {
        static uint32_t id = 0;
        return (id++);
    }

    /// @brief pool-id
    ///
    /// This ID is used to indentify this specific pool.
    uint32_t id_;

    isc::asiolink::IOAddress first_;

    isc::asiolink::IOAddress last_;

    Triplet<uint32_t> t1_;

    Triplet<uint32_t> t2_;

    Triplet<uint32_t> valid_;

    std::string comments_;

    ///uint128_t available_leases_;

    ///uint128_t total_leases_;
};

class Pool6 : public Pool {
public:
    typedef enum {
        TYPE_IA,
        TYPE_TA,
        TYPE_PD
    }  Pool6Type;

    Pool6(Pool6Type type, const isc::asiolink::IOAddress& first,
          const isc::asiolink::IOAddress& last,
          const Triplet<uint32_t>& t1,
          const Triplet<uint32_t>& t2,
          const Triplet<uint32_t>& preferred_lifetime,
          const Triplet<uint32_t>& valid_lifetime);

    Pool6(Pool6Type type, const isc::asiolink::IOAddress& addr,
          uint8_t prefix_len,
          const Triplet<uint32_t>& t1,
          const Triplet<uint32_t>& t2,
          const Triplet<uint32_t>& preferred_lifetime,
          const Triplet<uint32_t>& valid_lifetime);

    Pool6Type getType() const {
        return (type_);
    }

    Triplet<uint32_t> getPreferred() const {
        return (preferred_);
    }

protected:

    Pool6Type type_;

    /// @brief prefix length
    /// used by TYPE_PD only (zeroed for other types)
    uint8_t prefix_len_;

    Triplet<uint32_t> preferred_;
};

typedef boost::shared_ptr<Pool> PoolPtr;
typedef boost::shared_ptr<Pool6> Pool6Ptr;

typedef std::vector<Pool6Ptr> Pool6Collection;

class Subnet {
public:
    /// @brief checks if specified address is in range
    bool inRange(const isc::asiolink::IOAddress& addr);

protected:
    /// @brief protected constructor
    //
    /// By making the constructor protected, we make sure that noone will
    /// ever instantiate that class. Pool4 and Pool6 should be used instead.
    Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len);

    static uint32_t getNextID() {
        static uint32_t id = 0;
        return (id++);
    }

    /// @brief subnet-id
    uint32_t id_;

    isc::asiolink::IOAddress prefix_;

    uint8_t len_;
};

class Subnet6 : public Subnet {
public:
    Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length);

protected:
    /// collection of pools in that list
    Pool6Collection pools_;

};

} // namespace isc::dhcp
} // namespace isc

#endif
