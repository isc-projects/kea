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
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include <cassert>
#include <iostream>

#include <boost/foreach.hpp>

#include <asiolink/asiolink.h>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <cc/session.h>
#include <cc/data.h>
#include <config/ccsession.h>

#include <xfr/xfrout_client.h>

#include <auth/change_user.h>
#include <auth/common.h>

#include <recurse/spec_config.h>
#include <recurse/recursor.h>

using namespace std;
using namespace isc::data;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::dns;
using namespace isc::xfr;
using namespace asiolink;

namespace {

static bool verbose_mode = false;

// Default port current 5300 for testing purposes
static const string PROGRAM = "Recurse";
static const char* DNSPORT = "5300";

IOService io_service;
static Recursor *recursor;

ConstElementPtr
my_config_handler(ConstElementPtr new_config) {
    return (recursor->updateConfig(new_config));
}

ConstElementPtr
my_command_handler(const string& command, ConstElementPtr args) {
    ConstElementPtr answer = createAnswer();

    if (command == "print_message") {
        cout << args << endl;
        /* let's add that message to our answer as well */
        answer = createAnswer(0, args);
    } else if (command == "shutdown") {
        io_service.stop();
    }
    
    return (answer);
}

void
usage() {
    cerr << "Usage:  b10-recurse -f nameserver [-a address] [-p port] [-u user]"
                     "[-4|-6] [-v]" << endl;
    cerr << "\t-f: specify the nameserver to which queries should be forwarded"
         << endl;
    cerr << "\t-a: specify the address to listen on (default: all)" << endl;
    cerr << "\t-p: specify the port to listen on (default: " << DNSPORT << ")"
         << endl;
    cerr << "\t-4: listen on all IPv4 addresses (incompatible with -a)" << endl;
    cerr << "\t-6: listen on all IPv6 addresses (incompatible with -a)" << endl;
    cerr << "\t-u: change process UID to the specified user" << endl;
    cerr << "\t-v: verbose output" << endl;
    exit(1);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;
    const char* port = DNSPORT;
    const char* address = NULL;
    const char* forward = NULL;
    const char* uid = NULL;
    bool use_ipv4 = true, use_ipv6 = true;

    while ((ch = getopt(argc, argv, "46a:f:p:u:v")) != -1) {
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
        case 'a':
            address = optarg;
            break;
        case 'f':
            forward = optarg;
            break;
        case 'p':
            port = optarg;
            break;
        case 'u':
            uid = optarg;
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
        cerr << "[b10-auth] Error: Cannot specify both -4 and -6 "
             << "at the same time" << endl;
        usage();
    }

    if ((!use_ipv4 || !use_ipv6) && address != NULL) {
        cerr << "[b10-auth] Error: Cannot specify -4 or -6 "
             << "at the same time as -a" << endl;
        usage();
    }

    if (forward == NULL) {
        cerr << "[b10-recurse] No forward name server specified" << endl;
        usage();
    }

    int ret = 0;

    // XXX: we should eventually pass io_service here.
    Session* cc_session = NULL;
    ModuleCCSession* config_session = NULL;
    try {
        string specfile;
        if (getenv("B10_FROM_BUILD")) {
            specfile = string(getenv("B10_FROM_BUILD")) +
                "/src/bin/recurse/recurse.spec";
        } else {
            specfile = string(RECURSE_SPECFILE_LOCATION);
        }

        recursor = new Recursor(*forward);
        recursor->setVerbose(verbose_mode);
        cout << "[b10-recurse] Server created." << endl;

        SimpleCallback* checkin = recursor->getCheckinProvider();
        DNSLookup* lookup = recursor->getDNSLookupProvider();
        DNSAnswer* answer = recursor->getDNSAnswerProvider();

        DNSService* dns_service;

        if (address != NULL) {
            // XXX: we can only specify at most one explicit address.
            // This also means the server cannot run in the dual address
            // family mode if explicit addresses need to be specified.
            // We don't bother to fix this problem, however.  The -a option
            // is a short term workaround until we support dynamic listening
            // port allocation.
            dns_service = new DNSService(io_service, *port, *address,
                                         checkin, lookup, answer);
        } else {
            dns_service = new DNSService(io_service, *port, use_ipv4, use_ipv6,
                                         checkin, lookup, answer);
        }
        recursor->setDNSService(*dns_service);
        cout << "[b10-recurse] IOService created." << endl;

        cc_session = new Session(io_service.get_io_service());
        cout << "[b10-recurse] Configuration session channel created." << endl;

        config_session = new ModuleCCSession(specfile, *cc_session,
                                             my_config_handler,
                                             my_command_handler);
        cout << "[b10-recurse] Configuration channel established." << endl;

        if (uid != NULL) {
            changeUser(uid);
        }

        recursor->setConfigSession(config_session);
        recursor->updateConfig(ElementPtr());

        cout << "[b10-recurse] Server started." << endl;
        io_service.run();
    } catch (const std::exception& ex) {
        cerr << "[b10-recurse] Server failed: " << ex.what() << endl;
        ret = 1;
    }

    delete config_session;
    delete cc_session;
    delete recursor;

    return (ret);
}
