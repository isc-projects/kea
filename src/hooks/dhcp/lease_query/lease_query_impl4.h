// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_QUERY_IMPL4_H
#define LEASE_QUERY_IMPL4_H

#include <config.h>

#include <dhcp/pkt4.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <lease_query_impl.h>

namespace isc {
namespace lease_query {

/// @brief Provides configuration and for processing DHCPv4 lease queries.
class LeaseQueryImpl4 : public LeaseQueryImpl {
public:
    /// @brief Constructor
    ///
    /// @param config input configuration
    LeaseQueryImpl4(const data::ConstElementPtr config);

    /// @brief Destructor
    virtual ~LeaseQueryImpl4(){};

    /// @brief Processes a single DHCPv4 client Lease Query
    ///
    /// - Validates query content
    /// - Determines is the query is permitted
    /// - Queries matching lease(s)
    /// - Constructs the reply
    /// - Sends the reply
    ///
    /// @param base_query DHCPv4 lease query to process.
    virtual void processQuery(dhcp::PktPtr base_query) const;

    /// @brief Queries for an active lease matching an ip address
    ///
    /// @param ciaddr ip address for which to search
    /// @param[out] leases a collection of leases containing the
    /// matching lease (if one)
    ///
    /// @return returns the message response type based on the
    /// query results:
    /// - DHCPLEASEACTIVE - if there is an active lease for the ip address
    /// - DHCPLEASEUNASSIGNED - if ip address is one the server knows about
    /// but for which there is no currently active lease
    /// - DHCPUNKNOWN - it the ip address is not one the server knows about
    static dhcp::DHCPMessageType queryByIpAddress(const asiolink::IOAddress& ciaddr,
                                                  dhcp::Lease4Collection& leases);

    /// @brief Queries LeaseMgr for active leases matching a client
    ///
    /// @param client_id client id for which to search
    /// @param[out] leases a collection of leases containing the
    /// matching leases (if one).  The newest (by CLTT) will be
    /// the first lease in the collection.
    ///
    /// @return returns the message response type based on the
    /// query results:
    /// - DHCPLEASEACTIVE - if there are one or more active leases for the
    /// client id.
    /// - DHCPUNKNOWN -  if there are no active leases for the client id
    static dhcp::DHCPMessageType queryByClientId(const dhcp::ClientIdPtr& client_id,
                                                 dhcp::Lease4Collection& leases);

    /// @brief Queries LeaseMgr for active leases matching a HW address
    ///
    /// @param hwaddr Hardware address for which to search
    /// @param[out] leases a collection of leases containing the
    /// matching leases (if one).  The newest (by CLTT) will be
    /// the first lease in the collection.
    ///
    /// @return returns the message response type based on the
    /// query results:
    /// - DHCPLEASEACTIVE - if there are one or more active leases for the
    /// hardware address
    /// - DHCPUNKNOWN -  if there are no active leases for the hardware address
    static dhcp::DHCPMessageType queryByHWAddr(const dhcp::HWAddrPtr& hwaddr,
                                               dhcp::Lease4Collection& leases);

    /// @brief Creates a list of active leases from a list of leases
    ///
    /// The new list will contain active leases ordered from newest to
    /// oldest by CLTT.
    ///
    /// @param leases input list of leases.
    /// @return Cleaned list of leases.
    static dhcp::Lease4Collection winnowLeases(const dhcp::Lease4Collection& leases);

    /// @brief Creates a lease query response packet
    ///
    /// Orchestrates the construction of a response to lease query
    /// based on the response_type and list of active leases.
    ///
    /// @param response_type Message type of the response
    /// @param query client lease query to which we are responding.
    /// @param leases list of active leases (if any).
    ///
    /// @return pointer the populated response
    static dhcp::Pkt4Ptr buildResponse(dhcp::DHCPMessageType response_type,
                                       const dhcp::Pkt4Ptr& query,
                                       const dhcp::Lease4Collection& leases);

    /// @brief Creates the initial query response
    ///
    /// Creates the response packet and populating basic
    /// response values based on query attributes.
    ///
    /// @param response_type Message type of the response
    /// @param query client lease query to which we are responding
    ///
    /// @return pointer to the newly constructed response packet
    static dhcp::Pkt4Ptr initResponse(dhcp::DHCPMessageType response_type,
                                      const dhcp::Pkt4Ptr& query);

    /// @brief Adds associated leases to a query response
    ///
    /// @param response query response to which to add
    /// @param leases list of active leases (if any)
    static void addAssociatedLeases(dhcp::Pkt4Ptr response,
                                    const dhcp::Lease4Collection& leases);

    /// @brief Adds options to a query response
    ///
    /// Adds the following options to the reponse (regardless of PRL):
    ///
    /// - DHO_DHCP_CLIENT_IDENTIFIER - if one
    /// - DHO_DHCP_LEASE_TIME
    /// - DHO_CLIENT_LAST_TRANSACTION_TIME
    /// - DHO_DHCP_REBINDING_TIME - if subnet configured to provide and value is sane
    /// - DHO_DHCP_RENEWAL_TIME - if subnet configured to provide and value is sane
    /// - DHO_DHCP_AGENT_OPTIONS - if one
    ///
    /// @param query used to get associated client classes
    /// @param response query response to which to add
    /// @param lease newest active lease.
    static void addOptions(const dhcp::Pkt4Ptr& query, dhcp::Pkt4Ptr response,
                           const dhcp::Lease4Ptr& lease);

    /// @brief Adds life time, T1, and T2 options to a query response
    ///
    /// @param response query response to which to add
    /// @param lease newest active lease.
    /// @param subnet lease's subnet
    static void addLeaseTimes(dhcp::Pkt4Ptr response, const dhcp::Lease4Ptr& lease,
                              const dhcp::Subnet4Ptr& subnet);

    /// @brief Adds relay-agent-info option to a query response
    ///
    /// @param response query response to which to add
    /// @param lease newest active lease
    static void addRelayAgentInfo(dhcp::Pkt4Ptr response, const dhcp::Lease4Ptr& lease);

    /// @brief Packs and sends a query response
    ///
    /// @param response query response to send
    static void sendResponse(const dhcp::Pkt4Ptr& response);

    /// @brief Convenience method for generating per packet logging info
    ///
    /// @param packet  DHCPv4 lease query packet (query or response)
    ///
    /// @return the query label.
    static std::string leaseQueryLabel(const dhcp::Pkt4Ptr& packet);

    /// @brief Validates dhcp-server-identifier option in the inbound query (if one)
    ///
    /// @param query client lease query which server identifier is to be checked.
    /// @param[out] server_id_opt copy of the dhcp-server-identifier in the query
    /// @return True if the query either contained no dhcp-server-identifier or it did
    /// and it matched a known server identifier; false otherwise.
    static bool acceptServerId(const dhcp::Pkt4Ptr& query,
                               dhcp::OptionPtr& server_id_opt);

    /// @brief Constructs a list of configured option sets for a given lease
    /// and it's subnet.
    ///
    /// When lease and subnet are not provided the list will only contain the
    /// set of globally configured options.  When they are provided the list
    /// will contain option sets in the following order:
    ///
    /// - @todo Reservation options  (when/if implemented)
    /// - Pool options
    /// - Subnet options
    /// - Shared-network options
    /// - @todo Class options        (when/if implemented)
    /// - Global options
    ///
    /// @note This list built by this function could be used to support
    /// fulfilling PRL options for active leases. Currently we only use
    /// it for dhcp-server-identifier.
    ///
    /// @param[out] co_list list to populate
    /// @param lease lease to use for matching options
    /// @param subnet to use for matching options
    /// @param query to get associated client classes
    /// @throw Unexpected if lease is provided but subnet is not.
    static void buildCfgOptionList(dhcp::CfgOptionList& co_list,
                                   const dhcp::Pkt4Ptr& query,
                                   const dhcp::Lease4Ptr& lease = dhcp::Lease4Ptr(),
                                   const dhcp::Subnet4Ptr& subnet = dhcp::Subnet4Ptr());

    /// @brief Adds dhcp-server-identifier option (54) to the response
    ///
    /// If the response packet does not already contain the option it, will
    /// be added either from a configured value in co_list (if one) or
    /// constructed from the response's local address.
    ///
    /// @param response packet to which the option should be added
    /// @param co_list List of configured option sets in which to search for the
    /// option.  The sets should be in the list in the order of precedence.
    static void appendServerId(dhcp::Pkt4Ptr& response, dhcp::CfgOptionList& co_list);

    /// @brief Upgrade extended information.
    ///
    /// Sanitize the extended information and fills relay and remoted IDs
    /// SQL new columns. Does nothing for the memfile backend.
    ///
    /// @param handle Callout handle used to retrieve a command and
    /// provide a response.
    static int upgradeHandler(hooks::CalloutHandle& handle);
};

/// @brief Defines a smart pointer to LeaseQueryImpl4 instance.
typedef boost::shared_ptr<LeaseQueryImpl4> LeaseQueryImpl4Ptr;

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // LEASE_QUERY_IMPL4_H
