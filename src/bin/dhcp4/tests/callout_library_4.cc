// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Callout library for testing the scenarios when a hook library
/// posts some work to the IO service as a result of configuration.
/// Using a callout that always throws we can ensure that the server polls
/// this initial work before it starts working.
///
static const int LIBRARY_NUMBER = 4;

#include <config.h>

#include <asiolink/io_service.h>
#include <dhcp4/tests/callout_library_common.h>
#include <dhcpsrv/srv_config.h>

#include <string>
#include <vector>

using namespace isc::asiolink;
using namespace isc::hooks;

namespace {

// Start service method: always throw.
void start_service(void) {
    isc_throw(isc::Unexpected, "start service failed");
};

} // end anonymous

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

int (*do_load)(LibraryHandle& handle) = do_load_impl;

int (*do_unload)();

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
    for (auto const& arg : args) {
        if (appendArgument(SRV_CONFIG_MARKER_FILE, arg.c_str()) != 0) {
            return (1);
        }
    }

    // Get the IO context to post start_service on it.
    std::string error("");
    IOServicePtr io_context;
    try {
        handle.getArgument("io_context", io_context);
        if (!io_context) {
            error = "null io_context";
        }
        io_context->post(start_service);
    } catch (const std::exception& ex) {
        error = "no io_context in arguments";
    }
    if (!error.empty()) {
        handle.setArgument("error", error);
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
    }

    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
