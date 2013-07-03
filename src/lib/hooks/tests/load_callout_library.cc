// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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
/// @brief Basic library with load() function
///
/// This is source of a test library for various test (LibraryManager and
/// HooksManager).  The characteristics of the library produced from this
/// file are:
///
/// - The "version" and "load" framework functions are supplied.  One "standard"
///   callout is supplied ("hook_point_one") and two non-standard ones which are
///   registered during the call to "load" on the hooks "hook_point_two" and
///   "hook_point_three". 
///
///   All callouts do trivial calculations, the result of all being called in
///   sequence being
///
///   @f[ ((5 * data_1) + data_2) * data_3 @f]
///
///   ...where data_1, data_2 and data_3 are the values passed in arguments of
///   the same name to the three callouts (data_1 passed to hook_point_one, data_2 to
///   hook_point_two etc.) and the result is returned in the argument "result".

#include <hooks/hooks.h>

using namespace isc::hooks;

extern "C" {

// Callouts

int
context_create(CalloutHandle& handle) {
    handle.setContext("result", static_cast<int>(5));
    handle.setArgument("result", static_cast<int>(5));
    return (0);
}

// First callout adds the passed "data_1" argument to the initialized context
// value of 5. (Note that the value set by context_create is accessed through
// context and not the argument, so checking that context is correctly passed
// between callouts in the same library.)

int
hook_point_one(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_1", data);

    int result;
    handle.getContext("result", result);

    result *= data;
    handle.setArgument("result", result);

    return (0);
}

// Second callout multiplies the current context value by the "data_2"
// argument.

static int
hook_nonstandard_two(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_2", data);

    int result;
    handle.getArgument("result", result);

    result += data;
    handle.setArgument("result", result);

    return (0);
}

// Final callout adds "data_3" to the result.

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
    return (BIND10_HOOKS_VERSION);
}

int load(LibraryHandle& handle) {
    // Register the non-standard functions
    handle.registerCallout("hook_point_two", hook_nonstandard_two);
    handle.registerCallout("hook_point_three", hook_nonstandard_three);

    return (0);
}

};

