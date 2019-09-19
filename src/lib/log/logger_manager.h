// Copyright (C) 2011-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H

#include <exceptions/exceptions.h>
#include <log/logger_specification.h>

#include <boost/noncopyable.hpp>

#include <mutex>

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

class LoggerManager : public boost::noncopyable {
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

    /// \brief Process 'empty' specification
    ///
    /// This will disable any existing output options, and set
    /// the logging to go to the built-in default (stdout).
    /// If the logger has been initialized with buffering enabled,
    /// all log messages up to now shall be printed to stdout.
    ///
    /// This is mainly useful in scenarios where buffering is needed,
    /// but it turns out there are no logging specifications to
    /// handle.
    void process() {
        processInit();
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
    /// Any duplicate log IDs encountered are reported as warning, after which
    /// the global duplicates vector is cleared
    ///
    /// \param root Name of the root logger.  This should be set to the name of
    ///        the program.
    /// \param severity Severity at which to log
    /// \param dbglevel Debug severity (ignored if "severity" is not "DEBUG")
    /// \param file Name of the local message file.  This must be NULL if there
    ///        is no local message file.
    /// \param buffer If true, all log messages will be buffered until one of
    ///        the \c process() methods is called. If false, initial logging
    ///        shall go to the default output (i.e. stdout)
    static void init(const std::string& root,
                    isc::log::Severity severity = isc::log::INFO,
                    int dbglevel = 0, const char* file = NULL,
                    bool buffer = false);

    /// \brief List duplicated log messages.
    ///
    /// Lists the duplicated log messages using warning severity. Then, it
    /// clears the list of duplicated messages. This method is called by the
    /// \c init method and by the \c isc::hooks::LibraryManager when the new
    /// hooks library is loaded.
    static void logDuplicatedMessages();

    /// \brief Reset logging
    ///
    /// Resets logging to whatever was set in the call to init(), expect for
    /// the buffer option.
    static void reset();

    /// \brief Read local message file
    ///
    /// Reads the local message file into the global dictionary, overwriting
    /// existing messages.  If the file contained any message IDs not in the
    /// dictionary, they are listed in a warning message.
    ///
    /// \param file Name of the local message file
    static void readLocalMessageFile(const char* file);

    /// \brief Return a process-global mutex that's used for mutual
    /// exclusion among threads of a single process during logging
    /// calls.
    static std::mutex& getMutex();

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
