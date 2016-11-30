// Copyright (C) 2013-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_LOG_H
#define D2_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <process/process_messages.h>

namespace isc {
namespace d2 {

/// Define the loggers used within libkea-process library.
extern isc::log::Logger dctl_logger;

} // namespace d2
} // namespace isc

#endif // D2_LOG_H
