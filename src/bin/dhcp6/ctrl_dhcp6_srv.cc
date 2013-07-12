// Copyright (C) 2012-2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/session.h>
#include <config/ccsession.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/dhcp_config_parser.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp6/config_parser.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/spec_config.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

#include <cassert>
#include <iostream>

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
ControlledDhcpv6Srv::dhcp6StubConfigHandler(ConstElementPtr) {
    // This configuration handler is intended to be used only
    // when the initial configuration comes in. To receive this
    // configuration a pointer to this handler must be passed
    // using ModuleCCSession constructor. This constructor will
    // invoke the handler and will store the configuration for
    // the configuration session when the handler returns success.
    // Since this configuration is partial we just pretend to
    // parse it and always return success. The function that
    // initiates the session must get the configuration on its
    // own using getFullConfig.
    return (isc::config::createAnswer(0, "Configuration accepted."));
}

ConstElementPtr
ControlledDhcpv6Srv::dhcp6ConfigHandler(ConstElementPtr new_config) {

    if (!server_ || !server_->config_session_) {
        // That should never happen as we install config_handler
        // after we instantiate the server.
        ConstElementPtr answer =
            isc::config::createAnswer(1, "Configuration rejected,"
                                      " server is during startup/shutdown phase.");
        return (answer);
    }

    // The configuration passed to this handler function is partial.
    // In other words, it just includes the values being modified.
    // In the same time, there are dependencies between various
    // DHCP configuration parsers. For example: the option value can
    // be set if the definition of this option is set. If someone removes
    // an existing option definition then the partial configuration that
    // removes that definition is triggered while a relevant option value
    // may remain configured. This eventually results in the DHCP server
    // configuration being in the inconsistent state.
    // In order to work around this problem we need to merge the new
    // configuration with the existing (full) configuration.

    // Let's create a new object that will hold the merged configuration.
    boost::shared_ptr<MapElement> merged_config(new MapElement());
    // Let's get the existing configuration.
    ConstElementPtr full_config = server_->config_session_->getFullConfig();
    // The full_config and merged_config should be always non-NULL
    // but to provide some level of exception safety we check that they
    // really are (in case we go out of memory).
    if (full_config && merged_config) {
        merged_config->setValue(full_config->mapValue());

        // Merge an existing and new configuration.
        isc::data::merge(merged_config, new_config);
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_UPDATE)
            .arg(merged_config->str());
    }

    // Configure the server.
    ConstElementPtr answer = configureDhcp6Server(*server_, merged_config);

    // Check that configuration was successful. If not, do not reopen sockets.
    int rcode = 0;
    parseAnswer(rcode, answer);
    if (rcode != 0) {
        return (answer);
    }

    // Configuration may change active interfaces. Therefore, we have to reopen
    // sockets according to new configuration. This operation is not exception
    // safe and we really don't want to emit exceptions to the callback caller.
    // Instead, catch an exception and create appropriate answer.
    try {
        server_->openActiveSockets(server_->getPort());
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "failed to open sockets after server reconfiguration: " << ex.what();
        answer = isc::config::createAnswer(1, err.str());
    }
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
    // Create a session with the dummy configuration handler.
    // Dumy configuration handler is internally invoked by the
    // constructor and on success the constructor updates
    // the current session with the configuration that had been
    // committed in the previous session. If we did not install
    // the dummy handler, the previous configuration would have
    // been lost.
    config_session_ = new ModuleCCSession(specfile, *cc_session_,
                                          dhcp6StubConfigHandler,
                                          dhcp6CommandHandler, false);
    config_session_->start();

    // The constructor already pulled the configuration that had
    // been created in the previous session thanks to the dummy
    // handler. We can switch to the handler that will be
    // parsing future changes to the configuration.
    config_session_->setConfigHandler(dhcp6ConfigHandler);

    try {
        // Pull the full configuration out from the session.
        configureDhcp6Server(*this, config_session_->getFullConfig());
        // Configuration may disable or enable interfaces so we have to
        // reopen sockets according to new configuration.
        openActiveSockets(getPort());

    } catch (const DhcpConfigError& ex) {
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

ControlledDhcpv6Srv::ControlledDhcpv6Srv(uint16_t port)
    : Dhcpv6Srv(port), cc_session_(NULL), config_session_(NULL) {
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

void
ControlledDhcpv6Srv::openActiveSockets(const uint16_t port) {
    IfaceMgr::instance().closeSockets();

    // Get the reference to the collection of interfaces. This reference should be
    // valid as long as the program is run because IfaceMgr is a singleton.
    // Therefore we can safely iterate over instances of all interfaces and modify
    // their flags. Here we modify flags which indicate wheter socket should be
    // open for a particular interface or not.
    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();
    for (IfaceMgr::IfaceCollection::const_iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {
        Iface* iface_ptr = IfaceMgr::instance().getIface(iface->getName());
        if (CfgMgr::instance().isActiveIface(iface->getName())) {
            iface_ptr->inactive4_ = false;
            LOG_INFO(dhcp6_logger, DHCP6_ACTIVATE_INTERFACE)
                .arg(iface->getFullName());

        } else {
            // For deactivating interface, it should be sufficient to log it
            // on the debug level because it is more useful to know what
            // interface is activated which is logged on the info level.
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC,
                      DHCP6_DEACTIVATE_INTERFACE).arg(iface->getName());
            iface_ptr->inactive6_ = true;

        }
    }
    // Let's reopen active sockets. openSockets6 will check internally whether
    // sockets are marked active or inactive.
    if (!IfaceMgr::instance().openSockets6(port)) {
        LOG_WARN(dhcp6_logger, DHCP6_NO_SOCKETS_OPEN);
    }
}

};
};
