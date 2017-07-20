// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLIENT_LOG_H
#define CLIENT_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <client/client_messages.h>

namespace isc {
namespace client {

/// Define the loggers for the Kea client logging
extern isc::log::Logger client_logger;

} // namespace d2
} // namespace isc

#endif // CLIENT_LOG_H
