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

#ifndef __LOGGER_UNITTEST_SUPPORT_H
#define __LOGGER_UNITTEST_SUPPORT_H

#include <string>
#include <log/logger.h>

// Note: this file holds logging functions used by unit tests.

namespace isc {
namespace log {

/// \brief Run-Time Initialization for Unit Tests from Environment
///
/// Performs run-time initialization of the logger via the setting of
/// environment variables.  These are:
///
/// - B10_LOGGER_ROOT\n
/// Name of the root logger.  If not given, the string "bind10" will be used.
///
/// - B10_LOGGER_SEVERITY\n
/// Severity of messages that will be logged.  This must be one of the strings
/// "DEBUG", "INFO", "WARN", "ERROR", "FATAL" or "NONE". (Must be upper case
/// and must not contain leading or trailing spaces.)  If not specified (or if
/// specified but incorrect), the default passed as argument to this function
/// (currently DEBUG) will be used.
///
/// - B10_LOGGER_DBGLEVEL\n
/// Ignored if the level is not DEBUG, this should be a number between 0 and
/// 99 indicating the logging severity.  The default is 0.  If outside these
/// limits or if not a number, The value passed to this function (default
/// of MAX_DEBUG_LEVEL) is used.
///
/// - B10_LOGGER_LOCALMSG\n
/// If defined, the path specification of a file that contains message
/// definitions replacing ones in the default dictionary.
///
/// - B10_LOGGER_DESTINATION\n
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
/// TODO: Rename. This function overloads the initLogger() function that can
///       be used to initialize production programs.  This may lead to confusion.
void initLogger(isc::log::Severity severity = isc::log::DEBUG,
                int dbglevel = isc::log::MAX_DEBUG_LEVEL);


/// \brief Logging Severity from B10_LOGGER_SEVERITY
///
/// Support function called by the unit test logging initialization code.
/// It returns the logging severity defined by B10_LOGGER_SEVERITY.  If
/// not defined it returns the default passed to it.
///
/// \param defseverity Default severity used if B10_LOGGER_SEVERITY is not
//         defined.
///
/// \return Severity to use for the logging.
isc::log::Severity b10LoggerSeverity(isc::log::Severity defseverity);


/// \brief Logging Debug Level from B10_LOGGER_DBGLEVEL
///
/// Support function called by the unit test logging initialization code.
/// It returns the logging debug level defined by B10_LOGGER_DBGLEVEL.  If
/// not defined, it returns the default passed to it.
///
/// N.B. If there is an error, a message is written to stderr and a value
/// related to the error is used. (This is because (a) logging is not yet
/// initialized, hence only the error stream is known to exist, and (b) this
/// function is only used in unit test logging initialization, so incorrect
/// selection of a level is not really an issue.)
///
/// \param defdbglevel Default debug level to be used if B10_LOGGER_DBGLEVEL
///        is not defined.
///
/// \return Debug level to use.
int b10LoggerDbglevel(int defdbglevel);


/// \brief Reset Root Logger Characteristics
///
/// This is a simplified interface into the resetting of the characteristics
/// of the root logger.  It is aimed for use in unit tests and resets the
/// characteristics of the root logger to use a severity, debug level and
/// destination set by the environment variables B10_LOGGER_SEVERITY,
/// B10_LOGGER_DBGLEVEL and B10_LOGGER_DESTINATION.
void
resetUnitTestRootLogger();

} // namespace log
} // namespace isc



#endif // __LOGGER_UNITTEST_SUPPORT_H
