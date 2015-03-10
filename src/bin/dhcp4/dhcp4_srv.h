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

#ifndef DHCPV4_SRV_H
#define DHCPV4_SRV_H

#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <dhcp/option.h>
#include <dhcp/option_string.h>
#include <dhcp/option4_client_fqdn.h>
#include <dhcp/option_custom.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/alloc_engine.h>
#include <hooks/callout_handle.h>
#include <dhcpsrv/daemon.h>

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

/// @brief DHCPv4 message exchange.
///
/// This class represents the DHCPv4 message exchange. The message exchange
/// consists of the single client message, server response to this message
/// and the mechanisms to generate the server's response. The server creates
/// the instance of the @c DHCPv4Exchange for each inbound message that it
/// accepts for processing.
///
/// The use of the @c DHCPv4Exchange object as a central repository of
/// information about the message exchange simplifies the API of the
/// @c Dhcpv4Srv class.
///
/// Another benefit of using this class is that different methods of the
/// @c Dhcpv4Srv may share information. For example, the constructor of this
/// class selects the subnet and multiple methods of @c Dhcpv4Srv use this
/// subnet, without the need to select it again.
///
/// @todo This is the initial version of this class. In the future a lot of
/// code from the @c Dhcpv4Srv class will be migrated here.
class DHCPv4Exchange {
public:
    /// @brief Constructor.
    ///
    /// The constructor selects the subnet for the query and checks for the
    /// static host reservations for the client which has sent the message.
    /// The information about the reservations is stored in the
    /// @c AllocEngine::ClientContext4 object, which can be obtained by
    /// calling the @c getContext.
    ///
    /// @param alloc_engine Pointer to the instance of the Allocation Engine
    /// used by the server.
    /// @param query Pointer to the client message.
    DHCPv4Exchange(const AllocEnginePtr& alloc_engine, const Pkt4Ptr& query);

    /// @brief Initializes the instance of the response message.
    ///
    /// The type of the response depends on the type of the query message.
    /// For the DHCPDISCOVER the DHCPOFFER is created. For the DHCPREQUEST
    /// and DHCPINFORM the DHCPACK is created. For the DHCPRELEASE the
    /// response is not initialized.
    void initResponse();

    /// @brief Selects the subnet for the message processing.
    ///
    /// The pointer to the selected subnet is stored in the @c ClientContext4
    /// structure.
    void selectSubnet();

    /// @brief Selects the subnet for the message processing.
    ///
    /// @todo This variant of the @c selectSubnet method is static and public so
    /// as it may be invoked by the @c Dhcpv4Srv object. This is temporary solution
    /// and the function will go away once the server code fully supports the use
    /// of this class and it obtains the subnet from the context returned by the
    /// @c getContext method.
    ///
    /// @param query Pointer to the client's message.
    /// @return Pointer to the selected subnet or NULL if no suitable subnet
    /// has been found.
    static Subnet4Ptr selectSubnet(const Pkt4Ptr& query);

    /// @brief Returns the pointer to the query from the client.
    Pkt4Ptr getQuery() const {
        return (query_);
    }

    /// @brief Returns the pointer to the server's response.
    ///
    /// The returned pointer is NULL if the query type is DHCPRELEASE or DHCPDECLINE.
    Pkt4Ptr getResponse() const {
        return (resp_);
    }

    /// @brief Removes the response message by resetting the pointer to NULL.
    void deleteResponse() {
        resp_.reset();
    }

    /// @brief Returns the copy of the context for the Allocation engine.
    AllocEngine::ClientContext4Ptr getContext() const {
        return (context_);
    }

private:
    /// @brief Pointer to the allocation engine used by the server.
    AllocEnginePtr alloc_engine_;
    /// @brief Pointer to the DHCPv4 message sent by the client.
    Pkt4Ptr query_;
    /// @brief Pointer to the DHCPv4 message to be sent to the client.
    Pkt4Ptr resp_;
    /// @brief Context for use with allocation engine.
    AllocEngine::ClientContext4Ptr context_;
};

/// @brief Type representing the pointer to the @c DHCPv4Exchange.
typedef boost::shared_ptr<DHCPv4Exchange> DHCPv4ExchangePtr;


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
class Dhcpv4Srv : public Daemon {

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
    /// @param use_bcast configure sockets to support broadcast messages.
    /// @param direct_response_desired specifies if it is desired to
    /// use direct V4 traffic.
    Dhcpv4Srv(uint16_t port = DHCP4_SERVER_PORT,
              const bool use_bcast = true,
              const bool direct_response_desired = true);

    /// @brief Destructor. Used during DHCPv4 service shutdown.
    virtual ~Dhcpv4Srv();

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

    /// @brief Starts DHCP_DDNS client IO if DDNS updates are enabled.
    ///
    /// If updates are enabled, it Instructs the D2ClientMgr singleton to
    /// enter send mode.  If D2ClientMgr encounters errors it may throw
    /// D2ClientErrors. This method does not catch exceptions.
    void startD2();

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

    /// @name Functions filtering and sanity-checking received messages.
    ///
    /// @todo These functions are supposed to be moved to a new class which
    /// will manage different rules for accepting and rejecting messages.
    /// Perhaps ticket #3116 is a good opportunity to do it.
    ///
    //@{
    /// @brief Checks whether received message should be processed or discarded.
    ///
    /// This function checks whether received message should be processed or
    /// discarded. It should be called on the beginning of message processing
    /// (just after the message has been decoded). This message calls a number
    /// of other functions which check whether message should be processed,
    /// using different criteria.
    ///
    /// This function should be extended when new criteria for accepting
    /// received message have to be implemented. This function is meant to
    /// aggregate all early filtering checks on the received message. By having
    /// a single function like this, we are avoiding bloat of the server's main
    /// loop.
    ///
    /// @warning This function should remain exception safe.
    ///
    /// @param query Received message.
    ///
    /// @return true if the message should be further processed, or false if
    /// the message should be discarded.
    bool accept(const Pkt4Ptr& query) const;

    /// @brief Check if a message sent by directly connected client should be
    /// accepted or discarded.
    ///
    /// This function checks if the received message is from directly connected
    /// client. If it is, it checks that it should be processed or discarded.
    ///
    /// Note that this function doesn't validate all addresses being carried in
    /// the message. The primary purpose of this function is to filter out
    /// direct messages in the local network for which there is no suitable
    /// subnet configured. For example, this function accepts unicast messages
    /// because unicasts may be used by clients located in remote networks to
    /// to renew existing leases. If their notion of address is wrong, the
    /// server will have to sent a NAK, instead of dropping the message.
    /// Detailed validation of such messages is performed at later stage of
    /// processing.
    ///
    /// This function accepts the following messages:
    /// - all valid relayed messages,
    /// - all unicast messages,
    /// - all broadcast messages except DHCPINFORM received on the interface
    /// for which the suitable subnet exists (is configured).
    /// - all DHCPINFORM messages with source address or ciaddr set.
    ///
    /// @param query Message sent by a client.
    ///
    /// @return true if message is accepted for further processing, false
    /// otherwise.
    bool acceptDirectRequest(const Pkt4Ptr& query) const;

    /// @brief Check if received message type is valid for the server to
    /// process.
    ///
    /// This function checks that the received message type belongs to
    /// the range of types recognized by the server and that the
    /// message of this type should be processed by the server.
    ///
    /// The messages types accepted for processing are:
    /// - Discover
    /// - Request
    /// - Release
    /// - Decline
    /// - Inform
    ///
    /// @param query Message sent by a client.
    ///
    /// @return true if message is accepted for further processing, false
    /// otherwise.
    bool acceptMessageType(const Pkt4Ptr& query) const;

    /// @brief Verifies if the server id belongs to our server.
    ///
    /// This function checks if the server identifier carried in the specified
    /// DHCPv4 message belongs to this server. If the server identifier option
    /// is absent or the value carried by this option is equal to one of the
    /// server identifiers used by the server, the true is returned. If the
    /// server identifier option is present, but it doesn't match any server
    /// identifier used by this server, the false value is returned.
    ///
    /// @param pkt DHCPv4 message which server identifier is to be checked.
    ///
    /// @return true, if the server identifier is absent or matches one of the
    /// server identifiers that the server is using; false otherwise.
    bool acceptServerId(const Pkt4Ptr& pkt) const;
    //@}

    /// @brief Verifies if specified packet meets RFC requirements
    ///
    /// Checks if mandatory option is really there, that forbidden option
    /// is not there, and that client-id or server-id appears only once.
    ///
    /// @param ex DHCPv4 exchange holding the client's message to be checked.
    /// @param serverid expectation regarding server-id option
    /// @throw RFCViolation if any issues are detected
    static void sanityCheck(const DHCPv4Exchange& ex, RequirementLevel serverid);

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
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    void copyDefaultFields(DHCPv4Exchange& ex);

    /// @brief Appends options requested by client.
    ///
    /// This method assigns options that were requested by client
    /// (sent in PRL) or are enforced by server.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    void appendRequestedOptions(DHCPv4Exchange& ex);

    /// @brief Appends requested vendor options as requested by client.
    ///
    /// This method is similar to \ref appendRequestedOptions(), but uses
    /// vendor options. The major difference is that vendor-options use
    /// its own option spaces (there may be more than one distinct set of vendor
    /// options, each with unique vendor-id). Vendor options are requested
    /// using separate options within their respective vendor-option spaces.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    void appendRequestedVendorOptions(DHCPv4Exchange& ex);

    /// @brief Assigns a lease and appends corresponding options
    ///
    /// This method chooses the most appropriate lease for requesting
    /// client and assigning it. Options corresponding to the lease
    /// are added to specific message.
    ///
    /// This method may reset the pointer to the response in the @c ex object
    /// to indicate that the response should not be sent to the client.
    /// The caller must check if the response is is null after calling
    /// this method.
    ///
    /// The response type in the @c ex object may be set to DHCPACK or DHCPNAK.
    ///
    /// @param ex DHCPv4 exchange holding the client's message to be checked.
    void assignLease(DHCPv4Exchange& ex);

    /// @brief Append basic options if they are not present.
    ///
    /// This function adds the following basic options if they
    /// are not yet added to the response message:
    /// - Subnet Mask,
    /// - Router,
    /// - Name Server,
    /// - Domain Name.
    ///
    /// @param ex DHCPv4 exchange holding the client's message to be checked.
    void appendBasicOptions(DHCPv4Exchange& ex);

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
    /// This function does not throw. It simply logs the debug message if the
    /// processing of the FQDN or Hostname failed.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    void processClientName(DHCPv4Exchange& ex);

    /// @brief this is a prefix added to the contend of vendor-class option
    ///
    /// If incoming packet has a vendor class option, its content is
    /// prepended with this prefix and then interpreted as a class.
    /// For example, a packet that sends vendor class with value of "FOO"
    /// will cause the packet to be assigned to class VENDOR_CLASS_FOO.
    static const std::string VENDOR_CLASS_PREFIX;

private:
    /// @brief Process Client FQDN %Option sent by a client.
    ///
    /// This function is called by the @c Dhcpv4Srv::processClientName when
    /// the client has sent the FQDN option in its message to the server.
    /// It comprises the actual logic to parse the FQDN option and prepare
    /// the FQDN option to be sent back to the client in the server's
    /// response.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    void processClientFqdnOption(DHCPv4Exchange& ex);

    /// @brief Process Hostname %Option sent by a client.
    ///
    /// This function is called by the @c Dhcpv4Srv::processClientName when
    /// the client has sent the Hostname option in its message to the server.
    /// It comprises the actual logic to parse the Hostname option and
    /// prepare the Hostname option to be sent back to the client in the
    /// server's response.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    void processHostnameOption(DHCPv4Exchange& ex);

protected:

    /// @brief Creates NameChangeRequests which correspond to the lease
    /// which has been acquired.
    ///
    /// If this function is called when an existing lease is renewed, it
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
    /// This creates the @c isc::dhcp_ddns::NameChangeRequest; emits a
    /// the debug message which indicates whether the request being added is
    /// to remove DNS entry or add a new entry; and then sends the request
    /// to the D2ClientMgr for transmission to kea-dhcp-ddns.
    ///
    /// @param chg_type A type of the NameChangeRequest (ADD or REMOVE).
    /// @param lease A lease for which the NameChangeRequest is created and
    /// queued.
    void queueNameChangeRequest(const isc::dhcp_ddns::NameChangeType chg_type,
                                const Lease4Ptr& lease);

    /// @brief Attempts to renew received addresses
    ///
    /// Attempts to renew existing lease. This typically includes finding a lease that
    /// corresponds to the received address. If no such lease is found, a status code
    /// response is generated.
    ///
    /// @param renew client's message asking for renew
    /// @param reply server's response (ACK or NAK)
    void renewLease(const Pkt4Ptr& renew, Pkt4Ptr& reply);

    /// @brief Appends default options to a message.
    ///
    /// This method is currently no-op.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    void appendDefaultOptions(DHCPv4Exchange& ex);

    /// @brief Adds server identifier option to the server's response.
    ///
    /// This method adds a server identifier to the DHCPv4 message. It expects
    /// that the local (source) address is set for this message. If address is
    /// not set, it will throw an exception. This method also expects that the
    /// server identifier option is not present in the specified message.
    /// Otherwise, it will throw an exception on attempt to add a duplicate
    /// server identifier option.
    ///
    /// @note This method doesn't throw exceptions by itself but the underlying
    /// classes being used my throw. The reason for this method to not sanity
    /// check the specified message is that it is meant to be called internally
    /// by the @c Dhcpv4Srv class.
    ///
    /// @note This method is static because it is not dependent on the class
    /// state.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    static void appendServerID(DHCPv4Exchange& ex);

    /// @brief Set IP/UDP and interface parameters for the DHCPv4 response.
    ///
    /// This method sets the following parameters for the DHCPv4 message being
    /// sent to a client:
    /// - client unicast or a broadcast address,
    /// - client or relay port,
    /// - server address,
    /// - server port,
    /// - name and index of the interface which is to be used to send the
    /// message.
    ///
    /// Internally it calls the @c Dhcpv4Srv::adjustRemoteAddr to figure
    /// out the destination address (client unicast address or broadcast
    /// address).
    ///
    /// The destination port is always DHCPv4 client (68) or relay (67) port,
    /// depending if the response will be sent directly to a client.
    ///
    /// The source port is always set to DHCPv4 server port (67).
    ///
    /// The interface selected for the response is always the same as the
    /// one through which the query has been received.
    ///
    /// The source address for the response is the IPv4 address assigned to
    /// the interface being used to send the response. This function uses
    /// @c IfaceMgr to get the socket bound to the IPv4 address on the
    /// particular interface.
    ///
    /// @note This method is static because it is not dependent on the class
    /// state.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    static void adjustIfaceData(DHCPv4Exchange& ex);

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
    /// @note This method is static because it is not dependent on the class
    /// state.
    ///
    /// @param ex The exchange holding both the client's message and the
    /// server's response.
    static void adjustRemoteAddr(DHCPv4Exchange& ex);

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
    static isc::dhcp::Subnet4Ptr selectSubnet(const Pkt4Ptr& question);

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

    /// @brief Implements a callback function to parse options in the message.
    ///
    /// @param buf a A buffer holding options in on-wire format.
    /// @param option_space A name of the option space which holds definitions
    /// of to be used to parse options in the packets.
    /// @param [out] options A reference to the collection where parsed options
    /// will be stored.
    /// @return An offset to the first byte after last parsed option.
    size_t unpackOptions(const OptionBuffer& buf,
                         const std::string& option_space,
                         isc::dhcp::OptionCollection& options);

    /// @brief Assigns incoming packet to zero or more classes.
    ///
    /// @note For now, the client classification is very simple. It just uses
    /// content of the vendor-class-identifier option as a class. The resulting
    /// class will be stored in packet (see @ref isc::dhcp::Pkt4::classes_ and
    /// @ref isc::dhcp::Pkt4::inClass).
    ///
    /// @param pkt packet to be classified
    void classifyPacket(const Pkt4Ptr& pkt);

    /// @brief Performs packet processing specific to a class
    ///
    /// This processing is a likely candidate to be pushed into hooks.
    ///
    /// @param query incoming client's packet
    /// @param rsp server's response
    /// @return true if successful, false otherwise (will prevent sending response)
    bool classSpecificProcessing(const Pkt4Ptr& query, const Pkt4Ptr& rsp);

    /// @brief Allocation Engine.
    /// Pointer to the allocation engine that we are currently using
    /// It must be a pointer, because we will support changing engines
    /// during normal operation (e.g. to use different allocators)
    boost::shared_ptr<AllocEngine> alloc_engine_;

private:

    /// @brief Constructs netmask option based on subnet4
    /// @param subnet subnet for which the netmask will be calculated
    ///
    /// @return Option that contains netmask information
    static OptionPtr getNetmaskOption(const Subnet4Ptr& subnet);

    /// @brief Implements the error handler for socket open failure.
    ///
    /// This callback function is installed on the @c isc::dhcp::IfaceMgr
    /// when IPv4 sockets are being open. When socket fails to open for
    /// any reason, this function is called. It simply logs the error message.
    ///
    /// @param errmsg An error message containing a cause of the failure.
    static void ifaceMgrSocket4ErrorHandler(const std::string& errmsg);

    uint16_t port_;  ///< UDP port number on which server listens.
    bool use_bcast_; ///< Should broadcast be enabled on sockets (if true).

    /// Indexes for registered hook points
    int hook_index_pkt4_receive_;
    int hook_index_subnet4_select_;
    int hook_index_pkt4_send_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP4_SRV_H
