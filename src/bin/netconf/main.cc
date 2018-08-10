// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <netconf/netconf_log.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/daemon.h>
#include <iostream>

#include <sysrepo-cpp/Session.h>

using namespace std;
using namespace isc;
using namespace isc::netconf;

/// @brief Prints Kea Usage and exits
///
/// Note: This function never returns. It terminates the process.
void
usage() {
    cerr << "Kea netconf daemon, version " << VERSION << endl
         << endl
         << "Usage: " << endl
         << "  -c: config-file" << endl
         << "  -d: debug mode (maximum verbosity)" << endl
         << "  -v: print version number and exit" << endl
         << "  -V: print extended version and exit" << endl;
    exit(EXIT_FAILURE);
}

int
main(int argc, char* argv[]) {
    // The standard config file
    std::string config_file("");
    int ch;

    while ((ch = getopt(argc, argv, "vVc:")) != -1) {
        switch (ch) {
        case 'v':
            cout << string(PACKAGE_VERSION) << endl;
            return (EXIT_SUCCESS);

        case 'V':
            cout << string(PACKAGE_VERSION) << endl;
            cout << "git " << EXTENDED_VERSION << endl;
            return (EXIT_SUCCESS);

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
        //CfgMgr::instance().setDefaultLoggerName(KEA_NETCONF_LOGGER_NAME);

        // Initialize logging.  If verbose, we'll use maximum verbosity.
        bool verbose_mode = true;
        isc::dhcp::Daemon::loggerInit(NETCONF_LOGGER_NAME, verbose_mode);
        LOG_INFO(netconf_logger, NETCONF_STARTING).arg(VERSION).arg(getpid());

        Connection conn("kea-netconf");
        
        // Tell the admin we are ready to process packets
        LOG_INFO(netconf_logger, NETCONF_STATED).arg(VERSION);

        // And run the main loop of the server.
        while (true) {
            cout << "Dummy kea-netconf running. Press ctrl-c to terminate."
                 << endl;
            sleep(1);
        }

        LOG_INFO(netconf_logger, NETCONF_SHUTDOWN);

    } catch (const isc::Exception& ex) {
        // First, we parint the error on stderr (that should always work)
        cerr << "ERROR:" << ex.what() << endl;
        ret = EXIT_FAILURE;
    }

    return (ret);
}
