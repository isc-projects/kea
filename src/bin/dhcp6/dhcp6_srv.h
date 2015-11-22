// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/subnet.h>
#include <hooks/callout_handle.h>
#include <dhcpsrv/daemon.h>

#include <iostream>
#include <queue>

// Undefine the macro OPTIONAL which is defined in some operating
// systems but conflicts with a member of the RequirementLevel enum in
// the server class.

#ifdef OPTIONAL
#undef OPTIONAL
#endif

namespace isc {
namespace dhcp {

/// @brief This exception is thrown when DHCP server hits the error which should
/// result in discarding the message being processed.
class DHCPv6DiscardMessageError : public Exception {
public:
    DHCPv6DiscardMessageError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief DHCPv6 server service.
///
/// This class represents DHCPv6 server. It contains all
/// top-level methods and routines necessary for server operation.
/// In particular, it instantiates IfaceMgr, loads or generates DUID
/// that is going to be used as server-identifier, receives incoming
/// packets, processes them, manages leases assignment and generates
/// appropriate responses.
class Dhcpv6Srv : public Daemon {

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

    /// @brief returns Kea version on stdout and exit.
    /// redeclaration/redefinition. @ref Daemon::getVersion()
    static std::string getVersion(bool extended);

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
    /// @return UDP port on which server should listen.
    uint16_t getPort() const {
        return (port_);
    }

    /// @brief Starts DHCP_DDNS client IO if DDNS updates are enabled.
    ///
    /// If updates are enabled, it instructs the D2ClientMgr singleton to
    /// enter send mode.  If D2ClientMgr encounters errors it may throw
    /// D2ClientError. This method does not catch exceptions.
    void startD2();

    /// @brief Stops DHCP_DDNS client IO if DDNS updates are enabled.
    ///
    /// If updates are enabled, it instructs the D2ClientMgr singleton to
    /// leave send mode.  If D2ClientMgr encounters errors it may throw
    /// D2ClientError. This method does not catch exceptions.
    void stopD2();

    /// @brief Implements the error handler for DHCP_DDNS IO errors
    ///
    /// Invoked when a NameChangeRequest send to kea-dhcp-ddns completes with
    /// a failed status.  These are communications errors, not data related
    /// failures.
    ///
    /// This method logs the failure and then suspends all further updates.
    /// Updating can only be restored by reconfiguration or restarting the
    /// server.  There is currently no retry logic so the first IO error that
    /// occurs will suspend updates.
    /// @todo We may wish to make this more robust or sophisticated.
    ///
    /// @param result Result code of the send operation.
    /// @param ncr NameChangeRequest which failed to send.
    virtual void d2ClientErrorHandler(const dhcp_ddns::
                                      NameChangeSender::Result result,
                                      dhcp_ddns::NameChangeRequestPtr& ncr);

protected:

    /// @brief Compare received server id with our server id
    ///
    /// Checks if the server id carried in a query from a client matches
    /// server identifier being used by the server.
    ///
    /// @param pkt DHCPv6 packet carrying server identifier to be checked.
    /// @return true if server id carried in the query matches server id
    /// used by the server; false otherwise.
    bool testServerID(const Pkt6Ptr& pkt);

    /// @brief Check if the message can be sent to unicast.
    ///
    /// This function checks if the received message conforms to the section 15
    /// of RFC3315 which says that: "A server MUST discard any Solicit, Confirm,
    /// Rebind or Information-request messages it receives with a unicast
    /// destination address.
    ///
    /// @param pkt DHCPv6 message to be checked.
    /// @return false if the message has been sent to unicast address but it is
    /// not allowed according to RFC3315, section 15; true otherwise.
    bool testUnicast(const Pkt6Ptr& pkt) const;

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

    /// @brief Processes incoming Solicit and returns response.
    ///
    /// Processes received Solicit message and verifies that its sender
    /// should be served. In particular IA, TA and PD options are populated
    /// with to-be assigned addresses, temporary addresses and delegated
    /// prefixes, respectively. In the usual 4 message exchange, server is
    /// expected to respond with Advertise message. However, if client
    /// requests rapid-commit and server supports it, Reply will be sent
    /// instead of Advertise and requested leases will be assigned
    /// immediately.
    ///
    /// @param solicit Solicit message received from client
    ///
    /// @return Advertise, Reply message or NULL.
    Pkt6Ptr processSolicit(const Pkt6Ptr& solicit);

    /// @brief Processes incoming Request and returns Reply response.
    ///
    /// Processes incoming Request message and verifies that its sender
    /// should be served. In particular IA, TA and PD options are populated
    /// with assigned addresses, temporary addresses and delegated
    /// prefixes, respectively. Uses LeaseMgr to allocate or update existing
    /// leases.
    ///
    /// @param request a message received from client
    ///
    /// @return REPLY message or NULL
    Pkt6Ptr processRequest(const Pkt6Ptr& request);

    /// @brief Processes incoming Renew message.
    ///
    /// @param renew message received from the client
    /// @return Reply message to be sent to the client.
    Pkt6Ptr processRenew(const Pkt6Ptr& renew);

    /// @brief Processes incoming Rebind message.
    ///
    /// @todo There are cases when the Rebind message should be  discarded
    /// by the DHCP server. One of those is when the server doesn't have a
    /// record of the client and it is unable to determine whether the
    /// client is on the appropriate link or not. We don't seem to do it
    /// now.
    ///
    /// @param rebind message received from the client.
    /// @return Reply message to be sent to the client.
    Pkt6Ptr processRebind(const Pkt6Ptr& rebind);

    /// @brief Processes incoming Confirm message and returns Reply.
    ///
    /// This function processes Confirm message from the client according
    /// to section 18.2.2. of RFC3315. It discards the Confirm message if
    /// the message sent by the client contains no addresses, i.e. it has
    /// no IA_NA options or all IA_NA options contain no IAAddr options.
    ///
    /// If the Confirm message contains addresses this function will perform
    /// the following checks:
    /// - check if there is appropriate subnet configured for the client
    /// (e.g. subnet from which addresses are assigned for requests
    /// received on the particular interface).
    /// - check if all addresses sent in the Confirm message belong to the
    /// selected subnet.
    ///
    /// If any of the checks above fails, the Reply message with the status
    /// code NotOnLink is returned. Otherwise, the Reply message with the
    /// status code Success is returned.
    ///
    /// @param confirm Confirm message sent by a client.
    ///
    /// @return Reply message from the server or NULL pointer if Confirm
    /// message should be discarded by the server.
    Pkt6Ptr processConfirm(const Pkt6Ptr& confirm);

    /// @brief Process incoming Release message.
    ///
    /// @param release message received from client
    /// @return Reply message to be sent to the client.
    Pkt6Ptr processRelease(const Pkt6Ptr& release);

    /// @brief Process incoming Decline message.
    ///
    /// This method processes Decline message. It conducts standard sanity
    /// checks, creates empty reply and copies the necessary options from
    /// the client's message. Finally, it calls @ref declineLeases, where
    /// the actual address processing takes place.
    ///
    /// @throw RFCViolation if Decline message is invalid (lacking mandatory
    ///                     options)
    ///
    /// @param decline message received from client
    Pkt6Ptr processDecline(const Pkt6Ptr& decline);

    /// @brief Processes incoming Information-request message.
    ///
    /// @param inf_request message received from client
    /// @return Reply message to be sent to the client.
    Pkt6Ptr processInfRequest(const Pkt6Ptr& inf_request);

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
    /// @param query client's message (typically SOLICIT or REQUEST)
    /// @param answer server's response to the client's message. This
    /// message should contain Client FQDN option being sent by the server
    /// to the client (if the client sent this option to the server).
    /// @param orig_ctx client context (contains subnet, duid and other parameters)
    /// @param ia pointer to client's IA_NA option (client's request)
    ///
    /// @return IA_NA option (server's response)
    OptionPtr assignIA_NA(const isc::dhcp::Pkt6Ptr& query,
                          const isc::dhcp::Pkt6Ptr& answer,
                          AllocEngine::ClientContext6& orig_ctx,
                          Option6IAPtr ia);

    /// @brief Processes IA_PD option (and assigns prefixes if necessary).
    ///
    /// Generates response to IA_PD. This typically includes selecting (and
    /// allocating in the case of REQUEST) a prefix lease and creating an
    /// IAPREFIX option. In case of an allocation failure, it may contain a
    /// status code option with non-zero status denoting the cause of the
    /// allocation failure.
    ///
    /// @param query client's message (typically SOLICIT or REQUEST)
    /// @param answer server's response to the client's message.
    /// @param orig_ctx client context (contains subnet, duid and other parameters)
    /// @param ia pointer to client's IA_PD option (client's request)
    /// @return IA_PD option (server's response)
    OptionPtr assignIA_PD(const Pkt6Ptr& query,
                          const isc::dhcp::Pkt6Ptr& answer,
                          AllocEngine::ClientContext6& orig_ctx,
                          boost::shared_ptr<Option6IA> ia);

    /// @brief Extends lifetime of the specific IA_NA option.
    ///
    /// Generates response to IA_NA in Renew or Rebind. This typically includes
    /// finding a lease that corresponds to the received address. If no such
    /// lease is found, an IA_NA response is generated with an appropriate
    /// status code.
    ///
    /// @todo The behavior of this function will need to be extended to support
    /// draft-ietf-dhc-dhcpv6-stateful-issues. This draft modifies the behavior
    /// described in RFC3315 with respect to Renew and Rebind processing. Key
    /// changes are (version -05):
    /// - Renewing and Rebinding client MAY request additional bindings by
    /// putting an IA for all bindings it desires but has been unable to obtain.
    /// Server MAY allocate addresses if it finds that they are appropriate for
    /// the link that client is attached to.
    /// - When receiving Rebind, if the server determines that the addresses are
    /// not appropriate for the link the client is attached to, the server MAY
    /// send the IA with address lifetimes set to 0 or discard the message.
    ///
    /// @param query client's message (Renew or Rebind)
    /// @param answer server's response to the client's message. This
    /// message should contain Client FQDN option being sent by the server
    /// to the client (if the client sent this option to the server).
    /// @param orig_ctx client context (contains subnet, duid and other parameters)
    /// @param ia IA_NA option which carries address for which lease lifetime
    /// will be extended.
    /// @return IA_NA option (server's response)
    OptionPtr extendIA_NA(const Pkt6Ptr& query, const Pkt6Ptr& answer,
                          AllocEngine::ClientContext6& orig_ctx,
                          Option6IAPtr ia);

    /// @brief Extends lifetime of the prefix.
    ///
    /// This function is called by the logic which processes Renew and Rebind
    /// messages to extend the lifetime of the existing prefix.
    ///
    /// The behavior of this function is different in that when there is no
    /// binding found in the lease database for the particular client the
    /// NoBinding status code is returned when processing Renew, the exception
    /// is thrown when there is no binding and the Rebind message is processed
    /// (see RFC3633, section 12.2. for details).
    ///
    /// @param query client's message
    /// @param orig_ctx client context (contains subnet, duid and other parameters)
    /// @param ia IA_PD option that is being renewed
    /// @return IA_PD option (server's response)
    /// @throw DHCPv6DiscardMessageError when the message being processed should
    /// be discarded by the server, i.e. there is no binding for the client doing
    /// Rebind.
    OptionPtr extendIA_PD(const Pkt6Ptr& query,
                          AllocEngine::ClientContext6& orig_ctx,
                          Option6IAPtr ia);

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
    /// Relay information details are also copied here.
    ///
    /// @param question client's message (options will be copied from here)
    /// @param answer server's message (options will be copied here)
    void copyClientOptions(const Pkt6Ptr& question, Pkt6Ptr& answer);

    /// @brief Build the configured option list
    ///
    /// @note The configured option list is an *ordered* list of
    /// @c CfgOption objects used to append options to the response.
    ///
    /// @param question client's message
    /// @param ctx client context (for the subnet)
    /// @param co_list configured option list to build
    void buildCfgOptionList(const Pkt6Ptr& question,
                            AllocEngine::ClientContext6& ctx,
                            CfgOptionList& co_list);

    /// @brief Appends default options to server's answer.
    ///
    /// Adds required options to server's answer. In particular, server-id
    /// is added. Possibly other mandatory options will be added, depending
    /// on type (or content) of client message.
    ///
    /// @param question client's message
    /// @param answer server's message (options will be added here)
    /// @param co_list configured option list (currently unused)
    void appendDefaultOptions(const Pkt6Ptr& question, Pkt6Ptr& answer,
                              const CfgOptionList& co_list);

    /// @brief Appends requested options to server's answer.
    ///
    /// Appends options requested by client to the server's answer.
    ///
    /// @param question client's message
    /// @param answer server's message (options will be added here)
    /// @param co_list configured option list
    void appendRequestedOptions(const Pkt6Ptr& question, Pkt6Ptr& answer,
                                const CfgOptionList& co_list);

    /// @brief Appends requested vendor options to server's answer.
    ///
    /// This is mostly useful for Cable Labs options for now, but the method
    /// is easily extensible to other vendors.
    ///
    /// @param question client's message
    /// @param answer server's message (vendor options will be added here)
    /// @param ctx client context (contains subnet, duid and other parameters)
    /// @param co_list configured option list
    void appendRequestedVendorOptions(const Pkt6Ptr& question, Pkt6Ptr& answer,
                                      AllocEngine::ClientContext6& ctx,
                                      const CfgOptionList& co_list);

    /// @brief Assigns leases.
    ///
    /// It supports non-temporary addresses (IA_NA) and prefixes (IA_PD). It
    /// does NOT support temporary addresses (IA_TA).
    ///
    /// @param question client's message (with requested IA options)
    /// @param answer server's message (IA options will be added here).
    ///   This message should contain Client FQDN option being sent by the server
    ///   to the client (if the client sent this option to the server).
    /// @param ctx client context (contains subnet, duid and other parameters)
    void assignLeases(const Pkt6Ptr& question, Pkt6Ptr& answer,
                      AllocEngine::ClientContext6& ctx);

    /// @brief Processes Client FQDN Option.
    ///
    /// This function retrieves DHCPv6 Client FQDN %Option (if any) from the
    /// packet sent by a client and takes necessary actions upon this option.
    /// Received option comprises flags field which controls what DNS updates
    /// server should do. Server may override client's preference based on
    /// the current configuration. Server indicates that it has overridden
    /// the preference by storing DHCPv6 Client FQDN option with the
    /// appropriate flags in the response to a client. This option is also
    /// used to communicate the client's domain-name which should be sent
    /// to the DNS in the update. Again, server may act upon the received
    /// domain-name, i.e. if the provided domain-name is partial it should
    /// generate the fully qualified domain-name.
    ///
    /// This function takes into account the host reservation if one is matched
    /// to this client when forming the FQDN to be used with DNS as well as the
    /// lease name to be stored with the lease. In the following the term
    /// "reserved hostname" means a host reservation which includes a
    /// non-blank hostname.
    ///
    /// - If there is no Client FQDN and no reserved hostname then there
    /// will no be DNS updates and the lease hostname will be empty.
    ///
    /// - If there is no Client FQDN but there is reserved hostname then
    /// there will be no DNS updates and the lease hostname will be equal
    /// to reserved hostname.
    ///
    /// - If there is a Client FQDN and a reserved hostname, then both the
    /// FQDN and lease hostname will be equal to reserved hostname with
    /// the qualifying suffix appended.
    ///
    /// - If there is a Client FQDN but no reserved hostname then both the
    /// FQDN and lease hostname will be equal to the name provided in the
    /// client FQDN adjusted according the the DhcpDdns configuration
    /// parameters (e.g.replace-client-name, qualifying suffix...).
    ///
    /// All the logic required to form appropriate answer to the client is
    /// held in this function.
    ///
    /// @param question Client's message.
    /// @param answer Server's response to a client. If server generated
    /// Client FQDN option for the client, this option is stored in this
    /// object.
    /// @param ctx client context (includes subnet, client-id, hw-addr etc.)
    void processClientFqdn(const Pkt6Ptr& question, const Pkt6Ptr& answer,
                           AllocEngine::ClientContext6& ctx);

    /// @brief Creates a number of @c isc::dhcp_ddns::NameChangeRequest objects
    /// based on the DHCPv6 Client FQDN %Option.
    ///
    /// The @c isc::dhcp_ddns::NameChangeRequest class encapsulates the request
    /// from the DHCPv6 server to the DHCP-DDNS module to perform DNS Update.
    /// The FQDN option carries response to the client about DNS updates that
    /// server intends to perform for the DNS client. Based on this, the
    /// function will create zero or more @c isc::dhcp_ddns::NameChangeRequest
    /// objects and store them in the internal queue. Requests created by this
    /// function are only for adding or updating DNS records. If DNS updates are
    /// disabled, this method returns immediately.
    ///
    /// @todo Add support for multiple IAADDR options in the IA_NA.
    ///
    /// @param answer A message begins sent to the Client. If it holds the
    /// Client FQDN option, this option is used to create NameChangeRequests.
    void createNameChangeRequests(const Pkt6Ptr& answer);

    /// @brief Attempts to extend the lifetime of IAs.
    ///
    /// This function is called when a client sends Renew or Rebind message.
    /// It iterates through received IA options and attempts to extend
    /// corresponding lease lifetimes. Internally, it calls
    /// @c Dhcpv6Srv::extendIA_NA and @c Dhcpv6Srv::extendIA_PD to extend
    /// the lifetime of IA_NA and IA_PD leases accordingly.
    ///
    /// @param query client's Renew or Rebind message
    /// @param reply server's response
    /// @param ctx client context (contains subnet, duid and other parameters)
    void extendLeases(const Pkt6Ptr& query, Pkt6Ptr& reply,
                      AllocEngine::ClientContext6& ctx);

    /// @brief Attempts to release received addresses
    ///
    /// It iterates through received IA_NA options and attempts to release
    /// received addresses. If no such leases are found, or the lease fails
    /// proper checks (e.g. belongs to someone else), a proper status
    /// code is added to reply message. Released addresses are not added
    /// to REPLY packet, just its IA_NA containers.
    /// @param release client's message asking to release
    /// @param reply server's response
    /// @param ctx client context (includes subnet, client-id, hw-addr etc.)
    void releaseLeases(const Pkt6Ptr& release, Pkt6Ptr& reply,
                       AllocEngine::ClientContext6& ctx);

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

    /// @brief Assigns incoming packet to zero or more classes.
    ///
    /// @note This is done in two phases: first the content of the
    /// vendor-class-identifier option is used as a class, by
    /// calling @ref classifyByVendor(). Second classification match
    /// expressions are evaluated. The resulting classes will be stored
    /// in the packet (see @ref isc::dhcp::Pkt6::classes_ and
    /// @ref isc::dhcp::Pkt6::inClass).
    ///
    /// @param pkt packet to be classified
    void classifyPacket(const Pkt6Ptr& pkt);

    /// @brief Attempts to get a MAC/hardware address using configred sources
    ///
    /// Tries to extract MAC/hardware address information from the packet
    /// using MAC sources configured in 'mac-sources' configuration parameter.
    ///
    /// @param pkt will try to exact MAC address from this packet
    /// @return HWaddr pointer (or NULL if configured methods fail)
    static HWAddrPtr getMAC(const Pkt6Ptr& pkt);

    /// @brief Processes Relay-supplied options, if present
    ///
    /// This method implements RFC6422. It checks if there are any RSOO options
    /// inserted by the relay agents in the query message. If there are, they
    /// are copied over to the response if they meet the following criteria:
    /// - the option is marked as RSOO-enabled (see relay-supplied-options
    ///   configuration parameter)
    /// - there is no such option provided by the server)
    void processRSOO(const Pkt6Ptr& query, const Pkt6Ptr& rsp);

    /// @brief Creates client context for specified packet
    ///
    /// Instantiates the ClientContext6 and then:
    /// - Performs the subnet selection and stores the result in context
    /// - Extracts the duid from the packet and saves it to the context
    /// - Extracts the hardware address from the packet and saves it to
    /// the context
    /// - Performs host reservation lookup and stores the result in the
    /// context
    ///
    /// @return client context
    AllocEngine::ClientContext6 createContext(const Pkt6Ptr& pkt);

    /// @brief this is a prefix added to the contend of vendor-class option
    ///
    /// If incoming packet has a vendor class option, its content is
    /// prepended with this prefix and then interpreted as a class.
    /// For example, a packet that sends vendor class with value of "FOO"
    /// will cause the packet to be assigned to class VENDOR_CLASS_FOO.
    static const std::string VENDOR_CLASS_PREFIX;

    /// @brief Attempts to decline all leases in specified Decline message.
    ///
    /// This method iterates over all IA_NA options and calls @ref declineIA on
    /// each of them.
    ///
    /// @param decline Decline messege sent by a client
    /// @param reply Server's response (IA_NA with status will be added here)
    /// @param client context
    /// @return true when expected to continue, false when hooks told us to drop
    ///         the packet
    bool declineLeases(const Pkt6Ptr& decline, Pkt6Ptr& reply,
                       AllocEngine::ClientContext6& ctx);

    /// @brief Declines leases in a single IA_NA option
    ///
    /// This method iterates over all addresses in this IA_NA, verifies
    /// whether they belong to the client and calls @ref declineLease. If there's
    /// an error, general_status (a status put in the top level scope), will be
    /// updated.
    ///
    /// @param decline client's Decline message
    /// @param duid client's duid (used to verify if the client owns the lease)
    /// @param general_status [out] status in top-level message (may be updated)
    /// @param ia specific IA_NA option to process.
    /// @return IA_NA option with response (to be included in Reply message)
    OptionPtr
    declineIA(const Pkt6Ptr& decline, const DuidPtr& duid, int& general_status,
              boost::shared_ptr<Option6IA> ia);

    /// @brief Declines specific IPv6 lease.
    ///
    /// This method performs the actual decline and all necessary operations:
    /// - cleans up DNS, if necessary
    /// - updates subnet[X].declined-addresses (per subnet stat)
    /// - updates declined-addresses (global stat)
    /// - deassociates client information from the lease
    /// - moves the lease to DECLINED state
    /// - sets lease expiration time to decline-probation-period
    /// - adds status-code success
    ///
    /// @param decline used for generating removal Name Change Request.
    /// @param lease lease to be declined
    /// @param ia_rsp response IA_NA.
    /// @return true when expected to continue, false when hooks told us to drop
    ///         the packet
    bool declineLease(const Pkt6Ptr& decline, const Lease6Ptr lease,
                      boost::shared_ptr<Option6IA> ia_rsp);

    /// @brief A simple utility method that sets the status code
    ///
    /// Removes old status code and sets a new one.
    /// @param container status code will be added here
    /// @param status status code option
    void setStatusCode(boost::shared_ptr<Option6IA>& container,
                       const OptionPtr& status);

private:

    /// @brief Assign class using vendor-class-identifier option
    ///
    /// @note This is the first part of @ref classifyPacket
    ///
    /// @param pkt packet to be classified
    /// @param classes a reference to added class names for logging
    void classifyByVendor(const Pkt6Ptr& pkt, std::string& classes);

    /// @brief Generate FQDN to be sent to a client if none exists.
    ///
    /// This function is meant to be called by the functions which process
    /// client's messages. The function should be called after a function
    /// which creates FQDN option for the client. This option must exist
    /// in the answer message specified as an argument. It must also be
    /// called after functions which assign leases for a client. The
    /// IA options being a result of lease acquisition must be appended
    /// to the message specified as a parameter.
    ///
    /// If the Client FQDN option being present in the message carries empty
    /// hostname, this function will attempt to generate hostname from the
    /// IPv6 address being acquired by the client. The IPv6 address is retrieved
    /// from the IA_NA option carried in the specified message. If multiple
    /// addresses are present in the particular IA_NA option or multiple IA_NA
    /// options exist, the first address found is selected.
    ///
    /// The IPv6 address is converted to the hostname using the following
    /// pattern:
    /// @code
    ///     prefix-converted-ip-address.domain-name-suffix.
    /// @endcode
    /// where:
    /// - prefix is a configurable prefix string appended to all auto-generated
    /// hostnames.
    /// - converted-ip-address is created by replacing all colons from the IPv6
    /// address with hyphens.
    /// - domain-name-suffix is a suffix for a domain name that, together with
    /// the other parts, constitute the fully qualified domain name.
    ///
    /// When hostname is successfully generated, it is either used to update
    /// FQDN-related fields in a lease database or to update the Client FQDN
    /// option being sent back to the client. The lease database update is
    /// NOT performed if Advertise message is being processed.
    ///
    /// @param answer Message being sent to a client, which may hold IA_NA
    /// and Client FQDN options to be used to generate name for a client.
    ///
    /// @throw isc::Unexpected if specified message is NULL. This is treated
    /// as a programmatic error.
    void generateFqdn(const Pkt6Ptr& answer);

    /// @brief Updates statistics for received packets
    /// @param query packet received
    static void processStatsReceived(const Pkt6Ptr& query);

    /// @brief Updates statistics for transmitted packets
    /// @param query packet transmitted
    static void processStatsSent(const Pkt6Ptr& response);

    /// Server DUID (to be sent in server-identifier option)
    OptionPtr serverid_;

    /// UDP port number on which server listens.
    uint16_t port_;

protected:

    /// Indicates if shutdown is in progress. Setting it to true will
    /// initiate server shutdown procedure.
    volatile bool shutdown_;

    /// @brief Allocation Engine.
    /// Pointer to the allocation engine that we are currently using
    /// It must be a pointer, because we will support changing engines
    /// during normal operation (e.g. to use different allocators)
    boost::shared_ptr<AllocEngine> alloc_engine_;

    /// Holds a list of @c isc::dhcp_ddns::NameChangeRequest objects, which
    /// are waiting for sending to kea-dhcp-ddns module.
    std::queue<isc::dhcp_ddns::NameChangeRequest> name_change_reqs_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP6_SRV_H
