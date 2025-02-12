// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DDNS_TUNING_LOG_H
#define DDNS_TUNING_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <log/log_dbglevels.h>
#include <ddns_tuning_messages.h>

namespace isc {
namespace ddns_tuning {

extern isc::log::Logger ddns_tuning_logger;

} // end of namespace ddns_tuning
} // end of namespace isc
#endif
