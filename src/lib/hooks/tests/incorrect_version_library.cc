// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Incorrect version function test
///
/// This is source of a test library for various test (LibraryManager and
/// HooksManager).  The characteristics of the library produced from this
/// file are:
///
/// - It contains the version() framework function only, which returns an
///   incorrect version number.

#include <config.h>
#include <hooks/hooks.h>

extern "C" {

int version() {
    return (KEA_HOOKS_VERSION + 1);
}

};
