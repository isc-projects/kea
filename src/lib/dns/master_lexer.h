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

#ifndef MASTER_LEXER_H
#define MASTER_LEXER_H 1

#include <exceptions/exceptions.h>

#include <string>

#include <stdint.h>

namespace isc {
namespace dns {

class MasterLexer {
public:
    class Token;       // we define it separately for better readability
};

/// \brief Tokens for \c MasterLexer
///
/// This is a simple value-class encapsulating a type of a lexer token and
/// (if it has a value) its value.  Essentially, the class provides
/// constructors corresponding to different types of tokens, and corresponding
/// getter methods.  The type and value are fixed at the time of construction
/// and will never be modified throughout the lifetime of the object.
/// The getter methods are still provided to maximize the safety; an
/// application cannot refer to a value that is invalid for the type of token.
///
/// This class is intentionally implemented as copyable and assignable
/// (using the default version of copy constructor and assignment operator),
/// but it's mainly for internal implementation convenience.  Applications will
/// simply refer to Token object as a reference via the \c MasterLexer class.
class MasterLexer::Token {
public:
    /// \brief Enumeration for token types
    enum Type {
        END_OF_LINE, ///< End of line detected (if asked for detecting it)
        END_OF_FILE, ///< End of file detected (if asked for detecting it)
        INITIAL_WS,  ///< White spaces at the beginning of a line
        NOVALUE_TYPE_MAX = INITIAL_WS, ///< Max integer corresponding to
                                       /// no-value (type only) types.
                                       /// Mainly for internal use.
        STRING, ///< A single string
        QSTRING, ///< A single string quoted by double-quotes (").
        NUMBER,  ///< A decimal number (unsigned 32-bit)
        ERROR    ///< Error detected in getting a token
    };

    /// \brief Enumeration for lexer error codes
    enum ErrorCode {
        NOT_STARTED, ///< The lexer is just initialized and has no token
        UNBALANCED_PAREN,       ///< Unbalanced parentheses detected
        UNEXPECTED_END, ///< The lexer reaches the end of line or file
                       /// unexpectedly
        UNBALANCED_QUOTES,      ///< Unbalanced quotations detected
        MAX_ERROR_CODE ///< Max integer corresponding to valid error codes.
                       /// (excluding this one). Mainly for internal use.
    };

    /// \brief A simple representation of a range of a string.
    ///
    /// This is a straightforward pair of the start pointer of a string
    /// and its length.  The \c STRING and \c QSTRING types of tokens
    /// will be primarily represented in this form.
    ///
    /// Any character can be stored in the valid range of the region.
    /// In particular, there can be a nul character (\0) in the middle of
    /// the region.  On the other hand, it is not ensured that the string
    /// is nul-terminated.  So the usual string manipulation API may not work
    /// as expected.
    struct StringRegion {
        const char* beg;        ///< The start address of the string
        size_t len;             ///< The length of the string in bytes
    };

    /// \brief Constructor for non-value type of token.
    ///
    /// \throw InvalidParameter A value type token is specified.
    /// \param type The type of the token.  It must indicate a non-value
    /// type (not larger than \c NOVALUE_TYPE_MAX).
    explicit Token(Type type) : type_(type) {
        if (type > NOVALUE_TYPE_MAX) {
            isc_throw(InvalidParameter, "Token per-type constructor "
                      "called with invalid type: " << type);
        }
    }

    /// \brief Constructor for string and quoted-string types of token.
    ///
    /// The optional \c quoted parameter specifies whether it's a quoted or
    /// non quoted string.
    ///
    /// The string is specified as a pair of a pointer to the start address
    /// and its length.  Any character can be contained in any position of
    /// the valid range (see \c StringRegion).
    ///
    /// When it's a quoted string, the quotation marks must be excluded
    /// from the specified range.
    ///
    /// \param str_beg The start address of the string
    /// \param str_len The size of the string in bytes
    /// \param quoted true if it's a quoted string; false otherwise.
    Token(const char* str_beg, size_t str_len, bool quoted = false) :
        type_(quoted ? QSTRING : STRING)
    {
        val_.str_region_.beg = str_beg;
        val_.str_region_.len = str_len;
    }

    /// \brief Constructor for number type of token.
    ///
    /// \brief number An unsigned 32-bit integer corresponding to the token
    /// value.
    explicit Token(uint32_t number) : type_(NUMBER) {
        val_.number_ = number;
    }

    /// \brief Constructor for error type of token.
    ///
    /// \throw InvalidParameter Invalid error code value is specified.
    /// \brief error_code A pre-defined constant of \c ErrorCode.
    explicit Token(ErrorCode error_code) : type_(ERROR) {
        if (!(error_code < MAX_ERROR_CODE)) {
            isc_throw(InvalidParameter, "Invalid master lexer error code: "
                      << error_code);
        }
        val_.error_code_ = error_code;
    }

    /// \brief Return the token type.
    ///
    /// \throw none
    Type getType() const { return (type_); }

    /// \brief Return the value of a string-variant token.
    ///
    /// \throw InvalidOperation Called on a non string-variant types of token.
    /// \return A reference to \c StringRegion corresponding to the string
    ///         token value.
    const StringRegion& getStringRegion() const {
        if (type_ != STRING && type_ != QSTRING) {
            isc_throw(InvalidOperation,
                      "Token::getStringRegion() for non string-variant type");
        }
        return (val_.str_region_);
    }

    /// \brief Return the value of a string-variant token as a string object.
    ///
    /// Note that the underlying string may contain a nul (\0) character
    /// in the middle.  The returned string object will contain all characters
    /// of the valid range of the underlying string.  So some string
    /// operations such as c_str() may not work as expected.
    ///
    /// \throw InvalidOperation Called on a non string-variant types of token.
    /// \throw std::bad_alloc Resource allocation failure in constructing the
    ///                       string object.
    /// \return A std::string object corresponding to the string token value.
    std::string getString() const {
        if (type_ != STRING && type_ != QSTRING) {
            isc_throw(InvalidOperation,
                      "Token::getString() for non string-variant type");
        }
        return (std::string(val_.str_region_.beg,
                            val_.str_region_.beg + val_.str_region_.len));
    }

    /// \brief Return the value of a string-variant token as a string object.
    ///
    /// \throw InvalidOperation Called on a non number type of token.
    /// \return The integer corresponding to the number token value.
    uint32_t getNumber() const {
        if (type_ != NUMBER) {
            isc_throw(InvalidOperation,
                      "Token::getNumber() for non number type");
        }
        return (val_.number_);
    }

    /// \brief Return the error code of a error type token.
    ///
    /// \throw InvalidOperation Called on a non error type of token.
    /// \return The error code of the token.
    ErrorCode getErrorCode() const {
        if (type_ != ERROR) {
            isc_throw(InvalidOperation,
                      "Token::getErrorCode() for non error type");
        }
        return (val_.error_code_);
    };

    /// \brief Return a textual description of the error of a error type token.
    ///
    /// The returned string would be useful to produce a log message when
    /// a zone file parser encounters an error.
    ///
    /// \throw InvalidOperation Called on a non error type of token.
    /// \throw std::bad_alloc Resource allocation failure in constructing the
    ///                       string object.
    /// \return A string object that describes the meaning of the error.
    std::string getErrorText() const;

private:
    Type type_;    // this is not const so the class can be assignable

    // We use a union to represent different types of token values via the
    // unified Token class.  The class integrity should ensure valid operation
    // on the union; getter methods should only refer to the member set at
    // the construction.
    union {
        StringRegion str_region_;
        uint32_t number_;
        ErrorCode error_code_;
    } val_;
};

} // namespace dns
} // namespace isc
#endif  // MASTER_LEXER_H

// Local Variables:
// mode: c++
// End:
