// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option6_pdexclude.h>
#include <exceptions/exceptions.h>
#include <util/encode/hex.h>
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
      excluded_prefix_length_(excluded_prefix_length),
      subnet_id_() {

    // Expecting v6 prefixes of sane length.
    if (!delegated_prefix.isV6() || !excluded_prefix.isV6() ||
        (delegated_prefix_length > 128) || (excluded_prefix_length_ > 128)) {
        isc_throw(BadValue, "invalid delegated or excluded prefix values specified: "
                  << delegated_prefix << "/"
                  << static_cast<int>(delegated_prefix_length) << ", "
                  << excluded_prefix << "/"
                  << static_cast<int>(excluded_prefix_length_));
    }

    // Excluded prefix must be longer than or equal to the delegated prefix.
    if (excluded_prefix_length_ <= delegated_prefix_length) {
        isc_throw(BadValue, "length of the excluded prefix "
                  << excluded_prefix << "/"
                  << static_cast<int>(excluded_prefix_length_)
                  << " must be greater than the length of the"
                  " delegated prefix " << delegated_prefix << "/"
                  << static_cast<int>(delegated_prefix_length));
    }

    // Both prefixes must share common part with a length equal to the
    // delegated prefix length.
    std::vector<uint8_t> delegated_prefix_bytes = delegated_prefix.toBytes();
    boost::dynamic_bitset<uint8_t> delegated_prefix_bits(delegated_prefix_bytes.rbegin(),
                                                         delegated_prefix_bytes.rend());

    std::vector<uint8_t> excluded_prefix_bytes = excluded_prefix.toBytes();
    boost::dynamic_bitset<uint8_t> excluded_prefix_bits(excluded_prefix_bytes.rbegin(),
                                                        excluded_prefix_bytes.rend());


    // See RFC6603, section 4.2: assert(p1>>s == p2>>s)
    const uint8_t delta = 128 - delegated_prefix_length;

    if ((delegated_prefix_bits >> delta) != (excluded_prefix_bits >> delta)) {
        isc_throw(BadValue, "excluded prefix "
                  << excluded_prefix << "/"
                  << static_cast<int>(excluded_prefix_length_)
                  << " must have the same common prefix part of "
                  << static_cast<int>(delegated_prefix_length)
                  << " as the delegated prefix "
                  << delegated_prefix << "/"
                  << static_cast<int>(delegated_prefix_length));
    }


    // Shifting prefix by delegated prefix length leaves us with only a
    // subnet id part of the excluded prefix.
    excluded_prefix_bits <<= delegated_prefix_length;

    // Calculate subnet id length.
    const uint8_t subnet_id_length = getSubnetIDLength(delegated_prefix_length,
                                                       excluded_prefix_length);
    for (uint8_t i = 0; i < subnet_id_length; ++i) {
        // Retrieve bit representation of the current byte.
        const boost::dynamic_bitset<uint8_t> first_byte = excluded_prefix_bits >> 120;

        // Convert it to a numeric value.
        uint8_t val = static_cast<uint8_t>(first_byte.to_ulong());

        // Zero padded excluded_prefix_bits follow when excluded_prefix_length_ is
        // not divisible by 8.
        if (i == subnet_id_length - 1) {
            uint8_t length_delta = excluded_prefix_length_ - delegated_prefix_length;
            if (length_delta % 8 != 0) {
                uint8_t mask = 0xFF;
                mask <<= (8 - (length_delta % 8));
                val &= mask;
            }
        }
        // Store calculated value in a buffer.
        subnet_id_.push_back(val);

        // Go to the next byte.
        excluded_prefix_bits <<= 8;
    }
}

Option6PDExclude::Option6PDExclude(OptionBufferConstIter begin,
                                   OptionBufferConstIter end)
    : Option(V6, D6O_PD_EXCLUDE),
      excluded_prefix_length_(0),
      subnet_id_() {
    unpack(begin, end);
}

OptionPtr
Option6PDExclude::clone() const {
    return (cloneInternal<Option6PDExclude>());
}

void
Option6PDExclude::pack(isc::util::OutputBuffer& buf, bool) const {
    // Make sure that the subnet identifier is valid. It should never
    // be empty.
    if ((excluded_prefix_length_ == 0) || subnet_id_.empty()) {
        isc_throw(BadValue, "subnet identifier of a Prefix Exclude option"
                  " must not be empty");
    }

    // Header = option code and length.
    packHeader(buf);

    // Excluded prefix length is always 1 byte long field.
    buf.writeUint8(excluded_prefix_length_);

    // Write the subnet identifier.
    buf.writeData(static_cast<const void*>(&subnet_id_[0]), subnet_id_.size());
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
    uint8_t excluded_prefix_length = *begin++;
    if (excluded_prefix_length == 0) {
        isc_throw(BadValue, "excluded prefix length must not be 0");
    }

    std::vector<uint8_t> subnet_id_bytes(begin, end);

    // Subnet id parsed, proceed to the end of the option.
    begin = end;

    uint8_t last_bits_num = excluded_prefix_length % 8;
    if (last_bits_num > 0) {
        *subnet_id_bytes.rbegin() = (*subnet_id_bytes.rbegin() >> (8 - last_bits_num)
                                     << (8 - (last_bits_num)));
    }

    excluded_prefix_length_ = excluded_prefix_length;
    subnet_id_.swap(subnet_id_bytes);
}

uint16_t
Option6PDExclude::len() const {
    return (getHeaderLen() + sizeof(excluded_prefix_length_) + subnet_id_.size());
}

std::string
Option6PDExclude::toText(int indent) const {
    std::ostringstream s;
    s << headerToText(indent) << ": ";
    s << "excluded-prefix-len=" << static_cast<unsigned>(excluded_prefix_length_)
      << ", subnet-id=0x" << util::encode::encodeHex(subnet_id_);
    return (s.str());
}

asiolink::IOAddress
Option6PDExclude::getExcludedPrefix(const IOAddress& delegated_prefix,
                                    const uint8_t delegated_prefix_length) const {
    // Get binary representation of the delegated prefix.
    std::vector<uint8_t> delegated_prefix_bytes = delegated_prefix.toBytes();
    //  We need to calculate how many bytes include the useful data and assign
    // zeros to remaining bytes (beyond the prefix length).
    const uint8_t bytes_length = (delegated_prefix_length / 8) +
        static_cast<uint8_t>(delegated_prefix_length % 8 != 0);
    std::fill(delegated_prefix_bytes.begin() + bytes_length,
              delegated_prefix_bytes.end(), 0);

    // Convert the delegated prefix to bit format.
    boost::dynamic_bitset<uint8_t> bits(delegated_prefix_bytes.rbegin(),
                                        delegated_prefix_bytes.rend());

    boost::dynamic_bitset<uint8_t> subnet_id_bits(subnet_id_.rbegin(),
                                                  subnet_id_.rend());

    // Concatenate the delegated prefix with subnet id. The resulting prefix
    // is an excluded prefix in bit format.
    for (int i = subnet_id_bits.size() - 1; i >= 0; --i) {
        bits.set(128 - delegated_prefix_length - subnet_id_bits.size() + i,
                 subnet_id_bits.test(i));
    }

    // Convert the prefix to binary format.
    std::vector<uint8_t> bytes(V6ADDRESS_LEN);
    boost::to_block_range(bits, bytes.rbegin());

    // And create a prefix object from bytes.
    return (IOAddress::fromBytes(AF_INET6, &bytes[0]));
}

uint8_t
Option6PDExclude::getSubnetIDLength(const uint8_t delegated_prefix_length,
                                    const uint8_t excluded_prefix_length) const {
    uint8_t subnet_id_length_bits = excluded_prefix_length -
        delegated_prefix_length - 1;
    uint8_t subnet_id_length = (subnet_id_length_bits / 8) + 1;
    return (subnet_id_length);
}

} // end of namespace isc::dhcp
} // end of namespace isc
