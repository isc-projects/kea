// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __IO_ADDRESS_H
#define __IO_ADDRESS_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.
#include <unistd.h>             // for some network system calls
#include <stdint.h>             // for uint32_t
#include <asio/ip/address.hpp>

#include <functional>
#include <string>

#include <exceptions/exceptions.h>

namespace isc {
namespace asiolink {

    /// Defines length of IPv6 address.
    const static size_t V6ADDRESS_LEN = 16;

    /// Defines length of IPv4 address.
    const static size_t V4ADDRESS_LEN = 4;

/// \brief The \c IOAddress class represents an IP addresses (version
/// agnostic)
///
/// This class is a wrapper for the ASIO \c ip::address class.
class IOAddress {
public:
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
    IOAddress(const asio::ip::address& asio_address);
    //@}

    /// @brief Constructor for ip::address_v4 object.
    ///
    /// This constructor is intented to be used when constructing
    /// IPv4 address out of uint32_t type. Passed value must be in
    /// network byte order
    ///
    /// @param v4address IPv4 address represnted by uint32_t
    IOAddress(uint32_t v4address);

    /// \brief Convert the address to a string.
    ///
    /// This method is basically expected to be exception free, but
    /// generating the string will involve resource allocation,
    /// and if it fails the corresponding standard exception will be thrown.
    ///
    /// \return A string representation of the address.
    std::string toText() const;

    /// \brief Returns const reference to the underlying address object.
    ///
    /// This is useful, when access to interface offerted by
    //  asio::ip::address_v4 and asio::ip::address_v6 is beneficial.
    /// 
    /// \return A const reference to asio::ip::address object
    const asio::ip::address& getAddress() const;

    /// \brief Returns the address family
    ///
    /// \return AF_INET for IPv4 or AF_INET6 for IPv6.
    short getFamily() const;


    /// \brief Creates an address from over wire data.
    ///
    /// \param family AF_NET for IPv4 or AF_NET6 for IPv6.
    /// \param data pointer to first char of data
    ///
    /// \return Created IOAddress object
    static IOAddress
    from_bytes(short family, const uint8_t* data);

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
    ///
    /// \return true if this address is smaller than the other address.
    ///
    /// It is useful for comparing which address is bigger.
    /// Operations within one protocol family are obvious.
    /// Comparisons between v4 and v6 will allways return v4
    /// being smaller. This follows boost::asio::ip implementation
    bool smaller_than(const IOAddress& other) const {
        if (this->getFamily() < other.getFamily()) {
            return (true);
        }
        if (this->getFamily() > other.getFamily()) {
            return (false);
        }
        if (this->getFamily() == AF_INET6) {
            return (this->asio_address_.to_v6() < other.asio_address_.to_v6());
        } else {
            return (this->asio_address_.to_v4() < other.asio_address_.to_v4());
        }
    }

    /// \brief Checks if one address is smaller than the other
    ///
    /// \param other Address to compare against.
    ///
    /// See \ref smaller_than method for details.
    bool operator<(const IOAddress& other) const {
        return (smaller_than(other));
    }

    /// \brief Compare addresses for inequality
    ///
    /// \param other Address to compare against.
    ///
    /// \return false if addresses are equal, true if not.
    bool operator!=(const IOAddress& other) const {
        return (nequals(other));
    }

    /// \brief Converts IPv4 address to uint32_t
    ///
    /// Will throw BadValue exception if that is not IPv4
    /// address.
    ///
    /// \return uint32_t that represents IPv4 address in
    ///         network byte order
    operator uint32_t () const;

private:
    asio::ip::address asio_address_;
};

} // namespace asiolink
} // namespace isc
#endif // __IO_ADDRESS_H
