// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Error load library
///
/// This is source of a test library for various test (LibraryManager and
/// HooksManager).  The characteristics of the library produced from this
/// file are:
///
/// - All framework functions are supplied.  "version" returns the correct
///   value, but "load" and unload return an error.

#include <config.h>
#include <hooks/hooks.h>

using namespace isc::hooks;

extern "C" {

// Framework functions

int
version() {
    return (KEA_HOOKS_VERSION);
}

int
load(LibraryHandle&) {
    return (1);
}

int
unload() {
    return (1);
}

};

