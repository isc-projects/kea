// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the radius log hooks library.
#include <config.h>

#include <radius_log.h>

namespace isc {
namespace radius {

isc::log::Logger radius_logger("radius-hooks");

} // namespace radius
} // namespace isc
