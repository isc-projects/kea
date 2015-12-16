// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOGGER_SUPPORT_H
#define LOGGER_SUPPORT_H

#include <unistd.h>

#include <string>
#include <log/logger.h>
#include <log/logger_unittest_support.h>

/// \file
/// \brief Logging initialization functions
///
/// Contains a set of functions relating to logging initialization that are
/// used by the production code.

namespace isc {
namespace log {

/// \brief Is logging initialized?
///
/// As some underlying logging implementations can behave unpredictably if they
/// have not been initialized when a logging function is called, their
/// initialization state is tracked.  The logger functions will check this flag
/// and throw an exception if logging is not initialized at that point.
///
/// \return true if logging has been initialized, false if not
bool isLoggingInitialized();

/// \brief Set state of "logging initialized" flag
///
/// \param state State to set the flag to. (This is expected to be "true" - the
///        default - for all code apart from specific unit tests.)
void setLoggingInitialized(bool state = true);

/// \brief Run-time initialization
///
/// Performs run-time initialization of the logger in particular supplying:
///
/// - Name of the root logger
/// - The severity (and if applicable, debug level) for the root logger.
/// - Name of a local message file, containing localization of message text.
///
/// This function is likely to change over time as more debugging options are
/// held in the configuration database.
///
/// \param root Name of the root logger
/// \param severity Severity at which to log
/// \param dbglevel Debug severity (ignored if "severity" is not "DEBUG")
/// \param file Name of the local message file.
/// \param buffer If true, all log messages will be buffered until one of
///        the \c process() methods is called. If false, initial logging
///        shall go to the default output (i.e. stdout)
void initLogger(const std::string& root,
                isc::log::Severity severity = isc::log::INFO,
                int dbglevel = 0, const char* file = NULL,
                bool buffer = false);

/// \brief Reset root logger characteristics
///
/// This is a simplified interface into the resetting of the characteristics
/// of the root logger.  It is aimed for use in unit tests and initial
/// phase of bring up before logging configuration is parsed and applied.
/// It uses KEA_LOGGER_DESTINATION environment variable to specify
/// logging destination.
/// @param verbose defines whether logging should be verbose or not
void setDefaultLoggingOutput(bool verbose = true);


} // namespace log
} // namespace isc

#endif // LOGGER_SUPPORT_H
