// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/select.h>
//#include <netdb.h>
//#include <netinet/in.h>
//#include <stdlib.h>
//#include <errno.h>

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
#include <dhcp4/ctrl_dhcp4_srv.h>
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

namespace isc {
namespace dhcp {

ControlledDhcpv4Srv* ControlledDhcpv4Srv::server_ = NULL;

ConstElementPtr
dhcp4_config_handler(ConstElementPtr new_config) {
    cout << "b10-dhcp4: Received new config:" << new_config->str() << endl;
    ConstElementPtr answer = isc::config::createAnswer(0,
                             "Thank you for sending config.");
    return (answer);
}

ConstElementPtr
dhcp4_command_handler(const string& command, ConstElementPtr args) {
    cout << "b10-dhcp4: Received new command: [" << command << "], args="
         << args->str() << endl;
    if (command == "shutdown") {
        if (ControlledDhcpv4Srv::server_) {
            ControlledDhcpv4Srv::server_->shutdown();
        }
        ConstElementPtr answer = isc::config::createAnswer(0,
                                 "Shutting down.");
        return (answer);
    }

    ConstElementPtr answer = isc::config::createAnswer(1,
                             "Unrecognized command.");

    return (answer);
}

void ControlledDhcpv4Srv::sessionReader(void) {
    // Process one asio event. If there are more events, iface_mgr will call
    // this callback more than once.
    if (server_) {
        server_->io_service_.run_one();
    }
}

void ControlledDhcpv4Srv::establishSession() {
    
    string specfile;
    if (getenv("B10_FROM_BUILD")) {
        specfile = string(getenv("B10_FROM_BUILD")) +
            "/src/bin/auth/dhcp4.spec";
    } else {
        specfile = string(DHCP4_SPECFILE_LOCATION);
    }

    /// @todo: Check if session is not established already. Throw, if it is.
    
    cout << "b10-dhcp4: my specfile is " << specfile << endl;
    
    cc_session_ = new Session(io_service_.get_io_service());

    config_session_ = new ModuleCCSession(specfile, *cc_session_,
                                          dhcp4_config_handler,
                                          dhcp4_command_handler, false);
    config_session_->start();

    int ctrl_socket = cc_session_->getSocketDesc();
    cout << "b10-dhcp4: Control session started, socket="
         << ctrl_socket << endl;

    IfaceMgr::instance().set_session_socket(ctrl_socket, sessionReader);
}

void ControlledDhcpv4Srv::disconnectSession() {
    if (config_session_) {
        delete config_session_;
        config_session_ = NULL;
    }
    if (cc_session_) {
        cc_session_->disconnect();
        delete cc_session_;
        cc_session_ = NULL;
    }
}

ControlledDhcpv4Srv::ControlledDhcpv4Srv(uint16_t port /*= DHCP4_SERVER_PORT*/,
                                             bool verbose /* false */)
    :Dhcpv4Srv(port), cc_session_(NULL), config_session_(NULL) {

    // Initialize logging.  If verbose, we'll use maximum verbosity.
    isc::log::initLogger(DHCP4_NAME,
                         (verbose ? isc::log::DEBUG : isc::log::INFO),
                         isc::log::MAX_DEBUG_LEVEL, NULL);
    server_ = this; // remember this instance for use in callback
    
    establishSession();
}

void ControlledDhcpv4Srv::shutdown() {
    io_service_.stop(); // Stop ASIO transmissions
    Dhcpv4Srv::shutdown(); // Initiate DHCPv4 shutdown procedure.
}

ControlledDhcpv4Srv::~ControlledDhcpv4Srv() {
    disconnectSession();

    server_ = NULL; // forget this instance. There should be no callback anymore
                    // at this stage anyway.
}

};
};
