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

#include <map>
#include <iostream>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/message.h>

using std::string;
using std::pair;

using isc::dns::RRset;
using isc::dns::Name;
using isc::dns::TTL;
using isc::dns::RRsetPtr;
using isc::dns::RRType;
using isc::dns::RRClass;
using isc::dns::Message;
using isc::dns::Rdata::IN::A;
using isc::dns::Rdata::IN::AAAA;
using isc::dns::Rdata::Generic::NS;

static void
start_server(int s, const struct addrinfo *res)
{
    if (bind(s, res->ai_addr, res->ai_addrlen) < 0)
        return;

    // Create Database
    typedef pair<string, string> dnskey_t;
    std::map<dnskey_t, std::string> dnsdb;
    dnsdb.insert(pair<dnskey_t, string>(dnskey_t("www.jinmei.org", "A"),
                                        "149.20.54.162"));
    dnsdb.insert(pair<dnskey_t, string>(dnskey_t("www.jinmei.org", "AAAA"),
                                        "2001:4f8:3:36::162"));
    dnsdb.insert(pair<dnskey_t, string>(dnskey_t("www.isc.org", "A"),
                                        "149.20.64.42"));
    dnsdb.insert(pair<dnskey_t, string>(dnskey_t("www.isc.org", "AAAA"),
                                        "2001:4f8:0:2::d"));
    dnsdb.insert(pair<dnskey_t, string>(dnskey_t("isc.org", "NS"),
                                        "sfba.sns-pb.isc.org."));

    int cc;
    struct sockaddr_storage ss;
    struct sockaddr* sa;
    socklen_t sa_len;

    while (1) {
        Message msg;

        sa_len = sizeof(ss);
        sa = static_cast<struct sockaddr*>((void*)&ss);
        cc = msg.getBuffer().recvFrom(s, sa, &sa_len);
        if (cc > 0) {
            try {
                msg.fromWire();
            } catch (...) {
                std::cerr << "parse failed" << std::endl;
                continue;
            }

            std::cout << "received a message:\n" << msg.toText() << std::endl;
            if (msg.getSection(isc::dns::SECTION_QUESTION).size() != 1)
                continue;

            msg.makeResponse();
            msg.setAA(true);

            RRsetPtr query = msg.getSection(isc::dns::SECTION_QUESTION)[0];
            std::map<dnskey_t, string>::const_iterator it;
            isc::dns::Rdata::RDATAPTR rdatap;

            it = dnsdb.find(dnskey_t(query->getName().toText(true),
                                     query->getType().toText()));
            if (it != dnsdb.end()) {
                // XXX: this code logic is NOT clean.  should revisit API.
                if (query->getType() == RRType::A) {
                    rdatap = isc::dns::Rdata::RDATAPTR(new A(it->second));
                } else if (query->getType() == RRType::AAAA) {
                    rdatap = isc::dns::Rdata::RDATAPTR(new AAAA(it->second));
                } else if (query->getType() == RRType::NS) {
                    rdatap = isc::dns::Rdata::RDATAPTR(new NS(it->second));
                }

                msg.setRcode(Message::RCODE_NOERROR);

                RRset* rrset = new RRset(query->getName(), query->getClass(),
                                         query->getType(), TTL(3600));
                rrset->addRdata(rdatap);
                msg.addRrset(isc::dns::SECTION_ANSWER, RRsetPtr(rrset));
            } else {
                msg.setRcode(Message::RCODE_NXDOMAIN);
                // should add SOA to the authority section, but not implemented.
            }

            msg.toWire();
            std::cout << "sending a response (" <<
                boost::lexical_cast<string>(msg.getBuffer().getSize())
                      << " bytes):\n" << msg.toText() << std::endl;
            msg.getBuffer().sendTo(s, *sa, sa_len);
        }
    }
}

int
main(int argc, char* argv[])
{
    Message msg;
    int ch;
    const char* server_address = "127.0.0.1";
    const char* type_name = "A";
    const char* port = "53";
    bool receive_mode = false;

    while ((ch = getopt(argc, argv, "p:rs:t:")) != -1) {
        switch (ch) {
        case 'p':
            port = optarg;
            break;
        case 'r':
            receive_mode = true;
            break;
        case 's':
            server_address = optarg;
            break;
        case 't':
            type_name = optarg;
            break;
        }
    }

    argc -= optind;
    argv += optind;

    if (argc < 1 && !receive_mode) {
        std::cerr << "usage: "
            "dnsmessage-test [-s server_address] [-t qtype] qname\n"
                  << std::endl;
        return (1);
    }

    struct addrinfo hints, *res;
    int e;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = receive_mode ? AI_PASSIVE : 0;
    e = getaddrinfo(server_address, port, &hints, &res);
    if (e != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerror(e) << std::endl;
        return (1);
    }

    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (s < 0) {
        std::cerr << "failed to open socket" << std::endl;
        return (1);
    }

    if (receive_mode) {
        start_server(s, res);
    } else {
        msg.setQid(42);            // can be omitted, then QID will be 0
        msg.setRD(true);
        msg.addQuestion(Name(argv[0]), RRClass::IN, RRType(type_name));
        msg.toWire();
        std::cout << "sending a query (" <<
            boost::lexical_cast<string>(msg.getBuffer().getSize())
                  << " bytes):\n" << msg.toText() << std::endl;
        msg.getBuffer().sendTo(s, *res->ai_addr, res->ai_addrlen);

        Message rmsg;
        struct sockaddr_storage ss;
        struct sockaddr* sa;
        socklen_t sa_len;

        sa_len = sizeof(ss);
        sa = static_cast<struct sockaddr*>((void*)&ss);
        if (rmsg.getBuffer().recvFrom(s, sa, &sa_len) > 0) {
            try {
                rmsg.fromWire();
                std::cout << "received a response (" <<
                    boost::lexical_cast<string>(rmsg.getBuffer().getSize())
                          << " bytes):\n" << rmsg.toText() << std::endl;
            } catch (...) {
                std::cerr << "parse failed" << std::endl;
            }
        }
    }

    freeaddrinfo(res);

    return (0);
}
