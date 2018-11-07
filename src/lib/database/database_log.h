// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DATABASE_LOG_H
#define DATABASE_LOG_H

#include <databaae/db_messages.h>
#include <log/macros.h>

namespace isc {
namespace db {

/// @brief Common database library logger.
extern isc::log::Logger database_logger;

} // end of namespace isc::db
} // end of namespace isc

#endif // DATABASE_LOG_H
