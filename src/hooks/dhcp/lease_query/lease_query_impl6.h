// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_QUERY_IMPL6_H
#define LEASE_QUERY_IMPL6_H

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option_custom.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/cfgmgr.h>
#include <lease_query_impl.h>

namespace isc {
namespace lease_query {

/// @brief Defines a shared pointer to a Pkt6::RelayInfo.
typedef boost::shared_ptr<dhcp::Pkt6::RelayInfo> RelayInfoPtr;


/// @brief Defines an ordered list of prefix lengths.
typedef std::set<uint8_t> PrefixLengthList;

/// @brief Provides configuration and control flow for processing queries.
class LeaseQueryImpl6 : public LeaseQueryImpl {
public:
    /// @brief Constructor
    ///
    /// @param config input configuration
    LeaseQueryImpl6(const data::ConstElementPtr config);

    /// @brief Destructor
    virtual ~LeaseQueryImpl6(){};

    /// @brief Processes a single DHCPv6 client Lease Query.
    ///
    /// - Validates query content
    /// - Determines is the query is permitted
    /// - Queries matching lease(s)
    /// - Constructs the reply
    /// - Sends the reply
    ///
    /// @param base_query DHCPv6 lease query to process.
    /// @param invalid Reference to a flag set to true when the query
    /// is invalid (used to detect unexpected exceptions).
    /// @throw BadValue if the query is invalid for a number reasons,
    /// including if it comes from an unauthorized requester.
    virtual void processQuery(isc::dhcp::PktPtr base_query,
                              bool& invalid) const;

    /// @brief Queries for an active lease matching an ip address.
    ///
    /// The lease store is first searched for IA_NA lease for the given
    /// address.  If none are found and the list of prefix lengths is not empty,
    /// then the lease store is searched for IA_PD leases which match the given
    /// ip address masked with each prefix length.  The prefix lengths are tested
    /// in descending order.
    ///
    /// If no NA or PD leases are found, then the pools of each subnet are checked to
    /// to determine if the query address lies within them.
    ///
    /// @param iaaddr ip address for which to search
    /// @param[out] leases a collection of leases containing the
    /// matching lease (if one)
    /// @param prefix_lengths list of prefix lengths to use when searching
    /// for PD leases containing iaaddr.  The list is assumed to be in
    /// ascending order and is traversed in reverse.
    ///
    /// @return Status (code and text) to send back in the reply.
    static dhcp::Option6StatusCodePtr
    queryByIpAddress(const asiolink::IOAddress& iaaddr,
                     dhcp::Lease6Collection& leases,
                     const PrefixLengthList& prefix_lengths = PrefixLengthList());

    /// @brief Queries for active leases matching a client id (i.e. duid).
    ///
    /// Given a client DUID and a link address, this function will
    /// return a list of matching leases, sorted in descending order
    /// by CLTT (i.e. newest first).  A lease matches if it belongs to
    /// the client DUID, is active, and it belongs to the subnet whose
    /// range includes the link address if the link address specified
    /// is not ::.
    ///
    /// @param client_id client DUID for which to search.
    /// @param link_addr address of the link to search,
    /// @param[out] leases a collection of leases containing the
    /// matching leases (if any).
    ///
    /// @return Status (code and text) to send back in the reply.
    static dhcp::Option6StatusCodePtr
    queryByClientId(const dhcp::DuidPtr& client_id,
                    const asiolink::IOAddress& link_addr,
                    dhcp::Lease6Collection& leases);

    /// @brief Initial query for active leases matching a relay id (i.e. duid).
    ///
    /// Given a relay DUID and a link address, this function will return
    /// an initial list of matching leases, sorted by address.
    /// A lease matches if it was relayed by the given relay, is active,
    /// and it belongs to the subnet whose range includes the link address
    /// if the specified link address is not ::.
    ///
    /// @param relay_id relay DUID for which to search.
    /// @param[out] start_addr address to restart from.
    /// @param page_size maximum number of returned leases in this call.
    /// @param link_addr address of the link to search.
    /// @param[out] links set of subnet ids of the link to search.
    /// @param[out] leases a collection of leases containing the matching
    /// leases (if any).
    ///
    /// @return Status (code and text) to send back in the reply.
    static dhcp::Option6StatusCodePtr
    queryByRelayIdStart(const dhcp::DuidPtr& relay_id,
                        asiolink::IOAddress& start_addr,
                        const size_t page_size,
                        const asiolink::IOAddress& link_addr,
                        dhcp::SubnetIDSet& links,
                        dhcp::Lease6Collection& leases);

    /// @brief Subsequent query for active leases matching a relay id (i.e. duid).
    ///
    /// Given a relay DUID, a link and a start address, this function will
    /// return a partial list of matching leases, sorted by address.
    /// A lease matches if it was relayed by the given relay, is active,
    /// and it belongs to the subnet whose range includes the link address
    /// if the specified link address is not ::.
    /// The start address is used to note progress: if it is not updated
    /// there is no more leases to retrieve, otherwise the method should be
    /// called again with the updated value to retrieve remaining leases.
    ///
    /// @param relay_id relay DUID for which to search.
    /// @param page_size maximum number of returned leases in this call.
    /// @param[inout] start_addr address to start from.
    /// @param links set of subnet ids of the link to search.
    /// @param[out] leases a collection of leases containing the matching
    /// leases (if any).
    static void queryByRelayIdNext(const dhcp::DuidPtr& relay_id,
                                   asiolink::IOAddress& start_addr,
                                   const size_t page_size,
                                   const dhcp::SubnetIDSet& links,
                                   dhcp::Lease6Collection& leases);

    /// @brief Initial query for active leases matching a remote id.
    ///
    /// Given a remote id and a link address, this function will return
    /// an initial list of matching leases, sorted by address.
    /// A lease matches if it was relayed by the given relay, is active,
    /// and it belongs to the subnet whose range includes the link address
    /// if the specified link address is not ::.
    ///
    /// @param remote_id remote id for which to search.
    /// @param[out] start_addr address to restart from.
    /// @param page_size maximum number of returned leases in this call.
    /// @param link_addr address of the link to search.
    /// @param[out] links set of subnet ids of the link to search.
    /// @param[out] leases a collection of leases containing the matching
    /// leases (if any).
    ///
    /// @return Status (code and text) to send back in the reply.
    static dhcp::Option6StatusCodePtr
    queryByRemoteIdStart(const dhcp::OptionBuffer& remote_id,
                         asiolink::IOAddress& start_addr,
                         const size_t page_size,
                         const asiolink::IOAddress& link_addr,
                         dhcp::SubnetIDSet& links,
                         dhcp::Lease6Collection& leases);

    /// @brief Subsequent query for active leases matching a remote id.
    ///
    /// Given a remote id, a link and a start address, this function will
    /// return a partial list of matching leases, sorted by address.
    /// A lease matches if it was remoteed by the given relay, is active,
    /// and it belongs to the subnet whose range includes the link address
    /// if the specified link address is not ::.
    /// The start address is used to note progress: if it is not updated
    /// there is no more leases to retrieve, otherwise the method should be
    /// called again with the updated value to retrieve remaining leases.
    ///
    /// @param remote_id remote id for which to search.
    /// @param[inout] start_addr address to start from.
    /// @param page_size maximum number of returned leases in this call.
    /// @param links set of subnet ids of the link to search.
    /// @param[out] leases a collection of leases containing the matching
    /// leases (if any).
    static void queryByRemoteIdNext(const dhcp::OptionBuffer& remote_id,
                                    asiolink::IOAddress& start_addr,
                                    const size_t page_size,
                                    const dhcp::SubnetIDSet& links,
                                    dhcp::Lease6Collection& leases);

    /// @brief Initial query for active leases of a given link.
    ///
    /// Given a link address, this function will return an initial list of
    /// matching leases, sorted by address.
    /// A lease matches if it to the subnet whose range includes
    /// the link address.
    ///
    /// @param[out] start_addr address to restart from.
    /// @param page_size maximum number of returned leases in this call.
    /// @param link_addr address of the link to search.
    /// @param[out] links set of subnet ids of the link to search.
    /// @param[out] leases a collection of leases containing the matching
    /// leases (if any).
    ///
    /// @return Status (code and text) to send back in the reply.
    static dhcp::Option6StatusCodePtr
    queryByLinkStart(asiolink::IOAddress& start_addr,
                     const size_t page_size,
                     const asiolink::IOAddress& link_addr,
                     dhcp::SubnetIDSet& links,
                     dhcp::Lease6Collection& leases);

    /// @brief Subsequent query for active leases of a given link.
    ///
    /// Given a link address, this function will return an initial list of
    /// matching leases, sorted by address.
    /// A lease matches if it to the subnet whose range includes
    /// the link address.
    /// The start address is used to note progress: if it is not updated
    /// there is no more leases to retrieve, otherwise the method should be
    /// called again with the updated value to retrieve remaining leases.
    ///
    /// @param[inout] start_addr address to start from.
    /// @param page_size maximum number of returned leases in this call.
    /// @param links set of subnet ids of the link to search.
    /// @param[out] leases a collection of leases containing the matching
    /// leases (if any).
    static void queryByLinkNext(asiolink::IOAddress& start_addr,
                                const size_t page_size,
                                dhcp::SubnetIDSet& links,
                                dhcp::Lease6Collection& leases);

    /// @brief Creates a lease query reply packet.
    ///
    /// Orchestrates the construction of a reply to lease query
    /// based on the status code, client query, and the list of active leases
    /// (if any).
    ///
    /// @param status (code and text) to send back in the reply.
    /// @param query client lease query to which we are responding.
    /// @param leases list of active leases (if any).
    ///
    /// @return pointer the populated reply
    /// @throw Unexpected if status is empty
    static dhcp::Pkt6Ptr buildReply(const dhcp::Option6StatusCodePtr& status,
                                    const dhcp::Pkt6Ptr& query,
                                    dhcp::Lease6Collection& leases);

    /// @brief Creates the initial query reply.
    ///
    /// Creates the reply packet and populating basic
    /// reply values based on the client query.
    ///
    /// @param query client lease query to which we are responding
    ///
    /// @return pointer to the newly constructed reply packet
    /// @throw Unexpected if query does not contain a D6O_CLIENTID or
    /// if the server-id does not yet exist.
    static dhcp::Pkt6Ptr initReply(const dhcp::Pkt6Ptr& query);

    /// @brief Creates the query data response
    ///
    /// Creates a data packet.
    ///
    /// @param query client lease query to which we are responding
    ///
    /// @return pointer to the newly constructed data packet
    static dhcp::Pkt6Ptr initData(const dhcp::Pkt6Ptr& query);

    /// @brief Creates the final query done response.
    ///
    /// Creates the done packet.
    ///
    /// @param query client lease query to which we are responding
    ///
    /// @return pointer to the newly constructed done packet
    static dhcp::Pkt6Ptr initDone(const dhcp::Pkt6Ptr& query);

    /// @brief Constructs a client option based on a collection of leases
    ///
    /// Based on a collection of one or more active leases, sorted in
    /// descending order by CLTT (i.e. newest lease first), the function
    /// will either:
    ///
    /// Create a D6O_LQ_CLIENT_LINK option with a list of the link addresses
    /// (i.e. subnet prefixes) for each unique link, when the leases in the
    /// collection are from more than one subnet.
    ///
    //  or
    ///
    /// Create a D6O_CLIENT_DATA option with D6O_IAADDR and/or D6O_IAPREFIX
    /// options for each lease in the collection when those leases are all in
    /// the same subnet.  This option will also contain a D6O_CLIENT_ID and
    /// a D6O_CLT_TIME option whose values are taken from the first lease in
    /// the collection.  The valid and preferred lifetimes on each lease
    /// option will be reduced by the amount time elapsed since that lease's
    /// CLTT.
    ///
    /// @param leases list of active leases  (must contain at least one
    /// lease)
    ///
    /// @return Pointer to the newly created option
    /// @throw Unexpected if passed an empty lease collection or if
    /// there is no option definition for D6O_CLIENT_DATA.
    static dhcp::OptionPtr makeClientOption(dhcp::Lease6Collection& leases);

    /// @brief Constructs a client option based on a lease.
    ///
    /// Create a D6O_CLIENT_DATA option with D6O_IAADDR and/or D6O_IAPREFIX
    /// options for the lease. This option will also contain a D6O_CLIENT_ID
    /// and a D6O_CLT_TIME option. The valid and preferred lifetimes will
    /// be reduced by the amount time elapsed since CLTT.
    ///
    /// @param lease active lease
    ///
    /// @return Pointer to the newly created option
    /// @throw Unexpected if there is no option definition for D6O_CLIENT_DATA.
    static dhcp::OptionPtr makeClientOption(dhcp::Lease6Ptr lease);

    /// @brief Constructs a D6O_LQ_RELAY_DATA option from a lease user-context
    ///
    /// When kea-dhcp6 is configured with store-extended-info enabled and it
    /// assigns or renews a lease at the behest of a relayed client packet,
    /// it stores the the list of Pkt6::RelayInfos from that client packet
    /// into the lease's user-context.  If this function is passed a lease
    /// without this information it returns an empty OptionPtr.
    ///
    /// If not, it parses the user-context into a list of Pkt6::RelayInfo
    /// structures. It then creates a new D6O_LQ_RELAY_OPTION and populates
    /// it's peer address field from the first RelayInfo in the list.  It then
    /// uses the relay info list to construct a packed RELAY_FORW message
    /// into a buffer. This buffer is then added to the L6O_LQ_RELAY_OPTION
    /// as a D6O_RELAY_MSG option.
    ///
    /// If the relay information for a lease is malformed and cannot be
    /// extracted and parsed correctly, an warning will be logged and
    /// an empty pointer returned.  This allows a response to still be
    /// generated, albeit without the option.
    ///
    /// @param lease reference to the lease of interest
    ///
    /// @return A pointer to newly constructed option or an empty pointer
    /// @throw Unexpected if the lq-relay-data option definition is missing.
    static dhcp::OptionPtr makeRelayOption(const dhcp::Lease6& lease);

    /// @brief Calculates the packed size (in octets) of a given RelayInfo.
    ///
    /// This function was largely borrowed from Pkt6.
    ///
    /// @param relay relay whose size is desired
    /// @param innermost indicates whether or not this is the relay closest to
    /// the client.
    ///
    /// @return packed size of the relay.
    static uint16_t getRelayOverhead(const dhcp::Pkt6::RelayInfo& relay, bool innermost);

    /// @brief Converts an Element::list into a list of Pkt6::RelayInfo instances.
    ///
    /// @param relays an Element::list of relays
    /// @param[out] relay_infos a list into which to store the Pkt6::RelayInfo
    /// instances.
    ///
    /// @throw BadValue if the relay parameter is not an Element::list
    static void parseRelayInfoList(data::ConstElementPtr relays,
                                   std::vector<RelayInfoPtr>& relay_infos);

    /// @brief Converts an Element::map into an Pkt6::RelayInfo instance.
    ///
    /// @param relay an Element::map describing a relay
    ///
    /// @return Pointer to the newly constructed Pkt6::RelayInfo
    /// @throw BadValue if the relay parameter is empty or not an Element::map,
    /// or the map content is invalid for a number of other reasons.
    static RelayInfoPtr parseRelayInfo(data::ConstElementPtr relay);

    /// @brief Validates the server-id of a received DHCPV6_LEASEQUERY.
    ///
    /// If the inbound query contains a D6O_SERVERID option, it's value
    /// is checked against the global server-id value used by the kea-dhcp6
    /// server.  If it is malformed or does not match the function will
    /// throw.  Otherwise it will return.  If the query does not contain
    /// the option, it simply returns.
    ///
    /// @param query inbound DHCPV6_LEASEQUERY packet to check
    ///
    /// @throw BadValue if the query contained a malformed server-id or
    /// if the server-id does not match that of the kea-dhcp6 server.
    static void testServerId(const dhcp::Pkt6Ptr& query);

    /// @brief Constructs a D6O_STATUS_CODE option.
    ///
    /// @param status_code numeric status code
    /// @param message status text message
    ///
    /// @return Pointer to the newly create status option
    static dhcp::Option6StatusCodePtr makeStatusOption(const DHCPv6StatusCode&
                                                       status_code,
                                                       const std::string message = "");

    /// @brief Sends a response to the requester.
    ///
    /// Packs the given response packet and then submits it to IfaceMgr for
    /// transmission.
    ///
    /// @param response response packet to transmit
    void sendResponse(const dhcp::Pkt6Ptr& response) const;

    /// @brief Wrapper around the call to IfaceMgr::send().
    ///
    /// This function is virtual to facilitate unit testing.  It
    /// allows test derivations to intervene and examine outbound
    /// packets.
    ///
    /// @param response response packet to transmit
    virtual void send(const dhcp::Pkt6Ptr& response) const;

    /// @brief Convenience method for generating per packet logging info.
    ///
    /// @param packet DHCPv6 lease query packet (query or response)
    ///
    /// @return the query label.
    static std::string leaseQueryLabel(const dhcp::Pkt6Ptr& packet);

    /// @brief Upgrade extended information.
    ///
    /// Sanitize the extended information and (re)builds relay and remoted ID
    /// tables when enabled. Does nothing for the memfile backend.
    ///
    /// @param handle Callout handle used to retrieve a command and
    /// provide a response.
    static int upgradeHandler(hooks::CalloutHandle& handle);

    /// @brief Creates a prefix of a given length from an address.
    ///
    /// @param address IPv6 address to derive prefix from
    /// @param prefix_length length of the prefix desired
    ///
    /// @return the address with specified prefix length
    static asiolink::IOAddress getPrefixFromAddress(const asiolink::IOAddress& address,
                                                    const uint8_t prefix_length);

    /// @brief Add a prefix to the list of prefix lengths.
    ///
    /// @param prefix_len prefix length value to add. Value must be greater
    /// than 0 and less than or equal to 128.
    void addPrefixLength(uint8_t prefix_len) {
        if (prefix_len > 0 && prefix_len <= 128) {
            prefix_lens_.insert(prefix_len);
        }
    }

    /// @brief Empty the prefix length list.
    void clearPrefixLengthList() {
        prefix_lens_.clear();
    }

    /// @brief Fetch the prefix length list.
    ///
    /// @return the prefix length list.
    const PrefixLengthList& getPrefixLengthList() const {
        return (prefix_lens_);
    }

    /// @brief Populates the prefix length list from the given configuration.
    ///
    /// If the prefix length list has not been explicitly configured (i.e.
    /// build_prefix_lens_ is false), then the prefix length list is (re)populated
    /// from the PD pools in the given server configuration.
    ///
    /// @param cfg pointer the server configuration to use.
    void populatePrefixLengthList(dhcp::SrvConfigPtr cfg);

    /// @brief Dump the given list of prefix lengths to a string.
    ///
    /// The list is output in descending order to reflect the order in which it is used.
    ///
    /// @param prefix_lengths list to dump
    ///
    /// @return a string contain the prefix length list in JSON format.
    static std::string dumpPrefixLengthList(const PrefixLengthList& prefix_lengths);

    /// @brief List of PD prefix lengths to use when searching for leases by address.
    ///
    /// Assumed to be in ascending order by value.
    mutable PrefixLengthList prefix_lens_;

    /// @brief True if the prefix length should be gleaned from configured pools.
    ///
    /// This is false, if the last has been configure explicitly.
    bool build_prefix_lens_;
};

/// @brief Defines a smart pointer to LeaseQueryImpl6 instance.
typedef boost::shared_ptr<LeaseQueryImpl6> LeaseQueryImpl6Ptr;

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // LEASE_QUERY_IMPL6_H
