// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Callout Library
///
/// This is the source of a test library for the DHCP parser tests that
/// specify parameters. It will attempt to obtain its own parameters.

#include <config.h>

#include <hooks/hooks.h>

extern "C" {

// Framework functions
int
version() {
    return (KEA_HOOKS_VERSION);
}

};
