// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
    { DB_INVALID_ACCESS,        DATABASE_INVALID_ACCESS },

    { PGSQL_DEALLOC_ERROR,      DATABASE_PGSQL_DEALLOC_ERROR },
    { PGSQL_FATAL_ERROR,        DATABASE_PGSQL_FATAL_ERROR },
    { PGSQL_START_TRANSACTION,  DATABASE_PGSQL_START_TRANSACTION },
    { PGSQL_COMMIT,             DATABASE_PGSQL_COMMIT },
    { PGSQL_ROLLBACK,           DATABASE_PGSQL_ROLLBACK },
    { PGSQL_CREATE_SAVEPOINT,   DATABASE_PGSQL_CREATE_SAVEPOINT },
    { PGSQL_ROLLBACK_SAVEPOINT, DATABASE_PGSQL_ROLLBACK_SAVEPOINT },

    { MYSQL_FATAL_ERROR,        DATABASE_MYSQL_FATAL_ERROR },
    { MYSQL_START_TRANSACTION,  DATABASE_MYSQL_START_TRANSACTION },
    { MYSQL_COMMIT,             DATABASE_MYSQL_COMMIT },
    { MYSQL_ROLLBACK,           DATABASE_MYSQL_ROLLBACK },
};

isc::log::Logger database_logger("database");

DbLogger db_logger_translator(database_logger, db_message_map);

DbLoggerStack db_logger_stack = { db_logger_translator };

std::mutex db_logger_mutex;

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

template <>
isc::log::Logger::Formatter
DB_LOG<fatal>::formatter(DbMessageID const message_id,
                         int const /* debug_level = 0 */) {
    return isc::db::db_logger_stack.back().logger_.fatal(
        isc::db::db_logger_stack.back().translateMessage(message_id));
}

template <>
isc::log::Logger::Formatter
DB_LOG<error>::formatter(DbMessageID const message_id,
                         int const /* debug_level = 0 */) {
    return isc::db::db_logger_stack.back().logger_.error(
        isc::db::db_logger_stack.back().translateMessage(message_id));
}

template <>
isc::log::Logger::Formatter
DB_LOG<warn>::formatter(DbMessageID const message_id,
                        int const /* debug_level = 0 */) {
    return isc::db::db_logger_stack.back().logger_.warn(
        isc::db::db_logger_stack.back().translateMessage(message_id));
}

template <>
isc::log::Logger::Formatter
DB_LOG<info>::formatter(DbMessageID const message_id,
                        int const /* debug_level = 0 */) {
    return isc::db::db_logger_stack.back().logger_.info(
        isc::db::db_logger_stack.back().translateMessage(message_id));
}

template <>
isc::log::Logger::Formatter
DB_LOG<debug>::formatter(DbMessageID const message_id,
                         int const debug_level /* = 0 */) {
    return isc::db::db_logger_stack.back().logger_.debug(
        debug_level,
        isc::db::db_logger_stack.back().translateMessage(message_id));
}

template <>
bool
DB_LOG<fatal>::isEnabled(int const /* debug_level = 0 */) const {
    return db_logger_stack.back().logger_.isFatalEnabled();
}

template <>
bool
DB_LOG<error>::isEnabled(int const /* debug_level = 0 */) const {
    return db_logger_stack.back().logger_.isErrorEnabled();
}

template <>
bool
DB_LOG<warn>::isEnabled(int const /* debug_level = 0 */) const {
    return db_logger_stack.back().logger_.isWarnEnabled();
}

template <>
bool
DB_LOG<info>::isEnabled(int const /* debug_level = 0 */) const {
    return db_logger_stack.back().logger_.isInfoEnabled();
}

template <>
bool
DB_LOG<debug>::isEnabled(int const debug_level /* = 0 */) const {
    return db_logger_stack.back().logger_.isDebugEnabled(debug_level);
}

} // namespace db
} // namespace isc
