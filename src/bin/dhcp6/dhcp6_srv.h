// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCPV6_SRV_H
#define DHCPV6_SRV_H

#include <iostream>

#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option_definition.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/alloc_engine.h>
#include <dhcpsrv/subnet.h>

#include <boost/noncopyable.hpp>

namespace isc {

namespace dhcp {
/// @brief DHCPv6 server service.
///
/// This class represents DHCPv6 server. It contains all
/// top-level methods and routines necessary for server operation.
/// In particular, it instantiates IfaceMgr, loads or generates DUID
/// that is going to be used as server-identifier, receives incoming
/// packets, processes them, manages leases assignment and generates
/// appropriate responses.
///
/// @note Only one instance of this class is instantated as it encompasses
///       the whole operation of the server.  Nothing, however, enforces the
///       singleton status of the object.
class Dhcpv6Srv : public boost::noncopyable {

public:

    /// @brief Minimum length of a MAC address to be used in DUID generation.
    static const size_t MIN_MAC_LEN = 6;

    /// @brief Default constructor.
    ///
    /// Instantiates necessary services, required to run DHCPv6 server.
    /// In particular, creates IfaceMgr that will be responsible for
    /// network interaction. Will instantiate lease manager, and load
    /// old or create new DUID.
    ///
    /// @param port port on will all sockets will listen
    /// @param dbconfig Lease manager configuration string.  The default
    ///        of the "memfile" manager is used for testing.
    Dhcpv6Srv(uint16_t port = DHCP6_SERVER_PORT,
            const char* dbconfig = "type=memfile");

    /// @brief Destructor. Used during DHCPv6 service shutdown.
    virtual ~Dhcpv6Srv();

    /// @brief Returns server-intentifier option.
    ///
    /// @return server-id option
    OptionPtr getServerID() { return serverid_; }

    /// @brief Main server processing loop.
    ///
    /// Main server processing loop. Receives incoming packets, verifies
    /// their correctness, generates appropriate answer (if needed) and
    /// transmits respones.
    ///
    /// @return true, if being shut down gracefully, fail if experienced
    ///         critical error.
    bool run();

    /// @brief Instructs the server to shut down.
    void shutdown();

    /// @brief Return textual type of packet received by server.
    ///
    /// Returns the name of valid packet received by the server (e.g. SOLICIT).
    /// If the packet is unknown - or if it is a valid DHCP packet but not one
    /// expected to be received by the server (such as an ADVERTISE), the string
    /// "UNKNOWN" is returned.  This method is used in debug messages.
    ///
    /// As the operation of the method does not depend on any server state, it
    /// is declared static.
    ///
    /// @param type DHCPv4 packet type
    ///
    /// @return Pointer to "const" string containing the packet name.
    ///         Note that this string is statically allocated and MUST NOT
    ///         be freed by the caller.
    static const char* serverReceivedPacketName(uint8_t type);

protected:
    /// @brief Processes incoming SOLICIT and returns response.
    ///
    /// Processes received SOLICIT message and verifies that its sender
    /// should be served. In particular IA, TA and PD options are populated
    /// with to-be assinged addresses, temporary addresses and delegated
    /// prefixes, respectively. In the usual 4 message exchange, server is
    /// expected to respond with ADVERTISE message. However, if client
    /// requests rapid-commit and server supports it, REPLY will be sent
    /// instead of ADVERTISE and requested leases will be assigned
    /// immediately.
    ///
    /// @param solicit SOLICIT message received from client
    ///
    /// @return ADVERTISE, REPLY message or NULL
    Pkt6Ptr processSolicit(const Pkt6Ptr& solicit);

    /// @brief Processes incoming REQUEST and returns REPLY response.
    ///
    /// Processes incoming REQUEST message and verifies that its sender
    /// should be served. In particular IA, TA and PD options are populated
    /// with assinged addresses, temporary addresses and delegated
    /// prefixes, respectively. Uses LeaseMgr to allocate or update existing
    /// leases.
    ///
    /// @param request a message received from client
    ///
    /// @return REPLY message or NULL
    Pkt6Ptr processRequest(const Pkt6Ptr& request);

    /// @brief Stub function that will handle incoming RENEW messages.
    ///
    /// @param renew message received from client
    Pkt6Ptr processRenew(const Pkt6Ptr& renew);

    /// @brief Stub function that will handle incoming REBIND messages.
    ///
    /// @param rebind message received from client
    Pkt6Ptr processRebind(const Pkt6Ptr& rebind);

    /// @brief Stub function that will handle incoming CONFIRM messages.
    ///
    /// @param confirm message received from client
    Pkt6Ptr processConfirm(const Pkt6Ptr& confirm);

    /// @brief Stub function that will handle incoming RELEASE messages.
    ///
    /// @param release message received from client
    Pkt6Ptr processRelease(const Pkt6Ptr& release);

    /// @brief Stub function that will handle incoming DECLINE messages.
    ///
    /// @param decline message received from client
    Pkt6Ptr processDecline(const Pkt6Ptr& decline);

    /// @brief Stub function that will handle incoming INF-REQUEST messages.
    ///
    /// @param infRequest message received from client
    Pkt6Ptr processInfRequest(const Pkt6Ptr& infRequest);

    /// @brief Creates status-code option.
    ///
    /// @param code status code value (see RFC3315)
    /// @param text textual explanation (will be sent in status code option)
    /// @return status-code option
    OptionPtr createStatusCode(uint16_t code, const std::string& text);

    /// @brief Selects a subnet for a given client's packet.
    ///
    /// @param question client's message
    /// @return selected subnet (or NULL if no suitable subnet was found)
    isc::dhcp::Subnet6Ptr selectSubnet(const Pkt6Ptr& question);

    /// @brief Processes IA_NA option (and assigns addresses if necessary).
    ///
    /// Generates response to IA_NA. This typically includes selecting (and
    /// allocating a lease in case of REQUEST) a lease and creating
    /// IAADDR option. In case of allocation failure, it may contain
    /// status code option with non-zero status, denoting cause of the
    /// allocation failure.
    ///
    /// @param subnet subnet the client is connected to
    /// @param duid client's duid
    /// @param question client's message (typically SOLICIT or REQUEST)
    /// @param ia pointer to client's IA_NA option (client's request)
    /// @return IA_NA option (server's response)
    OptionPtr handleIA_NA(const isc::dhcp::Subnet6Ptr& subnet,
                          const isc::dhcp::DuidPtr& duid,
                          isc::dhcp::Pkt6Ptr question,
                          boost::shared_ptr<Option6IA> ia);

    /// @brief Copies required options from client message to server answer.
    ///
    /// Copies options that must appear in any server response (ADVERTISE, REPLY)
    /// to client's messages (SOLICIT, REQUEST, RENEW, REBIND, DECLINE, RELEASE).
    /// One notable example is client-id. Other options may be copied as required.
    ///
    /// @param question client's message (options will be copied from here)
    /// @param answer server's message (options will be copied here)
    void copyDefaultOptions(const Pkt6Ptr& question, Pkt6Ptr& answer);

    /// @brief Appends default options to server's answer.
    ///
    /// Adds required options to server's answer. In particular, server-id
    /// is added. Possibly other mandatory options will be added, depending
    /// on type (or content) of client message.
    ///
    /// @param question client's message
    /// @param answer server's message (options will be added here)
    void appendDefaultOptions(const Pkt6Ptr& question, Pkt6Ptr& answer);

    /// @brief Appends requested options to server's answer.
    ///
    /// Appends options requested by client to the server's answer.
    ///
    /// @param question client's message
    /// @param answer server's message (options will be added here)
    void appendRequestedOptions(const Pkt6Ptr& question, Pkt6Ptr& answer);

    /// @brief Assigns leases.
    ///
    /// TODO: This method is currently a stub. It just appends one
    /// hardcoded lease. It supports addresses (IA_NA) only. It does NOT
    /// support temporary addresses (IA_TA) nor prefixes (IA_PD).
    ///
    /// @param question client's message (with requested IA_NA)
    /// @param answer server's message (IA_NA options will be added here)
    void assignLeases(const Pkt6Ptr& question, Pkt6Ptr& answer);

    /// @brief Sets server-identifier.
    ///
    /// This method attempts to set server-identifier DUID. It loads it
    /// from a file. If file load fails, it generates new DUID using
    /// interface link-layer addresses (EUI-64) + timestamp (DUID type
    /// duid-llt, see RFC3315, section 9.2). If there are no suitable
    /// interfaces present, exception it thrown
    ///
    /// @throws isc::Unexpected Failed to read DUID file and no suitable
    ///         interfaces for new DUID generation are detected.
    void setServerID();

    /// @brief Initializes option definitions for standard options.
    ///
    /// Each standard option's format is described by the
    /// dhcp::OptionDefinition object. This function creates such objects
    /// for each standard DHCPv6 option.
    ///
    /// @todo list thrown exceptions.
    /// @todo extend this function to cover all standard options. Currently
    /// it is limited to critical options only.
    void initStdOptionDefs();

private:
    /// @brief Allocation Engine.
    /// Pointer to the allocation engine that we are currently using
    /// It must be a pointer, because we will support changing engines
    /// during normal operation (e.g. to use different allocators)
    boost::shared_ptr<AllocEngine> alloc_engine_;

    /// Server DUID (to be sent in server-identifier option)
    boost::shared_ptr<isc::dhcp::Option> serverid_;

    /// Indicates if shutdown is in progress. Setting it to true will
    /// initiate server shutdown procedure.
    volatile bool shutdown_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP6_SRV_H
