// Copyright (C) 2012-2015  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CTRL_DHCPV4_SRV_H
#define CTRL_DHCPV4_SRV_H

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
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
    /// @param port UDP port to be opened for DHCP traffic
    ControlledDhcpv4Srv(uint16_t port = DHCP4_SERVER_PORT);

    /// @brief Destructor.
    ~ControlledDhcpv4Srv();

    /// @brief Initializes the server.
    ///
    /// Depending on the configuration backend, it establishes msgq session,
    /// reads the JSON file from disk or may perform any other setup
    /// operation. For specific details, see actual implementation in
    /// *_backend.cc
    ///
    /// This method may throw if initialization fails. Exception types may be
    /// specific to used configuration backend.
    void init(const std::string& config_file);

    /// @brief Performs cleanup, immediately before termination
    ///
    /// This method performs final clean up, just before the Dhcpv4Srv object
    /// is destroyed. Currently it is a no-op.
    void cleanup();

    /// @brief Initiates shutdown procedure for the whole DHCPv4 server.
    void shutdown();

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
    /// @param new_config textual representation of the new configuration
    ///
    /// @return status of the config update
    static isc::data::ConstElementPtr
    processConfig(isc::data::ConstElementPtr new_config);

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
    /// This static callback method is called from IfaceMgr::receive6() method,
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

    /// @brief Static pointer to the sole instance of the DHCP server.
    ///
    /// This is required for config and command handlers to gain access to
    /// the server
    static ControlledDhcpv4Srv* server_;

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
