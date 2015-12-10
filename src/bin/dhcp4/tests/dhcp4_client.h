// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCP4_CLIENT_H
#define DHCP4_CLIENT_H

#include <asiolink/io_address.h>
#include <dhcp/hwaddr.h>
#include <dhcp/pkt4.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <util/optional_value.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <set>

namespace isc {
namespace dhcp {
namespace test {

/// @brief General error emitted by the DHCP4 test client.
class Dhcp4ClientError : public isc::Exception {
public:
    Dhcp4ClientError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief DHCPv4 client used for unit testing.
///
/// This class implements a DHCPv4 "client" which interoperates with the
/// @c NakedDhcpv4Srv class. It calls @c NakedDhcpv4Srv::fakeReceive to
/// deliver client messages to the server for processing. The server places
/// the response in the @c NakedDhcpv4Srv::fake_sent_ container. The client
/// pops messages from this container which simulates reception of the
/// response from the server.
///
/// The client maintains the leases it acquired from the server.
///
/// The client exposes a set of functions which simulate different exchange
/// types between the client and the server. It also provides the access to
/// the objects encapsulating responses from the server so as it is possible
/// to verify from the unit test that the server's response is correct.
class Dhcp4Client : public boost::noncopyable {
public:

    /// @brief States of the DHCP client.
    enum State {
        SELECTING,
        INIT_REBOOT,
        RENEWING,
        REBINDING
    };

    /// @brief Holds the DHCPv4 messages taking part in transaction between
    /// the client and the server.
    struct Context {
        /// @brief Holds the last sent message from the client to the server.
        Pkt4Ptr query_;
        /// @brief Holds the last sent message by the server to the client.
        Pkt4Ptr response_;
    };

    /// @brief Holds the configuration of the client received from the
    /// DHCP server.
    struct Configuration {
        /// @brief Holds IP addresses received in the Routers option.
        Option4AddrLst::AddressContainer routers_;
        /// @brief Holds IP addresses received in the DNS Servers option.
        Option4AddrLst::AddressContainer dns_servers_;
        /// @brief Holds IP addresses received in the Log Servers option.
        Option4AddrLst::AddressContainer log_servers_;
        /// @brief Holds IP addresses received in the Quotes Servers option.
        Option4AddrLst::AddressContainer quotes_servers_;
        /// @brief Holds a lease obtained by the client.
        Lease4 lease_;
        /// @brief Holds server id of the server which responded to the client's
        /// request.
        asiolink::IOAddress serverid_;

        /// @brief Constructor.
        Configuration();

        /// @brief Sets configuration values to defaults.
        void reset();
    };

    /// @brief Creates a new client.
    ///
    /// @param Initial client's state.
    Dhcp4Client(const State& state = SELECTING);

    /// @brief Creates a new client that communicates with a specified server.
    ///
    /// @param srv An instance of the DHCPv4 server to be used.
    /// @param state Initial client's state.
    Dhcp4Client(boost::shared_ptr<NakedDhcpv4Srv> srv,
                const State& state = SELECTING);

    /// @brief Creates a lease for the client using the specified address
    /// and valid lifetime.
    ///
    /// This method creates the lease using the specified address and
    /// valid lease lifetime. The client will use this lease in any
    /// future communication with the DHCP server. One of the use cases
    /// for this method is to pre-configure the client with the explicitly
    /// given address before it sends the DHCPINFORM to the DHCP server.
    /// The client will inject the leased address into the ciaddr field
    /// of the DHCPINFORM message.
    ///
    /// @param addr Lease address.
    /// @param valid_lft Valid lifetime.
    void createLease(const asiolink::IOAddress& addr, const uint32_t valid_lft);

    /// @brief Sends DHCPDISCOVER message to the server and receives response.
    ///
    /// The message being sent to the server includes Parameter Request List
    /// option if any options to be requested have been specified using the
    /// @c requestOptions or @c requestOption methods.
    ///
    /// The configuration returned by the server in the DHCPOFFER message is
    /// NOT stored in the client configuration: @c config_.
    ///
    /// @param requested_addr A pointer to the IP Address to be sent in the
    /// Requested IP Address option or NULL if the option should not be
    /// included.
    void doDiscover(const boost::shared_ptr<asiolink::IOAddress>&
                    requested_addr = boost::shared_ptr<asiolink::IOAddress>());

    /// @brief Perform 4-way exchange with a server.
    ///
    /// This method calls @c doDiscover and @c doRequest to perform the 4-way
    /// exchange with the server.
    ///
    /// @param requested_addr A pointer to the address to be requested using the
    /// Requested IP Address option.
    void doDORA(const boost::shared_ptr<asiolink::IOAddress>&
                requested_addr = boost::shared_ptr<asiolink::IOAddress>());

    /// @brief Sends DHCPINFORM message to the server and receives response.
    ///
    /// This function simulates sending the DHCPINFORM message to the server
    /// and receiving server's response (if any). The server's response and the
    /// message sent to the server is stored in the context structure and can
    /// be accessed using @c getContext function.
    ///
    /// The configuration returned by the server is stored in the
    /// @c config_ public member and can be accessed directly.
    ///
    /// @param set_ciaddr Indicates if the ciaddr should be set for an
    /// outgoing message and defaults to true. Note, that the RFC2131 mandates
    /// setting the ciaddr for DHCPINFORM but the server may still want to
    /// respond if the ciaddr is not set.
    ///
    /// @throw This function doesn't thrown exceptions on its own, but it calls
    /// functions that are not exception safe, so it may emit an exception if
    /// an error occurs.
    void doInform(const bool set_ciaddr = true);

    /// @brief Sends DHCPRELEASE Message to the server.
    ///
    /// This method simulates sending the DHCPRELEASE message to the server.
    /// The released lease is removed from the client's configuration.
    void doRelease();


    /// @brief Sends DHCPDECLINE Message to the server.
    ///
    /// This method simulates sending the DHCPDECLINE message to the server.
    /// The released lease is removed from the client's configuration.
    void doDecline();

    /// @brief Sends DHCPREQUEST Message to the server and receives a response.
    ///
    /// This method simulates sending the DHCPREQUEST message to the server and
    /// receiving a response. The DHCPREQUEST message can be used by the client
    /// being in various states:
    /// - SELECTING - client is trying to obtain a new lease and it has selected
    /// the server using the DHCPDISCOVER.
    /// - INIT-REBOOT - client cached an address it was previously using and is
    /// now trying to verify if this address is still valid.
    /// - RENEW - client's renewal timer has passed and the client is trying to
    /// extend the lifetime of the lease.
    /// - REBIND - client's rebind timer has passed and the client is trying to
    /// extend the lifetime of the lease from any server.
    ///
    /// Depending on the state that the client is in, different combinations of
    /// - ciaddr
    /// - Requested IP Address option
    /// - server identifier
    /// are used (as per RFC2131, section 4.3.2). Therefore, the unit tests
    /// must set the appropriate state of the client prior to calling this
    /// method using the @c setState function.
    ///
    /// When the server returns the DHCPACK the configuration carried in the
    /// DHCPACK message is applied and can be obtained from the @c config_.
    void doRequest();

    /// @brief Generates a hardware address used by the client.
    ///
    /// It assigns random values to the bytes of the hardware address.
    ///
    /// @param htype hardware address type. Currently the only type
    /// supported is Ethernet hardware address.
    ///
    /// @return Pointer to the generated hardware address.
    HWAddrPtr generateHWAddr(const uint8_t htype = HTYPE_ETHER) const;

    /// @brief Returns HW address used by the client.
    HWAddrPtr getHWAddress() const {
        return (hwaddr_);
    }

    /// @brief Returns current context.
    const Context& getContext() const {
        return (context_);
    }

    /// @brief Returns the server that the client is communicating with.
    boost::shared_ptr<NakedDhcpv4Srv> getServer() const {
        return (srv_);
    }

    /// @brief Creates the client id from the client id in the textual format.
    ///
    /// The generated client id will be added to the client's messages to the
    /// server.
    ///
    /// @param clientid Client id in the textual format. Use the empty client id
    /// value to not include the client id.
    void includeClientId(const std::string& clientid);

    /// @brief Creates an instance of the Client FQDN option to be included
    /// in the client's message.
    ///
    /// @param flags Flags.
    /// @param fqdn_name Name in the textual format.
    /// @param fqdn_type Type of the name (fully qualified or partial).
    void includeFQDN(const uint8_t flags, const std::string& fqdn_name,
                     Option4ClientFqdn::DomainNameType fqdn_type);

    /// @brief Creates an instance of the Hostname option to be included
    /// in the client's message.
    ///
    /// @param name Name to be stored in the option.
    void includeHostname(const std::string& name);

    /// @brief Modifies the client's HW address (adds one to it).
    ///
    /// The HW address should be modified to test negative scenarios when the
    /// client acquires a lease and tries to renew it with a different HW
    /// address. The server should detect the HW address mismatch and react
    /// accordingly.
    ///
    /// The HW address modification affects the value returned by the
    /// @c Dhcp4Client::getHWAddress.
    void modifyHWAddr();

    /// @brief Specify an option to be requested by a client.
    ///
    /// This function adds option code to the collection of option
    /// codes to be requested by a client.
    ///
    /// @param option Option code to be requested. The value of 0 is
    /// ignored and the function is no-op.
    void requestOption(const uint8_t option);

    /// @brief Specifies options to be requested by the client.
    ///
    /// This function configures the client to request options having
    /// specified codes using Parameter Request List option. The default
    /// value of 0 specify that the option is not requested.
    ///
    /// If there are options specified to be requested before the function
    /// is called, the new option codes override previously specified ones.
    /// In order to clear the list of requested options call
    /// @c requestOptions(0).
    ///
    /// @param option1 First option to be requested.
    /// @param option2 Second option to be requested (optional).
    /// @param option3 Third option to be requested (optional).
    void requestOptions(const uint8_t option1,
                        const uint8_t option2 = 0,
                        const uint8_t option3 = 0);

    /// @brief Sets destination address for the messages being sent by the
    /// client.
    ///
    /// By default, the client uses broadcast address 255.255.255.255 to
    /// communicate with the server. In certain cases it may be desired
    /// that different address is used. This function sets the new address
    /// for all future exchanges with the server.
    ///
    /// @param dest_addr New destination address.
    void setDestAddress(const asiolink::IOAddress& dest_addr) {
        dest_addr_ = dest_addr;
    }

    /// @brief Sets the explicit hardware address for the client.
    ///
    /// @param hwaddr_str String representation of the HW address. Use an
    /// empty string to set the NULL hardware address.
    void setHWAddress(const std::string& hwaddr_str);

    /// @brief Sets the interface over which the messages should be sent.
    ///
    /// @param iface_name Name of the interface over which the messages should
    /// be sent.
    void setIfaceName(const std::string& iface_name) {
        iface_name_ = iface_name;
    }

    /// @brief Sets client state.
    ///
    /// Depending on the current state the client's behavior is different
    /// when sending Request messages as per RFC2131, section 4.3.2.
    ///
    /// @param state New client's state.
    void setState(const State& state) {
        state_ = state;
    }

    /// @brief Simulate sending messages through a relay.
    ///
    /// @param use Parameter which 'true' value indicates that client should
    /// simulate sending messages via relay.
    /// @param relay_addr Relay address
    /// @param sf_relay_addr Server facing relay address.
    void useRelay(const bool use = true,
                  const asiolink::IOAddress& relay_addr =
                  asiolink::IOAddress("192.0.2.2"),
                  const asiolink::IOAddress& sf_relay_addr =
                  asiolink::IOAddress("10.0.0.2")) {
        use_relay_ = use;
        relay_addr_ = relay_addr;
        server_facing_relay_addr_ = sf_relay_addr;
    }

    /// @brief Current client's configuration obtained from the server.
    Configuration config_;

    /// @brief Specific ciaddr to be used in client's messages.
    ///
    /// If this value is "unspecified" the default values will be used
    /// by the client. If this value is specified, it will override ciaddr
    /// in the client's messages.
    isc::util::OptionalValue<asiolink::IOAddress> ciaddr_;

    /// @brief Adds extra option (an option the client will always send)
    ///
    /// @param opt additional option to be sent
    void addExtraOption(const OptionPtr& opt);

private:
    /// @brief Appends extra options, previously added with addExtraOption()
    ///
    /// @brief Copies options from extra_options_ into outgoing message
    void appendExtraOptions();

    /// @brief Creates and adds Requested IP Address option to the client's
    /// query.
    ///
    /// @param addr Address to be added in the Requested IP Address option.
    void addRequestedAddress(const asiolink::IOAddress& addr);

    /// @brief Stores configuration received from the server.
    ///
    /// This methods stores the configuration obtained from the DHCP server
    /// in the @c Configuration structure. This configuration includes:
    /// - obtained lease
    /// - server id of the server that provided the configuration
    /// - lease
    /// - selected options (used by unit tests):
    ///   - DNS Servers
    ///   - Routers
    ///   - Log Servers
    ///   - Quotes Servers
    void applyConfiguration();

    /// @brief Creates client's side DHCP message.
    ///
    /// @param msg_type Type of the message to be created.
    /// @return An instance of the message created.
    Pkt4Ptr createMsg(const uint8_t msg_type);

    /// @brief Includes the Client Identifier option in the client's message.
    ///
    /// This function creates an instance of the Client Identifier option
    /// if the client identifier has been specified and includes this
    /// option in the client's message to the server.
    void appendClientId();

    /// @brief Includes the Server Identifier option in the client's message.
    ///
    /// This function creates an instance of the Server Identifier option.
    /// It uses whatever information is stored in config_.serverid_.
    void appendServerId();

    /// @brief Includes FQDN or Hostname option in the client's message.
    ///
    /// This method checks if @c fqdn_ or @c hostname_ is specified and
    /// includes it in the client's message. If both are specified, the
    /// @c fqdn_ will be used.
    void appendName();

    /// @brief Include PRL Option in the query message.
    ///
    /// This function creates the instance of the PRL (Parameter Request List)
    /// option and adds option codes from the @c requested_options_ to it.
    /// It later adds the PRL option to the @c context_.query_ message
    /// if it is non-NULL.
    void appendPRL();

    /// @brief Simulates reception of the message from the server.
    ///
    /// @return Received message.
    Pkt4Ptr receiveOneMsg();

    /// @brief Simulates sending a message to the server.
    ///
    /// This function instantly triggers processing of the message by the
    /// server. The server's response can be gathered by invoking the
    /// @c receiveOneMsg function.
    ///
    /// @param msg Message to be sent.
    void sendMsg(const Pkt4Ptr& msg);

    /// @brief Current context (sent and received message).
    Context context_;

    /// @biref Current transaction id (altered on each send).
    uint32_t curr_transid_;

    /// @brief Currently used destination address.
    asiolink::IOAddress dest_addr_;

    /// @brief FQDN requested by the client.
    Option4ClientFqdnPtr fqdn_;

    /// @brief Hostname requested by the client.
    OptionStringPtr hostname_;

    /// @brief Current hardware address of the client.
    HWAddrPtr hwaddr_;

    /// @brief Current client identifier.
    ClientIdPtr clientid_;

    /// @brief Interface to be used to send the messages.
    std::string iface_name_;

    /// @brief Relay address to use.
    asiolink::IOAddress relay_addr_;

    /// @brief Collection of options codes to be requested by the client.
    std::set<uint8_t> requested_options_;

    /// @brief Address of the relay interface connected to the server.
    asiolink::IOAddress server_facing_relay_addr_;

    /// @brief Pointer to the server that the client is communicating with.
    boost::shared_ptr<NakedDhcpv4Srv> srv_;

    /// @brief Current state of the client.
    State state_;

    /// @brief Enable relaying messages to the server.
    bool use_relay_;

    /// @brief Extra options the client will send.
    OptionCollection extra_options_;
};

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

#endif // DHCP4_CLIENT_H
