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
using namespace std;

/// *** Free Function Tests ***

TEST(IpFunctionCheck, CreateNetmask) {

    // 8-bit tests: invalid arguments should throw.
    EXPECT_THROW(createNetmask<uint8_t>(9), isc::OutOfRange);

    // Check on all possible 8-bit values.  Use a signed type to generate a
    // variable with the most significant bits set, as right-shifting it is
    // guaranteed to introduce additional bits.
    int8_t expected8 = 0x80;
    for (size_t i = 1; i <= 8; ++i, expected8 >>= 1) {
        EXPECT_EQ(static_cast<uint8_t>(expected8), createNetmask<uint8_t>(i));
    }
    EXPECT_EQ(0, createNetmask<uint8_t>(0));

    // Do the same for 32 bits.
    EXPECT_THROW(createNetmask<int32_t>(33), isc::OutOfRange);

    // Check on all possible 8-bit values
    int32_t expected32 = 0x80000000;
    for (size_t i = 1; i <= 32; ++i, expected32 >>= 1) {
        EXPECT_EQ(static_cast<uint32_t>(expected32),
                  createNetmask<uint32_t>(i));
    }
    EXPECT_EQ(0, createNetmask<uint32_t>(0));
}

TEST(IpFunctionCheck, SplitIp) {
    pair<string, uint32_t> result;

    result = splitIpAddress("192.0.2.1/24", 32);
    EXPECT_EQ(string("192.0.2.1"), result.first);
    EXPECT_EQ(24, result.second);

    result = splitIpAddress("192.0.2.1/32", 32);
    EXPECT_EQ(string("192.0.2.1"), result.first);
    EXPECT_EQ(32, result.second);

    result = splitIpAddress("2001:db8::/128", 128);
    EXPECT_EQ(string("2001:db8::"), result.first);
    EXPECT_EQ(128, result.second);

    EXPECT_THROW(splitIpAddress("2001:db8::/129", 128), isc::OutOfRange);
    EXPECT_THROW(splitIpAddress("2001:db8::/xxxx", 32), isc::InvalidParameter);
    EXPECT_THROW(splitIpAddress("2001:db8::/32/s", 32), isc::InvalidParameter);
}

// *** IPV4 Tests ***

// Declare a derived class to allow a definition of the match() method to be
// provided.
//
// In this case, the match will check a uint32_t variable representing an IPV4
// address.

class DerivedV4Check : public Ipv4Check<uint32_t> {
public:
    // Basic (and default) constructor
    DerivedV4Check(uint32_t address = 1, size_t masksize = 32,
                   bool inverse = false) :
                   Ipv4Check<uint32_t>(address, masksize, inverse)
    {}

    // String constructor
    DerivedV4Check(const string& address, bool inverse = false) :
        Ipv4Check<uint32_t>(address, inverse)
    {}

    // Copy constructor
    DerivedV4Check(const DerivedV4Check& other) : Ipv4Check<uint32_t>(other)
    {}

    // Assignment operator
    DerivedV4Check& operator=(const DerivedV4Check& other) {
        if (this != &other) {
            Ipv4Check<uint32_t>::operator=(other);
        }
        return (*this);
    }

    // Clone method
    virtual IpBaseCheck<uint32_t>* clone() const {
        return (new DerivedV4Check(*this));
    }

    // Destructor
    virtual ~DerivedV4Check()
    {}

    // Concrete implementation of abstract method
    virtual bool matches(const uint32_t& context) const {
        return (compare(context));
    }
};

// Check that a default constructor can be instantiated.

TEST(Ipv4Check, V4DefaultConstructor) {
    DerivedV4Check acl1;

    // The test is needed to avoid the unused variable causing a warning or
    // getting optimised away.
    EXPECT_EQ(1, acl1.getAddress());
}

// Check that the constructor stores the elements correctly.  As the address
// is provided in the correct (network-byte order) format, the real test is
// checking that the network mask is stored in the correct byte order.

TEST(Ipv4Check, V4ConstructorAddress) {
    DerivedV4Check acl1(0x12345678);
    EXPECT_EQ(0x12345678, acl1.getAddress());
}

TEST(Ipv4Check, V4ConstructorMask) {
    // Valid values. Address of "1" is used as a placeholder
    DerivedV4Check acl1(1, 1);

    // The mask is stored in network byte order, so the pattern expected must
    // also be converted to network byte order for the comparison to succeed.
    uint32_t expected = htonl(0x80000000);
    EXPECT_EQ(expected, acl1.getNetmask());
    EXPECT_EQ(1, acl1.getMasksize());

    DerivedV4Check acl2(1, 24);
    expected = htonl(0xffffff00);
    EXPECT_EQ(expected, acl2.getNetmask());
    EXPECT_EQ(24, acl2.getMasksize());

    // ... and some invalid network masks
    EXPECT_THROW(DerivedV4Check(1, 0), isc::OutOfRange);
    EXPECT_THROW(DerivedV4Check(1, 33), isc::OutOfRange);
}

TEST(Ipv4Check, V4ConstructorInverse) {
    // Valid values. Address/mask of "1" is used as a placeholder
    DerivedV4Check acl1(1, 1);
    EXPECT_FALSE(acl1.getInverse());

    DerivedV4Check acl2(1, 1, true);
    EXPECT_TRUE(acl2.getInverse());

    DerivedV4Check acl3(1, 1, false);
    EXPECT_FALSE(acl3.getInverse());
}

TEST(Ipv4Check, V4StringConstructor) {
    DerivedV4Check acl1("192.168.132.255");
    uint32_t expected = htonl(0xc0a884ff);
    EXPECT_EQ(expected, acl1.getAddress());
    EXPECT_EQ(32, acl1.getMasksize());

    DerivedV4Check acl2("192.0.2.0/24");
    expected = htonl(0xc0000200);
    EXPECT_EQ(expected, acl2.getAddress());
    EXPECT_EQ(24, acl2.getMasksize());

    EXPECT_THROW(DerivedV4Check("192.0.2.0/0"), isc::OutOfRange);
    EXPECT_THROW(DerivedV4Check("192.0.2.0/33"), isc::OutOfRange);
    EXPECT_THROW(DerivedV4Check("192.0.2.0/24/3"), isc::InvalidParameter);
    EXPECT_THROW(DerivedV4Check("192.0.2.0/ww"), isc::InvalidParameter);
    EXPECT_THROW(DerivedV4Check("aa.255.255.0/ww"), isc::InvalidParameter);
}

TEST(Ipv4Check, V4CopyConstructor) {
    DerivedV4Check acl1("127.0.0.1/16", true);
    DerivedV4Check acl2(acl1);

    EXPECT_EQ(acl1.getAddress(), acl2.getAddress());
    EXPECT_EQ(acl1.getMasksize(), acl2.getMasksize());
    EXPECT_EQ(acl1.getNetmask(), acl2.getNetmask());
    EXPECT_EQ(acl1.getInverse(), acl2.getInverse());
}

TEST(Ipv4Check, V4AssignmentOperator) {
    DerivedV4Check acl1("127.0.0.1/16", true);
    DerivedV4Check acl2("192.1.2.3/12", false);

    acl2 = acl1;
    EXPECT_EQ(acl1.getAddress(), acl2.getAddress());
    EXPECT_EQ(acl1.getMasksize(), acl2.getMasksize());
    EXPECT_EQ(acl1.getNetmask(), acl2.getNetmask());
    EXPECT_EQ(acl1.getInverse(), acl2.getInverse());
}

TEST(IPv4Check, V4Clone) {
    DerivedV4Check acl1("127.0.0.1/16", true);

    boost::scoped_ptr<DerivedV4Check> acl2(
            static_cast<DerivedV4Check*>(acl1.clone()));
    EXPECT_EQ(acl1.getAddress(), acl2->getAddress());
    EXPECT_EQ(acl1.getMasksize(), acl2->getMasksize());
    EXPECT_EQ(acl1.getNetmask(), acl2->getNetmask());
    EXPECT_EQ(acl1.getInverse(), acl2->getInverse());
}

// Check that the comparison works - note that "matches" just calls the
// internal compare() code.
//
// As before, note that addresses passed to the class are expected to be in
// network-byte order.  Therefore for the comparisons to work as expected, we
// must convert the values to network-byte order first.

TEST(Ipv4Check, V4Compare) {
    // Exact address - match if given address matches stored address.
    DerivedV4Check acl1(htonl(0x23457f13), 32);
    EXPECT_TRUE(acl1.matches(htonl(0x23457f13)));
    EXPECT_FALSE(acl1.matches(htonl(0x23457f12)));
    EXPECT_FALSE(acl1.matches(htonl(0x13457f13)));

    // Exact address - match if address does not match stored address
    DerivedV4Check acl2(htonl(0x23457f13), 32, true);
    EXPECT_FALSE(acl2.matches(htonl(0x23457f13)));
    EXPECT_TRUE(acl2.matches(htonl(0x23457f12)));
    EXPECT_TRUE(acl2.matches(htonl(0x13457f13)));

    // Match if the address matches a mask
    DerivedV4Check acl3(htonl(0x23450000), 16);
    EXPECT_TRUE(acl3.matches(htonl(0x23450000)));
    EXPECT_TRUE(acl3.matches(htonl(0x23450001)));
    EXPECT_TRUE(acl3.matches(htonl(0x2345ffff)));
    EXPECT_FALSE(acl3.matches(htonl(0x23460000)));
    EXPECT_FALSE(acl3.matches(htonl(0x2346ffff)));

    // Match if the address does not match a mask
    DerivedV4Check acl4(htonl(0x23450000), 16, true);
    EXPECT_FALSE(acl4.matches(htonl(0x23450000)));
    EXPECT_FALSE(acl4.matches(htonl(0x23450001)));
    EXPECT_FALSE(acl4.matches(htonl(0x2345ffff)));
    EXPECT_TRUE(acl4.matches(htonl(0x23460000)));
    EXPECT_TRUE(acl4.matches(htonl(0x2346ffff)));
}



// *** IPV6 Tests ***
//
// Declare a derived class to allow a definition of the match() method to be
// provided.
//
// In this case, the match will check a vector of uint8_t s representing an IPV6
// address.

class DerivedV6Check : public Ipv6Check<vector<uint8_t> > {
public:
    // default constructor
    DerivedV6Check() : Ipv6Check<vector<uint8_t> >()
    {}

    // Basic constructor
    DerivedV6Check(const uint8_t* address, size_t masksize = 128,
                   bool inverse = false) :
                   Ipv6Check<vector<uint8_t> >(address, masksize, inverse)
    {}

    // String constructor
    DerivedV6Check(const string& address, bool inverse = false) :
        Ipv6Check<vector<uint8_t> >(address, inverse)
    {}

    // Clone method
    virtual IpBaseCheck<vector<uint8_t> >* clone() const {
        return (new DerivedV6Check(*this));
    }

    // Destructor
    virtual ~DerivedV6Check()
    {}

    // Concrete implementation of abstract method
    virtual bool matches(const vector<uint8_t>& context) const {
        return (compare(&context[0])); // (compare(context));
    }
};

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
    DerivedV6Check acl1;

    // The test is needed to avoid the unused variable causing a warning or
    // getting optimised away.
    EXPECT_EQ(0, acl1.getMasksize());
}

TEST(Ipv6Check, V6ConstructorAddress) {
    DerivedV6Check acl1(V6ADDR_1);
    vector<uint8_t> stored = acl1.getAddress();
    EXPECT_EQ(sizeof(V6ADDR_1), stored.size());
    EXPECT_TRUE(equal(stored.begin(), stored.end(), V6ADDR_1));
}

TEST(Ipv6Check, V6ConstructorMask) {

    // Valid masks...
    DerivedV6Check acl1(V6ADDR_1, 1);
    vector<uint8_t> stored = acl1.getNetmask();
    EXPECT_EQ(sizeof(MASK_1), stored.size());
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_1));

    DerivedV6Check acl2(V6ADDR_1, 8);
    stored = acl2.getNetmask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_8));

    DerivedV6Check acl3(V6ADDR_1, 48);
    stored = acl3.getNetmask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_48));

    DerivedV6Check acl4(V6ADDR_1, 51);
    stored = acl4.getNetmask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_51));

    DerivedV6Check acl5(V6ADDR_1, 128);
    stored = acl5.getNetmask();
    EXPECT_TRUE(equal(stored.begin(), stored.end(), MASK_128));

    // ... and some invalid network masks
    EXPECT_THROW(DerivedV6Check(V6ADDR_1, 0), isc::OutOfRange);
    EXPECT_THROW(DerivedV6Check(V6ADDR_1, 129), isc::OutOfRange);
}

TEST(Ipv6Check, V6ConstructorInverse) {
    // Valid values. Address/mask of "1" is used as a placeholder
    DerivedV6Check acl1(V6ADDR_1, 1);
    EXPECT_FALSE(acl1.getInverse());

    DerivedV6Check acl2(V6ADDR_1, 1, true);
    EXPECT_TRUE(acl2.getInverse());

    DerivedV6Check acl3(V6ADDR_1, 1, false);
    EXPECT_FALSE(acl3.getInverse());
}

TEST(Ipv6Check, V6StringConstructor) {
    DerivedV6Check acl1(V6ADDR_1_STRING);
    vector<uint8_t> address = acl1.getAddress();
    EXPECT_EQ(128, acl1.getMasksize());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_1));

    DerivedV6Check acl2(string(V6ADDR_2_STRING) + string("/48"));
    address = acl2.getAddress();
    EXPECT_EQ(48, acl2.getMasksize());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_2));

    DerivedV6Check acl3("::1");
    address = acl3.getAddress();
    EXPECT_EQ(128, acl3.getMasksize());
    EXPECT_TRUE(equal(address.begin(), address.end(), V6ADDR_3));

    EXPECT_THROW(DerivedV6Check("::1/0"), isc::OutOfRange);
    EXPECT_THROW(DerivedV6Check("::1/129"), isc::OutOfRange);
    EXPECT_THROW(DerivedV6Check("::1/24/3"), isc::InvalidParameter);
    EXPECT_THROW(DerivedV6Check("2001:0db8::abcd/ww"), isc::InvalidParameter);
    EXPECT_THROW(DerivedV6Check("2xx1:0db8::abcd/32"), isc::InvalidParameter);
}

TEST(Ipv6Check, V6CopyConstructor) {
    DerivedV6Check acl1(string(V6ADDR_2_STRING) + string("/52"));
    DerivedV6Check acl2(acl1);

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
    DerivedV6Check acl1(string(V6ADDR_2_STRING) + string("/52"));
    DerivedV6Check acl2(string(V6ADDR_1_STRING) + string("/48"));

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

TEST(Ipv6Check, V6Clone) {
    DerivedV6Check acl1(string(V6ADDR_2_STRING) + string("/52"));
    boost::scoped_ptr<DerivedV6Check> acl2(
        static_cast<DerivedV6Check*>(acl1.clone()));

    vector<uint8_t> acl1_address = acl1.getAddress();
    vector<uint8_t> acl2_address = acl2->getAddress();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_address.size());
    EXPECT_EQ(acl1_address.size(), acl2_address.size());
    EXPECT_TRUE(equal(acl1_address.begin(), acl1_address.end(),
                acl2_address.begin()));

    EXPECT_EQ(acl1.getMasksize(), acl2->getMasksize());

    vector<uint8_t> acl1_netmask = acl1.getNetmask();
    vector<uint8_t> acl2_netmask = acl2->getNetmask();
    EXPECT_EQ(sizeof(V6ADDR_1), acl1_netmask.size());
    EXPECT_EQ(acl1_netmask.size(), acl2_netmask.size());
    EXPECT_TRUE(equal(acl1_netmask.begin(), acl1_netmask.end(),
                acl2_netmask.begin()));

    EXPECT_EQ(acl1.getInverse(), acl2->getInverse());
}

TEST(Ipv6Check, V6Compare) {
    // Set up some data.  The constant doesn't depend on the template parameter,
    // so use a type name that's short.
    vector<uint8_t> v6addr_2(V6ADDR_2, V6ADDR_2 + DerivedV6Check::IPV6_SIZE);
    vector<uint8_t> v6addr_2_48(V6ADDR_2_48,
                                V6ADDR_2_48 + DerivedV6Check::IPV6_SIZE);
    vector<uint8_t> v6addr_2_52(V6ADDR_2_52,
                                V6ADDR_2_52 + DerivedV6Check::IPV6_SIZE);
    vector<uint8_t> v6addr_3(V6ADDR_3, V6ADDR_3 + DerivedV6Check::IPV6_SIZE);

    // Exact address - match if given address matches stored address.
    DerivedV6Check acl1(string(V6ADDR_2_STRING) + string("/128"));
    EXPECT_TRUE(acl1.matches(v6addr_2));
    EXPECT_FALSE(acl1.matches(v6addr_2_52));
    EXPECT_FALSE(acl1.matches(v6addr_2_48));
    EXPECT_FALSE(acl1.matches(v6addr_3));

    // Exact address - match if address does not match stored address
    DerivedV6Check acl2(string(V6ADDR_2_STRING) + string("/128"), true);
    EXPECT_FALSE(acl2.matches(v6addr_2));
    EXPECT_TRUE(acl2.matches(v6addr_2_52));
    EXPECT_TRUE(acl2.matches(v6addr_2_48));
    EXPECT_TRUE(acl2.matches(v6addr_3));

    // Match if the address matches a mask
    DerivedV6Check acl3(string(V6ADDR_2_STRING) + string("/52"));
    EXPECT_TRUE(acl3.matches(v6addr_2));
    EXPECT_TRUE(acl3.matches(v6addr_2_52));
    EXPECT_FALSE(acl3.matches(v6addr_2_48));
    EXPECT_FALSE(acl3.matches(v6addr_3));

    // Match if the address does not match a mask
    DerivedV6Check acl4(string(V6ADDR_2_STRING) + string("/52"), true);
    EXPECT_FALSE(acl4.matches(v6addr_2));
    EXPECT_FALSE(acl4.matches(v6addr_2_52));
    EXPECT_TRUE(acl4.matches(v6addr_2_48));
    EXPECT_TRUE(acl4.matches(v6addr_3));
}

// *** IP Tests ***

// Provide specializations for a simple joint struct holding both an
// IPV4 address and an IPV6 address

typedef struct {
    bool        isv4;
    uint32_t    v4addr;
    uint8_t     v6addr[16];
} GeneralAddress;

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
    EXPECT_FALSE(acl.matches(test));
}

TEST(IpCheck, V6Test) {
    IpCheck<GeneralAddress> acl(string(V6ADDR_2_STRING) + string("/52"));

    GeneralAddress test;
    test.isv4 = false;
    copy(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2), test.v6addr);
    EXPECT_TRUE(acl.matches(test));

    copy(V6ADDR_2, V6ADDR_2_52 + sizeof(V6ADDR_2_52), test.v6addr);
    EXPECT_TRUE(acl.matches(test));

    copy(V6ADDR_2, V6ADDR_2_48 + sizeof(V6ADDR_2_48), test.v6addr);
    EXPECT_FALSE(acl.matches(test));

    test.isv4 = true;
    copy(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2), test.v6addr);
                                        // Correct V6 address
    EXPECT_FALSE(acl.matches(test));

    // Quick check for negative match
    IpCheck<GeneralAddress> acl2(string(V6ADDR_2_STRING) + string("/52"), true);
    test.isv4 = false;
    copy(V6ADDR_2, V6ADDR_2 + sizeof(V6ADDR_2), test.v6addr);
    EXPECT_FALSE(acl.matches(test));
}
