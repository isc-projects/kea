// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STRUTIL_H
#define STRUTIL_H

#include <algorithm>
#include <cctype>
#include <stdint.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <exceptions/exceptions.h>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace util {
namespace str {

/// @brief A Set of C++ Utilities for Manipulating Strings

///
/// @brief A standard string util exception that is thrown if getToken or
/// numToToken are called with bad input data
///
class StringTokenError : public Exception {
public:
    StringTokenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Normalize Backslash
///
/// Only relevant to Windows, this replaces all "\" in a string with "/"
/// and returns the result.  On other systems it is a no-op.  Note
/// that Windows does recognize file names with the "\" replaced by "/"
/// (at least in system calls, if not the command line).
///
/// @param name Name to be substituted
void normalizeSlash(std::string& name);

/// @brief Trim Leading and Trailing Spaces
///
/// Returns a copy of the input string but with any leading or trailing spaces
/// or tabs removed.
///
/// @param instring Input string to modify
///
/// @return String with leading and trailing spaces removed
std::string trim(const std::string& instring);

/// @brief Finds the "trimmed" end of a buffer
///
/// Works backward from the end of the buffer, looking for the first
/// character not equal to the trim value, and returns an iterator
/// pointing that that position.
///
/// @param begin - Forward iterator pointing to the beginning of the
/// buffer to trim
/// @param end - Forward iterator pointing to the untrimmed end of
/// the buffer to trim
/// @param trim_val - byte value to trim off
///
/// @return Iterator pointing the first character from the end of the
/// buffer not equal to the  trim value
template<typename Iterator>
Iterator
seekTrimmed(Iterator begin, Iterator end, uint8_t trim_val) {
    for ( ; end != begin && *(end - 1) == trim_val; --end);
    return(end);
}

/// @brief Split String into Tokens
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
std::vector<std::string> tokens(const std::string& text,
        const std::string& delim = std::string(" \t\n"),
        bool escape = false);

/// @brief Uppercase Character
///
/// Used in uppercase() to pass as an argument to std::transform().  The
/// function std::toupper() can't be used as it takes an "int" as its argument;
/// this confuses the template expansion mechanism because dereferencing a
/// string::iterator returns a char.
///
/// @param chr Character to be upper-cased.
///
/// @return Uppercase version of the argument
inline char toUpper(char chr) {
    return (static_cast<char>(std::toupper(static_cast<int>(chr))));
}

/// @brief Uppercase String
///
/// A convenience function to uppercase a string.
///
/// @param text String to be upper-cased.
inline void uppercase(std::string& text) {
    std::transform(text.begin(), text.end(), text.begin(),
        isc::util::str::toUpper);
}

/// @brief Lowercase Character
///
/// Used in lowercase() to pass as an argument to std::transform().  The
/// function std::tolower() can't be used as it takes an "int" as its argument;
/// this confuses the template expansion mechanism because dereferencing a
/// string::iterator returns a char.
///
/// @param chr Character to be lower-cased.
///
/// @return Lowercase version of the argument
inline char toLower(char chr) {
    return (static_cast<char>(std::tolower(static_cast<int>(chr))));
}

/// @brief Lowercase String
///
/// A convenience function to lowercase a string
///
/// @param text String to be lower-cased.
inline void lowercase(std::string& text) {
    std::transform(text.begin(), text.end(), text.begin(),
        isc::util::str::toLower);
}

/// @brief Apply Formatting
///
/// Given a printf-style format string containing only "%s" place holders
/// (others are ignored) and a vector of strings, this produces a single string
/// with the placeholders replaced.
///
/// @param format Format string
/// @param args Vector of argument strings
///
/// @return Resultant string
std::string format(const std::string& format,
    const std::vector<std::string>& args);


/// @brief Returns one token from the given stringstream
///
/// Using the >> operator, with basic error checking
///
/// @throw StringTokenError if the token cannot be read from the stream
///
/// @param iss stringstream to read one token from
///
/// @return the first token read from the stringstream
std::string getToken(std::istringstream& iss);

/// @brief Converts a string token to an *unsigned* integer.
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
/// @throw StringTokenError if the value is out of range, or if it
///        could not be converted
///
/// @param num_token the string token to convert
///
/// @return the converted value, of type NumType
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
/// Convenience method which calls @c decodeSeparatedHexString() passing
/// in a colon for the separator.

/// @param hex_string Input string.
/// @param binary Vector receiving converted string into binary.
///
/// @throw isc::BadValue if the format of the input string is invalid.
void
decodeColonSeparatedHexString(const std::string& hex_string,
                              std::vector<uint8_t>& binary);

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
decodeFormattedHexString(const std::string& hex_string,
                         std::vector<uint8_t>& binary);

/// @brief Forward declaration to the @c StringSanitizer implementation.
class StringSanitizerImpl;

/// @brief Type representing the pointer to the @c StringSanitizerImpl.
typedef boost::shared_ptr<StringSanitizerImpl> StringSanitizerImplPtr;

/// @brief Implements a regular expression based string scrubber
///
/// The implementation uses C++11 regex IF the environment supports it
/// (tested in configure.ac). If not it falls back to C lib regcomp/regexec.
/// Older compilers, such as pre Gnu g++ 4.9.0, provided only experimental
/// implementations of regex which are recognized as buggy.
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
    /// @throw BadValue if given an invalid regular expression
    StringSanitizer(const std::string& char_set,
                    const std::string& char_replacement);

    /// @brief Destructor.
    ///
    /// Destroys the implementation instance.
    ~StringSanitizer();

    /// Returns a scrubbed copy of a given string
    ///
    /// Replaces all occurrences of characters described by the regular
    /// expression with the character replacement.
    ///
    /// @param original the string to scrub
    ///
    /// @throw Unexpected if an error occurs during scrubbing
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
typedef boost::shared_ptr<StringSanitizer> StringSanitizerPtr;

/// @brief Check if a string is printable
///
/// @param content String to check for printable characters
///
/// @return True if empty or contains only printable characters, False otherwise
inline bool
isPrintable(const std::string& content) {
    for (const auto& ch : content) {
        if (isprint(static_cast<int>(ch)) == 0) {
            return (false);
        }
    }
    return (true);
}

/// @brief Check if a byte vector is printable
///
/// @param content Vector to check for printable characters
///
/// @return True if empty or contains only printable characters, False otherwise
inline bool
isPrintable(const std::vector<uint8_t>& content) {
    for (const auto& ch : content) {
        if (isprint(static_cast<int>(ch)) == 0) {
            return (false);
        }
    }
    return (true);
}


/// @brief Dumps a buffer of bytes as a string of hexadecimal digits
///
/// @param data pointer to the data to dump
/// @param length number of bytes to dump. Caller should ensure the length
/// does not exceed the buffer.
std::string dumpAsHex(const uint8_t* data, size_t length);

} // namespace str
} // namespace util
} // namespace isc

#endif // STRUTIL_H
