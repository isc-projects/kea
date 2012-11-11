// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef IP_CHECK_H
#define IP_CHECK_H

#include <sys/socket.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include <boost/static_assert.hpp>

#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h> // for AF_INET/AF_INET6
#include <netinet/in.h>

#include <acl/check.h>
#include <exceptions/exceptions.h>
#include <util/strutil.h>

namespace isc {
namespace acl {

// Free functions.  These are not supposed to be used outside this module,
// but are declared public for testing.  To try to conceal them, they are
// put in an "internal" namespace.

namespace internal {

/// \brief Convert prefix length to mask
///
/// Given a prefix length and a data type, return a value of that data type
/// with the most significant "prefix length" bits set.  For example, if the
/// data type is an uint8_t and the prefix length is 3, the function would
/// return a uint8_t holding the binary value 11100000.  This value is used as
/// a mask in the address checks.
///
/// \param prefixlen number of bits to be set in the mask.  This must be
///        between 0 and 8.
///
/// \return uint8_t with the most significant "prefixlen" bits set.
///
/// \exception OutOfRange prefixlen is too large for the data type.

uint8_t createMask(size_t prefixlen);

/// \brief Split IP Address Prefix
///
/// Splits an IP address prefix (given in the form of "xxxxxx/n" or "xxxxx" into
/// a string representing the IP address and a number giving the length of the
/// prefix. (In the latter case, the prefix is equal in length to the width in
/// width in bits of the data type holding the address.) An exception will be
/// thrown if the string format is invalid or if the prefix length is invalid.
///
/// N.B. This function does NOT check that the address component is a valid IP
/// address; this is done elsewhere in the address parsing process.
///
/// \param ipprefix Address or address prefix.  The string should be passed
///                 without leading or trailing spaces.
///
/// \return Pair of (string, int) holding the address string and the prefix
///         length.  The second element is -1 if no prefix was given.
///
/// \exception InvalidParameter Address prefix not of the expected syntax

std::pair<std::string, int>
splitIPAddress(const std::string& ipprefix);

} // namespace internal

/// \brief A simple representation of IP address.
///
/// This structure provides address family independent interfaces of an
/// IP(v4 or v6) address, so that the application can perform
/// \c IPCheck::matches without knowing which version of address it is
/// handling.  (For example, consider the standard socket API: it uses
/// the generic \c sockaddr structure to represent endpoints).
///
/// An object of this class could be constructed from various types of
/// sources, but in the initial implementation there's only one constructor,
/// which takes a \c sockaddr structure.  For efficiency the \c IPAddress
/// object only retains a reference to the necessary part of \c sockaddr.
/// Therefore the corresponding \c sockaddr instance must be valid while the
/// \c IPAddress object is used.
///
/// This class is copyable so that a fixed object can be easily reused for
/// different addresses.  To ensure internal integrity, specific member
/// variables are kept private and only accessible via read-only accessor
/// methods.  Due to this, it is ensured, for example, that if \c getFamily()
/// returns \c AF_INET6, \c getLength() always returns 16.
///
/// All accessor methods are straightforward and exception free.
///
/// In future, we may introduce the default constructor to further improve
/// reusability.
struct IPAddress {
    /// The constructor from socket address structure.
    ///
    /// This constructor set up the internal data based on the actual type
    /// \c sa.  For example, if \c sa.sa_family is \c AF_INET, it assumes
    /// \c sa actually refers to a \c sockaddr_in structure.
    /// The behavior when this assumption isn't held is undefined.
    ///
    /// \param sa A reference to the socket address structure from which the
    /// \c IPAddress is to be constructed.
    explicit IPAddress(const struct sockaddr& sa);

    /// Return the address family of the address
    ///
    /// It's AF_INET for IPv4 and AF_INET6 for IPv6.
    int getFamily() const { return (family); }

    /// Return the binary representation of the address in network byte order.
    ///
    /// Only the \c getLength() bytes from the returned pointer are ensured
    /// to be valid.  In addition, if the \c sockaddr structure given on
    /// construction was dynamically allocated, the data is valid only until
    /// the \c sockaddr is invalidated.
    const uint8_t* getData() const { return (data); }

    /// Return the length of the address.
    size_t getLength() const { return (length); }
private:
    int family;
    const uint8_t* data;
    size_t length;
};

/// \brief IP Check
///
/// This class performs a match between an IP address prefix specified in an ACL
/// and a given IP address.  The check works for both IPv4 and IPv6 addresses.
///
/// The class is templated on the type of a context structure passed to the
/// matches() method, and a template specialisation for that method must be
/// supplied for the class to be used.

template <typename Context>
class IPCheck : public Check<Context> {
private:
    // Size of uint8_t array needed to hold different address types
    static const size_t IPV6_SIZE = sizeof(struct in6_addr);
    static const size_t IPV4_SIZE = sizeof(struct in_addr);

    // Confirm our assumption of relative sizes - this allows us to assume that
    // an array sized for an IPv6 address can hold an IPv4 address.
    BOOST_STATIC_ASSERT(sizeof(struct in6_addr) > sizeof(struct in_addr));

public:
    /// \brief String Constructor
    ///
    /// Constructs an IP Check object from an address or address prefix in the
    /// form <ip-address>/n".
    ///
    /// Also allowed are the special keywords "any4" and "any6", which match
    /// any IPv4 or IPv6 address.  These must be specified in lowercase.
    ///
    /// \param ipprefix IP address prefix in the form "<ip-address>/n"
    ///        (where the "/n" part is optional and should be valid for the
    ///        address).  If "n" is specified as zero, the match is for any
    ///        address in that address family.  The address can also be
    ///        given as "any4" or "any6".
    IPCheck(const std::string& ipprefix) : family_(0) {

        // Ensure array elements are correctly initialized with zeroes.
        std::fill(address_, address_ + IPV6_SIZE, 0);
        std::fill(mask_, mask_ + IPV6_SIZE, 0);

        // Only deal with the string after we've removed leading and trailing
        // spaces.
        const std::string mod_prefix = isc::util::str::trim(ipprefix);

        // Check for special cases first.
        if (mod_prefix == "any4") {
            family_ = AF_INET;

        } else if (mod_prefix == "any6") {
            family_ = AF_INET6;

        } else {

            // General address prefix.  Split into address part and prefix
            // length.
            const std::pair<std::string, int> result =
                internal::splitIPAddress(mod_prefix);

            // Try to convert the address.  If successful, the result is in
            // network-byte order (most significant components at lower
            // addresses).
            int status = inet_pton(AF_INET6, result.first.c_str(), address_);
            if (status == 1) {
                // It was an IPv6 address.
                family_ = AF_INET6;
            } else {
                // IPv6 interpretation failed, try IPv4.
                status = inet_pton(AF_INET, result.first.c_str(), address_);
                if (status == 1) {
                    family_ = AF_INET;
                }
            }

            // Handle errors.
            if (status == 0) {
                isc_throw(isc::InvalidParameter, "address prefix of " <<
                          ipprefix << " is not valid");
            } else if (status < 0) {
                isc_throw(isc::Unexpected, "address conversion of " <<
                          ipprefix << " failed due to a system error");
            }

            // All done, so set the mask used in the address comparison.
            setMask(result.second);
        }
    }

    /// \brief Destructor
    virtual ~IPCheck() {}

    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here.  Different
    /// specialisations must be provided for different argument types, and the
    /// program will fail to compile if a required specialisation is not
    /// provided.
    ///
    /// It is expected that matches() will extract the address information from
    /// the Context structure, and use compare() to actually perform the
    /// comparison.
    ///
    /// \param context Information to be matched
    virtual bool matches(const Context& context) const;

    /// \brief Estimated cost
    ///
    /// Assume that the cost of the match is linear and depends on the
    /// maximum number of comparison operations.
    ///
    /// \return Estimated cost of the comparison
    virtual unsigned cost() const {
        return ((family_ == AF_INET) ? IPV4_SIZE : IPV6_SIZE);
    }

    ///@{
    /// Access methods - mainly for testing

    /// \return Stored IP address
    std::vector<uint8_t> getAddress() const {
        const size_t vector_len = (family_ == AF_INET ? IPV4_SIZE : IPV6_SIZE);
        return (std::vector<uint8_t>(address_, address_ + vector_len));
    }

    /// \return Network mask applied to match
    std::vector<uint8_t> getMask() const {
        const size_t vector_len = (family_ == AF_INET ? IPV4_SIZE : IPV6_SIZE);
        return (std::vector<uint8_t>(mask_, mask_ + vector_len));
    }

    /// \return Prefix length of the match
    size_t getPrefixlen() const {
        // Work this out by counting bits in the mask.
        size_t count = 0;
        for (size_t i = 0; i < IPV6_SIZE; ++i) {
            if (mask_[i] == 0xff) {
                // All bits set in this byte
                count += 8;
                continue;

            } else if (mask_[i] != 0) {
                // Only some bits set in this byte.  Count them.
                uint8_t byte = mask_[i];
                for (int j = 0; j < 8; ++j) {
                    count += byte & 0x01;   // Add one if the bit is set
                    byte >>= 1;             // Go for next bit
                }
            }
            break;
        }
        return (count);
    }

    /// \return Address family
    int getFamily() const {
        return (family_);
    }
    ///@}

protected:
    /// \brief Comparison
    ///
    /// This is the actual comparison function that checks the IP address passed
    /// to this class with the matching information in the class itself.  It is
    /// expected to be called from matches().
    ///
    /// \param testaddr Address (in network byte order) to test against the
    ///                 check condition in the class.  This is expected to
    ///                 be IPV6_SIZE or IPV4_SIZE bytes long.
    /// \param family   Address family of testaddr.
    ///
    /// \return true if the address matches, false if it does not.
    virtual bool compare(const uint8_t* testaddr, int family) const {

        if (family != family_) {
            // Can't match if the address is of the wrong family
            return (false);
        }

        // Simple check failed, so have to do a complete match.  To check that
        // the address given matches the stored network address and mask, we
        // check the simple condition that:
        //
        //     address_given & mask_ == stored_address & mask_
        //
        // The result is checked for all bytes for which there are bits set in
        // the mask.  We stop at the first non-match (or when we run out of bits
        // in the mask).
        //
        // Note that the mask represents a contiguous set of bits.  As such, as
        // soon as we find a mask byte of zeroes, we have run past the part of
        // the address where we need to match.
        //
        // Note also that when checking an IPv4 address, the constructor has
        // set all bytes in the mask beyond the first four bytes to zero.
        // As the loop stops when it encounters a zero mask byte, if the
        // ACL is for an IPV4 address, the loop will never check more than four
        // bytes.

        bool match = true;
        for (int i = 0; match && (i < IPV6_SIZE) && (mask_[i] != 0); ++i) {
             match = ((testaddr[i] & mask_[i]) == (address_[i] & mask_[i]));
        }
        return (match);
    }

private:
    /// \brief Set Mask
    ///
    /// Sets up the mask from the prefix length.  This involves setting
    /// an individual mask in each byte of the mask array.
    ///
    /// The actual allowed value of the prefix length depends on the address
    /// family.
    ///
    /// \param requested Requested prefix length size.  If negative, the
    ///        maximum for the address family is assumed.  (A negative value
    ///        will arise if the string constructor was used and no mask size
    ///        was given.)
    void setMask(int requested) {

        // Set the maximum number of bits allowed in the mask, and request
        // that number of bits if no prefix length was given in the constructor.
        const int maxmask = 8 * ((family_ == AF_INET) ? IPV4_SIZE : IPV6_SIZE);
        if (requested < 0) {
            requested = maxmask;
        }

        // Validate that the mask is valid.
        if (requested <= maxmask) {

            // Loop, setting the bits in the set of mask bytes until all the
            // specified bits have been used up.  As both IPv4 and IPv6
            // addresses are stored in network-byte order, this works in
            // both cases.
            size_t bits_left = requested;   // Bits remaining to set
            int i = -1;
            while (bits_left > 0) {
                if (bits_left >= 8) {
                    mask_[++i] = ~0;  // All bits set
                    bits_left -= 8;

                } else if (bits_left > 0) {
                    mask_[++i] = internal::createMask(bits_left);
                    bits_left = 0;
                }
            }
        } else {
            isc_throw(isc::OutOfRange,
                      "mask size of " << requested << " is invalid " <<
                      "for the given address family");
        }
    }

    // Member variables.
    uint8_t address_[IPV6_SIZE];  ///< Address in binary form
    uint8_t mask_[IPV6_SIZE];     ///< Address mask
    int     family_;              ///< Address family
};

// Some compilers seem to need this to be explicitly defined outside the class
template <typename Context>
const size_t IPCheck<Context>::IPV6_SIZE;

template <typename Context>
const size_t IPCheck<Context>::IPV4_SIZE;

} // namespace acl
} // namespace isc

#endif // IP_CHECK_H

// Local Variables:
// mode: c++
// End:
