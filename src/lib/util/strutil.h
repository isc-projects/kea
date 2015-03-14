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

#ifndef STRUTIL_H
#define STRUTIL_H

#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <exceptions/exceptions.h>
#include <boost/lexical_cast.hpp>

namespace isc {
namespace util {
namespace str {

/// \brief A Set of C++ Utilities for Manipulating Strings

///
/// \brief A standard string util exception that is thrown if getToken or
/// numToToken are called with bad input data
///
class StringTokenError : public Exception {
public:
    StringTokenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief Normalize Backslash
///
/// Only relevant to Windows, this replaces all "\" in a string with "/"
/// and returns the result.  On other systems it is a no-op.  Note
/// that Windows does recognize file names with the "\" replaced by "/"
/// (at least in system calls, if not the command line).
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
/// Special cases are:
/// -# The empty string is considered to be zero tokens.
/// -# A string comprising nothing but delimiters is considered to be zero
///    tokens.
///
/// The reasoning behind this is that the string can be thought of as having
/// invisible leading and trailing delimiter characters.  Therefore both cases
/// reduce to a set of contiguous delimiters, which are considered a single
/// delimiter (so getting rid of the string).
///
/// We could use Boost for this, but this (simple) function eliminates one
/// dependency in the code.
///
/// \param text String to be split.  Passed by value as the internal copy is
/// altered during the processing.
/// \param delim Delimiter characters
///
/// \return Vector of tokens.
std::vector<std::string> tokens(const std::string& text,
        const std::string& delim = std::string(" \t\n"));


/// \brief Uppercase Character
///
/// Used in uppercase() to pass as an argument to std::transform().  The
/// function std::toupper() can't be used as it takes an "int" as its argument;
/// this confuses the template expansion mechanism because dereferencing a
/// string::iterator returns a char.
///
/// \param chr Character to be upper-cased.
///
/// \return Uppercase version of the argument
inline char toUpper(char chr) {
    return (static_cast<char>(std::toupper(static_cast<int>(chr))));
}


/// \brief Uppercase String
///
/// A convenience function to uppercase a string.
///
/// \param text String to be upper-cased.
inline void uppercase(std::string& text) {
    std::transform(text.begin(), text.end(), text.begin(),
        isc::util::str::toUpper);
}

/// \brief Lowercase Character
///
/// Used in lowercase() to pass as an argument to std::transform().  The
/// function std::tolower() can't be used as it takes an "int" as its argument;
/// this confuses the template expansion mechanism because dereferencing a
/// string::iterator returns a char.
///
/// \param chr Character to be lower-cased.
///
/// \return Lowercase version of the argument
inline char toLower(char chr) {
    return (static_cast<char>(std::tolower(static_cast<int>(chr))));
}

/// \brief Lowercase String
///
/// A convenience function to lowercase a string
///
/// \param text String to be lower-cased.
inline void lowercase(std::string& text) {
    std::transform(text.begin(), text.end(), text.begin(),
        isc::util::str::toLower);
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


/// \brief Returns one token from the given stringstream
///
/// Using the >> operator, with basic error checking
///
/// \exception StringTokenError if the token cannot be read from the stream
///
/// \param iss stringstream to read one token from
///
/// \return the first token read from the stringstream
std::string getToken(std::istringstream& iss);

/// \brief Converts a string token to an *unsigned* integer.
///
/// The value is converted using a lexical cast, with error and bounds
/// checking.
///
/// NumType is a *signed* integral type (e.g. int32_t) that is sufficiently
/// wide to store resulting integers.
///
/// BitSize is the maximum number of bits that the resulting integer can take.
/// This function first checks whether the given token can be converted to
/// an integer of NumType type.  It then confirms the conversion result is
/// within the valid range, i.e., [0, 2^BitSize - 1].  The second check is
/// necessary because lexical_cast<T> where T is an unsigned integer type
/// doesn't correctly reject negative numbers when compiled with SunStudio.
///
/// \exception StringTokenError if the value is out of range, or if it
///            could not be converted
///
/// \param num_token the string token to convert
///
/// \return the converted value, of type NumType
template <typename NumType, int BitSize>
NumType
tokenToNum(const std::string& num_token) {
    NumType num;
    try {
        num = boost::lexical_cast<NumType>(num_token);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(StringTokenError, "Invalid SRV numeric parameter: " <<
                  num_token);
    }
    if (num < 0 || num >= (static_cast<NumType>(1) << BitSize)) {
        isc_throw(StringTokenError, "Numeric SRV parameter out of range: " <<
                  num);
    }
    return (num);
}

} // namespace str
} // namespace util
} // namespace isc

#endif // STRUTIL_H
