// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_CMD_LOG_H
#define LEASE_CMD_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <mysql_cb_messages.h>

namespace isc {
namespace dhcp {

extern isc::log::Logger mysql_cb_logger;

}  // namespace dhcp
}  // namespace isc


#endif
