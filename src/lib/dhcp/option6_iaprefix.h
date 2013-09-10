// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION6_IAPREFIX_H
#define OPTION6_IAPREFIX_H

#include <asiolink/io_address.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option.h>

namespace isc {
namespace dhcp {


/// @brief Class that represents IAPREFIX option in DHCPv6
///
/// It is based on a similar class that handles addresses. There are major
/// differences, though. The fields are in different order. There is also
/// additional prefix length field.
///
/// It should be noted that to get a full prefix (2 values: base prefix, and
/// a prefix length) 2 methods are used: getAddress() and getLength(). Although
/// using getAddress() to obtain base prefix is somewhat counter-intuitive at
/// first, it becomes obvious when one realizes that an address is a special
/// case of a prefix with /128. It makes everyone's like much easier, because
/// the base prefix doubles as a regular address in many cases, e.g. when
/// searching for a lease.
class Option6IAPrefix : public Option6IAAddr {

public:
    /// length of the fixed part of the IAPREFIX option
    static const size_t OPTION6_IAPREFIX_LEN = 25;

    /// @brief Constructor, used for options constructed (during transmission).
    ///
    /// @param type option type
    /// @param addr reference to an address
    /// @param prefix_length length (1-128)
    /// @param preferred address preferred lifetime (in seconds)
    /// @param valid address valid lifetime (in seconds)
    Option6IAPrefix(uint16_t type, const isc::asiolink::IOAddress& addr,
                    uint8_t prefix_length, uint32_t preferred, uint32_t valid);

    /// @brief Constructor, used for received options.
    ///
    /// @throw OutOfRange if buffer is too short
    ///
    /// @param type option type
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    Option6IAPrefix(uint32_t type, OptionBuffer::const_iterator begin,
                    OptionBuffer::const_iterator end);

    /// @brief Writes option in wire-format.
    ///
    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @throw BadValue if the address is not IPv6
    ///
    /// @param buf pointer to a buffer
    void pack(isc::util::OutputBuffer& buf);

    /// @brief Parses received buffer.
    ///
    /// @throw OutOfRange when buffer is shorter than 25 bytes
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
    virtual std::string toText(int indent = 0);

    /// sets address in this option.
    ///
    /// @param addr address to be sent in this option
    void setPrefix(const isc::asiolink::IOAddress& prefix,
                   uint8_t length) { addr_ = prefix; prefix_len_ = length; }

    uint8_t getLength() const { return prefix_len_; }

    /// returns data length (data length + DHCPv4/DHCPv6 option header)
    virtual uint16_t len();

protected:
    uint8_t prefix_len_;
};

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_IA_H
