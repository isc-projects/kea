// Copyright (C) 2009-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HEX_H
#define HEX_H 1

#include <stdint.h>
#include <string>
#include <vector>

//
// Note: this helper module isn't specific to the DNS protocol per se.
// We should probably move this to somewhere else, possibly in some common
// utility area.
//

namespace isc {
namespace util {
namespace encode {
/// \brief Encode binary data in the base16 ('hex') format.
///
/// The underlying implementation is shared with \c encodeBase64, and most of
/// the description except the format (base16) equally applies.
/// Another notable exception is that the base16 encoding doesn't require
/// padding, so padding related considerations and the notion of canonical
/// encoding don't apply.
///
/// \param binary A vector object storing the data to be encoded. 
/// \return A newly created string that stores base16 encoded value for
/// binary.
std::string encodeHex(const std::vector<uint8_t>& binary);

/// \brief Decode a text encoded in the base16 ('hex') format into the
/// original %data.
///
/// The underlying implementation is shared with \c decodeBase64, and most
/// of the description except the format (base16) equally applies.
/// Another notable exception is that the base16 encoding doesn't require
/// padding, so padding related considerations and the notion of canonical
/// encoding don't apply.
///
/// \param input A text encoded in the base16 format.
/// \param result A vector in which the decoded %data is to be stored.
void decodeHex(const std::string& input, std::vector<uint8_t>& result);

/// \brief Encode in hexadecimal inline
///
/// \param value the value to encode
/// \return 0x followed by the value encoded in hexa
inline std::string toHex(std::string value) {
    std::vector<uint8_t> bin(value.begin(), value.end());
    return ("0x" + encodeHex(bin));
}

} // namespace encode
} // namespace util
} // namespace isc

#endif  // HEX_H

// Local Variables: 
// mode: c++
// End: 
