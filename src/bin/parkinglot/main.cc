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

Rdata::RdataPtr ns1, ns2, ns3, a, aaaa, soa;

static void
init_server() {
    ns1 = Rdata::RdataPtr(new NS("ns1.parking.com"));
    ns2 = Rdata::RdataPtr(new NS("ns2.parking.com"));
    ns3 = Rdata::RdataPtr(new NS("ns3.parking.com"));
    a = Rdata::RdataPtr(new A("127.0.0.1"));
    aaaa = Rdata::RdataPtr(new AAAA("::1"));
    soa == Rdata::RdataPtr(new SOA("parking.com", "noc.parking.com",
                                   1, 1800, 900, 604800, TTL(86400)));
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
process_message(int s) {
    Message msg;
    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);
    Name authors_name("authors.bind");

    if (msg.getBuffer().recvFrom(s, sa, &sa_len) > 0) {
        try {
            msg.fromWire();
        } catch (...) {
            cerr << "parse failed" << endl;
            return;
        }

        cout << "received a message:\n" << msg.toText() << endl;

        if (msg.getSection(SECTION_QUESTION).size() != 1)
            return;

        msg.makeResponse();
        msg.setAA(true);

        RRsetPtr query = msg.getSection(SECTION_QUESTION)[0];

        string name = query->getName().toText(true);
        if (query->getName() == authors_name &&
            query->getClass() == RRClass::CH,
            query->getType() == RRType::TXT) {
            msg.setRcode(Message::RCODE_NOERROR);
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH,
                                         RRType::TXT, TTL(0),
                                         TXT("JINMEI Tatuya")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH,
                                         RRType::TXT, TTL(0),
                                         TXT("Evan Hunt")));
            // add others name here!!

            msg.addRR(SECTION_AUTHORITY, RR(authors_name, RRClass::CH,
                                            RRType::NS, TTL(0),
                                            NS("authors.bind")));
        }

        if (zones.contains(name)) {
            msg.setRcode(Message::RCODE_NOERROR);
            RRset* nsset = new RRset(query->getName(), RRClass::IN,
                                     RRType::NS, TTL(3600));

            nsset->addRdata(ns1);
            nsset->addRdata(ns2);
            nsset->addRdata(ns3);

            if (query->getType() == RRType::NS)
                msg.addRRset(SECTION_ANSWER, RRsetPtr(nsset));
            else if (query->getType() == RRType::A) {
                msg.addRRset(SECTION_AUTHORITY, RRsetPtr(nsset));
                RR arr(query->getName(), RRClass::IN, RRType::A, TTL(3600), a);

                msg.addRR(SECTION_ANSWER, arr);
            } else if (query->getType() == RRType::AAAA) {
                msg.addRRset(SECTION_AUTHORITY, RRsetPtr(nsset));
                RR aaaarr(query->getName(), RRClass::IN, RRType::AAAA,
                          TTL(3600), aaaa);
                msg.addRR(SECTION_ANSWER, aaaarr);
            } else {
                RR soarr(query->getName(), RRClass::IN, RRType::SOA,
                         TTL(3600), soa);
                msg.addRR(SECTION_AUTHORITY, soarr);
            }
        } else {
            msg.setRcode(Message::RCODE_NXDOMAIN);
        }

        msg.toWire();
        cout << "sending a response (" <<
            boost::lexical_cast<string>(msg.getBuffer().getSize())
                  << " bytes):\n" << msg.toText() << endl;
        msg.getBuffer().sendTo(s, *sa, sa_len);
    }
}

static void
run_server(int s) {
    while (true) {
        process_message(s);
    }
}

int
main(int argc, char* argv[]) {
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

    // initialize
    init_db();
    init_server();

    // start the server
    int s = start_server(port);
    if (s < 0)
        throw FatalError("unable to start the server");

    // main server loop
    cout << "server running" << endl;
    run_server(s);

    return (0);
}
