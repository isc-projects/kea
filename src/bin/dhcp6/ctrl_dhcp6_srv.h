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

#ifndef CTRL_DHCPV6_SRV_H
#define CTRL_DHCPV6_SRV_H

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/session.h>
#include <config/ccsession.h>
#include <dhcp6/dhcp6_srv.h>

namespace isc {
namespace dhcp {

/// @brief Controlled version of the DHCPv6 server
///
/// This is a class that is responsible for establishing connection
/// with msqg (receving commands and configuration). This is an extended
/// version of Dhcpv6Srv class that is purely a DHCPv6 server, without
/// external control. ControlledDhcpv6Srv should be used in typical BIND10
/// (i.e. featuring msgq) environment, while Dhcpv6Srv should be used in
/// embedded environments.
///
/// For detailed explanation or relations between main(), ControlledDhcpv6Srv,
/// Dhcpv6Srv and other classes, see \ref dhcpv6Session.
class ControlledDhcpv6Srv : public isc::dhcp::Dhcpv6Srv {
public:

    /// @brief Constructor
    ///
    /// @param port UDP port to be opened for DHCP traffic
    ControlledDhcpv6Srv(uint16_t port = DHCP6_SERVER_PORT);

    /// @brief Destructor.
    ~ControlledDhcpv6Srv();

    /// @brief Initializes the server.
    ///
    /// Depending on the configuration backend, it establishes msgq session,
    /// reads the JSON file from disk or may perform any other setup
    /// operation. For specific details, see actual implementation in
    /// ctrl_*_dhcp6_srv.cc
    ///
    /// @return true if initialization was successful, false if it failed
    bool init(const std::string& config_file);

    /// @brief Terminates existing msgq session.
    ///
    /// This method terminates existing session with msgq. After calling
    /// it, no further messages over msgq (commands or configuration updates)
    /// may be received.
    ///
    /// It is ok to call this method when session is disconnected already.
    void cleanup();

    /// @brief Initiates shutdown procedure for the whole DHCPv6 server.
    void shutdown();

    /// @brief Session callback, processes received commands.
    ///
    /// @param command Text represenation of the command (e.g. "shutdown")
    /// @param args Optional parameters
    ///
    /// @return status of the command
    static isc::data::ConstElementPtr
    execDhcpv6ServerCommand(const std::string& command,
                            isc::data::ConstElementPtr args);

protected:
    /// @brief Static pointer to the sole instance of the DHCP server.
    ///
    /// This is required for config and command handlers to gain access to
    /// the server
    static ControlledDhcpv6Srv* server_;

    /// @brief A callback for handling incoming configuration updates.
    ///
    /// As pointer to this method is used a callback in ASIO used in
    /// ModuleCCSession, it has to be static.
    ///
    /// @param new_config textual representation of the new configuration
    ///
    /// @return status of the config update
    static isc::data::ConstElementPtr
    dhcp6ConfigHandler(isc::data::ConstElementPtr new_config);

    /// @brief A dummy configuration handler that always returns success.
    ///
    /// This configuration handler does not perform configuration
    /// parsing and always returns success. A dummy handler should
    /// be installed using \ref isc::config::ModuleCCSession ctor
    /// to get the initial configuration. This initial configuration
    /// comprises values for only those elements that were modified
    /// the previous session. The \ref dhcp6ConfigHandler can't be
    /// used to parse the initial configuration because it needs the
    /// full configuration to satisfy dependencies between the
    /// various configuration values. Installing the dummy handler
    /// that guarantees to return success causes initial configuration
    /// to be stored for the session being created and that it can
    /// be later accessed with
    /// \ref isc::config::ConfigData::getFullConfig().
    ///
    /// @param new_config new configuration.
    ///
    /// @return success configuration status.
    static isc::data::ConstElementPtr
    dhcp6StubConfigHandler(isc::data::ConstElementPtr new_config);

    /// @brief A callback for handling incoming commands.
    ///
    /// @param command textual representation of the command
    /// @param args parameters of the command
    ///
    /// @return status of the processed command
    static isc::data::ConstElementPtr
    dhcp6CommandHandler(const std::string& command, isc::data::ConstElementPtr args);

    /// @brief Callback that will be called from iface_mgr when command/config arrives.
    ///
    /// This static callback method is called from IfaceMgr::receive6() method,
    /// when there is a new command or configuration sent over msgq.
    static void sessionReader(void);

    /// @brief IOService object, used for all ASIO operations.
    isc::asiolink::IOService io_service_;

    /// @brief Helper session object that represents raw connection to msgq.
    isc::cc::Session* cc_session_;

    /// @brief Session that receives configuration and commands
    isc::config::ModuleCCSession* config_session_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif
