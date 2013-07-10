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

#ifndef HOOKS_H
#define HOOKS_H

#include <hooks/callout_handle.h>
#include <hooks/library_handle.h>

namespace {

// Version 1 of the hooks framework.
const int BIND10_HOOKS_VERSION = 1;

// Names of the framework functions.
const char* const LOAD_FUNCTION_NAME = "load";
const char* const UNLOAD_FUNCTION_NAME = "unload";
const char* const VERSION_FUNCTION_NAME = "version";

// Typedefs for pointers to the framework functions.
typedef int (*version_function_ptr)();
typedef int (*load_function_ptr)(isc::hooks::LibraryHandle&);
typedef int (*unload_function_ptr)();

} // Anonymous namespace

#endif  // HOOKS_H
