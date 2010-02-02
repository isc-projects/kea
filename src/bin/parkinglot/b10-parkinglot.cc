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
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

#include <algorithm>
#include <set>
#include <iostream>

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rdataclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/message.h>

#include <cc/data.h>

#include "common.h"
#include "builtin.h"
#include "b10-parkinglot.h"

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

using namespace std;

using namespace isc::dns;
using namespace isc::dns::rdata;
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

namespace {
struct GlueInserter {
    GlueInserter(const DataSourceParkingLot& data_source,
                 const Name& zname, const RRClass& qclass,
                 Message& msg) :
        data_source_(&data_source), zname_(&zname), qclass_(&qclass),
        msg_(&msg)
    {}
    void operator()(const RRsetPtr rrset)
    {
        if (rrset->getType() == RRType::NS()) {
            RdataIteratorPtr it = rrset->getRdataIterator();
            for (it->first(); !it->isLast(); it->next()) {
                const generic::NS& nsrdata =
                    dynamic_cast<const generic::NS&>(it->getCurrent());
                data_source_->addToMessage(*msg_, Section::ADDITIONAL(),
                                           *zname_, nsrdata.getNSName(),
                                           *qclass_, RRType::A());
                data_source_->addToMessage(*msg_, Section::ADDITIONAL(),
                                           *zname_, nsrdata.getNSName(),
                                           *qclass_, RRType::AAAA());
            }
        }
    }
    const DataSourceParkingLot* data_source_;
    const Name* zname_;
    const RRClass* qclass_;
    Message* msg_;
};
}

namespace {
const Name authors_name("authors.bind");
const Name version_name("version.bind");
}

void
ParkingLot::processMessage() {
    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);
    int s = sock;
    Message msg;
    char recvbuf[4096];
    int cc;

    if ((cc = recvfrom(s, recvbuf, sizeof(recvbuf), 0, sa, &sa_len)) > 0) {
        InputBuffer buffer(recvbuf, cc);
        try {
            msg.fromWire(buffer);
        } catch (...) {
            cerr << "parse failed" << endl;
            return;
        }

        cout << "received a message:\n" << msg.toText() << endl;

        if (msg.getRRCount(Section::QUESTION()) != 1) {
            return;
        }

        QuestionPtr query = *msg.beginQuestion();

        msg.makeResponse();
        msg.setHeaderFlag(MessageFlag::AA());
        Name zname(".");        // ugly, but should work for now
        msg.setRcode(Rcode::NOERROR());
        if (query->getType() == RRType::TXT() &&
            query->getClass() == RRClass::CH() &&
            query->getName() == authors_name) {
            msg.addRRset(Section::ANSWER(), getBuiltinAuthors().getAnswer());
            msg.addRRset(Section::AUTHORITY(),
                         getBuiltinAuthors().getAuthority());
        } else if (query->getType() == RRType::TXT() &&
                   query->getClass() == RRClass::CH() &&
            query->getName() == version_name) {
            msg.addRRset(Section::ANSWER(), getBuiltinVersion().getAnswer());
            msg.addRRset(Section::AUTHORITY(),
                         getBuiltinVersion().getAuthority());
        } else if (data_source.hasZoneFor(query->getName(), zname)) {
            SearchResult::status_type status =
                data_source.addToMessage(msg, Section::ANSWER(), zname,
                                         query->getName(), query->getClass(),
                                         query->getType());
            bool included_ns = false;

            // rcode is based on this result?
            if (status == SearchResult::name_not_found) {
                msg.setRcode(Rcode::NXDOMAIN());
                if (query->getType() != RRType::NS()) {
                    status = data_source.addToMessage(msg, Section::AUTHORITY(),
                                                      zname, zname,
                                                      query->getClass(),
                                                      RRType::SOA());
                }
            } else {
                if (query->getType() != RRType::NS()) {
                    status = data_source.addToMessage(msg, Section::AUTHORITY(),
                                                      zname, zname,
                                                      query->getClass(),
                                                      RRType::NS());
                }
                included_ns = true;
            }
            // If we included NS records, and their target falls below the zone, add glue
            if (included_ns) {
                for_each(msg.beginSection(Section::ANSWER()),
                         msg.endSection(Section::ANSWER()),
                         GlueInserter(data_source, zname, query->getClass(),
                                      msg));
                for_each(msg.beginSection(Section::AUTHORITY()),
                         msg.endSection(Section::AUTHORITY()),
                         GlueInserter(data_source, zname, query->getClass(),
                                      msg));
            }
        } else {
            msg.setRcode(Rcode::SERVFAIL());
        }

        OutputBuffer obuffer(4096);
        MessageRenderer renderer(obuffer);
        msg.toWire(renderer);
        cout << "sending a response (" <<
            boost::lexical_cast<string>(obuffer.getLength())
                  << " bytes):\n" << msg.toText() << endl;
        sendto(s, obuffer.getData(), obuffer.getLength(), 0, sa, sa_len);
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
