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

#ifndef CTRL_DHCPV4_SRV_H
#define CTRL_DHCPV4_SRV_H

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/session.h>
#include <config/ccsession.h>
#include <dhcp4/dhcp4_srv.h>

namespace isc {
namespace dhcp {

/// @brief Controlled version of the DHCPv4 server
///
/// This is a class that is responsible for establishing connection
/// with msqg (receving commands and configuration). This is an extended
/// version of Dhcpv4Srv class that is purely a DHCPv4 server, without
/// external control. ControlledDhcpv4Srv should be used in typical BIND10
/// (i.e. featuring msgq) environment, while Dhcpv4Srv should be used in
/// embedded environments.
///
/// For detailed explanation or relations between main(), ControlledDhcpv4Srv,
/// Dhcpv4Srv and other classes, see \ref dhcp4-session.
class ControlledDhcpv4Srv : public isc::dhcp::Dhcpv4Srv {
public:

    /// @brief Constructor
    ///
    /// @param port UDP port to be opened for DHCP traffic
    ControlledDhcpv4Srv(uint16_t port = DHCP4_SERVER_PORT);

    /// @brief Destructor.
    ~ControlledDhcpv4Srv();

    /// @brief Establishes msgq session.
    ///
    /// Creates session that will be used to receive commands and updated
    /// configuration from boss (or indirectly from user via bindctl).
    void establishSession();

    /// @brief Terminates existing msgq session.
    ///
    /// This method terminates existing session with msgq. After calling
    /// it, no further messages over msgq (commands or configuration updates)
    /// may be received.
    ///
    /// It is ok to call this method when session is disconnected already.
    void disconnectSession();

    /// @brief Initiates shutdown procedure for the whole DHCPv4 server.
    void shutdown();

    /// @brief Session callback, processes received commands.
    ///
    /// @param command text represenation of the command (e.g. "shutdown")
    /// @param args optional parameters
    ///
    /// @return status of the command
    static isc::data::ConstElementPtr
    execDhcpv4ServerCommand(const std::string& command,
                            isc::data::ConstElementPtr args);

protected:
    /// @brief Static pointer to the sole instance of the DHCP server.
    ///
    /// This is required for config and command handlers to gain access to
    /// the server
    static ControlledDhcpv4Srv* server_;

    /// @brief A callback for handling incoming configuration updates.
    ///
    /// As pointer to this method is used a callback in ASIO used in
    /// ModuleCCSession, it has to be static.
    ///
    /// @param new_config textual representation of the new configuration
    ///
    /// @return status of the config update
    static isc::data::ConstElementPtr
    dhcp4ConfigHandler(isc::data::ConstElementPtr new_config);

    /// @brief A callback for handling incoming commands.
    ///
    /// @param command textual representation of the command
    /// @param args parameters of the command
    ///
    /// @return status of the processed command
    static isc::data::ConstElementPtr
    dhcp4CommandHandler(const std::string& command, isc::data::ConstElementPtr args);

    /// @brief Callback that will be called from iface_mgr when command/config arrives.
    ///
    /// This static callback method is called from IfaceMgr::receive4() method,
    /// when there is a new command or configuration sent over msgq.
    static void sessionReader(void);

    /// @brief IOService object, used for all ASIO operations.
    isc::asiolink::IOService io_service_;

    /// @brief Helper session object that represents raw connection to msgq.
    isc::cc::Session* cc_session_;

    /// @brief Session that receives configuation and commands
    isc::config::ModuleCCSession* config_session_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif
