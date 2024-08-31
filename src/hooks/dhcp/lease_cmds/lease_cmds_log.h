// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_CMD_LOG_H
#define LEASE_CMD_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <lease_cmds_messages.h>

namespace isc {
namespace lease_cmds {

/// @brief Logging level used to log successful commands.
extern const int LEASE_CMDS_DBG_COMMAND_DATA;

extern isc::log::Logger lease_cmds_logger;

} // end of isc::lease_cmds
} // end of isc namespace


#endif
