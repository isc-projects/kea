// Copyright (C) 2010-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IO_ADDRESS_H
#define IO_ADDRESS_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.
#include <unistd.h>             // for some network system calls
#include <stdint.h>             // for uint32_t
#include <boost/asio/ip/address.hpp>

#include <functional>
#include <string>
#include <vector>

#include <exceptions/exceptions.h>

namespace isc {
namespace asiolink {

    /// Defines length of IPv6 address (in binary format).
    static constexpr size_t V6ADDRESS_LEN = 16;

    /// Defines length of IPv4 address (in binary format).
    static constexpr size_t V4ADDRESS_LEN = 4;

    /// @brief Maximum size of an IPv4 address represented as a text string. 12
    ///     digits plus 3 full stops (dots).
    static constexpr size_t V4ADDRESS_TEXT_MAX_LEN = 15u;

    /// @brief Maximum size of an IPv6 address represented as a text string. 32
    ///     hexadecimal characters written in 8 groups of four, plus 7 colon
    ///     separators.
    static constexpr size_t V6ADDRESS_TEXT_MAX_LEN = 39u;

/// \brief The \c IOAddress class represents an IP addresses (version
/// agnostic)
///
/// This class is a wrapper for the ASIO \c ip::address class.
class IOAddress {
public:

    /// \brief An \c IOAddress hash enabling the use in the unordered
    /// STL containers.
    struct Hash {
        /// \brief A hashing operator.
        ///
        /// \param io_address an address to be hashed.
        /// \return a hashing result.
        size_t operator()(const IOAddress &io_address) const;
    };

    ///
    /// \name Constructors and Destructor
    ///
    /// This class is copyable.  We use default versions of copy constructor
    /// and the assignment operator.
    /// We use the default destructor.
    //@{
    /// \brief Constructor from string.
    ///
    /// This constructor converts a textual representation of IPv4 and IPv6
    /// addresses into an IOAddress object.
    /// If \c address_str is not a valid representation of any type of
    /// address, an exception of class \c IOError will be thrown.
    /// This constructor allocates memory for the object, and if that fails
    /// a corresponding standard exception will be thrown.
    ///
    /// \param address_str Textual representation of address.
    IOAddress(const std::string& address_str);

    /// \brief Constructor from an ASIO \c ip::address object.
    ///
    /// This constructor is intended to be used within the wrapper
    /// implementation; user applications of the wrapper API won't use it.
    ///
    /// This constructor never throws an exception.
    ///
    /// \param asio_address The ASIO \c ip::address to be converted.
    IOAddress(const boost::asio::ip::address& asio_address);
    //@}

    /// @brief Constructor for ip::address_v4 object.
    ///
    /// This constructor is intended to be used when constructing
    /// IPv4 address out of uint32_t type. Passed value must be in
    /// network byte order
    ///
    /// @param v4address IPv4 address represented by uint32_t
    IOAddress(uint32_t v4address);

    /// \brief Convert the address to a string.
    ///
    /// This method is basically expected to be exception free, but
    /// generating the string will involve resource allocation,
    /// and if it fails the corresponding standard exception will be thrown.
    ///
    /// \return A string representation of the address.
    std::string toText() const;

    /// \brief Returns the address family
    ///
    /// \return AF_INET for IPv4 or AF_INET6 for IPv6.
    short getFamily() const;

    /// \brief Convenience function to check for an IPv4 address
    ///
    /// \return true if the address is a V4 address
    bool isV4() const {
        return (asio_address_.is_v4());
    }

    /// \brief Convenience function to check if it is an IPv4 zero address.
    ///
    /// \return true if the address is the zero IPv4 address.
    bool isV4Zero() const {
        return (equals(IPV4_ZERO_ADDRESS()));
    }

    /// \brief Convenience function to check if it is an IPv4 broadcast
    ///        address.
    ///
    /// \return true if the address is the broadcast IPv4 address.
    bool isV4Bcast() const {
        return (equals(IPV4_BCAST_ADDRESS()));
    }

    /// \brief Convenience function to check for an IPv6 address
    ///
    /// \return true if the address is a V6 address
    bool isV6() const {
        return (asio_address_.is_v6());
    }

    /// \brief Convenience function to check if it is an IPv4 zero address.
    ///
    /// \return true if the address is the zero IPv4 address.
    bool isV6Zero() const {
        return (equals(IPV6_ZERO_ADDRESS()));
    }

    /// \brief checks whether and address is IPv6 and is link-local
    ///
    /// \return true if the address is IPv6 link-local, false otherwise
    bool isV6LinkLocal() const;

    /// \brief checks whether and address is IPv6 and is multicast
    ///
    /// \return true if the address is IPv6 multicast, false otherwise
    bool isV6Multicast() const;

    /// \brief Creates an address from over wire data.
    ///
    /// \param family AF_INET for IPv4 or AF_INET6 for IPv6.
    /// \param data pointer to first char of data
    ///
    /// \return Created IOAddress object
    static IOAddress fromBytes(short family, const uint8_t* data);

    /// \brief Return address as set of bytes
    ///
    /// \return Contents of the address as a set of bytes in network-byte
    ///         order.
    std::vector<uint8_t> toBytes() const;

    /// \brief Compare addresses for equality
    ///
    /// \param other Address to compare against.
    ///
    /// \return true if addresses are equal, false if not.
    bool equals(const IOAddress& other) const {
        return (asio_address_ == other.asio_address_);
    }

    /// \brief Compare addresses for equality
    ///
    /// \param other Address to compare against.
    ///
    /// \return true if addresses are equal, false if not.
    bool operator==(const IOAddress& other) const {
        return equals(other);
    }

    /// \brief Compare addresses for inequality
    ///
    /// \param other Address to compare against.
    ///
    /// \return false if addresses are equal, true if not.
    bool nequals(const IOAddress& other) const {
        return (!equals(other));
    }

    /// \brief Checks if one address is smaller than the other
    ///
    /// \param other Address to compare against.
    bool operator<(const IOAddress& other) const {
        return (asio_address_ < other.asio_address_);
    }

    /// \brief Checks if one address is smaller or equal than the other
    ///
    /// \param other Address to compare against.
    bool operator<=(const IOAddress& other) const {
        return (asio_address_ <= other.asio_address_);
    }

    /// \brief Compare addresses for inequality
    ///
    /// \param other Address to compare against.
    ///
    /// \return false if addresses are equal, true if not.
    bool operator!=(const IOAddress& other) const {
        return (nequals(other));
    }

    /// @brief Subtracts one address from another (a - b)
    ///
    /// Treats addresses as integers and subtracts them. For example:
    /// @code
    /// 192.0.2.5 - 192.0.2.0 = 0.0.0.5
    /// fe80::abcd - fe80:: = ::abcd
    /// @endcode
    ///
    /// It is possible to subtract greater from lesser address, e.g.
    /// 192.168.56.10 - 192.168.67.20, but please do understand that
    /// the address space is a finite field in mathematical sense, so
    /// you may end up with a result that is greater then any of the
    /// addresses you specified. Also, subtraction is not commutative,
    /// so a - b != b - a.
    ///
    /// This operation is essential for calculating the number of
    /// leases in a pool, where we need to calculate (max - min).
    /// @throw BadValue if addresses are of different family
    /// @param a address to be subtracted from
    /// @param b address to be subtracted
    /// @return IOAddress object that represents the difference
    static IOAddress subtract(const IOAddress& a, const IOAddress& b);

    /// @brief Returns an address increased by one
    ///
    /// This method works for both IPv4 and IPv6 addresses. For example,
    /// increase 192.0.2.255 will become 192.0.3.0.
    ///
    /// Address space is a finite field in the mathematical sense, so keep
    /// in mind that the address space "loops". 255.255.255.255 increased
    /// by one gives 0.0.0.0. The same is true for maximum value of IPv6
    /// (all 1's) looping to ::.
    ///
    /// @todo Determine if we have a use-case for increasing the address
    /// by more than one. Increase by one is used in AllocEngine. This method
    /// could take extra parameter that specifies the value by which the
    /// address should be increased.
    ///
    /// @param addr address to be increased
    /// @return address increased by one
    static IOAddress
    increase(const IOAddress& addr);

    /// \brief Converts IPv4 address to uint32_t
    ///
    /// Will throw BadValue exception if that is not IPv4
    /// address.
    ///
    /// \return uint32_t that represents IPv4 address in
    ///         network byte order
    uint32_t toUint32() const;

    /// @name Methods returning @c IOAddress objects encapsulating typical addresses.
    ///
    //@{
    /// @brief Returns an address set to all zeros.
    static const IOAddress& IPV4_ZERO_ADDRESS() {
        static IOAddress address(0);
        return (address);
    }

    /// @brief Returns a "255.255.255.255" broadcast address.
    static const IOAddress& IPV4_BCAST_ADDRESS() {
        static IOAddress address(0xFFFFFFFF);
        return (address);
    }

    /// @brief Returns an IPv6 zero address.
    static const IOAddress& IPV6_ZERO_ADDRESS() {
        static IOAddress address("::");
        return (address);
    }

    //@}

private:
    boost::asio::ip::address asio_address_;
};

/// \brief Insert the IOAddress as a string into stream.
///
/// This method converts the \c address into a string and inserts it
/// into the output stream \c os.
///
/// This function overloads the global operator<< to behave as described
/// in ostream::operator<< but applied to \c IOAddress objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param address The \c IOAddress object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream&
operator<<(std::ostream& os, const IOAddress& address);

/// \brief Hash the IOAddress.
///
/// This method allows boost multi-index hashed indexes on IOAddresses.
/// It follows the requirement with equality: if two addresses are equal
/// their hashes are equal, if two addresses are not equal their hashes
/// are almost surely not equal.
///
/// \param address A \c IOAddress to hash.
/// \return The hash of the IOAddress.
size_t hash_value(const IOAddress& address);

} // namespace asiolink
} // namespace isc
#endif // IO_ADDRESS_H
