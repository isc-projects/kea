// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <util/encode/hex.h>

#include <cryptolink/cryptolink.h>

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
