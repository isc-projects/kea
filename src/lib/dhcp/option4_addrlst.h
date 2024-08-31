// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION4_ADDRLST_H
#define OPTION4_ADDRLST_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <util/buffer.h>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// Forward declaration to Option4AddrLst class.
class Option4AddrLst;

/// A pointer to the Option4AddrLst object.
typedef boost::shared_ptr<Option4AddrLst> Option4AddrLstPtr;

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
    Option4AddrLst(uint8_t type, OptionBufferConstIter first,
                   OptionBufferConstIter last);

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const;

    /// @brief Writes option in a wire-format to a buffer.
    ///
    /// Method will throw if option storing fails for some reason.
    ///
    /// @param buf output buffer (option will be stored there)
    /// @param check if set to false, allows options larger than 255 for v4
    virtual void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    virtual std::string toText(int indent = 0) const;

    /// Returns length of the complete option (data length + DHCPv4/DHCPv6
    /// option header)
    ///
    /// @return length of the option
    virtual uint16_t len() const;

    /// @brief Returns vector with addresses.
    ///
    /// We return a copy of our list. Although this includes overhead,
    /// it also makes this list safe to use after this option object
    /// is no longer available. As options are expected to hold only
    /// a few (1-3) addresses, the overhead is not that big.
    ///
    /// @return address container with addresses
    AddressContainer getAddresses() const { return addrs_; };

    /// @brief Sets addresses list.
    ///
    /// Clears existing list of addresses and adds a single address to that
    /// list. This is very convenient method for options that are supposed to
    /// only a single option. See addAddress() if you want to add
    /// address to existing list or setAddresses() if you want to
    /// set the whole list at once.
    ///
    /// Passed address must be IPv4 address. Otherwise BadValue exception
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
    /// Passed address must be IPv4 address. Otherwise BadValue exception
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
    /// Passed address must be IPv4 address. Otherwise BadValue exception
    /// will be thrown.
    ///
    /// @param addr an address that is going to be added to existing list
    void addAddress(const isc::asiolink::IOAddress& addr);

protected:
    /// contains list of addresses
    AddressContainer addrs_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION4_ADDRLST_H
