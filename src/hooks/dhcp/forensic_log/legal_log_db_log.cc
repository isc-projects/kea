// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the NSAS

#include <config.h>

#include <legal_log_db_log.h>
#include <mutex>

using namespace isc::db;
using namespace std;

namespace isc {

namespace db {

extern mutex db_logger_mutex;

}  // namespace db

namespace legal_log {

const DbLogger::MessageMap legal_log_db_message_map = {
    { DB_INVALID_ACCESS,       LEGAL_LOG_INVALID_ACCESS },

    { PGSQL_DEALLOC_ERROR,     LEGAL_LOG_PGSQL_DEALLOC_ERROR },
    { PGSQL_FATAL_ERROR,       LEGAL_LOG_PGSQL_FATAL_ERROR },
    { PGSQL_START_TRANSACTION, LEGAL_LOG_PGSQL_START_TRANSACTION },
    { PGSQL_COMMIT,            LEGAL_LOG_PGSQL_COMMIT },
    { PGSQL_ROLLBACK,          LEGAL_LOG_PGSQL_ROLLBACK },

    { MYSQL_FATAL_ERROR,       LEGAL_LOG_MYSQL_FATAL_ERROR },
    { MYSQL_START_TRANSACTION, LEGAL_LOG_MYSQL_START_TRANSACTION },
    { MYSQL_COMMIT,            LEGAL_LOG_MYSQL_COMMIT },
    { MYSQL_ROLLBACK,          LEGAL_LOG_MYSQL_ROLLBACK },
};

DbLogger legal_log_db_logger(legal_log_logger, legal_log_db_message_map);

LegalLogDbLogger::LegalLogDbLogger() {
    lock_guard<mutex> lk(db_logger_mutex);
    db_logger_stack.push_back(legal_log_db_logger);
}

LegalLogDbLogger::~LegalLogDbLogger() {
    lock_guard<mutex> lk(db_logger_mutex);
    db_logger_stack.pop_back();
}

} // namespace legal_log
} // namespace isc
