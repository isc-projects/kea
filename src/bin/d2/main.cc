// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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
#include <d2/d2_log.h>
#include <d2/d2_controller.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>

#include <iostream>

using namespace isc::d2;
using namespace std;

/// This file contains entry point (main() function) for standard DHCP-DDNS
/// process, b10-dhcp-ddns, component for BIND10 framework.  It fetches
/// the D2Controller singleton instance and invokes its launch method.
/// The exit value of the program will the return value of launch:
/// d2::NORMAL_EXIT - Indicates normal shutdown.
/// d2::INVALID_USAGE - Indicates invalid command line.
/// d2::PROCESS_INIT_ERROR  - Failed to create and initialize application
/// process
/// d2::SESSION_START_ERROR  - Could not connect to BIND10 (integrated mode
/// only).
/// d2::RUN_ERROR - A fatal error occurred in the application process
/// d2::SESSION_END_ERROR - Error occurred disconnecting from BIND10 (integrated
/// mode only).
int
main(int argc, char* argv[]) {

    // Instantiate/fetch the DHCP-DDNS application controller singleton.
    DControllerBasePtr& controller = D2Controller::instance();

    // Launch the controller passing in command line arguments.
    // Exit program with the controller's return code.
    return (controller->launch(argc, argv));
}
