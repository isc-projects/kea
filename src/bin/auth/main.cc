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
#include <netinet/in.h>  // IPPROTO_UDP
#include <stdlib.h>

#include <set>
#include <iostream>

#include <boost/foreach.hpp>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/message.h>

#include <cc/session.h>
#include <cc/data.h>
#include <config/ccsession.h>

#include "common.h"
#include "config.h"
#include "auth_srv.h"

#include <boost/foreach.hpp>

using namespace std;
using namespace isc::data;
using namespace isc::cc;
using namespace isc::config;

namespace {
const string PROGRAM = "Auth";
const char* DNSPORT = "5300";
}

/* need global var for config/command handlers.
 * todo: turn this around, and put handlers in the authserver
 * class itself? */
namespace {
AuthSrv *auth_server;
}

static void
usage() {
    cerr << "Usage: b10-auth [-p port] [-4|-6]" << endl;
    exit(1);
}

ElementPtr
my_config_handler(ElementPtr new_config)
{
    return auth_server->updateConfig(new_config);
}

ElementPtr
my_command_handler(const string& command, const ElementPtr args) {
    ElementPtr answer = createAnswer(0);

    if (command == "print_message") 
    {
        cout << args << endl;
        /* let's add that message to our answer as well */
        answer->get("result")->add(args);
    }
    return answer;
}

static int
getSocket(int af, const char* port) {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = af;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = IPPROTO_UDP;

    int error = getaddrinfo(NULL, port, &hints, &res);
    if (error != 0) {
        cerr << "getaddrinfo failed: " << gai_strerror(error);
        return (-1);
    }

    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (s < 0) {
        cerr << "failed to open socket" << endl;
        return (-1);
    }

    if (af == AF_INET6) {
        int on = 1;
        if (setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on)) < 0) {
            cerr << "couldn't set IPV6_V6ONLY socket option" << endl;
        }
    }

    if (bind(s, res->ai_addr, res->ai_addrlen) < 0) {
        cerr << "binding socket failure" << endl;
        close(s);
        return (-1);
    }

    return (s);
}

int
main(int argc, char* argv[]) {
    int ch;
    const char* port = DNSPORT;
    bool ipv4_only = false, ipv6_only = false;
    int ps4 = -1, ps6 = -1;

    while ((ch = getopt(argc, argv, "46p:")) != -1) {
        switch (ch) {
        case '4':
            ipv4_only = true;
            break;
        case '6':
            ipv6_only = true;
            break;
        case 'p':
            port = optarg;
            break;
        case '?':
        default:
            usage();
        }
    }

    if (argc - optind > 0) {
        usage();
    }

    if (ipv4_only && ipv6_only) {
        cerr << "-4 and -6 can't coexist" << endl;
        usage();
    }
    if (!ipv6_only) {
        ps4 = getSocket(AF_INET, port);
        if (ps4 < 0) {
            exit(1);
        }
    }
    if (!ipv4_only) {
        ps6 = getSocket(AF_INET6, port);
        if (ps6 < 0) {
            if (ps4 < 0) {
                close(ps4);
            }
            exit(1);
        }
    }

    auth_server = new AuthSrv;

    // initialize command channel
    int ret = 0;
    try {
        string specfile;
        if (getenv("B10_FROM_SOURCE")) {
            specfile = string(getenv("B10_FROM_SOURCE")) +
                "/src/bin/auth/auth.spec";
        } else {
            specfile = string(AUTH_SPECFILE_LOCATION);
        }
        ModuleCCSession cs(specfile, my_config_handler, my_command_handler);

        // main server loop
        fd_set fds;
        int ss = cs.getSocket();
        int nfds = max(max(ps4, ps6), ss) + 1;
        int counter = 0;

        cout << "Server started." << endl;
        while (true) {
            FD_ZERO(&fds);
            if (ps4 >= 0) {
                FD_SET(ps4, &fds);
            }
            if (ps6 >= 0) {
                FD_SET(ps6, &fds);
            }
            FD_SET(ss, &fds);

            int n = select(nfds, &fds, NULL, NULL, NULL);
            if (n < 0) {
                throw FatalError("select error");
            }

            if (ps4 >= 0 && FD_ISSET(ps4, &fds)) {
                ++counter;
                auth_server->processMessage(ps4);
            }
            if (ps6 >= 0 && FD_ISSET(ps6, &fds)) {
                ++counter;
                auth_server->processMessage(ps6);
            }
    
            if (FD_ISSET(ss, &fds)) {
                cs.check_command();
            }
        }
    } catch (SessionError se) {
        cout << se.what() << endl;
        ret = 1;
    }

    if (ps4 >= 0) {
        close(ps4);
    }
    if (ps6 >= 0) {
        close(ps6);
    }
    delete auth_server;
    return (ret);
}
