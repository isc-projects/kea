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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include <cassert>
#include <iostream>

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
#include <auth/config.h>
#include <auth/command.h>
#include <auth/change_user.h>
#include <auth/auth_srv.h>
#include <asiolink/asiolink.h>
#include <log/dummylog.h>

using namespace std;
using namespace isc::data;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::dns;
using namespace isc::xfr;
using namespace asiolink;

namespace {

bool verbose_mode = false;

/* need global var for config/command handlers.
 * todo: turn this around, and put handlers in the authserver
 * class itself? */
AuthSrv *auth_server;

ConstElementPtr
my_config_handler(ConstElementPtr new_config) {
    return (auth_server->updateConfig(new_config));
}

ConstElementPtr
my_command_handler(const string& command, ConstElementPtr args) {
    assert(auth_server != NULL);
    return (execAuthServerCommand(*auth_server, command, args));
}

void
usage() {
    cerr << "Usage:  b10-auth [-u user] [-nv]"
         << endl;
    cerr << "\t-n: do not cache answers in memory" << endl;
    cerr << "\t-u: change process UID to the specified user" << endl;
    cerr << "\t-v: verbose output" << endl;
    exit(1);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;
    const char* uid = NULL;
    bool cache = true;

    while ((ch = getopt(argc, argv, ":nu:v")) != -1) {
        switch (ch) {
        case 'n':
            cache = false;
            break;
        case 'u':
            uid = optarg;
            break;
        case 'v':
            verbose_mode = true;
            isc::log::denabled = true;
            break;
        case '?':
        default:
            usage();
        }
    }

    if (argc - optind > 0) {
        usage();
    }

    int ret = 0;

    // XXX: we should eventually pass io_service here.
    Session* cc_session = NULL;
    Session* xfrin_session = NULL;
    Session* statistics_session = NULL;
    bool xfrin_session_established = false; // XXX (see Trac #287)
    bool statistics_session_established = false; // XXX (see Trac #287)
    ModuleCCSession* config_session = NULL;
    string xfrout_socket_path;
    if (getenv("B10_FROM_BUILD") != NULL) {
        if (getenv("B10_FROM_SOURCE_LOCALSTATEDIR")) {
            xfrout_socket_path = string("B10_FROM_SOURCE_LOCALSTATEDIR") +
                "/auth_xfrout_conn";
        } else {
            xfrout_socket_path = string(getenv("B10_FROM_BUILD")) +
                "/auth_xfrout_conn";
        }
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
        IOService& io_service = auth_server->getIOService();
        DNSLookup* lookup = auth_server->getDNSLookupProvider();
        DNSAnswer* answer = auth_server->getDNSAnswerProvider();

        DNSService dns_service(io_service, checkin, lookup, answer);
        auth_server->setDNSService(dns_service);
        cout << "[b10-auth] DNSServices created." << endl;

        cc_session = new Session(io_service.get_io_service());
        cout << "[b10-auth] Configuration session channel created." << endl;

        config_session = new ModuleCCSession(specfile, *cc_session,
                                             my_config_handler,
                                             my_command_handler);
        cout << "[b10-auth] Configuration channel established." << endl;

        xfrin_session = new Session(io_service.get_io_service());
        cout << "[b10-auth] Xfrin session channel created." << endl;
        xfrin_session->establish(NULL);
        xfrin_session_established = true;
        cout << "[b10-auth] Xfrin session channel established." << endl;

        statistics_session = new Session(io_service.get_io_service());
        cout << "[b10-auth] Statistics session channel created." << endl;
        statistics_session->establish(NULL);
        statistics_session_established = true;
        cout << "[b10-auth] Statistics session channel established." << endl;

        auth_server->setXfrinSession(xfrin_session);
        auth_server->setStatisticsSession(statistics_session);

        // Configure the server.  configureAuthServer() is expected to install
        // all initial configurations, but as a short term workaround we
        // handle the traditional "database_file" setup by directly calling
        // updateConfig().
        auth_server->setConfigSession(config_session);
        configureAuthServer(*auth_server, config_session->getFullConfig());
        auth_server->updateConfig(ElementPtr());

        if (uid != NULL) {
            changeUser(uid);
        }

        cout << "[b10-auth] Server started." << endl;
        io_service.run();

    } catch (const std::exception& ex) {
        cerr << "[b10-auth] Server failed: " << ex.what() << endl;
        ret = 1;
    }

    if (statistics_session_established) {
        statistics_session->disconnect();
    }

    if (xfrin_session_established) {
        xfrin_session->disconnect();
    }

    delete statistics_session;
    delete xfrin_session;
    delete config_session;
    delete cc_session;
    delete auth_server;

    return (ret);
}
