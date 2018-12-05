// Copyright (C) 2011-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the Hooks

#include <config.h>

#include <hooks/hooks_log.h>
#include <log/macros.h>

namespace isc {
namespace hooks {

isc::log::Logger hooks_logger("hooks");

isc::log::Logger callouts_logger("callouts");

extern const int HOOKS_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
extern const int HOOKS_DBG_CALLS = isc::log::DBGLVL_TRACE_BASIC_DATA;
extern const int HOOKS_DBG_EXTENDED_CALLS = isc::log::DBGLVL_TRACE_DETAIL_DATA;


} // namespace hooks
} // namespace isc

