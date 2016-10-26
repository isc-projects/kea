// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option6_pdexclude.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <stdint.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option6PDExclude::Option6PDExclude(const isc::asiolink::IOAddress& delegated_prefix,
                                   const uint8_t delegated_prefix_length,
                                   const isc::asiolink::IOAddress& excluded_prefix,
                                   const uint8_t excluded_prefix_length)
    : Option(V6, D6O_PD_EXCLUDE),
      delegated_prefix_(delegated_prefix),
      delegated_prefix_length_(delegated_prefix_length),
      excluded_prefix_(excluded_prefix),
      excluded_prefix_length_(excluded_prefix_length) {

    // Expecting v6 prefixes of sane length.
    if (!delegated_prefix_.isV6() || !excluded_prefix_.isV6() ||
        (delegated_prefix_length_ > 128) || (excluded_prefix_length_ > 128)) {
        isc_throw(BadValue, "invalid delegated or excluded prefix values specified: "
                  << delegated_prefix_ << "/"
                  << static_cast<int>(delegated_prefix_length_) << ", "
                  << excluded_prefix_ << "/"
                  << static_cast<int>(excluded_prefix_length_));
    }

    // Excluded prefix must be longer than the delegated prefix.
    if (excluded_prefix_length_ <= delegated_prefix_length_) {
        isc_throw(BadValue, "length of the excluded prefix "
                  << excluded_prefix_ << "/"
                  << static_cast<int>(excluded_prefix_length_)
                  << " must be greater than the length of the"
                  " delegated prefix " << delegated_prefix_ << "/"
                  << static_cast<int>(delegated_prefix_length_));
    }

    // Both prefixes must share common part with a length equal to the
    // delegated prefix length.
    std::vector<uint8_t> delegated_prefix_bytes = delegated_prefix_.toBytes();
    boost::dynamic_bitset<uint8_t> delegated_prefix_bits(delegated_prefix_bytes.rbegin(),
                                                         delegated_prefix_bytes.rend());

    std::vector<uint8_t> excluded_prefix_bytes = excluded_prefix_.toBytes();
    boost::dynamic_bitset<uint8_t> excluded_prefix_bits(excluded_prefix_bytes.rbegin(),
                                                        excluded_prefix_bytes.rend());


    // See RFC6603, section 4.2: assert(p1>>s == p2>>s)
    const uint8_t delta = 128 - delegated_prefix_length;

    if ((delegated_prefix_bits >> delta) != (excluded_prefix_bits >> delta)) {
        isc_throw(BadValue, "excluded prefix "
                  << excluded_prefix_ << "/"
                  << static_cast<int>(excluded_prefix_length_)
                  << " must have the same common prefix part of "
                  << static_cast<int>(delegated_prefix_length)
                  << " as the delegated prefix "
                  << delegated_prefix_ << "/"
                  << static_cast<int>(delegated_prefix_length_));
    }

}

Option6PDExclude::Option6PDExclude(const isc::asiolink::IOAddress& delegated_prefix,
                                   const uint8_t delegated_prefix_length,
                                   OptionBufferConstIter begin,
                                   OptionBufferConstIter end)
    : Option(V6, D6O_PD_EXCLUDE),
      delegated_prefix_(delegated_prefix),
      delegated_prefix_length_(delegated_prefix_length),
      excluded_prefix_(IOAddress::IPV6_ZERO_ADDRESS()),
      excluded_prefix_length_(0) {
    unpack(begin, end);
}

OptionPtr
Option6PDExclude::clone() const {
    return (cloneInternal<Option6PDExclude>());
}

void
Option6PDExclude::pack(isc::util::OutputBuffer& buf) const {
    // Header = option code and length.
    packHeader(buf);

    // Excluded prefix length is always 1 byte long field.
    buf.writeUint8(excluded_prefix_length_);

    // Retrieve entire prefix and convert it to bit representation.
    std::vector<uint8_t> excluded_prefix_bytes = excluded_prefix_.toBytes();
    boost::dynamic_bitset<uint8_t> bits(excluded_prefix_bytes.rbegin(),
                                        excluded_prefix_bytes.rend());

    // Shifting prefix by delegated prefix length leaves us with only a
    // subnet id part of the excluded prefix.
    bits = bits << delegated_prefix_length_;

    // Calculate subnet id length.
    const uint8_t subnet_id_length = getSubnetIDLength();
    for (uint8_t i = 0; i < subnet_id_length; ++i) {
        // Retrieve bit representation of the current byte.
        const boost::dynamic_bitset<uint8_t> first_byte = bits >> 120;
        // Convert it to a numeric value.
        uint8_t val = static_cast<uint8_t>(first_byte.to_ulong());

        // Zero padded bits follow when excluded_prefix_length_ is not divisible by 8.
        if (i == subnet_id_length - 1) {
            uint8_t length_delta = excluded_prefix_length_ - delegated_prefix_length_;
            uint8_t mask = 0xFF;
            mask <<= (8 - (length_delta % 8));
            val &= mask;
        }
        // Store calculated value in a buffer.
        buf.writeUint8(val);

        // Go to the next byte.
        bits <<= 8;
    }
}

void
Option6PDExclude::unpack(OptionBufferConstIter begin,
                         OptionBufferConstIter end) {

    // At this point we don't know the excluded prefix length, but the
    // minimum requirement is that reminder of this option includes the
    // excluded prefix length and at least 1 byte of the IPv6 subnet id.
    if (std::distance(begin, end) < 2) {
        isc_throw(BadValue, "truncated Prefix Exclude option");
    }

    // We can safely read the excluded prefix length and move forward.
    excluded_prefix_length_ = *begin++;

    // We parsed the excluded prefix length so we can now determine the
    // size of the IPv6 subnet id. The reminder of the option should
    // include data of that size. If the option size is lower than the
    // subnet id length we report an error.
    const unsigned int subnet_id_length = getSubnetIDLength();
    if (subnet_id_length > std::distance(begin, end)) {
        isc_throw(BadValue, "truncated Prefix Exclude option, expected "
                  "IPv6 subnet id length is " << subnet_id_length);
    }

    // Get binary representation of the delegated prefix.
    std::vector<uint8_t> delegated_prefix_bytes = delegated_prefix_.toBytes();
    //  We need to calculate how many bytes include the useful data and assign
    // zeros to remaining bytes (beyond the prefix length).
    const uint8_t bytes_length = (delegated_prefix_length_ / 8) +
        static_cast<uint8_t>(delegated_prefix_length_ % 8 != 0);
    std::fill(delegated_prefix_bytes.begin() + bytes_length,
              delegated_prefix_bytes.end(), 0);

    // Convert the delegated prefix to bit format.
    boost::dynamic_bitset<uint8_t> bits(delegated_prefix_bytes.rbegin(),
                                        delegated_prefix_bytes.rend());

    // Convert subnet id to bit format.
    std::vector<uint8_t> subnet_id_bytes(begin, end);
    boost::dynamic_bitset<uint8_t> subnet_id_bits(subnet_id_bytes.rbegin(),
                                                  subnet_id_bytes.rend());

    // Subnet id parsed, proceed to the end of the option.
    begin = end;

    // Concatenate the delegated prefix with subnet id. The resulting prefix
    // is an excluded prefix in bit format.
    for (int i = subnet_id_bits.size() - 1; i >= 0; --i) {
        bits.set(128 - delegated_prefix_length_ - subnet_id_bits.size() + i,
                 subnet_id_bits.test(i));
    }

    // Convert the prefix to binary format.
    std::vector<uint8_t> bytes(V6ADDRESS_LEN);
    boost::to_block_range(bits, bytes.rbegin());

    // And create a prefix object from bytes.
    excluded_prefix_ = IOAddress::fromBytes(AF_INET6, &bytes[0]);
}

uint16_t
Option6PDExclude::len() const {
    return (getHeaderLen() + sizeof(excluded_prefix_length_)
            + getSubnetIDLength());
}

std::string
Option6PDExclude::toText(int indent) const {
    std::ostringstream s;
    s << headerToText(indent) << ": ";
    s << excluded_prefix_ << "/"
      << static_cast<int>(excluded_prefix_length_);
    return (s.str());
}

uint8_t
Option6PDExclude::getSubnetIDLength() const {
    uint8_t subnet_id_length_bits = excluded_prefix_length_ -
        delegated_prefix_length_ - 1;
    uint8_t subnet_id_length = (subnet_id_length_bits / 8) + 1;
    return (subnet_id_length);
}

} // end of namespace isc::dhcp
} // end of namespace isc
