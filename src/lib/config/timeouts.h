// Copyright (C) 2018-2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_TIMEOUTS_H
#define CONFIG_TIMEOUTS_H

namespace isc {
namespace config {

// All timeouts provided below are in milliseconds.

/// @brief Timeout for the DHCP server to receive command over the
/// unix domain socket.
constexpr long TIMEOUT_DHCP_SERVER_RECEIVE_COMMAND = 10000;

/// @brief Timeout for the Control Agent to receive command over the
/// RESTful interface.
constexpr long TIMEOUT_AGENT_RECEIVE_COMMAND = 10000;

/// @brief Timeout for the idle connection to be closed.
constexpr long TIMEOUT_AGENT_IDLE_CONNECTION_TIMEOUT = 30000;

/// @brief Timeout for the Control Agent to forward command to a
/// Kea server, e.g. DHCP server.
///
/// This value is high to ensure that the server have enough time
/// to generate large responses, e.g. dump whole lease database.
constexpr long TIMEOUT_AGENT_FORWARD_COMMAND = 60000;

/// @brief Timeout for the HTTP clients awaiting a response to a request.
///
/// This value is high to ensure that the client waits long enough
/// for the fulfilling server to generate a response.  Specified
/// milliseconds.
constexpr long TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST = 10000;


} // end of namespace isc::config
} // end of namespace isc

#endif // CONFIG_TIMEOUTS_H
