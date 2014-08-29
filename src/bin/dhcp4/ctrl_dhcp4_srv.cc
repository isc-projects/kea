// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <cc/data.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <hooks/hooks_manager.h>
#include <dhcp4/json_config_parser.h>
#include <dhcpsrv/cfgmgr.h>

using namespace isc::data;
using namespace isc::hooks;
using namespace std;

namespace isc {
namespace dhcp {

ControlledDhcpv4Srv* ControlledDhcpv4Srv::server_ = NULL;

ConstElementPtr
ControlledDhcpv4Srv::commandShutdownHandler(const string&, ConstElementPtr) {
    if (ControlledDhcpv4Srv::getInstance()) {
        ControlledDhcpv4Srv::getInstance()->shutdown();
    } else {
        LOG_WARN(dhcp4_logger, DHCP4_NOT_RUNNING);
        ConstElementPtr answer = isc::config::createAnswer(1,
                                              "Shutdown failure.");
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(0, "Shutting down.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv4Srv::commandLibReloadHandler(const string&, ConstElementPtr) {

    /// @todo delete any stored CalloutHandles referring to the old libraries
    /// Get list of currently loaded libraries and reload them.
    vector<string> loaded = HooksManager::getLibraryNames();
    bool status = HooksManager::loadLibraries(loaded);
    if (!status) {
        LOG_ERROR(dhcp4_logger, DHCP4_HOOKS_LIBS_RELOAD_FAIL);
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 "Failed to reload hooks libraries.");
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(0,
                             "Hooks libraries successfully reloaded.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv4Srv::commandConfigReloadHandler(const string&,
                                                ConstElementPtr args) {
    return (processConfig(args));
}

ConstElementPtr
ControlledDhcpv4Srv::processCommand(const string& command,
                                    ConstElementPtr args) {
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_COMMAND_RECEIVED)
              .arg(command).arg(args->str());

    ControlledDhcpv4Srv* srv = ControlledDhcpv4Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(1,
          "Server object not initialized, so can't process command '" +
          command + "', arguments: '" + args->str() + "'.");
        return (no_srv);
    }

    try {
        if (command == "shutdown") {
            return (srv->commandShutdownHandler(command, args));

        } else if (command == "libreload") {
            return (srv->commandLibReloadHandler(command, args));

        } else if (command == "config-reload") {
            return (srv->commandConfigReloadHandler(command, args));

        }
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 "Unrecognized command:" + command);
        return (answer);
    } catch (const Exception& ex) {
        return (isc::config::createAnswer(1, "Error while processing command '"
                                          + command + "':" + ex.what() +
                                          ", params: '" + args->str() + "'"));
    }
}

isc::data::ConstElementPtr
ControlledDhcpv4Srv::processConfig(isc::data::ConstElementPtr config) {

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_CONFIG_RECEIVED)
              .arg(config->str());

    ControlledDhcpv4Srv* srv = ControlledDhcpv4Srv::getInstance();

    // Single stream instance used in all error clauses
    std::ostringstream err;

    if (!srv) {
        err << "Server object not initialized, can't process config.";
        return (isc::config::createAnswer(1, err.str()));
    }

    ConstElementPtr answer = configureDhcp4Server(*srv, config);


    // Check that configuration was successful. If not, do not reopen sockets
    // and don't bother with DDNS stuff.
    try {
        int rcode = 0;
        isc::config::parseAnswer(rcode, answer);
        if (rcode != 0) {
            return (answer);
        }
    } catch (const std::exception& ex) {
        err << "Failed to process configuration:" << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Server will start DDNS communications if its enabled.
    try {
        srv->startD2();
    } catch (const std::exception& ex) {
        err << "Error starting DHCP_DDNS client after server reconfiguration: "
            << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Configuration may change active interfaces. Therefore, we have to reopen
    // sockets according to new configuration. This operation is not exception
    // safe and we really don't want to emit exceptions to whoever called this
    // method. Instead, catch an exception and create appropriate answer.
    try {
        CfgMgr::instance().getCurrentCfg()->getCfgIface()
            .openSockets(CfgIface::V4, srv->getPort(),
                         getInstance()->useBroadcast());

    } catch (std::exception& ex) {
        err << "failed to open sockets after server reconfiguration: "
            << ex.what();
        answer = isc::config::createAnswer(1, err.str());
    }
    return (answer);
}

ControlledDhcpv4Srv::ControlledDhcpv4Srv(uint16_t port /*= DHCP4_SERVER_PORT*/)
    :Dhcpv4Srv(port) {
    if (getInstance()) {
        isc_throw(InvalidOperation,
                  "There is another Dhcpv4Srv instance already.");
    }
    server_ = this; // remember this instance for later use in handlers
}

void ControlledDhcpv4Srv::shutdown() {
    io_service_.stop(); // Stop ASIO transmissions
    Dhcpv4Srv::shutdown(); // Initiate DHCPv4 shutdown procedure.
}

ControlledDhcpv4Srv::~ControlledDhcpv4Srv() {
    cleanup();
    
    server_ = NULL; // forget this instance. Noone should call any handlers at
                    // this stage.
}

void ControlledDhcpv4Srv::sessionReader(void) {
    // Process one asio event. If there are more events, iface_mgr will call
    // this callback more than once.
    if (getInstance()) {
        getInstance()->io_service_.run_one();
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
