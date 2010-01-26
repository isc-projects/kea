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

ParkingLot::ParkingLot(int port) {
    /*ns1 = Rdata::RdataPtr(new NS("ns1.parking.example"));
    ns2 = Rdata::RdataPtr(new NS("ns2.parking.example"));
    ns3 = Rdata::RdataPtr(new NS("ns3.parking.example"));
    a = Rdata::RdataPtr(new A("127.0.0.1"));
    aaaa = Rdata::RdataPtr(new AAAA("::1"));
    */

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

        msg.makeResponse();
        msg.setAA(true);
        TTL default_ttl = TTL(3600);

        Name zname;
        Name name = query->getName();
        RRClass qclass = query->getClass();
        RRType qtype = query->getType();
        SearchResult::status_type status;
        bool included_ns = false;
        if (data_source.hasZoneFor(query->getName(), zname)) {
            status = data_source.addToMessage(msg, SECTION_ANSWER, zname, name, qclass, qtype);
            // rcode is based on this result?
            if (status == SearchResult::name_not_found) {
                msg.setRcode(Message::RCODE_NXDOMAIN);
                if (qtype != RRType::NS) {
                    status = data_source.addToMessage(msg, SECTION_AUTHORITY, zname, zname, qclass, RRType::SOA);
                }
            } else {
                if (qtype != RRType::NS) {
                    status = data_source.addToMessage(msg, SECTION_AUTHORITY, zname, zname, qclass, RRType::NS);
                }
                included_ns = true;
            }
            // If we included NS records, and their target falls below the zone, add glue
            if (included_ns) {
                BOOST_FOREACH(RRsetPtr rrset, msg.getSection(SECTION_ANSWER)) {
                    if (rrset->getType() == RRType::NS) {
                        BOOST_FOREACH(Rdata::RdataPtr rdata, rrset->getRdatalist()) {
                            /* no direct way to get the Name from the rdata fields? */
                            Name ns_name = Name(rdata->toText());
                            data_source.addToMessage(msg, SECTION_ADDITIONAL, zname, ns_name, qclass, RRType::A);
                            data_source.addToMessage(msg, SECTION_ADDITIONAL, zname, ns_name, qclass, RRType::AAAA);
                        }
                    }
                }
                BOOST_FOREACH(RRsetPtr rrset, msg.getSection(SECTION_AUTHORITY)) {
                    if (rrset->getType() == RRType::NS) {
                        BOOST_FOREACH(Rdata::RdataPtr rdata, rrset->getRdatalist()) {
                            /* no direct way to get the Name from the rdata fields? */
                            Name ns_name = Name(rdata->toText());
                            data_source.addToMessage(msg, SECTION_ADDITIONAL, zname, ns_name, qclass, RRType::A);
                            data_source.addToMessage(msg, SECTION_ADDITIONAL, zname, ns_name, qclass, RRType::AAAA);
                        }
                    }
                }
            }
        } else {
            msg.setRcode(Message::RCODE_SERVFAIL);
        }
        msg.toWire();
        cout << "sending a response (" <<
            boost::lexical_cast<string>(msg.getBuffer().getSize())
                  << " bytes):\n" << msg.toText() << endl;
        msg.getBuffer().sendTo(s, *sa, sa_len);
    }
}

ElementPtr
ParkingLot::updateConfig(isc::data::ElementPtr config) {
    if (config->contains("zones")) {
        data_source.clear_zones();
        BOOST_FOREACH(isc::data::ElementPtr zone_el, config->get("zones")->listValue()) {
            data_source.serve(zone_el->stringValue());
        }
    }
    if (config->contains("port")) {
        // todo: what to do with port change. restart automatically?
        // ignore atm
    }
    if (config->contains("a_records")) {
        data_source.clearARecords();
        BOOST_FOREACH(isc::data::ElementPtr rel, config->get("a_records")->listValue()) {
            data_source.addARecord(rel->stringValue());
        }
    }
    if (config->contains("aaaa_records")) {
        data_source.clearAAAARecords();
        BOOST_FOREACH(isc::data::ElementPtr rel, config->get("aaaa_records")->listValue()) {
            data_source.addAAAARecord(rel->stringValue());
        }
    }
    if (config->contains("ns_records")) {
        data_source.clearNSRecords();
        BOOST_FOREACH(isc::data::ElementPtr rel, config->get("ns_records")->listValue()) {
            data_source.addNSRecord(rel->stringValue());
        }
    }
    return isc::data::Element::createFromString("{ \"result\": [0] }");
}


