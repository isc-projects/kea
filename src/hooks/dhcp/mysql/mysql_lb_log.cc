// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <mysql_lb_log.h>

namespace isc {
namespace dhcp {

extern const int MYSQL_LB_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
extern const int MYSQL_LB_DBG_RESULTS = isc::log::DBGLVL_TRACE_BASIC_DATA;
extern const int MYSQL_LB_DBG_TRACE_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;
extern const int MYSQL_LB_DBG_TRACE_DETAIL_DATA =
    isc::log::DBGLVL_TRACE_DETAIL_DATA;
extern const int MYSQL_LB_DBG_HOOKS = isc::log::DBGLVL_TRACE_BASIC;

isc::log::Logger mysql_lb_logger("mysql-lb-hooks");

}  // namespace dhcp
}  // namespace isc
