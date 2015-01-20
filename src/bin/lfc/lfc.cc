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

#include <config.h>
#include <lfc/lfc.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
//#include <dhcpsrv/cfgmgr.h>
#include <iostream>

using namespace std;

namespace isc {
namespace lfc {

/// @brief Defines the application name, it may be used to locate
/// configuration data and appears in log statements.
const char* lfc::lfc_app_name_ = "DhcpLFC";

/// @brief Defines the executable name.
const char*lfc::lfc_bin_name_ = "kea-lfc";

lfc::lfc()
    : dhcp_version_(0), verbose_(false), config_file_(""),
      previous_file_(""), copy_file_(""), output_file_("") {
    std::cerr << "created lfc" << std::endl;
}

lfc::~lfc() {
    std::cerr << "destroyed lfc" << std::endl;
}

void
lfc::launch(int argc, char* argv[], const bool test_mode) {
  try {
    parseArgs(argc, argv);
  } catch (const InvalidUsage& ex) {
    usage(ex.what());
    throw;  // rethrow it
  }

  std::cerr << "launched lfc" << std::endl;
}

void
lfc::parseArgs(int argc, char* argv[])
{
    int ch;

    while ((ch = getopt(argc, argv, "46dvVp:i:o:c:")) != -1) {
        switch (ch) {
	case '4':
            // Process DHCPv4 lease files.
            dhcp_version_ = 4;
            break;

	case '6':
            // Process DHCPv6 lease files.
            dhcp_version_ = 6;
            break;

	case 'v':
            // Print just Kea vesion and exit.
	  //            std::cout << getVersion(false) << std::endl;
            exit(EXIT_SUCCESS);

	case 'V':
            // Print extended  Kea vesion and exit.
	  //std::cout << getVersion(true) << std::endl;
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

    if (dhcp_version_ == 0) {
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

    if (config_file_.empty()) {
        isc_throw(InvalidUsage, "Config file not specified");	
    }

    // If verbose is set echo the input information
    if (verbose_ == true) {
      std::cerr << "Protocol version:    " << dhcp_version_ << std::endl
	        << "Previous lease file: " << previous_file_ << std::endl
	        << "Copy lease file:     " << copy_file_ << std::endl
	        << "Output lease file:   " << output_file_ << std::endl
	        << "Config file:         " << config_file_ << std::endl;
    }
}

void
lfc::pidCheck()
{
}

void
lfc::pidDelete()
{
}

void
lfc::usage(const std::string & text)
{
    if (text != "") {
        std::cerr << "Usage error: " << text << std::endl;
    }

    std::cerr << "Usage: " << lfc_bin_name_ << std::endl
              << " [-4|-6] -p file -i file -o file -c file" << std::endl
              << "   -4 or -6 clean a set of v4 or v6 lease files" << std::endl
              << "   -p <file>: previous lease file" << std::endl
              << "   -i <file>: copy of lease file" << std::endl
              << "   -o <file>: output lease file" << std::endl
              << "   -c <file>: configuration file" << std::endl
              << "   -v: print version number and exit" << std::endl
              << "   -V: print extended version inforamtion and exit" << std::endl
              << "   -d: optional, verbose output " << std::endl
              << std::endl;
}

}; // namespace isc::lfc
}; // namespace isc

//std::string
//isc::dhcp::Daemon::getVersion(bool extended) {
//    std::stringstream tmp;
//
//    tmp << VERSION;
//    if (extended) {
//        tmp << std::endl << EXTENDED_VERSION;
//
        // @todo print more details (is it Botan or OpenSSL build,
        // with or without MySQL/Postgres? What compilation options were
        // used? etc)
//    }
//
//    return (tmp.str());
//}
