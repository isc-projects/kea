// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the Eval (classification) code

#include <config.h>

#include <eval/eval_log.h>

namespace isc {
namespace dhcp {

extern const int EVAL_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
extern const int EVAL_DBG_STACK = isc::log::DBGLVL_TRACE_DETAIL_DATA;

isc::log::Logger eval_logger("eval");

} // namespace dhcp
} // namespace isc

