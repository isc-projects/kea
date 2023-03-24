// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Callout library for testing execution of the dhcp4_srv_configured
/// hook point.
///
static const int LIBRARY_NUMBER = 3;

#include <config.h>

#include <dhcp4/tests/callout_library_common.h>
#include <dhcpsrv/srv_config.h>

#include <string>
#include <vector>

using namespace isc::hooks;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

int
do_load_impl(LibraryHandle& handle) {
    // Determine if this callout is configured to fail.
    isc::dhcp::SrvConfigPtr config;
    isc::data::ConstElementPtr const& parameters(handle.getParameters());
    isc::data::ConstElementPtr mode_element(parameters ? parameters->get("mode") : 0);
    std::string mode(mode_element ? mode_element->stringValue() : "");
    if (mode == "fail-on-load") {
        return (1);
    }
    return (0);
}

int (*do_load)(isc::hooks::LibraryHandle& handle) = do_load_impl;

int (*do_unload)(isc::hooks::LibraryHandle& handle);

/// @brief Callout which appends library number and provided arguments to
/// the marker file for dhcp4_srv_configured callout.
///
/// @param handle callout handle passed to the callout.
///
/// @return 0 on success, 1 otherwise.
int
dhcp4_srv_configured(CalloutHandle& handle) {

    // Append library number.
    if (appendDigit(SRV_CONFIG_MARKER_FILE)) {
        return (1);
    }

    // Append argument names.
    std::vector<std::string> args = handle.getArgumentNames();
    for (auto arg = args.begin(); arg != args.end(); ++arg) {
        if (appendArgument(SRV_CONFIG_MARKER_FILE, arg->c_str()) != 0) {
            return (1);
        }
    }

    // Determine if this callout is configured to fail.
    isc::dhcp::SrvConfigPtr config;
    handle.getArgument("server_config", config);
    isc::data::ConstElementPtr mode_element(config ? config->toElement() ?
        config->toElement()->find("Dhcp4/hooks-libraries") ?
        config->toElement()->find("Dhcp4/hooks-libraries")->get(0) ?
        config->toElement()->find("Dhcp4/hooks-libraries")->get(0)->get("parameters") ?
        config->toElement()->find("Dhcp4/hooks-libraries")->get(0)->get("parameters")->get("mode")
        : 0 : 0 : 0 : 0 : 0);
    std::string mode(mode_element ? mode_element->stringValue() : "");
    if (mode == "fail-without-error") {
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
    } else if (mode == "fail-with-error") {
        std::string error("user explicitly configured me to fail");
        handle.setArgument("error", error);
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
    }

    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 0 which means not compatible with multi-threading.
int multi_threading_compatible() {
    return (0);
}

} // end extern "C"
