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

#include <cassert>
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
#include <util/strutil.h>
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
/// \param addrmask Address or address prefix.  The string should be passed
///                 without leading or trailing spaces.
///
/// \return Pair of (string, int) holding the address string and the prefix
///         length.  The second element is -1 if no prefix was given.
///
/// \exception InvalidParameter Address prefix not of the expected syntax

std::pair<std::string, int>
splitIPAddress(const std::string& prefix) {

    // Set the default value for the prefix length.  As the type of the address
    // is not known at the point this function is called, the maximum
    // allowable value is also not known.  And the value of 0 is reserved for
    // a "match any address" match.
    int prefix_size = -1;

    // Split string into its components - an address and a prefix length.
    // We initialize by assuming that there is no slash in the string given.
    std::string address = prefix;
    std::string prefixlen = "";

    // Parse the string given after stripping leading and trailing spaces.
    std::string mod_prefix = isc::util::str::trim(prefix);
    size_t slashpos = mod_prefix.find('/');
    if ((mod_prefix.size() == 0) || (slashpos == 0) ||
        (slashpos == (mod_prefix.size() - 1))) {
        // Nothing in prefix, or it starts with or ends with a slash.
        isc_throw(isc::InvalidParameter, "address prefix of " << prefix <<
                                         " is not valid");

    } else if (slashpos != std::string::npos) {
        // There is a slash somewhere in the string, split the string on it.
        // Don't worry about multiple slashes - if there are some, they will
        // appear in the prefixlen segment and will be detected when an attempt
        // is made to convert it to a number.
        address = mod_prefix.substr(0, slashpos);
        prefixlen = mod_prefix.substr(slashpos + 1);
    }

    // If there is a prefixlength, attempt to convert it.
    if (!prefixlen.empty()) {
        try {
            prefix_size = boost::lexical_cast<int>(prefixlen);
            if (prefix_size < 0) {
                isc_throw(isc::InvalidParameter, "address prefix of " <<
                          prefix << " is not valid");
            }
        } catch (boost::bad_lexical_cast&) {
            isc_throw(isc::InvalidParameter, "prefix length of " << prefixlen <<
                                             " is not valid");
        }
    }

    return (std::make_pair(address, prefix_size));
}

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
    // Size of uint8_t array to hold an IPV6 address, and size of a 32-bit word
    // equivalent.
    static const size_t IPV6_SIZE8 = sizeof(struct in6_addr);
    static const size_t IPV6_SIZE32 = IPV6_SIZE8 / 4;

    // Data type to hold the address, regardless of the address family.  The
    // union allows an IPV4 address to be treated as a sequence of bytes when
    // necessary.
    union AddressData {
        uint32_t    word[IPV6_SIZE32];      ///< Address in 32-bit words
        uint8_t     byte[IPV6_SIZE8];       ///< Address in 8-bit bytes
    };

public:
    /// \brief Default Constructor
    ///
    /// Constructs an empty IPCheck object.  The address family returned will
    /// be zero.
    IPCheck() : address_(), mask_(), prefixlen_(0), inverse_(false),
                family_(0), straddr_()
    {
        std::fill(address_.word, address_.word + IPV6_SIZE32, 0);
        std::fill(mask_.word, mask_.word + IPV6_SIZE32, 0);
    }

    /// \brief IPV4 Constructor
    ///
    /// Constructs an IPCheck object from a network address given as a
    /// 32-bit value in network byte order and a prefix length.
    ///
    /// \param address IP address to check for (as an address in network-byte
    ///        order).
    /// \param prefixlen The prefix length specified as an integer between 0 and
    ///        32. This determines the number of bits of the address to check.
    ///        (A value of zero imples match all IPV4 addresses.)
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    IPCheck(uint32_t address, int prefixlen = 8 * sizeof(uint32_t),
            bool inverse = false):
            address_(), mask_(), prefixlen_(prefixlen), inverse_(inverse),
            family_(AF_INET), straddr_()
    {
        address_.word[0] = address;
        std::fill(address_.word + 1, address_.word + IPV6_SIZE32, 0);
        std::fill(mask_.word, mask_.word + IPV6_SIZE32, 0);
        setMask(prefixlen_);
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
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    IPCheck(const uint8_t* address, int prefixlen = 8 * IPV6_SIZE8,
            bool inverse = false):
            address_(), mask_(), prefixlen_(prefixlen), inverse_(inverse),
            family_(AF_INET6), straddr_()
    {
        std::copy(address, address + IPV6_SIZE8, address_.byte);
        std::fill(mask_.word, mask_.word + IPV6_SIZE32, 0);
        setMask(prefixlen_);
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
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    IPCheck(const std::string& addrprfx, bool inverse = false) :
            address_(), mask_(), prefixlen_(0), inverse_(inverse),
            family_(0), straddr_(addrprfx)
    {
        // Initialize.
        std::fill(address_.word, address_.word + IPV6_SIZE32, 0);
        std::fill(mask_.word, mask_.word + IPV6_SIZE32, 0);

        // Check for special cases first
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
            family_ = AF_INET6;
            int status = inet_pton(AF_INET6, result.first.c_str(),
                                   address_.byte);
            if (status == 0) {

                // Not IPV6, try IPv4
                family_ = AF_INET;
                int status = inet_pton(AF_INET, result.first.c_str(),
                                       address_.word);
                if (status == 0) {
                    isc_throw(isc::InvalidParameter, "address prefix of " <<
                              result.first << " is a not valid");
                }
            }

            // All done, so set the mask used in checking.
            setMask(result.second);
        }
    }

    /// \brief Copy constructor
    ///
    /// \param other Object from which the copy is being constructed.
    IPCheck(const IPCheck<Context>& other) : address_(), mask_(),
            prefixlen_(other.prefixlen_), inverse_(other.inverse_),
            family_(other.family_), straddr_(other.straddr_)
    {
        std::copy(other.address_.word, other.address_.word + IPV6_SIZE32,
                  address_.word);
        std::copy(other.mask_.word, other.mask_.word + IPV6_SIZE32,
                  mask_.word);
    }

    /// \brief Assignment operator
    ///
    /// \param other Source of the assignment.
    ///
    /// \return Reference to current object.
    IPCheck& operator=(const IPCheck<Context>& other) {
        if (this != &other) {
            Check<Context>::operator=(other);
            std::copy(other.address_.word, other.address_.word + IPV6_SIZE32,
                      address_.word);
            std::copy(other.mask_.word, other.mask_.word + IPV6_SIZE32,
                      mask_.word);
            prefixlen_ = other.prefixlen_;
            inverse_ = other.inverse_;
            family_ = other.family_;
            straddr_ = other.straddr_;
        }
        return (*this);
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
        return ((family_ == AF_INET) ? 1 : IPV6_SIZE32);
    }

    ///@{
    /// Access methods - mainly for testing

    /// \return Stored IP address
    std::vector<uint8_t> getAddress() const {
        return (std::vector<uint8_t>(address_.byte, address_.byte + IPV6_SIZE8));
    }

    /// \return Network mask applied to match
    std::vector<uint8_t> getNetmask() const {
        return (std::vector<uint8_t>(mask_.byte, mask_.byte + IPV6_SIZE8));
    }

    /// \return String passed to constructor
    std::string getStringAddress() const {
        return (straddr_);
    }

    /// \return Prefix length of the match
    size_t getPrefixlen() const {
        return (prefixlen_);
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

    /// \return Setting of inverse flag
    bool getInverse() const {
        return (inverse_);
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
    ///                 be IPV6_SIZE8 bytes long.
    ///
    /// \return true if the address matches, false if it does not.
    virtual bool compare(const uint8_t* testaddr) const {

        if (prefixlen_ != 0) {

            // To check that the address given matches the stored network
            // address and mask, we check the simple condition that:
            //
            //     address_given & mask_ == stored_address & mask_
            //
            // The result is checked for all bytes for which there are bits set
            // in the mask.  We stop at the first non-match (or when we run
            // out of bits in the mask). (Note that the mask represents a
            // contiguous set of bits.  As such, as soon as we find a mask byte
            // of zeroes, we have run past the part of the address where we need
            // to match.
            //
            // We can optimise further by casting to a 32-bit array and checking
            // 32 bits at a time.

            bool match = true;
            for (int i = 0; match && (i < IPV6_SIZE8) && (mask_.byte[i] != 0);
                 ++i) {
                 match = ((testaddr[i] & mask_.byte[i]) ==
                          (address_.byte[i] & mask_.byte[i]));
            }

            // As with the V4 check, return the XOR with the inverse flag.
            return (match != inverse_);
        }

        // A prefix length of 0 is an unconditional match.
        return (true);
    }

    /// \brief Comparison
    ///
    /// Convenience comparison for an IPV4 address.
    ///
    /// \param testaddr Address (in network byte order) to test against the
    ///        check condition in the class.
    ///
    /// \return true if the address matches, false if it does not.
    virtual bool compare(const uint32_t testaddr) const {
        if (prefixlen_ != 0) {
            return (((testaddr & mask_.word[0]) ==
                     (address_.word[0] & mask_.word[0])) != inverse_);
        }

        // A prefix length of 0 is an unconditional match.
        return (true);
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

        // Set the maximum mask size allowed.
        int maxmask = 8 * ((family_ == AF_INET) ? sizeof(uint32_t) : IPV6_SIZE8);
        if (requested < 0) {
            requested = maxmask;
        }

        // Validate that the mask is valid.
        if (requested <= maxmask) {
            prefixlen_ = requested;

            // The mask array was initialized to zero in the constructor,
            // but as an addition check, assert that this is so.
            assert(std::find_if(mask_.word, mask_.word + IPV6_SIZE32,
                   std::bind1st(std::not_equal_to<uint32_t>(), 0)) ==
                   mask_.word + IPV6_SIZE32);

            // Loop, setting the bits in the set of mask bytes until all the
            // specified bits have been used up.  As both IPV4 and IPV6
            // addresses are stored in network-byte order, this works in
            // both cases.
            size_t bits_left = prefixlen_;   // Bits remaining to set
            int i = -1;
            while (bits_left > 0) {
                if (bits_left >= 8) {
                    mask_.byte[++i] = ~0;  // All bits set
                    bits_left -= 8;

                } else if (bits_left > 0) {
                    mask_.byte[++i] = internal::createMask<uint8_t>(bits_left);
                    bits_left = 0;

                }
            }
        } else {
            isc_throw(isc::OutOfRange,
                      "mask size of " << prefixlen_ << " is invalid " <<
                      "for the givem address");
        }
    }

    // Member variables

    AddressData address_;   ///< Address in binary form
    AddressData mask_;      ///< Address mask
    size_t      prefixlen_; ///< Mask size passed to constructor
    bool        inverse_;   ///< Test for equality or inequality
    int         family_;    ///< Address family
    std::string straddr_;   ///< Copy of constructor address string
};

} // namespace acl
} // namespace isc

#endif // __IP_CHECK_H
