// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Basic unload library
///
/// This is source of a test library for various test (LibraryManager and
/// HooksManager).  The characteristics of the library produced from this
/// file are:
///
/// - The "version" and "unload" framework functions are supplied. "version"
///   returns a valid value and "unload" creates a marker file and returns
///   success.

#include <config.h>

#include <hooks/hooks.h>
#include <hooks/tests/marker_file.h>

#include <fstream>

using namespace isc::hooks;

extern "C" {

// Framework functions

int
version() {
    return (KEA_HOOKS_VERSION);
}

int
unload() {
    // Create the marker file.
    std::fstream marker;
    marker.open(MARKER_FILE, std::fstream::out);
    marker.close();

    return (0);
}

};
