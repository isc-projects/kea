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
#include <cassert>
#include <iostream>

#include <cc/session.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <cc/session.h>
#include <config/ccsession.h>
#include <util/buffer.h>
#include <dhcp4/spec_config.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp/iface_mgr.h>
#include <asiolink/asiolink.h>

using namespace isc::asiolink;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::log;
using namespace isc::util;
using namespace std;

namespace isc {
namespace dhcp {

ControlledDhcpv4Srv* ControlledDhcpv4Srv::server_ = NULL;

ConstElementPtr
ControlledDhcpv4Srv::dhcp4ConfigHandler(ConstElementPtr new_config) {
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_CONFIG_UPDATE)
              .arg(new_config->str());
    ConstElementPtr answer = isc::config::createAnswer(0,
                             "Thank you for sending config.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv4Srv::dhcp4CommandHandler(const string& command, ConstElementPtr args) {
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_COMMAND_RECEIVED)
              .arg(command).arg(args->str());
    if (command == "shutdown") {
        if (ControlledDhcpv4Srv::server_) {
            ControlledDhcpv4Srv::server_->shutdown();
        } else {
            LOG_WARN(dhcp4_logger, DHCP4_NOT_RUNNING);
            ConstElementPtr answer = isc::config::createAnswer(1,
                                     "Shutdown failure.");
            return (answer);
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
            "/src/bin/dhcp4/dhcp4.spec";
    } else {
        specfile = string(DHCP4_SPECFILE_LOCATION);
    }

    /// @todo: Check if session is not established already. Throw, if it is.

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_CCSESSION_STARTING)
              .arg(specfile);
    cc_session_ = new Session(io_service_.get_io_service());
    config_session_ = new ModuleCCSession(specfile, *cc_session_,
                                          dhcp4ConfigHandler,
                                          dhcp4CommandHandler, false);
    config_session_->start();

    /// Integrate the asynchronous I/O model of BIND 10 configuration
    /// control with the "select" model of the DHCP server.  This is
    /// fully explained in \ref dhcpv4Session.
    int ctrl_socket = cc_session_->getSocketDesc();
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_CCSESSION_STARTED)
              .arg(ctrl_socket);
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

    // deregister session socket
    IfaceMgr::instance().set_session_socket(IfaceMgr::INVALID_SOCKET, NULL);
}

ControlledDhcpv4Srv::ControlledDhcpv4Srv(uint16_t port /*= DHCP4_SERVER_PORT*/)
    :Dhcpv4Srv(port), cc_session_(NULL), config_session_(NULL) {
    server_ = this; // remember this instance for use in callback
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

isc::data::ConstElementPtr
ControlledDhcpv4Srv::execDhcpv4ServerCommand(const std::string& command_id,
                                             isc::data::ConstElementPtr args) {
    try {
        return (dhcp4CommandHandler(command_id, args));
    } catch (const Exception& ex) {
        ConstElementPtr answer = isc::config::createAnswer(1, ex.what());
        return (answer);
    }
}


};
};
