// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCPSRV_DB_LOG_H
#define DHCPSRV_DB_LOG_H

#include <database/db_log.h>

namespace isc {
namespace dhcp {

/// @brief DHCP server database message map
extern const db::DbLogger::MessageMap dhcpsrv_db_message_map;

/// @brief DHCP server database Logger
///
/// It is the default database logger.
extern db::DbLogger dhcpsrv_db_logger;

} // namespace dhcp
} // namespace isc

#endif // DHCPSRV_DB_LOG_H
