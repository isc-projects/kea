// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <perfdhcp/avalanche_scen.h>
#include <perfdhcp/basic_scen.h>
#include <perfdhcp/command_options.h>

#include <exceptions/exceptions.h>

#include <iostream>
#include <stdint.h>

using namespace isc::perfdhcp;

int
main(int argc, char* argv[]) {
    CommandOptions command_options;
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
        command_options.usage();
        std::cerr << "\nERROR: parsing command line options: "
                  << e.what() << std::endl;
        if (diags.find('e') != std::string::npos) {
            std::cerr << "Fatal error" << std::endl;
        }
        return (ret_code);
    }
    try{
        auto scenario = command_options.getScenario();
        PerfSocket socket(command_options);
        if (scenario == Scenario::BASIC) {
            BasicScen scen(command_options, socket);
            ret_code = scen.run();
        } else if (scenario == Scenario::AVALANCHE) {
            AvalancheScen scen(command_options, socket);
            ret_code = scen.run();
        }
    } catch (std::exception& e) {
        ret_code = 1;
        std::cerr << "\nERROR: running perfdhcp: " << e.what() << std::endl;
        if (diags.find('e') != std::string::npos) {
            std::cerr << "Fatal error" << std::endl;
        }
    }
    return (ret_code);
}
