// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6_log.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <exceptions/exceptions.h>

#include <boost/lexical_cast.hpp>

#include <iostream>

using namespace isc::dhcp;
using namespace std;

/// This file contains entry point (main() function) for standard DHCPv6 server
/// component for BIND10 framework. It parses command-line arguments and
/// instantiates ControlledDhcpv6Srv class that is responsible for establishing
/// connection with msgq (receiving commands and configuration) and also
/// creating Dhcpv6 server object as well.
///
/// For detailed explanation or relations between main(), ControlledDhcpv6Srv,
/// Dhcpv6Srv and other classes, see \ref dhcpv6Session.

namespace {
const char* const DHCP6_NAME = "b10-dhcp6";

const char* const DHCP6_LOGGER_NAME = "kea";

void
usage() {
    cerr << "Usage: " << DHCP6_NAME << " [-v] [-s] [-p port_number] [-c cfgfile]" << endl;
    cerr << "  -v: verbose output" << endl;
    cerr << "  -s: skip configuration (don't connect to BIND10 or don't read config file)" << endl;
    cerr << "  -p number: specify non-standard port number 1-65535 "
         << "(useful for testing only)" << endl;
    cerr << "  -c file: specify configuration file" << endl;
    exit(EXIT_FAILURE);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;
    int port_number = DHCP6_SERVER_PORT; // The default. Any other values are
                                         // useful for testing only.
    bool stand_alone = false;  // Should be connect to BIND10 msgq?
    bool verbose_mode = false; // Should server be verbose?

    // The standard config file
    std::string config_file("");

    while ((ch = getopt(argc, argv, "vsp:c:")) != -1) {
        switch (ch) {
        case 'v':
            verbose_mode = true;
            break;

        case 's': // stand-alone
            stand_alone = true;
            break;

        case 'p': // port number
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

        case 'c': // config file
            config_file = optarg;
            break;

        default:
            usage();
        }
    }

    // Check for extraneous parameters.
    if (argc > optind) {
        usage();
    }


    int ret = EXIT_SUCCESS;
    try {
        // Initialize logging.  If verbose, we'll use maximum verbosity.
        // If standalone is enabled, do not buffer initial log messages
        Daemon::loggerInit(DHCP6_LOGGER_NAME, verbose_mode, stand_alone);

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_START_INFO)
            .arg(getpid()).arg(port_number).arg(verbose_mode ? "yes" : "no")
            .arg(stand_alone ? "yes" : "no" );

        LOG_INFO(dhcp6_logger, DHCP6_STARTING);

        ControlledDhcpv6Srv server(port_number);

        if (!stand_alone) {
            try {
                // Initialize the server, i.e. establish control session
                // if BIND10 backend is used or read a configuration file
                server.init(config_file);

            } catch (const std::exception& ex) {
                LOG_ERROR(dhcp6_logger, DHCP6_INIT_FAIL).arg(ex.what());

                // We should not continue if were told to configure (either read
                // config file or establish BIND10 control session).
                isc::log::LoggerManager log_manager;
                log_manager.process();

                cerr << "Failed to initialize server: " << ex.what() << endl;
                return (EXIT_FAILURE);
            }
        } else {
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_STANDALONE);
        }

        server.run();
        LOG_INFO(dhcp6_logger, DHCP6_SHUTDOWN);

    } catch (const std::exception& ex) {
        LOG_FATAL(dhcp6_logger, DHCP6_SERVER_FAILED).arg(ex.what());
        cerr << "Fatal error during start up: " << ex.what() << endl;
        ret = EXIT_FAILURE;
    }

    return (ret);
}
