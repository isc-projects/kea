// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MASTER_LEXER_H
#define MASTER_LEXER_H 1

#include <dns/exceptions.h>

#include <istream>
#include <string>

#include <stdint.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace dns {
namespace master_lexer_internal {
class State;
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
class MasterToken {
public:
    /// \brief Enumeration for token types
    ///
    /// \note At the time of initial implementation, all numeric tokens
    /// that would be extracted from \c MasterLexer should be represented
    /// as an unsigned 32-bit integer.  If we see the need for larger integers
    /// or negative numbers, we can then extend the token types.
    enum Type {
        END_OF_LINE, ///< End of line detected
        END_OF_FILE, ///< End of file detected
        INITIAL_WS,  ///< White spaces at the beginning of a line after an
                     ///< end of line or at the beginning of file (if asked
                     //   for detecting it)
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
        NO_TOKEN_PRODUCED, ///< No token was produced. This means programmer
                           /// error and should never get out of the lexer.
        NUMBER_OUT_OF_RANGE, ///< Number was out of range
        BAD_NUMBER,    ///< Number is expected but not recognized
        UNEXPECTED_QUOTES, ///< Unexpected quotes character detected
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
    /// the region.  So the usual string manipulation API may not work
    /// as expected.
    ///
    /// The `MasterLexer` implementation ensures that there are at least
    /// len + 1 bytes of valid memory region starting from beg, and that
    /// beg[len] is \0.  This means the application can use the bytes as a
    /// validly nul-terminated C string if there is no intermediate nul
    /// character.  Note also that due to this property beg is always non
    /// NULL; for an empty string len will be set to 0 and beg[0] is \0.
    struct StringRegion {
        const char* beg;        ///< The start address of the string
        size_t len;             ///< The length of the string in bytes
    };

    /// \brief Constructor for non-value type of token.
    ///
    /// \throw InvalidParameter A value type token is specified.
    /// \param type The type of the token.  It must indicate a non-value
    /// type (not larger than \c NOVALUE_TYPE_MAX).
    explicit MasterToken(Type type) : type_(type) {
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
    MasterToken(const char* str_beg, size_t str_len, bool quoted = false) :
        type_(quoted ? QSTRING : STRING)
    {
        val_.str_region_.beg = str_beg;
        val_.str_region_.len = str_len;
    }

    /// \brief Constructor for number type of token.
    ///
    /// \brief number An unsigned 32-bit integer corresponding to the token
    /// value.
    explicit MasterToken(uint32_t number) : type_(NUMBER) {
        val_.number_ = number;
    }

    /// \brief Constructor for error type of token.
    ///
    /// \throw InvalidParameter Invalid error code value is specified.
    /// \brief error_code A pre-defined constant of \c ErrorCode.
    explicit MasterToken(ErrorCode error_code) : type_(ERROR) {
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
        std::string ret;
        getString(ret);
        return (ret);
    }

    /// \brief Fill in a string with the value of a string-variant token.
    ///
    /// This is similar to the other version of \c getString(), but
    /// the caller is supposed to pass a placeholder string object.
    /// This will be more efficient if the caller uses the same
    /// \c MasterLexer repeatedly and needs to get string token in the
    /// form of a string object many times as this version could reuse
    /// the existing internal storage of the passed string.
    ///
    /// Any existing content of the passed string will be removed.
    ///
    /// \throw InvalidOperation Called on a non string-variant types of token.
    /// \throw std::bad_alloc Resource allocation failure in constructing the
    ///                       string object.
    ///
    /// \param ret A string object to be filled with the token string.
    void getString(std::string& ret) const {
        if (type_ != STRING && type_ != QSTRING) {
            isc_throw(InvalidOperation,
                      "Token::getString() for non string-variant type");
        }
        ret.assign(val_.str_region_.beg,
                   val_.str_region_.beg + val_.str_region_.len);
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
class MasterLexer : public boost::noncopyable {
    friend class master_lexer_internal::State;
public:
    /// \brief Exception thrown when we fail to read from the input
    /// stream or file.
    class ReadError : public Unexpected {
    public:
        ReadError(const char* file, size_t line, const char* what) :
            Unexpected(file, line, what)
        {}
    };

    /// \brief Exception thrown from a wrapper version of
    /// \c MasterLexer::getNextToken() for non fatal errors.
    ///
    /// See the method description for more details.
    ///
    /// The \c token_ member variable (read-only) is set to a \c MasterToken
    /// object of type ERROR indicating the reason for the error.
    class LexerError : public isc::dns::Exception {
    public:
        LexerError(const char* file, size_t line, MasterToken error_token) :
            isc::dns::Exception(file, line, error_token.getErrorText().c_str()),
            token_(error_token)
        {}
        const MasterToken token_;
    };

    /// \brief Special value for input source size meaning "unknown".
    ///
    /// This constant value will be used as a return value of
    /// \c getTotalSourceSize() when the size of one of the pushed sources
    /// is unknown.  Note that this value itself is a valid integer in the
    /// range of the type, so there's still a small possibility of
    /// ambiguity.  In practice, however, the value should be sufficiently
    /// large that should eliminate the possibility.
    static const size_t SOURCE_SIZE_UNKNOWN;

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
    /// The data in \c input must be complete at the time of this call.
    /// The behavior of the lexer is undefined if the caller builds or adds
    /// data in \c input after pushing it.
    ///
    /// Except for rare case system errors such as memory allocation failure,
    /// this method is generally expected to be exception free.  However,
    /// it can still throw if it encounters an unexpected failure when it
    /// tries to identify the "size" of the input source (see
    /// \c getTotalSourceSize()).  It's an unexpected result unless the
    /// caller intentionally passes a broken stream; otherwise it would mean
    /// some system-dependent unexpected behavior or possibly an internal bug.
    /// In these cases it throws an \c Unexpected exception.  Note that
    /// this version of the method doesn't return a boolean unlike the
    /// other version that takes a file name; since this failure is really
    /// unexpected and can be critical, it doesn't make sense to give the
    /// caller an option to continue (other than by explicitly catching the
    /// exception).
    ///
    /// \throw Unexpected An unexpected failure happens in initialization.
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

    /// \brief Get number of sources inside the lexer.
    ///
    /// This method never throws.
    size_t getSourceCount() const;

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

    /// \brief Return the total size of pushed sources.
    ///
    /// This method returns the sum of the size of sources that have been
    /// pushed to the lexer by the time of the call.  It would give the
    /// caller some hint about the amount of data the lexer is working on.
    ///
    /// The size of a normal file is equal to the file size at the time of
    /// the source is pushed.  The size of other type of input stream is
    /// the size of the data available in the stream at the time of the
    /// source is pushed.
    ///
    /// In some special cases, it's possible that the size of the file or
    /// stream is unknown.  It happens, for example, if the standard input
    /// is associated with a pipe from the output of another process and it's
    /// specified as an input source.  If the size of some of the pushed
    /// source is unknown, this method returns SOURCE_SIZE_UNKNOWN.
    ///
    /// The total size won't change when a source is popped.  So the return
    /// values of this method will monotonically increase or
    /// \c SOURCE_SIZE_UNKNOWN; once it returns \c SOURCE_SIZE_UNKNOWN,
    /// any subsequent call will also result in that value, by the above
    /// definition.
    ///
    /// Before pushing any source, it returns 0.
    ///
    /// \throw None
    size_t getTotalSourceSize() const;

    /// \brief Return the position of lexer in the pushed sources so far.
    ///
    /// This method returns the position in terms of the number of recognized
    /// characters from all sources that have been pushed by the time of the
    /// call.  Conceptually, the position in a single source is the offset
    /// from the beginning of the file or stream to the current "read cursor"
    /// of the lexer.  The return value of this method is the sum of the
    /// positions in all the pushed sources.  If any of the sources has
    /// already been popped, the position of the source at the time of the
    /// pop operation will be used for the calculation.
    ///
    /// If the lexer reaches the end for each of all the pushed sources,
    /// the return value should be equal to that of \c getTotalSourceSize().
    /// It's generally expected that a source is popped when the lexer
    /// reaches the end of the source.  So, when the application of this
    /// class parses all contents of all sources, possibly with multiple
    /// pushes and pops, the return value of this method and
    /// \c getTotalSourceSize() should be identical (unless the latter
    /// returns SOURCE_SIZE_UNKNOWN).  But this is not necessarily
    /// guaranteed as the application can pop a source in the middle of
    /// parsing it.
    ///
    /// Before pushing any source, it returns 0.
    ///
    /// The return values of this method and \c getTotalSourceSize() would
    /// give the caller an idea of the progress of the lexer at the time of
    /// the call.  Note, however, that since it's not predictable whether
    /// more sources will be pushed after the call, the progress determined
    /// this way may not make much sense; it can only give an informational
    /// hint of the progress.
    ///
    /// Note that the conceptual "read cursor" would move backward after a
    /// call to \c ungetToken(), in which case this method will return a
    /// smaller value.  That is, unlike \c getTotalSourceSize(), return
    /// values of this method may not always monotonically increase.
    ///
    /// \throw None
    size_t getPosition() const;

    /// \brief Parse and return another token from the input.
    ///
    /// It reads a bit of the last opened source and produces another token
    /// found in it.
    ///
    /// This method does not provide the strong exception guarantee. Generally,
    /// if it throws, the object should not be used any more and should be
    /// discarded. It was decided all the exceptions thrown from here are
    /// serious enough that aborting the loading process is the only reasonable
    /// recovery anyway, so the strong exception guarantee is not needed.
    ///
    /// \param options The options can be used to modify the tokenization.
    ///     The method can be made reporting things which are usually ignored
    ///     by this parameter. Multiple options can be passed at once by
    ///     bitwise or (eg. option1 | option 2). See description of available
    ///     options.
    /// \return Next token found in the input. Note that the token refers to
    ///     some internal data in the lexer. It is valid only until
    ///     getNextToken or ungetToken is called. Also, the token becomes
    ///     invalid when the lexer is destroyed.
    /// \throw isc::InvalidOperation in case the source is not available. This
    ///     may mean the pushSource() has not been called yet, or that the
    ///     current source has been read past the end.
    /// \throw ReadError in case there's problem reading from the underlying
    ///     source (eg. I/O error in the file on the disk).
    /// \throw std::bad_alloc in case allocation of some internal resources
    ///     or the token fail.
    const MasterToken& getNextToken(Options options = NONE);

    /// \brief Parse the input for the expected type of token.
    ///
    /// This method is a wrapper of the other version, customized for the case
    /// where a particular type of token is expected as the next one.
    /// More specifically, it's intended to be used to get tokens for RDATA
    /// fields.  Since most RDATA types of fixed format, the token type is
    /// often predictable and the method interface can be simplified.
    ///
    /// This method basically works as follows: it gets the type of the
    /// expected token, calls the other version of \c getNextToken(Options),
    /// and returns the token if it's of the expected type (due to the usage
    /// assumption this should be normally the case).  There are some non
    /// trivial details though:
    ///
    /// - If the expected type is MasterToken::QSTRING, both quoted and
    ///   unquoted strings are recognized and returned.
    /// - A string with quotation marks is not recognized as a
    /// - MasterToken::STRING. You have to get it as a
    /// - MasterToken::QSTRING.
    /// - If the optional \c eol_ok parameter is \c true (very rare case),
    ///   MasterToken::END_OF_LINE and MasterToken::END_OF_FILE are recognized
    ///   and returned if they are found instead of the expected type of
    ///   token.
    /// - If the next token is not of the expected type (including the case
    ///   a number is expected but it's out of range), ungetToken() is
    ///   internally called so the caller can re-read that token.
    /// - If other types or errors (such as unbalanced parentheses) are
    ///   detected, the erroneous part isn't "ungotten"; the caller can
    ///   continue parsing after that part.
    ///
    /// In some very rare cases where the RDATA has an optional trailing field,
    /// the \c eol_ok parameter would be set to \c true.  This way the caller
    /// can handle both cases (the field does or does not exist) by a single
    /// call to this method.  In all other cases \c eol_ok should be set to
    /// \c false, and that is the default and can be omitted.
    ///
    /// Unlike the other version of \c getNextToken(Options), this method
    /// throws an exception of type \c LexerError for non fatal errors such as
    /// broken syntax or encountering an unexpected type of token.  This way
    /// the caller can write RDATA parser code without bothering to handle
    /// errors for each field.  For example, pseudo parser code for MX RDATA
    /// would look like this:
    /// \code
    ///    const uint32_t pref =
    ///        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    ///    // check if pref is the uint16_t range; no other check is needed.
    ///    const Name mx(lexer.getNextToken(MasterToken::STRING).getString());
    /// \endcode
    ///
    /// In the case where \c LexerError exception is thrown, it's expected
    /// to be handled comprehensively for the parser of the RDATA or at a
    /// higher layer.  The \c token_ member variable of the corresponding
    /// \c LexerError exception object stores a token of type
    /// \c MasterToken::ERROR that indicates the reason for the error.
    ///
    /// Due to the specific intended usage of this method, only a subset
    /// of \c MasterToken::Type values are acceptable for the \c expect
    /// parameter: \c MasterToken::STRING, \c MasterToken::QSTRING, and
    /// \c MasterToken::NUMBER.  Specifying other values will result in
    /// an \c InvalidParameter exception.
    ///
    /// \throw InvalidParameter The expected token type is not allowed for
    /// this method.
    /// \throw LexerError The lexer finds non fatal error or it finds an
    /// \throw other Anything the other version of getNextToken() can throw.
    ///
    /// \param expect Expected type of token.  Must be either STRING, QSTRING,
    /// or NUMBER.
    /// \param eol_ok \c true iff END_OF_LINE or END_OF_FILE is acceptable.
    /// \return The expected type of token.
    const MasterToken& getNextToken(MasterToken::Type expect,
                                    bool eol_ok = false);

    /// \brief Return the last token back to the lexer.
    ///
    /// The method undoes the lasts call to getNextToken(). If you call the
    /// getNextToken() again with the same options, it'll return the same
    /// token. If the options are different, it may return a different token,
    /// but it acts as if the previous getNextToken() was never called.
    ///
    /// It is possible to return only one token back in time (you can't call
    /// ungetToken() twice in a row without calling getNextToken() in between
    /// successfully).
    ///
    /// It does not work after change of source (by pushSource or popSource).
    ///
    /// \throw isc::InvalidOperation If called second time in a row or if
    ///     getNextToken() was not called since the last change of the source.
    void ungetToken();

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

} // namespace dns
} // namespace isc
#endif  // MASTER_LEXER_H

// Local Variables:
// mode: c++
// End:
