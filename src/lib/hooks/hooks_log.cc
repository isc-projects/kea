// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the Hooks

#include <hooks/hooks_log.h>

namespace isc {
namespace hooks {

isc::log::Logger hooks_logger("hooks");

isc::log::Logger callouts_logger("callouts");

} // namespace hooks
} // namespace isc

