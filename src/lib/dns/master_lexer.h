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

#include <istream>
#include <string>

#include <stdint.h>

namespace isc {
namespace dns {
namespace master_lexer_internal {
class State;
}

/// \brief Tokenizer for parsing DNS master files.
///
/// The \c MasterLexer class provides tokenize interfaces for parsing DNS
/// master files.  It understands some special rules of master files as
/// defined in RFC 1035, such as comments, character escaping, and multi-line
/// data, and provides the user application with the actual data in a
/// more convenient form such as a std::string object.
///
/// In order to support the $INCLUDE notation, this class is designed to be
/// able to operate on multiple files or input streams in the nested way.
/// The \c pushSource() and \c popSource() methods correspond to the push
/// and pop operations.
///
/// While this class is public, it is less likely to be used by normal
/// applications; it's mainly expected to be used within this library,
/// specifically by the \c MasterLoader class and \c Rdata implementation
/// classes.
///
/// \note The error handling policy of this class is slightly different from
/// that of other classes of this library.  We generally throw an exception
/// for an invalid input, whether it's more likely to be a program error or
/// a "user error", which means an invalid input that comes from outside of
/// the library.  But, this class returns an error code for some certain
/// types of user errors instead of throwing an exception.  Such cases include
/// a syntax error identified by the lexer or a misspelled file name that
/// causes a system error at the time of open.  This is based on the assumption
/// that the main user of this class is a parser of master files, where
/// we want to give an option to ignore some non fatal errors and continue
/// the parsing.  This will be useful if it just performs overall error
/// checks on a master file.  When the (immediate) caller needs to do explicit
/// error handling, exceptions are not that a useful tool for error reporting
/// because we cannot separate the normal and error cases anyway, which would
/// be one major advantage when we use exceptions.  And, exceptions are
/// generally more expensive, either when it happens or just by being able
/// to handle with \c try and \c catch (depending on the underlying
/// implementation of the exception handling).  For these reasons, some of
/// this class does not throw for an error that would be reported as an
/// exception in other classes.
class MasterLexer {
    friend class master_lexer_internal::State;
public:
    class Token;       // we define it separately for better readability

    /// \brief Options for getNextToken.
    ///
    /// A compound option, indicating multiple options are set, can be
    /// specified using the logical OR operator (operator|()).
    enum Options {
        NONE = 0,               ///< No option
        INITIAL_WS = 1, ///< recognize begin-of-line spaces after an
                        ///< end-of-line
        QSTRING = 2,    ///< recognize quoted string
        NUMBER = 4   ///< recognize numeric text as integer
    };

    /// \brief The constructor.
    ///
    /// \throw std::bad_alloc Internal resource allocation fails (rare case).
    MasterLexer();

    /// \brief The destructor.
    ///
    /// It internally closes any remaining input sources.
    ~MasterLexer();

    /// \brief Open a file and make it the current input source of MasterLexer.
    ///
    /// The opened file can be explicitly closed by the \c popSource() method;
    /// if \c popSource() is not called within the lifetime of the
    /// \c MasterLexer, it will be closed in the destructor.
    ///
    /// In the case possible system errors in opening the file (most likely
    /// because of specifying a non-existent or unreadable file), it returns
    /// false, and if the optional \c error parameter is non NULL, it will be
    /// set to a description of the error (any existing content of the string
    /// will be discarded).  If opening the file succeeds, the given
    /// \c error parameter will be intact.
    ///
    /// Note that this method has two styles of error reporting: one by
    /// returning \c false (and setting \c error optionally) and the other
    /// by throwing an exception.  See the note for the class description
    /// about the distinction.
    ///
    /// \throw InvalidParameter filename is NULL
    /// \param filename A non NULL string specifying a master file
    /// \param error If non null, a placeholder to set error description in
    /// case of failure.
    ///
    /// \return true if pushing the file succeeds; false otherwise.
    bool pushSource(const char* filename, std::string* error = NULL);

    /// \brief Make the given stream the current input source of MasterLexer.
    ///
    /// The caller still holds the ownership of the passed stream; it's the
    /// caller's responsibility to keep it valid as long as it's used in
    /// \c MasterLexer or to release any resource for the stream after that.
    /// The caller can explicitly tell \c MasterLexer to stop using the
    /// stream by calling the \c popSource() method.
    ///
    /// \param input An input stream object that produces textual
    /// representation of DNS RRs.
    void pushSource(std::istream& input);

    /// \brief Stop using the most recently opened input source (file or
    /// stream).
    ///
    /// If it's a file, the previously opened file will be closed internally.
    /// If it's a stream, \c MasterLexer will simply stop using
    /// the stream; the caller can assume it will be never used in
    /// \c MasterLexer thereafter.
    ///
    /// This method must not be called when there is no source pushed for
    /// \c MasterLexer.  This method is otherwise exception free.
    ///
    /// \throw isc::InvalidOperation Called with no pushed source.
    void popSource();

    /// \brief Return the name of the current input source name.
    ///
    /// If it's a file, it will be the C string given at the corresponding
    /// \c pushSource() call, that is, its filename.  If it's a stream, it will
    /// be formatted as \c "stream-%p" where \c %p is hex representation
    /// of the address of the stream object.
    ///
    /// If there is no opened source at the time of the call, this method
    /// returns an empty string.
    ///
    /// \throw std::bad_alloc Resource allocation failed for string
    /// construction (rare case)
    ///
    /// \return A string representation of the current source (see the
    /// description)
    std::string getSourceName() const;

    /// \brief Return the input source line number.
    ///
    /// If there is an opened source, the return value will be a non-0
    /// integer indicating the line number of the current source where
    /// the \c MasterLexer is currently working.  The expected usage of
    /// this value is to print a helpful error message when parsing fails
    /// by specifically identifying the position of the error.
    ///
    /// If there is no opened source at the time of the call, this method
    /// returns 0.
    ///
    /// \throw None
    ///
    /// \return The current line number of the source (see the description)
    size_t getSourceLine() const;

private:
    struct MasterLexerImpl;
    MasterLexerImpl* impl_;
};

/// \brief Operator to combine \c MasterLexer options
///
/// This is a trivial shortcut so that compound options can be specified
/// in an intuitive way.
inline MasterLexer::Options
operator|(MasterLexer::Options o1, MasterLexer::Options o2) {
    return (static_cast<MasterLexer::Options>(
                static_cast<unsigned>(o1) | static_cast<unsigned>(o2)));
}

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
    ///
    /// \note At the time of initial implementation, all numeric tokens
    /// that would be extracted from \c MasterLexer should be represented
    /// as an unsigned 32-bit integer.  If we see the need for larger integers
    /// or negative numbers, we can then extend the token types.
    enum Type {
        END_OF_LINE, ///< End of line detected (if asked for detecting it)
        END_OF_FILE, ///< End of file detected (if asked for detecting it)
        INITIAL_WS,  ///< White spaces at the beginning of a line after an
                     ///< end of line
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
