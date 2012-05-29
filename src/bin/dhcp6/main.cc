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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include <cassert>
#include <iostream>

#include <exceptions/exceptions.h>
#if 0
// TODO cc is not used yet. It should be eventually
#include <cc/session.h>
#include <config/ccsession.h>
#endif

#include <util/buffer.h>
#include <log/dummylog.h>

#include <dhcp6/spec_config.h>
#include "dhcp6/dhcp6_srv.h"

using namespace std;
using namespace isc::util;

using namespace isc;
using namespace isc::dhcp;

namespace {

bool verbose_mode = false;

void
usage() {
    cerr << "Usage:  b10-dhcp6 [-v]"
         << endl;
    cerr << "\t-v: verbose output" << endl;
    cerr << "\t-p number: specify non-standard port number 1-65535 (useful for testing only)" << endl;
    exit(EXIT_FAILURE);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;
    int port_number = DHCP6_SERVER_PORT; // The default. Any other values are
                                         // useful for testing only.

    while ((ch = getopt(argc, argv, "vp:")) != -1) {
        switch (ch) {
        case 'v':
            verbose_mode = true;
            isc::log::denabled = true;
            break;
        case 'p':
            port_number = strtol(optarg, NULL, 10);
            if (port_number == 0) {
                cerr << "Failed to parse port number: [" << optarg
                     << "], 1-65535 allowed." << endl;
                usage();
            }
            break;
        case ':':
        default:
            usage();
        }
    }

    cout << "My pid=" << getpid() << endl;

    if (argc - optind > 0) {
        usage();
    }

    int ret = EXIT_SUCCESS;

    // TODO remainder of auth to dhcp6 code copy. We need to enable this in
    //      dhcp6 eventually
#if 0
    Session* cc_session = NULL;
    Session* statistics_session = NULL;
    ModuleCCSession* config_session = NULL;
#endif
    try {
        string specfile;
        if (getenv("B10_FROM_BUILD")) {
            specfile = string(getenv("B10_FROM_BUILD")) +
                "/src/bin/auth/dhcp6.spec";
        } else {
            specfile = string(DHCP6_SPECFILE_LOCATION);
        }

        cout << "[b10-dhcp6] Initiating DHCPv6 operation." << endl;

        Dhcpv6Srv* srv = new Dhcpv6Srv(port_number);

        srv->run();

    } catch (const std::exception& ex) {
        cerr << "[b10-dhcp6] Server failed: " << ex.what() << endl;
        ret = EXIT_FAILURE;
    }

    return (ret);
}
