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

class ParkingLot {
    public:
        explicit ParkingLot(int port);
        virtual ~ParkingLot() {};
        int getSocket() { return(sock); }
        void processMessage();
        
    private:
        Rdata::RdataPtr ns1, ns2, ns3, a, aaaa, soa;
        ZoneSet zones;
        int sock;
};

static void init_zones(ZoneSet& zones) {
    zones.serve("jinmei.org");
    zones.serve("nuthaven.org");
    zones.serve("isc.org");
    zones.serve("sisotowbell.org");
    zones.serve("flame.org");
}

ParkingLot::ParkingLot(int port) {
    init_zones(zones);

    ns1 = Rdata::RdataPtr(new NS("ns1.parking.com"));
    ns2 = Rdata::RdataPtr(new NS("ns2.parking.com"));
    ns3 = Rdata::RdataPtr(new NS("ns3.parking.com"));
    a = Rdata::RdataPtr(new A("127.0.0.1"));
    aaaa = Rdata::RdataPtr(new AAAA("::1"));
    soa = Rdata::RdataPtr(new SOA("parking.com", "noc.parking.com",
                                        1, 1800, 900, 604800, TTL(86400)));

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0)
        throw FatalError("failed to open socket");

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    socklen_t sa_len = sizeof(sin);
#ifdef HAVE_SIN_LEN
    sin.sin_len = sa_len;
#endif

    if (bind(s, (struct sockaddr *)&sin, sa_len) < 0)
        throw FatalError("could not bind socket");

    sock = s;
}

void
ParkingLot::processMessage() {
    Message msg;
    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);
    int s = sock;
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
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH,
                                         RRType::TXT, TTL(0),
                                         TXT("Jeremy C. Reed")));
            // add others name here!!

            msg.addRR(SECTION_AUTHORITY, RR(authors_name, RRClass::CH,
                                            RRType::NS, TTL(0),
                                            NS("authors.bind")));
        } else if (zones.contains(name)) {
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
usage() {
    cerr << "Usage: parkinglot [-p port]" << endl;
    exit(1);
}

int
main(int argc, char* argv[]) {
    Message msg;
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
    // ISC::CC::Session session;
    // session.establish();
    // session.subscribe("parkinglot");

    // main server loop
    cout << "server running" << endl;
    while (true)
        plot.processMessage();

    return (0);
}
