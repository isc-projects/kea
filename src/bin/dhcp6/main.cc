// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <kea_version.h>

#include <cfgrpt/config_report.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/parser_context.h>
#include <dhcp6/json_config_parser.h>
#include <dhcpsrv/cfgmgr.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <process/daemon.h>

#include <boost/lexical_cast.hpp>

#include <iostream>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;
using namespace std;

/// This file contains entry point (main() function) for standard DHCPv6 server
/// component of Kea software suite. It parses command-line arguments and
/// instantiates ControlledDhcpv6Srv class that is responsible for establishing
/// connection with msgq (receiving commands and configuration) and also
/// creating Dhcpv6 server object as well.
///
/// For detailed explanation or relations between main(), ControlledDhcpv6Srv,
/// Dhcpv6Srv and other classes, see \ref dhcpv6Session.

namespace {

const char* const DHCP6_NAME = "kea-dhcp6";

/// @brief Prints Kea Usage and exits
///
/// Note: This function never returns. It terminates the process.
void
usage() {
    cerr << "Kea DHCPv6 server, "
         << "version " << VERSION
         << " (" << PACKAGE_VERSION_TYPE << ")"
         << endl;
    cerr << endl;
    cerr << "Usage: " << DHCP6_NAME
         << " -[v|V|W] [-d] [-{c|t} cfgfile] [-p number] [-P number]" << endl;
    cerr << "  -v: print version number and exit" << endl;
    cerr << "  -V: print extended version and exit" << endl;
    cerr << "  -W: display the configuration report and exit" << endl;
    cerr << "  -d: debug mode with extra verbosity (former -v)" << endl;
    cerr << "  -c file: specify configuration file" << endl;
    cerr << "  -t file: check the configuration file syntax and exit" << endl;
    cerr << "  -p number: specify non-standard server port number 1-65535 "
         << "(useful for testing only)" << endl;
    cerr << "  -P number: specify non-standard client port number 1-65535 "
         << "(useful for testing only)" << endl;
    exit(EXIT_FAILURE);
}
}  // namespace

int
main(int argc, char* argv[]) {
    int ch;
    // The default. Any other values are useful for testing only.
    int server_port_number = DHCP6_SERVER_PORT;
    // Not zero values are useful for testing only.
    int client_port_number = 0;
    bool verbose_mode = false; // Should server be verbose?
    bool check_mode = false;   // Check syntax

    // The standard config file
    std::string config_file("");

    while ((ch = getopt(argc, argv, "dvVWc:p:P:t:")) != -1) {
        switch (ch) {
        case 'd':
            verbose_mode = true;
            break;

        case 'v':
            cout << Dhcpv6Srv::getVersion(false) << endl;
            return (EXIT_SUCCESS);

        case 'V':
            cout << Dhcpv6Srv::getVersion(true) << endl;
            return (EXIT_SUCCESS);

        case 'W':
            cout << isc::detail::getConfigReport() << endl;
            return (EXIT_SUCCESS);

        case 't':
            check_mode = true;
            // falls through

        case 'c': // config file
            config_file = optarg;
            break;

        case 'p': // server port number
            try {
                server_port_number = boost::lexical_cast<int>(optarg);
            } catch (const boost::bad_lexical_cast &) {
                cerr << "Failed to parse server port number: [" << optarg
                     << "], 1-65535 allowed." << endl;
                usage();
            }
            if (server_port_number <= 0 || server_port_number > 65535) {
                cerr << "Failed to parse server port number: [" << optarg
                     << "], 1-65535 allowed." << endl;
                usage();
            }
            break;

        case 'P': // client port number
            try {
                client_port_number = boost::lexical_cast<int>(optarg);
            } catch (const boost::bad_lexical_cast &) {
                cerr << "Failed to parse client port number: [" << optarg
                     << "], 1-65535 allowed." << endl;
                usage();
            }
            if (client_port_number <= 0 || client_port_number > 65535) {
                cerr << "Failed to parse client port number: [" << optarg
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

    // This is the DHCPv6 server
    CfgMgr::instance().setFamily(AF_INET6);

    if (check_mode) {
        try {
            // We need to initialize logging, in case any error messages are to be printed.
            // This is just a test, so we don't care about lockfile.
            setenv("KEA_LOCKFILE_DIR", "none", 0);
            Daemon::setDefaultLoggerName(DHCP6_ROOT_LOGGER_NAME);
            Daemon::loggerInit(DHCP6_ROOT_LOGGER_NAME, verbose_mode);

            // Check the syntax first.
            Parser6Context parser;
            ConstElementPtr json;
            json = parser.parseFile(config_file, Parser6Context::PARSER_DHCP6);
            if (!json) {
                cerr << "No configuration found" << endl;
                return (EXIT_FAILURE);
            }
            if (verbose_mode) {
                cerr << "Syntax check OK" << endl;
            }

            // Check the logic next.
            ConstElementPtr dhcp6 = json->get("Dhcp6");
            if (!dhcp6) {
                cerr << "Missing mandatory Dhcp6 element" << endl;
                return (EXIT_FAILURE);
            }
            ControlledDhcpv6Srv server(0);
            ConstElementPtr answer;

            // Now we pass the Dhcp6 configuration to the server, but
            // tell it to check the configuration only (check_only = true)
            answer = configureDhcp6Server(server, dhcp6, true);

            int status_code = 0;
            answer = isc::config::parseAnswer(status_code, answer);
            if (status_code == 0) {
                return (EXIT_SUCCESS);
            } else {
                cerr << "Error encountered: " << answer->stringValue() << endl;
                return (EXIT_FAILURE);
            }
        } catch (const std::exception& ex) {
            cerr << "Syntax check failed with: " << ex.what() << endl;
        }
        return (EXIT_FAILURE);
    }

    int ret = EXIT_SUCCESS;
    try {
        // It is important that we set a default logger name because this name
        // will be used when the user doesn't provide the logging configuration
        // in the Kea configuration file.
        Daemon::setDefaultLoggerName(DHCP6_ROOT_LOGGER_NAME);

        // Initialize logging.  If verbose, we'll use maximum verbosity.
        Daemon::loggerInit(DHCP6_ROOT_LOGGER_NAME, verbose_mode);
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_START_INFO)
            .arg(getpid())
            .arg(server_port_number)
            .arg(client_port_number)
            .arg(verbose_mode ? "yes" : "no");

        LOG_INFO(dhcp6_logger, DHCP6_STARTING)
            .arg(VERSION)
            .arg(PACKAGE_VERSION_TYPE);

        if (string(PACKAGE_VERSION_TYPE) == "development") {
            LOG_WARN(dhcp6_logger, DHCP6_DEVELOPMENT_VERSION);
        }

        // Create the server instance.
        ControlledDhcpv6Srv server(server_port_number, client_port_number);

        // Remember verbose-mode
        server.setVerbose(verbose_mode);

        // Create our PID file.
        server.setProcName(DHCP6_NAME);
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
                LOG_ERROR(dhcp6_logger, DHCP6_INIT_FAIL).arg(ex.what());
            } catch (...) {
                // The exception thrown during the initialization could
                // originate from logger subsystem. Therefore LOG_ERROR()
                // may fail as well.
                cerr << "Failed to initialize server: " << ex.what() << endl;
            }

            return (EXIT_FAILURE);
        }

        // Tell the admin we are ready to process packets
        LOG_INFO(dhcp6_logger, DHCP6_STARTED).arg(VERSION);

        // And run the main loop of the server.
        ret = server.run();

        LOG_INFO(dhcp6_logger, DHCP6_SHUTDOWN);

    } catch (const isc::process::DaemonPIDExists& ex) {
        // First, we print the error on stderr (that should always work)
        cerr << DHCP6_NAME << " already running? " << ex.what()
             << endl;

        // Let's also try to log it using logging system, but we're not
        // sure if it's usable (the exception may have been thrown from
        // the logger subsystem)
        try {
            LOG_FATAL(dhcp6_logger, DHCP6_ALREADY_RUNNING)
                .arg(DHCP6_NAME).arg(ex.what());
        } catch (...) {
            // Already logged so ignore
        }
        ret = EXIT_FAILURE;
    } catch (const std::exception& ex) {
        // First, we print the error on stderr (that should always work)
        cerr << DHCP6_NAME << ": Fatal error during start up: " << ex.what()
             << endl;

        // Let's also try to log it using logging system, but we're not
        // sure if it's usable (the exception may have been thrown from
        // the logger subsystem)
        try {
            LOG_FATAL(dhcp6_logger, DHCP6_SERVER_FAILED).arg(ex.what());
        } catch (...) {
            // Already logged so ignore
        }
        ret = EXIT_FAILURE;
    } catch (...) {
        cerr << DHCP6_NAME << ": Fatal error during start up"
             << endl;
        ret = EXIT_FAILURE;
    }

    return (ret);
}
