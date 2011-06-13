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

#include <boost/lexical_cast.hpp>
#include <utility>
#include <vector>

#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <acl/check.h>
#include <util/strutil.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace acl {

// Free functions

/// \brief Convert Mask Size to Mask
///
/// Given a mask size and a data type, return a value of that data type with the
/// most significant masksize bits set.  For example, if the data type is an
/// unsigned eight-bit byte and the masksize is 3, the function would return
/// an unsigned eight-bit byte with the binary value 11100000.
///
/// The function is templated on the data type of the mask.
///
/// \param masksize Size of the mask.  This must be between 1 and 8*sizeof(T).
///        An out of range exception is thrown if this is not the case.
///
/// \return Value with the most significant "masksize" bits set.

template <typename T>
T createNetmask(size_t masksize) {

    if ((masksize > 0) && (masksize <= 8 * sizeof(T))) {

        // In the following discussion:
        //
        // w is the width of the data type T in bits
        // m is the value of masksize, the number of most signifcant bits we
        // want to set.
        //
        // We note that the value of 2**m - 1 gives a result with the least
        // significant m bits set and the most signficant (w-m) bits clear.
        //
        // Hence the value 2**(w-m) - 1 gives a result with the least signficant
        // w-m bits set and the most significant m bits clear.
        //
        // The 1's complement of this value gives is the result we want.
        //
        // Final note:  masksize is non-zero, so we are assured that no term in 
        // the expression below will overflow.

        return (~((1 << (8 * sizeof(T) - masksize)) - 1));
    }

    isc_throw(isc::OutOfRange, "mask size must be between 1 and " <<
                               8 * sizeof(T));
}

/// \brief Split IP Address
///
/// Splits an IP address (given in the form of "xxxxxx/n" or "xxxxx" into a
/// string representing the IP address and a number giving the size of the
/// network mask in bits.
///
/// An exception will be thrown if the string format is invalid.  N.B. This
/// does NOT check that the address component is a valid IP address - only that
/// some string is present.
///
/// \param addrmask Address and/or address/mask.  The string should be passed
///                 without leading or trailing spaces.
/// \param defmask  Default value of the mask size, used if no mask is given.
/// \param maxmask  Maximum valid value of the mask size.
///
/// \return Pair of (string, uint32) holding the address string and the mask
///         size value.

std::pair<std::string, uint32_t>
splitIpAddress(const std::string& addrmask, uint32_t defmask, uint32_t maxmask){

    uint32_t masksize = defmask;

    // See if a mask size was given
    std::vector<std::string> components = isc::util::str::tokens(addrmask, "/");
    if (components.size() == 2) {

        // There appears to be, try converting it to a number.
        try {
            masksize = boost::lexical_cast<size_t>(components[1]);
        } catch (boost::bad_lexical_cast&) {
            isc_throw(isc::InvalidParameter,
                      "mask size specified in address/masksize " << addrmask <<
                      " is not valid");
        }

        // Is it in the valid range?
        if ((masksize == 0) || (masksize > maxmask)) {
            isc_throw(isc::OutOfRange,
                      "mask size specified in address/masksize " << addrmask <<
                      " must be in range 1 <= masksize <= " << maxmask);
        }

    } else if (components.size() > 2) {
        isc_throw(isc::InvalidParameter, "address/masksize of " <<
                  addrmask << " is not valid");
    }

    return (std::make_pair(components[0], masksize));
}


/// \brief IPV4 Check
///
/// This class performs a match between an IPv4 address specified in an ACL
/// (IP address, network mask and a flag indicating whether the check should
/// be for a match or for a non-match) and a given IP address.
///
/// \param Context Structure holding address to be matched.

template <typename Context>
class Ipv4Check : public Check<Context> {
public:
    /// \brief IPV4 Constructor
    ///
    /// Constructs an IPv4 Check object from a network address given as a
    /// 32-bit value in network byte order.
    ///
    /// \param address IP address to check for (as an address in network-byte
    ///        order).
    /// \param mask The network mask specified as an integer between 1 and
    ///        32 This determines the number of bits in the mask to check.
    ///        An exception will be thrown if the number is not within these
    ///        bounds.
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    Ipv4Check(uint32_t address = 1, size_t masksize = 32, bool inverse = false):
        address_(address), masksize_(masksize), inverse_(inverse), netmask_(0)
    {
        setNetmask();
    }



    /// \brief String Constructor
    ///
    /// Constructs an IPv4 Check object from a network address and size of mask
    /// given as a string of the form "a.b.c.d/n", where the "/n" part is
    /// optional.
    ///
    /// \param address IP address and netmask in the form "a.b.c.d/n" (where
    ///        the "/n" part is optional).
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    Ipv4Check(const std::string& address, bool inverse = false) :
        address_(1), masksize_(32), inverse_(inverse), netmask_(0)
    {
        // Split the address into address part and mask.
        std::pair<std::string, uint32_t> result =
            splitIpAddress(address, 8 * sizeof(uint32_t), 8 * sizeof(uint32_t));

        // Try to convert the address.
        int status = inet_pton(AF_INET, result.first.c_str(), &address_);
        if (status == 0) {
            isc_throw(isc::InvalidParameter, "address/masksize of " <<
                      address << " is not valid IPV4 address");
        }

        // All done, so finish initialization.
        masksize_ = result.second;
        setNetmask();
    }



    /// \brief Destructor
    virtual ~Ipv4Check() {}



    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here.  Different
    /// specialisations are provided for different argument types, so the
    /// link will fail if used for a type for which no match is provided.
    ///
    /// \param context Information to be matched
    virtual bool matches(const Context& context) const = 0;



    /// \brief Estimated cost
    ///
    /// Assume that the cost of the match is linear and depends on the number
    /// of comparison operations.
    virtual unsigned cost() const {
        return (1);             // Single check on a 32-bit word
    }



    ///@{
    /// Access methods - mainly for testing

    /// \return Stored IP address
    uint32_t getAddress() const {
        return (address_);
    }

    /// \return Network mask applied to match
    const uint32_t getNetmask() const {
        return (netmask_);
    }

    /// \return Mask size given to constructor
    size_t getMasksize() const {
        return (masksize_);
    }

    /// \return Setting of inverse flag
    bool getInverse() {
        return (inverse_);
    }
    ///@}

    /// \brief Set Network Mask
    ///
    /// Sets up the network mask from the mask size.
    void setNetmask() {
        // Validate that the mask is valid.
        if ((masksize_ >= 1) && (masksize_ <=  8 * sizeof(uint32_t))) {

            // Calculate the bitmask given by the number of bits.
            netmask_ = isc::acl::createNetmask<uint32_t>(masksize_);

            // ... and convert to network byte order.
            netmask_ = htonl(netmask_);

        } else {
            isc_throw(isc::OutOfRange,
                      "mask size of " << masksize_ << " is invalid " <<
                      "for the data type which is " << sizeof(uint32_t) <<
                      " bytes long");
        }
    }

    /// \brief Comparison
    ///
    /// This is the actual comparison function that checks the IP address passed
    /// to this class with the matching information in the class itself.  It is
    /// expected to be called from matches().
    ///
    /// \param address Address (in network byte order) to match against the
    ///                check condition in the class.
    ///
    /// \return true if the address matches, false if it does not.
    virtual bool compare(uint32_t address) const {

        // To check that the address given matches the stored network address
        // and netmask, we check the simple condition that:
        //
        //     address_given & netmask_ == stored_address & netmask_
        //
        // However, we must return the negation of the result if inverse_ is
        // set.  This leads to the truth table:
        //
        // Result inverse_ Return
        // false  false    false
        // false  true     true
        // true   false    true
        // true   true     false
        //
        // ... which is an XOR function.  Although there is no explicit logical
        /// XOR operator, with two bool arguments, "!=" serves that function.

        return (((address & netmask_) == (address_ & netmask_)) != inverse_);
    }

    // Member variables

    uint32_t    address_;   ///< IPv4 address
    size_t      masksize_;  ///< Mask size passed to constructor
    bool        inverse_;   ///< test for equality or inequality
    uint32_t    netmask_;   ///< Network mask applied to match

};

} // namespace acl
} // namespace isc

#endif // __IP_CHECK_H
