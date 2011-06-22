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

#ifndef __IP_CHECK_H
#define __IP_CHECK_H

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/scoped_ptr.hpp>

#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <acl/check.h>
#include <exceptions/exceptions.h>

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
/// data type is an uint8_t and the p[refix length is 3, the function would
/// return a uint8_t holding the binary value 11100000.  This value is used as
/// a mask in the address checks.
///
/// The function is templated on the data type of the mask.
///
/// \param prefixlen number of bits to be set in the mask.  This must be
///        between 0 and 8*sizeof(T).
///
/// \return Value with the most significant "prefixlen" bits set.
///
/// \exception OutOfRange prefixlen is too large for the data type.

template <typename T>
T createMask(size_t prefixlen) {

    if (prefixlen == 0) {
        return (0);

    } else if (prefixlen <= 8 * sizeof(T)) {

        // In the following discussion:
        //
        // w is the width of the data type T in bits.
        // m is the value of prefixlen, the number of most signifcant bits we
        // want to set.
        // ** is exponentiation (i.e. 2**n is 2 raised to the power of n).
        //
        // We note that the value of 2**m - 1 gives a value with the least
        // significant m bits set.  For a data type of width w, this means that
        // the most signficant (w-m) bits clear.
        //
        // Hence the value 2**(w-m) - 1 gives a result with the least signficant
        // w-m bits set and the most significant m bits clear.  The 1's
        // complement of this value gives is the result we want.
        //
        // Final note: at this point in the logic, m is non-zero, so w-m < w.
        // This means 1<<(w-m) will fit into a variable of width w bits.  In
        // other words, in the expression below, no term will cause an integer
        // overflow.
        return (~((1 << (8 * sizeof(T) - prefixlen)) - 1));
    }

    // Mask size is too large. (Note that prefixlen is unsigned, so can't be
    // negative.)
    isc_throw(isc::OutOfRange, "prefixlen argument must be between 0 and " <<
                               8 * sizeof(T));
}

/// \brief Split IP Address Prefix
///
/// Splits an IP address prefix (given in the form of "xxxxxx/n" or "xxxxx" into
/// a string representing the IP address and a number giving the length of the
/// prefix. (In the latter case, the prefix is equal in length to the width in
/// width in bits of the data type holding the address.) An exception will
/// be thrown if the string format is invalid or if the prefix length is
/// invalid.
///
/// N.B. This function does NOT check that the address component is a valid IP
/// address; this is done elsewhere in the address parsing process.
///
/// \param ipprefix Address or address prefix.  The string should be passed
///                 without leading or trailing spaces.
///
/// \return Pair of (string, int) holding the address string and the prefix
///         length.  The second element is -1 if no prefix was given.
// definitions and te/
/// \exception InvalidParameter Address prefix not of the expected syntax

std::pair<std::string, int>
splitIPAddress(const std::string& ipprefix);

} // namespace internal



/// \brief IP Check
///
/// This class performs a match between an IP address prefix specified in an ACL
/// and a given IP address.  The check works for both IPV4 and IPV6 addresses.
///
/// The class is templated on the type of a context structure passed to the
/// matches() method, and a template specialisation for that method must be
/// supplied for the class to be used.

template <typename Context>
class IPCheck : public Check<Context> {
private:
    // Size of uint8_t array to holds different address types
    static const size_t IPV6_SIZE = sizeof(struct in6_addr);
    static const size_t IPV4_SIZE = sizeof(struct in_addr);

public:
    /// \brief Default Constructor
    ///
    /// Constructs an empty IPCheck object.  The address family returned will
    /// be zero.
    IPCheck() : address_(), mask_(), family_(0)
    {}

    /// \brief IPV4 Constructor
    ///
    /// Constructs an IPCheck object from a network address given as a
    /// 32-bit value in network byte order and a prefix length.
    ///
    /// \param address IP address to check for (as an address in host-byte
    ///        order).  N.B.  Unlike the IPV6 constructor, this is in host
    ///        byte order.
    /// \param prefixlen The prefix length specified as an integer between 0 and
    ///        32. This determines the number of bits of the address to check.
    ///        (A value of zero imples match all IPV4 addresses.)
    IPCheck(uint32_t address, int prefixlen = 8 * IPV4_SIZE) :
            address_(IPV4_SIZE), mask_(), family_(AF_INET)
    {
        // The address is stored in network-byte order, so the 
        // the address passed should be stored at the lowest address in
        // the array.
        address_[3] = static_cast<uint8_t>((address      ) & 0xff);
        address_[2] = static_cast<uint8_t>((address >>  8) & 0xff);
        address_[1] = static_cast<uint8_t>((address >> 16) & 0xff);
        address_[0] = static_cast<uint8_t>((address >> 24) & 0xff);

        setMask(prefixlen);
    }

    /// \brief IPV6 Constructor
    ///
    /// Constructs an IPv6 Check object from a network address given as a
    /// 16-byte array in network-byte order and a prefix length.
    ///
    /// \param address IP address to check for (as an address in network-byte
    ///        order).
    /// \param mask The network mask specified as an integer between 1 and
    ///        128 This determines the number of bits in the mask to check.
    IPCheck(const uint8_t* address, int prefixlen = 8 * IPV6_SIZE) :
            address_(address, address + IPV6_SIZE), mask_(), family_(AF_INET6)
    {

        setMask(prefixlen);
    }

    /// \brief String Constructor
    ///
    /// Constructs an IP Check object from an address or address prefix in the
    /// form <ip-address>/n".
    /// 
    /// Also allowed are the special keywords "any4" and "any6", which match
    /// any IPV4 or IPV6 address.  These must be specified exactly as-is
    /// (i.e. lowercase, with no leading or trailing spaces).
    ///
    /// \param addrprfx IP address prefix in the form "<ip-address>/n"
    ///        (where the "/n" part is optional and should be valid for the
    ///        address).  If "n" is specified as zero, the match is for any
    ///        address in that address family.  The address can also be
    ///        given as "any4" or "any6".
    IPCheck(const std::string& addrprfx) : address_(), mask_(), family_(0)
    {
        // Check for special cases first.
        if (addrprfx == "any4") {
            family_ = AF_INET;

        } else if (addrprfx == "any6") {
            family_ = AF_INET6;

        } else {

            // General address prefix.  Split into address part and prefix
            // length.
            std::pair<std::string, int> result =
                internal::splitIPAddress(addrprfx);

            // Try to convert the address.  If successful, the result is in
            // network-byte order (most significant components at lower
            // addresses).
            BOOST_STATIC_ASSERT(IPV6_SIZE > IPV4_SIZE);
            uint8_t address_bytes[IPV6_SIZE];
            int status = inet_pton(AF_INET6, result.first.c_str(),
                                   address_bytes);
            if (status == 1) {
                // It was an IPV6 address, copy into the address store
                std::copy(address_bytes, address_bytes + IPV6_SIZE,
                          std::back_inserter(address_));
                family_ = AF_INET6;

            } else {
                // Not IPV6, try IPv4
                int status = inet_pton(AF_INET, result.first.c_str(),
                                       address_bytes);
                if (status == 1) {
                    std::copy(address_bytes, address_bytes + IPV4_SIZE,
                              std::back_inserter(address_));
                    family_ = AF_INET;

                } else {
                    isc_throw(isc::InvalidParameter, "address prefix of " <<
                              result.first << " is a not valid");
                }
            }

            // All done, so set the mask used in checking.
            setMask(result.second);
        }
    }

    /// \brief Destructor
    virtual ~IPCheck() {}

    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here.  Different
    /// specialisations must be  provided for different argument types, and the
    /// program will fail to compile if a required specialisation is not
    /// provided.
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
        return (address_);
    }

    /// \return Network mask applied to match
    std::vector<uint8_t> getMask() const {
        return (mask_);
    }

    /// \return Prefix length of the match
    size_t getPrefixlen() const {
        // Work this out by shifting bits out of the mask
        size_t count = 0;
        int index = 0;
        for (size_t i = 0; i < mask_.size(); ++i) {
            if (mask_[i] == 0xff) {
                // Full byte, 8 bit set
                count += 8;

            } else if (mask_[i] != 0) {
                // Partial set, count the bits
                uint8_t byte = mask_[i];
                for (int i = 0; i < 8 * sizeof(uint8_t); ++i) {
                    count += byte & 0x01;   // Add one if the bit is set
                    byte >>= 1;             // Go for next bit
                }

                // There won't be any more bits set after this, so exit
                break;
            }
        }
        return (count);
    }

    /// \return Address family
    int getFamily() const {
        // Check that a family_  value of 0 does not imply IPV4 or IPV6.
        // This avoids confusion if getFamily() is called on an object that
        // has been initialized by default.
        BOOST_STATIC_ASSERT(AF_INET != 0);
        BOOST_STATIC_ASSERT(AF_INET6 != 0);

        return (family_);
    }
    ///@}

private:
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
        // in the mask). (Note that the mask represents a contiguous set of
        // bits.  As such, as soon as we find a mask byte of zeroes, we have run
        // past the part of the address where we need to match.
        //
        // Note that if the passed address was any4 or any6, we rely on the
        // fact that the size of address_ and mask_ are zero - the loop will
        // terminate before the first iteration.

        bool match = true;
        for (int i = 0; match && (i < address_.size()) &&
                       (mask_[i] != 0); ++i) {
             match = ((testaddr[i] & mask_[i]) == (address_[i] & mask_[i]));
        }
        return (match);
    }


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

        mask_.clear();
        mask_.resize((family_ == AF_INET) ? IPV4_SIZE : IPV6_SIZE);

        // Set the maximum number of bits allowed in the mask.
        int maxmask = 8 * (mask_.size());
        if (requested < 0) {
            requested = maxmask;
        }

        // Validate that the mask is valid.
        if (requested <= maxmask) {

            // Loop, setting the bits in the set of mask bytes until all the
            // specified bits have been used up.  As both IPV4 and IPV6
            // addresses are stored in network-byte order, this works in
            // both cases.
            size_t bits_left = requested;   // Bits remaining to set
            int i = -1;
            while (bits_left > 0) {
                if (bits_left >= 8) {
                    mask_[++i] = ~0;  // All bits set
                    bits_left -= 8;

                } else if (bits_left > 0) {
                    mask_[++i] = internal::createMask<uint8_t>(bits_left);
                    bits_left = 0;

                }
            }
        } else {
            isc_throw(isc::OutOfRange,
                      "mask size of " << requested << " is invalid " <<
                      "for the givem address");
        }
    }

    // Member variables

    std::vector<uint8_t> address_;  ///< Address in binary form
    std::vector<uint8_t> mask_;     ///< Address mask
    int         family_;            ///< Address family
};

} // namespace acl
} // namespace isc

#endif // __IP_CHECK_H
