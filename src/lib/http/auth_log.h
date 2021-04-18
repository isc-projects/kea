// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef AUTH_LOG_H
#define AUTH_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <http/auth_messages.h>

namespace isc {
namespace http {

/// Define the HTTP authentication logger.
extern isc::log::Logger auth_logger;

} // namespace http
} // namespace isc

#endif // AUTH_LOG_H
