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

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/session.h>
#include <cc/session.h>
#include <config/ccsession.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/spec_config.h>
#include <dhcp6/config_parser.h>
#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

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


ControlledDhcpv6Srv* ControlledDhcpv6Srv::server_ = NULL;

ConstElementPtr
ControlledDhcpv6Srv::dhcp6ConfigHandler(ConstElementPtr new_config) {
    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_UPDATE)
              .arg(new_config->str());

    if (server_) {
        return (configureDhcp6Server(*server_, new_config));
    }

    // That should never happen as we install config_handler after we instantiate
    // the server.
    ConstElementPtr answer = isc::config::createAnswer(1,
           "Configuration rejected, server is during startup/shutdown phase.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::dhcp6CommandHandler(const string& command, ConstElementPtr args) {
    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_COMMAND_RECEIVED)
              .arg(command).arg(args->str());

    if (command == "shutdown") {
        if (ControlledDhcpv6Srv::server_) {
            ControlledDhcpv6Srv::server_->shutdown();
        } else {
            LOG_WARN(dhcp6_logger, DHCP6_NOT_RUNNING);
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

void ControlledDhcpv6Srv::sessionReader(void) {
    // Process one asio event. If there are more events, iface_mgr will call
    // this callback more than once.
    if (server_) {
        server_->io_service_.run_one();
    }
}

void ControlledDhcpv6Srv::establishSession() {

    string specfile;
    if (getenv("B10_FROM_BUILD")) {
        specfile = string(getenv("B10_FROM_BUILD")) +
            "/src/bin/dhcp6/dhcp6.spec";
    } else {
        specfile = string(DHCP6_SPECFILE_LOCATION);
    }

    /// @todo: Check if session is not established already. Throw, if it is.

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_CCSESSION_STARTING)
              .arg(specfile);
    cc_session_ = new Session(io_service_.get_io_service());
    config_session_ = new ModuleCCSession(specfile, *cc_session_,
                                          NULL,
                                          dhcp6CommandHandler, false);
    config_session_->start();

    // We initially create ModuleCCSession() without configHandler, as
    // the session module is too eager to send partial configuration.
    // We want to get the full configuration, so we explicitly call
    // getFullConfig() and then pass it to our configHandler.
    config_session_->setConfigHandler(dhcp6ConfigHandler);

    try {
        configureDhcp6Server(*this, config_session_->getFullConfig());
    } catch (const Dhcp6ConfigError& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_CONFIG_LOAD_FAIL).arg(ex.what());
    }

    /// Integrate the asynchronous I/O model of BIND 10 configuration
    /// control with the "select" model of the DHCP server.  This is
    /// fully explained in \ref dhcpv6Session.
    int ctrl_socket = cc_session_->getSocketDesc();
    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_CCSESSION_STARTED)
              .arg(ctrl_socket);
    IfaceMgr::instance().set_session_socket(ctrl_socket, sessionReader);
}

void ControlledDhcpv6Srv::disconnectSession() {
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

ControlledDhcpv6Srv::ControlledDhcpv6Srv(uint16_t port, const char* dbconfig)
    : Dhcpv6Srv(port, dbconfig), cc_session_(NULL), config_session_(NULL) {
    server_ = this; // remember this instance for use in callback
}

void ControlledDhcpv6Srv::shutdown() {
    io_service_.stop(); // Stop ASIO transmissions
    Dhcpv6Srv::shutdown(); // Initiate DHCPv6 shutdown procedure.
}

ControlledDhcpv6Srv::~ControlledDhcpv6Srv() {
    disconnectSession();

    server_ = NULL; // forget this instance. There should be no callback anymore
                    // at this stage anyway.
}

isc::data::ConstElementPtr
ControlledDhcpv6Srv::execDhcpv6ServerCommand(const std::string& command_id,
                                             isc::data::ConstElementPtr args) {
    try {
        return (dhcp6CommandHandler(command_id, args));
    } catch (const Exception& ex) {
        ConstElementPtr answer = isc::config::createAnswer(1, ex.what());
        return (answer);
    }
}


};
};
