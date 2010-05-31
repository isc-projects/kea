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

#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include <cassert>
#include <iostream>

#include <boost/foreach.hpp>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <cc/session.h>
#include <cc/data.h>
#include <config/ccsession.h>

#include "spec_config.h"
#include "common.h"
#include "auth_srv.h"
#include "asio_link.h"

using namespace std;
using namespace isc::data;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::dns;

namespace {

bool verbose_mode = false;

const string PROGRAM = "Auth";
const char* DNSPORT = "5300";

/* need global var for config/command handlers.
 * todo: turn this around, and put handlers in the authserver
 * class itself? */
AuthSrv *auth_server;

asio_link::IOService* io_service;

ElementPtr
my_config_handler(ElementPtr new_config) {
    return auth_server->updateConfig(new_config);
}

ElementPtr
my_command_handler(const string& command, const ElementPtr args) {
    ElementPtr answer = createAnswer();

    if (command == "print_message") {
        cout << args << endl;
        /* let's add that message to our answer as well */
        answer->get("result")->add(args);
    } else if (command == "shutdown") {
        io_service->stop();
    }
    
    return answer;
}

void
usage() {
    cerr << "Usage: b10-auth [-p port] [-4|-6]" << endl;
    exit(1);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;
    const char* port = DNSPORT;
    bool use_ipv4 = true, use_ipv6 = true;

    while ((ch = getopt(argc, argv, "46p:v")) != -1) {
        switch (ch) {
        case '4':
            // Note that -4 means "ipv4 only", we need to set "use_ipv6" here,
            // not "use_ipv4".  We could use something like "ipv4_only", but
            // we found the negatively named variable could confuse the code
            // logic.
            use_ipv6 = false;
            break;
        case '6':
            // The same note as -4 applies.
            use_ipv4 = false;
            break;
        case 'p':
            port = optarg;
            break;
        case 'v':
            verbose_mode = true;
            break;
        case '?':
        default:
            usage();
        }
    }

    if (argc - optind > 0) {
        usage();
    }

    if (!use_ipv4 && !use_ipv6) {
        cerr << "[b10-auth] Error: -4 and -6 can't coexist" << endl;
        usage();
    }

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

        auth_server = new AuthSrv;
        auth_server->setVerbose(verbose_mode);

        io_service = new asio_link::IOService(auth_server, port, use_ipv4,
                                              use_ipv6);

        ModuleCCSession cs(specfile, io_service->get_io_service(), my_config_handler, my_command_handler);

        auth_server->setConfigSession(&cs);
        auth_server->updateConfig(ElementPtr());

        
        cout << "[b10-auth] Server started." << endl;
        io_service->run();
    } catch (const std::exception& ex) {
        cerr << ex.what() << endl;
        ret = 1;
    }

    delete io_service;
    delete auth_server;
    return (ret);
}
