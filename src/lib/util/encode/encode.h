// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ENCODE_H
#define ENCODE_H

#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace util {
namespace encode {

/// @brief Class for encoding and decoding binary data using an algorithm
/// described in RFC 4648.
class BaseNEncoder {
public:

    /// @brief Constructor
    ///
    /// @param algorithm name of the algorithm, used for logging
    /// @param digit_set set of digits (i.e. alphabet) used for encoding
    /// @param bits_table table to translate digits to data used during decoding
    /// @param bits_per_digit number of data bits represented by a digit
    /// @param digits_per_group number of digits contained in a group
    /// @param pad_char character used for padding out to group size (0 means no
    /// padding)
    /// @param max_pad maximum number of pad characters in a group
    /// @param case_sensitive indicates if the algorithm's digit set is
    /// case sensitive
    BaseNEncoder(const std::string& algorithm,
                 const char* digit_set,
                 const std::vector<uint8_t>& bits_table,
                 size_t bits_per_digit,
                 size_t digits_per_group,
                 const char pad_char,
                 size_t max_pad,
                 bool case_sensitive);

    /// @brief Destructor
    virtual ~BaseNEncoder() = default;

    /// @brief Encodes binary data using the encoder's algorithm
    ///
    /// @param input binary data to encode
    ///
    /// @return resultant encoded data string
    /// @throw BadValue if an error occurs during encoding
    std::string encode(const std::vector<uint8_t>& input);

    /// @brief Decodes an encoded string using the encoder's algorithm
    ///
    /// @param encoded_str encoded string to decode
    /// @param[out] output vector into which the decoded data is stored
    ///
    /// @throw BadValue if an error occurs during decoding
    void decode(const std::string& encoded_str, std::vector<uint8_t>& output);

    /// @brief Translate a byte of binary data into the appropriate algorithm digit
    ///
    /// @param bits binary value to translate
    ///
    /// @return char containing the digit corresponding to the binary value
    /// @throw BadValue if the bits value is out of range
    char bitsToDigit(uint8_t bits);

    /// @brief Translate a digit into the appropriate algorithm bit value
    ///
    /// Function maps all 256 ASCII chars to their corresponding algorithm-specific
    /// data value.  A data value of 0xee marks a char as whitespace, 0xff marks a
    /// char is invalid.
    ///
    /// @param digit the algorithm digit to translate
    ///
    /// @return byte containing the binary value corresponding to the digit
    uint8_t digitToBits(uint8_t digit);

    /// @brief Get the algorithm name
    ///
    /// @return string containing the algorithm name
    std::string getAlgorithm() const {
        return (algorithm_);
    }

    /// @brief Get the digit set
    ///
    /// @return string containing the set of digits
    const char* getDigitSet() const {
        return (digit_set_);
    }

    /// @brief Get the digit lookup table
    ///
    /// @return vector containing the lookup table
    const std::vector<uint8_t>& getBitsTable() const {
        return (bits_table_);
    }

    /// @brief Get the number of data bits represented by a digit
    ///
    /// @return number of data bits per digit
    size_t getBitsPerDigit() {
        return (bits_per_digit_);
    }

    /// @brief Get the number of digits contained in a group
    ///
    /// @return number of digits per group
    size_t getDigitsPerGroup() const {
        return (digits_per_group_);
    }

    /// @brief Get the character used for padding out to group size (0 means no padding)
    ///
    /// @return Character used as a pad byte
    uint8_t getPadChar() const {
        return (pad_char_);
    }

    /// @brief Get the maximum number of pad characters in a group
    ///
    /// @return Maximum number of pad characters
    size_t getMaxPad() {
        return (max_pad_);
    }

    /// @brief Get the maxium index value of the digit set
    ///
    /// @return Maxium index value of the digit set
    size_t getMaxBitsToDigit() {
        return (max_bits_to_digit_);
    }

    /// @brief Get the maxium index value of the algorithm bit table
    ///
    /// @return Maxium index value of the algorithm bit table
    size_t getMaxDigitToBits() {
        return (max_digit_to_bits_);
    }

    /// @brief Indicates whether or not the algorithm's digit set
    /// is case-sensitive.
    ///
    /// @return true if the digit set is case-sensitive, false otherwise
    bool isCaseSensitive() {
        return (case_sensitive_);
    }

protected:
    /// @brief Name of the algorithm, used for logging
    std::string algorithm_;

    /// @brief Set of digits (i.e. alphabet) used for encoding
    const char* digit_set_;

    /// @brief Table to translate digits to data used during decoding
    ///
    /// The table must map all 256 ASCII chars to their corresponding
    /// algorithm-specific data value.  A data value of 0xee marks
    /// a char as whitespace, 0xff marks a char is invalid
    std::vector<uint8_t>bits_table_;

    /// @brief Number of data bits represented by a digit
    size_t bits_per_digit_;

    /// @brief Number of digits contained in a group
    size_t digits_per_group_;

    /// @brief Character used for padding out to group size (0 means no padding)
    const char pad_char_;

    /// @brief Maximum number of pad characters in a group
    size_t max_pad_;

    /// @brief Indicates whether or not the algorithm's digit set is case-sensitive
    bool case_sensitive_;

    /// @brief Maxium index value of the digit set
    size_t max_bits_to_digit_;

    /// @brief Maxium index value of the algorithm bit table
    size_t max_digit_to_bits_;
};

/// @brief Class for encoding and decoding binary data using Base64
/// as described in RFC 4648.
class Base64Encoder : public BaseNEncoder {
public:
    /// @brief Set of digits used for encoding in Base64
    static const char* DIGIT_SET;

    /// @brief Table that maps Base64 digits to their binary data value
    static const std::vector<uint8_t> BITS_TABLE;

    /// @brief Constructor
    Base64Encoder()
     : BaseNEncoder("base64", DIGIT_SET, BITS_TABLE, 6, 4, '=', 2, true) {
    }

    /// @brief Destructor
    ~Base64Encoder() = default;
};

/// @brief Class for encoding and decoding binary data using Base32Hex
/// as described in RFC 4648.
class Base32HexEncoder : public BaseNEncoder {
public:
    /// @brief Set of digits used for encoding in Base32Hex
    static const char* DIGIT_SET;

    /// @brief Table that maps Base32Hex digits to their binary data value
    static const std::vector<uint8_t> BITS_TABLE;

    /// @brief Constructor
    Base32HexEncoder()
     : BaseNEncoder("base32Hex", DIGIT_SET, BITS_TABLE, 5, 8, '=', 6, false) {
    }

    /// @brief Destructor
    ~Base32HexEncoder() = default;
};

/// @brief Class for encoding and decoding binary data using Base16 (aka Hex)
/// as described in RFC 4648.
class Base16Encoder : public BaseNEncoder {
public:
    /// @brief Set of digits used for encoding in Base16
    static const char* DIGIT_SET;

    /// @brief Table that maps Base16 digits to their binary data value
    static const std::vector<uint8_t> BITS_TABLE;

    /// @brief Constructor
    Base16Encoder()
     : BaseNEncoder("base16", DIGIT_SET, BITS_TABLE, 4, 2, '=', 0, false) {
    }

    /// @brief Destructor
    ~Base16Encoder() = default;
};

/// @brief Encode binary data in the base32-hex format.
///
/// @param binary vector object storing the data to be encoded.
/// @return string containing the base32-hex encoded value.
std::string encodeBase32Hex(const std::vector<uint8_t>& binary);

/// @brief Decode a base32-hex encoded string into binary data.
///
/// @param encoded_str string containing a base32-hex encoded value.
/// @param[out] output vector into which the decoded binary data is stored.
///
/// @throw BadValue if the input string is invalid.
void decodeBase32Hex(const std::string& encoded_str, std::vector<uint8_t>& output);

/// @brief Encode binary data in the base64 format.
///
/// @param binary vector object storing the data to be encoded.
/// @return string containing the base64 encoded value.
std::string encodeBase64(const std::vector<uint8_t>& binary);

/// @brief Decode a base64 encoded string into binary data.
///
/// @param encoded_str string containing a base64 encoded value.
/// @param[out] output vector into which the decoded binary data is stored.
///
/// @throw BadValue if the input string is invalid.
void decodeBase64(const std::string& encoded_str, std::vector<uint8_t>& output);

/// @brief Encode binary data in the base16 format.
///
/// @param binary vector object containing the data to be encoded.
/// @return string containing the base16 encoded value.
std::string encodeHex(const std::vector<uint8_t>& binary);

/// @brief Decode a base16 encoded string into binary data.
///
/// @param encoded_str string containing a base16 encoded value.
/// @param[out] output vector into which the decoded binary data is stored.
///
/// @throw BadValue if the input string is invalid.
void decodeHex(const std::string& encoded_str, std::vector<uint8_t>& output);

/// @brief Encode in hexadecimal inline.
///
/// @param value the value to encode.
///
/// @return 0x followed by the value encoded in hex.
inline std::string toHex(std::string value) {
    std::vector<uint8_t> bin(value.begin(), value.end());
    return ("0x" + encodeHex(bin));
}

} // namespace encode
} // namespace util
} // namespace isc

#endif  // ENCODE_H
