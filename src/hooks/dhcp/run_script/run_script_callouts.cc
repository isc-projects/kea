// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <hooks/hooks.h>

namespace isc {
namespace run_script {

RunScriptPtr impl;

} // end of namespace flex_option
} // end of namespace isc

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::run_script;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    try {
        impl.reset(new RunScriptImpl());
    } catch (const std::exception& ex) {
        LOG_ERROR(run_script_logger, RUN_SCRIPT_LOAD_ERROR)
            .arg(ex.what());
        return (1);
    }

    LOG_INFO(run_script_logger, RUN_SCRIPT_LOAD);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return always 0.
int unload() {
    impl.reset();
    LOG_INFO(run_script_logger, RUN_SCRIPT_UNLOAD);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"

