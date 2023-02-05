// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_LOG_H
#define DB_LOG_H

#include <log/macros.h>

#include <map>
#include <mutex>
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
namespace db {

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
extern const int DB_DBG_TRACE_DETAIL;

///@}

/// @brief Common database library logger.
extern isc::log::Logger database_logger;

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
    PGSQL_CREATE_SAVEPOINT,
    PGSQL_ROLLBACK_SAVEPOINT,
    PGSQL_TCP_USER_TIMEOUT_UNSUPPORTED,

    MYSQL_FATAL_ERROR,
    MYSQL_START_TRANSACTION,
    MYSQL_COMMIT,
    MYSQL_ROLLBACK,
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

/// @brief Global database logger stack (initialized to database logger)
extern DbLoggerStack db_logger_stack;

/// @brief Global mutex to protect logger stack
extern std::mutex db_logger_mutex;

/// @brief Check database logger stack
///
/// @throw Unexpected if the stack is empty
void checkDbLoggerStack();

/// @brief log type enumerations for use in DB_LOG specializations
enum log_type_t {
    fatal,
    error,
    warn,
    info,
    debug,
};

/// @brief DB_LOG_* logic
template <log_type_t log_type>
struct DB_LOG {
    /// @brief To preserve the old way of logging, this constructor facilitates
    /// initiating the DB_LOG_* chain call.
    DB_LOG(DbMessageID const message_id, int const debug_level = 0) {
        std::lock_guard<std::mutex> lock(isc::db::db_logger_mutex);
        isc::db::checkDbLoggerStack();
        if (isEnabled()) {
            formatter_ = formatter(message_id, debug_level);
        }
    }

    /// @brief Pass parameters to replace logger placeholders.
    ///
    /// @param first the parameter to be processed now
    /// @param args the parameters to be processes in recursive calls
    ///
    /// @return reference to this object so that these calls may be chained.
    template <typename T, typename... Args>
    DB_LOG& arg(T first, Args... args) {
        formatter_.arg(first);
        return arg(args...);
    }

    /// @brief The last invocation of the arg() which is without parameters.
    ///
    /// Required when using variadic arguments.
    ///
    /// @return reference to this object so that these calls may be chained.
    DB_LOG& arg() {
        return *this;
    }

private:
    /// @brief Initializes the logging formatter.
    ///
    /// @param message_id one of the DbMessageID enums
    /// @param debug_level one of debug levels specified in log_dbglevels.h
    ///
    /// @return the formatter responsible for logging
    isc::log::Logger::Formatter
    formatter(DbMessageID const message_id, int const debug_level = 0);

    /// @brief Check if the logger is ready to log.
    ///
    /// @param debug_level required only for debug log type
    ///
    /// @return true if the logger is enabled, false otherwise
    bool isEnabled(int const debug_level = 0) const;

    /// @brief the formatter responsible for logging
    isc::log::Logger::Formatter formatter_;
};

/// @brief all DB_LOG specializations
/// @{
struct DB_LOG_FATAL : DB_LOG<fatal> {
    DB_LOG_FATAL(DbMessageID const message_id) : DB_LOG(message_id) {
    }
};

struct DB_LOG_ERROR : DB_LOG<error> {
    DB_LOG_ERROR(DbMessageID const message_id) : DB_LOG(message_id) {
    }
};

struct DB_LOG_WARN : DB_LOG<warn> {
    DB_LOG_WARN(DbMessageID const message_id) : DB_LOG(message_id) {
    }
};

struct DB_LOG_INFO : DB_LOG<info> {
    DB_LOG_INFO(DbMessageID const message_id) : DB_LOG(message_id) {
    }
};

struct DB_LOG_DEBUG : DB_LOG<debug> {
    DB_LOG_DEBUG(int const debug_level, DbMessageID const message_id)
        : DB_LOG(message_id, debug_level) {
    }
};
///@}

/// @brief DHCP server database message map
extern const db::DbLogger::MessageMap db_message_map;

/// @brief Database logger translator.
extern db::DbLogger db_logger_translator;

} // namespace db
} // namespace isc

#endif // DB_LOG_H
