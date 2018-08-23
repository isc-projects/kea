// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <util/encode/hex.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_rng.h>

using namespace std;
using namespace isc::cryptolink;

// Test get version
TEST(CryptoLinkTest, Version) {
    EXPECT_NO_THROW(CryptoLink::getVersion());
}

// Tests whether getCryptoLink() returns a singleton instance
TEST(CryptoLinkTest, Singleton) {
    const CryptoLink& c1 = CryptoLink::getCryptoLink();
    const CryptoLink& c2 = CryptoLink::getCryptoLink();
    ASSERT_EQ(&c1, &c2);
}

// Tests whether getRNG() returns a global value
TEST(CryptoLinkTest, GlobalRNG) {
    CryptoLink& c = CryptoLink::getCryptoLink();
    RNGPtr rng1 = c.getRNG();
    RNGPtr rng2 = c.getRNG();
    ASSERT_EQ(rng1, rng2);
}

// Tests whether RNG works
TEST(CryptoLinkTest, RNG) {
    RNGPtr rng = CryptoLink::getCryptoLink().getRNG();
    vector<uint8_t> data;
    ASSERT_NO_THROW(data = rng->random(16));
    ASSERT_EQ(16, data.size());
    vector<uint8_t> zero;
    zero.resize(16);
    EXPECT_NE(0, memcmp(&zero[0], &data[0], zero.size()));

    // Retry with the function (vs method)
    vector<uint8_t> dataf;
    ASSERT_NO_THROW(dataf = random(16));
    ASSERT_EQ(16, dataf.size());
    EXPECT_NE(0, memcmp(&zero[0], &dataf[0], zero.size()));
    EXPECT_NE(0, memcmp(&data[0], &dataf[0], zero.size()));
}
