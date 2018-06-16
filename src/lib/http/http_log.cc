// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the top-level component of kea-dhcp-ddns.

#include <config.h>

#include <http/http_log.h>

namespace isc {
namespace http {

/// @brief Defines the logger used within libkea-http library.
isc::log::Logger http_logger("http");

} // namespace http
} // namespace isc

