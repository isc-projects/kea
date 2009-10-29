// host rewritten in C++ using BIND 10 DNS library

#include <arpa/inet.h>
#include <netdb.h>          // for getaddrinfo

#include <iostream>
using namespace std;    // I don't understand why this is needed for cout

#include "rrset.h"
#include "message.h"

using namespace isc::dns;

char* dns_type = NULL;    // not set, so A, AAAA, MX
char* server = "127.0.0.1";
int   verbose = 1;       // later make this an option and default to 0
int   first_time = 1;

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
            // HEADER and QUESTION SECTION:
            std::cout << rmsg.toText() << std::endl;
// ;; ANSWER SECTION:
//        std::cout << rmsg.getBuffer().getSection(SECTION_ANSWER).toText();
// SECTION_AUTHORITY
// SECTION_ADDITIONAL

            std::cout << "\nReceived " <<
                boost::lexical_cast<string>(rmsg.getBuffer().getSize()) <<
                " bytes\n";
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
        cout << "Usage: host _hostname_\n";
    }
    else {

        if (argc >= 3) {
          server = argv[2];
        }

        if (!dns_type) {
            host_lookup(argv[1], "A");
            host_lookup(argv[1], "AAAA");
//          host_lookup(argv[1], "MX");
// No MX yet
// terminate called after throwing an instance of 'isc::dns::DNSInvalidRRType'
        }

    }

    return (0);
}


