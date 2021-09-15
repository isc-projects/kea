// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_controller.h>
#include <exceptions/exceptions.h>
#include <cstdlib>
#include <iostream>

using namespace isc::agent;
using namespace isc::process;

int main(int argc, char* argv[]) {
    int ret = EXIT_SUCCESS;

    // Launch the controller passing in command line arguments.
    // Exit program with the controller's return code.
    try {
        // Instantiate/fetch the application controller singleton.
        DControllerBasePtr& controller = CtrlAgentController::instance();

        // 'false' value disables test mode.
        ret = controller->launch(argc, argv, false);
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
    } catch (const std::exception& ex) {
        std::cerr << "Service failed: " << ex.what() << std::endl;
        ret = EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Service failed" << std::endl;
        ret = EXIT_FAILURE;
    }

    CtrlAgentController::instance().reset();

    return (ret);
}
