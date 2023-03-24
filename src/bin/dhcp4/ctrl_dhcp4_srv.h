// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_DHCPV4_SRV_H
#define CTRL_DHCPV4_SRV_H

#include <asiolink/asio_wrapper.h>
#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <util/reconnect_ctl.h>
#include <dhcpsrv/timer_mgr.h>
#include <dhcp4/dhcp4_srv.h>

namespace isc {
namespace dhcp {

/// @brief Controlled version of the DHCPv4 server
///
/// This is a class that is responsible for DHCPv4 server being controllable,
/// by reading configuration file from disk.
class ControlledDhcpv4Srv : public isc::dhcp::Dhcpv4Srv {
public:

    /// @brief Constructor
    ///
    /// @param server_port UDP port to be opened for DHCP traffic
    /// @param client_port UDP port where all responses are sent to.
    ControlledDhcpv4Srv(uint16_t server_port = DHCP4_SERVER_PORT,
                        uint16_t client_port = 0);

    /// @brief Destructor.
    virtual ~ControlledDhcpv4Srv();

    /// @brief Initializes the server.
    ///
    /// It reads the JSON file from disk or may perform any other setup
    /// operation. In particular, it also install signal handlers.
    ///
    /// This method may throw if initialization fails.
    void init(const std::string& config_file);

    /// @brief Configure DHCPv4 server using the configuration file specified.
    ///
    /// This function is used to both configure the DHCP server on its startup
    /// and dynamically reconfigure the server when SIGHUP signal is received.
    ///
    /// It fetches DHCPv4 server's configuration from the 'Dhcp4' section of
    /// the JSON configuration file.
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
    /// This method performs final clean up, just before the Dhcpv4Srv object
    /// is destroyed. Currently it is a no-op.
    void cleanup();

    /// @brief Initiates shutdown procedure for the whole DHCPv4 server.
    /// @param exit_value integer value to the process should exit with.
    virtual void shutdownServer(int exit_value);

    /// @brief Command processor
    ///
    /// This method is uniform for all config backends. It processes received
    /// command (as a string + JSON arguments). Internally, it's just a
    /// wrapper that calls process*Command() methods and catches exceptions
    /// in them.
    ///
    /// Currently supported commands are:
    /// - shutdown
    /// - libreload
    /// - config-reload
    /// - config-set
    /// - config-get
    /// - config-test
    /// - dhcp-disable
    /// - dhcp-enable
    /// - version-get
    /// - build-report
    /// - leases-reclaim
    /// - config-write
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

    /// @brief Configuration processor
    ///
    /// This is a method for handling incoming configuration updates.
    /// This method should be called by all configuration backends when the
    /// server is starting up or when configuration has changed.
    ///
    /// As pointer to this method is used a callback in ASIO used in
    /// ModuleCCSession, it has to be static.
    ///
    /// @param config textual representation of the new configuration
    ///
    /// @return status of the config update
    static isc::data::ConstElementPtr
    processConfig(isc::data::ConstElementPtr config);

    /// @brief Configuration checker
    ///
    /// This is a method for checking incoming configuration.
    ///
    /// @param config JSON representation of the new configuration
    ///
    /// @return status of the config check
    static isc::data::ConstElementPtr
    checkConfig(isc::data::ConstElementPtr config);

    /// @brief Configuration checker for hook libraries
    ///
    /// This is a method for checking incoming configuration in the hooks
    /// libraries. It calls dhcp4_srv_configured hook point for all hooks.
    ///
    /// @param config JSON representation of the new configuration
    ///
    /// @return status of the config check
    static isc::data::ConstElementPtr
    finishConfigHookLibraries(isc::data::ConstElementPtr config);

    /// @brief Returns pointer to the sole instance of Dhcpv4Srv
    ///
    /// @return server instance (may return NULL, if called before server is spawned)
    static ControlledDhcpv4Srv* getInstance() {
        return (server_);
    }

private:
    /// @brief Callback that will be called from iface_mgr when data
    /// is received over control socket.
    ///
    /// This static callback method is called from IfaceMgr::receive4() method,
    /// when there is a new command or configuration sent over control socket
    /// (that was sent from some yet unspecified sender).
    static void sessionReader(void);

    /// @brief Handler for processing 'shutdown' command
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

    /// @brief Handler for processing 'libreload' command
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

    /// @brief Handler for processing 'config-reload' command
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
    /// map containing Dhcp4 map that contains DHCPv4 server configuration.
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
    /// map containing Dhcp4 map that contains DHCPv4 server configuration.
    ///
    /// @return status of the command
    isc::data::ConstElementPtr
    commandConfigTestHandler(const std::string& command,
                             isc::data::ConstElementPtr args);

    /// @brief A handler for processing 'dhcp-disable' command.
    ///
    /// @param command command name (ignored).
    /// @param args arguments for the command. It must be a map and
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

    /// @brief handler for server-tag-get command
    ///
    /// This method handles the server-tag-get command, which retrieves
    /// the current server tag and returns it in response.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return current configuration wrapped in a response
    isc::data::ConstElementPtr
    commandServerTagGetHandler(const std::string& command,
                               isc::data::ConstElementPtr args);

    /// @brief handler for config-backend-pull command
    ///
    /// This method handles the config-backend-pull command, which updates
    /// the server configuration from the Config Backends immediately.
    ///
    /// @param command (parameter ignored)
    /// @param args (ignored)
    ///
    /// @return status of the command/
    isc::data::ConstElementPtr
    commandConfigBackendPullHandler(const std::string& command,
                                    isc::data::ConstElementPtr args);

    /// @brief handler for processing 'status-get' command
    ///
    /// This handler processes status-get command, which retrieves
    /// the server process information i.e. the pid and returns it in response.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return process information wrapped in a response
    isc::data::ConstElementPtr
    commandStatusGetHandler(const std::string& command,
                            isc::data::ConstElementPtr args);

    /// @brief handler for processing 'statistic-sample-count-set-all' command
    ///
    /// This handler processes statistic-sample-count-set-all command,
    /// which sets max_sample_count_ limit of all statistics and the default.
    /// @ref isc::stats::StatsMgr::statisticSetMaxSampleCountAllHandler
    ///
    /// @param command (ignored)
    /// @param args structure containing a map that contains "max-samples"
    /// @return process information wrapped in a response
    isc::data::ConstElementPtr
    commandStatisticSetMaxSampleCountAllHandler(const std::string& command,
                                                isc::data::ConstElementPtr args);

    /// @brief handler for processing 'statistic-sample-age-set-all' command
    ///
    /// This handler processes statistic-sample-age-set-all command,
    /// which sets max_sample_age_ limit of all statistics and the default.
    /// @ref isc::stats::StatsMgr::statisticSetMaxSampleAgeAllHandler
    ///
    /// @param command (ignored)
    /// @param args structure containing a map that contains "duration"
    /// @return process information wrapped in a response
    isc::data::ConstElementPtr
    commandStatisticSetMaxSampleAgeAllHandler(const std::string& command,
                                              isc::data::ConstElementPtr args);

    /// @brief Reclaims expired IPv4 leases and reschedules timer.
    ///
    /// This is a wrapper method for @c AllocEngine::reclaimExpiredLeases4.
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
    /// This is a wrapper method for @c AllocEngine::deleteExpiredReclaimed4.
    /// It reschedules the timer for leases reclamation upon completion of
    /// this method.
    ///
    /// @param secs Minimum number of seconds after which a lease can be
    /// deleted.
    void deleteExpiredReclaimedLeases(const uint32_t secs);

    /// @brief Callback DB backends should be invoked upon loss of the
    /// connectivity.
    ///
    /// This function is invoked by DB backends when they detect a loss of
    /// connectivity.  The parameter, db_reconnect_ctl, conveys the configured
    /// maximum number of reconnect retries as well as the interval to wait
    /// between retry attempts.
    ///
    /// If either value is zero, reconnect is presumed to be disabled and
    /// the function will schedule a shutdown and return false.  This instructs
    /// the DB backend layer (the caller) to treat the connectivity loss as
    /// fatal. It stops the DHCP service until the connection is recovered.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters
    ///
    /// @return false if reconnect is not configured, true otherwise
    bool dbLostCallback(util::ReconnectCtlPtr db_reconnect_ctl);

    /// @brief Callback DB backends should be invoked upon restoration of
    /// connectivity.
    ///
    /// This function is invoked by DB backends when they recover the
    /// connectivity. It starts the DHCP service after the connection is
    /// recovered.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters
    ///
    /// @return false if reconnect is not configured, true otherwise
    bool dbRecoveredCallback(util::ReconnectCtlPtr db_reconnect_ctl);

    /// @brief Callback DB backends should be invoked upon failing to restore
    /// connectivity.
    ///
    /// This function is invoked by DB backends when they fail to recover the
    /// connectivity. It stops the server.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters
    ///
    /// @return false if reconnect is not configured, true otherwise
    bool dbFailedCallback(util::ReconnectCtlPtr db_reconnect_ctl);

    /// @brief This callback should be invoked upon failing to bind sockets.
    ///
    /// This function is invoked during the configuration of the interfaces
    /// when they fail to bind the service sockets. It may stop the server.
    ///
    /// @param reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters
    void openSocketsFailedCallback(util::ReconnectCtlPtr reconnect_ctl);

    /// @brief Callback invoked periodically to fetch configuration updates
    /// from the Config Backends.
    ///
    /// This method calls @c CBControlDHCPv4::databaseConfigFetch and then
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
    static ControlledDhcpv4Srv* server_;

    /// @brief Instance of the @c TimerMgr.
    ///
    /// Shared pointer to the instance of timer @c TimerMgr is held here to
    /// make sure that the @c TimerMgr outlives instance of this class.
    TimerMgrPtr timer_mgr_;
};

}  // namespace dhcp
}  // namespace isc

#endif
