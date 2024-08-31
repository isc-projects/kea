// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/encode/encode.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <functional>

using namespace std;
using namespace isc;
using namespace isc::util::encode;

namespace {

/// @brief Defines a pointer to BaseNEncoder instances.
typedef boost::shared_ptr<BaseNEncoder> BaseNEncoderPtr;

/// @brief Defines an encoding function.
typedef std::function<std::string (const std::vector<uint8_t>&)> EncodeFunc;

/// @brief Defines a decoding function.
typedef std::function<void (const std::string&, std::vector<uint8_t>&)> DecodeFunc;

/// @brief Test fixture for exercising BaseNEncoder derivatives.
class EncodeDecodeTest : public ::testing::Test {
public:

    /// @brief Constructor
    ///
    /// @param encoder pointer to an encoder instance to use in tests
    /// @param encode_func encoding function to test
    /// @param decode_func decoding function to test
    EncodeDecodeTest(BaseNEncoderPtr encoder, EncodeFunc encode_func, DecodeFunc decode_func)
        : encoder_(encoder), encode_func_(encode_func), decode_func_(decode_func) {
        // From RFC4648 test vectors.
        valid_input_strings_.push_back("");
        valid_input_strings_.push_back("f");
        valid_input_strings_.push_back("fo");
        valid_input_strings_.push_back("foo");
        valid_input_strings_.push_back("foob");
        valid_input_strings_.push_back("fooba");
        valid_input_strings_.push_back("foobar");
    }

    /// @brief Destructor
    ~EncodeDecodeTest() = default;

    /// @brief Verifies encoding and decoding of test vectors from RFC4648
    ///
    /// Tests encoding and decoding functions using RFC supplied test vectors
    /// by:
    /// -# Encoding an input string and verifying the output against the expected
    /// encoded string.
    /// -# Decoding the encoded output and verifying it against the original input
    /// string
    /// -# If the algorithm is case sensitive, convert the encoded output string to
    /// lower case and recheck that it is decoded properly
    void encodeDecode() {
        ASSERT_EQ(expected_encoded_strings_.size(), valid_input_strings_.size());
        // For each valid input string:
        // -# encode it and verify the encoded result is as expected
        // -# decode the encoded result and verify it yields the original valid
        // input string
        // -# convert the encoded result to lower case and verify decoding
        // yields correct result.
        auto expected_output_str = expected_encoded_strings_.begin();
        for (auto const& input : valid_input_strings_) {
            std::vector<uint8_t>input_data(input.begin(), input.end());
            std::string output_str;
            ASSERT_NO_THROW_LOG(output_str = (encode_func_)(input_data));
            ASSERT_EQ(output_str, *expected_output_str) << "input string: [" <<  input << "]";
            ++expected_output_str;

            std::vector<uint8_t> decoded_output;
            ASSERT_NO_THROW_LOG((decode_func_)(output_str, decoded_output));
            ASSERT_EQ(decoded_output, input_data);

            if (!encoder_->isCaseSensitive()) {
                const std::string lower_case_str = boost::algorithm::to_lower_copy(output_str);
                decoded_output.clear();
                ASSERT_NO_THROW_LOG((decode_func_)(lower_case_str, decoded_output));
                ASSERT_EQ(decoded_output, input_data);
            }
        }
    }

    /// @brief Verifies that a list of encoded strings produces the expected
    /// decoded results.
    ///
    /// @param encoded_strings list of encoded strings to decode
    /// @param expected_strings list of expected decoded data as strings
    void decode(std::vector<std::string>& encoded_strings,
                std::vector<std::string>& expected_strings) {

        ASSERT_EQ(encoded_strings.size(), expected_strings.size());
        auto expected_str = expected_strings.begin();
        for (auto const& encoded_str : encoded_strings) {
            std::vector<uint8_t> decoded_output;
            ASSERT_NO_THROW_LOG((decode_func_)(encoded_str, decoded_output));
            std::string tmp(decoded_output.begin(), decoded_output.end());
            EXPECT_EQ(tmp, *expected_str);
            ++expected_str;
        }
    }

    /// @brief Verifies that a list of invalid encoded strings fail to
    /// decode appropriately
    ///
    /// @param encoded_strings list of invalid encoded strings
    void decodeInvalid(std::vector<std::string>& encoded_strings) {
        for (auto const& encoded_str : encoded_strings) {
            std::vector<uint8_t> decoded_output;
            EXPECT_THROW((decode_func_)(encoded_str, decoded_output), BadValue);
        }
    }

    /// @brief Verifies the integrity to encoder's digit set and bit table.
    void mapTest() {
        size_t num_digits = strlen(encoder_->getDigitSet());
        size_t whitespaces = 0;
        size_t valid_digits = 0;
        size_t bad_chars = 0;
        size_t pad_chars = 0;
        size_t upper_cased = 0;

        auto pad_char = encoder_->getPadChar();

        // Ensure the bit table is the proper size.
        ASSERT_EQ(encoder_->getBitsTable().size(), 256);

        // Iterate over the whole ASCII character set:
        // 1. Convert the ASCII value to its encoded binary bit value.
        // 2. Classify the value as whitespace, invalid, pad or valid
        // 3. For valid digits verify they exist in the digit set
        for (uint16_t ascii = 0; ascii < 256; ++ascii) {
            // Look up the binary data for the digit.
            // No value under 256 should throw.
            uint8_t bits;
            ASSERT_NO_THROW_LOG(bits = encoder_->digitToBits(ascii));

            // Classify the bits value we found.
            switch(bits) {
            case 0xee:
                ASSERT_TRUE(isspace(ascii));
                ++whitespaces;
                break;
            case 0xff:
                ++bad_chars;
                break;
            default: {
                if (pad_char && ascii == pad_char) {
                    ++pad_chars;
                } else {
                    // Verify the ascii value is in the digit set.
                    if (encoder_->isCaseSensitive()) {
                        ASSERT_TRUE(strchr(encoder_->getDigitSet(), ascii))
                                 << "ascii: " << std::hex << ascii;
                        ++valid_digits;
                    } else {
                        auto check_ascii = toupper(ascii);
                        ASSERT_TRUE(strchr(encoder_->getDigitSet(), check_ascii))
                                 << "ascii: " << std::hex << ascii
                                 << " check_ascii: " << std::hex << check_ascii;

                        if (check_ascii == ascii){
                            ++valid_digits;
                        } else {
                            ++upper_cased;
                        }
                    }
                }

                break;
            }}
        }

        // Verify that we see all valid digits.
        EXPECT_EQ(valid_digits, num_digits);

        // Verify that all of the ASCII values are accounted for.
        EXPECT_EQ((valid_digits + upper_cased + whitespaces + bad_chars + pad_chars), 256)
            << " : " << valid_digits
            << " + " << upper_cased
            << " + " << whitespaces
            << " + " << bad_chars
            << " + " << pad_chars;
    }

    BaseNEncoderPtr encoder_;
    EncodeFunc encode_func_;
    DecodeFunc decode_func_;
    std::vector<std::string> valid_input_strings_;
    std::vector<std::string> expected_encoded_strings_;
};


/// @brief Test Fixture for Base64 encoding
class Base64Test : public EncodeDecodeTest {
public:
    Base64Test()
     : EncodeDecodeTest(BaseNEncoderPtr(new Base64Encoder()), encodeBase64, decodeBase64) {
        // From RFC4648 test vectors.
        expected_encoded_strings_.push_back("");
        expected_encoded_strings_.push_back("Zg==");
        expected_encoded_strings_.push_back("Zm8=");
        expected_encoded_strings_.push_back("Zm9v");
        expected_encoded_strings_.push_back("Zm9vYg==");
        expected_encoded_strings_.push_back("Zm9vYmE=");
        expected_encoded_strings_.push_back("Zm9vYmFy");
    }
};

/// @brief Test Fixture for Base32Hex encoding
class Base32HexTest : public EncodeDecodeTest {
public:
    Base32HexTest()
     : EncodeDecodeTest(BaseNEncoderPtr(new Base32HexEncoder()), encodeBase32Hex, decodeBase32Hex) {
        // From RFC4648 test vectors.
        expected_encoded_strings_.push_back("");
        expected_encoded_strings_.push_back("CO======");
        expected_encoded_strings_.push_back("CPNG====");
        expected_encoded_strings_.push_back("CPNMU===");
        expected_encoded_strings_.push_back("CPNMUOG=");
        expected_encoded_strings_.push_back("CPNMUOJ1");
        expected_encoded_strings_.push_back("CPNMUOJ1E8======");
    }
};

/// @brief Test Fixture for Base16 encoding
class Base16Test : public EncodeDecodeTest {
public:
    Base16Test()
     : EncodeDecodeTest(BaseNEncoderPtr(new Base16Encoder()), encodeHex, decodeHex) {
        // From RFC4648 test vectors.
        expected_encoded_strings_.push_back("");
        expected_encoded_strings_.push_back("66");
        expected_encoded_strings_.push_back("666F");
        expected_encoded_strings_.push_back("666F6F");
        expected_encoded_strings_.push_back("666F6F62");
        expected_encoded_strings_.push_back("666F6F6261");
        expected_encoded_strings_.push_back("666F6F626172");
    }
};

// Verify RFC test vectors for Base64
TEST_F(Base64Test, validEncodeDecode) {
    encodeDecode();
}

// Verify whitespaces are handled properly in Base64
TEST_F(Base64Test, whiteSpace) {
    std::vector<std::string> encoded_strings = {
        "Zm 9v\tYmF\ny",
        "Zm9vYg==",
        "Zm9vYmE=\n",
        " Zm9vYmE=\n",
        " ",
        "\n\t"
    };

    std::vector<std::string> expected_strings = {
        "foobar",
        "foob",
        "fooba",
        "fooba",
        "",
        ""
    };

    decode(encoded_strings, expected_strings);
}

// Verify invalid encodings are handled properly in Base64
TEST_F(Base64Test, decodeInvalid) {
    std::vector<std::string> encoded_strings = {
        // Incomplete input.
        "Zm9vYmF",
        // Only up to 2 padding characters are allowed.
        "A===",
        "A= ==",
        // Intermediate padding isn't allowed.
        "YmE=YmE=",
        // Non canonical form isn't allowed.
        "Zm9=",
        "Zm==",
    };

    decodeInvalid(encoded_strings);
}

// Verify mappings for Base64
TEST_F(Base64Test, mappingCheck) {
    mapTest();
}

// Verify RFC test vectors for Base32Hex
TEST_F(Base32HexTest, validEncodeDecode) {
    encodeDecode();
}

// Verify whitespaces are handled properly in Base32Hex
TEST_F(Base32HexTest, whiteSpace) {
    std::vector<std::string> encoded_strings = {
        "CP NM\tUOG=",
        "CPNMU===\n",
        "  CP NM\tUOG=",
        " "
    };

    std::vector<std::string> expected_strings = {
        "foob",
        "foo",
        "foob",
        ""
    };

    decode(encoded_strings, expected_strings);
}

// Verify invalid encodings are handled properly in Base32Hex
TEST_F(Base32HexTest, decodeInvalid) {
    std::vector<std::string> encoded_strings = {
        // Incomplete input.
        "CPNMUOJ",
        // Invalid number of padding characters.
        "CPNMU0==",
        "CO0=====",
        "CO=======",
        // Intermediate padding isn't allowed.
        "CPNMUOG=CPNMUOG=",
        // Non canonical form isn't allowed.
        "0P======"
    };

    decodeInvalid(encoded_strings);
}

// Verify mappings for Base32Hex
TEST_F(Base32HexTest, mappingCheck) {
    mapTest();
}

// Verify RFC test vectors for Base16
TEST_F(Base16Test, validEncodeDecode) {
    encodeDecode();
}

// Verify whitespaces are handled properly in Base16
TEST_F(Base16Test, whiteSpace) {
    std::vector<std::string> encoded_strings = {
        "66 6F\t6F62",
        "66 6F6F\n",
        " 66\v\t6F6F62",
        " "
    };

    std::vector<std::string> expected_strings = {
        "foob",
        "foo",
        "foob",
        ""
    };

    decode(encoded_strings, expected_strings);
}

// Verify invalid encodings are handled properly in Base16
TEST_F(Base16Test, decodeInvalid) {
    std::vector<std::string> encoded_strings = {
        // Non hex digits should fail.
        "lx",
        // Encoded string must have an even number of characters.
        "dea"
    };

    decodeInvalid(encoded_strings);
}

// Verify mappings for Base16
TEST_F(Base16Test, mappingCheck) {
    mapTest();
}

}
