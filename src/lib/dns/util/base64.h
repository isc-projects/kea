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

#ifndef __BASE64_H
#define __BASE64_H 1

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

/// \brief Encode binary data in the base64 format.
///
/// This function returns a new \c std::string object that stores a text
/// encoded in the base64 format for the given \c binary %data.
/// The resulting string will be a valid, canonical form of base64
/// representation as specified in RFC4648.
///
/// If memory allocation for the returned string fails, a corresponding
/// standard exception will be thrown.  This function never throws exceptions
/// otherwise.
///
/// \param binary A vector object storing the data to be encoded. 
/// \return A newly created string that stores base64 encoded value for binary.
std::string encodeBase64(const std::vector<uint8_t>& binary);

/// \brief Decode a text encoded in the base64 format into the original %data.
///
/// The \c input argument must be a valid string represented in the base64
/// format as specified in RFC4648.  Space characters (spaces, tabs, newlines)
/// can be included in \c input and will be ignored.  Without spaces, the
/// length of string must be a multiple of 4 bytes with necessary paddings.
/// Also it must be encoded using the canonical encoding (see RFC4648).
/// If any of these conditions is not met, an exception of class
/// \c isc::BadValue will be thrown.
///
/// If \c result doesn't have sufficient capacity to store all decoded %data
/// and memory allocation fails, a corresponding standard exception will be
/// thrown.  If the caller knows the necessary length (which can in theory
/// be calculated from the input string), this situation can be avoided by
/// reserving sufficient space for \c result beforehand.
///
/// Any existing %data in \c result will be removed.  This is the case in some
/// of the cases where an exception is thrown; that is, this function only
/// provides the basic exception guarantee.
///
/// \param input A text encoded in the base64 format.
/// \param result A vector in which the decoded %data is to be stored.
void decodeBase64(const std::string& input, std::vector<uint8_t>& result);
}
}

#endif  // __BASE64_H

// Local Variables: 
// mode: c++
// End: 
