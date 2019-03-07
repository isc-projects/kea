// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the NSAS

#include <config.h>

#include <exceptions/exceptions.h>
#include <database/db_log.h>
#include <database/db_messages.h>

using namespace isc::log;

namespace isc {
namespace db {

/// @brief Database logging levels.
const int DB_DBG_TRACE_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;

/// @brief Map of translated messages.
const DbLogger::MessageMap db_message_map = {
    { DB_INVALID_ACCESS,       DATABASE_INVALID_ACCESS },

    { PGSQL_DEALLOC_ERROR,     DATABASE_PGSQL_DEALLOC_ERROR },
    { PGSQL_FATAL_ERROR,       DATABASE_PGSQL_FATAL_ERROR },
    { PGSQL_START_TRANSACTION, DATABASE_PGSQL_START_TRANSACTION },
    { PGSQL_COMMIT,            DATABASE_PGSQL_COMMIT },
    { PGSQL_ROLLBACK,          DATABASE_PGSQL_ROLLBACK },

    { MYSQL_FATAL_ERROR,       DATABASE_MYSQL_FATAL_ERROR },
    { MYSQL_START_TRANSACTION, DATABASE_MYSQL_START_TRANSACTION },
    { MYSQL_COMMIT,            DATABASE_MYSQL_COMMIT },
    { MYSQL_ROLLBACK,          DATABASE_MYSQL_ROLLBACK },

    { CQL_DEALLOC_ERROR,       DATABASE_CQL_DEALLOC_ERROR },
    { CQL_CONNECTION_BEGIN_TRANSACTION,
                               DATABASE_CQL_CONNECTION_BEGIN_TRANSACTION },
    { CQL_CONNECTION_COMMIT,   DATABASE_CQL_CONNECTION_COMMIT },
    { CQL_CONNECTION_ROLLBACK, DATABASE_CQL_CONNECTION_ROLLBACK }
};


isc::log::Logger database_logger("database");

DbLogger db_logger_translator(database_logger, db_message_map);

DbLoggerStack db_logger_stack = { db_logger_translator };


const MessageID&
DbLogger::translateMessage(const DbMessageID& id) const {
    try {
        return (map_.at(id));
    } catch (const std::out_of_range&) {
        isc_throw(isc::Unexpected, "can't map message: " << id);
    }
}

void checkDbLoggerStack() {
    if (db_logger_stack.empty()) {
        isc_throw(isc::Unexpected, "database logger stack is empty");
    }
}

} // namespace db
} // namespace isc
