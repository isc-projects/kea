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

#ifndef DHCPV4_SRV_H
#define DHCPV4_SRV_H

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <dhcp/option.h>
#include <iostream>

namespace isc {

namespace dhcp {
/// @brief DHCPv4 server service.
///
/// This singleton class represents DHCPv4 server. It contains all
/// top-level methods and routines necessary for server operation.
/// In particular, it instantiates IfaceMgr, loads or generates DUID
/// that is going to be used as server-identifier, receives incoming
/// packets, processes them, manages leases assignment and generates
/// appropriate responses.
class Dhcpv4Srv : public boost::noncopyable {

    public:
    /// @brief Default constructor.
    ///
    /// Instantiates necessary services, required to run DHCPv6 server.
    /// In particular, creates IfaceMgr that will be responsible for
    /// network interaction. Will instantiate lease manager, and load
    /// old or create new DUID. It is possible to specify alternate
    /// port on which DHCPv4 server will listen on. That is mostly useful
    /// for testing purposes.
    ///
    /// @param port specifies port number to listen on
    Dhcpv4Srv(uint16_t port = DHCP4_SERVER_PORT);

    /// @brief Destructor. Used during DHCPv6 service shutdown.
    ~Dhcpv4Srv();

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
    /// @brief Processes incoming DISCOVER and returns response.
    ///
    /// Processes received DISCOVER message and verifies that its sender
    /// should be served. In particular, a lease is selected and sent
    /// as an offer to a client if it should be served.
    ///
    /// @param solicit DISCOVER message received from client
    ///
    /// @return OFFER message or NULL
    boost::shared_ptr<Pkt4>
    processDiscover(boost::shared_ptr<Pkt4>& discover);

    /// @brief Processes incoming REQUEST and returns REPLY response.
    ///
    /// Processes incoming REQUEST message and verifies that its sender
    /// should be served. In particular, verifies that requested lease
    /// is valid, not expired, not reserved, not used by other client and
    /// that requesting client is allowed to use it.
    ///
    /// Returns ACK message, NACK message, or NULL
    ///
    /// @param request a message received from client
    ///
    /// @return ACK or NACK message
    boost::shared_ptr<Pkt4> processRequest(boost::shared_ptr<Pkt4>& request);

    /// @brief Stub function that will handle incoming RELEASE messages.
    ///
    /// In DHCPv4, server does not respond to RELEASE messages, therefore
    /// this function does not return anything.
    ///
    /// @param release message received from client
    void processRelease(boost::shared_ptr<Pkt4>& release);

    /// @brief Stub function that will handle incoming DHCPDECLINE messages.
    ///
    /// @param decline message received from client
    void processDecline(boost::shared_ptr<Pkt4>& decline);

    /// @brief Stub function that will handle incoming INFORM messages.
    ///
    /// @param infRequest message received from client
    boost::shared_ptr<Pkt4> processInform(boost::shared_ptr<Pkt4>& inform);

    /// @brief Copies default parameters from client's to server's message
    ///
    /// Some fields are copied from client's message into server's response,
    /// e.g. client HW address, number of hops, transaction-id etc.
    ///
    /// @param question any message sent by client
    /// @param answer any message server is going to send as response
    void copyDefaultFields(const boost::shared_ptr<Pkt4>& question,
                           boost::shared_ptr<Pkt4>& answer);


    /// @brief Appends options requested by client.
    ///
    /// This method assigns options that were requested by client
    /// (sent in PRL) or are enforced by server.
    ///
    /// @param msg outgoing message (options will be added here)
    void appendRequestedOptions(boost::shared_ptr<Pkt4>& msg);


    /// @brief Assigns a lease and appends corresponding options
    ///
    /// This method chooses the most appropriate lease for reqesting
    /// client and assigning it. Options corresponding to the lease
    /// are added to specific message.
    ///
    /// Note: Lease manager is not implemented yet, so this method
    /// used fixed, hardcoded lease.
    ///
    /// @param msg OFFER or ACK message (lease options will be added here)
    void tryAssignLease(boost::shared_ptr<Pkt4>& msg);


    /// @brief Appends default options to a message
    ///
    /// @param msg message object (options will be added to it)
    /// @param msg_type specifies message type
    void appendDefaultOptions(boost::shared_ptr<Pkt4>& msg, uint8_t msg_type);

    /// @brief Returns server-intentifier option
    ///
    /// @return server-id option
    boost::shared_ptr<isc::dhcp::Option>
    getServerID() { return serverid_; }

    /// @brief Sets server-identifier.
    ///
    /// This method attempts to set server-identifier DUID. It tries to
    /// load previously stored IP from configuration. If there is no previously
    /// stored server identifier, it will pick up one address from configured
    /// and supported network interfaces.
    ///
    /// @throws isc::Unexpected Failed to obtain server identifier (i.e. no
    //          previously stored configuration and no network interfaces available)
    void setServerID();

    /// server DUID (to be sent in server-identifier option)
    boost::shared_ptr<isc::dhcp::Option> serverid_;

    /// indicates if shutdown is in progress. Setting it to true will
    /// initiate server shutdown procedure.
    volatile bool shutdown_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP4_SRV_H
