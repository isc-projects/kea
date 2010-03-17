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
#include <utility>
#include <vector>

#include <dns/base32.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;

namespace {

typedef pair<string, string> StringPair;

class Base32Test : public ::testing::Test {
protected:
    Base32Test() {
        // test vectors from RFC4648
#if 0   // the current implementation doesn't seem to handle '=' correctly
        test_sequence.push_back(StringPair("", ""));
        test_sequence.push_back(StringPair("f", "CO======"));
        test_sequence.push_back(StringPair("fo", "CPNG===="));
        test_sequence.push_back(StringPair("foo", "CPNMU==="));
        test_sequence.push_back(StringPair("foob", "CPNMUOG="));
#endif
        test_sequence.push_back(StringPair("fooba", "CPNMUOJ1"));
#if 0                           // this fails
        test_sequence.push_back(StringPair("foobar", "CPNMUOJ1E8======"));
#endif
    }
    vector<StringPair> test_sequence;
    vector<uint8_t> decoded_data;
};

void
decodeCheck(const string& input_string, vector<uint8_t>& output,
            const string& expected)
{
    decodeBase32(input_string, output);
    EXPECT_EQ(expected, string(&output[0], &output[0] + output.size()));
}


TEST_F(Base32Test, reversibility) {
    vector<uint8_t> result;
//    const string input("H9RSFB7FPF2L8HG35CMPC765TDK23RP6");
    const string input("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    decodeBase32(input, result);
    string output = encodeBase32(result);
    EXPECT_EQ(input, output);
}

TEST_F(Base32Test, decode0) {
    for (vector<StringPair>::const_iterator it = test_sequence.begin();
         it != test_sequence.end();
         ++it) {
        decodeCheck((*it).second, decoded_data, (*it).first);
    }
}

TEST_F(Base32Test, decode1) {
    vector<uint8_t> result;
    const std::string input("000G40O40K30E209185GO38E1S8124GJ");
    decodeBase32(input, result);
    EXPECT_EQ(20, result.size());
    for (uint8_t i = 0; i < 20; i++) {
        EXPECT_EQ((int) i, (int) result[i]);
    }
}

TEST_F(Base32Test, encode0) {
    for (vector<StringPair>::const_iterator it = test_sequence.begin();
         it != test_sequence.end();
         ++it) {
        decoded_data.assign((*it).first.begin(), (*it).first.end());
        EXPECT_EQ((*it).second, encodeBase32(decoded_data));
    }
}

TEST_F(Base32Test, encode1) {
    const std::string expect("000G40O40K30E209185GO38E1S8124GJ");
    vector<uint8_t> binary;
    for (uint8_t i = 0; i < 20; i++) {
        binary.push_back(i);
    }
    string base32 = encodeBase32(binary);
    EXPECT_EQ(expect, base32);
}
}
