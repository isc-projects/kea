// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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
        if (command_options.parse(argc, argv)) {
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

