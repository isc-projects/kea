// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

/// @file
/// @brief Marker file callout library
///
/// This is the source of a test library for the DHCP parser and configuration
/// tests.
///
/// To check that they libraries are loaded and unloaded correctly, the load
/// and unload functions in this library maintain two marker files - the load
/// marker file and the unload marker file.  The functions append a single
/// line to the file, creating the file if need be.  In this way, the test code
/// can determine whether the load/unload functions have been run and, if so,
/// in what order.
///
/// This file is the common library file for the tests.  It will not compile
/// by itself - it is included into each callout library which specifies the
/// missing constant LIBRARY_NUMBER before the inclusion.

#include <config.h>
#include <hooks/hooks.h>
#include "marker_file.h"

#include <fstream>

extern "C" {

/// @brief Append digit to marker file
///
/// If the marker file does not exist, create it.  Then append the single
/// digit (given by the constant LIBRARY_NUMBER) defined earlier to it and
/// close the file.
///
/// @param name Name of the file to open
///
/// @return 0 on success, non-zero on error.
int
appendDigit(const char* name) {
    // Open the file and check if successful.
    std::fstream file(name, std::fstream::out | std::fstream::app);
    if (!file.good()) {
        return (1);
    }

    // Add the library number to it and close.
    file << LIBRARY_NUMBER;
    file.close();

    return (0);
}

// Framework functions
int
version() {
    return (KEA_HOOKS_VERSION);
}

int
load(isc::hooks::LibraryHandle&) {
    return (appendDigit(LOAD_MARKER_FILE));
}

int
unload() {
    return (appendDigit(UNLOAD_MARKER_FILE));
}

};
