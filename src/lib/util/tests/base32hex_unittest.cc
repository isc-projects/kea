// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>

#include <cctype>
#include <string>
#include <utility>
#include <vector>

#include <exceptions/exceptions.h>

#include <util/encode/base32hex.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::util::encode;

namespace {

typedef pair<string, string> StringPair;

class Base32HexTest : public ::testing::Test {
protected:
    Base32HexTest() : encoding_chars("0123456789ABCDEFGHIJKLMNOPQRSTUV=") {
        // test vectors from RFC4648
        test_sequence.push_back(StringPair("", ""));
        test_sequence.push_back(StringPair("f", "CO======"));
        test_sequence.push_back(StringPair("fo", "CPNG===="));
        test_sequence.push_back(StringPair("foo", "CPNMU==="));
        test_sequence.push_back(StringPair("foob", "CPNMUOG="));
        test_sequence.push_back(StringPair("fooba", "CPNMUOJ1"));
        test_sequence.push_back(StringPair("foobar", "CPNMUOJ1E8======"));

        // the same data, encoded using lower case chars (testable only
        // for the decode side)
        test_sequence_lower.push_back(StringPair("f", "co======"));
        test_sequence_lower.push_back(StringPair("fo", "cpng===="));
        test_sequence_lower.push_back(StringPair("foo", "cpnmu==="));
        test_sequence_lower.push_back(StringPair("foob", "cpnmuog="));
        test_sequence_lower.push_back(StringPair("fooba", "cpnmuoj1"));
        test_sequence_lower.push_back(StringPair("foobar",
                                                 "cpnmuoj1e8======"));
    }
    vector<StringPair> test_sequence;
    vector<StringPair> test_sequence_lower;
    vector<uint8_t> decoded_data;
    const string encoding_chars;
};

void
decodeCheck(const string& input_string, vector<uint8_t>& output,
            const string& expected)
{
    decodeBase32Hex(input_string, output);
    EXPECT_EQ(expected, string(output.begin(), output.end()));
}

TEST_F(Base32HexTest, decode) {
    for (vector<StringPair>::const_iterator it = test_sequence.begin();
         it != test_sequence.end();
         ++it) {
        decodeCheck((*it).second, decoded_data, (*it).first);
    }

    // whitespace should be allowed
    decodeCheck("CP NM\tUOG=", decoded_data, "foob");
    decodeCheck("CPNMU===\n", decoded_data, "foo");
    decodeCheck("  CP NM\tUOG=", decoded_data, "foob");
    decodeCheck(" ", decoded_data, "");

    // Incomplete input
    EXPECT_THROW(decodeBase32Hex("CPNMUOJ", decoded_data), BadValue);

    // invalid number of padding characters
    EXPECT_THROW(decodeBase32Hex("CPNMU0==", decoded_data), BadValue);
    EXPECT_THROW(decodeBase32Hex("CO0=====", decoded_data), BadValue);
    EXPECT_THROW(decodeBase32Hex("CO=======", decoded_data), // too many ='s
                 BadValue);

    // intermediate padding isn't allowed
    EXPECT_THROW(decodeBase32Hex("CPNMUOG=CPNMUOG=", decoded_data), BadValue);

    // Non canonical form isn't allowed.
    // P => 25(11001), so the padding byte would be 01000000
    EXPECT_THROW(decodeBase32Hex("0P======", decoded_data), BadValue);
}

TEST_F(Base32HexTest, decodeLower) {
    for (vector<StringPair>::const_iterator it = test_sequence_lower.begin();
         it != test_sequence_lower.end();
         ++it) {
        decodeCheck((*it).second, decoded_data, (*it).first);
    }
}

TEST_F(Base32HexTest, encode) {
    for (vector<StringPair>::const_iterator it = test_sequence.begin();
         it != test_sequence.end();
         ++it) {
        decoded_data.assign((*it).first.begin(), (*it).first.end());
        EXPECT_EQ((*it).second, encodeBase32Hex(decoded_data));
    }
}

// For Base32Hex we use handmade mappings, so it's prudent to test the
// entire mapping table explicitly.
TEST_F(Base32HexTest, decodeMap) {
    string input(8, '0');       // input placeholder

    // We're going to populate an input string with only the last character
    // not equal to the zero character ('0') for each valid base32hex encoding
    // character.  Decoding that input should result in a data stream with
    // the last byte equal to the numeric value represented by the that
    // character.  For example, we'll generate and confirm the following:
    // "00000000" => should be 0 (as a 40bit integer)
    // "00000001" => should be 1 (as a 40bit integer)
    // ...
    // "0000000V" => should be 31 (as a 40bit integer)
    // We also check the use of an invalid character for the last character
    // surely fails. '=' should be accepted as a valid padding in this
    // context; space characters shouldn't be allowed in this context.

    for (int i = 0; i < 256; ++i) {
        input[7] = i;

        const char ch = toupper(i);
        const size_t pos = encoding_chars.find(ch);
        if (pos == string::npos) {
            EXPECT_THROW(decodeBase32Hex(input, decoded_data), BadValue);
        } else {
            decodeBase32Hex(input, decoded_data);
            if (ch == '=') {
                EXPECT_EQ(4, decoded_data.size());
            } else {
                EXPECT_EQ(5, decoded_data.size());
                EXPECT_EQ(pos, decoded_data[4]);
            }
        }
    }
}

TEST_F(Base32HexTest, encodeMap) {
    for (uint8_t i = 0; i < 32; ++i) {
        decoded_data.assign(4, 0);
        decoded_data.push_back(i);
        EXPECT_EQ(encoding_chars[i], encodeBase32Hex(decoded_data)[7]);
    }
}

}
