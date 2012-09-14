// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <util/addr_utilities.h>

namespace isc {
namespace util {

isc::asiolink::IOAddress firstAddrInPrefix(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len) {

    static char bitMask[]= { 0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };
    uint8_t packed[16];

    memcpy(packed, prefix.getAddress().to_v6().to_bytes().data(), 16);

    if (len % 8 != 0) {
        uint8_t mask = bitMask[len % 8];
        packed[len / 8] = packed[len / 8] & mask;
        len = (len/8 + 1) * 8;
    }
    for (int i = len / 8; i < 16; ++i) {
        packed[i] = 0x0;
    }

    return (isc::asiolink::IOAddress::from_bytes(AF_INET6, packed));
}

isc::asiolink::IOAddress lastAddrInPrefix(const isc::asiolink::IOAddress& prefix,
                                          uint8_t len) {

    static char bitMask[]= { 0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };
    uint8_t packed[16];

    memcpy(packed, prefix.getAddress().to_v6().to_bytes().data(), 16);

    if (len % 8 != 0) {
        uint8_t mask = bitMask[len % 8];
        packed[len / 8] = packed[len / 8] | ~mask;
        len = (len/8 + 1) * 8;
    }
    for (int i = len / 8; i < 16; ++i) {
        packed[i] = 0xff;
    }

    return (isc::asiolink::IOAddress::from_bytes(AF_INET6, packed));
}

};
};
