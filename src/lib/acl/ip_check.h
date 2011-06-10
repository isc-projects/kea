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
#include <vector>

#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <acl/check.h>
#include <util/strutil.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace acl {

/// \brief Convert Mask Size to Mask
///
/// Given a mask size and a data type, return a value of that data type with the
/// most significant maasksize bits set.  For example, if the data type is an
/// unsigned either-bit byte and the masksize is 3, the function would return
/// an eight-bit byte with the binary value 11100000.
///
/// This is a templated function.  The template parameter must be a signed type.
///
/// \param masksize Size of the mask.  This must be between 1 and sizeof(T).
///        An out of range exception is thrown if this is not the case.
///
/// \return Value with the most significant "masksize" bits set.

template <typename T>
T createNetmask(size_t masksize) {

    if ((masksize > 0) && (masksize <= 8 * sizeof(T))) {

        // To explain the logic, consider a single 4-bit word.  The masksize in
        // this case can be between 1 and 4.  The following table has the
        // following columns:
        //
        // Mask size (m): number of contiguous bits set
        //
        // Low value (lo): unsigned value of 4-bit word with the least-
        // significant m contiguous bits set.
        //
        // High value (hi): unsigned value of 4-bit word with the most-
        // significant m contiguous bits set.
        //
        //    m   lo   hi
        //    1    1    8
        //    2    3   12
        //    3    7   14
        //    4   15   15
        //
        // Clearly the low value is equal to (2**m - 1) (using ** to indicate
        // exponentiation).  It takes a little thought to see that the high
        // value is equal to 2**4 - 2**(4-m).  Unfortunately, this formula will
        // overflow as the intermediate value 2 << sizeof(T) will overflow in an
        // element of type T.
        //
        // However, another way of looking it is that to set the most signifcant
        // m bits, we set all bits and clear the least-significant 4-m bits.  If
        // T is a signed value, we can set all bits by setting it to -1.  If m
        // is 4, we omit clearing any bits, otherwise we clear the bits
        // represented by the bit pattern 2**(3-m) - 1.  (The value 2**(3-m)
        // will be greater than 0 and within the range of an unsigned data
        // type of the same size as T.  So it should not overflow.)
        //
        // Therefore we proceed on the assumption that T is signed
        T mask = -1;
        if (masksize < 8 * sizeof(T)) {
            mask &= ~((2 << (8 * sizeof(T) - 1 - masksize)) - 1);
        }

        return (mask);
    }

    // Invalid mask size
    isc_throw(isc::OutOfRange, "mask size of " << masksize << " is invalid " <<
                               "for the data type which is " << sizeof(T) <<
                               " bytes long");
}

/// \brief IP V4 Check
///
/// This class performs a match between an IPv4 address specified in an ACL
/// (IP address, network mask and a flag indicating whether the check should
/// be for a match or for no-match) and a given IPv4 address.
///
/// \param Context Structure holding address to be matched.

template <typename Context> class Ipv4Check : public Check<Context> {
public:

    /// \brief Constructor
    ///
    /// \param address IP address to check for (as an address in host-byte
    ///        order).
    /// \param mask The network mask specified as an integer between 1 and
    ///        32 This determines the number of bits in the mask to check.
    ///        An exception will be thrown if the number is not within these
    ///        bounds.
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    Ipv4Check(uint32_t address, size_t masksize = 32, bool inverse = false) :
        address_(address), masksize_(masksize), netmask_(0), inverse_(inverse)
    {
        init();
    }

    /// \brief Constructor
    ///
    /// \param address IP address and netmask in the form "a.b.c.d/n" (where
    ///        the "/n" part is optional.
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    Ipv4Check(const std::string& address, bool inverse = false) :
        address_(0), masksize_(32), netmask_(0), inverse_(inverse)
    {
        // See if there is a netmask.
        std::vector<std::string> components =
            isc::util::str::tokens(address, "/");
        if (components.size() == 2) {

            // Yes there is, convert to a mask
            try {
                masksize_ = boost::lexical_cast<size_t>(components[1]);
            } catch (boost::bad_lexical_cast&) {
                isc_throw(isc::InvalidParameter,
                          "mask specified in address/mask " << address <<
                          " is not valid");
            }
        } else if (components.size() > 2) {
            isc_throw(isc::InvalidParameter, "address/mask of " <<
                      address << " is not valid");
        }

        // Try to convert the address.
        int result = inet_pton(AF_INET, components[0].c_str(), &address_);
        if (result == 0) {
            isc_throw(isc::InvalidParameter, "address/mask of " <<
                      address << " is not valid");
        }
        address_ = ntohl(address_);

        // All done, so finish initialization.
        init();
    }

    /// \brief Destructor
    virtual ~Ipv4Check() {}

    /// \brief Comparison
    ///
    /// This is the actual comparison function that checks the IP address passed
    /// to this class with the matching information in the class itself.
    ///
    /// \param address Address to match against the check condition in the
    ///        class.
    ///
    /// \return true if the address matches, false if it does not.
    virtual bool compare(uint32_t address) {

        // To check that the address given matches the stored network address
        // and netmask, we check the simple condition that:
        //
        //     address_given & netmask_ == maskaddr_.
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
        // ... which is an XOR function.

        return (((address & netmask_) == maskaddr_) ^ inverse_);
    }

    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here.  Different
    /// specialisations are provided for different argument types, so the
    /// link will fail if used for a type for which no match is provided.
    ///
    /// \param context Information to be matched
    virtual bool matches(const Context& context) const {return false; }

    /// \brief Estimated cost
    ///
    /// Assume that the cost of the match is linear and depends on the number
    /// of compariosn operations.
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

private:
    /// \brief Initialization
    ///
    /// Common code shared by all constructors to set up the net mask and
    /// addresses.
    void init() {
        // Validate that the mask is valid.
        if ((masksize_ >= 1) && (masksize_ <= 32)) {

            // Calculate the bitmask given by the number of bits.
            netmask_ = isc::acl::createNetmask<int32_t>(masksize_);

            // For speed, store the masked off address.   This saves a mask
            // operation every time the value is checked.
            maskaddr_ = address_ & netmask_;
        } else {
            isc_throw(isc::OutOfRange,
                      "mask size of " << masksize_ << " is invalid " <<
                      "for the data type which is " << sizeof(uint32_t) <<
                      " bytes long");
        }
    }

    uint32_t    address_;   ///< IPv4 address
    uint32_t    maskaddr_;  ///< Masked IPV4 address
    size_t      masksize_;  ///< Mask size passed to constructor
    int32_t     netmask_;   ///< Network mask applied to match
    bool        inverse_;   ///< test for equality or inequality
};

} // namespace acl
} // namespace isc

#endif // __IP_CHECK_H
