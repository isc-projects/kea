// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H 1

#include <stdexcept>
#include <string>
#include <sstream>

namespace isc {

///
/// This is a base class for exceptions thrown from the DNS library module.
/// Normally, the exceptions are thrown via a convenient shortcut macro,
/// @ref isc_throw, which automatically gives trivial parameters for the
/// exception such as the file name and line number where the exception is
/// triggered.
///
class Exception : public std::exception {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// \brief Constructor for a given type for exceptions with file name and
    /// file line number.
    ///
    /// @param file the file name where the exception was thrown.
    /// @param line the line in @ref file where the exception was thrown.
    /// @param what a description (type) of the exception.
    Exception(const char* file, size_t line, const char* what) :
        file_(file), line_(line), what_(what) {}

    /// \brief Constructor for a given type for exceptions with file name and
    /// file line number.
    ///
    /// @param file the file name where the exception was thrown.
    /// @param line the line in @ref file where the exception was thrown.
    /// @param what a description (type) of the exception.
    Exception(const char* file, size_t line, const std::string& what) :
        file_(file), line_(line), what_(what) {}

    /// The destructor
    virtual ~Exception() throw() {}
    //@}
private:
    ///
    /// The assignment operator is intentionally disabled.
    ///
    void operator=(const Exception& src);

public:
    ///
    /// \name Methods Reimplemented against the Standard Exception Class
    ///
    //@{
    /// \brief Returns a C-style character string of the cause of the exception.
    ///
    /// Note: we normally don't use exception specifications, but this is an
    /// "exception" to that policy as it's enforced by the base class.
    ///
    /// @return A C-style character string of the exception cause.
    virtual const char* what() const throw();
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Gets a string describing the cause of the exception.
    ///
    /// @return the cause string.
    const std::string& getMessage() const { return (what_); }

    /// \brief Gets the file name where the exception was thrown.
    ///
    /// @return a C-style string of the file name.
    const char* getFile() const { return (file_); }

    /// \brief Gets the line number of the file where the exception was thrown.
    ///
    /// @return an integer specifying the line number.
    size_t getLine() const { return (line_); }
    //@}

private:
    const char* const file_;
    size_t line_;
    const std::string what_;
};

///
/// \brief A generic exception that is thrown if a parameter given
/// to a method would refer to or modify out-of-range data.
///
class OutOfRange : public Exception {
public:
    OutOfRange(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A generic exception that is thrown if a parameter given
/// to a method is considered invalid in that context.
///
class BadValue : public Exception {
public:
    BadValue(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A generic exception that is thrown when an unexpected
/// error condition occurs.
///
class Unexpected : public Exception {
public:
    Unexpected(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// A shortcut macro to insert known values into exception arguments.
///
/// It allows the \c stream argument to be part of a statement using an
/// \c ostream object and its \c operator<<.  For example,
/// \code int x = 10;
/// isc_throw(SomeException, "Error happened, parameter: " << x);
/// \endcode
/// will throw an exception of class \c SomeException whose \c what string
/// will be <code>"Error happened, parameter: 10"</code>.
///
/// Note: the stream related operations or creation of the exception object
/// may itself throw an exception (specifically \c std::bad_alloc).
/// Even though it should be very rare, we may have to address this issue later.
///
/// Note: in general we hate macros and avoid using it in the code.  This is
/// one of few exceptions to that policy.  inline functions cannot be used
/// for embedding \c __FILE__ and \c __LINE__.  This is the main reason why
/// this is defined as a macro.  The convenience for the ostream is a secondary
/// purpose (if that were the only possible reason we should rather avoid
/// using a macro).
#define isc_throw(type, stream) \
    do { \
        std::ostringstream oss__; \
        oss__ << stream; \
        throw type(__FILE__, __LINE__, oss__.str().c_str()); \
    } while (1)
}
#endif // __EXCEPTIONS_H

// Local Variables: 
// mode: c++
// End: 
