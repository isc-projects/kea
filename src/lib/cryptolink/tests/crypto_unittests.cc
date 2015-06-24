// Copyright (C) 2011, 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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
