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
#include <util/range_utilities.h>
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

/// @brief Name of the file holding DUID generated during a test.
const std::string DEFAULT_DUID_FILE = "duid-factory-test.duid";

/// @brief Test fixture class for @c DUIDFactory.
class DUIDFactoryTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Creates fake interface configuration. It also creates an instance
    /// of the @c DUIDFactory object used throughout the tests.
    DUIDFactoryTest();

    /// @brief Destructor.
    virtual ~DUIDFactoryTest();

    /// @brief Returns absolute path to a test DUID storage.
    ///
    /// @param duid_file_name Name of the file holding test DUID.
    std::string absolutePath(const std::string& duid_file_path) const;

    /// @brief Removes default DUID file used in the tests.
    ///
    /// This method is called from both constructor and destructor.
    void removeDefaultFile() const;

    /// @brief Returns contents of the DUID file.
    std::string readDefaultFile() const;

    /// @brief Converts string of hexadecimal digits to vector.
    ///
    /// @param hex String representation.
    /// @return Vector created from the converted string.
    std::vector<uint8_t> toVector(const std::string& hex) const;

    /// @brief Converts vector to string of hexadecimal digits.
    ///
    /// @param vec Input vector.
    /// @return String of hexadecimal digits converted from vector.
    std::string toString(const std::vector<uint8_t>& vec) const;

    /// @brief Converts current time to a string of hexadecimal digits.
    ///
    /// @return Time represented as text.
    std::string timeAsHexString() const;

    /// @brief Tests creation of a DUID-LLT.
    ///
    /// @param expected_htype Expected link layer type as string.
    /// @param expected_time Expected time as string.
    /// @param time_equal Indicates if @c expected time should be
    /// compared for equality with the time being part of a DUID
    /// (if true), or the time being part of the DUID should be
    /// less or equal current time (if false).
    /// @param expected_hwaddr Expected link layer type as string.
    void testLLT(const std::string& expected_htype,
                 const std::string& expected_time,
                 const bool time_equal,
                 const std::string& expected_hwaddr);

    /// @brief Tests creation of a DUID-LLT.
    ///
    /// @param expected_htype Expected link layer type as string.
    /// @param expected_time Expected time as string.
    /// @param time_equal Indicates if @c expected time should be
    /// compared for equality with the time being part of a DUID
    /// (if true), or the time being part of the DUID should be
    /// less or equal current time (if false).
    /// @param expected_hwaddr Expected link layer type as string.
    /// @param factory_ref Reference to DUID factory.
    void testLLT(const std::string& expected_htype,
                 const std::string& expected_time,
                 const bool time_equal,
                 const std::string& expected_hwaddr,
                 DUIDFactory& factory_ref);

    /// @brief Tests creation of a DUID-EN.
    ///
    /// @param expected_enterprise_id Expected enterprise id as string.
    /// @param expected_identifier Expected variable length identifier
    /// as string.
    void testEN(const std::string& expected_enterprise_id,
                const std::string& expected_identifier = "");

    /// @brief Tests creation of a DUID-LL.
    ///
    /// @param expected_htype Expected link layer type as string.
    /// @param expected_hwaddr Expected link layer type as string.
    void testLL(const std::string& expected_htype,
                const std::string& expected_hwaddr);

    /// @brief Returns reference to a default factory.
    DUIDFactory& factory() {
        return (factory_);
    }

private:

    /// @brief Creates fake interface configuration.
    IfaceMgrTestConfig iface_mgr_test_config_;

    /// @brief Holds default instance of the @c DUIDFactory class, being
    /// used throughout the tests.
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

std::string
DUIDFactoryTest::readDefaultFile() const {
    std::ifstream ifs;
    ifs.open(absolutePath(DEFAULT_DUID_FILE).c_str(), std::ifstream::in);
    if (!ifs.good()) {
        return (std::string());
    }
    std::string buf;
    std::ostringstream output;
    while (!ifs.eof() && ifs.good()) {
        ifs >> buf;
        output << buf;
    }
    ifs.close();

    return (output.str());
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
    testLLT(expected_htype, expected_time, time_equal, expected_hwaddr,
            factory());
}

void
DUIDFactoryTest::testLLT(const std::string& expected_htype,
                         const std::string& expected_time,
                         const bool time_equal,
                         const std::string& expected_hwaddr,
                         DUIDFactory& factory_ref) {
    DuidPtr duid = factory_ref.get();
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

    // Compare DUID with the one stored in the file.
    EXPECT_EQ(duid->toText(), readDefaultFile());
}



void
DUIDFactoryTest::testEN(const std::string& expected_enterprise_id,
                        const std::string& expected_identifier) {
    DuidPtr duid = factory().get();
    ASSERT_TRUE(duid);
    ASSERT_GE(duid->getDuid().size(), 8);
    std::string duid_text = toString(duid->getDuid());

    // DUID type EN.
    EXPECT_EQ("0002", duid_text.substr(0, 4));
    // Verify enterprise ID.
    EXPECT_EQ(expected_enterprise_id, duid_text.substr(4, 8));

    // If no expecyed identifier, we should at least check that the
    // generated identifier contains some random non-zero digits.
    if (expected_identifier.empty()) {
        EXPECT_FALSE(isRangeZero(duid->getDuid().begin(),
                                 duid->getDuid().end()));
    } else {
        // Check if identifier matches.
        EXPECT_EQ(expected_identifier, duid_text.substr(12));
    }

    // Compare DUID with the one stored in the file.
    EXPECT_EQ(duid->toText(), readDefaultFile());
}

void
DUIDFactoryTest::testLL(const std::string& expected_htype,
                        const std::string& expected_hwaddr) {
    DuidPtr duid = factory().get();
    ASSERT_TRUE(duid);
    ASSERT_GE(duid->getDuid().size(), 8);
    std::string duid_text = toString(duid->getDuid());

    // DUID type LL
    EXPECT_EQ("0003", duid_text.substr(0, 4));
    // Link layer type HTYPE_ETHER
    EXPECT_EQ(expected_htype, duid_text.substr(4, 4));

    // MAC address of the interface.
    EXPECT_EQ(expected_hwaddr, duid_text.substr(8));

    // Compare DUID with the one stored in the file.
    EXPECT_EQ(duid->toText(), readDefaultFile());
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

// This test verifies that the factory class creates DUID-LLT with
// the link layer type of the interface which link layer address
// is used to generate the DUID.
TEST_F(DUIDFactoryTest, createLLTExplicitHtype) {
    ASSERT_NO_THROW(factory().createLLT(HTYPE_FDDI, 0, std::vector<uint8_t>()));
    testLLT("0001", timeAsHexString(), false, "010101010101");
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

// This test verifies that the createLLT function will try to reuse existing
// DUID for the non-explicitly specified values.
TEST_F(DUIDFactoryTest, createLLTReuse) {
    // Create DUID-LLT and store it in a file.
    ASSERT_NO_THROW(factory().createLLT(HTYPE_FDDI, 0xFAFAFAFA,
                                        toVector("242424242424")));
    // Create another factory class, which uses the same file.
    DUIDFactory factory2(absolutePath(DEFAULT_DUID_FILE));
    // Create DUID-LLT without specifying hardware type, time and
    // link layer address. The factory function should use the
    // values in the existing DUID.
    ASSERT_NO_THROW(factory2.createLLT(0, 0, std::vector<uint8_t>()));
    testLLT("0008", "FAFAFAFA", true, "242424242424");
}

// This test verifies that the DUID-EN can be generated entirely. Such
// generated DUID contains ISC enterprise id and the random identifier.
TEST_F(DUIDFactoryTest, createEN) {
    ASSERT_NO_THROW(factory().createEN(0, std::vector<uint8_t>()));
    testEN("000009BF");
}

// This test verifies that the DUID-EN may contain custom enterprise id.
TEST_F(DUIDFactoryTest, createENExplicitEnterpriseId) {
    ASSERT_NO_THROW(factory().createEN(0xABCDEFAB, std::vector<uint8_t>()));
    testEN("ABCDEFAB");
}

// This test verifies that DUID-EN may contain custom variable length
// identifier and default enterprise id.
TEST_F(DUIDFactoryTest, createENExplicitIdentifier) {
    ASSERT_NO_THROW(factory().createEN(0, toVector("1212121212121212")));
    testEN("000009BF", "1212121212121212");
}

// This test verifies that DUID-EN can be created from explicit enterprise id
// and identifier.
TEST_F(DUIDFactoryTest, createENAllExplicitParameters) {
    ASSERT_NO_THROW(factory().createEN(0x01020304, toVector("ABCD")));
    testEN("01020304", "ABCD");
}

// This test verifies that the createEN function will try to reuse existing
// DUID for the non-explicitly specified values.
TEST_F(DUIDFactoryTest, createENReuse) {
    // Create DUID-EN and store it in a file.
    ASSERT_NO_THROW(factory().createEN(0xFAFAFAFA, toVector("242424242424")));
    // Create another factory class, which uses the same file.
    DUIDFactory factory2(absolutePath(DEFAULT_DUID_FILE));
    ASSERT_NO_THROW(factory2.createEN(0, std::vector<uint8_t>()));
    testEN("FAFAFAFA", "242424242424");
}

// This test verifies that the DUID-LL is generated when neither link layer
// type nor address is specified.
TEST_F(DUIDFactoryTest, createLL) {
    ASSERT_NO_THROW(factory().createLL(0, std::vector<uint8_t>()));
    testLL("0001", "010101010101");
}

// This test verifies that the DUID-LL is generated and the link layer type
// used is taken from the interface used to generate link layer address.
TEST_F(DUIDFactoryTest, createLLExplicitHtype) {
    ASSERT_NO_THROW(factory().createLL(HTYPE_FDDI, std::vector<uint8_t>()));
    testLL("0001", "010101010101");
}

// This test verifies that DUID-LL is created from explicitly provided
// link layer type and address.
TEST_F(DUIDFactoryTest, createLLAllExplicitParameters) {
    ASSERT_NO_THROW(factory().createLL(HTYPE_FDDI, toVector("242424242424")));
    testLL("0008", "242424242424");
}

// This test verifies that DUID-LLT is created when caller wants to obtain
// it and it doesn't exist.
TEST_F(DUIDFactoryTest, createLLTIfNotExists) {
    DuidPtr duid;
    ASSERT_NO_THROW(duid = factory().get());
    ASSERT_TRUE(duid);
    EXPECT_EQ(DUID::DUID_LLT, duid->getType());
}

// This test verifies that DUID-EN when there is no suitable interface to
// use to create DUID-LLT.
TEST_F(DUIDFactoryTest, createENIfNotExists) {
    // Remove interfaces. The DUID-LLT is a default type but it requires
    // that an interface with a suitable link-layer address is present
    // in the system. By removing the interfaces we cause the factory
    // to fail to generate DUID-LLT. It should fall back to DUID-EN.
    IfaceMgr::instance().clearIfaces();

    DuidPtr duid;
    ASSERT_NO_THROW(duid = factory().get());
    ASSERT_TRUE(duid);
    EXPECT_EQ(DUID::DUID_EN, duid->getType());
}

// This test verifies that the createLL function will try to reuse existing
// DUID for the non-explicitly specified values.
TEST_F(DUIDFactoryTest, createLLReuse) {
    // Create DUID-EN and store it in a file.
    ASSERT_NO_THROW(factory().createLL(HTYPE_FDDI, toVector("242424242424")));
    // Create another factory class, which uses the same file.
    DUIDFactory factory2(absolutePath(DEFAULT_DUID_FILE));
    // Create DUID-LL without specifying hardware type, time and
    // link layer address. The factory function should use the
    // values in the existing DUID.
    ASSERT_NO_THROW(factory2.createLL(0, std::vector<uint8_t>()));
    testLL("0008", "242424242424");
}

// This test verifies that it is possible to override a DUID.
TEST_F(DUIDFactoryTest, override) {
    // Create default DUID-LLT.
    ASSERT_NO_THROW(static_cast<void>(factory().get()));
    testLLT("0001", timeAsHexString(), false, "010101010101");

    ASSERT_NO_THROW(factory().createEN(0, toVector("12131415")));
    testEN("000009BF", "12131415");
}

} // End anonymous namespace
