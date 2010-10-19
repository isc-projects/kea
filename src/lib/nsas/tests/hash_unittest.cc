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

#include "hash.h"

using namespace std;

namespace isc {
namespace nsas {


/// \brief Text Fixture Class
class HashTest : public ::testing::Test {
};


// Test of the constructor
TEST_F(HashTest, Constructor) {
    
    // Default constructor
    Hash hash1(1009, 250);
    EXPECT_EQ(1009, hash1.tableSize());
    EXPECT_EQ(250, hash1.maxKeyLength());
}

// Test of the hash algorithm.  Without duplicating the code for the algorithm
// here, testing is a bit awkward.  So the tests will check that a series of
// names get hashed to different values.  (Choosing a 1009 element array should
// give minimal overlap; we'll allow for a maximum of 2 collisions with 50
// similar names.  If there are more, perhaps the algorithm is at fault.

TEST_F(HashTest, Algorithm) {

    const int size = 1009;      // Size of the hash table
    Hash hash(size, 255, false);// Hashing algorithm object with seed
                                // randomisation disabled
    string base = "alphabeta";  // Base of the names to behashed
    vector<uint32_t> values;    // Results stored here

    // Generate hash values
    for (int i = 0; i < 50; ++i) {
        string name = base + boost::lexical_cast<string>(i);
        uint32_t hashval = hash(name.c_str(), name.size());
        EXPECT_LT(hashval, size);
        values.push_back(hashval);
    }
    uint32_t cursize = values.size();

    // Check to see if they are unique.  Do this by sorting the values into
    // ascending order, removing duplicates, and checking the size again.
    //
    // Note that unique only shifts elements around - it does not remove non-
    // unique values, so it does change the size of the array.  The call to
    // erase removes the elements left at the end of the array.
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    uint32_t newsize = values.size();
    EXPECT_GE(newsize + 2, cursize);
}

// Test the case mapping function.

TEST_F(HashTest, CaseMapping) {

    Hash hash(1009, 255);
    
    // Check all unsigned characters
    for (int i = 0; i < 255; ++i) {
        if ((i >= 'A') && (i <= 'Z')) {
            EXPECT_EQ(static_cast<unsigned char>(i - 'A' + 'a'),
                hash.mapLower((unsigned char)i));
        }
        else {
            EXPECT_EQ(i, hash.mapLower(i));
        }
    }
}

// Test the mapping of mixed-case names

TEST_F(HashTest, MixedCase) {

    std::string test1 = "example1234.co.uk.";
    std::string test2 = "EXAmple1234.co.uk.";

    Hash hash(1009, 255);

    // Case not ignored, hashes should be different
    uint32_t value1 = hash(test1.c_str(), test1.size(), false);
    uint32_t value2 = hash(test2.c_str(), test2.size(), false);
    EXPECT_NE(value1, value2);

    // Case ignored, hashes should be the same
    uint32_t value3 = hash(test1.c_str(), test1.size(), true);
    uint32_t value4 = hash(test2.c_str(), test2.size(), true);
    EXPECT_EQ(value3, value4);

    // Check the default setting.
    uint32_t value5 = hash(test1.c_str(), test1.size());
    uint32_t value6 = hash(test2.c_str(), test2.size());
    EXPECT_EQ(value5, value6);

    // ... and just for good measure
    EXPECT_EQ(value1, value3);
    EXPECT_EQ(value1, value5);
}

// Test that the code performs when the length of the key is excessive
TEST_F(HashTest, Overlong) {

    // String 1 is a suitable prefix, string 2 is the same prefix plus 4096
    // repetions of the character 'x'.
    std::string string1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ012345";
    std::string string2 = string1 + string(4096, 'x');

    Hash hash(1009, string1.size());

    // Do two hashes
    uint32_t value1 = hash(string1.c_str(), string1.size());
    uint32_t value2 = hash(string2.c_str(), string2.size());
    EXPECT_EQ(value1, value2);
}

} // namespace nsas
} // namespace isc
