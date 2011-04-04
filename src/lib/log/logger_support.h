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

#include <string>
#include <log/logger.h>

namespace isc {
namespace log {

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
void initLogger(const std::string& root, isc::log::Severity severity,
    int dbglevel, const char* file);

} // namespace log
} // namespace isc


#endif // __LOGGER_SUPPORT_H
