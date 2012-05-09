// Copyright (C) 2010-2011  Internet Systems Consortium, Inc. ("ISC")
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

// host rewritten in C++ using BIND 10 DNS library

#include <arpa/inet.h>
#include <netdb.h>          // for getaddrinfo
#include <sys/time.h>       // for gettimeofday
#include <sys/socket.h>     // networking functions and definitions on FreeBSD

#include <unistd.h>

#include <string>
#include <iostream>

#include <util/buffer.h>

#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/message.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;

namespace {
char* dns_type = NULL;    // not set, so A, AAAA, MX
const char* server = "127.0.0.1";
const char* server_port = "53";
const char* dns_class  = "IN";
bool verbose = false;
bool dns_any = false;
int first_time = 1;
bool recursive_bit = true;
struct timeval before_time, after_time;

int
host_lookup(const char* const name, const char* const dns_class,
            const char* const type, bool any) {

    Message msg(Message::RENDER);

    msg.setQid(0); // does this matter?

    // TODO: add switch for this
    msg.setOpcode(Opcode::QUERY());
    msg.setRcode(Rcode::NOERROR());
    if (recursive_bit) {
        msg.setHeaderFlag(Message::HEADERFLAG_RD); // set recursive bit
    }

    msg.addQuestion(Question(Name(name),
                             RRClass(dns_class),
                             any ? RRType::ANY() : RRType(type)));  // if NULL then:

    MessageRenderer renderer;
    msg.toWire(renderer);

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0; // not using AI_NUMERICHOST in case to bootstrap
    if (getaddrinfo(server, server_port, &hints, &res) != 0) {
        cerr << "address/port conversion for " << server << ":"
             << server_port << " failed" << endl;
        return (1);
    }

    if (verbose) {
        cout << "Trying \"" << name << "\"\n";
    }

    if (verbose && first_time) {
        // this is only output the first time
        first_time = 0;
        cout << "Using domain server:\n";
        cout << "Name: " << server << "\n";
        // TODO: I guess I have to do a lookup to get that address and aliases
        // too
        //cout << "Address: " << address << "\n" ; // "#" << port << "\n";
        //cout << "Aliases: " << server << "\n";
    }

    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (s < 0) {
        cerr << "failed to open socket" << endl;
        return (1);
    }

    if (verbose) {
        gettimeofday(&before_time, NULL);
    }

    sendto(s, renderer.getData(), renderer.getLength(), 0, res->ai_addr,
           res->ai_addrlen);

    struct sockaddr_storage ss;
    struct sockaddr* sa;
    socklen_t sa_len;

    sa_len = sizeof(ss);
    sa = static_cast<struct sockaddr*>((void*)&ss);

    char recvbuf[4096];
    int cc;
    if ((cc = recvfrom(s, recvbuf, sizeof(recvbuf), 0, sa, &sa_len)) > 0) {
        try {
            Message rmsg(Message::PARSE);
            InputBuffer ibuffer(recvbuf, cc);

            rmsg.fromWire(ibuffer);
            if (!verbose) {
                string description = "";
                for (RRsetIterator it =
                         rmsg.beginSection(Message::SECTION_ANSWER);
                     it != rmsg.endSection(Message::SECTION_ANSWER);
                     ++it) {

                      if ((*it)->getType() == RRType::A()) {
                          description = "has address";
                      }
                      else if ((*it)->getType() == RRType::AAAA()) {
                          description = "has IPv6 address";
                      }
                      else if ((*it)->getType() == RRType::MX()) {
                          description = "mail is handled by";
                      }
                      else if ((*it)->getType() == RRType::TXT()) {
                          description = "descriptive text";
                      }

                      RdataIteratorPtr rit = (*it)->getRdataIterator();
                      for (; !rit->isLast(); rit->next()) {
                          // instead of using my name, maybe use returned label?
                          cout << name << " "  << description << " " <<
                              (*rit).getCurrent().toText() << endl;
                      }
                  }
            } else {
                gettimeofday(&after_time, NULL);

                // HEADER and QUESTION, ANSWER, AUTHORITY, and ADDITIONAL
                std::cout << rmsg.toText() << std::endl;

                if (before_time.tv_usec > after_time.tv_usec) {
                    after_time.tv_usec += 1000000;
                    --after_time.tv_sec;
                }

                int elapsed_time =
                    (after_time.tv_sec - before_time.tv_sec)
                    + ((after_time.tv_usec - before_time.tv_usec))/1000;

                // TODO: if NXDOMAIN, host(1) doesn't show HEADER
                // Host hsdjkfhksjhdfkj not found: 3(NXDOMAIN)
                // TODO: test if NXDOMAIN

                std::cout << "Received " << cc <<
                    " bytes in " << elapsed_time << " ms\n";
                // TODO: " bytes from 127.0.0.1#53 in 0 ms

            } //verbose
/*
TODO: handle InvalidRRClass
TODO: handle invalid type exception
        } catch (InvalidType ivt) {
            std::cerr << "invalid type:" << ivt.what();
*/
        } catch (const exception& ex) {
            std::cerr << "parse failed for " <<
                string(name) << "/" << type << ": " << ex.what() << std::endl;
        } catch (...) {
            std::cerr << "parse failed for " << string(name) << "/" << type;
        }
    }

    freeaddrinfo(res);

    return (0);
} // host_lookup()
}

int
main(int argc, char* argv[]) {
    int c;

    while ((c = getopt(argc, argv, "ac:dp:rt:v")) != -1)
        switch (c) {
        case 'a':
            dns_any = true;
            verbose = true;
            break;
        case 'c':
            dns_class = optarg;
            break;
	// p for port is a non-standard switch
        case 'p':
            server_port = optarg;
            break;
        case 'r':
            recursive_bit = false;
            break;
        case 't':
            dns_type = optarg;
            break;
        case 'd':
            // drop through to v, because debug and verbose are equivalent
        case 'v':
            verbose = true;
            break;
    }
    argc -= optind;
    argv += optind;

    if (argc < 1) {
        cout << "Usage: host [-adrv] [-c class] [-p port] [-t type] hostname [server]\n";
        exit(1);
    }

    if (argc >= 2) {
      server = argv[1];
    }

    if (dns_type == NULL) {
        host_lookup(argv[0], dns_class, "A", dns_any);
        // TODO: don't do next if A doesn't exist
        host_lookup(argv[0], dns_class, "AAAA", dns_any);
        host_lookup(argv[0], dns_class, "MX", dns_any);
    } else {
        // -t overrides -a, regardless of order
        host_lookup(argv[0], dns_class, dns_type, false);
    }
    return (0);
}
