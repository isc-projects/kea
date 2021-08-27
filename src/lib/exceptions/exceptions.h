// Copyright (C) 2009-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H 1

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
    /// @param line the line in \a file where the exception was thrown.
    /// @param what a description (type) of the exception.
    Exception(const char* file, size_t line, const char* what);

    /// \brief Constructor for a given type for exceptions with file name and
    /// file line number.
    ///
    /// @param file the file name where the exception was thrown.
    /// @param line the line in \a file where the exception was thrown.
    /// @param what a description (type) of the exception.
    Exception(const char* file, size_t line, const std::string& what);

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

    /// \brief Returns a C-style character string of the cause of exception.
    ///
    /// With verbose set to true, also returns file name and line numbers.
    /// Note that we can't simply define a single what() method with parameters,
    /// as the compiler would complain that it shadows the base class method.
    ///
    /// \param verbose if set to true, filename and line number will be added.
    /// \return A C-style character string of the exception cause.
    virtual const char* what(bool verbose) const throw();
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

    /// Specifies the filename where this exception was raised
    const char* const file_;

    /// Specifies the line number where this exception was raised
    size_t line_;

    /// Specifies actual content of the exception
    const std::string what_;

    /// Specifies actual context of the exception (with file:line added)
    std::string verbose_what_;
};

/// \brief A generic exception that is thrown if a parameter given
/// to a method would refer to or modify out-of-range data.
class OutOfRange : public Exception {
public:
    OutOfRange(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief A generic exception that is thrown if a parameter given
/// to a method or function is considered invalid and no other specific
/// exceptions are suitable to describe the error.
class InvalidParameter : public Exception {
public:
    InvalidParameter(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief A generic exception that is thrown if a parameter given
/// to a method is considered invalid in that context.
class BadValue : public Exception {
public:
    BadValue(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief A generic exception that is thrown if a function is called
/// in a prohibited way.
///
/// For example, this can happen if a class method is called when the object's
/// state does not allow that particular method.
class InvalidOperation : public Exception {
public:
    InvalidOperation(const char* file, size_t line, const char* what) :
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
/// \brief A generic exception that is thrown when a function is
/// not implemented.
///
/// This may be due to unfinished implementation or in case the
/// function isn't even planned to be provided for that situation,
/// i.e. not yet implemented or not supported.
class NotImplemented : public Exception {
public:
    NotImplemented(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A generic exception that is thrown when an object can
/// not be found.
class NotFound : public Exception {
public:
    NotFound(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief Exception thrown when a worker thread is trying to stop or pause the
/// respective thread pool (which would result in a dead-lock).
class MultiThreadingInvalidOperation : public Exception {
public:
    MultiThreadingInvalidOperation(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {};
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

///
/// Similar as isc_throw, but allows the exception to have one additional
/// parameter (the stream/text goes first)
#define isc_throw_1(type, stream, param1) \
    do { \
        std::ostringstream oss__; \
        oss__ << stream; \
        throw type(__FILE__, __LINE__, oss__.str().c_str(), param1); \
    } while (1)

///
/// Similar as isc_throw, but allows the exception to have two additional
/// parameters (the stream/text goes first)
#define isc_throw_2(type, stream, param1, param2) \
    do { \
        std::ostringstream oss__; \
        oss__ << stream; \
        throw type(__FILE__, __LINE__, oss__.str().c_str(), param1, param2); \
    } while (1)

///
/// Similar as isc_throw, but allows the exception to have three additional
/// parameters (the stream/text goes first)
#define isc_throw_3(type, stream, param1, param2, param3) \
    do { \
        std::ostringstream oss__; \
        oss__ << stream; \
        throw type(__FILE__, __LINE__, oss__.str().c_str(), param1, param2,\
                   param3); \
    } while (1)

///
/// Similar as isc_throw, but allows the exception to have four additional
/// parameters (the stream/text goes first)
#define isc_throw_4(type, stream, param1, param2, param3, param4) \
    do { \
        std::ostringstream oss__; \
        oss__ << stream; \
        throw type(__FILE__, __LINE__, oss__.str().c_str(), param1, param2,\
                   param3, param4); \
    } while (1)

}
#endif // EXCEPTIONS_H

// Local Variables:
// mode: c++
// End:
