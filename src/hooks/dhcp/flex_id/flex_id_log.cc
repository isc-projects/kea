// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the flex-id log hooks library.
#include <config.h>

#include <flex_id_log.h>

namespace isc {
namespace flex_id {

isc::log::Logger flex_id_logger("flex-id-hooks");

} // namespace flex_id
} // namespace isc
