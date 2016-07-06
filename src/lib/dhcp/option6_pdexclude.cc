// Copyright (C) 2015 - 2016 Deutsche Telekom AG.
//
// Author: Cristian Secareanu <cristian.secareanu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_pdexclude.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

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

Option6PDExclude::Option6PDExclude(const isc::asiolink::IOAddress& addr,
                                   uint8_t prefix_len,
                                   const isc::asiolink::IOAddress& prefix_excluded,
                                   uint8_t prefix_excluded_len
                                   )
    :Option(V6, D6O_PD_EXCLUDE)
    ,addr_(addr), prefix_len_(prefix_len)
    ,prefix_excluded_(prefix_excluded)
    ,prefix_excluded_len_(prefix_excluded_len) {

}

void
Option6PDExclude::pack(isc::util::OutputBuffer& buf) {
    // Header = option code and length.
    packHeader(buf);

    uint8_t excludedPrefLenBytes = excludedPrefixLenBytes();

    buf.writeData(&prefix_excluded_len_, sizeof(prefix_excluded_len_));

    std::vector<uint8_t> addrV6 = prefix_excluded_.toBytes();
    boost::dynamic_bitset<uint8_t> bits(addrV6.rbegin(), addrV6.rend());
    bits = bits << prefix_len_;

    for (int i = 0; i < excludedPrefLenBytes; i++) {
        boost::dynamic_bitset<uint8_t> tmp = bits >> 120;

        uint8_t val = static_cast<uint8_t>(tmp.to_ulong());

        //Zero padded bits follow when prefix_excluded_len_ is not divided exactly by 8
        if (i == excludedPrefLenBytes - 1) {
            uint8_t excluded_prefix_bits_no = prefix_excluded_len_ - prefix_len_;

            uint8_t unusedBits = 0xFF;
            unusedBits <<= (8 - (excluded_prefix_bits_no % 8)) % 8;

            val = val & unusedBits;
        }
        bits = bits << 8;
        buf.writeData(&val, sizeof(val));
    }
}

void Option6PDExclude::unpack(OptionBufferConstIter begin,
                              OptionBufferConstIter end) {
    prefix_len_ = 0;
    prefix_excluded_len_ = *begin;
    begin += sizeof(uint8_t);
    addr_ = IOAddress::IPV6_ZERO_ADDRESS();
    prefix_excluded_ = IOAddress::IPV6_ZERO_ADDRESS();
    begin = end;
}

uint16_t
Option6PDExclude::len()
{
    return getHeaderLen() + sizeof (prefix_excluded_len_) +
            excludedPrefixLenBytes();
}

uint8_t
Option6PDExclude::excludedPrefixLenBytes()
{
    uint8_t excludedPrefLenBits = prefix_excluded_len_ - prefix_len_ - 1;
    uint8_t excludedPrefLenBytes = (excludedPrefLenBits / 8) + 1;
    return excludedPrefLenBytes;
}

} // end of namespace isc::dhcp
} // end of namespace isc
