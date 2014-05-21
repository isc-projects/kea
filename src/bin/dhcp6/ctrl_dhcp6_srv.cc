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
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6_log.h>
#include <hooks/hooks_manager.h>
#include <dhcp6/json_config_parser.h>

using namespace isc::data;
using namespace isc::hooks;
using namespace std;

namespace isc {
namespace dhcp {

ControlledDhcpv6Srv* ControlledDhcpv6Srv::server_ = NULL;

ConstElementPtr
ControlledDhcpv6Srv::commandShutdownHandler(const string&, ConstElementPtr) {
    if (ControlledDhcpv6Srv::server_) {
        ControlledDhcpv6Srv::server_->shutdown();
    } else {
        LOG_WARN(dhcp6_logger, DHCP6_NOT_RUNNING);
        ConstElementPtr answer = isc::config::createAnswer(1, "Shutdown failure.");
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(0, "Shutting down.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandLibReloadHandler(const string&, ConstElementPtr) {
    /// @todo delete any stored CalloutHandles referring to the old libraries
    /// Get list of currently loaded libraries and reload them.
    vector<string> loaded = HooksManager::getLibraryNames();
    bool status = HooksManager::loadLibraries(loaded);
    if (!status) {
        LOG_ERROR(dhcp6_logger, DHCP6_HOOKS_LIBS_RELOAD_FAIL);
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 "Failed to reload hooks libraries.");
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(0,
                             "Hooks libraries successfully reloaded.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigReloadHandler(const string&, ConstElementPtr args) {

    return (processConfig(args));
}

isc::data::ConstElementPtr
ControlledDhcpv6Srv::processCommand(const std::string& command,
                                    isc::data::ConstElementPtr args) {
    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_COMMAND_RECEIVED)
              .arg(command).arg(args->str());

    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(1,
          "Server object not initialized, can't process command '" +
          command + "'.");
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

        return (isc::config::createAnswer(1, "Unrecognized command:"
                                          + command));

    } catch (const Exception& ex) {
        return (isc::config::createAnswer(1, "Error while processing command '"
                                          + command + "':" + ex.what()));
    }
}


isc::data::ConstElementPtr
ControlledDhcpv6Srv::processConfig(isc::data::ConstElementPtr config) {
    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(1,
          "Server object not initialized, can't process config.");
        return (no_srv);
    }

    ConstElementPtr answer = configureDhcp6Server(*srv, config);

    // Check that configuration was successful. If not, do not reopen sockets
    // and don't bother with DDNS stuff.
    try {
        int rcode = 0;
        isc::config::parseAnswer(rcode, answer);
        if (rcode != 0) {
            return (answer);
        }
    } catch (const std::exception& ex) {
        return (isc::config::createAnswer(1, "Failed to process configuration:"
                                          + string(ex.what())));
    }

    // Server will start DDNS communications if its enabled.
    try {
        srv->startD2();
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "error starting DHCP_DDNS client "
                " after server reconfiguration: " << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Configuration may change active interfaces. Therefore, we have to reopen
    // sockets according to new configuration. This operation is not exception
    // safe and we really don't want to emit exceptions to the callback caller.
    // Instead, catch an exception and create appropriate answer.
    try {
        srv->openActiveSockets(srv->getPort());
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "failed to open sockets after server reconfiguration: " << ex.what();
        answer = isc::config::createAnswer(1, err.str());
    }

    return (answer);
}

ControlledDhcpv6Srv::ControlledDhcpv6Srv(uint16_t port)
    : Dhcpv6Srv(port) {
    if (server_) {
        isc_throw(InvalidOperation,
                  "There is another Dhcpv6Srv instance already.");
    }
    server_ = this; // remember this instance for use in callback
}

void ControlledDhcpv6Srv::shutdown() {
    io_service_.stop(); // Stop ASIO transmissions
    Dhcpv6Srv::shutdown(); // Initiate DHCPv6 shutdown procedure.
}

ControlledDhcpv6Srv::~ControlledDhcpv6Srv() {
    cleanup();

    server_ = NULL; // forget this instance. There should be no callback anymore
                    // at this stage anyway.
}

void ControlledDhcpv6Srv::sessionReader(void) {
    // Process one asio event. If there are more events, iface_mgr will call
    // this callback more than once.
    if (server_) {
        server_->io_service_.run_one();
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
