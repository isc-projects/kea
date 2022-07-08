// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_ADDRLST_H
#define OPTION6_ADDRLST_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief DHCPv6 Option class for handling list of IPv6 addresses.
///
/// This class handles a list of IPv6 addresses. An example of such option
/// is dns-servers option. It can also be used to handle single address.
class Option6AddrLst: public Option {

public:
    /// a container for (IPv6) addresses
    typedef std::vector<isc::asiolink::IOAddress> AddressContainer;

    /// @brief Constructor used during option generation.
    ///
    /// @param type option type
    /// @param addrs vector of addresses to be stored
    Option6AddrLst(uint16_t type, const AddressContainer& addrs);

    /// @brief Simplified constructor for a single address
    ///
    /// @param type option type
    /// @param addr a single address to be stored
    Option6AddrLst(uint16_t type, const isc::asiolink::IOAddress& addr);

    /// @brief Constructor used for parsing received option
    ///
    /// @param type option type
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    Option6AddrLst(uint16_t type, OptionBufferConstIter begin,
                   OptionBufferConstIter end);

    virtual OptionPtr clone() const;

    /// @brief Assembles on-wire form of this option
    ///
    /// @param buf pointer to packet buffer
    /// @param check if set to false, allows options larger than 255 for v4
    void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Parses received data
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end);

    virtual std::string toText(int indent = 0) const;

    /// @brief Sets a single address.
    ///
    /// @param addr a single address to be added
    void setAddress(const isc::asiolink::IOAddress& addr);

    /// @brief Sets list of addresses.
    ///
    /// @param addrs a vector of addresses to be added
    void setAddresses(const AddressContainer& addrs);

    /// @brief Returns vector with addresses.
    ///
    /// We return a copy of our list. Although this includes overhead,
    /// it also makes this list safe to use after this option object
    /// is no longer available. As options are expected to hold only
    /// a few (1-3) addresses, the overhead is not that big.
    ///
    /// @return address container with addresses
    AddressContainer getAddresses() const { return addrs_; };

    // returns data length (data length + DHCPv4/DHCPv6 option header)
    virtual uint16_t len() const;

protected:
    AddressContainer addrs_;
};

/// @brief Pointer to the @c Option6AddrLst object.
typedef boost::shared_ptr<Option6AddrLst> Option6AddrLstPtr;

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_ADDRLST_H
