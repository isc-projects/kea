// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <stdlib.h>

#include <set>
#include <iostream>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/message.h>

#include <cc/cpp/session.h>

#include "zoneset.h"
#include "parkinglot.h"
#include "ccsession.h"

#include "common.h"

using namespace std;

const string PROGRAM = "parkinglot";
const int DNSPORT = 53;

static void
usage() {
    cerr << "Usage: parkinglot [-p port]" << endl;
    exit(1);
}

int
main(int argc, char* argv[]) {
    int ch;
    int port = DNSPORT;

    while ((ch = getopt(argc, argv, "p:")) != -1) {
        switch (ch) {
        case 'p':
            port = atoi(optarg);
            break;
        case '?':
        default:
            usage();
        }
    }

    if (argc - optind > 0)
        usage();

    // initialize parking lot
    ParkingLot plot(port);

    // initialize command channel
    CommandSession cs;

    // main server loop
    fd_set fds;
    int ps = plot.getSocket();
    int ss = cs.getSocket();
    int nfds = max(ps, ss) + 1;

    cout << "Server started." << endl;
    while (true) {
        FD_ZERO(&fds);
        FD_SET(ps, &fds);
        FD_SET(ss, &fds);

        int n = select(nfds, &fds, NULL, NULL, NULL);
        if (n < 0)
            throw FatalError("select error");
        
        if (FD_ISSET(ps, &fds))
            plot.processMessage();

        if (FD_ISSET(ss, &fds)) {
            pair<string,string> cmd = cs.getCommand();
            plot.command(cmd);
        }
    }

    return (0);
}
