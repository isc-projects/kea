// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/hooks.h>

namespace isc {
namespace limits {

extern "C" {

/// @brief Version function required by Hooks API for compatibility checks
int
version() {
    return (KEA_HOOKS_VERSION);
}

}  // extern "C"

}  // namespace limits
}  // namespace isc
