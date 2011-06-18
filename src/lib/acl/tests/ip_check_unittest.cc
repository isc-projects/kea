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
#include <netdb.h>
#include <string.h>

#include <gtest/gtest.h>
#include <acl/ip_check.h>
#include <boost/scoped_ptr.hpp>

using namespace isc::acl;
using namespace std;

// Simple struct holding either an IPV4 or IPV6 address.  This is the "Context"
// used for the tests.

struct GeneralAddress {
    bool        isv4;           // true if it holds a v4 address
    uint32_t    v4addr;
    uint8_t     v6addr[16];

    GeneralAddress()
    {}

    // Convenience constructor for V4 address.  As it is not marked as
    // explicit, it allows the automatic promotion of a uint32_t to a
    // GeneralAddress data type in calls to matches().
    GeneralAddress(uint32_t address) : isv4(true), v4addr(address)
    {
        fill(v6addr, v6addr + sizeof(v6addr), 0);   // Explicitly zero
    }

    // Convenience constructor for V6 address.  As it is not marked as
    // explicit, it allows the automatic promotion of a vector<uint8_t> to a
    // GeneralAddress data type in calls to matches().
    GeneralAddress(const vector<uint8_t>& address) : isv4(false), v4addr(0) {
        if (address.size() != sizeof(v6addr)) {
            isc_throw(isc::InvalidParameter, "vector passed to GeneralAddress "
                      "constructor is " << address.size() << " bytes long - it "
                      "should be " << sizeof(v6addr) << " instead");
        }
        copy(address.begin(), address.end(), v6addr);
    }
};

// Provide specializations of the Ipv4check and Ipv6Check matches() methods for
// the GeneralAddress structure.

namespace isc  {
namespace acl {
template <>
bool Ipv4Check<GeneralAddress>::matches(const GeneralAddress& addr) const {
    return (addr.isv4 ? compare(addr.v4addr) : false);
}

template <>
bool Ipv6Check<GeneralAddress>::matches(const GeneralAddress& addr) const {
    return (addr.isv4 ? false : compare(addr.v6addr));
}
} // namespace acl
} // namespace isc

namespace {
/// *** Free Function Tests ***

// Test the createNetmask() function.
TEST(IpFunctionCheck, CreateNetmask) {

    // 8-bit tests: invalid arguments should throw.
    EXPECT_THROW(createNetmask<uint8_t>(9), isc::OutOfRange);

    // Check on all possible 8-bit values.  Use a signed type to generate a
    // variable with the most significant bits set (right-shifting will
    // introduce additional bits).
    int8_t expected8 = 0x80;
    for (size_t i = 1; i <= 8; ++i, expected8 >>= 1) {
        EXPECT_EQ(static_cast<uint8_t>(expected8), createNetmask<uint8_t>(i));
    }
    EXPECT_EQ(0, createNetmask<uint8_t>(0));

    // Do the same for 32 bits.
    EXPECT_THROW(createNetmask<int32_t>(33), isc::OutOfRange);

    int32_t expected32 = 0x80000000;
    for (size_t i = 1; i <= 32; ++i, expected32 >>= 1) {
        EXPECT_EQ(static_cast<uint32_t>(expected32),
                  createNetmask<uint32_t>(i));
    }
    EXPECT_EQ(0, createNetmask<uint32_t>(0));
}

// Test the splitIpAddress() function.
TEST(IpFunctionCheck, SplitIpAddress) {
    pair<string, uint32_t> result;

    result = splitIpAddress("192.0.2.1/24", 32);
    EXPECT_EQ(string("192.0.2.1"), result.first);
    EXPECT_EQ(24, result.second);

    result = splitIpAddress("192.0.2.2/32", 32);
    EXPECT_EQ(string("192.0.2.2"), result.first);
    EXPECT_EQ(32, result.second);

    result = splitIpAddress("2001:db8::/128", 128);
    EXPECT_EQ(string("2001:db8::"), result.first);
    EXPECT_EQ(128, result.second);

    EXPECT_THROW(splitIpAddress("2001:db8::/129", 128), isc::OutOfRange);
    EXPECT_THROW(splitIpAddress("2001:db8::/xxxx", 32), isc::InvalidParameter);
    EXPECT_THROW(splitIpAddress("2001:db8::/32/s", 32), isc::InvalidParameter);
}

const struct sockaddr&
getSockAddr(const char* const addr) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICHOST;

    if (getaddrinfo(addr, NULL, &hints, &res) == 0) {
        static struct sockaddr_storage ss;
        void* ss_ptr = &ss;
        memcpy(ss_ptr, res->ai_addr, res->ai_addrlen);
        freeaddrinfo(res);
        return (*static_cast<struct sockaddr*>(ss_ptr));
    }

    // We don't expect getaddrinfo to fail for our tests.  But if that
    // ever happens we return a dummy value that would make subsequent test
    // fail.
    static struct sockaddr sa_dummy;
    sa_dummy.sa_family = AF_UNSPEC;
    return (sa_dummy);
}

TEST(IPAddress, constructIPv4) {
    IPAddress ipaddr(getSockAddr("192.0.2.1"));
    const char expected_data[4] = { 192, 0, 2, 1 };
    EXPECT_EQ(AF_INET, ipaddr.family);
    EXPECT_EQ(4, ipaddr.length);
    EXPECT_EQ(0, memcmp(expected_data, ipaddr.data, 4));
}

TEST(IPAddress, constructIPv6) {
    IPAddress ipaddr(getSockAddr("2001:db8:1234:abcd::53"));
    const char expected_data[16] = { 0x20, 0x01, 0x0d, 0xb8, 0x12, 0x34, 0xab,
                                     0xcd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                     0x00, 0x53 };
    EXPECT_EQ(AF_INET6, ipaddr.family);
    EXPECT_EQ(16, ipaddr.length);
    EXPECT_EQ(0, memcmp(expected_data, ipaddr.data, 16));
}

TEST(IPAddress, badConstruct) {
    struct sockaddr sa;
    sa.sa_family = AF_UNSPEC;
    EXPECT_THROW(IPAddress ipaddr(sa), isc::BadValue);
}

// *** IPV4 Tests ***
// Check that a default constructor can be instantiated.

TEST(Ipv4Check, V4DefaultConstructor) {
    Ipv4Check<GeneralAddress> acl1;

    // The test is needed to avoid the unused variable causing a warning or
    // getting optimised away.
    EXPECT_EQ(1, acl1.getAddress());
}

// Check that the constructor stores the elements correctly and, for the
// address and mask, in network-byte order.

TEST(Ipv4Check, V4ConstructorAddress) {
    // Address is presented in network byte order in constructor, so not
    // conversion is needed for this test.
    Ipv4Check<GeneralAddress> acl1(0x12345678);
    EXPECT_EQ(0x12345678, acl1.getAddress());
}

TEST(Ipv4Check, V4ConstructorMask) {
    // Valid values. Address of "1" is used as a placeholder
    Ipv4Check<GeneralAddress> acl1(1, 1);

    // The mask is stored in network byte order, so the pattern expected must
    // also be converted to network byte order for the comparison to succeed.
    uint32_t expected = htonl(0x80000000);
    EXPECT_EQ(expected, acl1.getNetmask());
    EXPECT_EQ(1, acl1.getMasksize());

    Ipv4Check<GeneralAddress> acl2(1, 24);
    expected = htonl(0xffffff00);
    EXPECT_EQ(expected, acl2.getNetmask());
    EXPECT_EQ(24, acl2.getMasksize());

    // ... and some invalid network masks
    EXPECT_THROW(Ipv4Check<GeneralAddress>(1, 0), isc::OutOfRange);
    EXPECT_THROW(Ipv4Check<GeneralAddress>(1, 33), isc::OutOfRange);
}

TEST(Ipv4Check, V4ConstructorInverse) {
    // Valid values. Address/mask of "1" is used as a placeholder
    Ipv4Check<GeneralAddress> acl1(1, 1);
    EXPECT_FALSE(acl1.getInverse());

    Ipv4Check<GeneralAddress> acl2(1, 1, true);
    EXPECT_TRUE(acl2.getInverse());

    Ipv4Check<GeneralAddress> acl3(1, 1, false);
    EXPECT_FALSE(acl3.getInverse());
}

TEST(Ipv4Check, V4StringConstructor) {
    Ipv4Check<GeneralAddress> acl1("192.0.2.255");
    uint32_t expected = htonl(0xc00002ff);
    EXPECT_EQ(expected, acl1.getAddress());
    EXPECT_EQ(32, acl1.getMasksize());

    Ipv4Check<GeneralAddress> acl2("192.0.2.0/24");
    expected = htonl(0xc0000200);
    EXPECT_EQ(expected, acl2.getAddress());
    EXPECT_EQ(24, acl2.getMasksize());

    EXPECT_THROW(Ipv4Check<GeneralAddress>("192.0.2.0/0"), isc::OutOfRange);
    EXPECT_THROW(Ipv4Check<GeneralAddress>("192.0.2.0/33"), isc::OutOfRange);
    EXPECT_THROW(Ipv4Check<GeneralAddress>("192.0.2.0/24/3"),
                 isc::InvalidParameter);
    EXPECT_THROW(Ipv4Check<GeneralAddress>("192.0.2.0/ww"),
                 isc::InvalidParameter);
    EXPECT_THROW(Ipv4Check<GeneralAddress>("aa.255.255.0/ww"),
                 isc::InvalidParameter);
}

TEST(Ipv4Check, V4CopyConstructor) {
    Ipv4Check<GeneralAddress> acl1("192.0.2.1/24", true);
    Ipv4Check<GeneralAddress> acl2(acl1);

    EXPECT_EQ(acl1.getAddress(), acl2.getAddress());
    EXPECT_EQ(acl1.getMasksize(), acl2.getMasksize());
    EXPECT_EQ(acl1.getNetmask(), acl2.getNetmask());
    EXPECT_EQ(acl1.getInverse(), acl2.getInverse());
}

TEST(Ipv4Check, V4AssignmentOperator) {
    Ipv4Check<GeneralAddress> acl1("192.0.2.0/24", true);
    Ipv4Check<GeneralAddress> acl2("192.0.2.128/25", false);

    acl2 = acl1;
    EXPECT_EQ(acl1.getAddress(), acl2.getAddress());
    EXPECT_EQ(acl1.getMasksize(), acl2.getMasksize());
    EXPECT_EQ(acl1.getNetmask(), acl2.getNetmask());
    EXPECT_EQ(acl1.getInverse(), acl2.getInverse());
}

// Check that the comparison works - note that "matches" just calls the
// internal compare() code. (Also note that the argument to matches() will be
// automatically converted to the GeneralAddress data type used for the tests
// because of its constructor taking a uint32_t argument.
//
// As before, note that addresses passed to the class are expected to be in
// network-byte order.  Therefore for the comparisons to work as expected, we
// must convert the values to network-byte order first.

TEST(Ipv4Check, V4Compare) {
    // Exact address - match if given address matches stored address.
    Ipv4Check<GeneralAddress> acl1(htonl(0x23457f13), 32);
    EXPECT_TRUE(acl1.matches(htonl(0x23457f13)));
    EXPECT_FALSE(acl1.matches(htonl(0x23457f12)));
    EXPECT_FALSE(acl1.matches(htonl(0x13457f13)));

    // Exact address - match if address does not match stored address
    Ipv4Check<GeneralAddress> acl2(htonl(0x23457f13), 32, true);
    EXPECT_FALSE(acl2.matches(htonl(0x23457f13)));
    EXPECT_TRUE(acl2.matches(htonl(0x23457f12)));
    EXPECT_TRUE(acl2.matches(htonl(0x13457f13)));

    // Match if the address matches a mask
    Ipv4Check<GeneralAddress> acl3(htonl(0x23450000), 16);
    EXPECT_TRUE(acl3.matches(htonl(0x23450000)));
    EXPECT_TRUE(acl3.matches(htonl(0x23450001)));
    EXPECT_TRUE(acl3.matches(htonl(0x2345ffff)));
    EXPECT_FALSE(acl3.matches(htonl(0x23460000)));
    EXPECT_FALSE(acl3.matches(htonl(0x2346ffff)));

    // Match if the address does not match a mask
    Ipv4Check<GeneralAddress> acl4(htonl(0x23450000), 16, true);
    EXPECT_FALSE(acl4.matches(htonl(0x23450000)));
    EXPECT_FALSE(acl4.matches(htonl(0x23450001)));
    EXPECT_FALSE(acl4.matches(htonl(0x2345ffff)));
    EXPECT_TRUE(acl4.matches(htonl(0x23460000)));
    EXPECT_TRUE(acl4.matches(htonl(0x2346ffff)));
}



// *** IPV6 Tests ***

// Some constants used in the tests

static const char* V6ADDR_1_STRING = "2001:0db8:1122:3344:5566:7788:99aa:bbcc";
static const uint8_t V6ADDR_1[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x11, 0x22, 0x33, 0x44,
    0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc
};

static const char* V6ADDR_2_STRING = "2001:0db8::dead:beef";
static const uint8_t V6ADDR_2[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 48 bits
static const uint8_t V6ADDR_2_48[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x55, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 52 bits
static const uint8_t V6ADDR_2_52[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x05, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

static const char* V6ADDR_3_STRING = "::1";
static const uint8_t V6ADDR_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};


// Mask with MS bit set
static const uint8_t MASK_1[] = {
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t MASK_8[] = {
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t MASK_48[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t MASK_51[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t MASK_128[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Check that a default constructor can be instantiated.

TEST(Ipv6Check, V6DefaultConstructor) {
    Ipv6Check<GeneralAddress> acl1;

    // The test is needed to avoid the unused variable causing a warning or
    // getting optimised away.
    EXPECT_EQ(0, acl1.getMasksize());
}

TEST(Ipv6Check, V6ConstructorAddress) {
    Ipv6Check<GeneralAddress> acl1(V6ADDR_1);
    vector<uint8_t> stored = acl1.getAddress();
    EXPECT_EQ(sizeof(V6ADDR_1), stored.size());
    EXPECT_TRUE(equal(stored.begin(), stored.end(), V6ADDR_1));
}

TEST(Ipv6Check, V6ConstructorMask) {

    // Valid masks...
    Ipv6Check<GeneralAddress> acl1(V6ADDR_1, 1);
    vector<uint8_t> stored = acl1.getNetmask();
    EXPECT_EQ(sizeof(MASK_1), stored.size());
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_1));

    Ipv6Check<GeneralAddress> acl2(V6ADDR_1, 8);
    stored = acl2.getNetmask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_8));

    Ipv6Check<GeneralAddress> acl3(V6ADDR_1, 48);
    stored = acl3.getNetmask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_48));

    Ipv6Check<GeneralAddress> acl4(V6ADDR_1, 51);
    stored = acl4.getNetmask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_51));

    Ipv6Check<GeneralAddress> acl5(V6ADDR_1, 128);
    stored = acl5.getNetmask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_128));

    // ... and some invalid network masks
    EXPECT_THROW(Ipv6Check<GeneralAddress>(V6ADDR_1, 0), isc::OutOfRange);
    EXPECT_THROW(Ipv6Check<GeneralAddress>(V6ADDR_1, 129), isc::OutOfRange);
}

TEST(Ipv6Check, V6ConstructorInverse) {
    // Valid values. Address/mask of "1" is used as a placeholder
    Ipv6Check<GeneralAddress> acl1(V6ADDR_1, 1);
    EXPECT_FALSE(acl1.getInverse());

    Ipv6Check<GeneralAddress> acl2(V6ADDR_1, 1, true);
    EXPECT_TRUE(acl2.getInverse());

    Ipv6Check<GeneralAddress> acl3(V6ADDR_1, 1, false);
    EXPECT_FALSE(acl3.getInverse());
}

TEST(Ipv6Check, V6StringConstructor) {
    Ipv6Check<GeneralAddress> acl1(V6ADDR_1_STRING);
    vector<uint8_t> address = acl1.getAddress();
    EXPECT_EQ(128, acl1.getMasksize());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_1));

    Ipv6Check<GeneralAddress> acl2(string(V6ADDR_2_STRING) + string("/48"));
    address = acl2.getAddress();
    EXPECT_EQ(48, acl2.getMasksize());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_2));

    Ipv6Check<GeneralAddress> acl3("::1");
    address = acl3.getAddress();
    EXPECT_EQ(128, acl3.getMasksize());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_3));

    EXPECT_THROW(Ipv6Check<GeneralAddress>("::1/0"), isc::OutOfRange);
    EXPECT_THROW(Ipv6Check<GeneralAddress>("::1/129"), isc::OutOfRange);
    EXPECT_THROW(Ipv6Check<GeneralAddress>("::1/24/3"), isc::InvalidParameter);
    EXPECT_THROW(Ipv6Check<GeneralAddress>("2001:0db8::abcd/ww"),
                 isc::InvalidParameter);
    EXPECT_THROW(Ipv6Check<GeneralAddress>("2xx1:0db8::abcd/32"),
                 isc::InvalidParameter);
}

TEST(Ipv6Check, V6CopyConstructor) {
    Ipv6Check<GeneralAddress> acl1(string(V6ADDR_2_STRING) + string("/52"));
    Ipv6Check<GeneralAddress> acl2(acl1);

    vector<uint8_t> acl1_address = acl1.getAddress();
    vector<uint8_t> acl2_address = acl1.getAddress();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_address.size());
    EXPECT_EQ(acl1_address.size(), acl2_address.size());
    EXPECT_TRUE(equal(acl1_address.begin(), acl1_address.end(),
                acl2_address.begin()));

    EXPECT_EQ(acl1.getMasksize(), acl2.getMasksize());

    vector<uint8_t> acl1_netmask = acl1.getNetmask();
    vector<uint8_t> acl2_netmask = acl1.getNetmask();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_netmask.size());
    EXPECT_EQ(acl1_netmask.size(), acl2_netmask.size());
    EXPECT_TRUE(equal(acl1_netmask.begin(), acl1_netmask.end(),
                acl2_netmask.begin()));

    EXPECT_EQ(acl1.getInverse(), acl2.getInverse());
}

TEST(Ipv6Check, V6AssignmentOperator) {
    Ipv6Check<GeneralAddress> acl1(string(V6ADDR_2_STRING) + string("/52"));
    Ipv6Check<GeneralAddress> acl2(string(V6ADDR_1_STRING) + string("/48"));

    acl2 = acl1;

    vector<uint8_t> acl1_address = acl1.getAddress();
    vector<uint8_t> acl2_address = acl2.getAddress();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_address.size());
    EXPECT_EQ(acl1_address.size(), acl2_address.size());
    EXPECT_TRUE(equal(acl1_address.begin(), acl1_address.end(),
                acl2_address.begin()));

    EXPECT_EQ(acl1.getMasksize(), acl2.getMasksize());

    vector<uint8_t> acl1_netmask = acl1.getNetmask();
    vector<uint8_t> acl2_netmask = acl2.getNetmask();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_netmask.size());
    EXPECT_EQ(acl1_netmask.size(), acl2_netmask.size());
    EXPECT_TRUE(equal(acl1_netmask.begin(), acl1_netmask.end(),
                acl2_netmask.begin()));

    EXPECT_EQ(acl1.getInverse(), acl2.getInverse());
}

TEST(Ipv6Check, V6Compare) {
    // Set up some data.  
    vector<uint8_t> v6addr_2(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2));
    vector<uint8_t> v6addr_2_48(V6ADDR_2_48, V6ADDR_2_48 + sizeof(V6ADDR_2_48));
    vector<uint8_t> v6addr_2_52(V6ADDR_2_52, V6ADDR_2_52 + sizeof(V6ADDR_2_52));
    vector<uint8_t> v6addr_3(V6ADDR_3, V6ADDR_3 + sizeof(V6ADDR_3));

    // Exact address - match if given address matches stored address.
    Ipv6Check<GeneralAddress> acl1(string(V6ADDR_2_STRING) + string("/128"));
    EXPECT_TRUE(acl1.matches(v6addr_2));
    EXPECT_FALSE(acl1.matches(v6addr_2_52));
    EXPECT_FALSE(acl1.matches(v6addr_2_48));
    EXPECT_FALSE(acl1.matches(v6addr_3));

    // Exact address - match if address does not match stored address
    Ipv6Check<GeneralAddress> acl2(string(V6ADDR_2_STRING) + string("/128"),
                                   true);
    EXPECT_FALSE(acl2.matches(v6addr_2));
    EXPECT_TRUE(acl2.matches(v6addr_2_52));
    EXPECT_TRUE(acl2.matches(v6addr_2_48));
    EXPECT_TRUE(acl2.matches(v6addr_3));

    // Match if the address matches a mask
    Ipv6Check<GeneralAddress> acl3(string(V6ADDR_2_STRING) + string("/52"));
    EXPECT_TRUE(acl3.matches(v6addr_2));
    EXPECT_TRUE(acl3.matches(v6addr_2_52));
    EXPECT_FALSE(acl3.matches(v6addr_2_48));
    EXPECT_FALSE(acl3.matches(v6addr_3));

    // Match if the address does not match a mask
    Ipv6Check<GeneralAddress> acl4(string(V6ADDR_2_STRING) + string("/52"),
                              true);
    EXPECT_FALSE(acl4.matches(v6addr_2));
    EXPECT_FALSE(acl4.matches(v6addr_2_52));
    EXPECT_TRUE(acl4.matches(v6addr_2_48));
    EXPECT_TRUE(acl4.matches(v6addr_3));
}

// *** IP Tests ***

TEST(IpCheck, V4Test) {
    IpCheck<GeneralAddress> acl("192.168.132.255/16");
                               //c0  a8  84  ff

    GeneralAddress test;
    test.isv4 = true;
    test.v4addr = htonl(0xc0a884ff);
    EXPECT_TRUE(acl.matches(test));

    test.v4addr = htonl(0xc0a884ee);    // Correct to 24 bits
    EXPECT_TRUE(acl.matches(test));

    test.v4addr = htonl(0xc0a8ffee);    // Correct to 16 bits
    EXPECT_TRUE(acl.matches(test));

    test.v4addr = htonl(0xc000ffee);    // Incorrect
    EXPECT_FALSE(acl.matches(test));

    test.isv4 = false;
    test.v4addr = htonl(0xc0a884ff);    // Correct IPV4 address
    EXPECT_FALSE(acl.matches(test));

    // Quick check for negative match
    IpCheck<GeneralAddress> acl2("192.168.132.255/16", true);
    test.isv4 = true;
    test.v4addr = htonl(0xc0a884ff);
    EXPECT_FALSE(acl2.matches(test));
}

TEST(IpCheck, V6Test) {
    IpCheck<GeneralAddress> acl(string(V6ADDR_2_STRING) + string("/52"));

    GeneralAddress test;
    test.isv4 = false;
    copy(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2), test.v6addr);
    EXPECT_TRUE(acl.matches(test));

    copy(V6ADDR_2_52, V6ADDR_2_52 + sizeof(V6ADDR_2_52), test.v6addr);
    EXPECT_TRUE(acl.matches(test));

    copy(V6ADDR_2_48, V6ADDR_2_48 + sizeof(V6ADDR_2_48), test.v6addr);
    EXPECT_FALSE(acl.matches(test));

    test.isv4 = true;
    copy(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2), test.v6addr);
                                        // Correct V6 address
    EXPECT_FALSE(acl.matches(test));

    // Quick check for negative match
    IpCheck<GeneralAddress> acl2(string(V6ADDR_2_STRING) + string("/52"), true);
    test.isv4 = false;
    copy(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2), test.v6addr);
    EXPECT_FALSE(acl2.matches(test));
}

// Check copy constructor and assignment operator for V4 address
TEST(IpCheck, V4Copying) {
    IpCheck<GeneralAddress> acl("192.168.132.255/16");
    GeneralAddress test;
    test.isv4 = true;
    test.v4addr = htonl(0xc0a884ff);

    IpCheck<GeneralAddress> acl1(acl);
    EXPECT_TRUE(acl1.matches(test));

    IpCheck<GeneralAddress> acl2("192.255.132.255/32");
    EXPECT_FALSE(acl2.matches(test));
    acl2 = acl;
    EXPECT_TRUE(acl2.matches(test));
}

// Check copy constructor and assignment operator for V6 address
TEST(IpCheck, V6Copying) {
    IpCheck<GeneralAddress> acl(string(V6ADDR_2_STRING) + string("/52"));
    GeneralAddress test;
    test.isv4 = false;
    copy(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2), test.v6addr);

    IpCheck<GeneralAddress> acl1(acl);
    EXPECT_TRUE(acl1.matches(test));

    IpCheck<GeneralAddress> acl2(V6ADDR_3_STRING);
    EXPECT_FALSE(acl2.matches(test));
    acl2 = acl;
    EXPECT_TRUE(acl2.matches(test));
}
}
