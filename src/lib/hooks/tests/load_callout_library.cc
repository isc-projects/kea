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
/// @brief Basic Load Library
///
/// This is a test file for the LibraryManager test.  It produces a library
/// that allows for tests of the basic library manager functions.
///
/// The characteristics of this library are:
///
/// - The "version" and "load" framework functions are supplied.  One "standard"
///   callout is supplied ("lm_one") and two non-standard ones which are
///   registered during the call to "load" on the hooks "lm_two" and
///   "lm_three". 
///
///   All callouts do trivial calculations, the result of the calculation being
///
///   @f[ ((5 * data_1) + data_2) * data_3 @f]
///
///   ...where data_1, data_2 and data_3 are the values passed in arguments
///   of the same name to the three callouts (data_1 passed to lm_one,
///   data_2 to lm_two etc.) and the result is returned in the argument
///   "result".

#include <hooks/hooks.h>
#include <iostream>

using namespace isc::hooks;

extern "C" {

// Callouts

int
context_create(CalloutHandle& handle) {
    handle.setContext("result", static_cast<int>(5));
    handle.setArgument("result", static_cast<int>(5));
    return (0);
}

// First callout multiples the passed "data_1" argument to the initialized
// context value of 5.

int
lm_one(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_1", data);

    int result;
    handle.getContext("result", result);

    result *= data;
    handle.setContext("result", result);
    handle.setArgument("result", result);

    return (0);
}

// Second callout multiplies the current context value by the "data_2"
// argument.

static int
lm_nonstandard_two(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_2", data);

    int result;
    handle.getContext("result", result);

    result += data;
    handle.setContext("result", result);
    handle.setArgument("result", result);

    return (0);
}

// Final callout adds the result in "data_3" and.

static int
lm_nonstandard_three(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_3", data);

    int result;
    handle.getContext("result", result);

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
    handle.registerCallout("lm_two", lm_nonstandard_two);
    handle.registerCallout("lm_three", lm_nonstandard_three);

    return (0);
}

};

