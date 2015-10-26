// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <config/command_mgr.h>
#include <stats/stats_mgr.h>

using namespace isc::data;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::stats;
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
ControlledDhcpv4Srv::commandLeasesReclaimHandler(const string&,
                                                 ConstElementPtr args) {
    int status_code = 1;
    string message;

    // args must be { "remove": <bool> }
    if (!args) {
        message = "Missing mandatory 'remove' parameter.";
    } else {
        ConstElementPtr remove_name = args->get("remove");
        if (!remove_name) {
            message = "Missing mandatory 'remove' parameter.";
        } else if (remove_name->getType() != Element::boolean) {
            message = "'remove' parameter expected to be a boolean.";
        } else {
            bool remove_lease = remove_name->boolValue();
            server_->alloc_engine_->reclaimExpiredLeases4(0, 0, remove_lease);
            status_code = 0;
            message = "Reclamation of expired leases is complete.";
        }
    }
    ConstElementPtr answer = isc::config::createAnswer(status_code, message);
    return (answer);
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

        } else if (command == "leases-reclaim") {
            return (srv->commandLeasesReclaimHandler(command, args));
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

    // We're going to modify the timers configuration. This is not allowed
    // when the thread is running.
    try {
        TimerMgr::instance()->stopThread();
    } catch (const std::exception& ex) {
        err << "Unable to stop worker thread running timers: "
            << ex.what() << ".";
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
    // sockets according to new configuration. It is possible that this
    // operation will fail for some interfaces but the openSockets function
    // guards against exceptions and invokes a callback function to
    // log warnings. Since we allow that this fails for some interfaces there
    // is no need to rollback configuration if socket fails to open on any
    // of the interfaces.
    CfgMgr::instance().getStagingCfg()->getCfgIface()->
        openSockets(AF_INET, srv->getPort(), getInstance()->useBroadcast());

    // Install the timers for handling leases reclamation.
    try {
        CfgMgr::instance().getStagingCfg()->getCfgExpiration()->
            setupTimers(&ControlledDhcpv4Srv::reclaimExpiredLeases,
                        &ControlledDhcpv4Srv::deleteExpiredReclaimedLeases,
                        server_);

    } catch (const std::exception& ex) {
        err << "unable to setup timers for periodically running the"
            " reclamation of the expired leases: "
            << ex.what() << ".";
        return (isc::config::createAnswer(1, err.str()));
    }

    // Start worker thread if there are any timers installed.
    if (TimerMgr::instance()->timersCount() > 0) {
        try {
            TimerMgr::instance()->startThread();
        } catch (const std::exception& ex) {
            err << "Unable to start worker thread running timers: "
                << ex.what() << ".";
            return (isc::config::createAnswer(1, err.str()));
        }
    }



    return (answer);
}

ControlledDhcpv4Srv::ControlledDhcpv4Srv(uint16_t port /*= DHCP4_SERVER_PORT*/)
    : Dhcpv4Srv(port), io_service_(), timer_mgr_(TimerMgr::instance()) {
    if (getInstance()) {
        isc_throw(InvalidOperation,
                  "There is another Dhcpv4Srv instance already.");
    }
    server_ = this; // remember this instance for later use in handlers

    // Register supported commands in CommandMgr
    CommandMgr::instance().registerCommand("shutdown",
        boost::bind(&ControlledDhcpv4Srv::commandShutdownHandler, this, _1, _2));

    /// @todo: register config-reload (see CtrlDhcpv4Srv::commandConfigReloadHandler)
    /// @todo: register libreload (see CtrlDhcpv4Srv::commandLibReloadHandler)

    CommandMgr::instance().registerCommand("leases-reclaim",
        boost::bind(&ControlledDhcpv4Srv::commandLeasesReclaimHandler, this, _1, _2));

    // Register statistic related commands
    CommandMgr::instance().registerCommand("statistic-get",
        boost::bind(&StatsMgr::statisticGetHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-reset",
        boost::bind(&StatsMgr::statisticResetHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-remove",
        boost::bind(&StatsMgr::statisticRemoveHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-get-all",
        boost::bind(&StatsMgr::statisticGetAllHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-reset-all",
        boost::bind(&StatsMgr::statisticResetAllHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-remove-all",
        boost::bind(&StatsMgr::statisticRemoveAllHandler, _1, _2));
}

void ControlledDhcpv4Srv::shutdown() {
    io_service_.stop(); // Stop ASIO transmissions
    Dhcpv4Srv::shutdown(); // Initiate DHCPv4 shutdown procedure.
}

ControlledDhcpv4Srv::~ControlledDhcpv4Srv() {
    try {
        cleanup();

        // Stop worker thread running timers, if it is running. Then
        // unregister any timers.
        timer_mgr_->stopThread();
        timer_mgr_->unregisterTimers();

        // Close the command socket (if it exists).
        CommandMgr::instance().closeCommandSocket();

        // Deregister any registered commands
        CommandMgr::instance().deregisterCommand("shutdown");
        CommandMgr::instance().deregisterCommand("leases-reclaim");
        CommandMgr::instance().deregisterCommand("statistic-get");
        CommandMgr::instance().deregisterCommand("statistic-reset");
        CommandMgr::instance().deregisterCommand("statistic-remove");
        CommandMgr::instance().deregisterCommand("statistic-get-all");
        CommandMgr::instance().deregisterCommand("statistic-reset-all");
        CommandMgr::instance().deregisterCommand("statistic-remove-all");

    } catch (...) {
        // Don't want to throw exceptions from the destructor. The server
        // is shutting down anyway.
        ;
    }

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

void
ControlledDhcpv4Srv::reclaimExpiredLeases(const size_t max_leases,
                                          const uint16_t timeout,
                                          const bool remove_lease,
                                          const uint16_t max_unwarned_cycles) {
    server_->alloc_engine_->reclaimExpiredLeases4(max_leases, timeout,
                                                  remove_lease,
                                                  max_unwarned_cycles);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::RECLAIM_EXPIRED_TIMER_NAME);
}

void
ControlledDhcpv4Srv::deleteExpiredReclaimedLeases(const uint32_t secs) {
    server_->alloc_engine_->deleteExpiredReclaimedLeases4(secs);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::FLUSH_RECLAIMED_TIMER_NAME);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
