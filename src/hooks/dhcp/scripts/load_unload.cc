// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file load_unload.cc Defines the load and unload hooks library functions.

#include <config.h>

#include <hooks/hooks.h>
#include <cc/data.h>
#include <scripts_log.h>
#include <scripts_cfg.h>

#include <sstream>
#include <vector>
#include <errno.h>

using namespace std;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::log;
using namespace hooks::scripts;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Called by the Hooks library manager when the library is loaded.
///
/// Instantiates the UserRegistry and opens the outcome file. Failure in
/// either results in a failed return code.
///
/// @return Returns 0 upon success, non-zero upon failure.
int load(LibraryHandle& handle) {
    // non-zero indicates an error.
    int ret_val = 0;

    ScriptsConfigPtr cfg = getScriptsConfig();
    cfg->clear();

    try {
        // zero out the errno to be safe
        errno = 0;

        ConstElementPtr scripts = handle.getParameter("scripts");
        if (!scripts) {
            LOG_ERROR(scripts_logger, SCRIPTS_HOOK_LOAD_ERROR)
                .arg("Mandatory parameter 'scripts' missing");
            return (1);
        }
        if (scripts->getType() != Element::list) {
            LOG_ERROR(scripts_logger, SCRIPTS_HOOK_LOAD_ERROR)
                .arg("Parameter 'scripts' specified, but it's not a list");
            return (1);
        }

        if (scripts->size() == 0) {
            LOG_ERROR(scripts_logger, SCRIPTS_HOOK_LOAD_ERROR)
                .arg("Parameter 'scripts' list specified, but it is empty.");
            return (1);
        }
        
        for (int i = 0; i < scripts->size(); i++) {
            auto s = scripts->get(i);
            if (!s || s->getType() != Element::string) {
                stringstream tmp;
                tmp << "Element " << i << " of the 'scripts' list is either empty or is not a string";
                LOG_ERROR(scripts_logger, SCRIPTS_HOOK_LOAD_ERROR)
                    .arg(tmp.str());
            }
            // Store the script name in our config.
            cfg->scripts_.push_back(s->stringValue());
            LOG_DEBUG(scripts_logger, DBGLVL_START_SHUT, SCRIPTS_HOOK_SCRIPT_ENTRY)
                .arg(s->stringValue());
        }
    }
    catch (const std::exception& ex) {
        // Log the error and return failure.
        LOG_ERROR(scripts_logger, SCRIPTS_HOOK_LOAD_ERROR).arg(ex.what());
        ret_val = 1;
    }

    try {
        ConstElementPtr async = handle.getParameter("async");
        if (async && async->getType() != Element::boolean) {
            LOG_ERROR(scripts_logger, SCRIPTS_HOOK_LOAD_ERROR)
                .arg("Parameter 'async' specified, but it's not a boolean");
            return (1);
        }
        cfg->async_ = async->boolValue();
    } catch (...) {
        // We don't care. The async parameter is optional.
    }

    return (ret_val);
}

/// @brief Called by the Hooks library manager when the library is unloaded.
///
/// Destroys the UserRegistry and closes the outcome file.
///
/// @return Always returns 0.
int unload() {
    try {
        // We only clean the configuration. There's nothing else to clean up.
        ScriptsConfigPtr cfg = getScriptsConfig();
        cfg->clear();
    } catch (const std::exception& ex) {
        // On the off chance something goes awry, catch it and log it.
        // @todo Not sure if we should return a non-zero result or not.
        LOG_ERROR(scripts_logger, SCRIPTS_HOOK_UNLOAD_ERROR).arg(ex.what());
    }

    return (0);
}

}
