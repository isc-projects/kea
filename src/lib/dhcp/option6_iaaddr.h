// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION6_IAADDR_H
#define OPTION6_IAADDR_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>

namespace isc {
namespace dhcp {

class Option6IAAddr: public Option {

public:
    /// length of the fixed part of the IAADDR option
    static const size_t OPTION6_IAADDR_LEN = 24;

    /// @brief Ctor, used for options constructed (during transmission).
    ///
    /// @param type option type
    /// @param addr reference to an address
    /// @param preferred address preferred lifetime (in seconds)
    /// @param valid address valid lifetime (in seconds)
    Option6IAAddr(uint16_t type, const isc::asiolink::IOAddress& addr,
                  uint32_t preferred, uint32_t valid);

    /// @brief ctor, used for received options.
    ///
    /// @param type option type
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    Option6IAAddr(uint32_t type, OptionBuffer::const_iterator begin,
                  OptionBuffer::const_iterator end);

    /// @brief Writes option in wire-format.
    ///
    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf pointer to a buffer
    void pack(isc::util::OutputBuffer& buf);

    /// @brief Parses received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end);

    /// Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    virtual std::string
    toText(int indent = 0);


    /// sets address in this option.
    ///
    /// @param addr address to be sent in this option
    void setAddress(const isc::asiolink::IOAddress& addr) { addr_ = addr; }

    /// Sets preferred lifetime (in seconds)
    ///
    /// @param pref address preferred lifetime (in seconds)
    ///
    void setPreferred(unsigned int pref) { preferred_=pref; }

    /// Sets valid lifetime (in seconds).
    ///
    /// @param valid address valid lifetime (in seconds)
    ///
    void setValid(unsigned int valid) { valid_=valid; }

    /// Returns  address contained within this option.
    ///
    /// @return address
    isc::asiolink::IOAddress
    getAddress() const { return addr_; }

    /// Returns preferred lifetime of an address.
    ///
    /// @return preferred lifetime (in seconds)
    unsigned int
    getPreferred() const { return preferred_; }

    /// Returns valid lifetime of an address.
    ///
    /// @return valid lifetime (in seconds)
    unsigned int
    getValid() const { return valid_; }

    /// returns data length (data length + DHCPv4/DHCPv6 option header)
    virtual uint16_t len();

protected:
    /// contains an IPv6 address
    isc::asiolink::IOAddress addr_;

    /// contains preferred-lifetime timer (in seconds)
    unsigned int preferred_;

    /// contains valid-lifetime timer (in seconds)
    unsigned int valid_;
};

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_IA_H
