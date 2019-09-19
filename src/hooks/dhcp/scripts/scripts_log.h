// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SCRIPTS_LOG_H
#define SCRIPTS_LOG_H

#include <log/message_initializer.h>
#include <log/macros.h>
#include <scripts_messages.h>

namespace hooks {
namespace scripts {

/// @brief Scripts Logger
///
/// Define the logger used to log messages.
extern isc::log::Logger scripts_logger;

} // end of namespace scripts
} // end of namespace hooks

#endif // SCRIPTS_LOG_H
