// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/legal_log_db_log.h>
#include <pgsql_fb_log.h>

using namespace isc::db;

namespace isc {
namespace dhcp {

extern const int PGSQL_FB_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;
extern const int PGSQL_FB_DBG_RESULTS = isc::log::DBGLVL_TRACE_BASIC_DATA;
extern const int PGSQL_FB_DBG_TRACE_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;
extern const int PGSQL_FB_DBG_TRACE_DETAIL_DATA =
    isc::log::DBGLVL_TRACE_DETAIL_DATA;
extern const int PGSQL_FB_DBG_HOOKS = isc::log::DBGLVL_TRACE_BASIC;

isc::log::Logger pgsql_fb_logger("pgsql-fb-hooks");

isc::log::Logger pgsql_legal_log_logger("pgsql-legal-log");

const isc::db::DbLogger::MessageMap pgsql_legal_log_db_message_map = {
    { DB_INVALID_ACCESS,       LEGAL_LOG_PGSQL_INVALID_ACCESS },

    { PGSQL_DEALLOC_ERROR,     LEGAL_LOG_PGSQL_DEALLOC_ERROR },
    { PGSQL_FATAL_ERROR,       LEGAL_LOG_PGSQL_FATAL_ERROR },
    { PGSQL_START_TRANSACTION, LEGAL_LOG_PGSQL_START_TRANSACTION },
    { PGSQL_COMMIT,            LEGAL_LOG_PGSQL_COMMIT },
    { PGSQL_ROLLBACK,          LEGAL_LOG_PGSQL_ROLLBACK },
};

isc::db::DbLogger pgsql_legal_log_db_logger(pgsql_legal_log_logger, pgsql_legal_log_db_message_map);

}  // namespace dhcp
}  // namespace isc
