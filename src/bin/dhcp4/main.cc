// Copyright (C) 2009-2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include <cassert>
#include <iostream>

#include <cc/session.h>
#include <cc/data.h>

#include <exceptions/exceptions.h>
#include <cc/session.h>
#include <config/ccsession.h>

#include <util/buffer.h>
#include <log/dummylog.h>

#include <dhcp4/spec_config.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp/iface_mgr.h>

#include <asiolink/asiolink.h>
#include <log/logger_support.h>

const char* const DHCP4_NAME = "b10-dhcp4";

using namespace std;
using namespace isc::util;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::data;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::asiolink;

namespace {

bool verbose_mode = false;

void
usage() {
    cerr << "Usage:  b10-dhcp4 [-v]"
         << endl;
    cerr << "\t-v: verbose output" << endl;
    exit(1);
}
} // end of anonymous namespace

// Global objects are ugly, but that is the most convenient way of
// having it accessible from handlers.
IOService io_service;

// The same applies to global pointers. Ugly, but useful.
Dhcpv4Srv* server = NULL;

ConstElementPtr
dhcp4_config_handler(ConstElementPtr new_config) {
    cout << "b10-dhcp4: Received new config:" << new_config->str() << endl;
    ConstElementPtr answer = isc::config::createAnswer(0,
                             "Thanks for sending config.");
    return (answer);
}

ConstElementPtr
dhcp4_command_handler(const string& command, ConstElementPtr args) {
    cout << "b10-dhcp4: Received new command: [" << command << "], args="
         << args->str() << endl;
    if (command == "shutdown") {
        if (server) {
            server->shutdown();
        }
        io_service.stop();
        ConstElementPtr answer = isc::config::createAnswer(0,
                                 "Shutting down.");
        return (answer);
    }

    ConstElementPtr answer = isc::config::createAnswer(1,
                             "Unrecognized command.");

    return (answer);
}

void session_reader(void) {
    io_service.run_one();
}

void establish_session() {

    Session* cc_session = NULL;
    ModuleCCSession* config_session = NULL;

    string specfile;
    if (getenv("B10_FROM_BUILD")) {
        specfile = string(getenv("B10_FROM_BUILD")) +
            "/src/bin/auth/dhcp4.spec";
    } else {
        specfile = string(DHCP4_SPECFILE_LOCATION);
    }

    cout << "b10-dhcp4: my specfile is " << specfile << endl;

    cc_session = new Session(io_service.get_io_service());

    config_session = new ModuleCCSession(specfile, *cc_session,
                                         dhcp4_config_handler,
                                         dhcp4_command_handler, false);

    config_session->start();

    int ctrl_socket = cc_session->getSocketDesc();
    cout << "b10-dhcp4: Control session started, socket="
         << ctrl_socket << endl;

    IfaceMgr::instance().set_session_socket(ctrl_socket, session_reader);

    // cout << "b10-dhcp4: About to call io_service.run()" << endl;
    // io_service.run();
    // cout << "b10-dhcp4: Returned from io_service.run()" << endl;
}

int
main(int argc, char* argv[]) {
    int ch;

    while ((ch = getopt(argc, argv, ":v")) != -1) {
        switch (ch) {
        case 'v':
            verbose_mode = true;
            isc::log::denabled = true;
            break;
        case ':':
        default:
            usage();
        }
    }

    // Initialize logging.  If verbose, we'll use maximum verbosity.
    isc::log::initLogger(DHCP4_NAME,
                         (verbose_mode ? isc::log::DEBUG : isc::log::INFO),
                         isc::log::MAX_DEBUG_LEVEL, NULL);


    cout << "My pid=" << getpid() << endl;

    if (argc - optind > 0) {
        usage();
    }

    int ret = 0;

    try {

        establish_session();

        cout << "[b10-dhcp4] Initiating DHCPv4 server operation." << endl;

        server = new Dhcpv4Srv();

        server->run();

        delete server;

    } catch (const std::exception& ex) {
        cerr << "[b10-dhcp4] Server failed: " << ex.what() << endl;
        ret = 1;
    }

    return (ret);
}
