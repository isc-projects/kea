// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcpsrv/cfgmgr.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <cfgrpt/config_report.h>

#include <boost/lexical_cast.hpp>

#include <iostream>

using namespace isc::dhcp;
using namespace std;

/// This file contains entry point (main() function) for standard DHCPv4 server
/// component of Kea software suite. It parses command-line arguments and
/// instantiates ControlledDhcpv4Srv class that is responsible for establishing
/// connection with msgq (receiving commands and configuration) and also
/// creating Dhcpv4 server object as well.

namespace {

const char* const DHCP4_NAME = "kea-dhcp4";

/// @brief Prints Kea Usage and exits
///
/// Note: This function never returns. It terminates the process.
void
usage() {
    cerr << "Kea DHCPv4 server, version " << VERSION << endl;
    cerr << endl;
    cerr << "Usage: " << DHCP4_NAME
         << " -[v|V|W] [-d] [-c cfgfile] [-p number]" << endl;
    cerr << "  -v: print version number and exit" << endl;
    cerr << "  -V: print extended version and exit" << endl;
    cerr << "  -W: display the configuration report and exit" << endl;
    cerr << "  -d: debug mode with extra verbosity (former -v)" << endl;
    cerr << "  -c file: specify configuration file" << endl;
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
    bool verbose_mode = false; // Should server be verbose?

    // The standard config file
    std::string config_file("");

    while ((ch = getopt(argc, argv, "dvVWc:p:")) != -1) {
        switch (ch) {
        case 'd':
            verbose_mode = true;
            break;

        case 'v':
            cout << Dhcpv4Srv::getVersion(false) << endl;
            return (EXIT_SUCCESS);

        case 'V':
            cout << Dhcpv4Srv::getVersion(true) << endl;
            return (EXIT_SUCCESS);

        case 'W':
            cout << isc::detail::getConfigReport() << endl;
            return (EXIT_SUCCESS);

        case 'c': // config file
            config_file = optarg;
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


    // Configuration file is required.
    if (config_file.empty()) {
        cerr << "Configuration file not specified." << endl;
        usage();
    }

    int ret = EXIT_SUCCESS;
    try {
        // It is important that we set a default logger name because this name
        // will be used when the user doesn't provide the logging configuration
        // in the Kea configuration file.
        CfgMgr::instance().setDefaultLoggerName(DHCP4_ROOT_LOGGER_NAME);

        // Initialize logging.  If verbose, we'll use maximum verbosity.
        Daemon::loggerInit(DHCP4_ROOT_LOGGER_NAME, verbose_mode);
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_START_INFO)
            .arg(getpid()).arg(port_number).arg(verbose_mode ? "yes" : "no");

        LOG_INFO(dhcp4_logger, DHCP4_STARTING).arg(VERSION);

        // Create the server instance.
        ControlledDhcpv4Srv server(port_number);

        // Remember verbose-mode
        server.setVerbose(verbose_mode);

        // Create our PID file.
        server.setProcName(DHCP4_NAME);
        server.setConfigFile(config_file);
        server.createPIDFile();

        try {
            // Initialize the server.
            server.init(config_file);
        } catch (const std::exception& ex) {

            try {
                // Let's log out what went wrong.
                isc::log::LoggerManager log_manager;
                log_manager.process();
                LOG_ERROR(dhcp4_logger, DHCP4_INIT_FAIL).arg(ex.what());
            } catch (...) {
                // The exception thrown during the initialization could
                // originate from logger subsystem. Therefore LOG_ERROR()
                // may fail as well.
                cerr << "Failed to initialize server: " << ex.what() << endl;
            }

            return (EXIT_FAILURE);
        }

        // Tell the admin we are ready to process packets
        LOG_INFO(dhcp4_logger, DHCP4_STARTED).arg(VERSION);

        // And run the main loop of the server.
        server.run();

        LOG_INFO(dhcp4_logger, DHCP4_SHUTDOWN);

    } catch (const isc::dhcp::DaemonPIDExists& ex) {
        // First, we print the error on stderr (that should always work)
        cerr << DHCP4_NAME << " already running? " << ex.what()
             << endl;

        // Let's also try to log it using logging system, but we're not
        // sure if it's usable (the exception may have been thrown from
        // the logger subsystem)
        LOG_FATAL(dhcp4_logger, DHCP4_ALREADY_RUNNING)
                  .arg(DHCP4_NAME).arg(ex.what());
        ret = EXIT_FAILURE;
    } catch (const std::exception& ex) {
        // First, we print the error on stderr (that should always work)
        cerr << DHCP4_NAME << ": Fatal error during start up: " << ex.what()
             << endl;

        // Let's also try to log it using logging system, but we're not
        // sure if it's usable (the exception may have been thrown from
        // the logger subsystem)
        LOG_FATAL(dhcp4_logger, DHCP4_SERVER_FAILED).arg(ex.what());
        ret = EXIT_FAILURE;
    }

    return (ret);
}
