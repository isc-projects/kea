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
#include <d2srv/d2srv_log.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>

#include <iostream>

using namespace isc::d2srv;
using namespace std;

/// This file contains entry point (main() function) for standard DHCP-DDNS 
///  server, b10-d2srv, component for BIND10 framework. It parses command-line 
/// arguments and instantiates D2Controller class that is responsible for 
/// establishing connection with msgq (receiving commands and configuration) 
/// and also creating D2Server object as well.
///
/// For detailed explanation or relations between main(), D2Controller,
/// D2Server and other classes, see \ref d2srvSession. 

namespace {

const char* const D2SRV_NAME = "b10-d2srv";

void
usage() {
    cerr << "Usage: " << D2SRV_NAME << " [-v] [-s] [-p number]" << endl;
    cerr << "  -v: verbose output" << endl;
    cerr << "  -s: stand-alone mode (don't connect to BIND10)" << endl;
    exit(EXIT_FAILURE);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;
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
    isc::log::initLogger(D2SRV_NAME,
                         (verbose_mode ? isc::log::DEBUG : isc::log::INFO),
                         isc::log::MAX_DEBUG_LEVEL, NULL, !stand_alone);
    LOG_INFO(d2srv_logger, D2SRV_STARTING);
    LOG_DEBUG(d2srv_logger, DBGLVL_START_SHUT, D2SRV_START_INFO)
              .arg(getpid()).arg(verbose_mode ? "yes" : "no")
              .arg(stand_alone ? "yes" : "no" );


    int ret = EXIT_SUCCESS;
    sleep(1000);
    LOG_INFO(d2srv_logger, D2SRV_SHUTDOWN);
    return (ret);
}

