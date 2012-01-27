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

#ifndef OPTION6_IAADDR_H_
#define OPTION6_IAADDR_H_

#include "asiolink/io_address.h"
#include "dhcp/option.h"

namespace isc {
namespace dhcp {

class Option6IAAddr: public Option {

public:
    /// length of the fixed part of the IAADDR option
    static const size_t OPTION6_IAADDR_LEN = 24;

    /// @brief ctor, used for options constructed (during transmission)
    ///
    /// @param type option type
    /// @param addr reference to an address
    /// @param preferred address preferred lifetime (in seconds)
    /// @param valid address valid lifetime (in seconds)
    Option6IAAddr(unsigned short type, const isc::asiolink::IOAddress& addr,
                  unsigned int preferred, unsigned int valid);

    /// ctor, used for received options
    /// boost::shared_array allows sharing a buffer, but it requires that
    /// different instances share pointer to the whole array, not point
    /// to different elements in shared array. Therefore we need to share
    /// pointer to the whole array and remember offset where data for
    /// this option begins
    ///
    /// @param type option type
    /// @param buf pointer to a buffer
    /// @param buf_len length of the buffer passed in buf
    /// @param offset offset to first data byte in that buffer
    /// @param len data length of this option
    Option6IAAddr(unsigned short type, boost::shared_array<uint8_t> buf,
                  unsigned int buf_len, unsigned int offset, unsigned int len);

    /// @brief Writes option in wire-format.
    ///
    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf pointer to a buffer
    /// @param buf_len length of the buffer
    /// @param offset offset to place, where option shout be stored
    ///
    /// @return offset to first unused byte after stored option
    unsigned int
    pack(boost::shared_array<uint8_t>& buf, unsigned int buf_len,
         unsigned int offset);

    /// @brief Parses buffer.
    ///
    /// Parses received buffer, returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param buf pointer to buffer
    /// @param buf_len length of buf
    /// @param offset offset, where start parsing option
    /// @param parse_len how many bytes should be parsed
    ///
    /// @return offset after last parsed octet
    virtual unsigned int
    unpack(const boost::shared_array<uint8_t>& buf,
           unsigned int buf_len,
           unsigned int offset,
           unsigned int parse_len);

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

#endif /* OPTION_IA_H_ */
