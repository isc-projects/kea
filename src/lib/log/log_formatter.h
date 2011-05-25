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

#ifndef __LOG_FORMATTER_H
#define __LOG_FORMMATER_H

#include <string>
#include <boost/lexical_cast.hpp>
#include <log/logger_level.h>

namespace isc {
namespace log {

/// \brief The internal replacement routine
///
/// This is used internally by the Formatter. Replaces a placeholder
/// in the message by replacement. If the placeholder is not found,
/// it adds a complain at the end.
void
replacePlaceholder(std::string* message, const std::string& replacement,
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
/// again. So, think of this behaviour as soul moving from one to another.
template<class Logger> class Formatter {
private:
    /// \brief The logger we will use to output the final message.
    ///
    /// If NULL, we are not active and should not produce anything.
    mutable Logger* logger_;

    /// \brief Message severity
    Severity severity_;

    /// \brief The messages with %1, %2... placeholders
    std::string* message_;

    /// \brief Which will be the next placeholder to replace
    unsigned nextPlaceholder_;

    Formatter& operator =(const Formatter& other);

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
    Formatter(const Severity& severity = NONE, std::string* message = NULL,
              Logger* logger = NULL) :
        logger_(logger), severity_(severity), message_(message),
        nextPlaceholder_(0)
    {
    }

    Formatter(const Formatter& other) :
        logger_(other.logger_), severity_(other.severity_),
        message_(other.message_), nextPlaceholder_(other.nextPlaceholder_)
    {
        other.logger_ = false;
    }
    /// \brief Destructor.
    //
    /// This is the place where output happens if the formatter is active.
    ~ Formatter() {
        if (logger_) {
            logger_->output(severity_, *message_);
            delete message_;
        }
    }
    /// \brief Replaces another placeholder
    ///
    /// Replaces another placeholder and returns a new formatter with it.
    /// Deactivates the current formatter. In case the formatter is not active,
    /// only produces another inactive formatter.
    ///
    /// \param arg The argument to place into the placeholder.
    template<class Arg> Formatter& arg(const Arg& value) {
        if (logger_) {
            return (arg(boost::lexical_cast<std::string>(value)));
        } else {
            return (*this);
        }
    }
    /// \brief String version of arg.
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
            replacePlaceholder(message_, arg, ++nextPlaceholder_ );
        }
        return (*this);
    }
};

}
}

#endif
