// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __BASE32HEX_H
#define __BASE32HEX_H 1

#include <stdint.h>
#include <string>
#include <vector>

//
// Note: this helper module isn't specific to the DNS protocol per se.
// We should probably move this to somewhere else, possibly in some common
// utility area.
//

namespace isc {
namespace dns {

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
}
}

#endif  // __BASE32HEX_H

// Local Variables:
// mode: c++
// End:
