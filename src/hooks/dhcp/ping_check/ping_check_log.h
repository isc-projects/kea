// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PING_CHECK_LOG_H
#define PING_CHECK_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <log/log_dbglevels.h>
#include <ping_check_messages.h>
#include <iostream>

namespace isc {
namespace ping_check {

extern isc::log::Logger ping_check_logger;

} // end of namespace ping_check
} // end of namespace isc
#endif
