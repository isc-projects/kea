// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_iaprefix.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <sstream>

#include <stdint.h>
#include <arpa/inet.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option6IAPrefix::Option6IAPrefix(uint16_t type, const isc::asiolink::IOAddress& prefix,
                                 uint8_t prefix_len, uint32_t pref, uint32_t valid)
    :Option6IAAddr(type, prefix, pref, valid), prefix_len_(prefix_len) {
    setEncapsulatedSpace("dhcp6");
    // Option6IAAddr will check if prefix is IPv6 and will throw if it is not
    if (prefix_len > 128) {
        isc_throw(BadValue, static_cast<unsigned>(prefix_len)
                  << " is not a valid prefix length. "
                  << "Allowed range is 0..128");
    }
}

Option6IAPrefix::Option6IAPrefix(uint32_t type, OptionBuffer::const_iterator begin,
                             OptionBuffer::const_iterator end)
    :Option6IAAddr(type, begin, end) {
    setEncapsulatedSpace("dhcp6");
    unpack(begin, end);
}

void Option6IAPrefix::pack(isc::util::OutputBuffer& buf) {
    if (!addr_.isV6()) {
        isc_throw(isc::BadValue, addr_ << " is not an IPv6 address");
    }

    buf.writeUint16(type_);

    // len() returns complete option length. len field contains
    // length without 4-byte option header
    buf.writeUint16(len() - getHeaderLen());

    buf.writeUint32(preferred_);
    buf.writeUint32(valid_);
    buf.writeUint8(prefix_len_);

    buf.writeData(&addr_.toBytes()[0], isc::asiolink::V6ADDRESS_LEN);

    // store encapsulated options (the only defined so far is PD_EXCLUDE)
    packOptions(buf);
}

void Option6IAPrefix::unpack(OptionBuffer::const_iterator begin,
                      OptionBuffer::const_iterator end) {
    if ( distance(begin, end) < OPTION6_IAPREFIX_LEN) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }

    preferred_ = readUint32(&(*begin), distance(begin, end));
    begin += sizeof(uint32_t);

    valid_ = readUint32(&(*begin), distance(begin, end));
    begin += sizeof(uint32_t);

    prefix_len_ = *begin;
    begin += sizeof(uint8_t);

    // 16 bytes: IPv6 address
    OptionBuffer address_with_mask;
    mask(begin, begin + V6ADDRESS_LEN, prefix_len_, address_with_mask);
    addr_ = IOAddress::fromBytes(AF_INET6, &(*address_with_mask.begin()));
    begin += V6ADDRESS_LEN;

    // unpack encapsulated options (the only defined so far is PD_EXCLUDE)
    unpackOptions(OptionBuffer(begin, end));
}

std::string Option6IAPrefix::toText(int indent) {
    std::stringstream output;
    output << headerToText(indent, "IAPREFIX") << ": "
           << "prefix=" << addr_ << "/" << static_cast<int>(prefix_len_)
           << ", preferred-lft=" << preferred_
           << ", valid-lft=" << valid_;

    output << suboptionsToText(indent + 2);
    return (output.str());
}

uint16_t Option6IAPrefix::len() {

    uint16_t length = OPTION6_HDR_LEN + OPTION6_IAPREFIX_LEN;

    // length of all suboptions
    for (OptionCollection::const_iterator it = options_.begin();
         it != options_.end(); ++it) {
        length += (*it).second->len();
    }
    return (length);
}

void
Option6IAPrefix::mask(OptionBuffer::const_iterator begin,
                      OptionBuffer::const_iterator end,
                      const uint8_t len,
                      OptionBuffer& output_address) {
    output_address.resize(16, 0);
    if (len >= 128) {
        std::copy(begin, end, output_address.begin());
    } else if (len > 0) {
        // All the bits that represent whole octets of the prefix are copied with
        // no change.
        std::copy(begin, begin + static_cast<uint8_t>(len/8), output_address.begin());
        // The remaining significant bits of the last octet have to be left unchanged,
        // but the remaining bits of this octet must be set to zero. The number of
        // significant bits is calculated as a reminder from the devision of the
        // prefix length by 8 (by size of the octet). The number of bits to be set
        // to zero is therefore calculated as: 8 - (len % 8).
        // Next, the mask is created by shifting the 0xFF by the number of bits
        // to be set to 0. By performing logical AND of this mask with the original
        // value of the last octet we get the final value for the new octet.
        output_address[len/8] = (*(begin + len/8) & (0xFF << (8 - (len % 8))));
    }
}


} // end of namespace isc::dhcp
} // end of namespace isc
