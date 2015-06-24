// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/addr_utilities.h>
#include <exceptions/exceptions.h>

#include <vector>
#include <limits>
#include <string.h>

using namespace isc;
using namespace isc::asiolink;

namespace {

/// @brief mask used for first/last address calculation in a IPv4 prefix
///
/// Using a static mask is faster than calculating it dynamically every time.
const uint32_t bitMask4[] = { 0xffffffff, 0x7fffffff, 0x3fffffff, 0x1fffffff,
                              0x0fffffff, 0x07ffffff, 0x03ffffff, 0x01ffffff,
                              0x00ffffff, 0x007fffff, 0x003fffff, 0x001fffff,
                              0x000fffff, 0x0007ffff, 0x0003ffff, 0x0001ffff,
                              0x0000ffff, 0x00007fff, 0x00003fff, 0x00001fff,
                              0x00000fff, 0x000007ff, 0x000003ff, 0x000001ff,
                              0x000000ff, 0x0000007f, 0x0000003f, 0x0000001f,
                              0x0000000f, 0x00000007, 0x00000003, 0x00000001,
                              0x00000000 };

/// @brief mask used for first/last address calculation in a IPv6 prefix
const uint8_t bitMask6[]= { 0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };

/// @brief calculates the first IPv6 address in a IPv6 prefix
///
/// Note: This is a private function. Do not use it directly.
/// Please use firstAddrInPrefix() instead.
///
/// @param prefix IPv6 prefix
/// @param len prefix length
isc::asiolink::IOAddress firstAddrInPrefix6(const isc::asiolink::IOAddress& prefix,
                                            uint8_t len) {
    if (len > 128) {
        isc_throw(isc::BadValue,
                  "Too large netmask. 0..128 is allowed in IPv6");
    }

    // First we copy the whole address as 16 bytes.
    // We don't check that it is a valid IPv6 address and thus has
    // the required length because it is already checked by
    // the calling function.
    uint8_t packed[V6ADDRESS_LEN];
    memcpy(packed, &prefix.toBytes()[0], V6ADDRESS_LEN);

    // If the length is divisible by 8, it is simple. We just zero out the host
    // part. Otherwise we need to handle the byte that has to be partially
    // zeroed.
    if (len % 8 != 0) {

        // Get the appropriate mask. It has relevant bits (those that should
        // stay) set and irrelevant (those that should be wiped) cleared.
        uint8_t mask = bitMask6[len % 8];

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
    return (isc::asiolink::IOAddress::fromBytes(AF_INET6, packed));
}

/// @brief calculates the first IPv4 address in a IPv4 prefix
///
/// Note: This is a private function. Do not use it directly.
/// Please use firstAddrInPrefix() instead.
///
/// @param prefix IPv4 prefix
/// @param len netmask length (0-32)
isc::asiolink::IOAddress firstAddrInPrefix4(const isc::asiolink::IOAddress& prefix,
                                            uint8_t len) {
    if (len > 32) {
        isc_throw(isc::BadValue, "Too large netmask. 0..32 is allowed in IPv4");
    }

    // We don't check that it is a valid IPv4 address and thus has
    // a required length of 4 bytes because it has been already
    // checked by the calling function.
    uint32_t addr = prefix;
    return (IOAddress(addr & (~bitMask4[len])));
}

/// @brief calculates the last IPv4 address in a IPv4 prefix
///
/// Note: This is a private function. Do not use it directly.
/// Please use firstAddrInPrefix() instead.
///
/// @param prefix IPv4 prefix that we calculate first address for
/// @param len netmask length (0-32)
isc::asiolink::IOAddress lastAddrInPrefix4(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len) {
    if (len > 32) {
        isc_throw(isc::BadValue, "Too large netmask. 0..32 is allowed in IPv4");
    }

    uint32_t addr = prefix;
    return (IOAddress(addr | bitMask4[len]));
}

/// @brief calculates the last IPv6 address in a IPv6 prefix
///
/// Note: This is a private function. Do not use it directly.
/// Please use lastAddrInPrefix() instead.
///
/// @param prefix IPv6 prefix that we calculate first address for
/// @param len netmask length (0-128)
isc::asiolink::IOAddress lastAddrInPrefix6(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len) {
    if (len > 128) {
        isc_throw(isc::BadValue,
                  "Too large netmask. 0..128 is allowed in IPv6");
    }

    // First we copy the whole address as 16 bytes.
    uint8_t packed[V6ADDRESS_LEN];
    memcpy(packed, &prefix.toBytes()[0], 16);

    // if the length is divisible by 8, it is simple. We just fill the host part
    // with ones. Otherwise we need to handle the byte that has to be partially
    // zeroed.
    if (len % 8 != 0) {
        // Get the appropriate mask. It has relevant bits (those that should
        // stay) set and irrelevant (those that should be set to 1) cleared.
        uint8_t mask = bitMask6[len % 8];

        // Let's set those irrelevant bits with 1. It would be perhaps
        // easier to not use negation here and invert bitMask6 content. However,
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
    return (isc::asiolink::IOAddress::fromBytes(AF_INET6, packed));
}

}; // end of anonymous namespace

namespace isc {
namespace dhcp {

isc::asiolink::IOAddress firstAddrInPrefix(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len) {
    if (prefix.isV4()) {
        return (firstAddrInPrefix4(prefix, len));

    } else {
        return (firstAddrInPrefix6(prefix, len));

    }
}

isc::asiolink::IOAddress lastAddrInPrefix(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len) {
    if (prefix.isV4()) {
        return (lastAddrInPrefix4(prefix, len));

    } else {
        return (lastAddrInPrefix6(prefix, len));

    }
}

isc::asiolink::IOAddress getNetmask4(uint8_t len) {
    if (len > 32) {
      isc_throw(BadValue, "Invalid netmask size "
                << static_cast<unsigned>(len) << ", allowed range is 0..32");
    }
    uint32_t x = ~bitMask4[len];

    return (IOAddress(x));
}

uint64_t
addrsInRange(const isc::asiolink::IOAddress& min,
             const isc::asiolink::IOAddress& max) {
    if (min.getFamily() != max.getFamily()) {
        isc_throw(BadValue, "Both addresses have to be the same family");
    }

    if (max < min) {
        isc_throw(BadValue, min.toText() << " must not be greater than "
                  << max.toText());
    }

    if (min.isV4()) {
        // Let's explicitly cast last_ and first_ (IOAddress). This conversion is
        // automatic, but let's explicitly cast it show that we moved to integer
        // domain and addresses are now substractable.
        uint64_t max_numeric = static_cast<uint32_t>(max);
        uint64_t min_numeric = static_cast<uint32_t>(min);

        // We can simply subtract the values. We need to increase the result
        // by one, as both min and max are included in the range. So even if
        // min == max, there's one address.
        return (max_numeric - min_numeric + 1);
    } else {

        // Calculating the difference in v6 is more involved. Let's subtract
        // one from the other. By subtracting min from max, we move the
        // [a, b] range to the [0, (b-a)] range. We don't care about the beginning
        // of the new range (it's always zero). The upper bound now specifies
        // the number of addresses minus one.
        IOAddress count = IOAddress::subtract(max, min);

        // There's one very special case. Someone is trying to check how many
        // IPv6 addresses are in IPv6 address space. He called this method
        // with ::, ffff:ffff:ffff:fffff:ffff:ffff:ffff:ffff. The diff is also
        // all 1s. Had we increased it by one, the address would flip to all 0s.
        // This will not happen in a real world. Apparently, unit-tests are
        // sometimes nastier then a real world.
        static IOAddress max6("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff");
        if (count == max6) {
            return (std::numeric_limits<uint64_t>::max());
        }

        // Increase it by one (a..a range still contains one address, even though
        // a subtracted from a is zero).
        count = IOAddress::increase(count);

        // We don't have uint128, so for anything greater than 2^64, we'll just
        // assume numeric_limits<uint64_t>::max. Let's do it the manual way.
        const std::vector<uint8_t>& bin(count.toBytes());

        // If any of the most significant 64 bits is set, we have more than
        // 2^64 addresses and can't represent it even on uint64_t.
        for (int i = 0 ; i < 8; i++) {
            if (bin[i]) {
                return (std::numeric_limits<uint64_t>::max());
            }
        }

        // Ok, we're good. The pool is sanely sized. It may be huge, but at least
        // that's something we can represent on uint64_t.
        uint64_t numeric = 0;
        for (int i = 8; i < 16; i++) {
            numeric <<= 8;
            numeric += bin[i];
        }

        return (numeric);
    }
}

uint64_t prefixesInRange(const uint8_t pool_len, const uint8_t delegated_len) {
    if (delegated_len < pool_len) {
        return (0);
    }

    uint64_t count = delegated_len - pool_len;

    if (count == 0) {
        // If we want to delegate /64 out of /64 pool, we have only
        // one prefix.
        return (1);
    } else if (count >= 64) {
        // If the difference is greater than or equal 64, e.g. we want to
        // delegate /96 out of /16 pool, the number is bigger than we can
        // express, so we'll stick with maximum value of uint64_t.
        return (std::numeric_limits<uint64_t>::max());
    } else {
        // Now count specifies the exponent (e.g. if the difference between the
        // delegated and pool length is 4, we have 16 prefixes), so we need
        // to calculate 2^(count - 1)
        return ((static_cast<uint64_t>(2)) << (count - 1));
    }
}

};
};
