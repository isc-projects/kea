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
/// @brief Basic Callout Library
///
/// This file is built into a shared library and is loaded by the LibraryManager
/// test.  The characteristics of this library are:
///
/// - Only the "version" framework function is supplied.  The other callouts
///   are assumed to be "standard" callouts.
///
/// - A context_create callout is supplied.
///
/// - Three other callouts are supplied.  Two do some trivial calculations
///   on the arguments supplied to it and the context variables.  The
///   third returns the results through the "result" argument, and this is
///   checked by the test program.

#include <hooks/hooks.h>

using namespace isc::hooks;

extern "C" {

int
version() {
    return (BIND10_HOOKS_VERSION);
}

// Callouts

int
context_create(CalloutHandle& handle) {
    handle.setContext("result", static_cast<int>(10));
    return (0);
}

// First callout adds the passed "data_1" argument to the initialized context
// value of 10.

int basic_one(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_1", data);

    int result;
    handle.getContext("result", result);

    result += data;
    handle.setContext("result", result);

    return (0);
}

// Second callout multiplies the current context value by the "data_2"
// argument.

int
basic_two(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_2", data);

    int result;
    handle.getContext("result", result);

    result *= data;
    handle.setContext("result", result);

    return (0);
}

// Final callout returns the value in the context through the "result"
// argument.

int
basic_three(CalloutHandle& handle) {
    int result;
    handle.getContext("result", result);
    handle.setArgument("result", result);

    return (0);
}

};

