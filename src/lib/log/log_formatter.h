// Copyright (C) 2011-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOG_FORMATTER_H
#define LOG_FORMATTER_H

#include <cstddef>
#include <string>
#include <iostream>

#include <exceptions/exceptions.h>
#include <log/logger_level.h>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

namespace isc {
namespace log {

/// \brief Format Failure
///
/// This exception is used to wrap a bad_lexical_cast exception thrown during
/// formatting an argument.

class FormatFailure : public isc::Exception {
public:
    FormatFailure(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};


/// \brief Mismatched Placeholders
///
/// This exception is used when the number of placeholders do not match
/// the number of arguments passed to the formatter.

class MismatchedPlaceholders : public isc::Exception {
public:
    MismatchedPlaceholders(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};


///
/// \brief Internal excess placeholder checker
///
/// This is used internally by the Formatter to check for excess
/// placeholders (and fewer arguments).
void
checkExcessPlaceholders(std::string& message, unsigned int placeholder);

///
/// \brief The internal replacement routine
///
/// This is used internally by the Formatter. Replaces a placeholder
/// in the message by replacement. If the placeholder is not found,
/// it adds a complain at the end.
void
replacePlaceholder(std::string& message, const std::string& replacement,
                   const unsigned placeholder);

///
/// \brief The log message formatter
///
/// This class allows us to format logging messages conveniently. We
/// call something like logger.warn(WARN_MSG).arg(15).arg(dnsMsg). This
/// outputs some text with placeholders replaced by the arguments, if
/// the logging verbosity is at WARN level or more.
///
/// To make this work, we use the Formatter. The warn (or whatever logging
/// function) returns a Formatter object. That one holds the string to be
/// output with the placeholders. It also remembers if there should be any
/// output at all (eg. if the logging is enabled for this level). When there's
/// no .arg call on the object, it is destroyed right away and we use the
/// destructor to output the text (but only in case we should output anything).
///
/// If there's an .arg call, we return reference to the same object, so another
/// .arg can be called on it. After the last .arg call is done, the object is
/// destroyed and, again, we can produce the output.
///
/// Of course, if the logging is turned off, we don't bother with any replacing
/// and just return.
///
/// User of logging code should not really care much about this class, only
/// call the .arg method to generate the correct output.
///
/// The class is a template to allow easy testing. Also, we want everything
/// here in the header anyway and it doesn't depend on the details of what
/// Logger really is, so it doesn't hurt anything.
///
/// Also, if you are interested in the internals, you might find the copy
/// constructor a bit strange. It deactivates the original formatter. We don't
/// really want to support copying of the Formatter by user, but C++ needs a
/// copy constructor when returning from the logging functions, so we need one.
/// And if we did not deactivate the original Formatter, that one would get
/// destroyed before any call to .arg, producing an output, and then the one
/// the .arg calls are called on would get destroyed as well, producing output
/// again. So, think of this behavior as soul moving from one to another.
template<class Logger> class Formatter {
private:
    /// \brief The logger we will use to output the final message.
    ///
    /// If NULL, we are not active and should not produce anything.
    mutable Logger* logger_;

    /// \brief Message severity
    Severity severity_;

    /// \brief The messages with %1, %2... placeholders
    boost::shared_ptr<std::string> message_;

    /// \brief Which will be the next placeholder to replace
    unsigned nextPlaceholder_;


public:
    /// \brief Constructor of "active" formatter
    ///
    /// This will create a formatter. If the arguments are set, it
    /// will be active (will produce output). If you leave them all as NULL,
    /// it will create an inactive Formatter -- one that'll produce no output.
    ///
    /// It is not expected to be called by user of logging system directly.
    ///
    /// \param severity The severity of the message (DEBUG, ERROR etc.)
    /// \param message The message with placeholders. We take ownership of
    ///     it and we will modify the string. Must not be NULL unless
    ///     logger is also NULL, but it's not checked.
    /// \param logger The logger where the final output will go, or NULL
    ///     if no output is wanted.
    Formatter(const Severity& severity = NONE,
              boost::shared_ptr<std::string> message = boost::make_shared<std::string>(),
              Logger* logger = NULL) :
        logger_(logger), severity_(severity), message_(message),
        nextPlaceholder_(0) {
    }

    /// \brief Copy constructor
    ///
    /// "Control" is passed to the created object in that it is the created object
    /// that will have responsibility for outputting the formatted message - the
    /// object being copied relinquishes that responsibility.
    Formatter(const Formatter& other) :
        logger_(other.logger_), severity_(other.severity_),
        message_(other.message_), nextPlaceholder_(other.nextPlaceholder_) {
        other.logger_ = NULL;
    }

    /// \brief Destructor.
    //
    /// This is the place where output happens if the formatter is active.
    ~Formatter() {
        if (logger_) {
            try {
                checkExcessPlaceholders(*message_, ++nextPlaceholder_);
                logger_->output(severity_, *message_);
            } catch (...) {
                // Catch and ignore all exceptions here.
            }
        }
    }

    /// \brief Assignment operator
    ///
    /// Essentially the same function as the assignment operator - the object being
    /// assigned to takes responsibility for outputting the message.
    Formatter& operator =(const Formatter& other) {
        if (&other != this) {
            logger_ = other.logger_;
            severity_ = other.severity_;
            message_ = other.message_;
            nextPlaceholder_ = other.nextPlaceholder_;
            other.logger_ = NULL;
        }

        return *this;
    }

    /// \brief Replaces another placeholder
    ///
    /// Replaces another placeholder and returns a new formatter with it.
    /// Deactivates the current formatter. In case the formatter is not active,
    /// only produces another inactive formatter.
    ///
    /// \param value The argument to place into the placeholder.
    template<class Arg> Formatter& arg(const Arg& value) {
        if (logger_) {
            try {
                return (arg(boost::lexical_cast<std::string>(value)));
            } catch (const boost::bad_lexical_cast& ex) {
                // The formatting of the log message got wrong, we don't want
                // to output it.
                deactivate();
                // A bad_lexical_cast during a conversion to a string is
                // *extremely* unlikely to fail.  However, there is nothing
                // in the documentation that rules it out, so we need to handle
                // it.  As it is a potentially very serious problem, throw the
                // exception detailing the problem with as much information as
                // we can.  (Note that this does not include 'value' -
                // boost::lexical_cast failed to convert it to a string, so an
                // attempt to do so here would probably fail as well.)
                isc_throw(FormatFailure, "bad_lexical_cast in call to "
                          "Formatter::arg(): " << ex.what());
            }
        } else {
            return (*this);
        }
    }

    /// \brief String version of arg.
    ///
    /// \param arg The text to place into the placeholder.
    Formatter& arg(const std::string& arg) {
        if (logger_) {
            // Note that this method does a replacement and returns the
            // modified string. If there are multiple invocations of arg() (e.g.
            // logger.info(msgid).arg(xxx).arg(yyy)...), each invocation
            // operates on the string returned by the previous one. This
            // sequential operation means that if we had a message like "%1 %2",
            // and called .arg("%2").arg(42), we would get "42 42"; the first
            // call replaces the %1" with "%2" and the second replaces all
            // occurrences of "%2" with 42. (Conversely, the sequence
            // .arg(42).arg("%1") would return "42 %1" - there are no recursive
            // replacements).
            try {
                replacePlaceholder(*message_, arg, ++nextPlaceholder_);
            } catch (...) {
                // Something went wrong here, the log message is broken, so
                // we don't want to output it, nor we want to check all the
                // placeholders were used (because they won't be).
                deactivate();
                throw;
            }
        }
        return (*this);
    }

    /// \brief Turn off the output of this logger.
    ///
    /// If the logger would output anything at the end, now it won't.
    /// Also, this turns off the strict checking of placeholders, if
    /// it is compiled in.
    ///
    /// The expected use is when there was an exception processing
    /// the arguments for the message.
    void deactivate() {
        if (logger_) {
            message_.reset();
            logger_ = NULL;
        }
    }
};

} // namespace log
} // namespace isc

#endif
