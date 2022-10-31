// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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

extern const int NETCONF_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
extern const int NETCONF_DBG_RESULTS = isc::log::DBGLVL_TRACE_BASIC_DATA;
extern const int NETCONF_DBG_TRACE_DETAIL_DATA =
    isc::log::DBGLVL_TRACE_DETAIL_DATA;

const char* NETCONF_LOGGER_NAME = "netconf";

isc::log::Logger netconf_logger(NETCONF_LOGGER_NAME);

}  // namespace netconf
}  // namespace isc

