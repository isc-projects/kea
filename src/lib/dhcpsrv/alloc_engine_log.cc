// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @brief Defines the logger used by the @c isc::dhcp::AllocEngine

#include <config.h>

#include "dhcpsrv/alloc_engine_log.h"

namespace isc {
namespace dhcp {

const int ALLOC_ENGINE_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
const int ALLOC_ENGINE_DBG_RESULTS = isc::log::DBGLVL_TRACE_BASIC_DATA;
const int ALLOC_ENGINE_DBG_TRACE_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;
const int ALLOC_ENGINE_DBG_TRACE_DETAIL_DATA = isc::log::DBGLVL_TRACE_DETAIL_DATA;

isc::log::Logger alloc_engine_logger("alloc-engine");

} // namespace dhcp
} // namespace isc

