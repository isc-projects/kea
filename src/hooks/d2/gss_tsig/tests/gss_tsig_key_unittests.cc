// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dns/name.h>
#include <gss_tsig_key.h>
#include <gss_tsig_api_utils.h>
#include <testutils/gtest_utils.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono;
using namespace isc;
using namespace isc::cryptolink;
using namespace isc::dns;
using namespace isc::gss_tsig;
using namespace isc::gss_tsig::test;

namespace {

/// @brief Test fixture for testing the GSS-TSIG key.
class GssTsigKeyTest : public GssApiBaseTest {
public:
    /// @brief Constructor.
    GssTsigKeyTest() : GssApiBaseTest() {
    }
};

/// @brief Check the constructor builds what is expected.
TEST_F(GssTsigKeyTest, basic) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    EXPECT_EQ(Name(name), key->getKeyName());
    EXPECT_EQ(name, key->getKeyName().toText());
    EXPECT_EQ(Name("gss-tsig."), key->getAlgorithmName());
    EXPECT_EQ(TSIGKey::GSSTSIG_NAME(), key->getAlgorithmName());
    EXPECT_EQ(UNKNOWN_HASH, key->getAlgorithm());
    EXPECT_EQ(0, key->getDigestbits());
    EXPECT_EQ(0, key->getSecretLength());
    EXPECT_FALSE(key->getSecret());
    string expected = name + "::gss-tsig.";
    EXPECT_EQ(expected, key->toText());
    EXPECT_FALSE(key->getSecCtx().get());
    system_clock::time_point epoch;
    system_clock::time_point now = system_clock::now();
    uint32_t now32 = static_cast<uint32_t>(system_clock::to_time_t(now));
    EXPECT_EQ(epoch, key->getInception());
    EXPECT_EQ(0, key->getInception32());
    EXPECT_EQ(epoch, key->getExpire());
    EXPECT_EQ(0, key->getExpire32());
    EXPECT_NO_THROW(key->setInception(now));
    EXPECT_EQ(now, key->getInception());
    EXPECT_EQ(now32, key->getInception32());
    std::chrono::hours day(24);
    system_clock::time_point tomorrow = now + day;
    uint32_t tomorrow32 = static_cast<uint32_t>(system_clock::to_time_t(tomorrow));
    EXPECT_NO_THROW(key->setExpire(tomorrow));
    EXPECT_EQ(tomorrow, key->getExpire());
    EXPECT_EQ(tomorrow32, key->getExpire32());
}

}
