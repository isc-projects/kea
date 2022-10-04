// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at tcp://mozilla.org/MPL/2.0/.

/// Defines the logger used by the libkea-tcp library.

#include <config.h>

#include <tcp/tcp_log.h>

namespace isc {
namespace tcp {

/// @brief Defines the logger used within libkea-tcp library.
isc::log::Logger tcp_logger("tcp");

} // namespace tcp
} // namespace isc

