// Copyright (C) 2011-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <dhcp/option.h>
#include <dhcp/option4_client_fqdn.h>
#include <dhcp/option_custom.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/alloc_engine.h>
#include <hooks/callout_handle.h>

#include <boost/noncopyable.hpp>

#include <iostream>
#include <queue>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when DHCID computation failed.
class DhcidComputeError : public isc::Exception {
public:
    DhcidComputeError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief DHCPv4 server service.
///
/// This singleton class represents DHCPv4 server. It contains all
/// top-level methods and routines necessary for server operation.
/// In particular, it instantiates IfaceMgr, loads or generates DUID
/// that is going to be used as server-identifier, receives incoming
/// packets, processes them, manages leases assignment and generates
/// appropriate responses.
///
/// This class does not support any controlling mechanisms directly.
/// See the derived \ref ControlledDhcpv4Srv class for support for
/// command and configuration updates over msgq.
///
/// For detailed explanation or relations between main(), ControlledDhcpv4Srv,
/// Dhcpv4Srv and other classes, see \ref dhcpv4Session.
class Dhcpv4Srv : public boost::noncopyable {

public:

    /// @brief defines if certain option may, must or must not appear
    typedef enum {
        FORBIDDEN,
        MANDATORY,
        OPTIONAL
    } RequirementLevel;

    /// @brief Default constructor.
    ///
    /// Instantiates necessary services, required to run DHCPv4 server.
    /// In particular, creates IfaceMgr that will be responsible for
    /// network interaction. Will instantiate lease manager, and load
    /// old or create new DUID. It is possible to specify alternate
    /// port on which DHCPv4 server will listen on. That is mostly useful
    /// for testing purposes. The Last two arguments of the constructor
    /// should be left at default values for normal server operation.
    /// They should be set to 'false' when creating an instance of this
    /// class for unit testing because features they enable require
    /// root privileges.
    ///
    /// @param port specifies port number to listen on
    /// @param dbconfig Lease manager configuration string.  The default
    ///        of the "memfile" manager is used for testing.
    /// @param use_bcast configure sockets to support broadcast messages.
    /// @param direct_response_desired specifies if it is desired to
    /// use direct V4 traffic.
    Dhcpv4Srv(uint16_t port = DHCP4_SERVER_PORT,
              const char* dbconfig = "type=memfile",
              const bool use_bcast = true,
              const bool direct_response_desired = true);

    /// @brief Destructor. Used during DHCPv4 service shutdown.
    virtual ~Dhcpv4Srv();

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

    /// @brief Return textual type of packet received by server
    ///
    /// Returns the name of valid packet received by the server (e.g. DISCOVER).
    /// If the packet is unknown - or if it is a valid DHCP packet but not one
    /// expected to be received by the server (such as an OFFER), the string
    /// "UNKNOWN" is returned.  This method is used in debug messages.
    ///
    /// As the operation of the method does not depend on any server state, it
    /// is declared static.
    ///
    /// @todo: This should be named static Pkt4::getName()
    ///
    /// @param type DHCPv4 packet type
    ///
    /// @return Pointer to "const" string containing the packet name.
    ///         Note that this string is statically allocated and MUST NOT
    ///         be freed by the caller.
    static const char* serverReceivedPacketName(uint8_t type);

    ///
    /// @name Public accessors returning values required to (re)open sockets.
    ///
    /// These accessors must be public because sockets are reopened from the
    /// static configuration callback handler. This callback handler invokes
    /// @c ControlledDhcpv4Srv::openActiveSockets which requires parameters
    /// which has to be retrieved from the @c ControlledDhcpv4Srv object.
    /// They are retrieved using these public functions
    //@{
    ///
    /// @brief Get UDP port on which server should listen.
    ///
    /// Typically, server listens on UDP port number 67. Other ports are used
    /// for testing purposes only.
    ///
    /// @return UDP port on which server should listen.
    uint16_t getPort() const {
        return (port_);
    }

    /// @brief Return bool value indicating that broadcast flags should be set
    /// on sockets.
    ///
    /// @return A bool value indicating that broadcast should be used (if true).
    bool useBroadcast() const {
        return (use_bcast_);
    }
    //@}

    /// @brief Open sockets which are marked as active in @c CfgMgr.
    ///
    /// This function reopens sockets according to the current settings in the
    /// Configuration Manager. It holds the list of the interfaces which server
    /// should listen on. This function will open sockets on these interfaces
    /// only. This function is not exception safe.
    ///
    /// @param port UDP port on which server should listen.
    /// @param use_bcast should broadcast flags be set on the sockets.
    static void openActiveSockets(const uint16_t port, const bool use_bcast);

protected:

    /// @brief verifies if specified packet meets RFC requirements
    ///
    /// Checks if mandatory option is really there, that forbidden option
    /// is not there, and that client-id or server-id appears only once.
    ///
    /// @param pkt packet to be checked
    /// @param serverid expectation regarding server-id option
    /// @throw RFCViolation if any issues are detected
    void sanityCheck(const Pkt4Ptr& pkt, RequirementLevel serverid);

    /// @brief Processes incoming DISCOVER and returns response.
    ///
    /// Processes received DISCOVER message and verifies that its sender
    /// should be served. In particular, a lease is selected and sent
    /// as an offer to a client if it should be served.
    ///
    /// @param discover DISCOVER message received from client
    ///
    /// @return OFFER message or NULL
    Pkt4Ptr processDiscover(Pkt4Ptr& discover);

    /// @brief Processes incoming REQUEST and returns REPLY response.
    ///
    /// Processes incoming REQUEST message and verifies that its sender
    /// should be served. In particular, verifies that requested lease
    /// is valid, not expired, not reserved, not used by other client and
    /// that requesting client is allowed to use it.
    ///
    /// Returns ACK message, NAK message, or NULL
    ///
    /// @param request a message received from client
    ///
    /// @return ACK or NAK message
    Pkt4Ptr processRequest(Pkt4Ptr& request);

    /// @brief Stub function that will handle incoming RELEASE messages.
    ///
    /// In DHCPv4, server does not respond to RELEASE messages, therefore
    /// this function does not return anything.
    ///
    /// @param release message received from client
    void processRelease(Pkt4Ptr& release);

    /// @brief Stub function that will handle incoming DHCPDECLINE messages.
    ///
    /// @param decline message received from client
    void processDecline(Pkt4Ptr& decline);

    /// @brief Stub function that will handle incoming INFORM messages.
    ///
    /// @param inform message received from client
    Pkt4Ptr processInform(Pkt4Ptr& inform);

    /// @brief Copies default parameters from client's to server's message
    ///
    /// Some fields are copied from client's message into server's response,
    /// e.g. client HW address, number of hops, transaction-id etc.
    ///
    /// @param question any message sent by client
    /// @param answer any message server is going to send as response
    void copyDefaultFields(const Pkt4Ptr& question, Pkt4Ptr& answer);

    /// @brief Appends options requested by client.
    ///
    /// This method assigns options that were requested by client
    /// (sent in PRL) or are enforced by server.
    ///
    /// @param question DISCOVER or REQUEST message from a client.
    /// @param msg outgoing message (options will be added here)
    void appendRequestedOptions(const Pkt4Ptr& question, Pkt4Ptr& msg);

    /// @brief Assigns a lease and appends corresponding options
    ///
    /// This method chooses the most appropriate lease for reqesting
    /// client and assigning it. Options corresponding to the lease
    /// are added to specific message.
    ///
    /// @param question DISCOVER or REQUEST message from client
    /// @param answer OFFER or ACK/NAK message (lease options will be added here)
    void assignLease(const Pkt4Ptr& question, Pkt4Ptr& answer);

    /// @brief Append basic options if they are not present.
    ///
    /// This function adds the following basic options if they
    /// are not yet added to the message:
    /// - Subnet Mask,
    /// - Router,
    /// - Name Server,
    /// - Domain Name.
    ///
    /// @param question DISCOVER or REQUEST message from a client.
    /// @param msg the message to add options to.
    void appendBasicOptions(const Pkt4Ptr& question, Pkt4Ptr& msg);

    /// @brief Processes Client FQDN and Hostname Options sent by a client.
    ///
    /// Client may send Client FQDN or Hostname option to communicate its name
    /// to the server. Server may use this name to perform DNS update for the
    /// lease being assigned to a client. If server takes responsibility for
    /// updating DNS for a client it may communicate it by sending the Client
    /// FQDN or Hostname %Option back to the client. Server select a different
    /// name than requested by a client to update DNS. In such case, the server
    /// stores this different name in its response.
    ///
    /// Client should not send both Client FQDN and Hostname options. However,
    /// if client sends both options, server should prefer Client FQDN option
    /// and ignore the Hostname option. If Client FQDN option is not present,
    /// the Hostname option is processed.
    ///
    /// The Client FQDN %Option is processed by this function as described in
    /// RFC4702.
    ///
    /// In response to a Hostname %Option sent by a client, the server may send
    /// Hostname option with the same or different hostname. If different
    /// hostname is sent, it is an indication to the client that server has
    /// overridden the client's preferred name and will rather use this
    /// different name to update DNS. However, since Hostname option doesn't
    /// carry an information whether DNS update will be carried by the server
    /// or not, the client is responsible for checking whether DNS update
    /// has been performed.
    ///
    /// After successful processing options stored in the first parameter,
    /// this function may add Client FQDN or Hostname option to the response
    /// message. In some cases, server may cease to add any options to the
    /// response, i.e. when server doesn't support DNS updates.
    ///
    /// @param query A DISCOVER or REQUEST message from a cient.
    /// @param [out] answer A response message to be sent to a client.
    void processClientName(const Pkt4Ptr& query, Pkt4Ptr& answer);

private:
    /// @brief Process Client FQDN %Option sent by a client.
    ///
    /// This function is called by the @c Dhcpv4Srv::processClientName when
    /// the client has sent the FQDN option in its message to the server.
    /// It comprises the actual logic to parse the FQDN option and prepare
    /// the FQDN option to be sent back to the client in the server's
    /// response.
    ///
    /// @param fqdn An DHCPv4 Client FQDN %Option sent by a client.
    /// @param [out] answer A response message to be sent to a client.
    void processClientFqdnOption(const Option4ClientFqdnPtr& fqdn,
                                 Pkt4Ptr& answer);

    /// @brief Process Hostname %Option sent by a client.
    ///
    /// @param opt_hostname An @c OptionCustom object encapsulating the Hostname
    /// %Option.
    /// @param [out] answer A response message to be sent to a client.
    void processHostnameOption(const OptionCustomPtr& opt_hostname,
                               Pkt4Ptr& answer);

protected:

    /// @brief Creates NameChangeRequests which correspond to the lease
    /// which has been acquired.
    ///
    /// If this function is called whe an existing lease is renewed, it
    /// may generate NameChangeRequest to remove existing DNS entries which
    /// correspond to the old lease instance. This function may cease to
    /// generate NameChangeRequests if the notion of the client's FQDN hasn't
    /// changed between an old and new lease.
    ///
    /// @param lease A pointer to the new lease which has been acquired.
    /// @param old_lease A pointer to the instance of the old lease which has
    /// been replaced by the new lease passed in the first argument. The NULL
    /// value indicates that the new lease has been allocated, rather than
    /// lease being renewed.
    void createNameChangeRequests(const Lease4Ptr& lease,
                                  const Lease4Ptr& old_lease);

    /// @brief Creates the NameChangeRequest and adds to the queue for
    /// processing.
    ///
    /// This function adds the @c isc::dhcp_ddns::NameChangeRequest to the
    /// queue and emits the debug message which indicates whether the request
    /// being added is to remove DNS entry or add a new entry. This function
    /// is exception free.
    ///
    /// @param chg_type A type of the NameChangeRequest (ADD or REMOVE).
    /// @param lease A lease for which the NameChangeRequest is created and
    /// queued.
    void queueNameChangeRequest(const isc::dhcp_ddns::NameChangeType chg_type,
                                const Lease4Ptr& lease);

    /// @brief Sends all outstanding NameChangeRequests to b10-dhcp-ddns module.
    ///
    /// The purpose of this function is to pick all outstanding
    /// NameChangeRequests from the FIFO queue and send them to b10-dhcp-ddns
    /// module.
    ///
    /// @todo Currently this function simply removes all requests from the
    /// queue but doesn't send them anywhere. In the future, the
    /// NameChangeSender will be used to deliver requests to the other module.
    void sendNameChangeRequests();

    /// @brief Attempts to renew received addresses
    ///
    /// Attempts to renew existing lease. This typically includes finding a lease that
    /// corresponds to the received address. If no such lease is found, a status code
    /// response is generated.
    ///
    /// @param renew client's message asking for renew
    /// @param reply server's response (ACK or NAK)
    void renewLease(const Pkt4Ptr& renew, Pkt4Ptr& reply);

    /// @brief Appends default options to a message
    ///
    /// @param msg message object (options will be added to it)
    /// @param msg_type specifies message type
    void appendDefaultOptions(Pkt4Ptr& msg, uint8_t msg_type);

    /// @brief Sets remote addresses for outgoing packet.
    ///
    /// This method sets the local and remote addresses on outgoing packet.
    /// The addresses being set depend on the following conditions:
    /// - has incoming packet been relayed,
    /// - is direct response to a client without address supported,
    /// - type of the outgoing packet,
    /// - broadcast flag set in the incoming packet.
    ///
    /// @warning This method does not check whether provided packet pointers
    /// are valid. Make sure that pointers are correct before calling this
    /// function.
    ///
    /// @param question instance of a packet received by a server.
    /// @param [out] msg response packet which addresses are to be adjusted.
    void adjustRemoteAddr(const Pkt4Ptr& question, Pkt4Ptr& msg);

    /// @brief Returns server-identifier option
    ///
    /// @return server-id option
    OptionPtr getServerID() { return serverid_; }

    /// @brief Sets server-identifier.
    ///
    /// This method attempts to set server-identifier DUID. It tries to
    /// load previously stored IP from configuration. If there is no previously
    /// stored server identifier, it will pick up one address from configured
    /// and supported network interfaces.
    ///
    /// @throws isc::Unexpected Failed to obtain server identifier (i.e. no
    //          previously stored configuration and no network interfaces available)
    void generateServerID();

    /// @brief attempts to load server-id from a file
    ///
    /// Tries to load duid from a text file. If the load is successful,
    /// it creates server-id option and stores it in serverid_ (to be used
    /// later by getServerID()).
    ///
    /// @param file_name name of the server-id file to load
    /// @return true if load was successful, false otherwise
    bool loadServerID(const std::string& file_name);

    /// @brief attempts to write server-id to a file
    /// Tries to write server-id content (stored in serverid_) to a text file.
    ///
    /// @param file_name name of the server-id file to write
    /// @return true if write was successful, false otherwise
    bool writeServerID(const std::string& file_name);

    /// @brief converts server-id to text
    /// Converts content of server-id option to a text representation, e.g.
    /// "192.0.2.1"
    ///
    /// @param opt option that contains server-id
    /// @return string representation
    static std::string srvidToString(const OptionPtr& opt);

    /// @brief Computes DHCID from a lease.
    ///
    /// This method creates an object which represents DHCID. The DHCID value
    /// is computed as described in RFC4701. The section 3.3. of RFC4701
    /// specifies the DHCID RR Identifier Type codes:
    /// - 0x0000 The 1 octet htype followed by glen octets of chaddr
    /// - 0x0001 The data octets from the DHCPv4 client's Client Identifier
    /// option.
    /// - 0x0002 The client's DUID.
    ///
    /// Currently this function supports first two of these identifiers.
    /// The 0x0001 is preferred over the 0x0000 - if the client identifier
    /// option is present, the former is used. If the client identifier
    /// is absent, the latter is used.
    ///
    /// @todo Implement support for 0x0002 DHCID identifier type.
    ///
    /// @param lease A pointer to the structure describing a lease.
    /// @return An object encapsulating DHCID to be used for DNS updates.
    /// @throw DhcidComputeError If the computation of the DHCID failed.
    static isc::dhcp_ddns::D2Dhcid computeDhcid(const Lease4Ptr& lease);

    /// @brief Selects a subnet for a given client's packet.
    ///
    /// @param question client's message
    /// @return selected subnet (or NULL if no suitable subnet was found)
    isc::dhcp::Subnet4Ptr selectSubnet(const Pkt4Ptr& question);

    /// server DUID (to be sent in server-identifier option)
    OptionPtr serverid_;

    /// indicates if shutdown is in progress. Setting it to true will
    /// initiate server shutdown procedure.
    volatile bool shutdown_;

    /// @brief dummy wrapper around IfaceMgr::receive4
    ///
    /// This method is useful for testing purposes, where its replacement
    /// simulates reception of a packet. For that purpose it is protected.
    virtual Pkt4Ptr receivePacket(int timeout);

    /// @brief dummy wrapper around IfaceMgr::send()
    ///
    /// This method is useful for testing purposes, where its replacement
    /// simulates transmission of a packet. For that purpose it is protected.
    virtual void sendPacket(const Pkt4Ptr& pkt);

private:

    /// @brief Constructs netmask option based on subnet4
    /// @param subnet subnet for which the netmask will be calculated
    ///
    /// @return Option that contains netmask information
    static OptionPtr getNetmaskOption(const Subnet4Ptr& subnet);

    /// @brief Allocation Engine.
    /// Pointer to the allocation engine that we are currently using
    /// It must be a pointer, because we will support changing engines
    /// during normal operation (e.g. to use different allocators)
    boost::shared_ptr<AllocEngine> alloc_engine_;

    uint16_t port_;  ///< UDP port number on which server listens.
    bool use_bcast_; ///< Should broadcast be enabled on sockets (if true).

    /// Indexes for registered hook points
    int hook_index_pkt4_receive_;
    int hook_index_subnet4_select_;
    int hook_index_pkt4_send_;

protected:

    /// Holds a list of @c isc::dhcp_ddns::NameChangeRequest objects which
    /// are waiting for sending  to b10-dhcp-ddns module.
    std::queue<isc::dhcp_ddns::NameChangeRequest> name_change_reqs_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP4_SRV_H
