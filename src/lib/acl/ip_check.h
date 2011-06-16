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

// The contents of this file are:
//
// 1. Free functions used by other code in the file.
// 2. Ipv4Check, the class handling the checking of IPV4 addresses.
// 3. Ipv6Check, the class handling the checking of IPV6 addresses.
// 4. IpCheck, the "external" interface and the one that should be used in
//    code implementing ACL checks.  Detailed documentation of use can be
//    found in this header for that class.

namespace isc {
namespace acl {

// Free functions

/// \brief Convert mask size to mask
///
/// Given a mask size and a data type, return a value of that data type with the
/// most significant "masksize" bits set.  For example, if the data type is an
/// uint8_t and the masksize is 3, the function would return a uint8_t holding
/// the binary value 11100000.
///
/// The function is templated on the data type of the mask.
///
/// \param masksize Size of the mask.  This must be between 0 and 8*sizeof(T).
///        An out of range exception is thrown if this is not the case.
///
/// \return Value with the most significant "masksize" bits set.

template <typename T>
T createNetmask(size_t masksize) {

    if (masksize == 0) {

        // Although a mask size of zero is invalid for the IP ACL check
        // specification, it simplifies logic elsewhere if this function is
        // allowed to handle a mask size of 0.
        return (0);

    } else if (masksize <= 8 * sizeof(T)) {

        // In the following discussion:
        //
        // w is the width of the data type T in bits.
        // m is the value of masksize, the number of most signifcant bits we
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
        // Final note: at this point in the logic, m is non-zero, so w-m < m.
        // This means 1<<(w-m) will fit into a variable of width w bits.  In
        // other words, in the expression below, no term will cause an integer
        // overflow.
        return (~((1 << (8 * sizeof(T) - masksize)) - 1));
    }

    // Mask size is too large. (Note that masksize is unsigned, so can't be
    // negative.)
    isc_throw(isc::OutOfRange, "masksize argument must be between 0 and " <<
                               8 * sizeof(T));
}

/// \brief Split IP Address
///
/// Splits an IP address (given in the form of "xxxxxx/n" or "xxxxx" into a
/// string representing the IP address and a number giving the size of the
/// network mask in bits. (In the latter case, the size of the network mask is
/// equal to the width of the data type holding the address.) An exception will
/// be thrown if the string format is invalid or if the network mask is larger
/// than a given maximum value.
///
/// N.B. This function does NOT check that the address component is a valid IP
/// address; this is done elsewhere in the address parsing process.
///
/// \param addrmask Address and/or address/mask.  The string should be passed
///                 without leading or trailing spaces.
///
/// \return Pair of (string, int) holding the address string and the mask
///         size value.  The second element is -1 if no mask was given.

std::pair<std::string, int>
splitIpAddress(const std::string& addrmask) {

    // Set the default value for the mask size
    int masksize = -1;

    // See if a mask size was given
    std::vector<std::string> components = isc::util::str::tokens(addrmask, "/");
    if (components.size() == 2) {

        // There appears to be, try converting it to a number.
        try {
            masksize = boost::lexical_cast<int>(components[1]);
        } catch (boost::bad_lexical_cast&) {
            isc_throw(isc::InvalidParameter,
                      "mask size specified in address/masksize " << addrmask <<
                      " is not valid");
        }

        // Is it in the valid range?
        if (masksize <= 0) {
            isc_throw(isc::OutOfRange,
                      "mask size specified in address/masksize " << addrmask <<
                      " must be a positive number");
        }

    } else if (components.size() > 2) {
        isc_throw(isc::InvalidParameter, "address/masksize of " <<
                  addrmask << " is not valid");
    }

    return (std::make_pair(components[0], masksize));
}



/// \brief IP Check
///
/// This class performs a match between an IP address specified in an ACL
/// (IP address, network mask and a flag indicating whether the check should
/// be for a match or for a non-match) and a given IP address.  The check
/// works for both IPV4 and IPV6 addresses.
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

    // Data type to hold the address, regardless of the address family.
    union AddressData {
        uint32_t    word[IPV6_SIZE32];      ///< Address in 32-bit words
        uint8_t     byte[IPV6_SIZE8];       ///< Address in 8-bit bytes
    };

public:
    /// \brief IPV4 Constructor
    ///
    /// Constructs an IPCheck object from a network address given as a
    /// 32-bit value in network byte order.
    ///
    /// \param address IP address to check for (as an address in network-byte
    ///        order).
    /// \param mask The network mask specified as an integer between 1 and
    ///        32. This determines the number of bits in the mask to check.
    ///        An exception will be thrown if the number is not within these
    ///        bounds.
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    IPCheck(uint32_t address = 1, int masksize = 8 * sizeof(uint32_t),
            bool inverse = false):
            address_(), netmask_(), masksize_(masksize), inverse_(inverse),
            family_(AF_INET), straddr_()
    {
        address_.word[0] = address;
        std::fill(address_.word + 1, address_.word + IPV6_SIZE32, 0);
        std::fill(netmask_.word, netmask_.word + IPV6_SIZE32, 0);
        setNetmask(masksize_);
    }

    /// \brief IPV6 Constructor
    ///
    /// Constructs an IPv6 Check object from a network address given as a
    /// 16-byte array in network-byte order.
    ///
    /// \param address IP address to check for (as an address in network-byte
    ///        order).
    /// \param mask The network mask specified as an integer between 1 and
    ///        128 This determines the number of bits in the mask to check.
    ///        An exception will be thrown if the number is not within these
    ///        bounds.
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    IPCheck(const uint8_t* address, int masksize = 8 * IPV6_SIZE8,
            bool inverse = false):
            address_(), netmask_(), masksize_(masksize), inverse_(inverse),
            family_(AF_INET6), straddr_()
    {
        std::copy(address, address + IPV6_SIZE8, address_.byte);
        std::fill(netmask_.word, netmask_.word + IPV6_SIZE32, 0);
        setNetmask(masksize_);
    }

    /// \brief String Constructor
    ///
    /// Constructs an IPv6 Check object from a network address and size of mask
    /// given as a string of the form <ip6-address>/n".
    ///
    /// \param address IP address and netmask in the form "<v6-address>/n"
    ///        (where the "/n" part is optional).
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    IPCheck(const std::string& address, bool inverse = false) :
            address_(), netmask_(), masksize_(0), inverse_(inverse),
            family_(0), straddr_(address)
    {
        // Initialize addresses.
        std::fill(address_.word, address_.word + IPV6_SIZE32, 0);
        std::fill(netmask_.word, netmask_.word + IPV6_SIZE32, 0);

        // Split the address into address part and mask.
        std::pair<std::string, int> result = splitIpAddress(address);

        // Try to convert the address.  If successful, the result is in
        // network-byte order (most significant components at lower addresses).
        family_ = AF_INET6;
        int status = inet_pton(AF_INET6, result.first.c_str(), address_.byte);
        if (status == 0) {

            // Not IPV6, try IPv4
            family_ = AF_INET;
            int status = inet_pton(AF_INET, result.first.c_str(),
                                   address_.word);

            if (status == 0) {
                isc_throw(isc::InvalidParameter, "address/masksize of " <<
                          address << " is not valid IP address");
            }
        }

        // All done, so finish initialization.
        setNetmask(result.second);
    }

    /// \brief Copy constructor
    IPCheck(const IPCheck<Context>& other) : address_(), netmask_(),
            masksize_(other.masksize_), inverse_(other.inverse_),
            family_(other.family_), straddr_(other.straddr_)
    {
        std::copy(other.address_.word, other.address_.word + IPV6_SIZE32, 
                  address_.word);
        std::copy(other.netmask_.word, other.netmask_.word + IPV6_SIZE32, 
                  netmask_.word);
    }

    /// \brief Assignment operator
    IPCheck& operator=(const IPCheck<Context>& other) {
        if (this != &other) {
            Check<Context>::operator=(other);
            std::copy(other.address_.word, other.address_.word + IPV6_SIZE32, 
                      address_.word);
            std::copy(other.netmask_.word, other.netmask_.word + IPV6_SIZE32, 
                      netmask_.word);
            masksize_ = other.masksize_;
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
    /// specialisations are provided for different argument types, so the
    /// program will fail to compile if a required specialisation is not
    /// provided.
    ///
    /// \param context Information to be matched
    virtual bool matches(const Context& context) const;

    /// \brief Estimated cost
    ///
    /// Assume that the cost of the match is linear and depends on the 
    // maximum number of comparison operations.
    /// of comparison operations.
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
        return (std::vector<uint8_t>(netmask_.byte, netmask_.byte + IPV6_SIZE8));
    }

    /// \return String passed to constructor
    std::string getStringAddress() const {
        return (straddr_);
    }

    /// \return Mask size given to constructor
    size_t getMasksize() const {
        return (masksize_);
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

        // To check that the address given matches the stored network address
        // and netmask, we check the simple condition that:
        //
        //     address_given & netmask_ == stored_address & netmask_
        //
        // The result is checked for all bytes for which there are bits set in
        // the network mask.  We stop at the first non-match (or when we run
        // out of bits in the network mask). (Note that the network mask
        // represents a contiguous set of bits.  As such, as soon as we find
        // a netmask byte of zeroes, we have run past the part of the address
        // where we need to match.
        //
        // We can optimise further by casting to a 32-bit array and checking
        // 32 bits at a time.

        bool match = true;
        for (int i = 0; match && (i < IPV6_SIZE8) && (netmask_.byte[i] != 0);
             ++i) {
             match = ((testaddr[i] & netmask_.byte[i]) ==
                      (address_.byte[i] & netmask_.byte[i]));
        }

        // As with the V4 check, return the XOR with the inverse flag.
        return (match != inverse_);
    }

    /// \brief Comparison
    ///
    /// Convenience comparison for an IPV4 address.
    ///
    /// \param testaddr Address (in network byte order).
    ///
    /// \return true if the address matches, false if it does not.
    virtual bool compare(const uint32_t testaddr) const {
        return (((testaddr & netmask_.word[0]) ==
                 (address_.word[0] & netmask_.word[0])) != inverse_);
    }


    /// \brief Set Network Mask
    ///
    /// Sets up the network mask from the mask size.  This involves setting
    /// an individual mask in each byte of the network mask.
    ///
    /// The actual allowed value of the mask size depends on the address
    /// family.
    ///
    /// \param requested Requested mask size.  If negative, the maximum for
    ///        the address family is assumed.
    void setNetmask(int requested) {

        // Set the maximum mask size allowed.
        int maxmask = 8 * ((family_ == AF_INET) ? sizeof(uint32_t) : IPV6_SIZE8);

        // Adjust if negative.
        if (requested < 0) {
            requested = maxmask;
        }

        // Validate that the mask is valid.
        if ((requested >= 1) && (requested <= maxmask)) {
            masksize_ = requested;

            // The netmask array was initialized to zero in the constructor,
            // but in debug mode we can check that.
            assert(std::find_if(netmask_.word, netmask_.word + IPV6_SIZE32,
                   std::bind1st(std::not_equal_to<uint32_t>(), 0)) ==
                   netmask_.word + IPV6_SIZE32);

            // Loop, setting the bits in the set of mask bytes until all the
            // specified bits have been used up.  As both IPV4 and IPV6
            // addressees are stored in network-byte order, this works in
            // both cases.
            size_t bits_left = masksize_;   // Bits remaining to set
            int i = -1;
            while (bits_left > 0) {
                if (bits_left >= 8) {
                    netmask_.byte[++i] = ~0;  // All bits set
                    bits_left -= 8;

                } else if (bits_left > 0) {
                    netmask_.byte[++i] = createNetmask<uint8_t>(bits_left);
                    bits_left = 0;

                }
            }
        } else {
            isc_throw(isc::OutOfRange,
                      "mask size of " << masksize_ << " is invalid " <<
                      "for the data type");
        }
    }

    // Member variables

    AddressData address_;   ///< Address in binary form
    AddressData netmask_;   ///< Network mask
    size_t      masksize_;  ///< Mask size passed to constructor
    bool        inverse_;   ///< Test for equality or inequality
    int         family_;    ///< Address family
    std::string straddr_;   ///< Copy of constructor address string
};

} // namespace acl
} // namespace isc

#endif // __IP_CHECK_H
