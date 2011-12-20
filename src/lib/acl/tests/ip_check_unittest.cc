// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <gtest/gtest.h>
#include <acl/ip_check.h>

#include "sockaddr.h"

using namespace isc::acl;
using namespace isc::acl::internal;
using namespace std;

namespace {
const size_t IPV4_SIZE = 4;
const size_t IPV6_SIZE = 16;

// Simple struct holding either an IPV4 or IPV6 address.  This is the "Context"
// used for the tests.
//
// The structure is also used for converting an IPV4 address to a four-byte
// array.
struct GeneralAddress {
    int             family;     // Family of the address
    vector<uint8_t> addr;       // Address type.  Size indicates what it holds

    // Convert uint32_t address in host-byte order to a uint8_t vector in
    // network-byte order.
    vector<uint8_t> convertUint32(uint32_t address) {
        BOOST_STATIC_ASSERT(sizeof(uint32_t) == IPV4_SIZE);

        vector<uint8_t> result(IPV4_SIZE);

        // Address is in network-byte order, so copy to the array.  The
        // MS byte is at the lowest address.
        result[3] = address & 0xff;
        result[2] = (address >> 8) & 0xff;
        result[1] = (address >> 16) & 0xff;
        result[0] = (address >> 24) & 0xff;

        return (result);
    }

    // Convenience constructor for V4 address.  As it is not marked as explicit,
    // it allows the automatic promotion of a uint32_t to a GeneralAddress data
    // type in calls to matches().
    GeneralAddress(uint32_t address) : family(AF_INET), addr()
    {
        addr = convertUint32(address);
    }

    // Convenience constructor for V6 address.  As it is not marked as explicit,
    // it allows the automatic promotion of a vector<uint8_t> to a
    // GeneralAddress data type in calls to matches().
    GeneralAddress(const vector<uint8_t>& address) : family(AF_INET6),
                                                     addr(address)
    {
        if (address.size() != IPV6_SIZE) {
            isc_throw(isc::InvalidParameter, "vector passed to GeneralAddress "
                      "constructor is " << address.size() << " bytes long - it "
                      "should be " << IPV6_SIZE << " bytes instead");
        }
    }

    // A couple of convenience methods for checking equality with different
    // representations of an address.

    // Check that the IPV4 address is the same as that given.
    bool equals(uint32_t address) {
        if (family == AF_INET) {
            const vector<uint8_t> byte_address = convertUint32(address);
            return (equal(byte_address.begin(), byte_address.end(),
                           addr.begin()));
        }
        return (false);
    }

    // Check that the array is equal to that given.
    bool equals(const vector<uint8_t>& byte_address) {
        if (addr.size() == byte_address.size()) {
            return (equal(byte_address.begin(), byte_address.end(),
                           addr.begin()));
        }
        return (false);
    }
};
} // Unnamed namespace

// Provide a specialisation of the IPCheck::matches() method for the
// GeneralAddress class.

namespace isc  {
namespace acl {
template <>
bool IPCheck<GeneralAddress>::matches(const GeneralAddress& address) const {
    return (compare(&address.addr[0], address.family));
}
} // namespace acl
} // namespace isc

namespace {
/// *** Free Function Tests ***

// Test the createMask() function.
TEST(IPFunctionCheck, CreateMask) {

    // Invalid arguments should throw.
    EXPECT_THROW(createMask(9), isc::OutOfRange);

    // Check on all possible 8-bit values.
    uint16_t expected = 0xff00;
    for (size_t i = 0; i <= 8; ++i, expected >>= 1) {
        EXPECT_EQ(static_cast<uint8_t>(expected & 0xff), createMask(i));
    }
}

// Test the splitIPAddress() function.
TEST(IPFunctionCheck, SplitIPAddress) {
    pair<string, uint32_t> result;

    result = splitIPAddress("192.0.2.1");
    EXPECT_EQ(string("192.0.2.1"), result.first);
    EXPECT_EQ(-1, result.second);

    result = splitIPAddress("192.0.2.1/24");
    EXPECT_EQ(string("192.0.2.1"), result.first);
    EXPECT_EQ(24, result.second);

    result = splitIPAddress("2001:db8::/128");
    EXPECT_EQ(string("2001:db8::"), result.first);
    EXPECT_EQ(128, result.second);

    result = splitIPAddress("192.0.2.1/0");
    EXPECT_EQ(string("192.0.2.1"), result.first);
    EXPECT_EQ(0, result.second);

    EXPECT_THROW(splitIPAddress("192.0.2.43/27 "), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress("192.0.2.43/-1"), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress("192.0.2.43//1"), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress("192.0.2.43/1/"), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress("/192.0.2.43/1"), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress("2001:db8::/xxxx"), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress("2001:db8::/32/s"), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress("1/"), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress("/1"), isc::InvalidParameter);
    EXPECT_THROW(splitIPAddress(" 1/ "), isc::InvalidParameter);
}

TEST(IPAddress, constructIPv4) {
    IPAddress ipaddr(tests::getSockAddr("192.0.2.1"));
    const uint8_t expected_data[4] = { 192, 0, 2, 1 };
    EXPECT_EQ(AF_INET, ipaddr.getFamily());
    EXPECT_EQ(4, ipaddr.getLength());
    EXPECT_EQ(0, memcmp(expected_data, ipaddr.getData(), 4));
}

TEST(IPAddress, constructIPv6) {
    IPAddress ipaddr(tests::getSockAddr("2001:db8:1234:abcd::53"));
    const uint8_t expected_data[16] = { 0x20, 0x01, 0x0d, 0xb8, 0x12, 0x34, 0xab,
                                        0xcd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x53 };
    EXPECT_EQ(AF_INET6, ipaddr.getFamily());
    EXPECT_EQ(16, ipaddr.getLength());
    EXPECT_EQ(0, memcmp(expected_data, ipaddr.getData(), 16));
}

TEST(IPAddress, badConstruct) {
    struct sockaddr sa;
    sa.sa_family = AF_UNSPEC;
    EXPECT_THROW(IPAddress ipaddr(sa), isc::BadValue);
}

// *** IPv4 Tests ***

TEST(IPCheck, V4StringConstructor) {

    // Constructor with no prefix length given (32 is assumed).
    IPCheck<GeneralAddress> acl1("192.0.2.255");
    EXPECT_EQ(32, acl1.getPrefixlen());
    EXPECT_EQ(AF_INET, acl1.getFamily());

    vector<uint8_t> stored1 = acl1.getAddress();
    EXPECT_EQ(IPV4_SIZE, stored1.size());
    GeneralAddress expected1(0xc00002ff);
    EXPECT_TRUE(expected1.equals(stored1));

    // Constructor with valid mask given
    IPCheck<GeneralAddress> acl2("192.0.2.0/24");
    EXPECT_EQ(24, acl2.getPrefixlen());
    EXPECT_EQ(AF_INET, acl2.getFamily());

    vector<uint8_t> stored2 = acl2.getAddress();
    EXPECT_EQ(IPV4_SIZE, stored2.size());
    GeneralAddress expected2(0xc0000200);
    EXPECT_TRUE(expected2.equals(stored2));

    // More valid masks
    IPCheck<GeneralAddress> acl3("192.0.2.1/0");
    EXPECT_EQ(0, acl3.getPrefixlen());
    EXPECT_EQ(AF_INET, acl3.getFamily());

    vector<uint8_t> stored3 = acl3.getAddress();
    EXPECT_EQ(IPV4_SIZE, stored3.size());
    GeneralAddress expected3(0xc0000201);
    EXPECT_TRUE(expected3.equals(stored3));

    IPCheck<GeneralAddress> acl4("192.0.2.2/32");
    EXPECT_EQ(32, acl4.getPrefixlen());
    EXPECT_EQ(AF_INET, acl4.getFamily());

    vector<uint8_t> stored4 = acl4.getAddress();
    EXPECT_EQ(IPV4_SIZE, stored4.size());
    GeneralAddress expected4(0xc0000202);
    EXPECT_TRUE(expected4.equals(stored4));

    // Any match
    IPCheck<GeneralAddress> acl5("any4");
    EXPECT_EQ(0, acl5.getPrefixlen());
    EXPECT_EQ(AF_INET, acl5.getFamily());

    vector<uint8_t> stored5 = acl5.getAddress();
    EXPECT_EQ(IPV4_SIZE, stored5.size());
    GeneralAddress expected5(0);
    EXPECT_TRUE(expected5.equals(stored5));

    // Invalid prefix lengths
    EXPECT_THROW(IPCheck<GeneralAddress>("192.0.2.0/33"), isc::OutOfRange);

    // ... and invalid strings
    EXPECT_THROW(IPCheck<GeneralAddress>("192.0.2.0/-1"),
                 isc::InvalidParameter);
    EXPECT_THROW(IPCheck<GeneralAddress>("192.0.2.0/24/3"),
                 isc::InvalidParameter);
    EXPECT_THROW(IPCheck<GeneralAddress>("192.0.2.0/ww"),
                 isc::InvalidParameter);
    EXPECT_THROW(IPCheck<GeneralAddress>("aa.255.255.0/ww"),
                 isc::InvalidParameter);
}

TEST(IPCheck, V4CopyConstructor) {
    IPCheck<GeneralAddress> acl1("192.0.2.1/24");
    IPCheck<GeneralAddress> acl2(acl1);

    EXPECT_EQ(acl1.getPrefixlen(), acl2.getPrefixlen());
    EXPECT_EQ(acl1.getFamily(), acl2.getFamily());

    vector<uint8_t> net1 = acl1.getMask();
    vector<uint8_t> net2 = acl2.getMask();
    EXPECT_EQ(net1.size(), net2.size());
    EXPECT_TRUE(equal(net1.begin(), net1.end(), net2.begin()));

    net1 = acl1.getAddress();
    net2 = acl2.getAddress();
    EXPECT_EQ(net1.size(), net2.size());
    EXPECT_TRUE(equal(net1.begin(), net1.end(), net2.begin()));
}

TEST(IPCheck, V4AssignmentOperator) {
    IPCheck<GeneralAddress> acl1("192.0.2.0/24");
    IPCheck<GeneralAddress> acl2("192.0.2.128/25");
    acl2 = acl1;

    EXPECT_EQ(acl1.getPrefixlen(), acl2.getPrefixlen());
    EXPECT_EQ(acl1.getFamily(), acl2.getFamily());

    vector<uint8_t> net1 = acl1.getMask();
    vector<uint8_t> net2 = acl2.getMask();
    EXPECT_EQ(net1.size(), net2.size());
    EXPECT_TRUE(equal(net1.begin(), net1.end(), net2.begin()));

    net1 = acl1.getAddress();
    net2 = acl2.getAddress();
    EXPECT_EQ(net1.size(), net2.size());
    EXPECT_TRUE(equal(net1.begin(), net1.end(), net2.begin()));
}

// Check that the comparison works - note that "matches" just calls the
// internal compare() code. (Also note that the argument to matches() will be
// automatically converted to the GeneralAddress data type used for the tests
// because of its constructor taking a uint32_t argument.

TEST(IPCheck, V4Compare) {
    // Exact address - match if given address matches stored address.
    IPCheck<GeneralAddress> acl1("192.0.2.255/32");
    EXPECT_TRUE(acl1.matches(0xc00002ff));
    EXPECT_FALSE(acl1.matches(0xc00002fe));
    EXPECT_FALSE(acl1.matches(0x13457f13));

    IPCheck<GeneralAddress> acl2("192.0.2.255/27");
    EXPECT_TRUE(acl2.matches(0xc00002ff));
    EXPECT_TRUE(acl2.matches(0xc00002fe));
    EXPECT_TRUE(acl2.matches(0xc00002ee));
    EXPECT_FALSE(acl2.matches(0xc00002de));
    EXPECT_FALSE(acl2.matches(0xd00002fe));
    EXPECT_FALSE(acl2.matches(0x13457f13));

    // Match if "any4" is specified
    IPCheck<GeneralAddress> acl3("any4");
    EXPECT_TRUE(acl3.matches(0xc00002ff));
    EXPECT_TRUE(acl3.matches(0xc00002fe));
    EXPECT_TRUE(acl3.matches(0xc00002ee));
    EXPECT_TRUE(acl3.matches(0xc00002de));
    EXPECT_TRUE(acl3.matches(0xd00002fe));
    EXPECT_TRUE(acl3.matches(0x13457f13));

    IPCheck<GeneralAddress> acl4("0.0.0.0/0");
    EXPECT_TRUE(acl4.matches(0xc00002ff));
    EXPECT_TRUE(acl4.matches(0xc00002fe));
    EXPECT_TRUE(acl4.matches(0xc00002ee));
    EXPECT_TRUE(acl4.matches(0xc00002de));
    EXPECT_TRUE(acl4.matches(0xd00002fe));
    EXPECT_TRUE(acl4.matches(0x13457f13));

    IPCheck<GeneralAddress> acl5("192.0.2.255/0");
    EXPECT_TRUE(acl5.matches(0xc00002ff));
    EXPECT_TRUE(acl5.matches(0xc00002fe));
    EXPECT_TRUE(acl5.matches(0xc00002ee));
    EXPECT_TRUE(acl5.matches(0xc00002de));
    EXPECT_TRUE(acl5.matches(0xd00002fe));
    EXPECT_TRUE(acl5.matches(0x13457f13));
}

// *** IPV6 Tests ***

// Some constants used in the tests

const char* V6ADDR_1_STRING = "2001:0db8:1122:3344:5566:7788:99aa:bbcc";
const uint8_t V6ADDR_1[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x11, 0x22, 0x33, 0x44,
    0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc
};

const char* V6ADDR_2_STRING = "2001:0db8::dead:beef";
const uint8_t V6ADDR_2[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 48 bits
const uint8_t V6ADDR_2_48[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0xff, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 49 bits
const uint8_t V6ADDR_2_49[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x7f, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 50 bits
const uint8_t V6ADDR_2_50[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x3f, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 51 bits
const uint8_t V6ADDR_2_51[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x1f, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 51 bits
const uint8_t V6ADDR_2_52[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x0f, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 127 bits
const uint8_t V6ADDR_2_127[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xee
};

const uint8_t V6ADDR_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};

const uint8_t V6ADDR_4[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

TEST(IPCheck, V6StringConstructor) {
    IPCheck<GeneralAddress> acl1(V6ADDR_1_STRING);
    vector<uint8_t> address = acl1.getAddress();

    EXPECT_EQ(128, acl1.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl1.getFamily());
    EXPECT_EQ(IPV6_SIZE, address.size());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_1));

    IPCheck<GeneralAddress> acl2(string(V6ADDR_2_STRING) + string("/51"));
    address = acl2.getAddress();
    EXPECT_EQ(IPV6_SIZE, address.size());
    EXPECT_EQ(51, acl2.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl2.getFamily());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_2));

    IPCheck<GeneralAddress> acl3(string(V6ADDR_2_STRING) + string("/127"));
    address = acl3.getAddress();
    EXPECT_EQ(IPV6_SIZE, address.size());
    EXPECT_EQ(127, acl3.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl3.getFamily());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_2));

    IPCheck<GeneralAddress> acl4("::1");
    address = acl4.getAddress();
    EXPECT_EQ(IPV6_SIZE, address.size());
    EXPECT_EQ(128, acl4.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl4.getFamily());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_3));

    // Any match.  In these cases, the address should all be zeroes.
    IPCheck<GeneralAddress> acl5("any6");
    address = acl5.getAddress();
    EXPECT_EQ(IPV6_SIZE, address.size());
    EXPECT_EQ(0, acl5.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl5.getFamily());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_4));

    IPCheck<GeneralAddress> acl6("::/0");
    address = acl6.getAddress();
    EXPECT_EQ(0, acl6.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl6.getFamily());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_4));

    // Some invalid strings
    EXPECT_THROW(IPCheck<GeneralAddress>("::1/129"), isc::OutOfRange);
    EXPECT_THROW(IPCheck<GeneralAddress>("::1/24/3"), isc::InvalidParameter);
    EXPECT_THROW(IPCheck<GeneralAddress>(":::1/24"), isc::InvalidParameter);
    EXPECT_THROW(IPCheck<GeneralAddress>("2001:0db8::abcd/ww"),
                 isc::InvalidParameter);
    EXPECT_THROW(IPCheck<GeneralAddress>("2xx1:0db8::abcd/32"),
                 isc::InvalidParameter);
}

TEST(IPCheck, V6CopyConstructor) {
    IPCheck<GeneralAddress> acl1(string(V6ADDR_2_STRING) + string("/52"));
    IPCheck<GeneralAddress> acl2(acl1);

    vector<uint8_t> acl1_address = acl1.getAddress();
    vector<uint8_t> acl2_address = acl1.getAddress();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_address.size());
    EXPECT_EQ(acl1_address.size(), acl2_address.size());
    EXPECT_TRUE(equal(acl1_address.begin(), acl1_address.end(),
                acl2_address.begin()));

    EXPECT_EQ(acl1.getPrefixlen(), acl2.getPrefixlen());

    vector<uint8_t> acl1_mask = acl1.getMask();
    vector<uint8_t> acl2_mask = acl1.getMask();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_mask.size());
    EXPECT_EQ(acl1_mask.size(), acl2_mask.size());
    EXPECT_TRUE(equal(acl1_mask.begin(), acl1_mask.end(),
                acl2_mask.begin()));
}

TEST(IPCheck, V6AssignmentOperator) {
    IPCheck<GeneralAddress> acl1(string(V6ADDR_2_STRING) + string("/52"));
    IPCheck<GeneralAddress> acl2(string(V6ADDR_1_STRING) + string("/48"));

    acl2 = acl1;

    vector<uint8_t> acl1_address = acl1.getAddress();
    vector<uint8_t> acl2_address = acl2.getAddress();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_address.size());
    EXPECT_EQ(acl1_address.size(), acl2_address.size());
    EXPECT_TRUE(equal(acl1_address.begin(), acl1_address.end(),
                acl2_address.begin()));

    EXPECT_EQ(acl1.getPrefixlen(), acl2.getPrefixlen());

    vector<uint8_t> acl1_mask = acl1.getMask();
    vector<uint8_t> acl2_mask = acl2.getMask();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_mask.size());
    EXPECT_EQ(acl1_mask.size(), acl2_mask.size());
    EXPECT_TRUE(equal(acl1_mask.begin(), acl1_mask.end(),
                acl2_mask.begin()));
}

TEST(IPCheck, V6Compare) {
    // Set up some data.
    vector<uint8_t> v6addr_2(V6ADDR_2, V6ADDR_2 + IPV6_SIZE);
    vector<uint8_t> v6addr_2_48(V6ADDR_2_48, V6ADDR_2_48 + IPV6_SIZE);
    vector<uint8_t> v6addr_2_49(V6ADDR_2_49, V6ADDR_2_49 + IPV6_SIZE);
    vector<uint8_t> v6addr_2_50(V6ADDR_2_50, V6ADDR_2_50 + IPV6_SIZE);
    vector<uint8_t> v6addr_2_51(V6ADDR_2_51, V6ADDR_2_51 + IPV6_SIZE);
    vector<uint8_t> v6addr_2_52(V6ADDR_2_52, V6ADDR_2_52 + IPV6_SIZE);
    vector<uint8_t> v6addr_2_127(V6ADDR_2_127, V6ADDR_2_127 + IPV6_SIZE);
    vector<uint8_t> v6addr_3(V6ADDR_3, V6ADDR_3 + IPV6_SIZE);

    // Exact address - match if given address matches stored address.
    IPCheck<GeneralAddress> acl1(string(V6ADDR_2_STRING) + string("/128"));
    EXPECT_TRUE(acl1.matches(v6addr_2));
    EXPECT_FALSE(acl1.matches(v6addr_2_127));
    EXPECT_FALSE(acl1.matches(v6addr_2_52));
    EXPECT_FALSE(acl1.matches(v6addr_2_51));
    EXPECT_FALSE(acl1.matches(v6addr_2_50));
    EXPECT_FALSE(acl1.matches(v6addr_2_49));
    EXPECT_FALSE(acl1.matches(v6addr_2_48));
    EXPECT_FALSE(acl1.matches(v6addr_3));

    // Match to various prefixes.
    IPCheck<GeneralAddress> acl2(string(V6ADDR_2_STRING) + string("/127"));
    EXPECT_TRUE(acl2.matches(v6addr_2));
    EXPECT_TRUE(acl2.matches(v6addr_2_127));
    EXPECT_FALSE(acl2.matches(v6addr_2_52));
    EXPECT_FALSE(acl2.matches(v6addr_2_51));
    EXPECT_FALSE(acl2.matches(v6addr_2_50));
    EXPECT_FALSE(acl2.matches(v6addr_2_49));
    EXPECT_FALSE(acl2.matches(v6addr_2_48));
    EXPECT_FALSE(acl2.matches(v6addr_3));

    IPCheck<GeneralAddress> acl3(string(V6ADDR_2_STRING) + string("/52"));
    EXPECT_TRUE(acl3.matches(v6addr_2));
    EXPECT_TRUE(acl3.matches(v6addr_2_127));
    EXPECT_TRUE(acl3.matches(v6addr_2_52));
    EXPECT_FALSE(acl3.matches(v6addr_2_51));
    EXPECT_FALSE(acl3.matches(v6addr_2_50));
    EXPECT_FALSE(acl3.matches(v6addr_2_49));
    EXPECT_FALSE(acl3.matches(v6addr_2_48));
    EXPECT_FALSE(acl3.matches(v6addr_3));

    IPCheck<GeneralAddress> acl4(string(V6ADDR_2_STRING) + string("/51"));
    EXPECT_TRUE(acl4.matches(v6addr_2));
    EXPECT_TRUE(acl4.matches(v6addr_2_127));
    EXPECT_TRUE(acl4.matches(v6addr_2_52));
    EXPECT_TRUE(acl4.matches(v6addr_2_51));
    EXPECT_FALSE(acl4.matches(v6addr_2_50));
    EXPECT_FALSE(acl4.matches(v6addr_2_49));
    EXPECT_FALSE(acl4.matches(v6addr_2_48));
    EXPECT_FALSE(acl4.matches(v6addr_3));

    IPCheck<GeneralAddress> acl5(string(V6ADDR_2_STRING) + string("/50"));
    EXPECT_TRUE(acl5.matches(v6addr_2));
    EXPECT_TRUE(acl5.matches(v6addr_2_127));
    EXPECT_TRUE(acl5.matches(v6addr_2_52));
    EXPECT_TRUE(acl5.matches(v6addr_2_51));
    EXPECT_TRUE(acl5.matches(v6addr_2_50));
    EXPECT_FALSE(acl5.matches(v6addr_2_49));
    EXPECT_FALSE(acl5.matches(v6addr_2_48));
    EXPECT_FALSE(acl5.matches(v6addr_3));

    IPCheck<GeneralAddress> acl6(string(V6ADDR_2_STRING) + string("/0"));
    EXPECT_TRUE(acl6.matches(v6addr_2));
    EXPECT_TRUE(acl6.matches(v6addr_2_127));
    EXPECT_TRUE(acl6.matches(v6addr_2_52));
    EXPECT_TRUE(acl6.matches(v6addr_2_51));
    EXPECT_TRUE(acl6.matches(v6addr_2_50));
    EXPECT_TRUE(acl6.matches(v6addr_2_49));
    EXPECT_TRUE(acl6.matches(v6addr_2_48));
    EXPECT_TRUE(acl6.matches(v6addr_3));

    // Match on any address
    IPCheck<GeneralAddress> acl7("any6");
    EXPECT_TRUE(acl7.matches(v6addr_2));
    EXPECT_TRUE(acl7.matches(v6addr_2_127));
    EXPECT_TRUE(acl7.matches(v6addr_2_52));
    EXPECT_TRUE(acl7.matches(v6addr_2_51));
    EXPECT_TRUE(acl7.matches(v6addr_2_50));
    EXPECT_TRUE(acl7.matches(v6addr_2_49));
    EXPECT_TRUE(acl7.matches(v6addr_2_48));
}

// *** Mixed-mode tests - mainly to check that no exception is thrown ***

TEST(IPCheck, MixedMode) {

    // ACL has a V4 address specified, check against a V6 address.
    IPCheck<GeneralAddress> acl1("192.0.2.255/24");
    GeneralAddress test1(vector<uint8_t>(V6ADDR_1, V6ADDR_1 + IPV6_SIZE));
    EXPECT_NO_THROW(acl1.matches(test1));
    EXPECT_FALSE(acl1.matches(test1));

    // Now the reverse - the ACL is specified with a V6 address.
    IPCheck<GeneralAddress> acl2(V6ADDR_2_STRING);
    GeneralAddress test2(0x12345678);
    EXPECT_FALSE(acl2.matches(test2));

    // Ensure only a V4 address matches "any4".
    IPCheck<GeneralAddress> acl3("any4");
    EXPECT_FALSE(acl3.matches(test1));
    EXPECT_TRUE(acl3.matches(test2));

    // ... and check the reverse
    IPCheck<GeneralAddress> acl4("any6");
    EXPECT_TRUE(acl4.matches(test1));
    EXPECT_FALSE(acl4.matches(test2));

    // Check where the bit pattern of an IPv4 address matches that of an IPv6
    // one.
    IPCheck<GeneralAddress> acl5("2001:db8::/32");
    GeneralAddress test5(0x20010db8);
    EXPECT_FALSE(acl5.matches(test5));

    // ... and where the reverse is true. (2001:db8 corresponds to 32.1.13.184).
    IPCheck<GeneralAddress> acl6("32.1.13.184");
    GeneralAddress test6(vector<uint8_t>(V6ADDR_1, V6ADDR_1 + IPV6_SIZE));
    EXPECT_FALSE(acl6.matches(test6));
}
} // Unnamed namespace
