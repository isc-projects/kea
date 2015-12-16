// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DNS_RDATA_CHARSTRING_H
#define DNS_RDATA_CHARSTRING_H 1

#include <dns/master_lexer.h>

#include <string>
#include <vector>
#include <algorithm>
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

/// \brief Type for DNS character string without the length prefix.
typedef std::vector<uint8_t> CharStringData;

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
void stringToCharString(const MasterToken::StringRegion& str_region,
                        CharString& result);

/// \brief Convert a DNS character-string into corresponding binary data.
///
/// This method functions similar to \c stringToCharString() except it
/// does not include the 1-octet length prefix in the \c result, and the
/// result is not limited to MAX_CHARSTRING_LEN octets.
///
/// \throw InvalidRdataText Upon syntax errors.
///
/// \brief str_region A string that represents a character-string.
/// \brief result A placeholder vector where the resulting data are to be
/// stored.  Expected to be empty, but it's not checked.
void stringToCharStringData(const MasterToken::StringRegion& str_region,
                            CharStringData& result);

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

/// \brief Convert a CharStringData into a textual DNS character-string.
///
/// Reverse of \c stringToCharStringData(). See \c stringToCharString()
/// vs. \c stringToCharStringData().
///
/// \param char_string The \c CharStringData to convert.
/// \return A string representation of \c char_string.
std::string charStringDataToString(const CharStringData& char_string);

/// \brief Compare two CharString objects
///
/// \param self The CharString field to compare
/// \param other The CharString field to compare to
///
/// \return -1 if \c self would be sorted before \c other
///          1 if \c self would be sorted after \c other
///          0 if \c self and \c other are equal
int compareCharStrings(const CharString& self, const CharString& other);

/// \brief Compare two CharStringData objects
///
/// \param self The CharStringData field to compare
/// \param other The CharStringData field to compare to
///
/// \return -1 if \c self would be sorted before \c other
///          1 if \c self would be sorted after \c other
///          0 if \c self and \c other are equal
int compareCharStringDatas(const CharStringData& self,
                           const CharStringData& other);

/// \brief Convert a buffer containing a character-string to CharString
///
/// This method reads one character-string from the given buffer (in wire
/// format) and places the result in the given \c CharString object.
/// Since this is expected to be used in message parsing, the exception it
/// raises is of that type.
///
/// On success, the buffer position is advanced to the end of the char-string,
/// and the number of bytes read is returned.
///
/// \param buffer The buffer to read from.
/// \param rdata_len The total size of the rr's rdata currently being read
/// (used for integrity checks in the wire data)
/// \param target The \c CharString where the result will be stored. Any
/// existing data in the target will be overwritten.
/// \throw DNSMessageFORMERR If the available data is not enough to read
/// the character-string, or if the character-string length is out of bounds
/// \return The number of bytes read
size_t bufferToCharString(isc::util::InputBuffer& buffer, size_t rdata_len,
                          CharString& target);


} // namespace detail
} // namespace generic
} // namespace rdata
} // namespace dns
} // namespace isc
#endif  // DNS_RDATA_CHARSTRING_H

// Local Variables:
// mode: c++
// End:
