// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
/// case of a prefix with /128. It makes everyone's life much easier, because
/// the base prefix doubles as a regular address in many cases, e.g. when
/// searching for a lease.
///
/// When searching for a prefix in the database or simply comparing two prefixes
/// for equality, it is important that only the significant parts of the
/// prefixes are compared. It is possible that the client or a server sends a
/// prefix which has non-significant bits (beyond prefix length) set. The
/// server or client receiving such a prefix should be liberal and not discard
/// this prefix. It should rather ignore the non-significant bits. Therefore
/// the unpack() function, which parses the prefix from the wire, always sets
/// the non-significant bits to 0 so as two prefixes received on the wire can
/// be compared without additional processing.
///
/// @todo Currently, the constructor which creates the option from the textual
/// format doesn't set non-significant bits to 0. This is because it is assumed
/// that the prefixes from the string are created locally (not received over the
/// wire) and should be validated before the option is created. If we wanted
/// to set non-significant bits to 0 when the prefix is created from the textual
/// format it would have some performance implications, because the option would
/// need to be turned into wire format, appropriate bits set to 0 and then
/// option would need to be created again from the wire format. We may consider
/// doing it if we find a use case where it is required.
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

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const;

    /// @brief Writes option in wire-format.
    ///
    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @throw BadValue if the address is not IPv6
    ///
    /// @param buf pointer to a buffer
    /// @param check if set to false, allows options larger than 255 for v4
    void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Parses received buffer.
    ///
    /// This function calls the @c Option6IAPrefix::mask function to set the
    /// non-significant bits of the prefix (bits beyond the length of the
    /// prefix) to zero. See the @c Option6IAPrefix class documentation for
    /// details why it is done.
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
    virtual std::string toText(int indent = 0) const;

    /// sets address in this option.
    ///
    /// @param prefix prefix to be sent in this option
    /// @param length prefix length
    void setPrefix(const isc::asiolink::IOAddress& prefix,
                   uint8_t length) { addr_ = prefix; prefix_len_ = length; }

    uint8_t getLength() const { return prefix_len_; }

    /// returns data length (data length + DHCPv4/DHCPv6 option header)
    virtual uint16_t len() const;

private:

    /// @brief Apply mask of the specific length to the IPv6 address.
    ///
    /// @param begin Iterator pointing to the buffer holding IPv6 address.
    /// @param end Iterator pointing to the end of the buffer holding IPv6
    /// address.
    /// @param len Length of the mask to be applied.
    /// @param [out] output_address Reference to the buffer where the address
    /// with a mask applied is output.
    void mask(OptionBuffer::const_iterator begin,
              OptionBuffer::const_iterator end,
              const uint8_t len,
              OptionBuffer& output_address) const;

    uint8_t prefix_len_;
};

/// @brief Pointer to the @c Option6IAPrefix object.
typedef boost::shared_ptr<Option6IAPrefix> Option6IAPrefixPtr;

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_IAPREFIX_H
