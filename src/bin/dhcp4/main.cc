// Copyright (C) 2011-2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <log/logger_support.h>

#include <boost/lexical_cast.hpp>

#include <iostream>

using namespace isc::dhcp;
using namespace std;

/// This file contains entry point (main() function) for standard DHCPv4 server
/// component for BIND10 framework. It parses command-line arguments and
/// instantiates ControlledDhcpv4Srv class that is responsible for establishing
/// connection with msgq (receiving commands and configuration) and also
/// creating Dhcpv4 server object as well.
///
/// For detailed explanation or relations between main(), ControlledDhcpv4Srv,
/// Dhcpv4Srv and other classes, see \ref dhcpv4Session.

namespace {

const char* const DHCP4_NAME = "b10-dhcp4";

void
usage() {
    cerr << "Usage: " << DHCP4_NAME << " [-v] [-s] [-p number]" << endl;
    cerr << "  -v: verbose output" << endl;
    cerr << "  -s: stand-alone mode (don't connect to BIND10)" << endl;
    cerr << "  -p number: specify non-standard port number 1-65535 "
         << "(useful for testing only)" << endl;
    exit(EXIT_FAILURE);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;
    int port_number = DHCP4_SERVER_PORT; // The default. any other values are
                                         // useful for testing only.
    bool stand_alone = false;  // Should be connect to BIND10 msgq?
    bool verbose_mode = false; // Should server be verbose?

    while ((ch = getopt(argc, argv, "vsp:")) != -1) {
        switch (ch) {
        case 'v':
            verbose_mode = true;
            break;

        case 's':
            stand_alone = true;
            break;

        case 'p':
            try {
                port_number = boost::lexical_cast<int>(optarg);
            } catch (const boost::bad_lexical_cast &) {
                cerr << "Failed to parse port number: [" << optarg
                     << "], 1-65535 allowed." << endl;
                usage();
            }
            if (port_number <= 0 || port_number > 65535) {
                cerr << "Failed to parse port number: [" << optarg
                     << "], 1-65535 allowed." << endl;
                usage();
            }
            break;

        default:
            usage();
        }
    }

    // Check for extraneous parameters.
    if (argc > optind) {
        usage();
    }

    // Initialize logging.  If verbose, we'll use maximum verbosity.
    // If standalone is enabled, do not buffer initial log messages
    isc::log::initLogger(DHCP4_NAME,
                         (verbose_mode ? isc::log::DEBUG : isc::log::INFO),
                         isc::log::MAX_DEBUG_LEVEL, NULL, !stand_alone);
    LOG_INFO(dhcp4_logger, DHCP4_STARTING);
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_START_INFO)
              .arg(getpid()).arg(port_number).arg(verbose_mode ? "yes" : "no")
              .arg(stand_alone ? "yes" : "no" );


    int ret = EXIT_SUCCESS;
    try {
        ControlledDhcpv4Srv server(port_number);
        if (!stand_alone) {
            try {
                server.establishSession();
            } catch (const std::exception& ex) {
                LOG_ERROR(dhcp4_logger, DHCP4_SESSION_FAIL).arg(ex.what());
                // Let's continue. It is useful to have the ability to run
                // DHCP server in stand-alone mode, e.g. for testing
            }
        } else {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_STANDALONE);
        }
        server.run();
        LOG_INFO(dhcp4_logger, DHCP4_SHUTDOWN);

    } catch (const std::exception& ex) {
        LOG_FATAL(dhcp4_logger, DHCP4_SERVER_FAILED).arg(ex.what());
        ret = EXIT_FAILURE;
    }

    return (ret);
}
