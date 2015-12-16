// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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


/// @brief Returns the default ('kea') root logger name
///
/// @return The default name of root logger.
const std::string& getDefaultRootLoggerName();

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
