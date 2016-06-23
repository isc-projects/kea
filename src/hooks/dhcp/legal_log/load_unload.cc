// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file load_unload.cc Defines the load and unload hooks library functions.

#include <config.h>

#include <cc/data.h>
#include <hooks/hooks.h>
#include <legal_log_log.h>
#include <rotating_file.h>

using namespace isc;
using namespace hooks;
using namespace legal_log;

/// @brief Pointer to the legal output file instance
RotatingFilePtr legal_file;

/// @brief Default path name
const char* default_legal_path = LEGAL_LOG_DIR;

/// @brief Default base name
const char* default_legal_base = "kea-legal";

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Called by the Hooks library manager when the library is loaded.
///
/// Instantiates the RotatingFile and then opens it.  It supports the following
/// parameters via the Hook Library Parameter mechanism::
///
/// "path" - Directory in which the legal file(s) will be written.  The default
/// value is "<prefix>/kea/var".  The directory must exist.
///
/// "base-name" - An arbitrary value which is used in conjunction with current
/// system date to form the current legal file name.  It defaults to "kea-legal".
///
/// Legal file names will have the form:
///
///     <path>/<base-name>.<CCYYMMDD>.txt
///
/// @return Returns 0 upon success, non-zero if the legal file cannot be opened
int load(LibraryHandle& handle) {
    // non-zero indicates an error.
    int ret_val = 0;

    try {
        std::string path(LEGAL_LOG_DIR);
        std::string base(default_legal_base);

        data::ConstElementPtr param = handle.getParameter("path");
        if (param && !param->stringValue().empty()) {
            path = param->stringValue();
        }

        param = handle.getParameter("base-name");
        if (param && !param->stringValue().empty()) {
            base = param->stringValue();
        }

        legal_file.reset(new RotatingFile(path, base));
        legal_file->open();
    }
    catch (const std::exception& ex) {
        // Log the error and return failure.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_LOAD_ERROR)
            .arg(ex.what());
        ret_val = 1;
    }

    return (ret_val);
}

/// @brief Called by the Hooks library manager when the library is unloaded.
///
/// Explicitly destroys the RotatingFile instance. Any errors are logged but
/// swallowed.
///
/// @return Always returns 0.
int unload() {
    try {
        // Since it's "global" Let's explicitly destroy it now rather
        // than indeterminately. Note, RotatingFile destructor will close
        // the file.
        legal_file.reset();
    } catch (const std::exception& ex) {
        // On the off chance something goes awry, catch it and log it.
        // @todo Not sure if we should return a non-zero result or not.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_UNLOAD_ERROR)
            .arg(ex.what());
    }

    return (0);
}

}
