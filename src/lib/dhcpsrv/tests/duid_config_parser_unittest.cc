// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_duid.h>
#include <dhcpsrv/parsers/duid_config_parser.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <util/encode/hex.h>
#include <gtest/gtest.h>
#include <limits>
#include <sstream>
#include <string>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for @c DUIDConfigParser
class DUIDConfigParserTest : public ::testing::Test {
public:

    /// @brief Creates simple configuration with DUID type only.
    ///
    /// @param duid_type DUID type in the textual format.
    std::string createConfigWithType(const std::string& duid_type) const;

    /// @brief Creates simple configuration with DUID type and one
    /// numeric parameter.
    ///
    /// @param name Parameter name.
    /// @param value Parameter value.
    std::string createConfigWithInteger(const std::string& name,
                                        const int64_t value) const;

    /// @brief Parse configuration.
    ///
    /// @param config String representing DUID configuration.
    void build(const std::string& config) const;

    /// @brief Test that only a DUID type can be specified.
    ///
    /// @param duid_type DUID type in numeric format.
    /// @param duid_type_text DUID type in textual format.
    void testTypeOnly(const DUID::DUIDType& duid_type,
                      const std::string duid_type_text) const;

    /// @brief Test that invalid configuration is rejected.
    ///
    /// @param config Holds JSON configuration to be used.
    void testInvalidConfig(const std::string& config) const;

    /// @brief Test out of range numeric values.
    ///
    /// @param param_name Parameter name.
    /// @tparam Type of the numeric parameter.
    template<typename NumericType>
    void testOutOfRange(const std::string& param_name) {
        // Obtain maximum value for the specified numeric type.
        const uint64_t max_value = std::numeric_limits<NumericType>::max();

        // Negative values are not allowed.
        EXPECT_THROW(build(createConfigWithInteger(param_name, -1)),
                     DhcpConfigError);
        // Zero is allowed.
        EXPECT_NO_THROW(build(createConfigWithInteger(param_name, 0)));
        // Maximum value.
        EXPECT_NO_THROW(build(createConfigWithInteger(param_name, max_value)));
        // Value greater than maximum should result in exception.
        EXPECT_THROW(build(createConfigWithInteger(param_name, max_value + 1)),
                     DhcpConfigError);
    }

    /// @brief Converts vector to string of hexadecimal digits.
    ///
    /// @param vec Input vector.
    /// @return String of hexadecimal digits converted from vector.
    std::string toString(const std::vector<uint8_t>& vec) const;
};

std::string 
DUIDConfigParserTest::createConfigWithType(const std::string& duid_type) const {
    std::ostringstream s;
    s << "{ \"type\": \"" << duid_type << "\" }";
    return (s.str());
}

std::string
DUIDConfigParserTest::createConfigWithInteger(const std::string& name,
                                              const int64_t value) const {
    std::ostringstream s;
    s << "{ \"type\": \"LLT\", \"" << name << "\": " << value << " }";
    return (s.str());
}

void
DUIDConfigParserTest::build(const std::string& config) const {
    ElementPtr config_element = Element::fromJSON(config);
    DUIDConfigParser parser;
    parser.build(config_element);
}


void
DUIDConfigParserTest::testTypeOnly(const DUID::DUIDType& duid_type,
                                   const std::string duid_type_text) const {
    // Use DUID configuration with only a "type".
    ASSERT_NO_THROW(build(createConfigWithType(duid_type_text)));

    // Make sure that the type is correct and that other parameters are set
    // to their defaults.
    CfgDUIDPtr cfg_duid = CfgMgr::instance().getStagingCfg()->getCfgDUID();
    EXPECT_EQ(duid_type, cfg_duid->getType());
    EXPECT_TRUE(cfg_duid->getIdentifier().empty());
    EXPECT_EQ(0, cfg_duid->getHType());
    EXPECT_EQ(0, cfg_duid->getTime());
    EXPECT_EQ(0, cfg_duid->getEnterpriseId());
}

void
DUIDConfigParserTest::testInvalidConfig(const std::string& config) const {
    EXPECT_THROW(build(config), DhcpConfigError);
}

std::string
DUIDConfigParserTest::toString(const std::vector<uint8_t>& vec) const {
    try {
        return (util::encode::encodeHex(vec));
    } catch (...) {
        ADD_FAILURE() << "toString: unable to encode vector to"
            " hexadecimal string";
    }
    return ("");
}

// This test verifies that it is allowed to specify a DUID-LLT type.
TEST_F(DUIDConfigParserTest, typeOnlyLLT) {
    testTypeOnly(DUID::DUID_LLT, "LLT");
}

// This test verifies that it is allowed to specify a DUID-EN type.
TEST_F(DUIDConfigParserTest, typeOnlyEN) {
    testTypeOnly(DUID::DUID_EN, "EN");
}

// This test verifies that it is allowed to specify a DUID-LL type.
TEST_F(DUIDConfigParserTest, typeOnlyLL) {
    testTypeOnly(DUID::DUID_LL, "LL");
}

// This test verifies that using unsupported DUID type will result in
// configuration error.
TEST_F(DUIDConfigParserTest, typeInvalid) {
    testInvalidConfig(createConfigWithType("WRONG"));
}

// This test verifies that DUID type is required.
TEST_F(DUIDConfigParserTest, noType) {
    // First check that the configuration with DUID type specified is
    // accepted.
    ASSERT_NO_THROW(build("{ \"type\": \"LLT\", \"time\": 1 }"));
    // Now remove the type and expect an error.
    testInvalidConfig("{ \"time\": 1 }");
}

// This test verifies that all parameters can be set.
TEST_F(DUIDConfigParserTest, allParameters) {
    // Set all parameters.
    ASSERT_NO_THROW(build("{ \"type\": \"EN\","
                          "  \"identifier\": \"ABCDEF\","
                          "  \"time\": 100,"
                          "  \"htype\": 8,"
                          "  \"enterprise-id\": 2024,"
                          "  \"persist\": false"
                          "}"));

    // Verify that parameters have been set correctly.
    CfgDUIDPtr cfg_duid = CfgMgr::instance().getStagingCfg()->getCfgDUID();
    EXPECT_EQ(DUID::DUID_EN, cfg_duid->getType());
    EXPECT_EQ("ABCDEF", toString(cfg_duid->getIdentifier()));
    EXPECT_EQ(8, cfg_duid->getHType());
    EXPECT_EQ(100, cfg_duid->getTime());
    EXPECT_EQ(2024, cfg_duid->getEnterpriseId());
    EXPECT_FALSE(cfg_duid->persist());
}

// Test out of range values for time.
TEST_F(DUIDConfigParserTest, timeOutOfRange) {
    testOutOfRange<uint32_t>("time");
}

// Test out of range values for hardware type.
TEST_F(DUIDConfigParserTest, htypeOutOfRange) {
    testOutOfRange<uint16_t>("htype");
}

// Test out of range values for enterprise id.
TEST_F(DUIDConfigParserTest, enterpriseIdOutOfRange) {
    testOutOfRange<uint32_t>("enterprise-id");
}

} // end of anonymous namespace
