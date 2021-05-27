// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Basic callout library
///
/// This is source of a test library for Control Agent.
///
/// - Only the "version" framework function is supplied.
///
/// - hookpt_one callout is supplied.

#include <config.h>
#include <hooks/hooks.h>

using namespace isc::hooks;
using namespace std;

namespace {

extern "C" {

// Callouts.  All return their result through the "result" argument.

int
context_create(CalloutHandle& handle) {
    handle.setContext("result", static_cast<int>(10));
    handle.setArgument("result", static_cast<int>(10));
    return (0);
}

// First callout adds the passed "integer" argument to the initialized context
// value of 10. (Note that the value set by context_create is accessed through
// context and not the argument, so checking that context is correctly passed
// between callouts in the same library.)

int
hookpt_one(CalloutHandle& handle) {
    int data;
    handle.getArgument("integer", data);

    int result;
    handle.getArgument("result", result);

    result += data;
    handle.setArgument("result", result);

    return (0);
}

// Framework functions.

int
version() {
    return (KEA_HOOKS_VERSION);
}

// load() initializes the user library if the main image was statically linked.
int
load(isc::hooks::LibraryHandle&) {
#ifdef USE_STATIC_LINK
    hooksStaticLinkInit();
#endif
    return (0);
}

}
}

