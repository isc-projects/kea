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

#ifndef OPTION4_ADDRLST_H_
#define OPTION4_ADDRLST_H_

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <util/buffer.h>
#include <dhcp/option.h>

namespace isc {
namespace dhcp {


/// @brief DHCPv4 Option class for handling list of IPv4 addresses.
///
/// This class handles a list of IPv4 addresses. An example of such option
/// is dns-servers option. It can also be used to handle a single address.
class Option4AddrLst : public isc::dhcp::Option {
public:

    /// Defines a collection of IPv4 addresses.
    typedef std::vector<isc::asiolink::IOAddress> AddressContainer;

    /// @brief Constructor, creates an option with empty list of addresses.
    ///
    /// Creates empty option that can hold addresses. Addresses can be added
    /// with addAddress(), setAddress() or setAddresses().
    ///
    /// @param type option type
    Option4AddrLst(uint8_t type);

    /// @brief Constructor, creates an option with a list of addresses.
    ///
    /// Creates an option that contains specified list of IPv4 addresses.
    ///
    /// @param type option type
    /// @param addrs container with a list of addresses
    Option4AddrLst(uint8_t type, const AddressContainer& addrs);

    /// @brief Constructor, creates an option with a single address.
    ///
    /// Creates an option that contains a single address.
    ///
    /// @param type option type
    /// @param addr a single address that will be stored as 1-elem. address list
    Option4AddrLst(uint8_t type, const isc::asiolink::IOAddress& addr);

    /// @brief Constructor, used for received options.
    ///
    /// TODO: This can be templated to use different containers, not just
    /// vector. Prototype should look like this:
    /// template<typename InputIterator> Option(Universe u, uint16_t type,
    /// InputIterator first, InputIterator last);
    ///
    /// vector<int8_t> myData;
    /// Example usage: new Option(V4, 123, myData.begin()+1, myData.end()-1)
    /// This will create DHCPv4 option of type 123 that contains data from
    /// trimmed (first and last byte removed) myData vector.
    ///
    /// @param type option type (0-255 for V4 and 0-65535 for V6)
    /// @param first iterator to the first element that should be copied
    /// @param last iterator to the next element after the last one
    ///        to be copied.
    Option4AddrLst(uint8_t type, std::vector<uint8_t>::const_iterator first,
           std::vector<uint8_t>::const_iterator last);

    /// @brief Writes option in a wire-format to a buffer.
    ///
    /// Method will throw if option storing fails for some reason.
    ///
    /// TODO Once old (DHCPv6) implementation is rewritten,
    /// unify pack4() and pack6() and rename them to just pack().
    ///
    /// @param buf output buffer (option will be stored there)
    virtual void
    pack4(isc::util::OutputBuffer& buf);

    /// Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    virtual std::string
    toText(int indent = 0);

    /// Returns length of the complete option (data length + DHCPv4/DHCPv6
    /// option header)
    ///
    /// @return length of the option
    virtual uint16_t len();

    /// @brief Returns vector with addresses.
    ///
    /// We return a copy of our list. Although this includes overhead,
    /// it also makes this list safe to use after this option object
    /// is no longer available. As options are expected to hold only
    /// a couple (1-3) addresses, the overhead is not that big.
    ///
    /// @return address container with addresses
    AddressContainer
    getAddresses() { return addrs_; };

    /// @brief Sets addresses list.
    ///
    /// Clears existing list of addresses and adds a single address to that
    /// list. This is very convenient method for options that are supposed to
    /// only a single option. See addAddress() if you want to add
    /// address to existing list or setAddresses() if you want to
    /// set the whole list at once.
    ///
    /// Passed address must be IPv4 address. Otherwire BadValue exception
    /// will be thrown.
    ///
    /// @param addrs address collection to be set
    void setAddresses(const AddressContainer& addrs);

    /// @brief Clears address list and sets a single address.
    ///
    /// Clears existing list of addresses and adds a single address to that
    /// list. This is very convenient method for options that are supposed to
    /// only a single option. See addAddress() if you want to add
    /// address to existing list or setAddresses() if you want to
    /// set the whole list at once.
    ///
    /// Passed address must be IPv4 address. Otherwire BadValue exception
    /// will be thrown.
    ///
    /// @param addr an address that is going to be set as 1-element address list
    void setAddress(const isc::asiolink::IOAddress& addr);

    /// @brief Adds address to existing list of addresses.
    ///
    /// Adds a single address to that list. See setAddress() if you want to
    /// define only a single address or setAddresses() if you want to
    /// set the whole list at once.
    ///
    /// Passed address must be IPv4 address. Otherwire BadValue exception
    /// will be thrown.
    ///
    /// @param addr an address thait is going to be added to existing list
    void addAddress(const isc::asiolink::IOAddress& addr);

protected:
    /// contains list of addresses
    AddressContainer addrs_;
};

} // namespace isc::dhcp
} // namespace isc

#endif
