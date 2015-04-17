// Copyright (C) 2013,2015  Internet Systems Consortium, Inc. ("ISC")
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
/// @brief Basic callout library
///
/// This is source of a test library for various test (LibraryManager and
/// HooksManager).  The characteristics of the library produced from this
/// file are:
///
/// - Only the "version" framework function is supplied.
///
/// - A context_create callout is supplied.
///
/// - Three "standard" callouts are supplied corresponding to the hooks
///   "hookpt_one", "hookpt_two", "hookpt_three".  All do some trivial
///   calculations on the arguments supplied to it and the context variables,
///   returning intermediate results through the "result" argument. The result
///   of executing all four callouts in order is:
///
///   @f[ (10 + data_1) * data_2 - data_3 @f]
///
///   ...where data_1, data_2 and data_3 are the values passed in arguments of
///   the same name to the three callouts (data_1 passed to hookpt_one, data_2
///   to hookpt_two etc.) and the result is returned in the argument "result".
///
/// - The logger instance is created and some log messages are defined. Some
///   log messages are duplicated purposely, to check that the logger handles
///   the duplicates correctly.

#include <config.h>
#include <hooks/hooks.h>
#include <fstream>
#include <log/logger.h>
#include <log/macros.h>
#include <log/message_initializer.h>

using namespace isc::hooks;
using namespace isc::log;
using namespace std;

namespace {

/// @brief Logger used by the library.
isc::log::Logger logger("bcl");

/// @brief Log messages.
const char* log_messages[] = {
    "BCL_LOAD_START", "basic callout load %1",
    "BCL_LOAD_END", "basic callout load end",
    "BCL_LOAD_END", "duplicate of basic callout load end",
    NULL
};

/// @brief Initializer for log messages.
const MessageInitializer message_initializer(log_messages);

}

extern "C" {

// Callouts.  All return their result through the "result" argument.

int
context_create(CalloutHandle& handle) {
    handle.setContext("result", static_cast<int>(10));
    handle.setArgument("result", static_cast<int>(10));
    return (0);
}

// First callout adds the passed "data_1" argument to the initialized context
// value of 10. (Note that the value set by context_create is accessed through
// context and not the argument, so checking that context is correctly passed
// between callouts in the same library.)

int
hookpt_one(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_1", data);

    int result;
    handle.getArgument("result", result);

    result += data;
    handle.setArgument("result", result);

    return (0);
}

// Second callout multiplies the current context value by the "data_2"
// argument.

int
hookpt_two(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_2", data);

    int result;
    handle.getArgument("result", result);

    result *= data;
    handle.setArgument("result", result);

    return (0);
}

// Final callout subtracts the result in "data_3".

int
hookpt_three(CalloutHandle& handle) {
    int data;
    handle.getArgument("data_3", data);

    int result;
    handle.getArgument("result", result);

    result -= data;
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
    LOG_INFO(logger, "BCL_LOAD_START").arg("argument");
    LOG_INFO(logger, "BCL_LOAD_END");
    return (0);
}

}

