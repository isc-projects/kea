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

#ifndef OPTION6_ADDRLST_H_
#define OPTION6_ADDRLST_H_

#include <vector>
#include <asiolink/io_address.h>
#include <dhcp/option.h>

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
    ///
    Option6AddrLst(unsigned short type,
                   const AddressContainer& addrs);

    /// @brief Simplified constructor for a single address
    ///
    /// @param type option type
    /// @param addr a single address to be stored
    ///
    Option6AddrLst(unsigned short type,
                   const isc::asiolink::IOAddress& addr);

    /// @brief Constructor used for parsing received option
    ///
    /// @param type option type
    /// @param buf pointer to packet buffer
    /// @param buf_len length of packet buffer
    /// @param offset offset to beginning of option data
    /// @param len length of option data
    ///
    Option6AddrLst(unsigned short type, boost::shared_array<uint8_t> buf,
                   unsigned int buf_len,
                   unsigned int offset,
                   unsigned int len);

    /// @brief Assembles on-wire form of this option
    ///
    /// @param buf pointer to packet buffer
    /// @param buf_len length of packet buffer
    /// @param offset offset to place, where option is to be stored
    ///
    /// @return offset to the next unused char (just after stored option)
    ///
    unsigned int
    pack(boost::shared_array<uint8_t>& buf, unsigned int buf_len,
         unsigned int offset);

    /// @brief Parses received data
    ///
    /// @param buf pointer to packet buffer
    /// @param buf_len length of packet buffer
    /// @param offset offset to option data
    /// @param parse_len specified option data length
    ///
    /// @return offset to the next unparsed char (just after parsed option)
    ///
    virtual unsigned int
    unpack(const boost::shared_array<uint8_t>& buf,
           unsigned int buf_len,
           unsigned int offset,
           unsigned int parse_len);

    virtual std::string toText(int indent = 0);

    /// @brief Sets a single address.
    ///
    /// @param addr a single address to be added
    ///
    void setAddress(const isc::asiolink::IOAddress& addr);

    /// @brief Sets list of addresses.
    ///
    /// @param addrs a vector of addresses to be added
    ///
    void setAddresses(const AddressContainer& addrs);

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

    // returns data length (data length + DHCPv4/DHCPv6 option header)
    virtual uint16_t len();

protected:
    AddressContainer addrs_;
};

} // isc::dhcp namespace
} // isc namespace

#endif /* OPTION_ADDRLST_H_ */
