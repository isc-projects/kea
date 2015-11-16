// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/duid.h>
#include <dhcpsrv/cfg_duid.h>
#include <exceptions/exceptions.h>
#include <util/encode/hex.h>
#include <gtest/gtest.h>
#include <stdint.h>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::dhcp;

namespace {

/// @brief Converts vector to string of hexadecimal digits.
///
/// @param vec Input vector.
/// @return String of hexadecimal digits converted from vector.
std::string toString(const std::vector<uint8_t>& vec) {
    try {
        return (util::encode::encodeHex(vec));
    } catch (...) {
        ADD_FAILURE() << "toString: unable to encode vector to"
            " hexadecimal string";
    }
    return ("");
}


// This test verifies default values of the DUID configuration.
TEST(CfgDUIDTest, defaults) {
    CfgDUID cfg_duid;
    EXPECT_EQ(DUID::DUID_LLT, cfg_duid.getType());

    EXPECT_TRUE(cfg_duid.getIdentifier().empty())
        << "expected empty identifier, found: "
        << toString(cfg_duid.getIdentifier());

    EXPECT_EQ(0, cfg_duid.getHType());
    EXPECT_EQ(0, cfg_duid.getTime());
    EXPECT_EQ(0, cfg_duid.getEnterpriseId());
}

// This test verifies that it is possible to set values for the CfgDUID.
TEST(CfgDUIDTest, setValues) {
    CfgDUID cfg_duid;
    // Set values.
    ASSERT_NO_THROW(cfg_duid.setType(DUID::DUID_EN));
    ASSERT_NO_THROW(cfg_duid.setIdentifier("ABCDEF"));
    ASSERT_NO_THROW(cfg_duid.setHType(100));
    ASSERT_NO_THROW(cfg_duid.setTime(32100));
    ASSERT_NO_THROW(cfg_duid.setEnterpriseId(10));

    // Check that values have been set correctly.
    EXPECT_EQ(DUID::DUID_EN, cfg_duid.getType());
    EXPECT_EQ("ABCDEF", toString(cfg_duid.getIdentifier()));
    EXPECT_EQ(100, cfg_duid.getHType());
    EXPECT_EQ(32100, cfg_duid.getTime());
    EXPECT_EQ(10, cfg_duid.getEnterpriseId());
}

// This test checks positive scenarios for setIdentifier.
TEST(CfgDUIDTest, setIdentifier) {
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

TEST(CfgDUIDTest, setInvalidIdentifier) {
    CfgDUID cfg_duid;
    // Check that hexadecimal characters may be lower case.
    ASSERT_NO_THROW(cfg_duid.setIdentifier("a1b2c3"));
    EXPECT_EQ("A1B2C3", toString(cfg_duid.getIdentifier()));

    // Try to set invalid value. This should not modify original
    // value.
    ASSERT_THROW(cfg_duid.setIdentifier("hola!"), isc::BadValue);
    EXPECT_EQ("A1B2C3", toString(cfg_duid.getIdentifier()));
}

} // end of anonymous namespace
