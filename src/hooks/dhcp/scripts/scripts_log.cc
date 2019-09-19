// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the user check hooks library.
#include <config.h>

#include <scripts_log.h>

namespace hooks {
namespace scripts {

isc::log::Logger scripts_logger("scripts");

} // namespace hooks::scripts
} // namespace hooks
