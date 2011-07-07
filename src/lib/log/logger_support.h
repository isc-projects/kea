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

#ifndef __LOGGER_SUPPORT_H
#define __LOGGER_SUPPORT_H

#include <unistd.h>

#include <string>
#include <log/logger.h>

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

/// \brief Set "logging initialized" flag
///
/// Sets the state of the "logging initialized" flag.
///
/// \param state State to set the flag to. (This is expected to be "true" - the
///        default - for all code apart from specific unit tests.)
void setLoggingInitialized(bool state = true);



/// \brief Run-Time Initialization
///
/// Performs run-time initialization of the logger in particular supplying:
///
/// - Name of the root logger
/// - The severity (and if applicable, debug level) for the root logger.
/// - Name of a local message file, containing localisation of message text.
///
/// This function is likely to change over time as more debugging options are
/// held in the configuration database.
///
/// \param root Name of the root logger
/// \param severity Severity at which to log
/// \param dbglevel Debug severity (ignored if "severity" is not "DEBUG")
/// \param file Name of the local message file.
void initLogger(const std::string& root,
                isc::log::Severity severity = isc::log::INFO,
                int dbglevel = 0, const char* file = NULL);


/// \brief Run-Time Initialization from Environment
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

void initLogger(isc::log::Severity severity = isc::log::DEBUG,
                int dbglevel = isc::log::MAX_DEBUG_LEVEL);

} // namespace log
} // namespace isc


#endif // __LOGGER_SUPPORT_H
