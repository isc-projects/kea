// Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the NSAS

#include <config.h>

#include "dhcpsrv/dhcpsrv_log.h"

namespace isc {
namespace dhcp {

extern const int DHCPSRV_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
extern const int DHCPSRV_DBG_RESULTS = isc::log::DBGLVL_TRACE_BASIC_DATA;
extern const int DHCPSRV_DBG_TRACE_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;
extern const int DHCPSRV_DBG_TRACE_DETAIL_DATA =
    isc::log::DBGLVL_TRACE_DETAIL_DATA;
extern const int DHCPSRV_DBG_HOOKS = isc::log::DBGLVL_TRACE_BASIC;

isc::log::Logger dhcpsrv_logger("dhcpsrv");

} // namespace dhcp
} // namespace isc

