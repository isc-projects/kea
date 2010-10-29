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

#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>

#include "hash_key.h"

using namespace std;

namespace isc {
namespace nsas {

/// \brief Test Fixture Class
class HashKeyTest : public ::testing::Test {
};


// Test of the constructor
TEST_F(HashKeyTest, Constructor) {
    
    // Basic constructor
    string  test1("ABCDEF");
    HashKey key1(test1.c_str(), test1.size(), 1);
    EXPECT_EQ(key1.key, test1.c_str());
    EXPECT_EQ(key1.keylen, test1.size());
    EXPECT_EQ(key1.class_code, 1);

    // String constructor
    string  test2("uvwxyz");
    HashKey key2(test2, 2);
    EXPECT_EQ(key2.key, test2.c_str());
    EXPECT_EQ(key2.keylen, test2.size());
    EXPECT_EQ(key2.class_code, 2);
}

// Equality check
TEST_F(HashKeyTest, Equality) {
    string  test1("abcdef123");    // Simple string
    string  test2("abcdef123");    // Same key, different object
    string  test3("AbCdEf123");    // Same key, different case (unequal)
    string  test4("ABCDE123");     // Different key (almost same)
    string  test5("uvwxyz987");    // Different key

    EXPECT_TRUE(HashKey(test1, 1) == HashKey(test1, 1));   // Same key and class
    EXPECT_FALSE(HashKey(test1, 1) == HashKey(test1, 2));  // Different class

    EXPECT_TRUE(HashKey(test1, 2) == HashKey(test2, 2));   // Same value key/class
    EXPECT_FALSE(HashKey(test1, 2) == HashKey(test2, 3));

    EXPECT_TRUE(HashKey(test1, 3) == HashKey(test3, 3));   // Same key
    EXPECT_FALSE(HashKey(test1, 3) == HashKey(test3, 4));

    EXPECT_FALSE(HashKey(test1, 1) == HashKey(test4, 1));
    EXPECT_FALSE(HashKey(test1, 1) == HashKey(test5, 1));
}

} // namespace nsas
} // namespace isc
