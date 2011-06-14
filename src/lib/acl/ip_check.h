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
/// \param maxmask  Default value of the mask size, used if no mask is given.
///                 It is also the maximum permitted value of the mask.  An
///                 OutOfRange exception is thrown if the mask size value is
///                 greater than this.
///
/// \return Pair of (string, size_t) holding the address string and the mask
///         size value.

std::pair<std::string, size_t>
splitIpAddress(const std::string& addrmask, size_t maxmask) {

    // Set the default value for the mask size
    size_t masksize = maxmask;

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
/// The base Check class is templated on a context structure which is passed
/// to the matches() method.  In Check, the method is declared abstract.  In
/// this class, the method is concrete, but no declaration is provided.  To
/// use the class for a given data type X say, a template specialisation of the
/// method must be provided, i.e.
/// \code
/// template <> bool Ipv4Check<X>::matches(const X& context) const {
/// :
/// }
/// \endcode
///
/// The Ipv4Check class should not be directly.  Instead, use IpCheck.

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
    /// \param addrmask IP address and netmask in the form "a.b.c.d/n" (where
    ///        the "/n" part is optional).
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    Ipv4Check(const std::string& addrmask, bool inverse = false) :
        address_(1), masksize_(32), inverse_(inverse), netmask_(0)
    {
        // Split into address part and mask.
        std::pair<std::string, size_t> result =
            splitIpAddress(addrmask, 8 * sizeof(uint32_t));

        // Try to convert the address.  The result is in network-byte order.
        int status = inet_pton(AF_INET, result.first.c_str(), &address_);
        if (status == 0) {
            isc_throw(isc::InvalidParameter, "address/masksize of " <<
                      addrmask << " is not valid IPV4 address");
        }

        // All done, so finish initialization.
        masksize_ = result.second;
        setNetmask();
    }

    // Default copy constructor and assignment operator is correct for this
    // class (all member variables have appropriate operations defined).

    /// \brief Destructor
    virtual ~Ipv4Check() {}

    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here.  Different
    /// specialisations are provided for different argument types, so the
    /// program link will fail if used for a type for which no match is
    /// provided.
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

    /// \brief Comparison
    ///
    /// This is the actual comparison function that checks the IP address passed
    /// to this class with the matching information in the class itself.  It is
    /// expected to be called from matches().
    ///
    /// \param addr Address (in network byte order) to match against the
    ///             check condition in the class.
    ///
    /// \return true if the address matches, false if it does not.
    virtual bool compare(uint32_t addr) const {

        // To check that the address given matches the stored network address
        // and netmask, we check the simple condition that:
        //
        //     address_given & netmask_ == stored_address & netmask_
        //
        // However, we must return the negation of the result if inverse_ is
        // set.  The appropriate truth table is:
        //
        // Result inverse_ Return
        // false  false    false
        // false  true     true
        // true   false    true
        // true   true     false
        //
        // ... which is an XOR operation.  Although there is no explicit logical
        /// XOR operator, with two bool arguments "!=" serves that function.

        return (((addr & netmask_) == (address_ & netmask_)) != inverse_);
    }

private:
    /// \brief Set Network Mask
    ///
    /// Sets up the network mask from the mask size.  A value with the most
    /// significant "mask size" bits is created and then stored in network-byte
    /// order, the same way as addresses are presented and stored.
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

    // Member variables

    uint32_t    address_;   ///< IPv4 address
    size_t      masksize_;  ///< Mask size passed to constructor
    bool        inverse_;   ///< Test for equality or inequality
    uint32_t    netmask_;   ///< Network mask applied to match
};



/// \brief IPV6 Check
///
/// This class performs a match between an IPv6 address specified in an ACL
/// (IP address, network mask and a flag indicating whether the check should
/// be for a match or for a non-match) and a given IP address.
///
/// Like Ipv4Check, the class is templated on the type of a context structure
/// passed to the matches() method, and a template specialisation for that
/// method must be supplied for the class to be used.  Also like Ipv4Check,
/// the class should not be used directly, Ipcheck should be used instead.

template <typename Context>
class Ipv6Check : public Check<Context> {
private:
    // Size of array to hold and IPV6 address.
    static const size_t IPV6_SIZE = sizeof(struct in6_addr);

public:
    /// \brief Default Constructor
    ///
    /// Only provided for use as a placeholder in array initializations etc.
    /// There are no setXxxx() methods; an object of this class can be updated
    /// by assignment.
    Ipv6Check() :
        address_(IPV6_SIZE, 0), masksize_(0), inverse_(false),
        netmask_(IPV6_SIZE, 0)
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
    /// given as a string of the form <ip6-address>/n".
    ///
    /// \param address IP address and netmask in the form "<v6-address>/n"
    ///        (where the "/n" part is optional).
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    Ipv6Check(const std::string& address, bool inverse = false) :
        address_(IPV6_SIZE, 0), masksize_(8 * IPV6_SIZE), inverse_(inverse),
        netmask_(IPV6_SIZE, 0)
    {
        // Split the address into address part and mask.
        std::pair<std::string, size_t> result =
            splitIpAddress(address, 8 * IPV6_SIZE);

        // Try to convert the address.  If successful, the result is in
        // network-byte order (most significant components at lower addresses).
        int status = inet_pton(AF_INET6, result.first.c_str(), &address_[0]);
        if (status == 0) {
            isc_throw(isc::InvalidParameter, "address/masksize of " <<
                      address << " is not valid IPV6 address");
        }

        // All done, so finish initialization.
        masksize_ = result.second;
        setNetmask();
    }

    // Default copy constructor and assignment operator is correct for this
    // class (all member variables have equivalent operations).

    /// \brief Destructor
    virtual ~Ipv6Check() {}

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
        // a netmask byte of zeroes, we have run past the part of the address
        // where we need to match.

        bool match = true;
        for (int i = 0; match && (i < netmask_.size()) && (netmask_[i] != 0);
             ++i) {
             match = ((testaddr[i] & netmask_[i]) ==
                      (address_[i] & netmask_[i]));
        }

        // As with the V4 check, return the XOR with the inverse flag.
        return (match != inverse_);
    }

private:
    /// \brief Set Network Mask
    ///
    /// Sets up the network mask from the mask size.  This involves setting
    /// an individual mask in each byte of the network mask.
    void setNetmask() {

        // Validate that the mask is valid.
        if ((masksize_ >= 1) && (masksize_ <=  8 * IPV6_SIZE)) {

            // Loop, setting the bits in the set of mask bytes until all the
            // specified bits have been used up.  The netmask array was
            // initialized to zero in the constructor, but in debug mode we
            // can check that.
            assert(std::find_if(netmask_.begin(), netmask_.end(),
                   std::bind1st(std::not_equal_to<uint8_t>(), 0)) ==
                   netmask_.end());

            size_t bits_left = masksize_;   // Bits remaining to set
            int i = -1;
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
                      "for the data type which is " << IPV6_SIZE <<
                      " bytes long");
        }
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
/// Derived from the base Check class, the class is templated on the Context
/// parameter.  Internally, it uses the Ipv4Check and Ipv6Check classes and as a
/// result requires that specializations for their matches() methods be provided
/// for the template parameter.

template <typename Context>
class IpCheck : public Check<Context> {
public:

    /// \brief String Constructor
    ///
    /// Constructs an IP Check object from a network address and size of mask
    /// given as a string of the form "<address>/n", where the "/n" part is
    /// optional.
    ///
    /// \param address IP address and netmask in the form "<address>/n".  The
    ///        "/n" part is optional but, if provided, must match the type
    ///        of address specified.
    /// \param inverse If false (the default), matches() returns true if the
    ///        condition matches.  If true, matches() returns true if the
    ///        condition does not match.
    IpCheck(const std::string& address, bool inverse = false) :
        address_(address), inverse_(inverse)
    {
        createCheck();
    }

    /// \brief Copy constructor
    ///
    /// \param other Object to be copied
    IpCheck(const IpCheck<Context>& other) : Check<Context>(other),
        address_(other.address_), inverse_(other.inverse_)
    {
        // The address_ and inverse_ objects are copied but, rather than copy
        // the stored "check_" object (the type of which is indeterminate, as
        // only a pointer to a base class is stored), it recreates the object
        // from the stored constructor arguments.
        createCheck();
    }

    /// \brief Assignment operator
    ///
    /// \param other Object to be copied
    ///
    /// \return reference to current object
    IpCheck& operator=(const IpCheck& other) {
        if (this != &other) {
            // Similar to the copy constructor, this copies the constructor
            // arguments from the source of the assignment and recreates the
            // check object from them.
            address_ = other.address_;
            inverse_ = other.inverse_;
            createCheck();
        }
        return (*this);
    }

    /// \brief Destructor
    virtual ~IpCheck() {}

    /// \brief The check itself
    ///
    /// Matches the passed argument to the condition stored here by devolving
    /// the check to the internal Ipv4Check or Ipv6Check object.  Appropriate
    /// specialisations for the matches() method in those classes must be
    /// provided for the program to link successfully.
    ///
    /// \param context Information to be matched
    virtual bool matches(const Context& context) const {
        return (check_->matches(context));
    }

    /// \brief Estimated cost
    ///
    /// Assume that the cost of the match is linear and depends on the number
    /// of comparison operations.  The cost is obtained from the type of
    /// check object stored.
    virtual unsigned cost() const {
        return (check_->cost());
    }

private:
    /// \brief Create check object
    ///
    /// Creates an instance of the actual check object (Ipv4Check or Ipv6Check)
    /// that will be used to perform the checking.  It assumes that the member
    /// variables are set appropriately.
    void createCheck() {
        try {
            check_.reset(new Ipv4Check<Context>(address_, inverse_));
        } catch (isc::Exception&) {
            check_.reset(new Ipv6Check<Context>(address_, inverse_));
        }
    }

    // Member variables
    std::string         address_;   ///< Copy of constructor address string
    bool                inverse_;   ///< Copy of constructor inverse flag
    boost::scoped_ptr<Check<Context> >  check_; ///< Check object
};

} // namespace acl
} // namespace isc

#endif // __IP_CHECK_H
