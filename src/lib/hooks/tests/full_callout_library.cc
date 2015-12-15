// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Full callout library
///
/// This is source of a test library for various test (LibraryManager and
/// HooksManager).  The characteristics of the library produced from this
/// file are:
///
/// The characteristics of this library are:
///
/// - All three framework functions are supplied (version(), load() and
///   unload()), with unload() creating a marker file.  The test code checks
///   for the presence of this file, so verifying that unload() has been run.
///
/// - One standard and two non-standard callouts are supplied, with the latter
///   being registered by the load() function.
///
///   All callouts do trivial calculations, the result of all being called in
///   sequence being
///
///   @f[ ((7 * data_1) - data_2) * data_3 @f]
///
///   ...where data_1, data_2 and data_3 are the values passed in arguments of
///   the same name to the three callouts (data_1 passed to hookpt_one, data_2
///   to hookpt_two etc.) and the result is returned in the argument "result".

#include <config.h>

#include <hooks/hooks.h>
#include <hooks/tests/marker_file.h>

#include <fstream>

using namespace isc::hooks;

extern "C" {

// Callouts

int
context_create(CalloutHandle& handle) {
    handle.setContext("result", static_cast<int>(7));
    handle.setArgument("result", static_cast<int>(7));
    return (0);
}

// First callout adds the passed "data_1" argument to the initialized context
// value of 7. (Note that the value set by context_create is accessed through
// context and not the argument, so checking that context is correctly passed
// between callouts in the same library.)

int
hookpt_one(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_1", data);

    int result;
    handle.getArgument("result", result);

    result *= data;
    handle.setArgument("result", result);

    return (0);
}

// Second callout subtracts the passed value of data_2 from the current
// running total.

static int
hook_nonstandard_two(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_2", data);

    int result;
    handle.getArgument("result", result);

    result -= data;
    handle.setArgument("result", result);

    return (0);
}

// Final callout multiplies the current running total by data_3.

static int
hook_nonstandard_three(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_3", data);

    int result;
    handle.getArgument("result", result);

    result *= data;
    handle.setArgument("result", result);

    return (0);
}

// Framework functions

int
version() {
    return (KEA_HOOKS_VERSION);
}

int
load(LibraryHandle& handle) {
    // Initialize if the main image was statically linked
#ifdef USE_STATIC_LINK
    hooksStaticLinkInit();
#endif
    // Register the non-standard functions
    handle.registerCallout("hookpt_two", hook_nonstandard_two);
    handle.registerCallout("hookpt_three", hook_nonstandard_three);

    return (0);
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

