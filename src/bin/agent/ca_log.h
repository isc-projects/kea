// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_LOG_H
#define CTRL_AGENT_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <agent/ca_messages.h>

namespace isc {
namespace agent {

/// @brief Control Agent logger.
extern isc::log::Logger agent_logger;

} // namespace isc::agent
} // namespace isc

#endif
