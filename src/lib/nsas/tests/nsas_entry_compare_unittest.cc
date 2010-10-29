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
#include "nsas_entry_compare.h"
#include "nsas_test.h"

using namespace std;

namespace isc {
namespace nsas {

/// \brief Test Fixture Class
class NsasEntryCompareTest : public ::testing::Test {
};


// Test of the comparison
TEST_F(NsasEntryCompareTest, Compare) {

    // Construct a couple of different objects
    TestEntry entry1("test1", 42);
    TestEntry entry2("test1", 24);
    TestEntry entry3("test2", 42);

    // Create corresponding hash key objects
    HashKey key1(entry1.getName(), entry1.getClass());
    HashKey key2(entry2.getName(), entry2.getClass());
    HashKey key3(entry3.getName(), entry3.getClass());
    
    // Perform the comparison
    NsasEntryCompare<TestEntry> compare;

    EXPECT_TRUE(compare(&entry1, key1));
    EXPECT_FALSE(compare(&entry1, key2));
}

} // namespace nsas
} // namespace isc
