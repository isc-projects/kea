// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the NSAS

#include <config.h>

#include <dhcpsrv/dhcpsrv_db_log.h>
#include <dhcpsrv/dhcpsrv_log.h>

using namespace isc::db;

namespace isc {
namespace dhcp {

const DbLogger::MessageMap dhcpsrv_db_message_map = {
    { DB_INVALID_ACCESS,       DHCPSRV_INVALID_ACCESS },

    { PGSQL_DEALLOC_ERROR,     DHCPSRV_PGSQL_DEALLOC_ERROR },
    { PGSQL_FATAL_ERROR,       DHCPSRV_PGSQL_FATAL_ERROR },
    { PGSQL_START_TRANSACTION, DHCPSRV_PGSQL_START_TRANSACTION },
    { PGSQL_COMMIT,            DHCPSRV_PGSQL_COMMIT },
    { PGSQL_ROLLBACK,          DHCPSRV_PGSQL_ROLLBACK },

    { MYSQL_FATAL_ERROR,       DHCPSRV_MYSQL_FATAL_ERROR },
    { MYSQL_START_TRANSACTION, DHCPSRV_MYSQL_START_TRANSACTION },
    { MYSQL_COMMIT,            DHCPSRV_MYSQL_COMMIT },
    { MYSQL_ROLLBACK,          DHCPSRV_MYSQL_ROLLBACK },

    { CQL_DEALLOC_ERROR,       DHCPSRV_CQL_DEALLOC_ERROR },
    { CQL_CONNECTION_BEGIN_TRANSACTION,
                               DHCPSRV_CQL_CONNECTION_BEGIN_TRANSACTION },
    { CQL_CONNECTION_COMMIT,   DHCPSRV_CQL_CONNECTION_COMMIT },
    { CQL_CONNECTION_ROLLBACK, DHCPSRV_CQL_CONNECTION_ROLLBACK }
};

DbLogger dhcpsrv_db_logger(dhcpsrv_logger, dhcpsrv_db_message_map);

// Do this initialization here!
//DbLoggerStack db_logger_stack = { dhcpsrv_db_logger };


} // namespace dhcp
} // namespace isc
