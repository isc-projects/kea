// Copyright (C) 2020-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option_int.h>
#include <dhcp/option_custom.h>
#include <dhcp/option4_addrlst.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <lease_query_log.h>
#include <lease_query_impl4.h>
#include <stats/stats_mgr.h>
#include <util/str.h>

#include <boost/pointer_cast.hpp>

#include <sstream>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::lease_query;
using namespace isc::log;
using namespace isc::stats;

namespace {

/// @brief Comparator for sorting v4 leases by descending CLTT.
bool cltt_descending(const Lease4Ptr& first, const Lease4Ptr& second) {
        return (first->cltt_ > second->cltt_);
}

} // end of anonymous namespace

LeaseQueryImpl4::LeaseQueryImpl4(const ConstElementPtr config)
    : LeaseQueryImpl(AF_INET, config) {
};

void
LeaseQueryImpl4::processQuery(PktPtr base_query) const {
    Pkt4Ptr query = boost::dynamic_pointer_cast<Pkt4>(base_query);
    if (!query) {
        // Shouldn't happen.
        isc_throw(BadValue, "LeaseQueryImpl4 query is not DHCPv4 packet");
    }

    /// - Validates query content
    IOAddress requester_ip = query->getGiaddr();
    if (requester_ip.isV4Zero())  {
        isc_throw(BadValue, "giaddr cannot be 0.0.0.0");
    }

    if (!isRequester(requester_ip)) {
        isc_throw(BadValue, "rejecting query from unauthorized requester: "
                  << requester_ip.toText());
    }

    OptionPtr client_server_id;
    if (!acceptServerId(query, client_server_id)) {
        isc_throw(BadValue, "rejecting query from: "
                  << requester_ip.toText() << ", unknown server-id: "
                  << (client_server_id ? client_server_id->toText() : "malformed"));
    }

    // Let's figure out which query type we have base on which attributes
    // the client sent.  The attributes are mutually exclusive so we'll
    // make a bit mask of which ones the query contains and go from there.
    IOAddress ciaddr = query->getCiaddr();
    uint8_t query_mask = (!ciaddr.isV4Zero() ? 1 : 0);

    HWAddrPtr hwaddr = query->getHWAddr();
    query_mask |= ((hwaddr->htype_ || hwaddr->hwaddr_.size()) ? 2 : 0);

    ClientIdPtr client_id;
    OptionPtr opt = query->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (opt) {
        client_id.reset(new ClientId(opt->getData()));
        query_mask += 4;
    }

    Lease4Collection leases;
    DHCPMessageType response_type;

    // Do the query based on which query attribute we have,
    // or error out.
    switch (query_mask) {
    case 1:
        // Query by ip address.
        response_type = queryByIpAddress(ciaddr, leases);
        break;
    case 2:
        // Query by HW address.
        response_type = queryByHWAddr(hwaddr, leases);
        break;
    case 4:
        // Query by client id.
        response_type = queryByClientId(client_id, leases);
        break;
    default:
        // We have some combination of the three which is invalid.
        isc_throw(BadValue, "malformed lease query: "
                  << "ciaddr: [" << ciaddr
                  << "] HWAddr: [" << hwaddr->toText()
                  << "] Client id: [" << (client_id ? client_id->toText() : "")
                  << "]");
    }

    Pkt4Ptr response = buildResponse(response_type, query, leases);
    /// Send the response if we have one
    if (response) {
        sendResponse(response);
    }
}

DHCPMessageType
LeaseQueryImpl4::queryByIpAddress(const IOAddress& ciaddr,
                                  Lease4Collection& leases) {
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(ciaddr);
    if (lease) {
        if (lease->state_ == Lease::STATE_DEFAULT && !lease->expired()) {
            // Found an active lease.
            leases.push_back(lease);
            return (DHCPLEASEACTIVE);
        }

        // We have a lease but it's not active.
        return (DHCPLEASEUNASSIGNED);
    }

    // We didn't find a lease, so we need to determine if it is a lease
    // we should know about.  We iterate over all subnets, in case the
    // address is inRange() of more than one subnet.
    const Subnet4Collection* subnets;
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    for (auto const& subnet : *subnets) {

        if (subnet->inPool(Lease::TYPE_V4, ciaddr)) {
            // Belongs to a pool in this subnet, but not leased.
            return (DHCPLEASEUNASSIGNED);
        }
    }

    // Not an address we know about.
    return (DHCPLEASEUNKNOWN);
}

DHCPMessageType
LeaseQueryImpl4::queryByClientId(const ClientIdPtr& client_id,
                                 Lease4Collection& leases) {
    leases = winnowLeases(LeaseMgrFactory::instance().getLease4(*client_id));
    return (!leases.empty() ?  DHCPLEASEACTIVE : DHCPLEASEUNKNOWN);
}

DHCPMessageType
LeaseQueryImpl4::queryByHWAddr(const HWAddrPtr& hwaddr,
                               Lease4Collection& leases) {
    leases = winnowLeases(LeaseMgrFactory::instance().getLease4(*hwaddr));
    return (!leases.empty() ?  DHCPLEASEACTIVE : DHCPLEASEUNKNOWN);
}

Lease4Collection
LeaseQueryImpl4::winnowLeases(const Lease4Collection& found_leases) {
    // We want only the active leases and we want them ordered
    // newest to oldest by CLTT.
    Lease4Collection active_leases;
    if (!found_leases.empty()) {
        for (auto const& lease : found_leases) {
            if (lease->state_ == Lease::STATE_DEFAULT && !lease->expired()) {
                active_leases.push_back(lease);
            }
        }

        std::sort(active_leases.begin(), active_leases.end(), cltt_descending);
     }

    return (active_leases);
}

Pkt4Ptr
LeaseQueryImpl4::buildResponse(DHCPMessageType response_type,
                               const Pkt4Ptr& query,
                               const Lease4Collection& leases) {
    // Create the basic response packet.
    Pkt4Ptr response = initResponse(response_type, query);

    switch(response_type) {
    case DHCPLEASEUNKNOWN:
    case DHCPLEASEUNASSIGNED: {
        // RFC 4388 is ambiguous on this issue, so for
        // negative queries we will always return the
        // query parameter. Only one which will have
        // a non-empty value.  This alleviates the requester
        // from having to try to match queries to
        // responses.
        response->setCiaddr(query->getCiaddr());
        response->setHWAddr(query->getHWAddr());
        OptionPtr opt = query->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
        if (opt) {
            response->addOption(opt);
        }

        // Add the server-id.
        CfgOptionList co_list;
        buildCfgOptionList(co_list, query);
        appendServerId(response, co_list);
        break;
    }

    case DHCPLEASEACTIVE: {
        if (leases.size() == 0) {
            isc_throw(Unexpected, "buildResponse - lease list is empty!");
        }

        // Get the newest active lease.
        const Lease4Ptr& newest = leases[0];

        // Set ciaddr and HW address from lease values.
        response->setCiaddr(newest->addr_);
        if (newest->hwaddr_) {
            response->setHWAddr(newest->hwaddr_);
        }

        // Add the active lease options.
        addOptions(query, response, newest);

        // Add the associated leases (if any).
        addAssociatedLeases(response, leases);
        break;
    }

    default:
        // Shouldn't happen.
        isc_throw(Unexpected, "invalid response type: " << response_type);
        break;
    }

    return (response);
}

Pkt4Ptr
LeaseQueryImpl4::initResponse(DHCPMessageType response_type, const Pkt4Ptr& query) {
    Pkt4Ptr response(new Pkt4(response_type, query->getTransid()));
    response->setGiaddr(query->getGiaddr());

    // Zero out the hwaddr type. Pkt4 constructor defaults it to HTYPE_ETHER.
    response->setHWAddr(HWAddrPtr(new HWAddr(std::vector<uint8_t>{}, 0)));

    // Set the destination to giaddr at the standard server port.
    response->setRemoteAddr(query->getGiaddr());
    response->setRemotePort(DHCP4_SERVER_PORT);

    HWAddrPtr dst_hw_addr = query->getRemoteHWAddr();
    if (dst_hw_addr) {
        response->setRemoteHWAddr(dst_hw_addr);
    }

    // Set the source accordingly.
    IOAddress local_addr = query->getLocalAddr();
    if (local_addr.isV4Bcast()) {
        local_addr = IfaceMgr::instance().getSocket(query).addr_;
    }

    response->setLocalAddr(local_addr);
    response->setLocalPort(query->getLocalPort());
    response->setIface(query->getIface());
    response->setIndex(query->getIndex());

    HWAddrPtr src_hw_addr = query->getLocalHWAddr();
    if (src_hw_addr) {
        response->setLocalHWAddr(src_hw_addr);
    }

    // If we got server id from the client add it.
    OptionPtr client_server_id = query->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    if (client_server_id) {
        response->addOption(client_server_id);
    }

    return (response);
}

void
LeaseQueryImpl4::addAssociatedLeases(Pkt4Ptr response, const Lease4Collection& leases) {
    Option4AddrLstPtr associates(new Option4AddrLst(DHO_ASSOCIATED_IP));
    int cnt = 0;
    for (auto const& lease : leases) {
        if (lease->addr_ != response->getCiaddr()) {
            associates->addAddress(lease->addr_);
            ++cnt;
        }
    }

    if (cnt) {
        response->addOption(associates);
    }
}

void
LeaseQueryImpl4::addOptions(const Pkt4Ptr& query, Pkt4Ptr response, const Lease4Ptr& lease) {
    // Per RFC 4388 all of the following options should be sent if the
    // client asks for them in the query's PRL option.  ISC DHCP always sends
    // them, so for now we will too.

    // Get the subnet for finding various options.
    Subnet4Ptr subnet = CfgMgr::instance().getCurrentCfg()
                        ->getCfgSubnets4()->getSubnet(lease->subnet_id_);
    if (!subnet) {
        isc_throw(Unexpected, "subnet_id: " << lease->subnet_id_ << " does not exist!");
    }

    // Add the client-id.
    if (lease->client_id_) {
        OptionPtr cid_opt(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                     lease->client_id_->getClientId()));
        response->addOption(cid_opt);
    }

    // Add lease life time, T1 and T2.
    addLeaseTimes(response, lease, subnet);

    // Add relay-agent-info (82) from the extended info in the lease's
    // user-context and add it to the response.
    addRelayAgentInfo(response, lease);

    // Add the server-id.
    CfgOptionList co_list;
    buildCfgOptionList(co_list, query);
    appendServerId(response, co_list);
}

void
LeaseQueryImpl4::addLeaseTimes(Pkt4Ptr response, const Lease4Ptr& lease,
                               const Subnet4Ptr& subnet) {
    time_t now = time(0);
    time_t elapsed;

    // How much time has elapsed since last client transmission?
    if (now > lease->cltt_) {
        elapsed = now - lease->cltt_;
    } else {
        // Something insane here so send back times unadjusted.
        elapsed = 0;
    }

    // Add the time elapsed CLTT (see RFC 4388 6.1)
    OptionPtr opt(new OptionUint32(Option::V4, DHO_CLIENT_LAST_TRANSACTION_TIME, elapsed));
    response->addOption(opt);

    // If the lifetime is infinite use as is, and skip sending T1/T2.
    if (lease->valid_lft_ == Lease::INFINITY_LFT) {
        opt.reset(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME,
                                   Lease::INFINITY_LFT));
        response->addOption(opt);
        return;
    }

    // Calculate the remaining life time.
    time_t adjusted_lft = lease->valid_lft_ - elapsed;

    // Add the adjusted lease time to the packet.
    opt.reset(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, adjusted_lft));
    response->addOption(opt);

    // Now figure out T1 and T2.  This logic is largely lifted from
    // Dhcpv4Srv::setTeeTimes(), it would be handy if there were
    // a way to share it.
    time_t t2_time = 0;
    // If T2 is explicitly configured we'll use try value.
    if (!subnet->getT2().unspecified()) {
        t2_time = subnet->getT2();
    } else if (subnet->getCalculateTeeTimes()) {
        // Calculating tee times is enabled, so calculated it.
        t2_time = static_cast<time_t>(round(subnet->getT2Percent()
                                      * (lease->valid_lft_)));
    }

    // Calculate remaining T2.
    t2_time -= elapsed;

    // Send the T2 candidate value only if it's sane: to be sane it must be less than
    // the valid life time.
    time_t timer_ceiling = adjusted_lft;
    if (t2_time > 0 && t2_time < timer_ceiling) {
        OptionUint32Ptr t2(new OptionUint32(Option::V4, DHO_DHCP_REBINDING_TIME, t2_time));
        response->addOption(t2);
        // When we send T2, timer ceiling for T1 becomes T2.
        timer_ceiling = t2_time;
    }

    time_t t1_time = 0;
    // If T1 is explicitly configured we'll use try value.
    if (!subnet->getT1().unspecified()) {
        t1_time = subnet->getT1();
    } else if (subnet->getCalculateTeeTimes()) {
        // Calculating tee times is enabled, so calculate it.
        t1_time = static_cast<time_t>(round(subnet->getT1Percent()
                                      * (lease->valid_lft_)));
    }

    // Calculate remaining T1.
    t1_time -= elapsed;

    // Send T1 if it's sane: If we sent T2, T1 must be less than that.  If not it must be
    // less than the valid life time.
    if (t1_time > 0 && t1_time < timer_ceiling) {
        OptionUint32Ptr t1(new OptionUint32(Option::V4, DHO_DHCP_RENEWAL_TIME, t1_time));
        response->addOption(t1);
    }
}

void
LeaseQueryImpl4::addRelayAgentInfo(Pkt4Ptr response, const Lease4Ptr& lease) {
    ConstElementPtr user_context;
    if (lease->getContext()) {
        user_context = UserContext::toElement(lease->getContext());
    }

    if (!user_context) {
        return;
    }

    ConstElementPtr extended_info = user_context->get("ISC");
    if (!extended_info) {
        return;
    }

    ConstElementPtr relay_agent_info = extended_info->get("relay-agent-info");
    if (!relay_agent_info) {
        return;
    }

    // In the new layout the relay-agent-info is a map and the RAI content
    // is in the sub-options entry of the map, in the old layout the
    // relay-agent-info is a string holding the RAI content.
    if (relay_agent_info->getType() == Element::map) {
        relay_agent_info = relay_agent_info->get("sub-options");
        if (!relay_agent_info) {
            return;
        }
    }

    try {
        std::vector<uint8_t> opt_data;
        util::str::decodeFormattedHexString(relay_agent_info->stringValue(), opt_data);

        OptionPtr rai;
        rai.reset(new Option(Option::V4, DHO_DHCP_AGENT_OPTIONS, opt_data));
        response->addOption(rai);
    } catch (const std::exception& ex) {
        isc_throw(Unexpected, "Error creating relay-agent-info option: " << ex.what());
    }
}

std::string
LeaseQueryImpl4::leaseQueryLabel(const Pkt4Ptr& packet) {
    std::stringstream label;

    try {
        label << "type: " << packet->getName()
              << ", giaddr: " << packet->getGiaddr().toText()
              << ", transid: " << packet->getTransid()
              << ", ciaddr: " << packet->getCiaddr().toText();

        HWAddrPtr hwaddr = packet->getHWAddr();
        label << ", hwaddr: " << (hwaddr ? hwaddr->toText() : "none");

        OptionPtr client_opt = packet->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
        if (!client_opt) {
            label << ", cid: none";
        } else {
            try {
                ClientId client_id(client_opt->getData());
                label << ", cid: " << client_id.toText();
            } catch (...) {
                label << ", cid: (malformed)";
            }
        }
    } catch (const std::exception& ex) {
        // Shouldn't happen. This just ensures we're exception safe.
        label << "label error" << ex.what();
    }

    return (label.str());
}

void
LeaseQueryImpl4::sendResponse(const Pkt4Ptr& response) {
    // Pack the response.
    try {
        response->pack();
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger, DHCP4_LEASE_QUERY_PACKET_PACK_FAILED)
                  .arg(leaseQueryLabel(response))
                  .arg(ex.what());
    }

    try {
        IfaceMgr::instance().send(response);
        LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC, DHCP4_LEASE_QUERY_RESPONSE_SENT)
                  .arg(leaseQueryLabel(response))
                  .arg(response->getRemoteAddr())
                  .arg(response->getRemotePort());

        StatsMgr::instance().addValue("pkt4-sent", static_cast<int64_t>(1));
        switch (response->getType()) {
        case DHCPLEASEUNKNOWN:
            StatsMgr::instance().addValue("pkt4-lease-query-response-unknown-sent",
                                          static_cast<int64_t>(1));
            break;
        case DHCPLEASEUNASSIGNED:
            StatsMgr::instance().addValue("pkt4-lease-query-response-unassigned-sent",
                                          static_cast<int64_t>(1));
            break;
        case DHCPLEASEACTIVE:
            StatsMgr::instance().addValue("pkt4-lease-query-response-active-sent",
                                          static_cast<int64_t>(1));
            break;
        default:
            // Shouldn't happen
            break;
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger, DHCP4_LEASE_QUERY_SEND_FAILED)
                  .arg(leaseQueryLabel(response))
                  .arg(response->getIface())
                  .arg(response->getRemoteAddr())
                  .arg(response->getRemotePort())
                  .arg(ex.what());
    }
}

bool
LeaseQueryImpl4::acceptServerId(const Pkt4Ptr& query, OptionPtr& server_id_opt) {
    // Regardless of the outcome we send back the client server-id.  It's only
    // meaningful to the caller when we return true.
    server_id_opt = query->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    if (!server_id_opt) {
        // Client did not specify a server id, accept the query.
        return (true);
    }

    // Server identifier is present. Let's convert it to 4-byte address
    // and try to match with server identifiers used by the server.
    OptionCustomPtr option_custom =
        boost::dynamic_pointer_cast<OptionCustom>(server_id_opt);
    // Unable to convert the option to the option type which encapsulates it.
    // We treat this as non-matching server id.
    if (!option_custom) {
        return (false);
    }
    // The server identifier option should carry exactly one IPv4 address.
    if (option_custom->getDataFieldsNum() != 1) {
        return (false);
    }

    // The server identifier MUST be an IPv4 address and not 0.0.0.0.
    IOAddress client_server_id = option_custom->readAddress();
    if (!client_server_id.isV4() ||
        (client_server_id == IOAddress::IPV4_ZERO_ADDRESS())) {
        return (false);
    }

    // If we're listening on the client's server_id
    // accept the query.
    if (IfaceMgr::instance().hasOpenSocket(client_server_id)) {
        return (true);
    }

    // Check if there are any subnets configured with
    // this server identifier.
    SrvConfigPtr cfg = CfgMgr::instance().getCurrentCfg();
    ConstCfgSubnets4Ptr cfg_subnets = cfg->getCfgSubnets4();
    if (cfg_subnets->hasSubnetWithServerId(client_server_id)) {
        return (true);
    }

    // This server identifier is not configured for any of the subnets, so
    // check on the shared network level.
    CfgSharedNetworks4Ptr cfg_networks = cfg->getCfgSharedNetworks4();
    if (cfg_networks->hasNetworkWithServerId(client_server_id)) {
        return (true);
    }

    // Check if the server identifier is configured at client class level.
    const ClientClasses& classes = query->getClasses();
    for (auto const& cclass : classes) {
        // Find the client class definition for this class
        const ClientClassDefPtr& ccdef = CfgMgr::instance().getCurrentCfg()->
            getClientClassDictionary()->findClass(cclass);
        if (!ccdef) {
            continue;
        }

        if (ccdef->getCfgOption()->empty()) {
            // Skip classes which don't configure options
            continue;
        }

        OptionCustomPtr context_opt_server_id = boost::dynamic_pointer_cast<OptionCustom>
                (ccdef->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_DHCP_SERVER_IDENTIFIER).option_);
        if (context_opt_server_id && (context_opt_server_id->readAddress() == client_server_id)) {
            return (true);
        }
    }

    // Finally, it is possible that the server identifier is specified
    // on the global level.
    OptionCustomPtr cfg_server_id = boost::dynamic_pointer_cast<OptionCustom>
        (cfg->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_DHCP_SERVER_IDENTIFIER).option_);

    return (cfg_server_id && (cfg_server_id->readAddress() == client_server_id));
}

void
LeaseQueryImpl4::appendServerId(Pkt4Ptr& response, CfgOptionList& co_list) {
    if (response->getOption(DHO_DHCP_SERVER_IDENTIFIER)) {
        // Already has it.
        return;
    }

    // If there's one in the configured options use it.
    for (auto const& cfg_options : co_list) {
        OptionDescriptor server_id_desc = cfg_options->get(DHCP4_OPTION_SPACE,
                                                          DHO_DHCP_SERVER_IDENTIFIER);
        if (server_id_desc.option_) {
            response->addOption(server_id_desc.option_);
            return;
        }
    }

    // Failing all of the above, let's infer one from the local address.
    const OptionDefinition& option_def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();
    OptionCustomPtr server_id(new OptionCustom(option_def, Option::V4));
    server_id->writeAddress(response->getLocalAddr());
    response->addOption(server_id);
}

void
LeaseQueryImpl4::buildCfgOptionList(CfgOptionList& co_list, const Pkt4Ptr& query,
                                    const Lease4Ptr& lease, const Subnet4Ptr& subnet) {
    // When lease is provided we're getting options for an active lease response.
    if (lease) {
        if (!subnet) {
            isc_throw (Unexpected, "buildCfgOptionList: subnet must be provided with lease");
        }

        /// @todo  We don't support host options (yet).  We Would have to look
        /// for reservations based on ip-address, mac, and or client-id.
        /// If we had class-list we skip HR lookup if for clients that
        /// are not KNOWN.
        /// host = find-host-somehow();
        /// if (host && !host->getCfgOption4()->empty()) {
        ///    co_list.push_back(host->getCfgOption4());

        // Add pool options.
        PoolPtr pool = subnet->getPool(Lease::TYPE_V4, lease->addr_, false);
        if (pool && !pool->getCfgOption()->empty()) {
            co_list.push_back(pool->getCfgOption());
        }

        // Add subnet options.
        if (!subnet->getCfgOption()->empty()) {
            co_list.push_back(subnet->getCfgOption());
        }

        // Next shared network options.
        SharedNetwork4Ptr network;
        subnet->getSharedNetwork(network);
        if (network && !network->getCfgOption()->empty()) {
            co_list.push_back(network->getCfgOption());
        }

        // Each class in the incoming packet
        const ClientClasses& classes = query->getClasses();
        for (auto const& cclass : classes) {
            // Find the client class definition for this class
            const ClientClassDefPtr& ccdef = CfgMgr::instance().getCurrentCfg()->
                getClientClassDictionary()->findClass(cclass);
            if (!ccdef) {
                // Skip it
                continue;
            }

            if (ccdef->getCfgOption()->empty()) {
                // Skip classes which don't configure options
                continue;
            }

            co_list.push_back(ccdef->getCfgOption());
        }
    }

    // Add global options
    if (!CfgMgr::instance().getCurrentCfg()->getCfgOption()->empty()) {
        co_list.push_back(CfgMgr::instance().getCurrentCfg()->getCfgOption());
    }
}

int
LeaseQueryImpl4::upgradeHandler(CalloutHandle& handle) {
    ConstElementPtr response;
    size_t upgraded = 0;
    LeasePageSize page_size(LeaseQueryImpl::PageSize);
    try {
        util::MultiThreadingCriticalSection cc;
        auto& lease_mgr = LeaseMgrFactory::instance();
        upgraded = lease_mgr.upgradeExtendedInfo4(page_size);
    } catch (const std::exception& ex) {
        // log here.
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        handle.setArgument("response", response);
        return (1);
    }

    // log here.
    std::ostringstream msg;
    msg << "Upgraded " << upgraded << " lease";
    if (upgraded != 1) {
        msg << "s";
    }
    response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str());
    handle.setArgument("response", response);
    return (0);
}
