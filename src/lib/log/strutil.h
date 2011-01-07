// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __STRUTIL_H
#define __STRUTIL_H

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace isc {
namespace strutil {

/// \brief A Set of C++ Utilities for Manipulating Strings

/// \brief Normalize Backslash
///
/// Only relevant to Windows, this replaces all "\" in a string with "/" and
/// returns the result.  On other systems it is a no-op.  Note that Windows does
/// recognise file names with the "\" replaced by "/" (at least in system calls,
/// if not the command line).
///
/// \param name Name to be substituted
void normalizeSlash(std::string& name);


/// \brief Trim Leading and Trailing Spaces
///
/// Returns a copy of the input string but with any leading or trailing spaces
/// or tabs removed.
///
/// \param instring Input string to modify
///
/// \return String with leading and trailing spaces removed
std::string trim(const std::string& instring);


/// \brief Split String into Tokens
///
/// Splits a string into tokens (the tokens being delimited by one or more of
/// the delimiter characters) and returns the tokens in a vector array. Note
/// that adjacent delimiters are considered to be a single delimiter.
///
/// We could use Boost for this, but this (simple) function eliminates one
/// dependency in the code.
///
/// \param text String to be split.  Passed by value as the internal copy is
/// altered during the processing.
/// \param delim Delimiter characters
///
/// \return Vector of tokens.
std::vector<std::string> tokens(const std::string text,
        const std::string& delim = std::string(" \t\n"));


/// \brief Uppercase Character
///
/// Needed to pass as an argument to transform() in uppercase(), as the
/// function std::toupper() takes an "int" as its argument and the template
/// expansion mechanism gets confused.
///
/// \param chr Character to be upper-cased.
///
/// \return Uppercase version of the argument
inline char toUpper(char chr) {
    return static_cast<char>(std::toupper(static_cast<int>(chr)));
}


/// \brief Uppercase String
///
/// A convenience function to uppercase a string.
///
/// \param text String to be upper-cased.
inline void uppercase(std::string& text) {
    std::transform(text.begin(), text.end(), text.begin(),
        isc::strutil::toUpper);
}

/// \brief Lowercase Character
///
/// Needed to pass as an argument to transform() in lowercase(), as the
/// function std::tolower() takes an "int" as its argument and the template
/// expansion mechanism gets confused.
///
/// \param chr Character to be lower-cased.
///
/// \return Lowercase version of the argument
inline char toLower(char chr) {
    return static_cast<char>(std::tolower(static_cast<int>(chr)));
}

/// \brief Lowercase String
///
/// A convenience function to lowercase a string
///
/// \param text String to be lower-cased.
inline void lowercase(std::string& text) {
    std::transform(text.begin(), text.end(), text.begin(),
        isc::strutil::toLower);
}


/// \brief Apply Formatting
///
/// Given a printf-style format string containing only "%s" place holders
/// (others are ignored) and a vector of strings, this produces a single string
/// with the placeholders replaced.
///
/// \param format Format string
/// \param args Vector of argument strings
///
/// \return Resultant string
std::string format(const std::string& format,
    const std::vector<std::string>& args);


} // namespace strutil
} // namespace isc

#endif // __STRUTIL_H
