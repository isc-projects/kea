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

#include <string.h>
#include <exceptions/exceptions.h>
#include <dhcp/addr_utilities.h>

using namespace isc::asiolink;

const static uint32_t masks[] = { 0x00000000, 0x00000001, 0x00000003, 0x00000007,
                                  0x0000000f, 0x0000001f, 0x0000003f, 0x0000007f,
                                  0x000000ff, 0x000001ff, 0x000003ff, 0x000007ff,
                                  0x00000fff, 0x00001fff, 0x00003fff, 0x00007fff,
                                  0x0000ffff, 0x0001ffff, 0x0003ffff, 0x0007ffff,
                                  0x000fffff, 0x001fffff, 0x003fffff, 0x007fffff,
                                  0x00ffffff, 0x01ffffff, 0x03ffffff, 0x07ffffff,
                                  0x0fffffff, 0x1fffffff, 0x3fffffff, 0x7fffffff,
                                  0xffffffff };

const static uint8_t bitMask[]= { 0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };


namespace isc {
namespace dhcp {

isc::asiolink::IOAddress firstAddrInPrefix6(const isc::asiolink::IOAddress& prefix,
                                            uint8_t len) {

    uint8_t packed[V6ADDRESS_LEN];

    // First we copy the whole address as 16 bytes.
    memcpy(packed, prefix.getAddress().to_v6().to_bytes().data(), 16);

    // If the length is divisible by 8, it is simple. We just zero out the host
    // part. Otherwise we need to handle the byte that has to be partially
    // zeroed.
    if (len % 8 != 0) {

        // Get the appropriate mask. It has relevant bits (those that should
        // stay) set and irrelevant (those that should be wiped) cleared.
        uint8_t mask = bitMask[len % 8];

        // Let's leave only whatever the mask says should not be cleared.
        packed[len / 8] = packed[len / 8] & mask;

        // Since we have just dealt with this byte, let's move the prefix length
        // to the beginning of the next byte (len is expressed in bits).
        len = (len / 8 + 1) * 8;
    }

    // Clear out the remaining bits.
    for (int i = len / 8; i < sizeof(packed); ++i) {
        packed[i] = 0x0;
    }

    // Finally, let's wrap this into nice and easy IOAddress object.
    return (isc::asiolink::IOAddress::from_bytes(AF_INET6, packed));
}

isc::asiolink::IOAddress firstAddrInPrefix4(const isc::asiolink::IOAddress& prefix,
                                            uint8_t len) {
    uint32_t addr = prefix;
    if (len>32) {
        isc_throw(BadValue, "Too large netmask. 0..32 is allowed in IPv4");
    }

    return (IOAddress(addr & (~masks[32-len])));
}

isc::asiolink::IOAddress firstAddrInPrefix(const isc::asiolink::IOAddress& prefix,
                                            uint8_t len) {
    if (prefix.getFamily() == AF_INET) {
        return firstAddrInPrefix4(prefix, len);
    } else {
        return firstAddrInPrefix6(prefix, len);
    }
}

isc::asiolink::IOAddress lastAddrInPrefix4(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len) {
    uint32_t addr = prefix;
    if (len>32) {
        isc_throw(BadValue, "Too large netmask. 0..32 is allowed in IPv4");
    }

    return (IOAddress(addr | masks[32-len]));
}

isc::asiolink::IOAddress lastAddrInPrefix6(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len) {

    const static uint8_t bitMask[]= { 0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };
    uint8_t packed[V6ADDRESS_LEN];

    // First we copy the whole address as 16 bytes.
    memcpy(packed, prefix.getAddress().to_v6().to_bytes().data(), 16);

    // if the length is divisible by 8, it is simple. We just fill the host part
    // with ones. Otherwise we need to handle the byte that has to be partially
    // zeroed.
    if (len % 8 != 0) {
        // Get the appropriate mask. It has relevant bits (those that should
        // stay) set and irrelevant (those that should be set to 1) cleared.
        uint8_t mask = bitMask[len % 8];

        // Let's set those irrelevant bits with 1. It would be perhaps
        // easier to not use negation here and invert bitMask content. However,
        // with this approach, we can use the same mask in first and last
        // address calculations.
        packed[len / 8] = packed[len / 8] | ~mask;

        // Since we have just dealt with this byte, let's move the prefix length
        // to the beginning of the next byte (len is expressed in bits).
        len = (len / 8 + 1) * 8;
    }

    // Finally set remaining bits to 1.
    for (int i = len / 8; i < sizeof(packed); ++i) {
        packed[i] = 0xff;
    }

    // Finally, let's wrap this into nice and easy IOAddress object.
    return (isc::asiolink::IOAddress::from_bytes(AF_INET6, packed));
}

isc::asiolink::IOAddress lastAddrInPrefix(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len) {
    if (prefix.getFamily() == AF_INET) {
        return lastAddrInPrefix4(prefix, len);
    } else {
        return lastAddrInPrefix6(prefix, len);
    }
}

};
};
