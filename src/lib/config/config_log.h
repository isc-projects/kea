// Copyright (C) 2011-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_LOG_H
#define CONFIG_LOG_H

#include <log/macros.h>
#include "config_messages.h"

namespace isc {
namespace config {

/// @brief Command processing Logger
///
/// Define the logger used to log messages related to command processing.
/// We could define it in multiple modules, but defining in a single
/// module and linking to it saves time and space.
extern isc::log::Logger command_logger;

// Enumerate configuration elements as they are processed.
extern const int DBG_COMMAND;

} // namespace config
} // namespace isc

#endif // CONFIG_LOG_H
