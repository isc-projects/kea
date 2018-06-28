// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <d2/d2_log.h>
#include <d2/d2_controller.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <boost/pointer_cast.hpp>
#include <iostream>

using namespace isc::d2;
using namespace isc::process;
using namespace std;

/// This file contains entry point (main() function) for standard DHCP-DDNS
/// process, kea-dhcp-ddns, component of Kea software suite.  It fetches
/// the D2Controller singleton instance and invokes its launch method.
/// The exit value of the program will be EXIT_SUCCESS if there were no
/// errors, EXIT_FAILURE otherwise.
int main(int argc, char* argv[]) {
    int ret = EXIT_SUCCESS;

    // Instantiate/fetch the DHCP-DDNS application controller singleton.
    DControllerBasePtr& controller = D2Controller::instance();

    // Launch the controller passing in command line arguments.
    // Exit program with the controller's return code.
    try  {
        // 'false' value disables test mode.
        controller->launch(argc, argv, false);
    } catch (const VersionMessage& ex) {
        std::string msg(ex.what());
        if (!msg.empty()) {
            std::cout << msg << std::endl;
        }
    } catch (const InvalidUsage& ex) {
        std::string msg(ex.what());
        if (!msg.empty()) {
            std::cerr << msg << std::endl;
        }
        ret = EXIT_FAILURE;
    } catch (const isc::Exception& ex) {
        std::cerr << "Service failed: " << ex.what() << std::endl;
        ret = EXIT_FAILURE;
    }

    boost::dynamic_pointer_cast<D2Controller>(controller)->d2ShutdownHandler();

    return (ret);
}
