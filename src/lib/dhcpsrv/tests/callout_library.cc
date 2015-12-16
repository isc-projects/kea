// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Callout Library
///
/// This is the source of a test library for the basic DHCP parser 
/// tests.  It just has to load - nothing else.

#include <config.h>

#include <hooks/hooks.h>

extern "C" {

// Framework functions
int
version() {
    return (KEA_HOOKS_VERSION);
}

};
