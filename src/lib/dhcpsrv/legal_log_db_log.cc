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

namespace dhcp {

LegalLogDbLogger::LegalLogDbLogger(DbLogger& legal_log_db_logger) {
    lock_guard<mutex> lk(db_logger_mutex);
    db_logger_stack.push_back(legal_log_db_logger);
}

LegalLogDbLogger::~LegalLogDbLogger() {
    lock_guard<mutex> lk(db_logger_mutex);
    db_logger_stack.pop_back();
}

} // namespace dhcp
} // namespace isc
