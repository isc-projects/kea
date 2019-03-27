// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_DHCPV6_SRV_H
#define CTRL_DHCPV6_SRV_H

#include <asiolink/asio_wrapper.h>
#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <database/database_connection.h>
#include <dhcpsrv/timer_mgr.h>
#include <dhcp6/dhcp6_srv.h>

namespace isc {
namespace dhcp {

/// @brief Controlled version of the DHCPv6 server
///
/// This is a class that is responsible for DHCPv6 server being controllable,
/// by reading configuration file from disk.
class ControlledDhcpv6Srv : public isc::dhcp::Dhcpv6Srv {
public:

    /// @brief Constructor
    ///
    /// @param server_port UDP port to be opened for DHCP traffic
    /// @param client_port UDP port where all responses are sent to.
    ControlledDhcpv6Srv(uint16_t server_port = DHCP6_SERVER_PORT,
                        uint16_t client_port = 0);

    /// @brief Destructor.
    virtual ~ControlledDhcpv6Srv();

    /// @brief Initializes the server.
    ///
    /// It reads the JSON file from disk or may perform any other setup
    /// operation. In particular, it also install signal handlers.
    ///
    /// This method may throw if initialization fails.
    void init(const std::string& config_file);

    /// @brief Loads specific configuration file
    ///
    /// This utility method is called whenever we know a filename of the config
    /// and need to load it. It calls config-set command once the content of
    /// the file has been loaded and verified to be a sane JSON configuration.
    /// config-set handler will process the config file (apply it as current
    /// configuration).
    ///
    /// @param file_name name of the file to be loaded
    /// @return status of the file loading and outcome of config-set
    isc::data::ConstElementPtr
    loadConfigFile(const std::string& file_name);

    /// @brief Performs cleanup, immediately before termination
    ///
    /// This method performs final clean up, just before the Dhcpv6Srv object
    /// is destroyed. Currently it is a no-op.
    void cleanup();

    /// @brief Initiates shutdown procedure for the whole DHCPv6 server.
    void shutdown();

    /// @brief command processor
    ///
    /// This method is uniform for all config backends. It processes received
    /// command (as a string + JSON arguments). Internally, it's just a
    /// wrapper that calls process*Command() methods and catches exceptions
    /// in them.
    ///
    /// Currently supported commands are:
    /// - config-reload
    /// - config-test
    /// - leases-reclaim
    /// - libreload
    /// - shutdown
    /// ...
    ///
    /// @note It never throws.
    ///
    /// @param command Text representation of the command (e.g. "shutdown")
    /// @param args Optional parameters
    ///
    /// @return status of the command
    static isc::data::ConstElementPtr
    processCommand(const std::string& command, isc::data::ConstElementPtr args);

    /// @brief configuration processor
    ///
    /// This is a method for handling incoming configuration updates.
    /// This method should be called by all configuration backends when the
    /// server is starting up or when configuration has changed.
    ///
    /// As pointer to this method is used a callback in ASIO used in
    /// ModuleCCSession, it has to be static.
    ///
    /// @param new_config textual representation of the new configuration
    ///
    /// @return status of the config update
    static isc::data::ConstElementPtr
    processConfig(isc::data::ConstElementPtr new_config);

    /// @brief Configuration checker
    ///
    /// This is a method for checking incoming configuration.
    ///
    /// @param new_config JSON representation of the new configuration
    ///
    /// @return status of the config check
    isc::data::ConstElementPtr
    checkConfig(isc::data::ConstElementPtr new_config);

    /// @brief returns pointer to the sole instance of Dhcpv6Srv
    ///
    /// @return server instance (may return NULL, if called before server is spawned)
    static ControlledDhcpv6Srv* getInstance() {
        return (server_);
    }

private:

    /// @brief Callback that will be called from iface_mgr when data
    /// is received over control socket.
    ///
    /// This static callback method is called from IfaceMgr::receive6() method,
    /// when there is a new command or configuration sent over control socket
    /// (that was sent from some yet unspecified sender).
    static void sessionReader(void);

    /// @brief handler for processing 'shutdown' command
    ///
    /// This handler processes shutdown command, which initializes shutdown
    /// procedure.
    /// @param command (parameter ignored)
    /// @param args (parameter ignored)
    ///
    /// @return status of the command
    isc::data::ConstElementPtr
    commandShutdownHandler(const std::string& command,
                           isc::data::ConstElementPtr args);

    /// @brief handler for processing 'libreload' command
    ///
    /// This handler processes libreload command, which unloads all hook
    /// libraries and reloads them.
    ///
    /// @param command (parameter ignored)
    /// @param args (parameter ignored)
    ///
    /// @return status of the command
    isc::data::ConstElementPtr
    commandLibReloadHandler(const std::string& command,
                            isc::data::ConstElementPtr args);

    /// @brief handler for processing 'config-reload' command
    ///
    /// This handler processes config-reload command, which processes
    /// configuration specified in args parameter.
    ///
    /// @param command (parameter ignored)
    /// @param args configuration to be processed
    ///
    /// @return status of the command
    isc::data::ConstElementPtr
    commandConfigReloadHandler(const std::string& command,
                               isc::data::ConstElementPtr args);

    /// @brief handler for processing 'get-config' command
    ///
    /// This handler processes get-config command, which retrieves
    /// the current configuration and returns it in response.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return current configuration wrapped in a response
    isc::data::ConstElementPtr
    commandConfigGetHandler(const std::string& command,
                            isc::data::ConstElementPtr args);

    /// @brief handler for processing 'write-config' command
    ///
    /// This handle processes write-config command, which writes the
    /// current configuration to disk. This command takes one optional
    /// parameter called filename. If specified, the current configuration
    /// will be written to that file. If not specified, the file used during
    /// Kea start-up will be used. To avoid any exploits, the path is
    /// always relative and .. is not allowed in the filename. This is
    /// a security measure against exploiting file writes remotely.
    ///
    /// @param command (ignored)
    /// @param args may contain optional string argument filename
    /// @return status of the configuration file write
    isc::data::ConstElementPtr
    commandConfigWriteHandler(const std::string& command,
                              isc::data::ConstElementPtr args);

    /// @brief handler for processing 'config-set' command
    ///
    /// This handler processes config-set command, which processes
    /// configuration specified in args parameter.
    /// @param command (parameter ignored)
    /// @param args configuration to be processed. Expected format:
    /// map containing Dhcp6 map that contains DHCPv6 server configuration.
    /// May also contain Logging map that specifies logging configuration.
    ///
    /// @return status of the command
    isc::data::ConstElementPtr
    commandConfigSetHandler(const std::string& command,
                            isc::data::ConstElementPtr args);

    /// @brief handler for processing 'config-test' command
    ///
    /// This handler processes config-test command, which checks
    /// configuration specified in args parameter.
    /// @param command (parameter ignored)
    /// @param args configuration to be checked. Expected format:
    /// map containing Dhcp6 map that contains DHCPv6 server configuration.
    /// May also contain Logging map that specifies logging configuration.
    ///
    /// @return status of the command
    isc::data::ConstElementPtr
    commandConfigTestHandler(const std::string& command,
                             isc::data::ConstElementPtr args);

    /// @brief A handler for processing 'dhcp-disable' command.
    ///
    /// @param command command name (ignored).
    /// @param args aguments for the command. It must be a map and
    /// it may include optional 'max-period' parameter.
    ///
    /// @return result of the command.
    isc::data::ConstElementPtr
    commandDhcpDisableHandler(const std::string& command,
                              isc::data::ConstElementPtr args);

    /// @brief A handler for processing 'dhcp-enable' command.
    ///
    /// @param command command name (ignored)
    /// @param args arguments for the command (ignored).
    ///
    /// @return result of the command.
    isc::data::ConstElementPtr
    commandDhcpEnableHandler(const std::string& command,
                             isc::data::ConstElementPtr args);

    /// @Brief handler for processing 'version-get' command
    ///
    /// This handler processes version-get command, which returns
    /// over the control channel the -v and -V command line arguments.
    /// @param command (parameter ignored)
    /// @param args (parameter ignored)
    ///
    /// @return status of the command with the version in text and
    /// the extended version in arguments.
    isc::data::ConstElementPtr
    commandVersionGetHandler(const std::string& command,
                             isc::data::ConstElementPtr args);

    /// @brief handler for processing 'build-report' command
    ///
    /// This handler processes build-report command, which returns
    /// over the control channel the -W command line argument.
    /// @param command (parameter ignored)
    /// @param args (parameter ignored)
    ///
    /// @return status of the command with the config report
    isc::data::ConstElementPtr
    commandBuildReportHandler(const std::string& command,
                              isc::data::ConstElementPtr args);

    /// @brief Handler for processing 'leases-reclaim' command
    ///
    /// This handler processes leases-reclaim command, which triggers
    /// the leases reclamation immediately.
    /// No limit for processing time or number of processed leases applies.
    ///
    /// @param command (parameter ignored)
    /// @param args arguments map { "remove": <bool> }
    ///        if true a lease is removed when it is reclaimed,
    ///        if false its state is changed to "expired-reclaimed".
    ///
    /// @return status of the command (should be success unless args
    ///         was not a Bool Element).
    isc::data::ConstElementPtr
    commandLeasesReclaimHandler(const std::string& command,
                                isc::data::ConstElementPtr args);

    /// @brief Reclaims expired IPv6 leases and reschedules timer.
    ///
    /// This is a wrapper method for @c AllocEngine::reclaimExpiredLeases6.
    /// It reschedules the timer for leases reclamation upon completion of
    /// this method.
    ///
    /// @param max_leases Maximum number of leases to be reclaimed.
    /// @param timeout Maximum amount of time that the reclamation routine
    /// may be processing expired leases, expressed in milliseconds.
    /// @param remove_lease A boolean value indicating if the lease should
    /// be removed when it is reclaimed (if true) or it should be left in the
    /// database in the "expired-reclaimed" state (if false).
    /// @param max_unwarned_cycles A number of consecutive processing cycles
    /// of expired leases, after which the system issues a warning if there
    /// are still expired leases in the database. If this value is 0, the
    /// warning is never issued.
    void reclaimExpiredLeases(const size_t max_leases, const uint16_t timeout,
                              const bool remove_lease,
                              const uint16_t max_unwarned_cycles);


    /// @brief Deletes reclaimed leases and reschedules the timer.
    ///
    /// This is a wrapper method for @c AllocEngine::deleteExpiredReclaimed6.
    /// It reschedules the timer for leases reclamation upon completion of
    /// this method.
    ///
    /// @param secs Minimum number of seconds after which a lease can be
    /// deleted.
    void deleteExpiredReclaimedLeases(const uint32_t secs);

    /// @brief Attempts to reconnect the server to the DB backend managers
    ///
    /// This is a self-rescheduling function that attempts to reconnect to the
    /// server's DB backends after connectivity to one or more have been
    /// lost.  Upon entry it will attempt to reconnect via @ref CfgDdbAccess::
    /// createManagers.  If this is succesful, DHCP servicing is re-enabled and
    /// server returns to normal operation.
    ///
    /// If reconnection fails and the maximum number of retries has not been
    /// exhausted, it will schedule a call to itself to occur at the
    /// configured retry interval. DHCP service remains disabled.
    ///
    /// If the maximum number of retries has been exhausted an error is logged
    /// and the server shuts down.
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters
    ///
    void dbReconnect(db::ReconnectCtlPtr db_reconnect_ctl);

    /// @brief Callback DB backends should invoke upon loss of connectivity
    ///
    /// This function is invoked by DB backends when they detect a loss of
    /// connectivity.  The parameter, db_reconnect_ctl, conveys the configured
    /// maximum number of reconnect retries as well as the interval to wait
    /// between retry attempts.
    ///
    /// If either value is zero, reconnect is presumed to be disabled and
    /// the function will returns false.  This instructs the DB backend
    /// layer (the caller) to treat the connectivity loss as fatal.
    ///
    /// Otherwise, the function saves db_reconnect_ctl and invokes
    /// dbReconnect to initiate the reconnect process.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters
    bool dbLostCallback(db::ReconnectCtlPtr db_reconnect_ctl);

    /// @brief Callback invoked periodically to fetch configuration updates
    /// from the Config Backends.
    ///
    /// This method calls @c CBControlDHCPv6::databaseConfigFetch and then
    /// reschedules the timer.
    ///
    /// @param srv_cfg Server configuration holding the database credentials
    /// and server tag.
    /// @param failure_count pointer to failure counter which causes this
    /// callback to stop scheduling the timer after 10 consecutive failures
    /// to fetch the updates.
    void cbFetchUpdates(const SrvConfigPtr& srv_cfg,
                        boost::shared_ptr<unsigned> failure_count);

    /// @brief Static pointer to the sole instance of the DHCP server.
    ///
    /// This is required for config and command handlers to gain access to
    /// the server. Some of them need to be static methods.
    static ControlledDhcpv6Srv* server_;

    /// @brief IOService object, used for all ASIO operations.
    isc::asiolink::IOService io_service_;

    /// @brief Instance of the @c TimerMgr.
    ///
    /// Shared pointer to the instance of timer @c TimerMgr is held here to
    /// make sure that the @c TimerMgr outlives instance of this class.
    TimerMgrPtr timer_mgr_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif
