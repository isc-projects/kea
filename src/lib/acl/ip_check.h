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
#include <iterator>
#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

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
/// \param masksize Size of the mask.  This must be between 0 and 8*sizeof(T).
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

    } else if (masksize == 0) {

        // Simplifies logic elsewhere we we are allowed to cope with a mask
        // size of 0.

        return (0);
    }

    isc_throw(isc::OutOfRange, "mask size must be between 0 and " <<
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
/// \param maxmask  Default value of the mask size, used if no mask is given.
///                 It is also the maximum permitted value of the mask.
///
/// \return Pair of (string, uint32) holding the address string and the mask
///         size value.

std::pair<std::string, uint32_t>
splitIpAddress(const std::string& addrmask, uint32_t maxmask) {

    uint32_t masksize = maxmask;

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


/// \brief IP Base
///
/// Base class for both the Ipv4 and Ipv4 check classes.  The only thing this
/// supplies over and above the Check class is a clone() method, to return
/// a pointer to a newly-allocated copy of itself.

template <typename Context>
class IpBaseCheck : public Check<Context> {
public:
    /// \brief Clone Object
    ///
    /// Implemented by derived classes, this causes a class to create a copy
    /// of itself and return a pointer to the object.
    ///
    /// \return Pointer to the cloned object.  It is the caller's responsibility
    ///         to delete this object.
    virtual IpBaseCheck* clone() const {
        return (0);
    }
};



/// \brief IPV4 Check
///
/// This class performs a match between an IPv4 address specified in an ACL
/// (IP address, network mask and a flag indicating whether the check should
/// be for a match or for a non-match) and a given IP address.
///
/// \param Context Structure holding address to be matched.

template <typename Context>
class Ipv4Check : public IpBaseCheck<Context> {
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
            splitIpAddress(address, 8 * sizeof(uint32_t));

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

    // Default copy constructor and assignment operator are correct for this
    // class.

    /// \brief Destructor
    virtual ~Ipv4Check() {}

    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here.  Different
    /// specialisations are provided for different argument types, so the
    /// link will fail if used for a type for which no match is provided.
    ///
    /// \param context Information to be matched
    virtual bool matches(const Context& context) const;

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
    bool        inverse_;   ///< Test for equality or inequality
    uint32_t    netmask_;   ///< Network mask applied to match
};



// Used for an assertion check
namespace {
bool isNonZero(uint8_t i) {
    return (i != 0);
}
} // Anonymous namespace

/// \brief IPV6 Check
///
/// This class performs a match between an IPv6 address specified in an ACL
/// (IP address, network mask and a flag indicating whether the check should
/// be for a match or for a non-match) and a given IP address.
///
/// \param Context Structure holding address to be matched.

template <typename Context>
class Ipv6Check : public IpBaseCheck<Context> {
public:

    // Size of array to old IPV6 address.
    static const size_t IPV6_SIZE = sizeof(struct in6_addr);

    /// \brief Default Constructor
    Ipv6Check() :
        address_(IPV6_SIZE, 0), masksize_(0),
        inverse_(false), netmask_(IPV6_SIZE, 0)
    {}

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
    Ipv6Check(const uint8_t* address, size_t masksize = 8 * IPV6_SIZE,
              bool inverse = false) :
        address_(address, address + IPV6_SIZE), masksize_(masksize),
        inverse_(inverse), netmask_(IPV6_SIZE, 0)
    {
        setNetmask();
    }

    /// \brief String Constructor
    ///
    /// Constructs an IPv6 Check object from a network address and size of mask
    /// given as a string of the form "a.b.c.d/n", where the "/n" part is
    /// optional.
    ///
    /// \param address IP address and netmask in the form "<v6-address>/n"
    ///        (where the "/n" part is optional).
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    Ipv6Check(const std::string& address, bool inverse = false) :
        address_(IPV6_SIZE, 0), masksize_(8 * IPV6_SIZE),
        inverse_(inverse), netmask_(IPV6_SIZE, 0)
    {
        // Split the address into address part and mask.
        std::pair<std::string, uint32_t> result =
            splitIpAddress(address, 8 * IPV6_SIZE);

        // Try to convert the address.
        int status = inet_pton(AF_INET6, result.first.c_str(), &address_[0]);
        if (status == 0) {
            isc_throw(isc::InvalidParameter, "address/masksize of " <<
                      address << " is not valid IPV6 address");
        }

        // All done, so finish initialization.
        masksize_ = result.second;
        setNetmask();
    }

    /// \brief Copy constructor
    Ipv6Check(const Ipv6Check& other) : IpBaseCheck<Context>(other),
        address_(other.address_.begin(), other.address_.end()),
        masksize_(other.masksize_), inverse_(other.inverse_),
        netmask_(other.netmask_.begin(), other.netmask_.end())
    {}

    /// \brief Assignment operator
    Ipv6Check& operator=(const Ipv6Check& other) {
        if (this != &other) {
            // Copy parent
            IpBaseCheck<Context>::operator=(other);

            // Copy this object
            address_.clear();
            std::copy(other.address_.begin(), other.address_.end(),
                      std::back_inserter(address_));
            masksize_ = other.masksize_;
            inverse_ = other.inverse_;
            netmask_.clear();
            std::copy(other.netmask_.begin(), other.netmask_.end(),
                      std::back_inserter(netmask_));
        }
        return (*this);
    }

    /// \brief Destructor
    virtual ~Ipv6Check() {}

    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here.  Different
    /// specialisations are provided for different argument types, so the
    /// link will fail if used for a type for which no match is provided.
    ///
    /// \param context Information to be matched
    virtual bool matches(const Context& context) const;

    /// \brief Estimated cost
    ///
    /// Assume that the cost of the match is linear and depends on the number
    /// of comparison operations.
    virtual unsigned cost() const {
        return (IPV6_SIZE);             // Up to 16 checks
    }

    ///@{
    /// Access methods - mainly for testing

    /// \return Stored IP address
    std::vector<uint8_t> getAddress() const {
        return (address_);
    }

    /// \return Network mask applied to match
    std::vector<uint8_t> getNetmask() const {
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
    /// Sets up the network mask from the mask size.  This involves setting
    /// mask in each byte of the network mask.
    void setNetmask() {

        // Validate that the mask is valid.
        if ((masksize_ >= 1) && (masksize_ <=  8 * IPV6_SIZE)) {

            // Loop, setting the bits in the set of mask bytes until all the
            // specified bits have been used up.  The netmask array was
            // initialized to zero in the constructor.
            assert(std::find_if(netmask_.begin(), netmask_.end(), isNonZero) ==
                   netmask_.end());

            size_t bits_left = masksize_;   // Bits remaining to set
            int i = -1;                     // To allow pre-incrementing
            while (bits_left > 0) {
                if (bits_left >= 8) {
                    netmask_[++i] = ~0;  // All bits set
                    bits_left -= 8;

                } else if (bits_left > 0) {
                    netmask_[++i] = createNetmask<uint8_t>(bits_left);
                    bits_left = 0;

                }
            }
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
    /// \param testaddr Address (in network byte order) to test against the
    ///                 check condition in the class.  This is expected to
    ///                 be IPV6_SIZE bytes long.
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
        // a netmask byte of zeroes, we have run part the part of the address
        // where we need to match.

        bool match = true;
        for (int i = 0; match && (i < IPV6_SIZE) && (netmask_[i] != 0); ++i){
             match = ((testaddr[i] & netmask_[i]) ==
                      (address_[i] & netmask_[i]));
        }

        // As with the V4 check, return the XOR with the inverse flag.
        return (match != inverse_);
    }

    // Member variables

    std::vector<uint8_t>    address_;   ///< IPv6 address
    size_t                  masksize_;  ///< Mask size passed to constructor
    bool                    inverse_;   ///< Test for equality or inequality
    std::vector<uint8_t>    netmask_;   ///< Network mask applied to match

};


/// \brief Generic IP Address Check Object
///
/// This class performs a match between an IP address specified in an ACL
/// (IP address (either V4 of V6), network mask and a flag indicating whether
/// the check should be for a match or for a non-match) and a given IP address.
///
/// \param Context Structure holding address to be matched.

template <typename Context>
class IpCheck : public IpBaseCheck<Context> {
public:

    /// \brief String Constructor
    ///
    /// Constructs an IP Check object from a network address and size of mask
    /// given as a string of the form "<address>/n", where the "/n" part is
    /// optional.
    ///
    /// \param address IP address and netmask in the form "<address>/n"
    ///        (where the "/n" part is optional).
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    IpCheck(const std::string& address, bool inverse = false) {
        try {
            check_.reset(new Ipv4Check<Context>(address, inverse));
            isv4_ = true;
        } catch (isc::Exception&) {
            check_.reset(new Ipv6Check<Context>(address, inverse));
            isv4_ = false;
        }
    }

    /// \brief Copy constructor
    IpCheck(const IpCheck<Context>& other) : IpBaseCheck<Context>(other),
                                             check_(other.check_->clone())
    {}

    /// \brief Assignment operator
    IpCheck& operator=(const IpCheck& other) {
        if (this != &other) {
            IpBaseCheck<Context>::operator=(other);
            check_.reset(other.check_->clone());
        }
    }

    /// \brief Clone
    IpBaseCheck<Context>* clone() const {
        return (new IpCheck<Context>(*this));
    }

    /// \brief Destructor
    virtual ~IpCheck() {}

    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here.  Different
    /// specialisations are provided for different argument types, so the
    /// link will fail if used for a type for which no match is provided.
    ///
    /// \param context Information to be matched
    virtual bool matches(const Context& context) const {
        return (check_->matches(context));
    }

    /// \brief Estimated cost
    ///
    /// Assume that the cost of the match is linear and depends on the number
    /// of comparison operations.
    virtual unsigned cost() const {
        return (check_->cost());
    }

private:
    // Member variables

    bool                                      isv4_;  ///< true if V4 address
    boost::scoped_ptr<IpBaseCheck<Context> >  check_; ///< Check object
};

} // namespace acl
} // namespace isc

#endif // __IP_CHECK_H
