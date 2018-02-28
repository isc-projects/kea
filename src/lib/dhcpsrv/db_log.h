// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_LOG_H
#define DB_LOG_H

#include <log/macros.h>

#include <map>
#include <list>

/// @file db_log.h
///
/// We want to reuse the database backend connection and exchange code
/// for other uses, in particular for hook libraries. But this code
/// includes some calls to the system logger for debug and uncommon
/// cases and of course we do not want to get log messages from
/// a hook library to seem to come from DHCP server core.
///
/// The solution is to use a database logger which calls the right
/// logger with mapped messages.

namespace isc {
namespace dhcp {

///@{
/// @brief Database logging levels
///
/// Defines the levels used to output debug messages in the database
/// support.  Note that higher numbers equate to more verbose (and detailed)
/// output.

/// @brief Additional information
///
/// Record detailed tracing. This is generally reserved for tracing access to
/// the lease database.
const int DB_DBG_TRACE_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;

///@}

///@{
/// @brief Database messages
///
enum DbMessageID {
    DB_INVALID_ACCESS,

    PGSQL_DEALLOC_ERROR,
    PGSQL_FATAL_ERROR,
    PGSQL_START_TRANSACTION,
    PGSQL_COMMIT,
    PGSQL_ROLLBACK,

    MYSQL_FATAL_ERROR,
    MYSQL_START_TRANSACTION,
    MYSQL_COMMIT,
    MYSQL_ROLLBACK,

    CQL_DEALLOC_ERROR,
    CQL_CONNECTION_BEGIN_TRANSACTION,
    CQL_CONNECTION_COMMIT,
    CQL_CONNECTION_ROLLBACK
};
///@}

/// @brief Database logger class
///
class DbLogger {
public:
    /// @brief Translation map type
    typedef std::map<DbMessageID, isc::log::MessageID> MessageMap;

    /// @brief Constructor
    ///
    /// @param logger logger which will be called
    /// @param map message id translation map
    DbLogger(isc::log::Logger& logger, const MessageMap& map)
        : logger_(logger), map_(map) {
    }

    /// @brief Translate message
    ///
    /// @param id database message id
    /// @return logger message
    /// @throw Unexpected if the id is not in the message map
    const isc::log::MessageID& translateMessage(const DbMessageID& id) const;

    /// @brief The logger
    isc::log::Logger& logger_;

    /// @brief The translation map
    const MessageMap& map_;
};

/// @brief Database logger stack
typedef std::list<DbLogger> DbLoggerStack;

/// @brief Global database logger stack (initialized to dhcpsrv logger)
extern DbLoggerStack db_logger_stack;

/// @brief Check database logger stack
///
/// @throw Unexpected if the stack is empty
void checkDbLoggerStack();

///@{
/// @brief Macros

#define DB_LOG_DEBUG(LEVEL, MESSAGE) \
    checkDbLoggerStack(); \
    if (!db_logger_stack.back().logger_.isDebugEnabled((LEVEL))) { \
    } else \
        db_logger_stack.back().logger_.debug((LEVEL), \
                db_logger_stack.back().translateMessage((MESSAGE)))


#define DB_LOG_INFO(MESSAGE) \
    checkDbLoggerStack(); \
    if (!db_logger_stack.back().logger_.isInfoEnabled()) { \
    } else \
        db_logger_stack.back().logger_.info( \
                db_logger_stack.back().translateMessage((MESSAGE)))

#define DB_LOG_WARN(MESSAGE) \
    checkDbLoggerStack(); \
    if (!db_logger_stack.back().logger_.isWarnEnabled()) { \
    } else \
        db_logger_stack.back().logger_.warn( \
                db_logger_stack.back().translateMessage((MESSAGE)))

#define DB_LOG_ERROR(MESSAGE) \
    checkDbLoggerStack(); \
    if (!db_logger_stack.back().logger_.isErrorEnabled()) { \
    } else \
        db_logger_stack.back().logger_.error( \
                db_logger_stack.back().translateMessage((MESSAGE)))

#define DB_LOG_FATAL(MESSAGE) \
    checkDbLoggerStack(); \
    if (!db_logger_stack.back().logger_.isFatalEnabled()) { \
    } else \
        db_logger_stack.back().logger_.fatal( \
                db_logger_stack.back().translateMessage((MESSAGE)))

///@}

} // namespace dhcp
} // namespace isc

#endif // DB_LOG_H
