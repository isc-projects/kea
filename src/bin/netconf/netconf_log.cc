// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file netconf_log.cc
/// Contains the loggers used by the netconf agent.

#include <config.h>

#include <netconf/netconf_log.h>

namespace isc {
namespace netconf {

const char* NETCONF_LOGGER_NAME = "netconf";

isc::log::Logger netconf_logger(NETCONF_LOGGER_NAME);

} // namespace netconf
} // namespace isc

