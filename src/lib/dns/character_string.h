// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CHARACTER_STRING_H
#define CHARACTER_STRING_H

#include <string>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

namespace isc {
namespace dns {

// \brief Some utility functions to extract <character-string> from string
// or InputBuffer
//
// <character-string> is expressed in one or two ways: as a contiguous set
// of characters without interior spaces, or as a string beginning with a "
// and ending with a ".  Inside a " delimited string any character can
// occur, except for a " itself, which must be quoted using \ (back slash).
// Ref. RFC1035


namespace characterstr {
    /// Get a <character-string> from a string
    ///
    /// \param input_str The input string
    /// \param input_iterator The iterator from which to start extracting,
    ///        the iterator will be updated to new position after the function
    ///        is returned
    /// \param quoted If not \c NULL, returns \c true at this address if
    ///        the string is quoted, \cfalse otherwise
    /// \return A std::string that contains the extracted <character-string>
    std::string getNextCharacterString(const std::string& input_str,
                                       std::string::const_iterator& input_iterator,
                                       bool* quoted = NULL);

    /// Get a <character-string> from a input buffer
    ///
    /// \param buffer The input buffer
    /// \param len The input buffer total length
    /// \return A std::string that contains the extracted <character-string>
    std::string getNextCharacterString(util::InputBuffer& buffer, size_t len);

} // namespace characterstr
} // namespace dns
} // namespace isc

#endif // CHARACTER_STRING_H
