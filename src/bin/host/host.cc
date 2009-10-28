/*
   host rewritten in C++ using BIND 10 DNS library

 */

#include <arpa/inet.h>

#include <iostream>
using namespace std;    // I don't understand why this is needed for cout

/*     #include "name.h" */
#include "rrset.h"
#include "message.h"

using namespace isc::dns;

char* dns_type = "A";    // A is the default lookup type

int
main(int argc, char* argv[])
{
    Message msg;

    if (argc < 2) {
        cout << "Usage: host _hostname_\n";
    }
    else {

        cout << argv[1] << "\n";
        msg.setQid(0); // does this matter?

// TODO: add switch for this
          msg.setRD(true);    // set recursive bit

        msg.addQuestion(Name(argv[1]),
            RRClass::IN,    // IN class only for now
            RRType(dns_type));

        msg.toWire();

        int s = socket(PF_INET,        // IPv4 for now
            SOCK_DGRAM, IPPROTO_UDP);    // UDP for now
        if (s < 0) {
            cerr << "failed to open socket" << endl;
            return (1);
        }
        
        char* sin_addr;
        inet_pton(AF_INET, "127.0.0.1", sin_addr);
        int size = sizeof(sin_addr);

//        msg.SingleBuffer().sendTo(s, sin_addr, size);

    }
}


