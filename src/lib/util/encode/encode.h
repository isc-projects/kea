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

/// @brief Encode binary data in the base32-hex format.
///
/// @param binary vector object storing the data to be encoded.
/// @return string containing the base32-hex encoded value.
std::string encodeBase32Hex(const std::vector<uint8_t>& binary);

/// @brief Decode a base32-hex encoded string into binary data.
///
/// @param encoded_str string containing a base32-hex encoded value.
/// @param[out] output vector into which the decoded binary data is stored.
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
/// @throw BadValue if the input string is invalid.
void decodeHex(const std::string& encoded_str, std::vector<uint8_t>& output);

/// @brief Encode in hexadecimal inline
///
/// @param value the value to encode
/// @return 0x followed by the value encoded in hexa
inline std::string toHex(std::string value) {
    std::vector<uint8_t> bin(value.begin(), value.end());
    return ("0x" + encodeHex(bin));
}

} // namespace encode
} // namespace util
} // namespace isc

#endif  // ENCODE_H
