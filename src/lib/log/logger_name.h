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

#ifndef LOGGER_NAME_H
#define LOGGER_NAME_H

#include <string>

/// \brief Define Name of Root Logger
///
/// In BIND-10, the name root logger of a program is the name of the program
/// itself (in contrast to packages such as log4cplus where the root logger name
//  is something like "root").  These trivial functions allow the setting and
// getting of that name by the logger classes.

namespace isc {
namespace log {

/// \brief Set root logger name
///
/// This function should be called by the program's initialization code before
/// any logging functions are called.
///
/// \param name Name of the root logger.  This should be the program name.
void setRootLoggerName(const std::string& name);

/// \brief Get root logger name
///
/// \return Name of the root logger.
const std::string& getRootLoggerName();

/// \brief Expand logger name
///
/// Given a logger name, returns the fully-expanded logger name.  If the name
/// starts with the root logger name, it is returned as-is.  Otherwise it is
/// prefixed with the root logger name.
///
/// \param name Name to expand.
///
/// \return Fully-expanded logger name.
std::string expandLoggerName(const std::string& name);

}
}

#endif // LOGGER_NAME_H
