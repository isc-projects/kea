// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at tcp://mozilla.org/MPL/2.0/.

#ifndef TCP_LOG_H
#define TCP_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <tcp/tcp_messages.h>

namespace isc {
namespace tcp {

/// Define the logger used within libkea-tcp library.
extern isc::log::Logger tcp_logger;

} // namespace tcp
} // namespace isc

#endif // TCP_LOG_H
