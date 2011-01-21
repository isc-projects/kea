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

#include <config.h>

#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>

#include "../hash_key.h"
#include <dns/rrclass.h>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace nsas {

/// \brief Test Fixture Class
class HashKeyTest : public ::testing::Test {
};


// Test of the constructor
TEST_F(HashKeyTest, Constructor) {
    
    // Basic constructor
    string  test1("ABCDEF");
    HashKey key1(test1.c_str(), test1.size(), RRClass::IN());
    EXPECT_EQ(key1.key, test1.c_str());
    EXPECT_EQ(key1.keylen, test1.size());
    EXPECT_EQ(key1.class_code, RRClass::IN());

    // String constructor
    string  test2("uvwxyz");
    HashKey key2(test2, RRClass::CH());
    EXPECT_EQ(key2.key, test2.c_str());
    EXPECT_EQ(key2.keylen, test2.size());
    EXPECT_EQ(key2.class_code, RRClass::CH());
}

// Equality check
TEST_F(HashKeyTest, Equality) {
    string  test1("abcdef123");    // Simple string
    string  test2("abcdef123");    // Same key, different object
    string  test3("AbCdEf123");    // Same key, different case (unequal)
    string  test4("ABCDE123");     // Different key (almost same)
    string  test5("uvwxyz987");    // Different key

    EXPECT_TRUE(HashKey(test1, RRClass::IN()) == HashKey(test1,
        RRClass::IN()));   // Same key and class
    EXPECT_FALSE(HashKey(test1, RRClass::IN()) == HashKey(test1,
        RRClass::CH()));  // Different class

    EXPECT_TRUE(HashKey(test1, RRClass::CH()) == HashKey(test2,
        RRClass::CH()));   // Same value key/class
    EXPECT_FALSE(HashKey(test1, RRClass::CH()) == HashKey(test2,
        RRClass::IN()));

    EXPECT_TRUE(HashKey(test1, RRClass::HS()) == HashKey(test3,
        RRClass::HS()));   // Same key
    EXPECT_FALSE(HashKey(test1, RRClass::HS()) == HashKey(test3,
        RRClass::IN()));

    EXPECT_FALSE(HashKey(test1, RRClass::IN()) == HashKey(test4,
        RRClass::IN()));
    EXPECT_FALSE(HashKey(test1, RRClass::IN()) == HashKey(test5,
        RRClass::IN()));
}

} // namespace nsas
} // namespace isc
