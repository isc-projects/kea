// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file load_unload.cc Defines the load and unload hooks library functions.

#include <config.h>

#include <hooks/hooks.h>
#include <legal_file.h>
#include <legal_log_log.h>

#include <iostream>
#include <fstream>
#include <errno.h>

using namespace isc;
using namespace hooks;
using namespace legal_log;

/// @brief Pointer to the legal output file instance
LegalFilePtr legal_file;

/// @brief Default path name
const char* default_legal_path = "/tmp";

/// @brief Default base name
const char* default_legal_base = "kea-legal";

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Called by the Hooks library manager when the library is loaded.
///
/// Instantiates the LegalFile and then opens it.
/// @todo once 4297 is completed this needs to be modified to get the
/// path and base name from the library's parameters.
///
/// If the file cannot be opened, the load will fail.
///
/// @return Returns 0 upon success, non-zero upon failure.
int load(LibraryHandle&) {
    // non-zero indicates an error.
    int ret_val = 0;

    try {
        // @todo  get path and base name from parameters
        legal_file.reset(new LegalFile(default_legal_path,
                                       default_legal_base));
        legal_file->open();
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
/// Explicitly destroys the LegalFile instance. Any errors are logged but
/// swallowed.
///
/// @return Always returns 0.
int unload() {
    try {
        // Since it's "global" Let's explicitly destroy it now rather
        // than indeterminately. Note, LegalFile destructor will close
        // the file.
        legal_file.reset();
    } catch (const std::exception& ex) {
        // On the off chance something goes awry, catch it and log it.
        // @todo Not sure if we should return a non-zero result or not.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_HOOK_UNLOAD_ERROR)
            .arg(ex.what());
    }

    return (0);
}

}
