// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <d2/d2_controller.h>
#include <d2/d2_process.h>
#include <d2/spec_config.h>

#include <stdlib.h>

namespace isc {
namespace d2 {

/// @brief Defines the application name, this is passed into base class
/// it may be used to locate configuration data and appears in log statement.
const char* D2Controller::d2_app_name_ = "DhcpDdns";

/// @brief Defines the executable name. This is passed into the base class
const char* D2Controller::d2_bin_name_ = "kea-dhcp-ddns";

DControllerBasePtr&
D2Controller::instance() {
    // If the instance hasn't been created yet, create it.  Note this method
    // must use the base class singleton instance methods.
    if (!getController()) {
        DControllerBasePtr controller_ptr(new D2Controller());
        setController(controller_ptr);
    }

    return (getController());
}

DProcessBase* D2Controller::createProcess() {
    // Instantiate and return an instance of the D2 application process. Note
    // that the process is passed the controller's io_service.
    return (new D2Process(getAppName().c_str(), getIOService()));
}

D2Controller::D2Controller()
    : DControllerBase(d2_app_name_, d2_bin_name_) {
    // set the spec file either from the environment or
    // use the production value.
    if (getenv("KEA_FROM_BUILD")) {
        setSpecFileName(std::string(getenv("KEA_FROM_BUILD")) +
            "/src/bin/d2/dhcp-ddns.spec");
    } else {
        setSpecFileName(D2_SPECFILE_LOCATION);
    }
}

D2Controller::~D2Controller() {
}

}; // end namespace isc::d2
}; // end namespace isc
