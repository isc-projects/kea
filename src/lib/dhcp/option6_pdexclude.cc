// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// Author: Cristian Secareanu <cristian.secareanu@qualitance.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option6_pdexclude.h>
#include <exceptions/exceptions.h>

#include <boost/dynamic_bitset.hpp>

#include <sstream>

#include <arpa/inet.h>
#include <stdint.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option6PDExclude::Option6PDExclude(
        const isc::asiolink::IOAddress& delegated_address,
        uint8_t delegated_prefix_length,
        const isc::asiolink::IOAddress& excluded_address,
        uint8_t excluded_prefix_length) :
    Option(V6, D6O_PD_EXCLUDE), delegated_address_(delegated_address),
    delegated_prefix_length_(delegated_prefix_length),
    excluded_address_(excluded_address),
    excluded_prefix_length_(excluded_prefix_length) {
}

void Option6PDExclude::pack(isc::util::OutputBuffer& buf) {
    // Header = option code and length.
    packHeader(buf);

    buf.writeData(&excluded_prefix_length_, sizeof(excluded_prefix_length_));

    std::vector<uint8_t> excluded_address_bytes = excluded_address_.toBytes();
    boost::dynamic_bitset<uint8_t> bits(excluded_address_bytes.rbegin(), excluded_address_bytes.rend());
    bits = bits << delegated_prefix_length_;

    uint8_t subtractedPrefixesOctetLength = getSubtractedPrefixesOctetLength();
    for (uint8_t i = 0U; i < subtractedPrefixesOctetLength; i++) {
        boost::dynamic_bitset<uint8_t> tmp = bits >> 120;

        uint8_t val = static_cast<uint8_t>(tmp.to_ulong());

        //Zero padded bits follow when excluded_prefix_length_ is not divided exactly by 8
        if (i == subtractedPrefixesOctetLength - 1U) {
            uint8_t subtractedPrefixesBitLength = excluded_prefix_length_ -
                    delegated_prefix_length_;
            uint8_t zeroPaddingBitLength = (8 - (subtractedPrefixesBitLength % 8)) % 8;
            val <<= zeroPaddingBitLength;
        }
        bits = bits << 8;
        buf.writeData(&val, sizeof(val));
    }
}

void Option6PDExclude::unpack(OptionBufferConstIter begin,
        OptionBufferConstIter end) {
    delegated_prefix_length_ = 0;
    excluded_prefix_length_ = *begin;
    begin += sizeof(uint8_t);
    delegated_address_ = IOAddress::IPV6_ZERO_ADDRESS();
    excluded_address_ = IOAddress::IPV6_ZERO_ADDRESS();
    begin = end;
}

uint16_t Option6PDExclude::len() {
    return getHeaderLen() + sizeof(excluded_prefix_length_)
            + getSubtractedPrefixesOctetLength();
}

uint8_t Option6PDExclude::getSubtractedPrefixesOctetLength() {
    // Promote what is less than 8 bits to 1 octet.
    uint8_t subtractedPrefixesBitLength = excluded_prefix_length_
            - delegated_prefix_length_ - 1;
    uint8_t subtractedPrefixesOctetLength = (subtractedPrefixesBitLength / 8) + 1;
    return subtractedPrefixesOctetLength;
}

} // end of namespace isc::dhcp
} // end of namespace isc
