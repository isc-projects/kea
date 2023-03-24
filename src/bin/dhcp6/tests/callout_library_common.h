// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
/// The additional marker file is created for the dhcp6_srv_configured hook
/// point. It records the library number and the names of the parameters
/// provided to the callout.
///
/// This file is the common library file for the tests.  It will not compile
/// by itself - it is included into each callout library which specifies the
/// missing constant LIBRARY_NUMBER before the inclusion.

#include <config.h>
#include <hooks/hooks.h>
#include "marker_file.h"

#include <fstream>

extern "C" {

extern int (*do_load)(isc::hooks::LibraryHandle& handle);

extern int (*do_unload)(isc::hooks::LibraryHandle& handle);

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

/// @brief Append argument name passed to the callout to a marker file.
///
/// @param file_name Name of the file to open.
/// @param parameter Parameter name.
///
/// @return 0 on success, non-zero on error.
int appendArgument(const char* file_name, const char* argument) {
    // Open the file and check if successful.
    std::fstream file(file_name, std::fstream::out | std::fstream::app);
    if (!file.good()) {
        return (1);
    }

    // Add the library number to it and close.
    file << argument;
    file.close();

    return (0);
}

// Framework functions
int
version() {
    return (KEA_HOOKS_VERSION);
}

int
load(isc::hooks::LibraryHandle& handle) {
    int result = 0;
    result = appendDigit(LOAD_MARKER_FILE);
    if (result == 0 && do_load) {
        result = do_load(handle);
    }
    return (result);
}

int
unload(isc::hooks::LibraryHandle& handle) {
    int result = 0;
    result = appendDigit(UNLOAD_MARKER_FILE);
    if (result == 0 && do_unload) {
        result = do_unload(handle);
    }
    return (result);
}

};
