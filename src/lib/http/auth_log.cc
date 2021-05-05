// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the HTTP authentication.

#include <config.h>

#include <http/auth_log.h>

namespace isc {
namespace http {

/// @brief Defines the logger used by the HTTP authentication.
isc::log::Logger auth_logger("auth");

} // namespace http
} // namespace isc
