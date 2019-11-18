// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BOOTP_LOG_H
#define BOOTP_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <log/log_dbglevels.h>
#include <bootp_messages.h>

namespace isc {
namespace bootp {

extern isc::log::Logger bootp_logger;

} // end of namespace bootp
} // end of namespace isc
#endif
