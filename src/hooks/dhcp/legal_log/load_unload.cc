// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file load_unload.cc Defines the load and unload hooks library functions.

#include <config.h>

#include <hooks/hooks.h>
#include <legal_log_log.h>

#include <iostream>
#include <fstream>
#include <errno.h>

using namespace isc;
using namespace hooks;
using namespace legal_log;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Called by the Hooks library manager when the library is loaded.
///
/// TODO 
/// Failure in either results in a failed return code.
///
/// @return Returns 0 upon success, non-zero upon failure.
int load(LibraryHandle&) {
    // non-zero indicates an error.
    int ret_val = 0;

    try {
        // TODO
    }
    catch (const std::exception& ex) {
        // Log the error and return failure.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_HOOK_LOAD_ERROR)
            .arg(ex.what());
        ret_val = 1;
    }

    return (ret_val);
}

/// @brief Called by the Hooks library manager when the library is unloaded.
///
/// TOFO
///
/// @return Always returns 0.
int unload() {
    try {
        // TODO
    } catch (const std::exception& ex) {
        // On the off chance something goes awry, catch it and log it.
        // @todo Not sure if we should return a non-zero result or not.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_HOOK_UNLOAD_ERROR)
            .arg(ex.what());
    }

    return (0);
}

}
