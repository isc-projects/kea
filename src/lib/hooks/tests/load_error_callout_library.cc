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
/// @brief Error Load Library
///
/// This is a test file for the LibraryManager test.  It produces a library
/// that allows for tests of the basic library manager functions.
///
/// The characteristics of this library are:
///
/// - The "version" and "load" framework functions are supplied.  "version"
///   returns the correct value, but "load" returns an error.

#include <hooks/hooks.h>
#include <iostream>

using namespace isc::hooks;

extern "C" {

// Framework functions

int
version() {
    return (BIND10_HOOKS_VERSION);
}

int load(LibraryHandle&) {
    return (1);
}

};

