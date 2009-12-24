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

#include <cc/cpp/data.h>

#include "common.h"
#include "parkinglot.h"

#include <boost/foreach.hpp>

using namespace std;

using namespace isc::dns;
using namespace isc::dns::Rdata::IN;
using namespace isc::dns::Rdata::Generic;
using namespace isc::data;

void
ParkingLot::addARecord(std::string data) {
    a_records.push_back(Rdata::RdataPtr(new A(data)));
}

void
ParkingLot::addAAAARecord(std::string data) {
    aaaa_records.push_back(Rdata::RdataPtr(new AAAA(data)));
}

void
ParkingLot::addNSRecord(std::string data) {
    ns_records.push_back(Rdata::RdataPtr(new NS(data)));
}

void
ParkingLot::setSOARecord(isc::dns::Rdata::RdataPtr soa_record) {
}

void
ParkingLot::setDefaultZoneData() {
    clearARecords();
    clearAAAARecords();
    clearNSRecords();

    addARecord("127.0.0.1");
    addAAAARecord("::1");
    addNSRecord("ns1.parking.example");
    addNSRecord("ns2.parking.example");
    addNSRecord("ns3.parking.example");
}

ParkingLot::ParkingLot(int port) {
    setDefaultZoneData();
    /*ns1 = Rdata::RdataPtr(new NS("ns1.parking.example"));
    ns2 = Rdata::RdataPtr(new NS("ns2.parking.example"));
    ns3 = Rdata::RdataPtr(new NS("ns3.parking.example"));
    a = Rdata::RdataPtr(new A("127.0.0.1"));
    aaaa = Rdata::RdataPtr(new AAAA("::1"));
    */
    soa = Rdata::RdataPtr(new SOA("parking.example", "noc.parking.example",
                                        1, 1800, 900, 604800, TTL(86400)));

    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
    Name authors_name("authors.bind");
    Name version_name("version.bind");
    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);
    int s = sock;
    Message msg;

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
        if (query->getClass() == RRClass::CH &&
            query->getType() == RRType::TXT &&
            query->getName() == authors_name) {
            msg.setRcode(Message::RCODE_NOERROR);
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH, 
                                         RRType::TXT, TTL(0), 
                                         TXT("Han Feng")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH, 
                                         RRType::TXT, TTL(0), 
                                         TXT("Kazunori Fujiwara")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH, 
                                         RRType::TXT, TTL(0), 
                                         TXT("Michael Graff")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH,
                                         RRType::TXT, TTL(0),
                                         TXT("Evan Hunt")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH,
                                         RRType::TXT, TTL(0),
                                         TXT("Jelte Jansen")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH, 
                                         RRType::TXT, TTL(0), 
                                         TXT("Jin Jian")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH,
                                         RRType::TXT, TTL(0),
                                         TXT("JINMEI Tatuya")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH, 
                                         RRType::TXT, TTL(0), 
                                         TXT("Naoki Kambe")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH, 
                                         RRType::TXT, TTL(0), 
                                         TXT("Shane Kerr"))); 
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH, 
                                         RRType::TXT, TTL(0), 
                                         TXT("Zhang Likun")));
            msg.addRR(SECTION_ANSWER, RR(authors_name, RRClass::CH, 
                                         RRType::TXT, TTL(0), 
                                         TXT("Jeremy C. Reed"))); 
            msg.addRR(SECTION_AUTHORITY, RR(authors_name, RRClass::CH,
                                            RRType::NS, TTL(0),
                                            NS("authors.bind")));
        } else if (query->getClass() == RRClass::CH &&
                   query->getType() == RRType::TXT &&
                   query->getName() == version_name) {            
            msg.setRcode(Message::RCODE_NOERROR);
            msg.addRR(SECTION_ANSWER, RR(version_name, RRClass::CH,
                                         RRType::TXT, TTL(0),
                                         TXT("10.0.0s20091030")));
            msg.addRR(SECTION_AUTHORITY, RR(version_name, RRClass::CH,
                                            RRType::NS, TTL(0),
                                            NS("version.bind")));
        } else if (zones.contains(name)) {
            msg.setRcode(Message::RCODE_NOERROR);
            RRset* nsset = new RRset(query->getName(), RRClass::IN,
                                     RRType::NS, TTL(3600));
            BOOST_FOREACH(isc::dns::Rdata::RdataPtr ns, ns_records) {
                nsset->addRdata(ns);
            }

            if (query->getType() == RRType::NS)
                msg.addRRset(SECTION_ANSWER, RRsetPtr(nsset));
            else if (query->getType() == RRType::A) {
                msg.addRRset(SECTION_AUTHORITY, RRsetPtr(nsset));

                BOOST_FOREACH(isc::dns::Rdata::RdataPtr a, a_records) {
                    RR arr(query->getName(), RRClass::IN, RRType::A, TTL(3600), a);
                    msg.addRR(SECTION_ANSWER, arr);
                }
            } else if (query->getType() == RRType::AAAA) {
                msg.addRRset(SECTION_AUTHORITY, RRsetPtr(nsset));
                BOOST_FOREACH(isc::dns::Rdata::RdataPtr aaaa, aaaa_records) {
                    RR aaaarr(query->getName(), RRClass::IN, RRType::AAAA,
                              TTL(3600), aaaa);
                    msg.addRR(SECTION_ANSWER, aaaarr);
                }
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

void
ParkingLot::command(pair<string,ElementPtr> cmd) {
    if (cmd.first == "shutdown")
        exit(0);
    else if (cmd.first == "config_update") {
        // what to do with port settings?
        ElementPtr zonelist_el = (cmd.second)->get("zones");
        // We could walk through both lists and remove and serve
        // accordingly, or simply clear all and add everything
        zones.clear_zones();
        BOOST_FOREACH(ElementPtr zone, zonelist_el->list_value()) {
            zones.serve(zone->string_value());
        }
    }
}

void
ParkingLot::serve(std::string zone_name) {
    zones.serve(zone_name);
}
