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

#ifndef __LOGGER_MANAGER_H
#define __LOGGER_MANAGER_H

#include <log/logger_specification.h>

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
    /// Given a list of logger specifications, disables all current logging
    /// and resets the properties of each logger to that given.
    ///
    /// \param start Iterator pointing to the start of the collection of
    ///        logging specifications.
    /// \param finish Iterator pointing to the end of the collection of
    ///        logging specification.
    template <typename T>
    void process(T start, T finish) {
        processInit();
        for (T i = start; i != finish; ++i) {
            processSpecification(*i);
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

    /// \brief Initialization
    ///
    /// Static method for initializing the whole of the logging system.  This
    /// must be called before anything else.
    static void init();


private:
    /// \brief Initialize Processing
    ///
    /// Initializes the processing of a list of specifications by resetting all
    /// loggers to their defaults.  Note that loggers aren't removed as unless
    /// a previously-enabled logger is re-enabled, it becomes inactive.
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


#endif // __LOGGER_MANAGER_H
