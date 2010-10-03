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

#include <recurse/spec_config.h>
#include <recurse/common.h>
#include <recurse/change_user.h>
#include <recurse/recursor.h>

using namespace std;
using namespace isc::data;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::dns;
using namespace isc::xfr;
using namespace asiolink;

namespace {

bool verbose_mode = false;

const string PROGRAM = "Recurse";
const char* DNSPORT = "5300";

IOService* io_service;
Recursor *recursor;

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
        io_service->stop();
    }
    
    return (answer);
}

void
usage() {
    cerr << "Usage: b10-recurse -f nameserver [-a address] [-p port] "
            "[-4|-6] [-nv]" << endl;
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
    bool use_ipv4 = true, use_ipv6 = true, cache = true;

    while ((ch = getopt(argc, argv, "46a:f:np:u:v")) != -1) {
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
        case 'n':
            cache = false;
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
        cerr << "[b10-recurse] Error: -4 and -6 can't coexist" << endl;
        usage();
    }

    if ((!use_ipv4 || !use_ipv6) && address != NULL) {
        cerr << "[b10-recurse] Error: -4|-6 and -a can't coexist" << endl;
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
        recursor ->setVerbose(verbose_mode);
        cout << "[b10-recurse] Server created." << endl;

        IOCallback* checkin = recursor->getCheckinProvider();
        DNSLookup* lookup = recursor->getDNSLookupProvider();
        DNSAnswer* answer = recursor->getDNSAnswerProvider();

        if (address != NULL) {
            // XXX: we can only specify at most one explicit address.
            // This also means the server cannot run in the dual address
            // family mode if explicit addresses need to be specified.
            // We don't bother to fix this problem, however.  The -a option
            // is a short term workaround until we support dynamic listening
            // port allocation.
            io_service = new IOService(*port, *address,
                                       checkin, lookup, answer);
        } else {
            io_service = new IOService(*port, use_ipv4, use_ipv6,
                                       checkin, lookup, answer);
        }
        recursor->setIOService(*io_service);
        cout << "[b10-recurse] IOService created." << endl;

        cc_session = new Session(io_service->get_io_service());
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
        io_service->run();
    } catch (const std::exception& ex) {
        cerr << "[b10-recurse] Server failed: " << ex.what() << endl;
        ret = 1;
    }

    delete config_session;
    delete cc_session;
    delete io_service;
    delete recursor;

    return (ret);
}
