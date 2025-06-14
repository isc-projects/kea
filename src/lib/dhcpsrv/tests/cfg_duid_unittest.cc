// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/duid.h>
#include <dhcpsrv/cfg_duid.h>
#include <exceptions/exceptions.h>
#include <testutils/io_utils.h>
#include <testutils/test_to_element.h>
#include <util/encode/encode.h>
#include <gtest/gtest.h>
#include <stdint.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::test;
using namespace isc::data;

namespace {

/// @brief Specifies file name holding DUID.
const std::string DUID_FILE_NAME = "test.duid";

/// @brief Test fixture class for @c CfgDUID.
class CfgDUIDTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Removes DUID file if present.
    CfgDUIDTest() {
        static_cast<void>(remove(absolutePath(DUID_FILE_NAME).c_str()));
    }

    /// @brief Destructor.
    ///
    /// Removes DUID file if present.
    virtual ~CfgDUIDTest() {
        static_cast<void>(remove(absolutePath(DUID_FILE_NAME).c_str()));
    }

    /// @brief Returns absolute path to a file used by tests.
    ///
    /// @param filename File name.
    std::string absolutePath(const std::string& filename) const;

    /// @brief Converts vector to string of hexadecimal digits.
    ///
    /// @param vec Input vector.
    /// @return String of hexadecimal digits converted from vector.
    std::string toString(const std::vector<uint8_t>& vec) const;
};

std::string
CfgDUIDTest::absolutePath(const std::string& filename) const {
    std::ostringstream s;
    s << TEST_DATA_BUILDDIR << "/" << filename;
    return (s.str());
}

/// @brief Converts vector to string of hexadecimal digits.
///
/// @param vec Input vector.
/// @return String of hexadecimal digits converted from vector.
std::string
CfgDUIDTest::toString(const std::vector<uint8_t>& vec) const {
    try {
        return (util::encode::encodeHex(vec));
    } catch (...) {
        ADD_FAILURE() << "toString: unable to encode vector to"
            " hexadecimal string";
    }
    return ("");
}


// This test verifies default values of the DUID configuration.
TEST_F(CfgDUIDTest, defaults) {
    CfgDUID cfg_duid;
    EXPECT_EQ(DUID::DUID_LLT, cfg_duid.getType());

    EXPECT_TRUE(cfg_duid.getIdentifier().empty())
        << "expected empty identifier, found: "
        << toString(cfg_duid.getIdentifier());

    EXPECT_EQ(0, cfg_duid.getHType());
    EXPECT_EQ(0, cfg_duid.getTime());
    EXPECT_EQ(0, cfg_duid.getEnterpriseId());
    EXPECT_TRUE(cfg_duid.persist());
    EXPECT_FALSE(cfg_duid.getContext());

    std::string expected = "{ \"type\": \"LLT\",\n"
        "\"identifier\": \"\",\n"
        "\"htype\": 0,\n"
        "\"time\": 0,\n"
        "\"enterprise-id\": 0,\n"
        "\"persist\": true }";
    runToElementTest<CfgDUID>(expected, cfg_duid);
}

// This test verifies that it is possible to set values for the CfgDUID.
TEST_F(CfgDUIDTest, setValues) {
    CfgDUID cfg_duid;
    // Set values.
    ASSERT_NO_THROW(cfg_duid.setType(DUID::DUID_EN));
    ASSERT_NO_THROW(cfg_duid.setIdentifier("ABCDEF"));
    ASSERT_NO_THROW(cfg_duid.setHType(100));
    ASSERT_NO_THROW(cfg_duid.setTime(32100));
    ASSERT_NO_THROW(cfg_duid.setEnterpriseId(10));
    ASSERT_NO_THROW(cfg_duid.setPersist(false));
    std::string user_context = "{ \"comment\": \"bar\", \"foo\": 1 }";
    ASSERT_NO_THROW(cfg_duid.setContext(Element::fromJSON(user_context)));

    // Check that values have been set correctly.
    EXPECT_EQ(DUID::DUID_EN, cfg_duid.getType());
    EXPECT_EQ("ABCDEF", toString(cfg_duid.getIdentifier()));
    EXPECT_EQ(100, cfg_duid.getHType());
    EXPECT_EQ(32100, cfg_duid.getTime());
    EXPECT_EQ(10, cfg_duid.getEnterpriseId());
    EXPECT_FALSE(cfg_duid.persist());
    ASSERT_TRUE(cfg_duid.getContext());
    EXPECT_EQ(user_context, cfg_duid.getContext()->str());

    std::string expected = "{\n"
        " \"type\": \"EN\",\n"
        " \"identifier\": \"ABCDEF\",\n"
        " \"htype\": 100,\n"
        " \"time\": 32100,\n"
        " \"enterprise-id\": 10,\n"
        " \"persist\": false,\n"
        " \"user-context\": { \"foo\": 1,\n"
        " \"comment\": \"bar\" }\n"
        "}";
    runToElementTest<CfgDUID>(expected, cfg_duid);
}

// This test checks positive scenarios for setIdentifier.
TEST_F(CfgDUIDTest, setIdentifier) {
    CfgDUID cfg_duid;
    // Check that hexadecimal characters may be lower case.
    ASSERT_NO_THROW(cfg_duid.setIdentifier("a1b2c3"));
    EXPECT_EQ("A1B2C3", toString(cfg_duid.getIdentifier()));

    // Check that whitespaces are allowed.
    ASSERT_NO_THROW(cfg_duid.setIdentifier("  ABC  DEF    "));
    EXPECT_EQ("ABCDEF", toString(cfg_duid.getIdentifier()));

    // Check that identifier including only whitespaces is ignored.
    ASSERT_NO_THROW(cfg_duid.setIdentifier("      "));
    EXPECT_TRUE(cfg_duid.getIdentifier().empty())
        << "expected empty identifier, found: "
        << toString(cfg_duid.getIdentifier());
}

// This test verifies that the invalid identifier is rejected and
// exception is thrown.
TEST_F(CfgDUIDTest, setInvalidIdentifier) {
    CfgDUID cfg_duid;
    // Check that hexadecimal characters may be lower case.
    ASSERT_NO_THROW(cfg_duid.setIdentifier("a1b2c3"));
    EXPECT_EQ("A1B2C3", toString(cfg_duid.getIdentifier()));

    // Try to set invalid value. This should not modify original
    // value.
    ASSERT_THROW(cfg_duid.setIdentifier("hola!"), isc::BadValue);
    EXPECT_EQ("A1B2C3", toString(cfg_duid.getIdentifier()));
}

// This method checks that the DUID-LLT can be created from the
// specified configuration.
TEST_F(CfgDUIDTest, createLLT) {
    CfgDUID cfg;
    ASSERT_NO_THROW(cfg.setType(DUID::DUID_LLT));
    ASSERT_NO_THROW(cfg.setTime(0x1123));
    ASSERT_NO_THROW(cfg.setHType(8));
    ASSERT_NO_THROW(cfg.setIdentifier("12564325A63F"));

    // Generate DUID from this configuration.
    DuidPtr duid;
    ASSERT_NO_THROW(duid = cfg.create(absolutePath(DUID_FILE_NAME)));
    ASSERT_TRUE(duid);

    // Verify if the DUID is correct.
    EXPECT_EQ("00:01:00:08:00:00:11:23:12:56:43:25:a6:3f",
              duid->toText());

    // Verify that the DUID file has been created.
    EXPECT_TRUE(fileExists(absolutePath(DUID_FILE_NAME)));

    // Verify getCurrentDuid() returns the value created.
    DuidPtr current_duid = cfg.getCurrentDuid();
    ASSERT_TRUE(current_duid);
    EXPECT_EQ(*current_duid, *duid);
}

// This method checks that the DUID-EN can be created from the
// specified configuration.
TEST_F(CfgDUIDTest, createEN) {
    CfgDUID cfg;
    ASSERT_NO_THROW(cfg.setType(DUID::DUID_EN));
    ASSERT_NO_THROW(cfg.setIdentifier("250F3E26A762"));
    ASSERT_NO_THROW(cfg.setEnterpriseId(0x1010));

    // Generate DUID from this configuration.
    DuidPtr duid;
    ASSERT_NO_THROW(duid = cfg.create(absolutePath(DUID_FILE_NAME)));
    ASSERT_TRUE(duid);

    // Verify if the DUID is correct.
    EXPECT_EQ("00:02:00:00:10:10:25:0f:3e:26:a7:62", duid->toText());

    // Verify that the DUID file has been created.
    EXPECT_TRUE(fileExists(absolutePath(DUID_FILE_NAME)));

    // Verify getCurrentDuid() returns the value created.
    DuidPtr current_duid = cfg.getCurrentDuid();
    ASSERT_TRUE(current_duid);
    EXPECT_EQ(*current_duid, *duid);
}

// This method checks that the DUID-LL can be created from the
// specified configuration.
TEST_F(CfgDUIDTest, createLL) {
    CfgDUID cfg;
    ASSERT_NO_THROW(cfg.setType(DUID::DUID_LL));
    ASSERT_NO_THROW(cfg.setIdentifier("124134A4B367"));
    ASSERT_NO_THROW(cfg.setHType(2));

    // Generate DUID from this configuration.
    DuidPtr duid;
    ASSERT_NO_THROW(duid = cfg.create(absolutePath(DUID_FILE_NAME)));
    ASSERT_TRUE(duid);

    // Verify if the DUID is correct.
    EXPECT_EQ("00:03:00:02:12:41:34:a4:b3:67", duid->toText());

    // Verify that the DUID file has been created.
    EXPECT_TRUE(fileExists(absolutePath(DUID_FILE_NAME)));

    // Verify getCurrentDuid() returns the value created.
    DuidPtr current_duid = cfg.getCurrentDuid();
    ASSERT_TRUE(current_duid);
    EXPECT_EQ(*current_duid, *duid);
}

// This test verifies that it is possible to disable storing
// generated DUID on a hard drive.
TEST_F(CfgDUIDTest, createDisableWrite) {
    CfgDUID cfg;
    ASSERT_NO_THROW(cfg.setType(DUID::DUID_EN));
    ASSERT_NO_THROW(cfg.setIdentifier("250F3E26A762"));
    ASSERT_NO_THROW(cfg.setEnterpriseId(0x1010));
    ASSERT_NO_THROW(cfg.setPersist(false));

    // Generate DUID from this configuration.
    DuidPtr duid;
    ASSERT_NO_THROW(duid = cfg.create(absolutePath(DUID_FILE_NAME)));
    ASSERT_TRUE(duid);

    // Verify if the DUID is correct.
    EXPECT_EQ("00:02:00:00:10:10:25:0f:3e:26:a7:62", duid->toText());

    // DUID persistence is disabled so there should be no DUID file.
    EXPECT_FALSE(fileExists(absolutePath(DUID_FILE_NAME)));

    // Verify getCurrentDuid() returns the value created.
    DuidPtr current_duid = cfg.getCurrentDuid();
    ASSERT_TRUE(current_duid);
    EXPECT_EQ(*current_duid, *duid);
}

} // end of anonymous namespace
