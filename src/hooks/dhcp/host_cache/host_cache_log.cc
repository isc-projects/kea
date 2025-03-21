// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the host-cache log hooks library.
#include <config.h>

#include <host_cache_log.h>

namespace isc {
namespace host_cache {

isc::log::Logger host_cache_logger("host-cache-hooks");

} // namespace host_cache
} // namespace isc
