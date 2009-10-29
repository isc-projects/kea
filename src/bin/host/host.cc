// host rewritten in C++ using BIND 10 DNS library

#include <arpa/inet.h>
#include <netdb.h>          // for getaddrinfo
#include <sys/time.h>       // for gettimeofday

#include <iostream>
using namespace std;    // I don't understand why this is needed for cout

#include "dns/rrset.h"
#include "dns/message.h"

using namespace isc::dns;

char* dns_type = NULL;    // not set, so A, AAAA, MX
char* server = "127.0.0.1";
int   verbose = 1;       // later make this an option and default to 0
int   first_time = 1;
struct timeval before_time, after_time;

int
host_lookup(char* name, char* type)
{

    Message msg;

    msg.setQid(0); // does this matter?

// TODO: add switch for this
    msg.setRD(true);    // set recursive bit

    msg.addQuestion(Name(name),
    RRClass::IN,    // IN class only for now
    RRType(type));  // if NULL then:
// terminate called after throwing an instance of 'std::logic_error'
//  what():  basic_string::_S_construct NULL not valid


    msg.toWire();

    struct addrinfo hints, *res;
    int e;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0; // not using AI_NUMERICHOST in case to bootstrap
    e = getaddrinfo(server, "53", &hints, &res);

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

            if (verbose) {
                gettimeofday(&after_time, NULL);
            }

            // HEADER and QUESTION SECTION:
            std::cout << rmsg.toText() << std::endl;
// ;; ANSWER SECTION:
//        std::cout << rmsg.getBuffer().getSection(SECTION_ANSWER).toText();
// SECTION_AUTHORITY
// SECTION_ADDITIONAL

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

            std::cout << "\nReceived " <<
                boost::lexical_cast<string>(rmsg.getBuffer().getSize()) <<
                " bytes in " << elapsed_time << " ms\n";
// TODO: " bytes from 127.0.0.1#53 in 0 ms
        } catch (...) {
            std::cerr << "parse failed" << std::endl;
        }
    }

    freeaddrinfo(res);

} // host_lookup()

int
main(int argc, char* argv[])
{

    if (argc < 2) {
        cout << "Usage: host hostname [server]\n";
    }
    else {

        if (argc >= 3) {
          server = argv[2];
        }

        if (!dns_type) {
            host_lookup(argv[1], "A");
// TODO: don't do next if doesn't exist
            host_lookup(argv[1], "AAAA");
//          host_lookup(argv[1], "MX");
// No MX yet
// terminate called after throwing an instance of 'isc::dns::DNSInvalidRRType'
        }

    }

    return (0);
}


