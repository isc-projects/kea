// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE32HEX_H
#define BASE32HEX_H 1

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

/// \brief Encode binary data in the base32hex format.
///
/// The underlying implementation is shared with \c encodeBase64, and all
/// description except the format (base32hex) equally applies.
///
/// Note: the encoding format is base32hex, not base32.
///
/// \param binary A vector object storing the data to be encoded. 
/// \return A newly created string that stores base32hex encoded value for
/// binary.
std::string encodeBase32Hex(const std::vector<uint8_t>& binary);

/// \brief Decode a text encoded in the base32hex format into the
/// original %data.
///
/// The underlying implementation is shared with \c decodeBase64, and all
/// description except the format (base32hex) equally applies.
///
/// Note: the encoding format is base32hex, not base32.
///
/// \param input A text encoded in the base32hex format.
/// \param result A vector in which the decoded %data is to be stored.
void decodeBase32Hex(const std::string& input, std::vector<uint8_t>& result);

} // namespace encode 
} // namespace util
} // namespace isc

#endif  // BASE32HEX_H

// Local Variables:
// mode: c++
// End:
