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

#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H

#include "exceptions/exceptions.h"
#include <log/logger_specification.h>

// Generated if, when updating the logging specification, an unknown
// destination is encountered.
class UnknownLoggingDestination : public isc::Exception {
public:
    UnknownLoggingDestination(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

namespace isc {
namespace log {

class LoggerManagerImpl;

/// \brief Logger Manager
///
/// The logger manager class exists to process the set of logger specifications
/// and use them to set up the logging in the program appropriately.
///
/// To isolate the underlying implementation from basic processing, the
/// LoggerManager is implemented using the "pimpl" idiom.

class LoggerManager {
public:
    /// \brief Constructor
    LoggerManager();

    /// \brief Destructor
    ~LoggerManager();

    /// \brief Process Specifications
    ///
    /// Replaces the current logging configuration by the one given.
    ///
    /// \param start Iterator pointing to the start of the collection of
    ///        logging specifications.
    /// \param finish Iterator pointing to the end of the collection of
    ///        logging specification.
    template <typename T>
    void process(T start, T finish) {
        processInit();
        if (start == finish) {
            // empty iterator; set defaults
            const LoggerSpecification spec;
            processSpecification(spec);
        } else {
            for (T i = start; i != finish; ++i) {
                processSpecification(*i);
            }
        }
        processEnd();
    }

    /// \brief Process a single specification
    ///
    /// A convenience function for a single specification.
    ///
    /// \param spec Specification to process
    void process(const LoggerSpecification& spec) {
        processInit();
        processSpecification(spec);
        processEnd();
    }

    /// \brief Run-Time Initialization
    ///
    /// Performs run-time initialization of the logger system, in particular
    /// supplying the root logger name and name of a replacement message file.
    ///
    /// This must be the first logging function called in the program.  If
    /// an attempt is made to log a message before this is function is called,
    /// the results will be dependent on the underlying logging package.
    ///
    /// \param root Name of the root logger.  This should be set to the name of
    ///        the program.
    /// \param severity Severity at which to log
    /// \param dbglevel Debug severity (ignored if "severity" is not "DEBUG")
    /// \param file Name of the local message file.  This must be NULL if there
    ///        is no local message file.
    static void init(const std::string& root,
                    isc::log::Severity severity = isc::log::INFO,
                    int dbglevel = 0, const char* file = NULL);

    /// \brief Reset logging
    ///
    /// Resets logging to whatever was set in the call to init().
    static void reset();

    /// \brief Read local message file
    ///
    /// Reads the local message file into the global dictionary, overwriting
    /// existing messages.  If the file contained any message IDs not in the
    /// dictionary, they are listed in a warning message.
    ///
    /// \param file Name of the local message file
    static void readLocalMessageFile(const char* file);

private:
    /// \brief Initialize Processing
    ///
    /// Initializes the processing of a list of specifications by resetting all
    /// loggers to their defaults, which is to pass the message to their
    /// parent logger.  (Except for the root logger, where the default action is
    /// to output the message.)
    void processInit();

    /// \brief Process Logging Specification
    ///
    /// Processes the given specification.  It is assumed at this point that
    /// either the logger does not exist or has been made inactive.
    void processSpecification(const LoggerSpecification& spec);

    /// \brief End Processing
    ///
    /// Place holder for finish processing.
    /// TODO: Check that the root logger has something enabled
    void processEnd();

    // Members
    LoggerManagerImpl*  impl_;      ///< Pointer to implementation
};

} // namespace log
} // namespace isc


#endif // LOGGER_MANAGER_H
