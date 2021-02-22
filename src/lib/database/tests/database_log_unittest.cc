// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/db_log.h>

#include <gtest/gtest.h>

using isc::db::DB_DBG_TRACE_DETAIL;
using isc::db::DB_INVALID_ACCESS;
using isc::db::DB_LOG_FATAL;
using isc::db::DB_LOG_ERROR;
using isc::db::DB_LOG_WARN;
using isc::db::DB_LOG_INFO;
using isc::db::DB_LOG_DEBUG;
using isc::db::db_logger_mutex;

namespace {

/// Test that the mutex unlocks after a call to DB_LOG.
/// Let's use DB_INVALID_ACCESS as an example for all.
TEST(DatabaseLogTest, mutexIsolation) {
    DB_LOG_FATAL(DB_INVALID_ACCESS).arg("hello");
    EXPECT_TRUE(db_logger_mutex.try_lock());
    db_logger_mutex.unlock();

    DB_LOG_ERROR(DB_INVALID_ACCESS).arg("hello");
    EXPECT_TRUE(db_logger_mutex.try_lock());
    db_logger_mutex.unlock();

    DB_LOG_WARN(DB_INVALID_ACCESS).arg("hello");
    EXPECT_TRUE(db_logger_mutex.try_lock());
    db_logger_mutex.unlock();

    DB_LOG_INFO(DB_INVALID_ACCESS).arg("hello");
    EXPECT_TRUE(db_logger_mutex.try_lock());
    db_logger_mutex.unlock();

    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, DB_INVALID_ACCESS).arg("hello");
    EXPECT_TRUE(db_logger_mutex.try_lock());
    db_logger_mutex.unlock();
}

}  // namespace
