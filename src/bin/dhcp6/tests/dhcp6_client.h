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

#ifndef DHCP6_CLIENT_H
#define DHCP6_CLIENT_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <set>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

/// @brief DHCPv6 client used for unit testing.
///
/// This class implements a DHCPv6 "client" which interoperates with the
/// @c NakedDhcpv6Srv class. It calls @c NakedDhcpv6Srv::fakeRecive to
/// deliver client messages to the server for processing. The server places
/// the response in the @c NakedDhcpv6Srv::fake_sent_ container. The client
/// pops messages from this container which simulates reception of the
/// response from the server.
///
/// The client maintains the leases it acquired from the server. If it has
/// acquired the lease as a result of SARR exchange, it will use this lease
/// when the Rebind process is triggered by the unit test.
///
/// The client exposes a set of functions which simulate different exchange
/// types between the client and the server. It also provides the access to
/// the objects encapsulating responses from the server so as it is possible
/// to verify from the unit test that the server's response is correct.
///
/// @todo This class has been implemented to simplify the structure of the
/// unit test and to make unit tests code self-explanatory. Currently,
/// this class is mostly used by the unit tests which test Rebind processing
/// logic. At some point we may want to use this class to test some other
/// message types, e.g. Renew, in which case it may need to be extended.
/// Also, once we implement the support for multiple IAAddr and IAPrefix
/// options within single IA, the logic which maintains leases will have
/// to be extended to support it.
class Dhcp6Client : public boost::noncopyable {
public:

    /// @brief Holds an information about single lease.
    struct LeaseInfo {
        /// @brief A structure describing the lease.
        Lease6 lease_;

        /// @brief Holds the last status code that server has sent for
        /// the particular lease.
        uint16_t status_code_;

        /// @brief Default constructor for the structure.
        LeaseInfo() :
            lease_(), status_code_(0) { }
    };

    /// @brief Holds the current client configuration obtained from the
    /// server over DHCP.
    ///
    /// Currently it simply contains the collection of leases acquired
    /// and a list of options. Note: this is a simple copy of all
    /// non-IA options and often includes "protocol" options, like
    /// server-id and client-id.
    struct Configuration {
        /// @brief List of received leases
        std::vector<LeaseInfo> leases_;

        /// @brief List of received options
        OptionCollection options_;

        /// @brief Status code received in the global option scope.
        uint16_t status_code_;

        /// @brief Indicates if the status code has been received in the
        /// last transaction.
        bool received_status_code_;

        /// @brief Constructor.
        Configuration() {
            clear();
        }

        /// @brief Clears configuration.
        void clear() {
            leases_.clear();
            resetGlobalStatusCode();
        }

        /// @brief Clears global status code.
        ///
        /// This function should be called before the new message is received.
        void resetGlobalStatusCode() {
            status_code_ = 0;
            received_status_code_ = false;
        }

        /// @brief Finds an option with the specific code in the received
        /// configuration.
        ///
        /// @param code Option code.
        ///
        /// @return Pointer to the option if the option exists, or NULL if
        /// the option doesn't exist.
        OptionPtr findOption(const uint16_t code) const {
            std::multimap<unsigned int, OptionPtr>::const_iterator it = options_.find(code);
            if (it != options_.end()) {
                return (it->second);
            }
            return (OptionPtr());
        }
    };

    /// @brief Holds the DHCPv6 messages taking part in transaction between
    /// the client and the server.
    struct Context {
        /// @brief Holds the last sent message from the client to the server.
        Pkt6Ptr query_;
        /// @brief Holds the last sent message by the server to the client.
        Pkt6Ptr response_;
    };

    /// @brief Creates a new client.
    ///
    /// This constructor initializes the class members to default values:
    /// - relay link-addr = 3000:1::1
    /// - first transaction id = 0
    /// - dest-addr = All_DHCP_Relay_Agents_and_Servers
    /// - duid (LLT) = <random 4 bytes>00010203040506
    /// - link-local-addr = fe80::3a60:77ff:fed5:cdef
    /// - IA_NA not requested
    /// - IA_PD not requested
    /// - not relayed
    Dhcp6Client();

    /// @brief Creates a new client that communicates with a specified server.
    ///
    /// This constructor allows passing a pointer to the server object which
    /// should be used in a test. The server may be preconfigured before passed
    /// to the constructor. The default configuration used by the client is:
    /// - relay link-addr = 3000:1::1
    /// - first transaction id = 0
    /// - dest-addr = All_DHCP_Relay_Agents_and_Servers
    /// - duid (LLT) = <random 4 bytes>00010203040506
    /// - link-local-addr = fe80::3a60:77ff:fed5:cdef
    /// - IA_NA not requested
    /// - IA_PD not requested
    /// - not relayed
    ///
    /// @param srv Object representing server under test.
    Dhcp6Client(boost::shared_ptr<isc::test::NakedDhcpv6Srv>& srv);

    /// @brief Create lease for the client.
    ///
    /// This function creates new lease on the client side without contacting
    /// the server. This may be useful for the negative tests in which the
    /// client is supposed to send invalid addresses/prefixes to the server
    /// and expect certain responses.
    ///
    /// @param lease A lease to be applied for the client.
    void createLease(const Lease6& lease);

    /// @brief Performs a 4-way echange between the client and the server.
    ///
    /// If the 4-way exchange is successful, the client should acquire leases
    /// according to the server's current configuration and the type of leases
    /// that have been requested (IA_NA, IA_PD).
    ///
    /// The leases acquired are accessible through the @c config_ member.
    ///
    /// @throw This function doesn't throw exceptions on its own, but it calls
    /// functions that are not exception safe, so it may throw exceptions if
    /// error occurs.
    ///
    /// @todo Perform sanity checks on returned messages.
    void doSARR();

    /// @brief Send Solicit and receive Advertise.
    ///
    /// This function simulates the first transaction of the 4-way exchange,
    /// i.e. sends a Solicit to the server and receives Advertise. It doesn't
    /// set the lease configuration in the @c config_.
    ///
    /// @throw This function doesn't throw exceptions on its own, but it calls
    /// functions that are not exception safe, so it may throw exceptions if
    /// error occurs.
    ///
    /// @todo Perform sanity checks on returned messages.
    void doSolicit();

    /// @brief Sends a Renew to the server and receives the Reply.
    ///
    /// This function simulates sending the Renew message to the server and
    /// receiving server's response (if any). The client uses existing leases
    /// (either address or prefixes) and places them in the Renew message.
    /// If the server responds to the Renew (and extends the lease lifetimes)
    /// the current lease configuration is updated.
    ///
    /// @throw This function doesn't throw exceptions on its own, but it calls
    /// functions that are not exception safe, so it may throw exceptions if
    /// error occurs.
    ///
    /// @todo Perform sanity checks on returned messages.
    void doRenew();

    /// @brief Sends a Rebind to the server and receives the Reply.
    ///
    /// This function simulates sending the Rebind message to the server and
    /// receiving server's response (if any). The client uses existing leases
    /// (either address or prefixes) and places them in the Rebind message.
    /// If the server responds to the Rebind (and extends the lease lifetimes)
    /// the current lease configuration is updated.
    ///
    /// @throw This function doesn't throw exceptions on its own, but it calls
    /// functions that are not exception safe, so it may throw exceptions if
    /// error occurs.
    ///
    /// @todo Perform sanity checks on returned messages.
    void doRebind();

    /// @brief Sends Request to the server and receives Reply.
    ///
    /// This function simulates sending the Request message to the server and
    /// receiving server's response (if any). The client copies IA options
    /// from the current context (server's Advertise) to request acquisition
    /// of offered IAs. If the server responds to the Request (leases are
    /// acquired) the client's lease configuration is updated.
    ///
    /// @throw This function doesn't throw exceptions on its own, but it calls
    /// functions that are not exception safe, so it may throw exceptions if
    /// error occurs.
    ///
    /// @todo Perform sanity checks on returned messages.
    void doRequest();

    /// @brief Sends Confirm to the server and receives Reply.
    ///
    /// This function simulates sending the Confirm message to the server and
    /// receiving server's response (if any).
    void doConfirm();


    /// @brief Performs stateless (inf-request / reply) exchange.
    ///
    /// This function generates Information-request message, sends it
    /// to the server and then receives the reply. Contents of the Inf-Request
    /// are controlled by use_na_, use_pd_, use_client_id_ and use_oro_
    /// fields. This method does not process the response in any specific
    /// way, just stores it.
    void doInfRequest();

    /// @brief Removes the stateful configuration obtained from the server.
    ///
    /// It removes all leases held by the client.
    void clearConfig() {
        config_.clear();
    }

    /// @brief Simulates aging of leases by the specified number of seconds.
    ///
    /// This function moves back the time of acquired leases by the specified
    /// number of seconds. It is useful for checking whether the particular
    /// lease has been later updated (e.g. as a result of Rebind) as it is
    /// expected that the fresh lease has cltt set to "now" (not to the time
    /// in the past).
    void fastFwdTime(const uint32_t secs);

    /// @brief Returns DUID option used by the client.
    OptionPtr getClientId() const;

    /// @brief Returns current context.
    const Context& getContext() const {
        return (context_);
    }

    /// @brief Returns the collection of IAIDs held by the client.
    std::set<uint32_t> getIAIDs() const;

    /// @brief Returns lease at specified index.
    ///
    /// @warning This method doesn't check if the specified index is out of
    /// range. The caller is responsible for using a correct offset by
    /// invoking the @c getLeaseNum function.
    ///
    /// @param at Index of the lease held by the client.
    /// @return A lease at the specified index.
    Lease6 getLease(const size_t at) const {
        return (config_.leases_[at].lease_);
    }

    /// @brief Returns collection of leases for specified IAID.
    ///
    /// @param iaid IAID for which the leases should be returned.
    ///
    /// @return Vector containing leases for the IAID.
    std::vector<Lease6> getLeasesByIAID(const uint32_t iaid) const;

    /// @brief Returns the value of the global status code for the last
    /// transaction.
    uint16_t getStatusCode() const {
        return (config_.status_code_);
    }

    /// @brief Returns status code set by the server for the lease.
    ///
    /// @warning This method doesn't check if the specified index is out of
    /// range. The caller is responsible for using a correct offset by
    /// invoking the @c getLeaseNum function.
    ///
    /// @param at Index of the lease held by the client.
    /// @return A status code for the lease at the specified index.
    uint16_t getStatusCode(const size_t at) const {
        return (config_.leases_[at].status_code_);
    }

    /// @brief Returns number of acquired leases.
    size_t getLeaseNum() const {
        return (config_.leases_.size());
    }

    /// @brief Returns the server that the client is communicating with.
    boost::shared_ptr<isc::test::NakedDhcpv6Srv> getServer() const {
        return (srv_);
    }

    /// @brief Sets the client's DUID from a string value
    ///
    /// Replaces the client's DUID with one constructed from the given
    /// string.  The string is expected to contain hexadecimal digits with or
    /// without ":" separators.
    ///
    /// @param str The string of digits from which to create the DUID
    ///
    /// The DUID modification affects the value returned by the
    /// @c Dhcp6Client::getClientId
    void setDUID(const std::string& duid_str);

    /// @brief Modifies the client's DUID (adds one to it).
    ///
    /// The DUID should be modified to test negative scenarios when the client
    /// acquires a lease and tries to renew it with a different DUID. The server
    /// should detect the DUID mismatch and react accordingly.
    ///
    /// The DUID modification affects the value returned by the
    /// @c Dhcp6Client::getClientId
    void modifyDUID();

    /// @brief Checks if the global status code was received in the response
    /// from the server.
    ///
    /// @return true if the global status code option was received.
    bool receivedStatusCode() const {
        return (config_.received_status_code_);
    }

    /// @brief Sets destination address for the messages being sent by the
    /// client.
    ///
    /// By default, the client uses All_DHCP_Relay_Agents_and_Servers
    /// multicast address to communicate with the server. In certain cases
    /// it ay be desired that different address is used (e.g. unicast in Renew).
    /// This function sets the new address for all future exchanges with the
    /// server.
    ///
    /// @param dest_addr New destination address.
    void setDestAddress(const asiolink::IOAddress& dest_addr) {
        dest_addr_ = dest_addr;
    }

    /// @brief Sets the interface to be used by the client.
    ///
    /// @param iface_name Interface name.
    void setInterface(const std::string& iface_name) {
        iface_name_ = iface_name;
    }

    /// @brief Sets a prefix hint to be sent to a server.
    ///
    /// @param pref_lft Preferred lifetime.
    /// @param valid_lft Valid lifetime.
    /// @param len Prefix length.
    /// @param prefix Prefix for which the client has a preference.
    void useHint(const uint32_t pref_lft, const uint32_t valid_lft,
                 const uint8_t len, const std::string& prefix);

    /// @brief Place IA_NA options to request address assignment.
    ///
    /// This function configures the client to place IA_NA options in its
    /// Solicit messages to request the IPv6 address assignment.
    ///
    /// @param use Parameter which 'true' value indicates that client should
    /// request address assignment.
    void useNA(const bool use = true) {
        use_na_ = use;
    }

    /// @brief Place IA_PD options to request prefix assignment.
    ///
    /// This function configures the client to place IA_PD options in its
    /// Solicit messages to request the IPv6 address assignment.
    ///
    /// @param use Parameter which 'true' value indicates that client should
    /// request prefix assignment.
    void usePD(const bool use = true) {
        use_pd_ = use;
    }

    /// @brief Simulate sending messages through a relay.
    ///
    /// @param use Parameter which 'true' value indicates that client should
    /// simulate sending messages via relay.
    /// @param link_addr Relay link-addr.
    void useRelay(const bool use = true,
                  const asiolink::IOAddress& link_addr = asiolink::IOAddress("3000:1::1")) {
        use_relay_ = use;
        relay_link_addr_ = link_addr;
    }

    /// @brief Controls whether the client should send a client-id or not
    /// @param send should the client-id be sent?
    void useClientId(const bool send) {
        use_client_id_ = send;
    }

    /// @brief Specifies if the Rapid Commit option should be included in
    /// the Solicit message.
    ///
    /// @param rapid_commit Boolean parameter controlling if the Rapid Commit
    /// option must be included in the Solicit (if true), or not (if false).
    void useRapidCommit(const bool rapid_commit) {
        use_rapid_commit_ = rapid_commit;
    }

    /// @brief Creates an instance of the Client FQDN option to be included
    /// in the client's message.
    ///
    /// @param flags Flags.
    /// @param fqdn_name Name in the textual format.
    /// @param fqdn_type Type of the name (fully qualified or partial).
    void useFQDN(const uint8_t flags, const std::string& fqdn_name,
                 Option6ClientFqdn::DomainNameType fqdn_type);

    /// @brief Lease configuration obtained by the client.
    Configuration config_;

    /// @brief Link address of the relay to be used for relayed messages.
    asiolink::IOAddress relay_link_addr_;

    /// @brief RelayInfo (information about relays)
    ///
    /// Dhcp6Client will typically contruct this info itself, but if
    /// it is provided here by the test, this data will be used as is.
    std::vector<Pkt6::RelayInfo> relay_info_;

    /// @brief Controls whether the client will send ORO
    ///
    /// The actual content of the ORO is specified in oro_.
    /// It is useful to split the actual content and the ORO sending
    /// decision, so we could test cases of sending empty ORO.
    /// @param send controls whether ORO will be sent or not.
    void useORO(bool send) {
        use_oro_ = send;
    }

    /// @brief Instructs client to request specified option in ORO
    ///
    /// @param option_code client will request this option code
    void requestOption(uint16_t option_code) {
        use_oro_ = true;
        oro_.push_back(option_code);
    }

    /// @brief returns client-id
    /// @return client-id
    DuidPtr getDuid() const {
        return (duid_);
    }

private:

    /// @brief Applies the new leases for the client.
    ///
    /// This method is called when the client obtains a new configuration
    /// from the server in the Reply message. This function adds new leases
    /// or replaces existing ones, on the client's side. Client uses these
    /// leases in any later communication with the server when doing Renew
    /// or Rebind.
    ///
    /// @param reply Server response.
    ///
    /// @todo Currently this function supports one IAAddr or IAPrefix option
    /// within IA. We will need to extend it to support multiple options
    /// within a single IA once server supports that.
    void applyRcvdConfiguration(const Pkt6Ptr& reply);

    /// @brief Applies configuration for the single lease.
    ///
    /// This method is called by the @c Dhcp6Client::applyRcvdConfiguration for
    /// each individual lease.
    ///
    /// @param lease_info Structure holding new lease information.
    void applyLease(const LeaseInfo& lease_info);

    /// @brief Includes CLient FQDN in the client's message.
    ///
    /// This method checks if @c fqdn_ is specified and includes it in
    /// the client's message.
    void appendFQDN();

    /// @brief Copy IA options from one message to another.
    ///
    /// This method copies IA_NA and IA_PD options from one message to another.
    /// It is useful when the client needs to construct the Request message
    /// using addresses and prefixes returned by the client in Advertise.
    ///
    /// @param source Message from which IA options will be copied.
    /// @param dest Message to which IA options will be copied.
    ///
    /// @todo Add support for IA_TA.
    void copyIAs(const Pkt6Ptr& source, const Pkt6Ptr& dest);

    /// @brief Creates IA options from existing configuration.
    ///
    /// This method iterates over existing leases that client acquired and
    /// places corresponding IA_NA or IA_PD options into a specified message.
    /// This is useful to construct Renew, Rebind or Confirm message from the
    /// existing configuration that client has obtained using 4-way exchange.
    ///
    /// If there are no leases no IA options will be added. If the lease exists
    /// but any of the lifetime values is set to 0, the IA option will be added
    /// but the IAAddr (or IAPrefix) option will not be added.
    ///
    /// @param dest Message to which the IA options will be added.
    void copyIAsFromLeases(const Pkt6Ptr& dest) const;

    /// @brief Creates client's side DHCP message.
    ///
    /// @param msg_type Type of the message to be created.
    /// @return An instance of the message created.
    Pkt6Ptr createMsg(const uint8_t msg_type);

    /// @brief Generates DUID for the client.
    ///
    /// @param duid_type Type of the DUID. Currently, only LLT is accepted.
    /// @return Object encapsulating a DUID.
    DuidPtr generateDUID(DUID::DUIDType duid_type) const;

    /// @brief Simulates reception of the message from the server.
    ///
    /// @return Received message.
    Pkt6Ptr receiveOneMsg();

    /// @brief Simulates sending a message to the server.
    ///
    /// This function instantly triggers processing of the message by the
    /// server. The server's response can be gathered by invoking the
    /// @c receiveOneMsg function.
    ///
    /// @param msg Message to be sent.
    void sendMsg(const Pkt6Ptr& msg);

    /// @brief Current context (sent and received message).
    Context context_;

    /// @biref Current transaction id (altered on each send).
    uint32_t curr_transid_;

    /// @brief Currently used destination address.
    asiolink::IOAddress dest_addr_;

    /// @brief Currently used DUID.
    DuidPtr duid_;

    /// @brief Currently used link local address.
    asiolink::IOAddress link_local_;

    /// @brief Currently used interface.
    std::string iface_name_;

    /// @brief Pointer to the server that the client is communicating with.
    boost::shared_ptr<isc::test::NakedDhcpv6Srv> srv_;

    bool use_na_;    ///< Enable address assignment.
    bool use_pd_;    ///< Enable prefix delegation.
    bool use_relay_; ///< Enable relaying messages to the server.

    bool use_oro_;  ///< Conth
    bool use_client_id_;
    bool use_rapid_commit_;

    /// @brief Pointer to the option holding a prefix hint.
    Option6IAPrefixPtr prefix_hint_;

    /// @brief List of options to be requested
    ///
    /// Content of this vector will be sent as ORO if use_oro_ is set
    /// to true. See @ref sendORO for details.
    std::vector<uint16_t> oro_;

    /// @brief FQDN requested by the client.
    Option6ClientFqdnPtr fqdn_;
};

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

#endif // DHCP6_CLIENT
