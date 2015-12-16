// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOGGER_UNITTEST_SUPPORT_H
#define LOGGER_UNITTEST_SUPPORT_H

#include <string>
#include <log/logger.h>

/// \file
/// \brief Miscellaneous logging functions used by the unit tests.
///
/// As the configuration database is usually unavailable during unit tests,
/// the functions defined here allow a limited amount of logging configuration
/// through the use of environment variables

namespace isc {
namespace log {

/// \brief Run-Time Initialization for Unit Tests from Environment
///
/// Performs run-time initialization of the logger via the setting of
/// environment variables.  These are:
///
/// - KEA_LOGGER_ROOT\n
/// Name of the root logger.  If not given, the string "kea" will be used.
///
/// - KEA_LOGGER_SEVERITY\n
/// Severity of messages that will be logged.  This must be one of the strings
/// "DEBUG", "INFO", "WARN", "ERROR", "FATAL" or "NONE". (Must be upper case
/// and must not contain leading or trailing spaces.)  If not specified (or if
/// specified but incorrect), the default passed as argument to this function
/// (currently DEBUG) will be used.
///
/// - KEA_LOGGER_DBGLEVEL\n
/// Ignored if the level is not DEBUG, this should be a number between 0 and
/// 99 indicating the logging severity.  The default is 0.  If outside these
/// limits or if not a number, The value passed to this function (default
/// of MAX_DEBUG_LEVEL) is used.
///
/// - KEA_LOGGER_LOCALMSG\n
/// If defined, the path specification of a file that contains message
/// definitions replacing ones in the default dictionary.
///
/// - KEA_LOGGER_DESTINATION\n
/// If defined, the destination of the logging output.  This can be one of:
///   - \c stdout Send output to stdout.
///   - \c stderr Send output to stderr
///   - \c syslog Send output to syslog using the facility local0.
///   - \c syslog:xxx  Send output to syslog, using the facility xxx. ("xxx"
///     should be one of the syslog facilities such as "local0".)  There must
///     be a colon between "syslog" and "xxx
///   - \c other Anything else is interpreted as the name of a file to which
///     output is appended.  If the file does not exist, it is created.
///
/// Any errors in the settings cause messages to be output to stderr.
///
/// This function is aimed at test programs, allowing the default settings to
/// be overridden by the tester.  It is not intended for use in production
/// code.
///
/// @note: Do NOT use this function in production code as it creates
/// lockfile in the build dir. That's ok for tests, but not
/// ok for production code.
///
/// @todo: Rename. This function overloads the initLogger() function that can
///       be used to initialize production programs.  This may lead to confusion.
void initLogger(isc::log::Severity severity = isc::log::DEBUG,
                int dbglevel = isc::log::MAX_DEBUG_LEVEL);


/// \brief Obtains logging severity from KEA_LOGGER_SEVERITY
///
/// Support function called by the unit test logging initialization code.
/// It returns the logging severity defined by KEA_LOGGER_SEVERITY.  If
/// not defined it returns the default passed to it.
///
/// \param defseverity Default severity used if KEA_LOGGER_SEVERITY is not
//         defined.
///
/// \return Severity to use for the logging.
isc::log::Severity keaLoggerSeverity(isc::log::Severity defseverity);


/// \brief Obtains logging debug level from KEA_LOGGER_DBGLEVEL
///
/// Support function called by the unit test logging initialization code.
/// It returns the logging debug level defined by KEA_LOGGER_DBGLEVEL.  If
/// not defined, it returns the default passed to it.
///
/// N.B. If there is an error, a message is written to stderr and a value
/// related to the error is used. (This is because (a) logging is not yet
/// initialized, hence only the error stream is known to exist, and (b) this
/// function is only used in unit test logging initialization, so incorrect
/// selection of a level is not really an issue.)
///
/// \param defdbglevel Default debug level to be used if KEA_LOGGER_DBGLEVEL
///        is not defined.
///
/// \return Debug level to use.
int keaLoggerDbglevel(int defdbglevel);

} // namespace log
} // namespace isc



#endif // LOGGER_UNITTEST_SUPPORT_H
