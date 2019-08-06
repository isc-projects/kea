// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @brief Defines the logger used by the @c isc::dhcp::HostMgr

#include <config.h>

#include "dhcpsrv/fuzz_log.h"

namespace isc {
namespace dhcp {

extern const int FUZZ_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
extern const int FUZZ_DBG_TRACE_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;

isc::log::Logger fuzz_logger("fuzz");

} // namespace dhcp
} // namespace isc

