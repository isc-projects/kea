// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DNS_RDATA_CHARSTRING_H
#define DNS_RDATA_CHARSTRING_H 1

#include <dns/master_lexer.h>

#include <string>
#include <vector>
#include <stdint.h>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {

/// \brief Type for DNS character string.
///
/// A character string can contain any unsigned 8-bit value, so this cannot
/// be the bare char basis.
typedef std::vector<uint8_t> CharString;

/// \brief Convert a DNS character-string into corresponding binary data.
///
/// This helper function takes a string object that is expected to be a
/// textual representation of a valid DNS character-string, and dumps
/// the corresponding binary sequence in the given placeholder (passed
/// via the \c result parameter).  It handles escape notations of
/// character-strings with a backslash ('\'), and checks the length
/// restriction.
///
/// \throw CharStringTooLong The resulting binary data are too large for a
/// valid character-string.
/// \throw InvalidRdataText Other syntax errors.
///
/// \brief str_region A string that represents a character-string.
/// \brief result A placeholder vector where the resulting data are to be
/// stored.  Expected to be empty, but it's not checked.
void strToCharString(const MasterToken::StringRegion& str_region,
                     CharString& result);

/// \brief Convert a CharString into a textual DNS character-string.
///
/// This method converts a binary 8-bit representation of a DNS
/// character string into a textual string representation, escaping any
/// special characters in the process. For example, characters like
/// double-quotes, semi-colon and backspace are prefixed with backspace
/// character, and characters not in the printable range of [0x20, 0x7e]
/// (inclusive) are converted to the \xxx 3-digit decimal
/// representation.
///
/// \param char_string The \c CharString to convert.
/// \return A string representation of \c char_string.
std::string charStringToString(const CharString& char_string);

} // namespace detail
} // namespace generic
} // namespace rdata
} // namespace dns
} // namespace isc
#endif  // DNS_RDATA_CHARSTRING_H

// Local Variables:
// mode: c++
// End:
