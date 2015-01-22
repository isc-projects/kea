// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <lfc/lfc.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <config.h>
#include <iostream>

using namespace std;

namespace isc {
namespace lfc {

/// @brief Defines the application name, it may be used to locate
/// configuration data and appears in log statements.
const char* lfcController::lfc_app_name_ = "DhcpLFC";

/// @brief Defines the executable name.
const char* lfcController::lfc_bin_name_ = "kea-lfc";

lfcController::lfcController()
    : protocol_version_(0), verbose_(false), config_file_(""), previous_file_(""),
      copy_file_(""), output_file_(""), finish_file_(""), pid_file_("") {
}

lfcController::~lfcController() {
}

void
lfcController::launch(int argc, char* argv[], const bool test_mode) {
  try {
    parseArgs(argc, argv);
  } catch (const InvalidUsage& ex) {
    usage(ex.what());
    throw;  // rethrow it
  }
}

void
lfcController::parseArgs(int argc, char* argv[]) {
    int ch;

    while ((ch = getopt(argc, argv, "46dvVp:i:o:c:f:")) != -1) {
        switch (ch) {
        case '4':
            // Process DHCPv4 lease files.
            protocol_version_ = 4;
            break;

        case '6':
            // Process DHCPv6 lease files.
            protocol_version_ = 6;
            break;

        case 'v':
            // Print just Kea vesion and exit.
            std::cout << getVersion(false) << std::endl;
            exit(EXIT_SUCCESS);

        case 'V':
            // Print extended  Kea vesion and exit.
            std::cout << getVersion(true) << std::endl;
            exit(EXIT_SUCCESS);

        case 'd':
            // Verbose output.
            verbose_ = true;
            break;

        case 'p':
            // Previous file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Previous file name missing");
            }
            previous_file_ = optarg;
            break;

        case 'i':
            // Copy file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Copy file name missing");
            }
            copy_file_ = optarg;
            break;

        case 'o':
            // Output file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Output file name missing");
            }
            output_file_ = optarg;
            break;

        case 'f':
            // Output file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Finish file name missing");
            }
            finish_file_ = optarg;
            break;

        case 'c':
            // Previous file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Configuration file name missing");
            }
            config_file_ = optarg;
            break;

        default:
            usage("");
        }
    }

    // Check for extraneous parameters.
    if (argc > optind) {
        isc_throw(InvalidUsage, "Extraneous parameters.");
    }

    if (protocol_version_ == 0) {
        isc_throw(InvalidUsage, "DHCP version required");
    }

    if (previous_file_.empty()) {
        isc_throw(InvalidUsage, "Previous file not specified");
    }

    if (copy_file_.empty()) {
        isc_throw(InvalidUsage, "Copy file not specified");
    }

    if (output_file_.empty()) {
        isc_throw(InvalidUsage, "Output file not specified");
    }

    if (finish_file_.empty()) {
        isc_throw(InvalidUsage, "Finish file not specified");
    }

    if (config_file_.empty()) {
        isc_throw(InvalidUsage, "Config file not specified");
    }

    // If verbose is set echo the input information
    if (verbose_ == true) {
      std::cerr << "Protocol version:    " << protocol_version_ << std::endl
                << "Previous lease file: " << previous_file_ << std::endl
                << "Copy lease file:     " << copy_file_ << std::endl
                << "Output lease file:   " << output_file_ << std::endl
                << "Finishn file:        " << finish_file_ << std::endl
                << "Config file:         " << config_file_ << std::endl
                << "PID file:            " << pid_file_ << std::endl;
    }
}

void
lfcController::usage(const std::string& text) {
    if (text != "") {
        std::cerr << "Usage error: " << text << std::endl;
    }

    std::cerr << "Usage: " << lfc_bin_name_ << std::endl
              << " [-4|-6] -p file -i file -o file -f file -c file" << std::endl
              << "   -4 or -6 clean a set of v4 or v6 lease files" << std::endl
              << "   -p <file>: previous lease file" << std::endl
              << "   -i <file>: copy of lease file" << std::endl
              << "   -o <file>: output lease file" << std::endl
              << "   -f <file>: finish file" << std::endl
              << "   -c <file>: configuration file" << std::endl
              << "   -v: print version number and exit" << std::endl
              << "   -V: print extended version inforamtion and exit" << std::endl
              << "   -d: optional, verbose output " << std::endl
              << std::endl;
}

std::string
lfcController::getVersion(bool extended) {
    std::stringstream tmp;

    tmp << VERSION;
    if (extended) {
        tmp << std::endl << EXTENDED_VERSION;
    }

    return (tmp.str());
}

}; // namespace isc::lfc
}; // namespace isc
