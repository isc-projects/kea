// host rewritten in C++ using BIND 10 DNS library

#include <arpa/inet.h>
#include <netdb.h>          // for getaddrinfo

#include <iostream>
using namespace std;    // I don't understand why this is needed for cout

#include "rrset.h"
#include "message.h"

using namespace isc::dns;

char* dns_type = "A";    // A is the default lookup type
char* server = "127.0.0.1";
int   verbose = 1;       // later make this an option and default to 0

int
main(int argc, char* argv[])
{
    Message msg;

    if (argc < 2) {
        cout << "Usage: host _hostname_\n";
    }
    else {

        if (verbose) {
            cout << "Trying \"" << argv[1] << "\"\n";
        }

        if (argc >= 3) {
          server = argv[2];
        }

        msg.setQid(0); // does this matter?

// TODO: add switch for this
        msg.setRD(true);    // set recursive bit

        msg.addQuestion(Name(argv[1]),
            RRClass::IN,    // IN class only for now
            RRType(dns_type));

        msg.toWire();

        struct addrinfo hints, *res;
        int e;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = 0; // not using AI_NUMERICHOST in case to bootstrap
        e = getaddrinfo(server, "53", &hints, &res);

        if (verbose) {
            cout << "Using domain server:\n";
            cout << "Name: " << server << "\n";
//            cout << "Address: " << server << "#" << port << "\n";
//            cout << "Aliases: " << server << "\n";
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
                std::cout << rmsg.toText() << std::endl;
            } catch (...) {
                std::cerr << "parse failed" << std::endl;
            }
        }

// QUESTION SECTION:

// ;; ANSWER SECTION:

        std::cout << "\nReceived " <<
            boost::lexical_cast<string>(rmsg.getBuffer().getSize()) <<
            " bytes\n";
// TODO: " bytes from 127.0.0.1#53 in 0 ms

// TODO: do this for A, AAAA, MX

        freeaddrinfo(res);

    }

    return (0);
}


