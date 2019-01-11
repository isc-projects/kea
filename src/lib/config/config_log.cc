// Copyright (C) 2011-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the config lib

#include <config.h>

#include "config/config_log.h"

namespace isc {
namespace config {

isc::log::Logger command_logger("commands");

extern const int DBG_COMMAND = isc::log::DBGLVL_COMMAND;

} // namespace nsas
} // namespace isc

