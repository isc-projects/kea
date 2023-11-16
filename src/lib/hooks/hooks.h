// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKS_H
#define HOOKS_H

#include <hooks/callout_handle.h>
#include <hooks/library_handle.h>

namespace {

// Version 20401 of the hooks framework, set for Kea 2.4.1
const int KEA_HOOKS_VERSION = 20401;

// Names of the framework functions.
const char* const LOAD_FUNCTION_NAME = "load";
const char* const UNLOAD_FUNCTION_NAME = "unload";
const char* const VERSION_FUNCTION_NAME = "version";
const char* const MULTI_THREADING_COMPATIBLE_FUNCTION_NAME =
    "multi_threading_compatible";

// Typedefs for pointers to the framework functions.
typedef int (*version_function_ptr)();
typedef int (*load_function_ptr)(isc::hooks::LibraryHandle&);
typedef int (*unload_function_ptr)();
typedef int (*multi_threading_compatible_function_ptr)();

} // Anonymous namespace

namespace isc {
namespace hooks {

/// @brief User-Library Initialization for Statically-Linked Kea
///
/// If Kea is statically-linked, a user-created hooks library will not be
/// able to access symbols in it.  In particular, it will not be able to access
/// singleton objects.
///
/// The hooks framework handles some of this.  For example, although there is
/// a singleton ServerHooks object, hooks framework objects store a reference
/// to it when they are created.  When the user library needs to register a
/// callout (which requires access to the ServerHooks information), it accesses
/// the ServerHooks object through a pointer passed from the Kea image.
///
/// The logging framework is more problematical. Here the code is partly
/// statically linked (the Kea logging library) and partly shared (the
/// log4cplus).  The state of the former is not accessible to the user library,
/// but the state of the latter is.  So within the user library, we need to
/// initialize the Kea logging library but not initialize the log4cplus
/// code.  Some of the initialization is done when the library is loaded, but
/// other parts are done at run-time.
///
/// This function - to be called by the user library code in its load() function
/// when running against a statically linked Kea - initializes the Kea
/// logging library.  In particular, it loads the message dictionary with the
/// text of the Kea messages.
///
/// @note This means that the virtual address space is loaded with two copies
/// of the message dictionary.  Depending on how the user libraries are linked,
/// loading multiple user libraries may involve loading one message dictionary
/// per library.

void hooksStaticLinkInit();

} // namespace hooks
} // namespace isc

#endif  // HOOKS_H
