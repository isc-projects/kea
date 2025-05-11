// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the legal log hooks library.
#include <config.h>

#include <legal_log_log.h>

namespace isc {
namespace legal_log {

isc::log::Logger legal_log_logger("legal-log-hooks");

} // namespace legal_log
} // namespace isc
