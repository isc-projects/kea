// host rewritten in C++ using BIND 10 DNS library

#include <arpa/inet.h>
#include <netdb.h>          // for getaddrinfo
#include <sys/time.h>       // for gettimeofday

#include <string>
#include <iostream>

#include "dns/cpp/buffer.h"
#include "dns/cpp/name.h"
#include "dns/cpp/message.h"
#include "dns/cpp/messagerenderer.h"
#include "dns/cpp/rrclass.h"
#include "dns/cpp/rrtype.h"
#include "dns/cpp/rrset.h"
#include "dns/cpp/message.h"

using namespace std;
using namespace isc::dns;

char* dns_type = NULL;    // not set, so A, AAAA, MX
std::string server = "127.0.0.1";
int   verbose = 0;
int   first_time = 1;
bool  recursive_bit = true;
struct timeval before_time, after_time;

int
host_lookup(char* name, std::string type)
{

    Message msg;

    msg.setQid(0); // does this matter?

// TODO: add switch for this
    msg.setOpcode(Opcode::QUERY());
    msg.setRcode(Rcode::NOERROR());
    if (recursive_bit) {
        msg.setHeaderFlag(MessageFlag::RD());    // set recursive bit
    }

    msg.addQuestion(Question(Name(name),
                             RRClass::IN(),    // IN class only for now
                             RRType(type)));  // if NULL then:
// terminate called after throwing an instance of 'std::logic_error'
//  what():  basic_string::_S_construct NULL not valid

    OutputBuffer obuffer(512);
    MessageRenderer renderer(obuffer);
    msg.toWire(renderer);

    struct addrinfo hints, *res;
    int e;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0; // not using AI_NUMERICHOST in case to bootstrap
    e = getaddrinfo(server.c_str(), "53", &hints, &res);

    if (verbose) {
        cout << "Trying \"" << name << "\"\n";
    }

    if (verbose && first_time) {
        // this is only output the first time
        first_time = 0;
        cout << "Using domain server:\n";
        cout << "Name: " << server << "\n";
// TODO: I guess I have to do a lookup to get that address and aliases too
//        cout << "Address: " << address << "\n" ; // "#" << port << "\n";
//        cout << "Aliases: " << server << "\n";
    }

    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (s < 0) {
        cerr << "failed to open socket" << endl;
        return (1);
    }

    if (verbose) {
        gettimeofday(&before_time, NULL);
    }

    sendto(s, obuffer.getData(), obuffer.getLength(), 0, res->ai_addr,
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
            Message rmsg;
            InputBuffer ibuffer(recvbuf, cc);

            rmsg.fromWire(ibuffer);
            if (!verbose) {
                  for (RRsetIterator it = rmsg.beginSection(Section::ANSWER());
                       it != rmsg.endSection(Section::ANSWER());
                       ++it) {
                      if ((*it)->getType() != RRType::A()) {
                          continue;
                      }

                      RdataIteratorPtr rit = (*it)->getRdataIterator();
                      for (rit->first(); !rit->isLast(); rit->next()) {
                          // instead of using my name, maybe use returned label?
                          cout << name << " has address " <<
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
// TODO: figure out the new libdns way to test if NXDOMAIN

                std::cout << "Received " << cc <<
                    " bytes in " << elapsed_time << " ms\n";
                // TODO: " bytes from 127.0.0.1#53 in 0 ms

            } //verbose
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

int
main(int argc, char* argv[])
{

    int c;

    while ((c = getopt(argc, argv, "rt:v")) != -1)
        switch (c) {

        case 'r':
            recursive_bit = false;
            break;
        case 't':
            dns_type = optarg;
            break;
        case 'v':
            verbose = 1;
            break;

    }
    argc -= optind;
    argv += optind;

    if (argc < 1) {
        cout << "Usage: host [-vr] [-t type] hostname [server]\n";
        exit(1);
    }

    if (argc >= 2) {
      server = argv[1];
    }

    if (!dns_type) {
        host_lookup(argv[0], "A");
// TODO: don't do next if A doesn't exist
        host_lookup(argv[0], "AAAA");
        host_lookup(argv[0], "MX");
    } else {
        host_lookup(argv[0], dns_type); 
    }
    return (0);
}


