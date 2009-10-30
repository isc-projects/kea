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
#include <netdb.h>
#include <stdlib.h>

#include <set>
#include <iostream>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/message.h>

#include "common.h"
#include "zoneset.h"

using namespace std;

using namespace isc::dns;
using namespace isc::dns::Rdata::IN;
using namespace isc::dns::Rdata::Generic;

const string PROGRAM = "parkinglot";
const int DNSPORT = 53;

ZoneSet zones;

static void
init_db() {
    zones.serve("jinmei.org");
    zones.serve("nuthaven.org");
    zones.serve("isc.org");
    zones.serve("sisotowbell.org");
    zones.serve("flame.org");
}

static int
start_server(int port) {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0)
        throw FatalError("failed to open socket");

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    socklen_t sa_len = sizeof(sin);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&sin);

    if (bind(s, sa, sa_len) < 0)
        return (-1);

    return (s);
}

static void
run_server(int s) {
    Rdata::RdataPtr ns1, ns2, ns3;
    ns1 = Rdata::RdataPtr(new NS("ns1.parking.com"));
    ns2 = Rdata::RdataPtr(new NS("ns2.parking.com"));
    ns3 = Rdata::RdataPtr(new NS("ns3.parking.com"));

    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);

    while (true) {
        Message msg;
        if (msg.getBuffer().recvFrom(s, sa, &sa_len) > 0) {
            try {
                msg.fromWire();
            } catch (...) {
                cerr << "parse failed" << endl;
                continue;
            }

            cout << "received a message:\n" << msg.toText() << endl;

            if (msg.getSection(SECTION_QUESTION).size() != 1)
                continue;

            msg.makeResponse();
            msg.setAA(true);

            RRsetPtr query = msg.getSection(SECTION_QUESTION)[0];

            string name = query->getName().toText(true);
            if (zones.contains(name)) {
                msg.setRcode(Message::RCODE_NOERROR);
                RRset* nsset = new RRset(query->getName(), query->getClass(),
                                         RRType::NS, TTL(3600));

                nsset->addRdata(ns1);
                nsset->addRdata(ns2);
                nsset->addRdata(ns3);

                if (query->getType() == RRType::NS)
                    msg.addRRset(SECTION_ANSWER, RRsetPtr(nsset));
                else
                    msg.addRRset(SECTION_AUTHORITY, RRsetPtr(nsset));

                if (query->getType() == RRType::A) {
                    RR arr(query->getName(), query->getClass(),
                           RRType::A, TTL(3600),
                           Rdata::RdataPtr(new A("127.0.0.1")));

                    msg.addRR(SECTION_ANSWER, arr);
                } else if (query->getType() == RRType::AAAA) {
                    RR aaaarr(query->getName(), query->getClass(),
                              RRType::AAAA, TTL(3600),
                              Rdata::RdataPtr(new AAAA("::1")));
                    msg.addRR(SECTION_ANSWER, aaaarr);
                }
            } else {
                msg.setRcode(Message::RCODE_NXDOMAIN);
                // should add SOA to the authority section, but not implemented.
            }

            msg.toWire();
            cout << "sending a response (" <<
                boost::lexical_cast<string>(msg.getBuffer().getSize())
                      << " bytes):\n" << msg.toText() << endl;
            msg.getBuffer().sendTo(s, *sa, sa_len);
        }
    }
}

int
main(int argc, char* argv[])
{
    Message msg;
    int ch;
    int port = DNSPORT;
    bool err = false;

    while ((ch = getopt(argc, argv, "p:")) != -1) {
        switch (ch) {
        case 'p':
            port = atoi(optarg);
            break;
        case '?':
        default:
            err = true;
        }
    }

    if (err || (argc - optind) > 0) {
        cerr << "Usage: parkinglot [-p port]" << endl;
        exit(1);
    }

    // initialize DNS database
    init_db();

    // start the server
    int s = start_server(port);
    if (s < 0)
        throw FatalError("unable to start the server");

    // main server loop
    cout << "server running" << endl;
    run_server(s);

    return (0);
}
