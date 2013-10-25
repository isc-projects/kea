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
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/alloc_engine.h>
#include <hooks/callout_handle.h>

#include <boost/noncopyable.hpp>

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

    /// @brief Appends requested vendor options as requested by client.
    ///
    /// This method is similar to \ref appendRequestedOptions(), but uses
    /// vendor options. The major difference is that vendor-options use
    /// its own option spaces (there may be more than one distinct set of vendor
    /// options, each with unique vendor-id). Vendor options are requested
    /// using separate options within their respective vendor-option spaces.
    ///
    /// @param question DISCOVER or REQUEST message from a client.
    /// @param msg outgoing message (options will be added here)
    void appendRequestedVendorOptions(const Pkt4Ptr& question, Pkt4Ptr& answer);

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
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCP4_SRV_H
