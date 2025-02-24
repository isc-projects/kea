// Copyright (C) 2019-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/legal_log_db_log.h>
#include <mysql_fb_log.h>

using namespace isc::db;

namespace isc {
namespace dhcp {

extern const int MYSQL_FB_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
extern const int MYSQL_FB_DBG_RESULTS = isc::log::DBGLVL_TRACE_BASIC_DATA;
extern const int MYSQL_FB_DBG_TRACE_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;
extern const int MYSQL_FB_DBG_TRACE_DETAIL_DATA =
    isc::log::DBGLVL_TRACE_DETAIL_DATA;
extern const int MYSQL_FB_DBG_HOOKS = isc::log::DBGLVL_TRACE_BASIC;

isc::log::Logger mysql_fb_logger("mysql-fb-hooks");

isc::log::Logger mysql_legal_log_logger("mysql-legal-log");

const isc::db::DbLogger::MessageMap mysql_legal_log_db_message_map = {
    { DB_INVALID_ACCESS,       LEGAL_LOG_MYSQL_INVALID_ACCESS },

    { MYSQL_FATAL_ERROR,       LEGAL_LOG_MYSQL_FATAL_ERROR },
    { MYSQL_START_TRANSACTION, LEGAL_LOG_MYSQL_START_TRANSACTION },
    { MYSQL_COMMIT,            LEGAL_LOG_MYSQL_COMMIT },
    { MYSQL_ROLLBACK,          LEGAL_LOG_MYSQL_ROLLBACK },
};

isc::db::DbLogger mysql_legal_log_db_logger(mysql_legal_log_logger, mysql_legal_log_db_message_map);

}  // namespace dhcp
}  // namespace isc
