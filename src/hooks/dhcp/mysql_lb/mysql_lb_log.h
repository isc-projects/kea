// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_LB_LOG_H
#define MYSQL_LB_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <mysql_lb_messages.h>

namespace isc {
namespace dhcp {

extern isc::log::Logger mysql_lb_logger;

}  // namespace dhcp
}  // namespace isc

#endif
