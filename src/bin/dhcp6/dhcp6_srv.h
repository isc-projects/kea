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

#ifndef DHCPV6_SRV_H
#define DHCPV6_SRV_H

#include <dhcp_ddns/ncr_msg.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option_definition.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/alloc_engine.h>
#include <dhcpsrv/subnet.h>
#include <hooks/callout_handle.h>

#include <boost/noncopyable.hpp>

#include <iostream>
#include <queue>

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
/// @note Only one instance of this class is instantiated as it encompasses
///       the whole operation of the server.  Nothing, however, enforces the
///       singleton status of the object.
class Dhcpv6Srv : public boost::noncopyable {

public:
    /// @brief defines if certain option may, must or must not appear
    typedef enum {
        FORBIDDEN,
        MANDATORY,
        OPTIONAL
    } RequirementLevel;

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
    Dhcpv6Srv(uint16_t port = DHCP6_SERVER_PORT);

    /// @brief Destructor. Used during DHCPv6 service shutdown.
    virtual ~Dhcpv6Srv();

    /// @brief Returns server-indentifier option.
    ///
    /// @return server-id option
    OptionPtr getServerID() { return serverid_; }

    /// @brief Main server processing loop.
    ///
    /// Main server processing loop. Receives incoming packets, verifies
    /// their correctness, generates appropriate answer (if needed) and
    /// transmits responses.
    ///
    /// @return true, if being shut down gracefully, fail if experienced
    ///         critical error.
    bool run();

    /// @brief Instructs the server to shut down.
    void shutdown();

    /// @brief Get UDP port on which server should listen.
    ///
    /// Typically, server listens on UDP port 547. Other ports are only
    /// used for testing purposes.
    ///
    /// This accessor must be public because sockets are reopened from the
    /// static configuration callback handler. This callback handler invokes
    /// @c ControlledDhcpv4Srv::openActiveSockets which requires port parameter
    /// which has to be retrieved from the @c ControlledDhcpv4Srv object.
    /// They are retrieved using this public function.
    ///
    /// @return UDP port on which server should listen.
    uint16_t getPort() const {
        return (port_);
    }

    /// @brief Open sockets which are marked as active in @c CfgMgr.
    ///
    /// This function reopens sockets according to the current settings in the
    /// Configuration Manager. It holds the list of the interfaces which server
    /// should listen on. This function will open sockets on these interfaces
    /// only. This function is not exception safe.
    ///
    /// @param port UDP port on which server should listen.
    static void openActiveSockets(const uint16_t port);

protected:

    /// @brief verifies if specified packet meets RFC requirements
    ///
    /// Checks if mandatory option is really there, that forbidden option
    /// is not there, and that client-id or server-id appears only once.
    ///
    /// @param pkt packet to be checked
    /// @param clientid expectation regarding client-id option
    /// @param serverid expectation regarding server-id option
    /// @throw RFCViolation if any issues are detected
    void sanityCheck(const Pkt6Ptr& pkt, RequirementLevel clientid,
                     RequirementLevel serverid);

    /// @brief Processes incoming SOLICIT and returns response.
    ///
    /// Processes received SOLICIT message and verifies that its sender
    /// should be served. In particular IA, TA and PD options are populated
    /// with to-be assigned addresses, temporary addresses and delegated
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
    /// with assigned addresses, temporary addresses and delegated
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
    /// allocating a lease in case of REQUEST) an address lease and creating
    /// IAADDR option. In case of allocation failure, it may contain
    /// status code option with non-zero status, denoting cause of the
    /// allocation failure.
    ///
    /// @param subnet subnet the client is connected to
    /// @param duid client's duid
    /// @param query client's message (typically SOLICIT or REQUEST)
    /// @param ia pointer to client's IA_NA option (client's request)
    /// @param fqdn A DHCPv6 Client FQDN %Option generated in a response to the
    /// FQDN option sent by a client.
    /// @return IA_NA option (server's response)
    OptionPtr assignIA_NA(const isc::dhcp::Subnet6Ptr& subnet,
                          const isc::dhcp::DuidPtr& duid,
                          const isc::dhcp::Pkt6Ptr& query,
                          Option6IAPtr ia,
                          const Option6ClientFqdnPtr& fqdn);

    /// @brief Processes IA_PD option (and assigns prefixes if necessary).
    ///
    /// Generates response to IA_PD. This typically includes selecting (and
    /// allocating in the case of REQUEST) a prefix lease and creating an
    /// IAPREFIX option. In case of an allocation failure, it may contain a
    /// status code option with non-zero status denoting the cause of the
    /// allocation failure.
    ///
    /// @param subnet subnet the client is connected to
    /// @param duid client's duid
    /// @param query client's message (typically SOLICIT or REQUEST)
    /// @param ia pointer to client's IA_PD option (client's request)
    /// @return IA_PD option (server's response)
    OptionPtr assignIA_PD(const Subnet6Ptr& subnet, const DuidPtr& duid,
                          const Pkt6Ptr& query,
                          boost::shared_ptr<Option6IA> ia);

    /// @brief Renews specific IA_NA option
    ///
    /// Generates response to IA_NA in Renew. This typically includes finding a
    /// lease that corresponds to the received address. If no such lease is
    /// found, an IA_NA response is generated with an appropriate status code.
    ///
    /// @param subnet subnet the sender belongs to
    /// @param duid client's duid
    /// @param query client's message
    /// @param ia IA_NA option that is being renewed
    /// @param fqdn DHCPv6 Client FQDN Option included in the server's response
    /// @return IA_NA option (server's response)
    OptionPtr renewIA_NA(const Subnet6Ptr& subnet, const DuidPtr& duid,
                         const Pkt6Ptr& query, boost::shared_ptr<Option6IA> ia,
                         const Option6ClientFqdnPtr& fqdn);

    /// @brief Renews specific IA_PD option
    ///
    /// Generates response to IA_PD in Renew. This typically includes finding a
    /// lease that corresponds to the received prefix. If no such lease is
    /// found, an IA_PD response is generated with an appropriate status code.
    ///
    /// @param subnet subnet the sender belongs to
    /// @param duid client's duid
    /// @param query client's message
    /// @param ia IA_PD option that is being renewed
    /// @return IA_PD option (server's response)
    OptionPtr renewIA_PD(const Subnet6Ptr& subnet, const DuidPtr& duid,
                         const Pkt6Ptr& query, boost::shared_ptr<Option6IA> ia);

    /// @brief Releases specific IA_NA option
    ///
    /// Generates response to IA_NA in Release message. This covers finding and
    /// removal of a lease that corresponds to the received address. If no such
    /// lease is found, an IA_NA response is generated with an appropriate
    /// status code.
    ///
    /// As RFC 3315 requires that a single status code be sent for the whole message,
    /// this method may update the passed general_status: it is set to SUCCESS when
    /// message processing begins, but may be updated to some error code if the
    /// release process fails.
    ///
    /// @param duid client's duid
    /// @param query client's message
    /// @param general_status a global status (it may be updated in case of errors)
    /// @param ia IA_NA option that is being released
    /// @return IA_NA option (server's response)
    OptionPtr releaseIA_NA(const DuidPtr& duid, const Pkt6Ptr& query,
                           int& general_status,
                           boost::shared_ptr<Option6IA> ia);

    /// @brief Releases specific IA_PD option
    ///
    /// Generates response to IA_PD in Release message. This covers finding and
    /// removal of a lease that corresponds to the received prefix(es). If no such
    /// lease is found, an IA_PD response is generated with an appropriate
    /// status code.
    ///
    /// @param duid client's duid
    /// @param query client's message
    /// @param general_status a global status (it may be updated in case of errors)
    /// @param ia IA_PD option that is being released
    /// @return IA_PD option (server's response)
    OptionPtr releaseIA_PD(const DuidPtr& duid, const Pkt6Ptr& query,
                           int& general_status,
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

    /// @brief Appends requested vendor options to server's answer.
    ///
    /// This is mostly useful for Cable Labs options for now, but the method
    /// is easily extensible to other vendors.
    ///
    /// @param question client's message
    /// @param answer server's message (vendor options will be added here)
    void appendRequestedVendorOptions(const Pkt6Ptr& question, Pkt6Ptr& answer);

    /// @brief Assigns leases.
    ///
    /// It supports addresses (IA_NA) only. It does NOT support temporary
    /// addresses (IA_TA) nor prefixes (IA_PD).
    /// @todo: Extend this method once TA and PD becomes supported
    ///
    /// @param question client's message (with requested IA_NA)
    /// @param answer server's message (IA_NA options will be added here)
    /// @param fqdn an FQDN option generated in a response to the client's
    /// FQDN option.
    void assignLeases(const Pkt6Ptr& question, Pkt6Ptr& answer,
                      const Option6ClientFqdnPtr& fqdn);

    /// @brief Processes Client FQDN Option.
    ///
    /// This function retrieves DHCPv6 Client FQDN %Option (if any) from the
    /// packet sent by a client and takes necessary actions upon this option.
    /// Received option comprises flags field which controls what DNS updates
    /// server should do. Server may override client's preference based on
    /// the current configuration. Server indicates that it has overridden
    /// the preference by storing DHCPv6 Client Fqdn %Option with the
    /// appropriate flags in the response to a client. This option is also
    /// used to communicate the client's domain-name which should be sent
    /// to the DNS in the update. Again, server may act upon the received
    /// domain-name, i.e. if the provided domain-name is partial it should
    /// generate the fully qualified domain-name.
    ///
    /// All the logic required to form appropriate answer to the client is
    /// held in this function.
    ///
    /// @param question Client's message.
    ///
    /// @return FQDN option produced in the response to the client's message.
    Option6ClientFqdnPtr processClientFqdn(const Pkt6Ptr& question);

    /// @brief Adds DHCPv6 Client FQDN %Option to the server response.
    ///
    /// This function will add the specified FQDN option into the server's
    /// response when FQDN is not NULL and server is either configured to
    /// always include the FQDN in the response or client requested it using
    /// %Option Request %Option.
    /// This function is exception safe.
    ///
    /// @param question A message received from the client.
    /// @param [out] answer A server's response where FQDN option will be added.
    /// @param fqdn A DHCPv6 Client FQDN %Option to be added to the server's
    /// response to a client.
    void appendClientFqdn(const Pkt6Ptr& question,
                          Pkt6Ptr& answer,
                          const Option6ClientFqdnPtr& fqdn);

    /// @brief Creates a number of @c isc::dhcp_ddns::NameChangeRequest objects
    /// based on the DHCPv6 Client FQDN %Option.
    ///
    /// The @c isc::dhcp_ddns::NameChangeRequest class encapsulates the request
    /// from the DHCPv6 server to the DHCP-DDNS module to perform DNS Update.
    /// The FQDN option carries response to the client about DNS updates that
    /// server intents to perform for the DNS client. Based on this, the
    /// function will create zero or more @c isc::dhcp_ddns::NameChangeRequest
    /// objects and store them in the internal queue. Requests created by this
    /// function are only adding or updating DNS records. In order to generate
    /// requests for DNS records removal, use @c createRemovalNameChangeRequest.
    ///
    /// @todo Add support for multiple IAADDR options in the IA_NA.
    ///
    /// @param answer A message beging sent to the Client.
    /// @param fqdn_answer A DHCPv6 Client FQDN %Option which is included in the
    /// response message sent to a client.
    void createNameChangeRequests(const Pkt6Ptr& answer,
                                  const Option6ClientFqdnPtr& fqdn_answer);

    /// @brief Creates a @c isc::dhcp_ddns::NameChangeRequest which requests
    /// removal of DNS entries for a particular lease.
    ///
    /// This function should be called upon removal of the lease from the lease
    /// database, i.e, when client sent Release or Decline message. It will
    /// create a single @c isc::dhcp_ddns::NameChangeRequest which removes the
    /// existing DNS records for the lease, which server is responsible for.
    /// Note that this function will not remove the entries which server hadn't
    /// added. This is the case, when client performs forward DNS update on its
    /// own.
    ///
    /// @param lease A lease for which the the removal of corresponding DNS
    /// records will be performed.
    void createRemovalNameChangeRequest(const Lease6Ptr& lease);

    /// @brief Sends all outstanding NameChangeRequests to bind10-d2 module.
    ///
    /// The purpose of this function is to pick all outstanding
    /// NameChangeRequests from the FIFO queue and send them to bind10-dhcp-ddns
    /// module.
    ///
    /// @todo Currently this function simply removes all requests from the
    /// queue but doesn't send them anywhere. In the future, the
    /// NameChangeSender will be used to deliver requests to the other module.
    void sendNameChangeRequests();

    /// @brief Attempts to renew received addresses
    ///
    /// It iterates through received IA_NA options and attempts to renew
    /// received addresses. If no such leases are found, proper status
    /// code is added to reply message. Renewed addresses are added
    /// as IA_NA/IAADDR to reply packet.
    /// @param renew client's message asking for renew
    /// @param reply server's response
    /// @param fqdn A DHCPv6 Client FQDN %Option generated in the response to the
    /// client's FQDN option.
    void renewLeases(const Pkt6Ptr& renew, Pkt6Ptr& reply,
                     const Option6ClientFqdnPtr& fqdn);

    /// @brief Attempts to release received addresses
    ///
    /// It iterates through received IA_NA options and attempts to release
    /// received addresses. If no such leases are found, or the lease fails
    /// proper checks (e.g. belongs to someone else), a proper status
    /// code is added to reply message. Released addresses are not added
    /// to REPLY packet, just its IA_NA containers.
    /// @param release client's message asking to release
    /// @param reply server's response
    void releaseLeases(const Pkt6Ptr& release, Pkt6Ptr& reply);

    /// @brief Sets server-identifier.
    ///
    /// This method attempts to generate server-identifier DUID. It generates a
    /// new DUID using interface link-layer addresses (EUI-64) + timestamp (DUID
    /// type duid-llt, see RFC3315, section 9.2). If there are no suitable
    /// interfaces present, exception it thrown
    ///
    /// @throws isc::Unexpected Failed to read DUID file and no suitable
    ///         interfaces for new DUID generation are detected.
    void generateServerID();

    /// @brief attempts to load DUID from a file
    ///
    /// Tries to load duid from a text file. If the load is successful,
    /// it creates server-id option and stores it in serverid_ (to be used
    /// later by getServerID()).
    ///
    /// @param file_name name of the DUID file to load
    /// @return true if load was successful, false otherwise
    bool loadServerID(const std::string& file_name);

    /// @brief attempts to write DUID to a file
    /// Tries to write duid content (stored in serverid_) to a text file.
    ///
    /// @param file_name name of the DUID file to write
    /// @return true if write was successful, false otherwise
    bool writeServerID(const std::string& file_name);

    /// @brief converts DUID to text
    /// Converts content of DUID option to a text representation, e.g.
    /// 01:ff:02:03:06:80:90:ab:cd:ef
    ///
    /// @param opt option that contains DUID
    /// @return string representation
    static std::string duidToString(const OptionPtr& opt);


    /// @brief dummy wrapper around IfaceMgr::receive6
    ///
    /// This method is useful for testing purposes, where its replacement
    /// simulates reception of a packet. For that purpose it is protected.
    virtual Pkt6Ptr receivePacket(int timeout);

    /// @brief dummy wrapper around IfaceMgr::send()
    ///
    /// This method is useful for testing purposes, where its replacement
    /// simulates transmission of a packet. For that purpose it is protected.
    virtual void sendPacket(const Pkt6Ptr& pkt);

    /// @brief Implements a callback function to parse options in the message.
    ///
    /// @param buf a A buffer holding options in on-wire format.
    /// @param option_space A name of the option space which holds definitions
    /// of to be used to parse options in the packets.
    /// @param [out] options A reference to the collection where parsed options
    /// will be stored.
    /// @param relay_msg_offset Reference to a size_t structure. If specified,
    /// offset to beginning of relay_msg option will be stored in it.
    /// @param relay_msg_len reference to a size_t structure. If specified,
    /// length of the relay_msg option will be stored in it.
    /// @return An offset to the first byte after last parsed option.
    size_t unpackOptions(const OptionBuffer& buf,
                         const std::string& option_space,
                         isc::dhcp::OptionCollection& options,
                         size_t* relay_msg_offset,
                         size_t* relay_msg_len);

private:
    /// @brief Allocation Engine.
    /// Pointer to the allocation engine that we are currently using
    /// It must be a pointer, because we will support changing engines
    /// during normal operation (e.g. to use different allocators)
    boost::shared_ptr<AllocEngine> alloc_engine_;

    /// Server DUID (to be sent in server-identifier option)
    OptionPtr serverid_;

    /// Indicates if shutdown is in progress. Setting it to true will
    /// initiate server shutdown procedure.
    volatile bool shutdown_;

    /// UDP port number on which server listens.
    uint16_t port_;

protected:

    /// Holds a list of @c isc::dhcp_ddns::NameChangeRequest objects, which
    /// are waiting for sending to b10-dhcp-ddns module.
    std::queue<isc::dhcp_ddns::NameChangeRequest> name_change_reqs_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP6_SRV_H
