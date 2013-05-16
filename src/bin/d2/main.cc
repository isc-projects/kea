// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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
#include <d2/d2_log.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>

#include <iostream>

using namespace isc::d2;
using namespace std;

/// This file contains entry point (main() function) for standard DHCP-DDNS 
/// process, b10-d2, component for BIND10 framework. It parses command-line
/// arguments and instantiates D2Controller class that is responsible for
/// establishing connection with msgq (receiving commands and configuration)
/// and also creating D2Server object as well.
///
/// For detailed explanation or relations between main(), D2Controller,
/// D2Server and other classes, see \ref d2Session.

namespace {

const char* const D2_NAME = "b10-d2";

void
usage() {
    cerr << "Usage: " << D2_NAME << " [-v] [-s]" << endl;
    cerr << "  -s: stand-alone mode (don't connect to BIND10)" << endl;
    cerr << "  -v: verbose output (only when in stand-alone mode" << endl;
    exit(EXIT_FAILURE);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;

    // @TODO NOTE these parameters are preliminary only. They are here to
    // for symmetry with the DHCP servers.  They may or may not
    // become part of the eventual implementation.

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
    // Verbose logging is only enabled when in stand alone mode.
    isc::log::initLogger(D2_NAME,
                         ((verbose_mode && stand_alone)
                           ? isc::log::DEBUG : isc::log::INFO),
                         isc::log::MAX_DEBUG_LEVEL, NULL, !stand_alone);
    LOG_INFO(d2_logger, D2_STARTING);
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2_START_INFO)
              .arg(getpid()).arg(verbose_mode ? "yes" : "no")
              .arg(stand_alone ? "yes" : "no" );

    // For now we will sleep awhile to simulate doing something.
    // Without at least a sleep, the process will start, exit and be
    // restarted by Bind10/Init endlessley in a rapid succession.
    sleep(1000);
    LOG_INFO(d2_logger, D2_SHUTDOWN);
    return (EXIT_SUCCESS);
}

