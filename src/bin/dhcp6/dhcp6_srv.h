// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "dhcp/pkt6.h"
#include "dhcp/option.h"
#include <iostream>

namespace isc {

namespace dhcp {
/// @brief DHCPv6 server service.
///
/// This singleton class represents DHCPv6 server. It contains all
/// top-level methods and routines necessary for server operation.
/// In particular, it instantiates IfaceMgr, loads or generates DUID
/// that is going to be used as server-identifier, receives incoming
/// packets, processes them, manages leases assignment and generates
/// appropriate responses.
class Dhcpv6Srv : public boost::noncopyable {

public:
    /// @brief Default constructor.
    ///
    /// Instantiates necessary services, required to run DHCPv6 server.
    /// In particular, creates IfaceMgr that will be responsible for
    /// network interaction. Will instantiate lease manager, and load
    /// old or create new DUID.
    ///
    /// @param port port on will all sockets will listen
    Dhcpv6Srv(uint16_t port = DHCP6_SERVER_PORT);

    /// @brief Destructor. Used during DHCPv6 service shutdown.
    ~Dhcpv6Srv();

    /// @brief Returns server-intentifier option
    ///
    /// @return server-id option
    boost::shared_ptr<isc::dhcp::Option>
    getServerID() { return serverid_; }

    /// @brief Main server processing loop.
    ///
    /// Main server processing loop. Receives incoming packets, verifies
    /// their correctness, generates appropriate answer (if needed) and
    /// transmits respones.
    ///
    /// @return true, if being shut down gracefully, fail if experienced
    ///         critical error.
    bool run();

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
    boost::shared_ptr<Pkt6>
    processSolicit(boost::shared_ptr<Pkt6> solicit);

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
    boost::shared_ptr<Pkt6>
    processRequest(boost::shared_ptr<Pkt6> request);

    /// @brief Stub function that will handle incoming RENEW messages.
    ///
    /// @param renew message received from client
    boost::shared_ptr<Pkt6>
    processRenew(boost::shared_ptr<Pkt6> renew);

    /// @brief Stub function that will handle incoming REBIND messages.
    ///
    /// @param rebind message received from client
    boost::shared_ptr<Pkt6>
    processRebind(boost::shared_ptr<Pkt6> rebind);

    /// @brief Stub function that will handle incoming CONFIRM messages.
    ///
    /// @param confirm message received from client
    boost::shared_ptr<Pkt6>
    processConfirm(boost::shared_ptr<Pkt6> confirm);

    /// @brief Stub function that will handle incoming RELEASE messages.
    ///
    /// @param release message received from client
    boost::shared_ptr<Pkt6>
    processRelease(boost::shared_ptr<Pkt6> release);

    /// @brief Stub function that will handle incoming DECLINE messages.
    ///
    /// @param decline message received from client
    boost::shared_ptr<Pkt6>
    processDecline(boost::shared_ptr<Pkt6> decline);

    /// @brief Stub function that will handle incoming INF-REQUEST messages.
    ///
    /// @param infRequest message received from client
    boost::shared_ptr<Pkt6>
    processInfRequest(boost::shared_ptr<Pkt6> infRequest);

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

    /// server DUID (to be sent in server-identifier option)
    boost::shared_ptr<isc::dhcp::Option> serverid_;

    /// indicates if shutdown is in progress. Setting it to true will
    /// initiate server shutdown procedure.
    volatile bool shutdown;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP6_SRV_H
