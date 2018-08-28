// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the NSAS

#include <config.h>

#include <exceptions/exceptions.h>
#include <database/db_log.h>

using namespace isc::log;

namespace isc {
namespace db {

DbLoggerStack db_logger_stack;

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
