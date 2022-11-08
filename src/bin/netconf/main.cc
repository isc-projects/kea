// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <netconf/netconf_controller.h>

#include <cstdlib>
#include <iostream>

using namespace isc::netconf;
using namespace isc::process;

using namespace std;

int main(int argc, char* argv[]) {
    int ret = EXIT_SUCCESS;

    // Launch the controller passing in command line arguments.
    // Exit program with the controller's return code.
    try {
        // Instantiate/fetch the application controller singleton.
        DControllerBasePtr& controller = NetconfController::instance();

        // 'false' value disables test mode.
        controller->launch(argc, argv, false);
    } catch (const VersionMessage& ex) {
        string msg(ex.what());
        if (!msg.empty()) {
            cout << msg << endl;
        }
    } catch (const InvalidUsage& ex) {
        string msg(ex.what());
        if (!msg.empty()) {
            cerr << msg << endl;
        }
        ret = EXIT_FAILURE;
    } catch (exception const& ex) {
        cerr << "Service failed: " << ex.what() << endl;
        ret = EXIT_FAILURE;
    } catch (...) {
        cerr << "Service failed" << endl;
        ret = EXIT_FAILURE;
    }

    NetconfController::instance().reset();

    return (ret);
}
