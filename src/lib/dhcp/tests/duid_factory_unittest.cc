// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>
#include <dhcp/duid_factory.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <util/encode/hex.h>
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

const std::string DEFAULT_DUID_FILE = "duid-factory-test.duid";

class DUIDFactoryTest : public ::testing::Test {
public:

    DUIDFactoryTest();

    virtual ~DUIDFactoryTest();

    std::string absolutePath(const std::string& duid_file_path) const;

    void removeDefaultFile() const;

    std::vector<uint8_t> toVector(const std::string& hex) const;

    std::string toString(const std::vector<uint8_t>& vec) const;

    std::string timeAsHexString() const;

    void testLLT(const std::string& expected_htype,
                 const std::string& expected_time,
                 const bool time_equal,
                 const std::string& expected_hwaddr);

    DUIDFactory& factory() {
        return (factory_);
    }

private:

    IfaceMgrTestConfig iface_mgr_test_config_;

    DUIDFactory factory_;

};

DUIDFactoryTest::DUIDFactoryTest()
    : iface_mgr_test_config_(true),
      factory_(absolutePath(DEFAULT_DUID_FILE)) {
    removeDefaultFile();
}

DUIDFactoryTest::~DUIDFactoryTest() {
    removeDefaultFile();
}

std::string
DUIDFactoryTest::absolutePath(const std::string& duid_file_path) const {
    std::ostringstream s;
    s << TEST_DATA_BUILDDIR << "/" << duid_file_path;
    return (s.str());
}

void
DUIDFactoryTest::removeDefaultFile() const {
    static_cast<void>(remove(absolutePath(DEFAULT_DUID_FILE).c_str()));
}

std::vector<uint8_t>
DUIDFactoryTest::toVector(const std::string& hex) const {
    std::vector<uint8_t> vec;
    try {
        util::encode::decodeHex(hex, vec);
    } catch (...) {
        ADD_FAILURE() << "toVector: the following string " << hex
            << " is not a valid hex string";
    }

    return (vec);
}

std::string
DUIDFactoryTest::toString(const std::vector<uint8_t>& vec) const {
    try {
        return (util::encode::encodeHex(vec));
    } catch (...) {
        ADD_FAILURE() << "toString: unable to encode vector to"
            " hexadecimal string";
    }
    return ("");
}

std::string
DUIDFactoryTest::timeAsHexString() const {
    time_t current_time = time(NULL) - DUID_TIME_EPOCH;
    std::ostringstream s;
    s << std::hex << std::setw(8) << std::setfill('0') << current_time;
    return (boost::to_upper_copy<std::string>(s.str()));
}

void
DUIDFactoryTest::testLLT(const std::string& expected_htype,
                         const std::string& expected_time,
                         const bool time_equal,
                         const std::string& expected_hwaddr) {
    DuidPtr duid = factory().get();
    ASSERT_TRUE(duid);
    ASSERT_GE(duid->getDuid().size(), 14);
    std::string duid_text = toString(duid->getDuid());

    // DUID type LLT
    EXPECT_EQ("0001", duid_text.substr(0, 4));
    // Link layer type HTYPE_ETHER
    EXPECT_EQ(expected_htype, duid_text.substr(4, 4));

    // Verify if time is correct.
    if (time_equal) {
        // Strict time check.
        EXPECT_EQ(expected_time, duid_text.substr(8, 8));
    } else {
        // Timestamp equal or less current time.
        EXPECT_LE(duid_text.substr(8, 8), expected_time);
    }

    // MAC address of the interface.
    EXPECT_EQ(expected_hwaddr, duid_text.substr(16));
}


// This test verifies that the factory class will generate the entire
// DUID-LLT if there are no explicit values specified for the
// time, link layer type and link layer address.
TEST_F(DUIDFactoryTest, createLLT) {
    // Use 0 values for time and link layer type and empty vector for
    // the link layer address. The createLLT function will need to
    // use current time, HTYPE_ETHER and MAC address of one of the
    // interfaces.
    ASSERT_NO_THROW(factory().createLLT(0, 0, std::vector<uint8_t>()));
    testLLT("0001", timeAsHexString(), false, "010101010101");
}

// This test verifies that the factory class creates a DUID-LLT from
// the explicitly specified time, when link layer type and address are
// generated.
TEST_F(DUIDFactoryTest, createLLTExplicitTime) {
    ASSERT_NO_THROW(factory().createLLT(0, 0xABCDEF, std::vector<uint8_t>()));
    testLLT("0001", "00ABCDEF", true, "010101010101");
}

// This test verifies that the factory class creates DUID-LLT from
// the explcitly specified link layer type, when the time and link
// layer address are generated.
TEST_F(DUIDFactoryTest, createLLTExplicitHtype) {
    ASSERT_NO_THROW(factory().createLLT(HTYPE_FDDI, 0, std::vector<uint8_t>()));
    testLLT("0008", timeAsHexString(), false, "010101010101");
}

// This test verifies that the factory class creates DUID-LLT from
// explcitly specified link layer address, when other parameters
// are generated.
TEST_F(DUIDFactoryTest, createLLTExplicitLinkLayerAddress) {
    ASSERT_NO_THROW(factory().createLLT(0, 0, toVector("121212121212")));
    testLLT("0001", timeAsHexString(), false, "121212121212");
}

// This test verifies that the factory function creates DUID-LLT from
// all values explicitly specified.
TEST_F(DUIDFactoryTest, createLLTAllExplcitParameters) {
    ASSERT_NO_THROW(factory().createLLT(HTYPE_FDDI, 0xFAFAFAFA,
                                        toVector("24242424242424242424")));
    testLLT("0008", "FAFAFAFA", true, "24242424242424242424");
}

} // End anonymous namespace
