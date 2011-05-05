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
/// If there's an .arg call, it replaces a placeholder with the argument
/// converted to string and produces another Formatter. We mark the current
/// Formatter so it won't output anything in it's destructor and the task
/// to do the output is moved onto the new object. Again, the last one in
/// the chain is destroyed without any modification and does the real output.
///
/// Of course, if the logging is turned off, we don't bother with any replacing
/// and just return new empty Formatter. As everything here is in the header
/// file, compiler should be able to easily optimise most of the work with
/// creating and destroying objects and simply do the replacing only.
///
/// User of logging code should not really care much about this class, only
/// call the .arg method to generate the correct output.
///
/// The class is a template to allow easy testing. Also, we want everything
/// here in the header anyway and it doesn't depend on the details of what
/// Logger really is, so it doesn't hurt anything.
template<class Logger> class Formatter {
private:
    /// \brief The logger we will use to output the final message
    Logger* logger_;
    /// \brief Prefix (eg. "ERROR", "DEBUG" or like that)
    const char* prefix_;
    /// \brief The messages with %1, %2... placeholders
    std::string* message_;
    /// \brief Which will be the next placeholder to replace
    const unsigned nextPlaceholder_;
    /// \brief Should we do output?
    mutable bool active_;
    Formatter& operator =(const Formatter& other);
public:
    /// \brief Constructor of "active" formatter
    ///
    /// This will create a formatter in active mode -- the one when it
    /// will generate output.
    ///
    /// It is not expected to be called by user of logging system directly.
    ///
    /// \param prefix The prefix, like "ERROR" or "DEBUG"
    /// \param message The message with placeholders. We take ownership of
    ///     it and we will modify the string. Must not be NULL and it's
    ///     not checked.
    /// \param nextPlaceholder It is the number of next placeholder which
    ///     should be replaced. It should be called with 1, higher numbers
    ///     are used internally in the chain.
    /// \param logger The logger where the final output will go.
    Formatter(const char* prefix, std::string* message,
              const unsigned nextPlaceholder, Logger& logger) :
        logger_(&logger), prefix_(prefix), message_(message),
        nextPlaceholder_(nextPlaceholder), active_(true)
    {
    }
    /// \brief Constructor of "inactive" formatter
    ///
    /// It is not expected to be called by user of the logging system directly.
    ///
    /// This will create a formatter that produces no output.
    Formatter() :
        message_(NULL),
        nextPlaceholder_(0),
        active_(false)
    {
    }

    Formatter(const Formatter& other) :
        logger_(other.logger_), prefix_(other.prefix_),
        message_(other.message_), nextPlaceholder_(other.nextPlaceholder_),
        active_(other.active_)
    {
        other.active_ = false;
    }
    /// \brief Destructor.
    //
    /// This is the place where output happens if the formatter is active.
    ~ Formatter() {
        if (active_) {
            logger_->output(prefix_, *message_);
        }
        delete message_;
    }
    /// \brief Replaces another placeholder
    ///
    /// Replaces another placeholder and returns a new formatter with it.
    /// Deactivates the current formatter. In case the formatter is not active,
    /// only produces another inactive formatter.
    ///
    /// \param arg The argument to place into the placeholder.
    template<class Arg> Formatter arg(const Arg& value) {
        return (arg(boost::lexical_cast<std::string>(value)));
    }
    /// \brief String version of arg.
    Formatter arg(const std::string& arg) {
        if (active_) {
            // FIXME: This logic has a problem. If we had a message like
            // "%1 %2" and called .arg("%2").arg(42), we would get "42 %2".
            // But we consider this to be rare enough not to complicate
            // matters.
            active_ = false;
            replacePlaceholder(message_, arg, nextPlaceholder_);
            std::string *message(message_);
            message_ = NULL;
            try {
                return (Formatter<Logger>(prefix_, message,
                                          nextPlaceholder_ + 1, *logger_));
            }
            // Make sure the memory is not leaked on stuff like bad_alloc
            catch (...) {
                delete message;
                throw;
            }
        } else {
            return (Formatter<Logger>());
        }
    }
};

}
}

#endif
