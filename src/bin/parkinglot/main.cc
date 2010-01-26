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

#include <boost/foreach.hpp>

#include <dns/cpp/buffer.h>
#include <dns/cpp/name.h>
#include <dns/cpp/rrset.h>
#include <dns/cpp/message.h>

#include <cc/cpp/session.h>
#include <cc/cpp/data.h>
#include <config/cpp/ccsession.h>

#include "zoneset.h"
#include "parkinglot.h"

#include "common.h"

#include <boost/foreach.hpp>

#include "config.h"

using namespace std;

const string PROGRAM = "ParkingLot";
const int DNSPORT = 5300;

/* need global var for config/command handlers.
 * todo: turn this around, and put handlers in the parkinglot
 * class itself? */
ParkingLot plot = ParkingLot(DNSPORT);

static void
usage() {
    cerr << "Usage: parkinglot [-p port]" << endl;
    exit(1);
}

isc::data::ElementPtr
my_config_handler(isc::data::ElementPtr config)
{
    return plot.updateConfig(config);
}

isc::data::ElementPtr
my_command_handler(isc::data::ElementPtr command)
{
    isc::data::ElementPtr answer = isc::data::Element::createFromString("{ \"result\": [0] }");

    cout << "[XX] Handle command: " << endl << command->str() << endl;
    if (command->get(0)->stringValue() == "print_message") 
    {
        cout << command->get(1)->get("message") << endl;
        /* let's add that message to our answer as well */
        cout << "[XX] answer was: " << answer->str() << endl;
        answer->get("result")->add(command->get(1));
        cout << "[XX] answer now: " << answer->str() << endl;
    }

    return answer;
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
    //plot = ParkingLot(port);

    // initialize command channel
    try {
        CommandSession cs = CommandSession(PROGRAM, PARKINGLOT_SPECFILE_LOCATION, my_config_handler, my_command_handler);
    
        // main server loop
        fd_set fds;
        int ps = plot.getSocket();
        int ss = cs.getSocket();
        int nfds = max(ps, ss) + 1;
        int counter = 0;
    
        cout << "Server started." << endl;
        while (true) {
            FD_ZERO(&fds);
            FD_SET(ps, &fds);
            FD_SET(ss, &fds);
    
            int n = select(nfds, &fds, NULL, NULL, NULL);
            if (n < 0)
                throw FatalError("select error");
    
            if (FD_ISSET(ps, &fds)) {
                ++counter;
                plot.processMessage();
            }
    
            /* isset not really necessary, but keep it for now */
            if (FD_ISSET(ss, &fds)) {
                cs.check_command();
            }
        }
    } catch (isc::cc::SessionError se) {
        cout << se.what() << endl;
        exit(1);
    }
    
    return (0);
}
