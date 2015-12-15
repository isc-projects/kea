// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>
#include <utility>
#include <vector>

#include <exceptions/exceptions.h>

#include <util/encode/base64.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::util::encode;

namespace {

typedef pair<string, string> StringPair;

class Base64Test : public ::testing::Test {
protected:
    Base64Test()
    {
        // test vectors from RFC4648
        test_sequence.push_back(StringPair("", ""));
        test_sequence.push_back(StringPair("f", "Zg=="));
        test_sequence.push_back(StringPair("fo", "Zm8="));
        test_sequence.push_back(StringPair("foo", "Zm9v"));
        test_sequence.push_back(StringPair("foob", "Zm9vYg=="));
        test_sequence.push_back(StringPair("fooba", "Zm9vYmE="));
        test_sequence.push_back(StringPair("foobar", "Zm9vYmFy"));
    }
    vector<StringPair> test_sequence;
    vector<uint8_t> decoded_data;
};

void
decodeCheck(const string& input_string, vector<uint8_t>& output,
            const string& expected)
{
    decodeBase64(input_string, output);
    EXPECT_EQ(expected, string(output.begin(), output.end()));
}

TEST_F(Base64Test, decode) {
    for (vector<StringPair>::const_iterator it = test_sequence.begin();
         it != test_sequence.end();
         ++it) {
        decodeCheck((*it).second, decoded_data, (*it).first);
    }

    // whitespace should be allowed
    decodeCheck("Zm 9v\tYmF\ny", decoded_data, "foobar");
    decodeCheck("Zm9vYg==", decoded_data, "foob");
    decodeCheck("Zm9vYmE=\n", decoded_data, "fooba");
    decodeCheck(" Zm9vYmE=\n", decoded_data, "fooba");
    decodeCheck(" ", decoded_data, "");
    decodeCheck("\n\t", decoded_data, "");

    // incomplete input
    EXPECT_THROW(decodeBase64("Zm9vYmF", decoded_data), BadValue);

    // only up to 2 padding characters are allowed
    EXPECT_THROW(decodeBase64("A===", decoded_data), BadValue);
    EXPECT_THROW(decodeBase64("A= ==", decoded_data), BadValue);

    // intermediate padding isn't allowed
    EXPECT_THROW(decodeBase64("YmE=YmE=", decoded_data), BadValue);

    // Non canonical form isn't allowed.
    // Z => 25(011001), m => 38(100110), 9 => 60(111101), so the padding
    // byte would be 0100 0000.
    EXPECT_THROW(decodeBase64("Zm9=", decoded_data), BadValue);
    // Same for the 1st padding byte.  This would make it 01100000.
    EXPECT_THROW(decodeBase64("Zm==", decoded_data), BadValue);
}

TEST_F(Base64Test, encode) {
    for (vector<StringPair>::const_iterator it = test_sequence.begin();
         it != test_sequence.end();
         ++it) {
        decoded_data.assign((*it).first.begin(), (*it).first.end());
        EXPECT_EQ((*it).second, encodeBase64(decoded_data));
    }
}
}
