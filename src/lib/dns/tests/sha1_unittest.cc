// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <stdint.h>
#include <string>

#include <dns/util/sha1.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;

namespace {
class Sha1Test : public ::testing::Test {
protected:
    Sha1Test() {}
};

// Tests copied from RFC 3174
TEST_F(Sha1Test, Test1) {
    SHA1Context sha;
    uint8_t digest[SHA1_HASHSIZE];
    uint8_t expected[SHA1_HASHSIZE] = {
        0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a, 0xba, 0x3e,
        0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c, 0x9c, 0xd0, 0xd8, 0x9d
    };

    EXPECT_EQ(0, SHA1Reset(&sha));
    EXPECT_EQ(0, SHA1Input(&sha, (const uint8_t *) "abc", 3));
    EXPECT_EQ(0, SHA1Result(&sha, digest));
    for (int i = 0; i < SHA1_HASHSIZE; i++) {
        EXPECT_EQ(digest[i], expected[i]);
    }
}

TEST_F(Sha1Test, Test2) {
    SHA1Context sha;
    string test("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    uint8_t digest[SHA1_HASHSIZE];
    uint8_t expected[SHA1_HASHSIZE] = {
        0x84, 0x98, 0x3e, 0x44, 0x1c, 0x3b, 0xd2, 0x6e, 0xba, 0xae,
        0x4a, 0xa1, 0xf9, 0x51, 0x29, 0xe5, 0xe5, 0x46, 0x70, 0xf1
    };

    EXPECT_EQ(0, SHA1Reset(&sha));
    EXPECT_EQ(0, SHA1Input(&sha, (const uint8_t *) test.c_str(),
                           test.length()));
    EXPECT_EQ(0, SHA1Result(&sha, digest));
    for (int i = 0; i < SHA1_HASHSIZE; i++) {
        EXPECT_EQ(digest[i], expected[i]);
    }
}

TEST_F(Sha1Test, Test3) {
    SHA1Context sha;
    uint8_t digest[SHA1_HASHSIZE];
    uint8_t expected[SHA1_HASHSIZE] = {
        0x34, 0xaa, 0x97, 0x3c, 0xd4, 0xc4, 0xda, 0xa4, 0xf6, 0x1e,
        0xeb, 0x2b, 0xdb, 0xad, 0x27, 0x31, 0x65, 0x34, 0x01, 0x6f
    };

    EXPECT_EQ(0, SHA1Reset(&sha));
    for (int i = 0; i < 1000000; i++) {
        EXPECT_EQ(0, SHA1Input(&sha, (const uint8_t *) "a", 1));
    }
    EXPECT_EQ(0, SHA1Result(&sha, digest));
    for (int i = 0; i < SHA1_HASHSIZE; i++) {
        EXPECT_EQ(digest[i], expected[i]);
    }
}

TEST_F(Sha1Test, Test4) {
    SHA1Context sha;
    string test("01234567012345670123456701234567"
                "01234567012345670123456701234567");
    uint8_t digest[SHA1_HASHSIZE];
    uint8_t expected[SHA1_HASHSIZE] = {
        0xde, 0xa3, 0x56, 0xa2, 0xcd, 0xdd, 0x90, 0xc7, 0xa7, 0xec,
        0xed, 0xc5, 0xeb, 0xb5, 0x63, 0x93, 0x4f, 0x46, 0x04, 0x52
    };

    EXPECT_EQ(0, SHA1Reset(&sha));
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(0, SHA1Input(&sha, (const uint8_t *) test.c_str(),
                               test.length()));
    }
    EXPECT_EQ(0, SHA1Result(&sha, digest));
    for (int i = 0; i < SHA1_HASHSIZE; i++) {
        EXPECT_EQ(digest[i], expected[i]);
    }
}
}

