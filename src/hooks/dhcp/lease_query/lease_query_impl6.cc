// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/pkt6.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <lease_query_impl6.h>
#include <lease_query_log.h>
#include <blq_service.h>
#include <stats/stats_mgr.h>
#include <util/encode/encode.h>
#include <util/io.h>
#include <util/str.h>

#include <boost/range/adaptor/reversed.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include <set>

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

/// @brief Comparator for sorting v6 leases by descending CLTT.
bool cltt_descending(const Lease6Ptr& first, const Lease6Ptr& second) {
    return (first->cltt_ > second->cltt_);
}

}

LeaseQueryImpl6::LeaseQueryImpl6(const ConstElementPtr config)
    : LeaseQueryImpl(AF_INET6, config), prefix_lens_(), build_prefix_lens_(true) {
    auto blq_service = BulkLeaseQueryService::instance();
    if (blq_service) {
        CfgMgr::instance().getStagingCfg()->getCfgDbAccess()->
          setExtendedInfoTablesEnabled(blq_service->getExtendedInfoTablesEnabled());
    }

    ConstElementPtr prefix_lengths = config->get("prefix-lengths");
    if (!prefix_lengths) {
        return;
    }

    if (prefix_lengths->getType() != Element::list) {
        isc_throw(BadValue, "'prefix-lengths' is not a list");
    }

    // If it's specified, empty or otherwise, we don't build it dynamically.
    // An empty list "[]" means we don't do PD pool searching by IP address.
    build_prefix_lens_ = false;
    for (auto const& entry : prefix_lengths->listValue()) {
        try {
            if (entry->getType() != Element::integer) {
                isc_throw(BadValue, "must be an integer");
            }

            auto plen = entry->intValue();
            if (plen <= 0 || plen > 128) {
                isc_throw(BadValue, "must be greater than 0 and less than or equal to 128");
            }

            addPrefixLength(plen);
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "'prefix-lengths' entry '" << entry->str()
                      << "' is invalid: " << ex.what());
        }
    }
}

void
LeaseQueryImpl6::processQuery(PktPtr base_query, bool& invalid,
                              bool& sending) const {
    Pkt6Ptr query = boost::dynamic_pointer_cast<Pkt6>(base_query);
    if (!query) {
        // Shouldn't happen.
        isc_throw(BadValue, "LeaseQueryImpl6 query is not DHCPv6 packet");
    }

    // Ensure there is a client id
    DuidPtr req_clientid = query->getClientId();
    if (!req_clientid) {
        invalid = true;
        StatsMgr::instance().addValue("pkt6-rfc-violation",
                                      static_cast<int64_t>(1));
        isc_throw(BadValue, "DHCPV6_LEASEQUERY must supply a D6O_CLIENTID");
    }

    // If client sent a server-id, validate it.
    try {
        testServerId(query);
    } catch (const BadValue&) {
        invalid = true;
        // Drop statistic updated by testServerId.
        throw;
    }

    // Validates query content using the source address.
    IOAddress requester_ip = query->getRemoteAddr();
    if (requester_ip.isV6Zero())  {
        /// Not sure this really possible.
        invalid = true;
        StatsMgr::instance().addValue("pkt6-rfc-violation",
                                      static_cast<int64_t>(1));
        isc_throw(BadValue, "DHCPV6_LEASEQUERY source address cannot be ::");
    }

    if (!isRequester(requester_ip)) {
        // RFC 5007 says we may discard or return STATUS_NotAllowed
        invalid = true;
        StatsMgr::instance().addValue("pkt6-admin-filtered",
                                      static_cast<int64_t>(1));
        isc_throw(BadValue,
                 "rejecting DHCPV6_LEASEQUERY from unauthorized requester: "
                  << requester_ip.toText());
    }

    // Get the lease query option.
    OptionCustomPtr lq_option = boost::dynamic_pointer_cast<OptionCustom>
                                (query->getOption(D6O_LQ_QUERY));
    if (!lq_option) {
        invalid = true;
        StatsMgr::instance().addValue("pkt6-rfc-violation",
                                      static_cast<int64_t>(1));
        isc_throw(BadValue, "DHCPV6_LEASEQUERY must supply a D6O_LQ_QUERY option");
    }

    // Extract the type and link fields.
    uint8_t query_type;
    IOAddress query_link_addr(IOAddress::IPV6_ZERO_ADDRESS());
    try {
        query_type = lq_option->readInteger<uint8_t>(0);
        query_link_addr = lq_option->readAddress(1);
    } catch (const std::exception& ex) {
        // unpack() should catch this?
        invalid = true;
        StatsMgr::instance().addValue("pkt6-rfc-violation",
                                      static_cast<int64_t>(1));
        isc_throw(BadValue, "error reading query field(s):" << ex.what());
    }

    // Based on the query type, extract the requisite options and
    // perform the query.
    Lease6Collection leases;
    Option6StatusCodePtr status_opt;
    switch (query_type) {
    case LQ6QT_BY_ADDRESS: {
        Option6IAAddrPtr query_iaaddr = boost::dynamic_pointer_cast<Option6IAAddr>
                                        (lq_option->getOption(D6O_IAADDR));
        if (!query_iaaddr) {
            status_opt = makeStatusOption(STATUS_MalformedQuery, "missing D6O_IAADDR");
        } else {
            status_opt = queryByIpAddress(query_iaaddr->getAddress(), leases, prefix_lens_);
        }

        break;
    }

    case LQ6QT_BY_CLIENTID: {
        OptionPtr opt = lq_option->getOption(D6O_CLIENTID);
        if (!opt) {
            status_opt = makeStatusOption(STATUS_MalformedQuery, "missing D6O_CLIENTID");
            break;
        }

        DuidPtr query_client_id;
        try {
            query_client_id.reset(new DUID(opt->getData()));
        } catch (const std::exception& ex) {
            status_opt = makeStatusOption(STATUS_MalformedQuery, "malformed D6O_CLIENTID");
            break;
        }

        status_opt = queryByClientId(query_client_id, query_link_addr, leases);
        break;
        }

    default:
        status_opt = makeStatusOption(STATUS_UnknownQueryType, "unknown query-type");
        break;
    }

    // Construct the reply.
    sending = true;
    Pkt6Ptr reply = buildReply(status_opt, query, leases);
    if (reply) {
        sendResponse(reply);
    }
}

IOAddress
LeaseQueryImpl6::getPrefixFromAddress(const IOAddress& address, uint8_t prefix_length) {
    if (address.getFamily() != AF_INET6) {
        isc_throw(BadValue, "getPrefixFromAddress() - not a v6 address: " << address);
    }

    if (prefix_length == 0 || prefix_length > 128) {
        isc_throw(BadValue, "getPrefixFromAddress() - invalid prefix length:" << prefix_length);
    }

    // Get the address as bytes.
    auto address_bytes = address.toBytes();

    // Copy the whole bytes into the prefix first.
    auto keep_bytes = prefix_length / 8;
    std::vector<uint8_t> prefix_bytes(address_bytes.begin(), address_bytes.begin() + keep_bytes);

    // Mask on any remaining bits.
    auto keep_bits = prefix_length % 8;

    static uint8_t masks[] = { 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe };
    if (keep_bits) {
        prefix_bytes.push_back(address_bytes[keep_bytes] & masks[keep_bits - 1]);
    }

    // IOAddress::fromBytes() requires 16 bytes of data so pad it out with zeros.
    prefix_bytes.insert(prefix_bytes.end(), 16 - prefix_bytes.size(), 0);

    return (IOAddress::fromBytes(AF_INET6, prefix_bytes.data()));
}

Option6StatusCodePtr
LeaseQueryImpl6::queryByIpAddress(const IOAddress& iaaddr, Lease6Collection& leases,
                                  const PrefixLengthList& prefix_lengths) {
    // Database possible call: check if the hook was terminated.
    CHECK_TERMINATED;
    // Look for a lease for the given address.
    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, iaaddr);
    if (!lease && prefix_lengths.size()) {
        // Iterate over list of prefix-lengths in descending order.
        for (auto const& it : boost::adaptors::reverse(prefix_lengths)) {
            IOAddress prefix = getPrefixFromAddress(iaaddr, it);
            lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD, prefix);
            if (lease) {
                break;
            }
        }
    }

    if (lease) {
        if ((lease->state_ == Lease::STATE_DEFAULT) && (!lease->expired())) {
            // Found an active lease.
            leases.push_back(lease);
            return (makeStatusOption(STATUS_Success, "active lease found"));
        }

        // There's a lease but it isn't active.
        // Not real clear what should get returned in this case.
        return (makeStatusOption(STATUS_Success, "inactive lease exists"));
    }

    // We didn't find a lease, so we need to determine if it is a lease
    // we should know about.  We iterate over all subnets, in case the
    // address is inRange() of more than one subnet.
    const Subnet6Collection* subnets;
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    for (auto const& subnet : *subnets) {

        // Belongs to a pool in this subnet, but not leased.
        if ((subnet->inPool(Lease::TYPE_NA, iaaddr)) ||
            (subnet->inPool(Lease::TYPE_PD, iaaddr))) {
            return (makeStatusOption(STATUS_Success, "no active lease"));
        }
    }

    return (makeStatusOption(STATUS_NotConfigured, "address not in a configured pool"));
}

Option6StatusCodePtr
LeaseQueryImpl6::queryByClientId(const DuidPtr& client_id, const IOAddress& link_addr,
                                 Lease6Collection& leases) {
    // If the client specified a link to filter on, look up matching subnets.
    // We'll fetch the leases by client DUID and link filter them afterwards.
    SubnetIDSet links;
    if (!link_addr.isV6Zero()) {
        auto subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
        links = subnets->getLinks(link_addr);
        if (links.empty()) {
            return (makeStatusOption(STATUS_NotConfigured, "not a configured link"));
        }
    }

    // Database possible call: check if the hook was terminated.
    CHECK_TERMINATED;

    // Fetch all leases by client DUID.
    Lease6Collection found_leases = LeaseMgrFactory::instance().getLeases6(*client_id);

    // We want only the active leases.
    if (!found_leases.empty()) {
        for (auto const& lease : found_leases) {
            if (lease->state_ == Lease::STATE_DEFAULT && !lease->expired()) {
                // Filter by query links (if any).
                if (!links.empty() && !links.count(lease->subnet_id_)) {
                    continue;
                }

                // It's a match, keep it.
                leases.push_back(lease);
            }
        }
    }

    if (!leases.empty()) {
        // Sort the leases by descending value of CLTT (i.e. newest first)
        std::sort(leases.begin(), leases.end(), cltt_descending);
        return (makeStatusOption(STATUS_Success, "active lease(s) found"));
    }

    return (makeStatusOption(STATUS_Success, "no active leases"));
}

Option6StatusCodePtr
LeaseQueryImpl6::queryByRelayIdStart(const DuidPtr& relay_id,
                                     IOAddress& start_addr,
                                     const size_t page_size,
                                     const IOAddress& link_addr,
                                     SubnetIDSet& links,
                                     Lease6Collection& leases) {
    // If the client specified a link to filter on, look up matching subnets.
    links.clear();
    if (!link_addr.isV6Zero()) {
        auto subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
        links = subnets->getLinks(link_addr);
        if (links.empty()) {
            return (makeStatusOption(STATUS_NotConfigured, "not a configured link"));
        }
    }

    // Fetch an initial page of leases by relay DUID.
    start_addr = IOAddress::IPV6_ZERO_ADDRESS();
    Lease6Collection found_leases;
    for (;;) {
        // Database possible call: check if the hook was terminated.
        CHECK_TERMINATED;

        found_leases =
            LeaseMgrFactory::instance().getLeases6ByRelayId(*relay_id,
                                                            start_addr,
                                                            LeasePageSize(page_size));
        if (found_leases.empty()) {
            return (makeStatusOption(STATUS_Success, "no active leases"));
        }
        // Record the last address to restart from this point.
        start_addr = found_leases.back()->addr_;
        for (auto const& lease : found_leases) {
            if (lease->state_ == Lease::STATE_DEFAULT && !lease->expired()) {
                // Filter by query links (if any).
                if (!links.empty() && !links.count(lease->subnet_id_)) {
                    continue;
                }

                // It's a match, keep it.
                leases.push_back(lease);
            }
        }

        if (!leases.empty()) {
            return (makeStatusOption(STATUS_Success, "active lease(s) found"));
        }
    }
}

void
LeaseQueryImpl6::queryByRelayIdNext(const DuidPtr& relay_id,
                                    IOAddress& start_addr,
                                    const size_t page_size,
                                    const SubnetIDSet& links,
                                    Lease6Collection& leases) {
    // Database possible call: check if the hook was terminated.
    CHECK_TERMINATED;

    Lease6Collection found_leases =
        LeaseMgrFactory::instance().getLeases6ByRelayId(*relay_id,
                                                        start_addr,
                                                        LeasePageSize(page_size));
    if (found_leases.empty()) {
        return;
    }
    const IOAddress seen = start_addr;
    // Record the last address to restart from this point.
    start_addr = found_leases.back()->addr_;
    if (start_addr == seen) {
        return;
    }
    for (auto const& lease : found_leases) {
        if (lease->addr_ == seen) {
            continue;
        }
        if (lease->state_ == Lease::STATE_DEFAULT && !lease->expired()) {
            // Filter by query links (if any).
            if (!links.empty() && !links.count(lease->subnet_id_)) {
                    continue;
            }
        }

        // It's a match, keep it.
        leases.push_back(lease);
    }
}

Option6StatusCodePtr
LeaseQueryImpl6::queryByRemoteIdStart(const OptionBuffer& remote_id,
                                      IOAddress& start_addr,
                                      const size_t page_size,
                                      const IOAddress& link_addr,
                                      SubnetIDSet& links,
                                      Lease6Collection& leases) {
    // If the client specified a link to filter on, look up matching subnets.
    links.clear();
    if (!link_addr.isV6Zero()) {
        auto subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
        links = subnets->getLinks(link_addr);
        if (links.empty()) {
            return (makeStatusOption(STATUS_NotConfigured, "not a configured link"));
        }
    }

    // Fetch an initial page of leases by remote id.
    start_addr = IOAddress::IPV6_ZERO_ADDRESS();
    Lease6Collection found_leases;
    for (;;) {
        // Database possible call: check if the hook was terminated.
        CHECK_TERMINATED;

        found_leases =
            LeaseMgrFactory::instance().getLeases6ByRemoteId(remote_id,
                                                             start_addr,
                                                             LeasePageSize(page_size));
        if (found_leases.empty()) {
            return (makeStatusOption(STATUS_Success, "no active leases"));
        }
        // Record the last address to restart from this point.
        start_addr = found_leases.back()->addr_;
        for (auto const& lease : found_leases) {
            if (lease->state_ == Lease::STATE_DEFAULT && !lease->expired()) {
                // Filter by query links (if any).
                if (!links.empty() && !links.count(lease->subnet_id_)) {
                    continue;
                }

                // It's a match, keep it.
                leases.push_back(lease);
            }
        }

        if (!leases.empty()) {
            return (makeStatusOption(STATUS_Success, "active lease(s) found"));
        }
    }
}

void
LeaseQueryImpl6::queryByRemoteIdNext(const OptionBuffer& remote_id,
                                     IOAddress& start_addr,
                                     const size_t page_size,
                                     const SubnetIDSet& links,
                                     Lease6Collection& leases) {
    // Database possible call: check if the hook was terminated.
    CHECK_TERMINATED;

    Lease6Collection found_leases =
        LeaseMgrFactory::instance().getLeases6ByRemoteId(remote_id,
                                                         start_addr,
                                                         LeasePageSize(page_size));
    if (found_leases.empty()) {
        return;
    }
    const IOAddress seen = start_addr;
    // Record the last address to restart from this point.
    start_addr = found_leases.back()->addr_;
    if (start_addr == seen) {
        return;
    }
    for (auto const& lease : found_leases) {
        if (lease->addr_ == seen) {
            continue;
        }
        if (lease->state_ == Lease::STATE_DEFAULT && !lease->expired()) {
            // Filter by query links (if any).
            if (!links.empty() && !links.count(lease->subnet_id_)) {
                continue;
            }
        }

        // It's a match, keep it.
        leases.push_back(lease);
    }
}

Option6StatusCodePtr
LeaseQueryImpl6::queryByLinkStart(IOAddress& start_addr,
                                  const size_t page_size,
                                  const IOAddress& link_addr,
                                  SubnetIDSet& links,
                                  Lease6Collection& leases) {
    // The link is required.
    if (link_addr.isV6Zero()) {
        return (makeStatusOption(STATUS_MalformedQuery, "link address is ::"));
    }
    links.clear();
    auto subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    links = subnets->getLinks(link_addr);
    if (links.empty()) {
        return (makeStatusOption(STATUS_NotConfigured, "not a configured link"));
    }

    Lease6Collection found_leases;
    // Iterate over subnets.
    for (;;) {
        // Try first subnet.
        auto it = links.begin();
        if (it == links.end()) {
            // No subnet: done.
            return (makeStatusOption(STATUS_Success, "no active leases"));
        }
        // Fetch an initial page of leases on the subnet.
        start_addr = IOAddress::IPV6_ZERO_ADDRESS();
        for (;;) {
            // Database possible call: check if the hook was terminated.
            CHECK_TERMINATED;

            found_leases =
                LeaseMgrFactory::instance().getLeases6(*it, start_addr,
                                                       LeasePageSize(page_size));
            if (found_leases.empty()) {
                // Remove the current subnet and try the next one.
                links.erase(it);
                start_addr = IOAddress::IPV6_ZERO_ADDRESS();
                break;
            }

            // Record the last address to restart from this point.
            start_addr = found_leases.back()->addr_;
            for (auto const& lease : found_leases) {
                if (lease->state_ == Lease::STATE_DEFAULT &&
                    !lease->expired()) {
                    // It's a match, keep it.
                    leases.push_back(lease);
                }
            }
            if (!leases.empty()) {
                return (makeStatusOption(STATUS_Success, "active lease(s) found"));
            }
        }
    }
}

void
LeaseQueryImpl6::queryByLinkNext(IOAddress& start_addr,
                                 const size_t page_size,
                                 SubnetIDSet& links,
                                 Lease6Collection& leases) {

    Lease6Collection found_leases;
    // Iterate over subnets.
    for (;;) {
        // Try first subnet.
        auto it = links.begin();
        if (it == links.end()) {
            // No subnet: done.
            return;
        }
        // Fetch next page of leases on the subnet.
        for (;;) {
            // Database possible call: check if the hook was terminated.
            CHECK_TERMINATED;

            found_leases =
                LeaseMgrFactory::instance().getLeases6(*it, start_addr,
                                                       LeasePageSize(page_size));
            if (found_leases.empty()) {
                // Remove the current subnet and try the next one.
                links.erase(it);
                start_addr = IOAddress::IPV6_ZERO_ADDRESS();
                break;
            }

            const IOAddress seen = start_addr;
            // Record the last address to restart from this point.
            start_addr = found_leases.back()->addr_;
            if (start_addr == seen) {
                return;
            }
            for (auto const& lease : found_leases) {
                if (lease->addr_ == seen) {
                    continue;
                }
                if (lease->state_ == Lease::STATE_DEFAULT &&
                    !lease->expired()) {
                    // It's a match, keep it.
                    leases.push_back(lease);
                }
            }
            if (!leases.empty()) {
                return;
            }
        }
    }
}

Pkt6Ptr
LeaseQueryImpl6::buildReply(const Option6StatusCodePtr& status,
                            const Pkt6Ptr& query,
                            Lease6Collection& leases) {
    if (!status) {
        // Shouldn't happen.
        isc_throw(Unexpected, "status option cannot be empty");
    }

    Pkt6Ptr reply;
    switch (status->getStatusCode()) {
        case STATUS_Success: {
            // Create the reply.
            reply = initReply(query);

            // If we found leases add the client and/or relay-data options.
            if (!leases.empty()) {
                // Add the client option.
                OptionPtr client_opt = makeClientOption(leases);
                reply->addOption(client_opt);

                // If we are returning leases (not links), make the
                // relay option from the extended-store (if any) of
                // the newest lease.
                if (client_opt->getType() != D6O_LQ_CLIENT_LINK) {
                    OptionPtr opt = makeRelayOption(*(*leases.begin()));
                    if (opt) {
                        reply->addOption(opt);
                    }
                }
            }

            /// @todo RFC 5007 allows clients to request options via an
            /// for D6O_ORO option. We do not currently support that.

            // RFC 5007 says you may return a status of success.
            // ISC DHCP does not.
            reply->addOption(status);
            break;
        }

        case STATUS_UnknownQueryType:
        case STATUS_MalformedQuery:
        case STATUS_NotConfigured:
        case STATUS_NotAllowed: {
            // Query could not be performed or was for an address
            // we do not know about. We send back only the status.
            reply = initReply(query);
            reply->addOption(status);
            break;
        }

        default:
            // No meaningful reply can be sent.
            break;
    }

    return (reply);
}

Pkt6Ptr
LeaseQueryImpl6::initReply(const Pkt6Ptr& query) {
    Pkt6Ptr reply;

    reply.reset(new Pkt6(DHCPV6_LEASEQUERY_REPLY, query->getTransid()));
    reply->setRemoteAddr(query->getRemoteAddr());
    reply->setRemotePort(query->getRemotePort());
    reply->setLocalAddr(query->getLocalAddr());
    reply->setLocalPort(query->getLocalPort());
    reply->setIface(query->getIface());
    reply->setIndex(query->getIndex());

    DuidPtr duid = query->getClientId();
    if (!duid) {
        isc_throw(Unexpected, "query has no D6O_CLIENTID");
    }

    OptionPtr opt(new Option(Option::V6, D6O_CLIENTID, duid->getDuid()));
    reply->addOption(opt);

    DuidPtr server_id = CfgMgr::instance().getCurrentCfg()
                        ->getCfgDUID()->getCurrentDuid();
    if (!server_id) {
        isc_throw(Unexpected, "server_id does not exist");
    }

    opt.reset(new Option(Option::V6, D6O_SERVERID, server_id->getDuid()));
    reply->addOption(opt);
    return (reply);
}

Pkt6Ptr
LeaseQueryImpl6::initData(const Pkt6Ptr& query) {
    Pkt6Ptr response;

    response.reset(new Pkt6(DHCPV6_LEASEQUERY_DATA, query->getTransid()));
    response->setRemoteAddr(query->getRemoteAddr());
    response->setRemotePort(query->getRemotePort());
    return (response);
}

Pkt6Ptr
LeaseQueryImpl6::initDone(const Pkt6Ptr& query) {
    Pkt6Ptr done;

    done.reset(new Pkt6(DHCPV6_LEASEQUERY_DONE, query->getTransid()));
    done->setRemoteAddr(query->getRemoteAddr());
    done->setRemotePort(query->getRemotePort());
    return (done);
}

OptionPtr
LeaseQueryImpl6::makeClientOption(Lease6Collection& leases) {
    if (leases.empty()) {
        isc_throw(Unexpected, "makeClientOption: leases list is empty");
    }

    // Querying by client-id may find leases on multiple links.
    // We need to detect that case so we can return a D6O_LQ_CLIENT_LINK
    // option.
    // Iterate over leases and build a list of unique subnet ids.
    SubnetIDSet links;
    for (auto const& lease : leases) {
        if (lease->subnet_id_) {
            // The use of a set will remove duplicates.
            static_cast<void>(links.insert(lease->subnet_id_));
        }
    }

    if (links.size() > 1) {
        CfgSubnets6Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
        Option6AddrLst::AddressContainer addrs;
        for (auto const& link : links) {
            ConstSubnet6Ptr subnet = subnets->getBySubnetId(link);
            std::pair<isc::asiolink::IOAddress, uint8_t> pair = subnet->get();
            addrs.push_back(pair.first);
        }

        Option6AddrLstPtr opt(new Option6AddrLst(D6O_LQ_CLIENT_LINK, addrs));
        return (opt);
    }

    const OptionDefinition& def = LibDHCP::D6O_CLIENT_DATA_DEF();
    OptionCustomPtr cd_option(new OptionCustom(def, Option::V6));

    // Get the client id and CLTT from the first lease.
    const Lease6& first_lease = *(*leases.begin());
    OptionPtr opt(new Option(Option::V6, D6O_CLIENTID, first_lease.duid_->getDuid()));
    cd_option->addOption(opt);

    // How much time has elapsed since last client transmission?
    time_t now = time(0);
    time_t elapsed;
    if (first_lease.cltt_ < now) {
        elapsed = now - first_lease.cltt_;
    } else {
        // Something insane here so send back times unadjusted.
        elapsed = 0;
    }

    // Add CLTT option based on the newest lease.
    opt.reset(new OptionUint32(Option::V6, D6O_CLT_TIME, elapsed));
    cd_option->addOption(opt);

    // Iterate over the leases adding the appropriate option
    // for each one.
    for (auto const& lease : leases) {
        if (lease->cltt_ < now) {
            elapsed = now - lease->cltt_;
        } else {
            // Something insane here so send back times unadjusted.
            elapsed = 0;
        }

        // Calculate the remaining lifetimes.
        uint32_t preferred = lease->preferred_lft_;
        if (elapsed < preferred) {
            preferred -= elapsed;
        }

        uint32_t valid = lease->valid_lft_;
        if (elapsed < valid) {
            valid -= elapsed;
        }

        // Create the option.
        OptionPtr lease_opt;
        if (lease->type_ == Lease::TYPE_NA) {
            lease_opt.reset(new Option6IAAddr(D6O_IAADDR, lease->addr_,
                                              preferred, valid));
        } else {
            lease_opt.reset(new Option6IAPrefix(D6O_IAPREFIX,
                                                lease->addr_, lease->prefixlen_,
                                                preferred, valid));
        }

        cd_option->addOption(lease_opt);
    }

    return (cd_option);
}

OptionPtr
LeaseQueryImpl6::makeClientOption(Lease6Ptr lease) {
    const OptionDefinition& def = LibDHCP::D6O_CLIENT_DATA_DEF();
    OptionCustomPtr cd_option(new OptionCustom(def, Option::V6));

    // Get the client id and CLTT.
    OptionPtr opt(new Option(Option::V6, D6O_CLIENTID, lease->duid_->getDuid()));
    cd_option->addOption(opt);

    // How much time has elapsed since last client transmission?
    time_t now = time(0);
    time_t elapsed;
    if (lease->cltt_ < now) {
        elapsed = now - lease->cltt_;
    } else {
        // Something insane here so send back times unadjusted.
        elapsed = 0;
    }

    // Add CLTT option.
    opt.reset(new OptionUint32(Option::V6, D6O_CLT_TIME, elapsed));
    cd_option->addOption(opt);

    // Calculate the remaining lifetimes.
    uint32_t preferred = lease->preferred_lft_;
    if (elapsed < preferred) {
        preferred -= elapsed;
    }

    uint32_t valid = lease->valid_lft_;
    if (elapsed < valid) {
        valid -= elapsed;
    }

    // Create the resource option.
    OptionPtr lease_opt;
    if (lease->type_ == Lease::TYPE_NA) {
        lease_opt.reset(new Option6IAAddr(D6O_IAADDR, lease->addr_,
                                          preferred, valid));
    } else {
        lease_opt.reset(new Option6IAPrefix(D6O_IAPREFIX,
                                            lease->addr_, lease->prefixlen_,
                                            preferred, valid));
    }
    cd_option->addOption(lease_opt);

    // Add relay info.
    OptionPtr relay_opt = makeRelayOption(*lease);
    if (relay_opt) {
        cd_option->addOption(relay_opt);
    }

    return (cd_option);
}

OptionPtr
LeaseQueryImpl6::makeRelayOption(const Lease6& lease) {
    ConstElementPtr user_context;
    std::vector<RelayInfoPtr> relay_infos;

    try {
        if (lease.getContext()) {
            user_context = UserContext::toElement(lease.getContext());
        }

        if (!user_context) {
            return (OptionPtr());
        }

        ConstElementPtr extended_info = user_context->get("ISC");
        if (!extended_info) {
            return (OptionPtr());
        }

        // New layout puts the extended info in the relay-info entry.
        ConstElementPtr relay_info = extended_info->get("relay-info");
        if (!relay_info) {
            // Old layout uses the relays entry.
            relay_info = extended_info->get("relays");
        }
        if (!relay_info) {
            return (OptionPtr());
        }

        // Parse the relay element list into Pkt6::RelayInfo instances.
        parseRelayInfoList(relay_info, relay_infos);
        if (relay_infos.empty()) {
            // If we have an empty list, that's actually wrong, it should not
            // have been stored in the first place.
            isc_throw(Unexpected, "relay info list should not be empty");
        }
    } catch (const std::exception& ex) {
        LOG_WARN(lease_query_logger, DHCP6_LEASE_QUERY_ERROR_GETTING_RELAY_INFO)
                 .arg(lease.toText())
                 .arg(ex.what());
        return (OptionPtr());
    }

    // Create the relay data option.
    const OptionDefinition& def = LibDHCP::D6O_LQ_RELAY_DATA_DEF();
    OptionCustomPtr rd_option(new OptionCustom(def, Option::V6));

    // The peer field should come from the outer-most relay
    rd_option->writeAddress(relay_infos.front()->peeraddr_, 0);

    // For convenience, set the index of the last one.
    size_t innermost = relay_infos.size() - 1;

    // Iterate backward through the RelayInfo list and calculate the
    // packed size of each one in succession.
    uint16_t len = 0;
    for (size_t i = relay_infos.size(); i > 0; --i) {
        relay_infos[i - 1]->relay_msg_len_ = len;
        len += getRelayOverhead(*(relay_infos[i - 1]), (i == innermost));
    }

    // Now iterate forward over them, writing them to an OutputBuffer.
    isc::util::OutputBuffer buffer_out(Pkt6::DHCPV6_RELAY_HDR_LEN
                                       + relay_infos[0]->relay_msg_len_);

    for (size_t i = 0; i < relay_infos.size(); ++i) {
        RelayInfoPtr relay = relay_infos[i];

        // build relay-forw/relay-repl header (see RFC 8415, section 9)
        buffer_out.writeUint8(DHCPV6_RELAY_FORW);
        buffer_out.writeUint8(relay->hop_count_);
        buffer_out.writeData(&(relay->linkaddr_.toBytes()[0]),
                             isc::asiolink::V6ADDRESS_LEN);
        buffer_out.writeData(&relay->peeraddr_.toBytes()[0],
                              isc::asiolink::V6ADDRESS_LEN);

        // Store every option in this relay's scope.
        for (auto const& opt : relay->options_) {
            (opt.second)->pack(buffer_out);
        }

        // Include the header for the relay-msg option which will
        // contain the next relay forward. It's payload will be generated
        // in the next iteration.
        if (i < innermost) {
            buffer_out.writeUint16(D6O_RELAY_MSG);
            buffer_out.writeUint16(relay->relay_msg_len_);
        }
    }

    // Now convert them to an option buffer and add them to
    // relay data option.
    const OptionBuffer& relay_buffer = buffer_out.getVector();
    rd_option->writeBinary(relay_buffer, 1);

    // Dizzy yet? Don't worry, we're done.
    return (rd_option);
}

uint16_t
LeaseQueryImpl6::getRelayOverhead(const Pkt6::RelayInfo& relay, bool innermost) {
    uint16_t len = Pkt6::DHCPV6_RELAY_HDR_LEN; // fixed header

    if (innermost) {
        len += Option::OPTION6_HDR_LEN; // header of the relay-msg option
    }

    for (auto const& opt : relay.options_) {
        len += (opt.second)->len();
    }

    return (len);
}

void
LeaseQueryImpl6::parseRelayInfoList(ConstElementPtr relay_info,
                                    std::vector<RelayInfoPtr>& relay_infos) {
    if (!relay_info || relay_info->getType() != Element::list) {
        isc_throw(BadValue, "parseRelayInfoList: relay-info element empty or not a list");
    }

    for (auto const& relay : relay_info->listValue()) {
        RelayInfoPtr info = parseRelayInfo(relay);
        relay_infos.push_back(info);
    }
}

RelayInfoPtr
LeaseQueryImpl6::parseRelayInfo(ConstElementPtr relay_elem) {
    if (!relay_elem || (relay_elem->getType() != Element::map)) {
        isc_throw(BadValue, "parseRelayInfo: relay element empty or not a map");
    }

    RelayInfoPtr relay_info(new Pkt6::RelayInfo());
    auto elem = relay_elem->get("hop");
    if (!elem) {
        isc_throw(BadValue, "parseRelayInfo: 'hop' is missing");
    }

    try {
        relay_info->hop_count_ = static_cast<uint8_t>(elem->intValue());
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "parseRelayInfo: 'hop' is invalid: " << ex.what());
    }

    elem = relay_elem->get("peer");
    if (!elem) {
        isc_throw(BadValue, "parseRelayInfo: 'peer' is missing");
    }

    try {
        relay_info->peeraddr_ = IOAddress(elem->stringValue());
        if (!relay_info->peeraddr_.isV6()) {
            isc_throw(BadValue, "not a V6 address: " << relay_info->peeraddr_);
        }
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "parseRelayInfo: 'peer' is invalid: " << ex.what());
    }

    elem = relay_elem->get("link");
    if (!elem) {
        isc_throw(BadValue, "parseRelayInfo: 'link' is missing");
    }

    try {
        relay_info->linkaddr_ = IOAddress(elem->stringValue());
        if (!relay_info->linkaddr_.isV6()) {
            isc_throw(BadValue, "not a V6 address: " << relay_info->linkaddr_);
        }
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "parseRelayInfo: 'link' is invalid: " << ex.what());
    }

    // The options element is optional.
    elem = relay_elem->get("options");
    if (elem) {
        try {
            std::string hex_str = elem->stringValue();

            OptionBuffer binary;
            util::str::decodeFormattedHexString(hex_str, binary);
            static_cast<void>(LibDHCP::unpackOptions6(binary, DHCP6_OPTION_SPACE,
                                                      relay_info->options_));
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "parseRelayInfo: 'options' is invalid: " << ex.what());
        }
    }

    return (relay_info);
}

void
LeaseQueryImpl6::testServerId(const Pkt6Ptr& query) {
    OptionPtr client_server_id = query->getOption(D6O_SERVERID);
    if (client_server_id) {
        DuidPtr client_duid;
        try {
            client_duid.reset(new DUID(client_server_id->getData()));
        } catch (const std::exception& ex) {
            StatsMgr::instance().addValue("pkt6-rfc-violation",
                                          static_cast<int64_t>(1));
            isc_throw(BadValue, "DHCPV6_LEASEQUERY D6O_SERVERID malformed: "
                      << ex.what());
        }

        DuidPtr server_id = CfgMgr::instance().getCurrentCfg()->getCfgDUID()->getCurrentDuid();
        if (!server_id) {
            StatsMgr::instance().addValue("pkt6-rfc-violation",
                                          static_cast<int64_t>(1));
            isc_throw(Unexpected, "Server has no current server id?");
        } else if (*client_duid != *server_id) {
            StatsMgr::instance().addValue("pkt6-not-for-us",
                                          static_cast<int64_t>(1));
            isc_throw(BadValue, "rejecting DHCPV6_LEASEQUERY from: "
                      << query->getRemoteAddr() << ", unknown server-id: "
                      << (client_server_id ? client_server_id->toText() : "malformed"));
        }
    }

    // We have a winner!
}

void
LeaseQueryImpl6::sendResponse(const dhcp::Pkt6Ptr& response) const {
    // Pack the response.
    try {
        response->pack();
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger, DHCP6_LEASE_QUERY_PACKET_PACK_FAILED)
                  .arg(leaseQueryLabel(response))
                  .arg(ex.what());
        return;
    }

    try {
        send(response);
        LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC, DHCP6_LEASE_QUERY_REPLY_SENT)
                  .arg(leaseQueryLabel(response))
                  .arg(response->getRemoteAddr())
                  .arg(response->getRemotePort());

        StatsMgr::instance().addValue("pkt6-sent", static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt6-lease-query-reply-sent",
                                      static_cast<int64_t>(1));
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger, DHCP6_LEASE_QUERY_REPLY_SEND_FAILED)
                  .arg(leaseQueryLabel(response))
                  .arg(response->getIface())
                  .arg(response->getRemoteAddr())
                  .arg(response->getRemotePort())
                  .arg(ex.what());
    }
}

void LeaseQueryImpl6::send(const dhcp::Pkt6Ptr& response) const {
    IfaceMgr::instance().send(response);
}

Option6StatusCodePtr
LeaseQueryImpl6::makeStatusOption(const DHCPv6StatusCode& status_code,
                                  const std::string message) {
    Option6StatusCodePtr opt(new Option6StatusCode(status_code, message));
    return (opt);
}

std::string
LeaseQueryImpl6::leaseQueryLabel(const Pkt6Ptr& packet) {
    std::stringstream label;

    try {
        DuidPtr client_id = packet->getClientId();
        label << "type: " << packet->getName()
              << ", client id: " << (client_id ? client_id->toText() : "<none>")
              << ", requester: " << packet->getRemoteAddr()
              << ", transid: " << packet->getTransid();

    } catch (const std::exception& ex) {
        // Shouldn't happen. This just ensures we're exception safe.
        label << "label error" << ex.what();
    }

    return (label.str());
}

int
LeaseQueryImpl6::upgradeHandler(CalloutHandle& handle) {
    ConstElementPtr response;
    size_t upgraded = 0;
    LeasePageSize page_size(LeaseQueryImpl::PageSize);
    try {
        util::MultiThreadingCriticalSection cc;
        auto& lease_mgr = LeaseMgrFactory::instance();
        // check getExtendedInfoTablesEnabled() here?
        upgraded = lease_mgr.upgradeExtendedInfo6(page_size);
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

void
LeaseQueryImpl6::populatePrefixLengthList(SrvConfigPtr cfg) {
    if (build_prefix_lens_) {
        // Empty the current entries.
        clearPrefixLengthList();

        // traverse subnet pd pools and build list
        const Subnet6Collection* subnets = cfg->getCfgSubnets6()->getAll();
        for (auto const& subnet : *subnets) {
            const PoolCollection& pools = subnet->getPools(Lease::TYPE_PD);
            for (auto const& pool : pools) {
                Pool6Ptr p6 = boost::dynamic_pointer_cast<Pool6>(pool);
                addPrefixLength(p6->getLength());
            }
        }
    }

    LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC, DHCP6_LEASE_QUERY_PREFIX_LENGTH_LIST)
              .arg(dumpPrefixLengthList(prefix_lens_));
}

std::string
LeaseQueryImpl6::dumpPrefixLengthList(const PrefixLengthList& prefix_lengths) {
    std::ostringstream oss;
    oss << "[";

    auto first_one = true;
    for (auto const& it : boost::adaptors::reverse(prefix_lengths)) {
        if (!first_one) {
            oss << ",";
        } else {
            first_one = false;
        }

        oss << " " << static_cast<int>(it);
    }

    oss << " ]";
    return (oss.str());
}
