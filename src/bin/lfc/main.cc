// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <lfc/lfc_controller.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp>
#include <iostream>

using namespace std;
using namespace isc::lfc;

/// This file contains the entry point (main() function) for the
/// standard LFC process, kea-lfc, component of the Kea software suite.
/// It creates an instance of the LFCController class and invokes
/// its launch method.
/// The exit value of the program will be EXIT_SUCCESS if there were no
/// errors, EXIT_FAILURE otherwise.
int main(int argc, char* argv[]) {
    int ret = EXIT_SUCCESS;
    LFCController lfc_controller;

    // Launch the controller passing in command line arguments.
    // Exit program with the controller's return code.
    try  {
        // 'false' value disables test mode.
        lfc_controller.launch(argc, argv, false);

    } catch (const boost::exception& ex) {
        std::cerr << boost::diagnostic_information(ex) << std::endl;
        ret = EXIT_FAILURE;

    } catch (const std::exception& ex) {
        std::cerr << "Service failed: " << ex.what() << std::endl;
        ret = EXIT_FAILURE;
    }

    return (ret);
}
