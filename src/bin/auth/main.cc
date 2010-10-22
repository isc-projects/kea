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

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <cc/session.h>
#include <cc/data.h>
#include <config/ccsession.h>

#include <xfr/xfrout_client.h>

#include <auth/spec_config.h>
#include <auth/common.h>
#include <auth/change_user.h>
#include <auth/auth_srv.h>
#include <asiolink/asiolink.h>

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
static const string PROGRAM = "Auth";
static const char* DNSPORT = "5300";

/* need global var for config/command handlers.
 * todo: turn this around, and put handlers in the authserver
 * class itself? */
static AuthSrv *auth_server;

static IOService io_service;

ConstElementPtr
my_config_handler(ConstElementPtr new_config) {
    return (auth_server->updateConfig(new_config));
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
    cerr << "Usage:  b10-auth [-a address] [-p port] [-u user] [-4|-6] [-nv]"
         << endl;
    cerr << "\t-a: specify the address to listen on (default: all) " << endl;
    cerr << "\t-p: specify the port to listen on (default: " << DNSPORT << ")"
         << endl;
    cerr << "\t-4: listen on all IPv4 addresses (incompatible with -a)" << endl;
    cerr << "\t-6: listen on all IPv6 addresses (incompatible with -a)" << endl;
    cerr << "\t-n: do not cache answers in memory" << endl;
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
    const char* uid = NULL;
    bool use_ipv4 = true, use_ipv6 = true, cache = true;

    while ((ch = getopt(argc, argv, "46a:np:u:v")) != -1) {
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

    int ret = 0;

    // XXX: we should eventually pass io_service here.
    Session* cc_session = NULL;
    Session* xfrin_session = NULL;
    bool xfrin_session_established = false; // XXX (see Trac #287)
    ModuleCCSession* config_session = NULL;
    string xfrout_socket_path;
    if (getenv("B10_FROM_BUILD") != NULL) {
        xfrout_socket_path = string(getenv("B10_FROM_BUILD")) + "/auth_xfrout_conn";
    } else {
        xfrout_socket_path = UNIX_SOCKET_FILE;
    }
    XfroutClient xfrout_client(xfrout_socket_path);
    try {
        string specfile;
        if (getenv("B10_FROM_BUILD")) {
            specfile = string(getenv("B10_FROM_BUILD")) +
                "/src/bin/auth/auth.spec";
        } else {
            specfile = string(AUTH_SPECFILE_LOCATION);
        }

        auth_server = new AuthSrv(cache, xfrout_client);
        auth_server->setVerbose(verbose_mode);
        cout << "[b10-auth] Server created." << endl;

        SimpleCallback* checkin = auth_server->getCheckinProvider();
        DNSLookup* lookup = auth_server->getDNSLookupProvider();
        DNSAnswer* answer = auth_server->getDNSAnswerProvider();

        DNSService* dns_service;
        if (address != NULL) {
            // XXX: we can only specify at most one explicit address.
            // This also means the server cannot run in the dual address
            // family mode if explicit addresses need to be specified.
            // We don't bother to fix this problem, however.  The -a option
            // is a short term workaround until we support dynamic listening
            // port allocation.
            dns_service = new DNSService(io_service,  *port, *address,
                                         checkin, lookup, answer);
        } else {
            dns_service = new DNSService(io_service, *port, use_ipv4,
                                         use_ipv6, checkin, lookup,
                                         answer);
        }
        auth_server->setIOService(io_service);
        cout << "[b10-auth] IOService created." << endl;

        cc_session = new Session(io_service.get_io_service());
        cout << "[b10-auth] Configuration session channel created." << endl;

        config_session = new ModuleCCSession(specfile, *cc_session,
                                             my_config_handler,
                                             my_command_handler);
        cout << "[b10-auth] Configuration channel established." << endl;

        if (uid != NULL) {
            changeUser(uid);
        }

        xfrin_session = new Session(io_service.get_io_service());
        cout << "[b10-auth] Xfrin session channel created." << endl;
        xfrin_session->establish(NULL);
        xfrin_session_established = true;
        cout << "[b10-auth] Xfrin session channel established." << endl;

        // XXX: with the current interface to asiolink we have to create
        // auth_server before io_service while Session needs io_service.
        // In a next step of refactoring we should make asiolink independent
        // from auth_server, and create io_service, auth_server, and
        // sessions in that order.
        auth_server->setXfrinSession(xfrin_session);
        auth_server->setConfigSession(config_session);
        auth_server->updateConfig(ElementPtr());

        cout << "[b10-auth] Server started." << endl;
        io_service.run();
    } catch (const std::exception& ex) {
        cerr << "[b10-auth] Server failed: " << ex.what() << endl;
        ret = 1;
    }

    if (xfrin_session_established) {
        xfrin_session->disconnect();
    }

    delete xfrin_session;
    delete config_session;
    delete cc_session;
    delete auth_server;

    return (ret);
}
