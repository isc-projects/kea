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
#include <config/command_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6_dhcp4o6_ipc.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/json_config_parser.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::stats;
using namespace std;

namespace {

// Name of the file holding server identifier.
static const char* SERVER_DUID_FILE = "kea-dhcp6-serverid";

}

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

ConstElementPtr
ControlledDhcpv6Srv::commandLeasesReclaimHandler(const string&,
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
            server_->alloc_engine_->reclaimExpiredLeases6(0, 0, remove_lease);
            status_code = 0;
            message = "Reclamation of expired leases is complete.";
        }
    }
    ConstElementPtr answer = isc::config::createAnswer(status_code, message);
    return (answer);
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

        } else if (command == "leases-reclaim") {
            return (srv->commandLeasesReclaimHandler(command, args));
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

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_RECEIVED)
              .arg(config->str());

    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(1,
          "Server object not initialized, can't process config.");
        return (no_srv);
    }

    // We're going to modify the timers configuration. This is not allowed
    // when the thread is running.
    try {
        TimerMgr::instance()->stopThread();
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "Unable to stop worker thread running timers: "
            << ex.what() << ".";
        return (isc::config::createAnswer(1, err.str()));
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

    // Regenerate server identifier if needed.
    try {
        const std::string duid_file = CfgMgr::instance().getDataDir() + "/" +
            std::string(SERVER_DUID_FILE);
        DuidPtr duid = CfgMgr::instance().getStagingCfg()->getCfgDUID()->create(duid_file);
        server_->serverid_.reset(new Option(Option::V6, D6O_SERVERID, duid->getDuid()));
        if (duid) {
            LOG_INFO(dhcp6_logger, DHCP6_USING_SERVERID)
                .arg(duid->toText())
                .arg(duid_file);
        }

    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "unable to configure server identifier: " << ex.what();
        return (isc::config::createAnswer(1, err.str()));
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

    // Setup DHCPv4-over-DHCPv6 IPC
    try {
        Dhcp6to4Ipc::instance().open();
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "error starting DHCPv4-over-DHCPv6 IPC "
               " after server reconfiguration: " << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Configuration may change active interfaces. Therefore, we have to reopen
    // sockets according to new configuration. It is possible that this
    // operation will fail for some interfaces but the openSockets function
    // guards against exceptions and invokes a callback function to
    // log warnings. Since we allow that this fails for some interfaces there
    // is no need to rollback configuration if socket fails to open on any
    // of the interfaces.
    CfgMgr::instance().getStagingCfg()->getCfgIface()->openSockets(AF_INET6, srv->getPort());

    // Install the timers for handling leases reclamation.
    try {
        CfgMgr::instance().getStagingCfg()->getCfgExpiration()->
            setupTimers(&ControlledDhcpv6Srv::reclaimExpiredLeases,
                        &ControlledDhcpv6Srv::deleteExpiredReclaimedLeases,
                        server_);

    } catch (const std::exception& ex) {
        std::ostringstream err;
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
            std::ostringstream err;
            err << "Unable to start worker thread running timers: "
                << ex.what() << ".";
            return (isc::config::createAnswer(1, err.str()));
        }
    }

    // Finally, we can commit runtime option definitions in libdhcp++. This is
    // exception free.
    LibDHCP::commitRuntimeOptionDefs();

    return (answer);
}

ControlledDhcpv6Srv::ControlledDhcpv6Srv(uint16_t port)
    : Dhcpv6Srv(port), io_service_(), timer_mgr_(TimerMgr::instance()) {
    if (server_) {
        isc_throw(InvalidOperation,
                  "There is another Dhcpv6Srv instance already.");
    }
    server_ = this; // remember this instance for use in callback

    // Register supported commands in CommandMgr
    CommandMgr::instance().registerCommand("shutdown",
        boost::bind(&ControlledDhcpv6Srv::commandShutdownHandler, this, _1, _2));

    /// @todo: register config-reload (see CtrlDhcpv4Srv::commandConfigReloadHandler)
    /// @todo: register libreload (see CtrlDhcpv4Srv::commandLibReloadHandler)

    CommandMgr::instance().registerCommand("leases-reclaim",
        boost::bind(&ControlledDhcpv6Srv::commandLeasesReclaimHandler, this, _1, _2));

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

void ControlledDhcpv6Srv::shutdown() {
    io_service_.stop(); // Stop ASIO transmissions
    Dhcpv6Srv::shutdown(); // Initiate DHCPv6 shutdown procedure.
}

ControlledDhcpv6Srv::~ControlledDhcpv6Srv() {
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

void
ControlledDhcpv6Srv::reclaimExpiredLeases(const size_t max_leases,
                                          const uint16_t timeout,
                                          const bool remove_lease,
                                          const uint16_t max_unwarned_cycles) {
    server_->alloc_engine_->reclaimExpiredLeases6(max_leases, timeout,
                                                  remove_lease,
                                                  max_unwarned_cycles);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::RECLAIM_EXPIRED_TIMER_NAME);
}

void
ControlledDhcpv6Srv::deleteExpiredReclaimedLeases(const uint32_t secs) {
    server_->alloc_engine_->deleteExpiredReclaimedLeases6(secs);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::FLUSH_RECLAIMED_TIMER_NAME);
}


}; // end of isc::dhcp namespace
}; // end of isc namespace
