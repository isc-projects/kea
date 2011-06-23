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


#include <gtest/gtest.h>
#include <acl/ip_check.h>
#include <boost/scoped_ptr.hpp>

using namespace isc::acl;
using namespace isc::acl::internal;
using namespace std;

namespace {
const size_t IPV4_SIZE = 4;
const size_t IPV6_SIZE = 16;
}

// Simple struct holding either an IPV4 or IPV6 address.  This is the "Context"
// used for the tests.
//
// The structure is also used for converting an IPV4 address to a four-byte
// array.
struct GeneralAddress {
    vector<uint8_t> addr;       // Address type.  Size indicates what it holds

    // Convert uint32_t address to a uint8_t vector
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
    GeneralAddress(uint32_t address) : addr()
    {
        addr = convertUint32(address);
    }

    // Convenience constructor for V6 address.  As it is not marked as explicit,
    // it allows the automatic promotion of a vector<uint8_t> to a
    // GeneralAddress data type in calls to matches().
    GeneralAddress(const vector<uint8_t>& address) : addr(address)
    {
        // Implicit assertion here that an IPV6 address size is 16 bytes
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
        if (addr.size() == IPV4_SIZE) {
            const vector<uint8_t> byte_address = convertUint32(address);
            return (equal(byte_address.begin(), byte_address.end(),
                           addr.begin()));
        }
        return (false);
    }

    // Check that the array is equal to that given
    bool equals(const vector<uint8_t>& byte_address) {
        if (addr.size() == byte_address.size()) {
            return (equal(byte_address.begin(), byte_address.end(),
                           addr.begin()));
        }
        return (false);
    }
};

// Provide a specialisation of the IPCheck::matches() method for the
// GeneralAddress class.

namespace isc  {
namespace acl {
template <>
bool IPCheck<GeneralAddress>::matches(const GeneralAddress& address) const {
    return (compare(&address.addr[0],
            (address.addr.size() == IPV4_SIZE) ? AF_INET : AF_INET6));
}
} // namespace acl
} // namespace isc

/// *** Free Function Tests ***

// Test the createMask() function.
TEST(IPFunctionCheck, CreateMask) {

    // 8-bit tests: invalid arguments should throw.
    EXPECT_THROW(createMask<uint8_t>(9), isc::OutOfRange);

    // Check on all possible 8-bit values.  Use a signed type to generate a
    // variable with the most significant bits set (right-shifting will
    // introduce additional bits).
    int8_t expected8 = 0x80;
    for (size_t i = 1; i <= 8; ++i, expected8 >>= 1) {
        EXPECT_EQ(static_cast<uint8_t>(expected8), createMask<uint8_t>(i));
    }
    EXPECT_EQ(0, createMask<uint8_t>(0));

    // Do the same for 32 bits.
    EXPECT_THROW(createMask<int32_t>(33), isc::OutOfRange);

    int32_t expected32 = 0x80000000;
    for (size_t i = 1; i <= 32; ++i, expected32 >>= 1) {
        EXPECT_EQ(static_cast<uint32_t>(expected32),
                  createMask<uint32_t>(i));
    }
    EXPECT_EQ(0, createMask<uint32_t>(0));
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

// *** IPV4 Tests ***

// Check that the constructor stores the elements correctly and, for the
// address and mask, in network-byte order.

TEST(IPCheck, V4ConstructorAddress) {
    GeneralAddress address(0x12345678);

    // Address is presented in network byte order in constructor, so no
    // conversion is needed for this test.
    IPCheck<GeneralAddress> acl(0x12345678);
    vector<uint8_t> stored = acl.getAddress();

    EXPECT_EQ(AF_INET, acl.getFamily());
    EXPECT_TRUE(address.equals(stored));
}

TEST(IPCheck, V4ConstructorMask) {
    // The mask is stored in network byte order.  The conversion to a byte
    // array within the IPCheck object should take care of the ordering.
    IPCheck<GeneralAddress> acl1(1, 1);         // Address of 1 is placeholder
    GeneralAddress mask1(0x80000000);           // Expected mask
    vector<uint8_t> stored1 = acl1.getMask();
    EXPECT_TRUE(mask1.equals(stored1));
    EXPECT_EQ(1, acl1.getPrefixlen());

    // Different check
    IPCheck<GeneralAddress> acl2(1, 24);
    GeneralAddress mask2(0xffffff00);
    vector<uint8_t> stored2 = acl2.getMask();
    EXPECT_TRUE(mask2.equals(stored2));
    EXPECT_EQ(24, acl2.getPrefixlen());

    // ... and some invalid network masks
    EXPECT_THROW(IPCheck<GeneralAddress>(1, 33), isc::OutOfRange);
    vector<uint8_t> dummy(IPV6_SIZE);
    EXPECT_THROW(IPCheck<GeneralAddress>(&dummy[0], 129), isc::OutOfRange);
}

TEST(IPCheck, V4StringConstructor) {
    // Constructor with no mask given
    IPCheck<GeneralAddress> acl1("192.0.2.255");
    EXPECT_EQ(32, acl1.getPrefixlen());
    EXPECT_EQ(AF_INET, acl1.getFamily());

    vector<uint8_t> stored1 = acl1.getAddress();
    GeneralAddress expected1(0xc00002ff);
    EXPECT_TRUE(expected1.equals(stored1));

    // Constructor with valid mask given
    IPCheck<GeneralAddress> acl2("192.0.2.0/24");
    EXPECT_EQ(24, acl2.getPrefixlen());
    EXPECT_EQ(AF_INET, acl2.getFamily());

    vector<uint8_t> stored2 = acl2.getAddress();
    GeneralAddress expected2(0xc0000200);
    EXPECT_TRUE(expected2.equals(stored2));

    // Any match
    IPCheck<GeneralAddress> acl3("any4");
    EXPECT_EQ(0, acl3.getPrefixlen());
    EXPECT_EQ(AF_INET, acl3.getFamily());

    // Invalid prefix lengths
    EXPECT_THROW(IPCheck<GeneralAddress>("192.0.2.0/33"), isc::OutOfRange);
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
//
// As before, note that addresses passed to the class are expected to be in
// network-byte order.  Therefore for the comparisons to work as expected, we
// must convert the values to network-byte order first.

TEST(IPCheck, V4Compare) {
    // Exact address - match if given address matches stored address.
    IPCheck<GeneralAddress> acl1(0x23457f13, 32);
    EXPECT_TRUE(acl1.matches(0x23457f13));
    EXPECT_FALSE(acl1.matches(0x23457f12));
    EXPECT_FALSE(acl1.matches(0x13457f13));

    // Match if the address matches a mask
    IPCheck<GeneralAddress> acl2(0x23450000, 16);
    EXPECT_TRUE(acl2.matches(0x23450000));
    EXPECT_TRUE(acl2.matches(0x23450001));
    EXPECT_TRUE(acl2.matches(0x2345ffff));
    EXPECT_FALSE(acl2.matches(0x23460000));
    EXPECT_FALSE(acl2.matches(0x2346ffff));

    // Match if "any4" is specified
    IPCheck<GeneralAddress> acl3("any4");
    EXPECT_TRUE(acl3.matches(0x23450000));
    EXPECT_TRUE(acl3.matches(0x23450001));
    EXPECT_TRUE(acl3.matches(0x2345ffff));
    EXPECT_TRUE(acl3.matches(0x23460000));
    EXPECT_TRUE(acl3.matches(0x2346ffff));

    IPCheck<GeneralAddress> acl4(0x23450000, 0);
    EXPECT_TRUE(acl4.matches(0x23450000));
    EXPECT_TRUE(acl4.matches(0x23450001));
    EXPECT_TRUE(acl4.matches(0x2345ffff));
    EXPECT_TRUE(acl4.matches(0x23460000));
    EXPECT_TRUE(acl4.matches(0x2346ffff));
}



// *** IPV6 Tests ***

// Some constants used in the tests

namespace {

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
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x55, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

// Identical to V6ADDR_2 to 52 bits
const uint8_t V6ADDR_2_52[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x05, 0x66,
    0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
};

const char* V6ADDR_3_STRING = "::1";
const uint8_t V6ADDR_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};


// Mask with MS bit set
const uint8_t MASK_1[] = {
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t MASK_8[] = {
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t MASK_48[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t MASK_51[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t MASK_128[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

} // Anonymous namespace

TEST(IPCheck, V6ConstructorAddress) {
    IPCheck<GeneralAddress> acl1(V6ADDR_1);
    vector<uint8_t> stored = acl1.getAddress();
    EXPECT_EQ(sizeof(V6ADDR_1), stored.size());
    EXPECT_TRUE(equal(stored.begin(), stored.end(), V6ADDR_1));
}

TEST(IPCheck, V6ConstructorMask) {

    // Valid masks...
    IPCheck<GeneralAddress> acl1(V6ADDR_1, 1);
    vector<uint8_t> stored = acl1.getMask();
    EXPECT_EQ(sizeof(MASK_1), stored.size());
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_1));

    IPCheck<GeneralAddress> acl2(V6ADDR_1, 8);
    stored = acl2.getMask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_8));

    IPCheck<GeneralAddress> acl3(V6ADDR_1, 48);
    stored = acl3.getMask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_48));

    IPCheck<GeneralAddress> acl4(V6ADDR_1, 51);
    stored = acl4.getMask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_51));

    IPCheck<GeneralAddress> acl5(V6ADDR_1, 128);
    stored = acl5.getMask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_128));

    // ... and some invalid network masks
    EXPECT_THROW(IPCheck<GeneralAddress>(V6ADDR_1, 129), isc::OutOfRange);
}

TEST(IPCheck, V6StringConstructor) {
    IPCheck<GeneralAddress> acl1(V6ADDR_1_STRING);
    vector<uint8_t> address = acl1.getAddress();
    EXPECT_EQ(128, acl1.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl1.getFamily());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_1));

    IPCheck<GeneralAddress> acl2(string(V6ADDR_2_STRING) + string("/48"));
    address = acl2.getAddress();
    EXPECT_EQ(48, acl2.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl2.getFamily());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_2));

    IPCheck<GeneralAddress> acl3("::1");
    address = acl3.getAddress();
    EXPECT_EQ(128, acl3.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl3.getFamily());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_3));

    // Any match
    IPCheck<GeneralAddress> acl4("any6");
    EXPECT_EQ(0, acl4.getPrefixlen());
    EXPECT_EQ(AF_INET6, acl4.getFamily());

    EXPECT_NO_THROW(IPCheck<GeneralAddress>("::1/0"));
    EXPECT_THROW(IPCheck<GeneralAddress>("::1/129"), isc::OutOfRange);
    EXPECT_THROW(IPCheck<GeneralAddress>("::1/24/3"), isc::InvalidParameter);
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
    vector<uint8_t> v6addr_2(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2));
    vector<uint8_t> v6addr_2_48(V6ADDR_2_48, V6ADDR_2_48 + sizeof(V6ADDR_2_48));
    vector<uint8_t> v6addr_2_52(V6ADDR_2_52, V6ADDR_2_52 + sizeof(V6ADDR_2_52));
    vector<uint8_t> v6addr_3(V6ADDR_3, V6ADDR_3 + sizeof(V6ADDR_3));

    // Exact address - match if given address matches stored address.
    IPCheck<GeneralAddress> acl1(string(V6ADDR_2_STRING) + string("/128"));
    EXPECT_TRUE(acl1.matches(v6addr_2));
    EXPECT_FALSE(acl1.matches(v6addr_2_52));
    EXPECT_FALSE(acl1.matches(v6addr_2_48));
    EXPECT_FALSE(acl1.matches(v6addr_3));

    // Match if the address matches a mask
    IPCheck<GeneralAddress> acl2(string(V6ADDR_2_STRING) + string("/52"));
    EXPECT_TRUE(acl2.matches(v6addr_2));
    EXPECT_TRUE(acl2.matches(v6addr_2_52));
    EXPECT_FALSE(acl2.matches(v6addr_2_48));
    EXPECT_FALSE(acl2.matches(v6addr_3));

    // Match on any address
    IPCheck<GeneralAddress> acl3("any6");
    EXPECT_TRUE(acl3.matches(v6addr_2));
    EXPECT_TRUE(acl3.matches(v6addr_2_52));
    EXPECT_TRUE(acl3.matches(v6addr_2_48));
    EXPECT_TRUE(acl3.matches(v6addr_3));

    IPCheck<GeneralAddress> acl4(string(V6ADDR_1_STRING) + string("/0"));
    EXPECT_TRUE(acl4.matches(v6addr_2));
    EXPECT_TRUE(acl4.matches(v6addr_2_52));
    EXPECT_TRUE(acl4.matches(v6addr_2_48));
    EXPECT_TRUE(acl4.matches(v6addr_3));
}

// *** Mixed-mode tests - mainly to check that no exception is thrown ***

TEST(IPCheck, MixedMode) {

    // ACL has a V4 address specified, check against a V6 address.
    IPCheck<GeneralAddress> acl1("192.0.2.255/24");
    GeneralAddress test1(vector<uint8_t>(V6ADDR_1, V6ADDR_1 + sizeof(V6ADDR_1)));
    EXPECT_NO_THROW(acl1.matches(test1));
    EXPECT_FALSE(acl1.matches(test1));

    // Now the reverse - the ACL is specified with a V6 address.
    IPCheck<GeneralAddress> acl2(V6ADDR_2_STRING);
    GeneralAddress test2(0x12345678);
    EXPECT_NO_THROW(acl2.matches(test2));
    EXPECT_FALSE(acl2.matches(test2));

    // Ensure only a V4 address matches "any4".
    IPCheck<GeneralAddress> acl3("any4");
    EXPECT_FALSE(acl3.matches(test1));
    EXPECT_TRUE(acl3.matches(test2));

    // ... and check the reverse
    IPCheck<GeneralAddress> acl4("any6");
    EXPECT_TRUE(acl4.matches(test1));
    EXPECT_FALSE(acl4.matches(test2));
}
