// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_UTIL_STR_H
#define KEA_UTIL_STR_H

#include <exceptions/exceptions.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

namespace isc {
namespace util {
namespace str {

/// @brief A Set of C++ Utilities for Manipulating Strings

///
/// @brief A standard string util exception that is thrown if getToken or
/// numToToken are called with bad input data
class StringTokenError : public Exception {
public:
    StringTokenError(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

/// @brief Trim leading and trailing spaces.
///
/// Returns a copy of the input string but with any leading or trailing spaces
/// or tabs removed.
///
/// @param input Input string to modify.
///
/// @return String with leading and trailing spaces removed.
std::string
trim(const std::string& input);

/// @brief Finds the "trimmed" end of a buffer
///
/// Works backward from the end of the buffer, looking for the first
/// character not equal to the trim value, and returns an iterator
/// pointing to that position.
///
/// @param begin - Forward iterator pointing to the beginning of the
/// buffer to trim.
/// @param end - Forward iterator pointing to the untrimmed end of
/// the buffer to trim.
/// @param trim_val - byte value to trim off
///
/// @return Iterator pointing the first character from the end of the
/// buffer not equal to the trim value.
template <typename Iterator>
Iterator
seekTrimmed(Iterator const& begin, Iterator end, uint8_t const trim_val) {
    while (end != begin && *(end - 1) == trim_val) {
        --end;
    }
    return (end);
}

/// @brief Split string into tokens.
///
/// Splits a string into tokens (the tokens being delimited by one or more of
/// the delimiter characters) and returns the tokens in a vector.
/// Adjacent delimiters are considered to be a single delimiter.
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
/// Optional escape allows to escape delimiter characters (and *only* them
/// and the escape character itself) using backslash.
///
/// We could use Boost for this, but this (simple) function eliminates one
/// dependency in the code.
///
/// @param text String to be split.  Passed by value as the internal copy is
/// altered during the processing.
/// @param delim Delimiter characters
/// @param escape Use backslash to escape delimiter characters
///
/// @return Vector of tokens.
std::vector<std::string>
tokens(const std::string& text, const std::string& delim = " \t\n", bool escape = false);

/// @brief Convert character to uppercase.
///
/// Used in uppercase() to pass as a parameter to std::transform().  The
/// function std::toupper() can't be used as it takes an "int" as its parameter;
/// this confuses the template expansion mechanism because dereferencing a
/// string::iterator returns a char.
///
/// @param chr Character to be upper-cased.
///
/// @return Uppercase version of the input character.
char
toUpper(char const chr);

/// @brief Convert string to uppercase.
///
/// @param text String to be upper-cased.
void
uppercase(std::string& text);

/// @brief Convert character to lowercase.
///
/// Used in lowercase() to pass as a parameter to std::transform().  The
/// function std::tolower() can't be used as it takes an "int" as its parameter;
/// this confuses the template expansion mechanism because dereferencing a
/// string::iterator returns a char.
///
/// @param chr Character to be lower-cased.
///
/// @return Lowercase version of the input character.
char
toLower(char const chr);

/// @brief Convert string to lowercase.
///
/// @param text String to be lower-cased.
void
lowercase(std::string& text);

/// @brief Converts a string in quotes into vector.
///
/// A converted string is first trimmed. If a trimmed string is in
/// quotes, the quotes are removed and the resulting string is copied
/// into a vector. If the string is not in quotes, an empty vector is
/// returned.
///
/// The resulting string is copied to a vector and returned.
///
/// This function is intended to be used by the server configuration
/// parsers to convert string values surrounded with quotes into
/// binary form.
///
/// @param quoted_string String to be converted.
///
/// @return Vector containing converted string or empty string if
/// input string didn't contain expected quote characters.
std::vector<uint8_t>
quotedStringToBinary(const std::string& quoted_string);

/// @brief Converts a string of separated hexadecimal digits
/// into a vector.
///
/// Octets may contain 1 or 2 digits. For example, using a colon
/// for a separator all of the following are valid:
///
/// - yy:yy:yy:yy:yy
/// - y:y:y:y:y
/// - y:yy:yy:y:y
///
/// If the decoded string doesn't match any of the supported formats,
/// an exception is thrown.
///
/// @param hex_string Input string.
/// @param sep character to use as a separator.
/// @param binary Vector receiving converted string into binary.
///
/// @throw isc::BadValue if the format of the input string is invalid.
void
decodeSeparatedHexString(const std::string& hex_string,
                         const std::string& sep,
                         std::vector<uint8_t>& binary);

/// @brief Converts a string of hexadecimal digits with colons into
///  a vector.
///
/// @param hex_string Input string.
/// @param binary Vector receiving converted string into binary.
///
/// @throw isc::BadValue if the format of the input string is invalid.
void
decodeColonSeparatedHexString(const std::string& hex_string, std::vector<uint8_t>& binary);

/// @brief Converts a formatted string of hexadecimal digits into
/// a vector.
///
/// This function supports the following formats:
///
/// - yy:yy:yy:yy or yy yy yy yy - octets delimited by colons or
/// spaces, see @c decodeSeparatedHexString
///
/// - yyyyyyyyyy
/// - 0xyyyyyyyyyy
///
/// If there is an odd number of hexadecimal digits in the input
/// string, the '0' is prepended to the string before decoding.
///
/// @param hex_string Input string.
/// @param binary Vector receiving converted string into binary.
///
/// @throw isc::BadValue if the format of the input string is invalid.
void
decodeFormattedHexString(const std::string& hex_string, std::vector<uint8_t>& binary);

/// @brief Forward declaration to the @c StringSanitizer implementation.
class StringSanitizerImpl;

/// @brief Type representing the pointer to the @c StringSanitizerImpl.
using StringSanitizerImplPtr = std::shared_ptr<StringSanitizerImpl>;

/// @brief Implements a regular expression based string scrubber.
class StringSanitizer {
public:
    /// @brief Constructor.
    ///
    /// Compiles the given character set into a regular expression, and
    /// retains the given character replacement. Thereafter, the instance
    /// may be used to scrub an arbitrary number of strings.
    ///
    /// @param char_set string containing a regular expression (POSIX
    /// extended syntax) that describes the characters to replace.  If you
    /// wanted to sanitize hostnames for example, you could specify the
    /// inversion of valid characters "[^A-Za-z0-9_-]".
    /// @param char_replacement string of one or more characters to use as the
    /// replacement for invalid characters.
    ///
    /// @throw BadValue if given an invalid regular expression.
    StringSanitizer(const std::string& char_set, const std::string& char_replacement);

    /// @brief Returns a scrubbed copy of a given string.
    ///
    /// Replaces all occurrences of characters described by the regular
    /// expression with the character replacement.
    ///
    /// @param original The string to be scrubbed.
    ///
    /// @throw Unexpected if an error occurs during scrubbing.
    std::string scrub(const std::string& original);

    /// @brief The maximum size for regex parameters.
    ///
    /// @note The regex engine is implemented using recursion and can cause
    /// stack overflow if the input data is too large. An arbitrary size of
    /// 4096 should be enough for all cases.
    static const uint32_t MAX_DATA_SIZE;

private:
    /// @brief Pointer to the @c StringSanitizerImpl.
    StringSanitizerImplPtr impl_;
};

/// @brief Type representing the pointer to the @c StringSanitizer.
using StringSanitizerPtr = std::unique_ptr<StringSanitizer>;

/// @brief Check if a string is printable.
///
/// @param content String to check for printable characters.
///
/// @return True if empty or contains only printable characters, False otherwise.
bool
isPrintable(const std::string& content);

/// @brief Check if a byte vector is printable.
///
/// @param content Vector to check for printable characters.
///
/// @return True if empty or contains only printable characters, False otherwise.
bool
isPrintable(const std::vector<uint8_t>& content);

/// @brief Dumps a buffer of bytes as a string of hexadecimal digits.
///
/// @param data Pointer to the data to dump.
/// @param length Number of bytes to dump. Caller should ensure the length
/// does not exceed the buffer.
std::string
dumpAsHex(const uint8_t* data, size_t length);

}  // namespace str
}  // namespace util
}  // namespace isc

#endif  // KEA_UTIL_STR_H
