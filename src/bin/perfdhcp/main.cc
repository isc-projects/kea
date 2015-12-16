// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <stdint.h>

#include <config.h>
#include <exceptions/exceptions.h>

#include "test_control.h"
#include "command_options.h"

using namespace isc::perfdhcp;

int
main(int argc, char* argv[]) {
    CommandOptions& command_options = CommandOptions::instance();
    std::string diags(command_options.getDiags());
    int ret_code = 0;
    try {
        // If parser returns true it means that user specified
        // 'h' or 'v' command line option. Program shows the
        // help or version message and exits here.
        // The third argument indicates that the command line
        // should be printed when it gets parsed. This is useful
        // in particular when the command line needs to be
        // extracted from the log file.
        if (command_options.parse(argc, argv, true)) {
            return (ret_code);
        }
    } catch(isc::Exception& e) {
        ret_code = 1;
        std::cerr << "Error parsing command line options: "
                  << e.what() << std::endl;
        command_options.usage();
        if (diags.find('e') != std::string::npos) {
            std::cerr << "Fatal error" << std::endl;
        }
        return (ret_code);
    }
    try{
        TestControl& test_control = TestControl::instance();
        ret_code =  test_control.run();
    } catch (isc::Exception& e) {
        ret_code = 1;
        std::cerr << "Error running perfdhcp: " << e.what() << std::endl;
        if (diags.find('e') != std::string::npos) {
            std::cerr << "Fatal error" << std::endl;
        }
    }
    return (ret_code);
}
