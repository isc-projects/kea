// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/pkt4.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <bulk_lease_query4.h>
#include <lease_query_impl4.h>
#include <lease_query_log.h>
#include <blq_service.h>
#include <stats/stats_mgr.h>
#include <util/encode/encode.h>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::lease_query;
using namespace isc::log;
using namespace isc::stats;

std::string
getStatusCodeName(BLQStatusCode status) {
    switch (status) {
    case BLQ_STATUS_Success:
        return ("Success");
    case BLQ_STATUS_UnspecFail:
        return ("UnspecFail");
    case BLQ_STATUS_QueryTerminated:
        return ("QueryTerminated");
    case BLQ_STATUS_MalformedQuery:
        return ("MalformedQuery");
    case BLQ_STATUS_NotAllowed:
        return ("NotAllowed");
    default:
        return ("(unknown status code)");
    }
}

std::string
getStateName(BLQStates state) {
    switch (state) {
    case BLQ_STATE_AVAILABLE:
        return ("AVAILABLE");
    case BLQ_STATE_ACTIVE:
        return ("ACTIVE");
    case BLQ_STATE_EXPIRED:
        return ("EXPIRED");
    case BLQ_STATE_RELEASED:
        return ("RELEASED");
    case BLQ_STATE_ABANDONED:
        return ("ABANDONED");
    case BLQ_STATE_RESET:
        return ("RESET");
    case BLQ_STATE_REMOTE:
        return ("REMOTE");
    case BLQ_STATE_TRANSITIONING:
        return ("TRANSITIONING");
    default:
        return ("(unknown state)");
    }
}

std::string
BulkLeaseQuery4::leaseQueryLabel(const BlqMsgPtr& msg) {
    Pkt4Ptr pkt = boost::dynamic_pointer_cast<Pkt4>(msg->getPkt());
    if (!pkt) {
        return ("<none>");
    }
    return (LeaseQueryImpl4::leaseQueryLabel(pkt));
}

void
BulkLeaseQuery4::init() {
    // Take the page size from the MT LQ listener manager.
    auto service = BulkLeaseQueryService::instance();
    if (service) {
        page_size_ = service->getMaxLeasePerFetch();
    }

    query4_ = boost::dynamic_pointer_cast<Pkt4>(query_->getQuery());
    if (!query4_) {
        // Shouldn't happen
        isc_throw(BadValue, "BulkLeaseQuery4 has no DHCPv4 query");
    }

    // Check addresses.
    if (!query4_->getCiaddr().isV4Zero()) {
        sendDone(BLQ_STATUS_MalformedQuery, "ciaddr must be zero");
        return;
    }
    if (!query4_->getYiaddr().isV4Zero()) {
        sendDone(BLQ_STATUS_MalformedQuery, "yiaddr must be zero");
        return;
    }
    if (!query4_->getSiaddr().isV4Zero()) {
        sendDone(BLQ_STATUS_MalformedQuery, "siaddr must be zero");
        return;
    }

    // Get the client identifier.
    query_client_id_ = query4_->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (query_client_id_) {
        query_mask_ |= 1;
    }

    // Get the hardware address.
    query_hwaddr_ = query4_->getHWAddr();
    if (query_hwaddr_->htype_ || query_hwaddr_->hwaddr_.size()) {
        query_mask_ |= 2;
    }

    // Get the RAI.
    OptionPtr rai = query4_->getOption(DHO_DHCP_AGENT_OPTIONS);

    // Get the relay identifier.
    if (rai) {
        query_relay_id_ = rai->getOption(RAI_OPTION_RELAY_ID);
        if (query_relay_id_) {
            if (query_relay_id_->getData().empty()) {
                sendDone(BLQ_STATUS_MalformedQuery, "empty relay id option");
                return;
            }
            query_mask_ |= 4;
        }
    }

    // Get the remote identifier.
    if (rai) {
        query_remote_id_ = rai->getOption(RAI_OPTION_REMOTE_ID);
        if (query_remote_id_) {
            if (query_remote_id_->getData().empty()) {
                sendDone(BLQ_STATUS_MalformedQuery, "empty remote id option");
                return;
            }
            query_mask_ |= 8;
        }
    }

    // Get the query start time.
    OptionPtr opt = query4_->getOption(DHO_QUERY_START_TIME);
    if (opt) {
        OptionUint32Ptr qst =
            boost::dynamic_pointer_cast<OptionInt<uint32_t>>(opt);
        if (qst) {
            query_start_time_ = qst->getValue();
        }
        if (!qst || (static_cast<int32_t>(query_start_time_) < 0)) {
            sendDone(BLQ_STATUS_MalformedQuery, "illegal 'query-start-time'");
            return;
        }
    }

    // Get the query end time.
    opt = query4_->getOption(DHO_QUERY_END_TIME);
    if (opt) {
        OptionUint32Ptr qst =
            boost::dynamic_pointer_cast<OptionInt<uint32_t>>(opt);
        if (qst) {
            query_end_time_ = qst->getValue();
        }
        if (!qst || (static_cast<int32_t>(query_end_time_) < 0)) {
            sendDone(BLQ_STATUS_MalformedQuery, "illegal 'query-end-time'");
            return;
        }
    }
    if ((query_start_time_ > 0) && (query_end_time_ > 0) &&
        (query_start_time_ > query_end_time_)) {
        sendDone(BLQ_STATUS_MalformedQuery, "query-start-time > query-end-time");
        return;
    }

    // Get the VPN-ID.
    opt = query4_->getOption(DHO_VSS);
    if (opt) {
        sendDone(BLQ_STATUS_NotAllowed, "VPNs are not supported");
        return;
    }

    // Do the query based on which query attribute we have,
    // or error out.
    switch (query_mask_) {
    case 0:
        // Query for all configured addresses (not implemented).
        sendDone(BLQ_STATUS_NotAllowed,
                 "query for all configured addresses is not supported");
        return;

    case 1:
    case 2:
    case 4:
    case 8:
        // Supported query by something.
        return;

    default:
        // Multiple query types.
        sendDone(BLQ_STATUS_MalformedQuery, "multiple queries");
        return;

    }
}

void
BulkLeaseQuery4::start() {
    if (started_) {
        isc_throw(InvalidOperation, "BulkLeaseQuery4 already in progress");
    }
    started_ = true;

    switch (query_mask_) {
    case 1:
        // Query by client id.
        bulkQueryByClientId();
        return;
    case 2:
        // Query by hardware addr.
        bulkQueryByHWAddr();
        return;
    case 4:
        // Query by relay id.
        bulkQueryByRelayId();
        return;
    case 8:
        // Query by remote id.
        bulkQueryByRemoteId();
        return;
    default:
        isc_throw(InvalidOperation, "unknown query-type");
    }
}

void
BulkLeaseQuery4::bulkQueryByClientId() {
    if (!query_client_id_) {
        isc_throw(InvalidOperation, "no query client id");
    }

    // Fetch leases.
    ClientId client_id(query_client_id_->getData());
    Lease4Collection leases = LeaseMgrFactory::instance().getLease4(client_id);

    // Send responses.
    for (auto const& lease : leases) {
        if (lease->state_ != Lease::STATE_DEFAULT) {
            // Not active.
            continue;
        }
        if (lease->expired()) {
            // Already expired.
            continue;
        }
        if ((query_start_time_ > 0) && (lease->cltt_ < query_start_time_)) {
            // Too old.
            continue;
        }
        if ((query_end_time_ > 0) && (lease->cltt_ > query_end_time_)) {
            // Too young.
            continue;
        }

        // Send response.
        sendActive(lease);
    }

    // Send the done message.
    sendDone(BLQ_STATUS_Success);
}

void
BulkLeaseQuery4::bulkQueryByHWAddr() {
    if (!query_hwaddr_) {
        isc_throw(InvalidOperation, "no query hardware addr");
    }

    Lease4Collection leases =
        LeaseMgrFactory::instance().getLease4(*query_hwaddr_);

    // Send responses.
    for (auto const& lease : leases) {
        if (lease->state_ != Lease::STATE_DEFAULT) {
            // Not active.
            continue;
        }
        if (lease->expired()) {
            // Already expired.
            continue;
        }
        if ((query_start_time_ > 0) && (lease->cltt_ < query_start_time_)) {
            // Too old.
            continue;
        }
        if ((query_end_time_ > 0) && (lease->cltt_ > query_end_time_)) {
            // Too young.
            continue;
        }

        // Send response.
        sendActive(lease);
    }

    // Send the done message.
    sendDone(BLQ_STATUS_Success);
}

void
BulkLeaseQuery4::bulkQueryByRelayId() {
    if (!query_relay_id_) {
        isc_throw(InvalidOperation, "no query relay id");
    }

    auto const& relay_id = query_relay_id_->getData();
    Lease4Collection leases;

    // Database possible call: check if the hook was terminated.
    CHECK_TERMINATED;

    leases =
        LeaseMgrFactory::instance().getLeases4ByRelayId(relay_id,
                                                        start_addr_,
                                                        LeasePageSize(page_size_),
                                                        query_start_time_,
                                                        query_end_time_);
    // when empty it is done.
    if (leases.empty()) {
        sendDone(BLQ_STATUS_Success);
        return;
    }

    // Record the last address to restart from this point.
    start_addr_ = leases.back()->addr_;

    // Send responses.
    for (auto const& lease : leases) {
        if (lease->state_ != Lease::STATE_DEFAULT) {
            // Not active.
            continue;
        }
        if (lease->expired()) {
            // Already expired.
            continue;
        }

        // Send response.
        sendActive(lease);
    }

    post_(std::bind(&BulkLeaseQuery4::doBulkQueryByRelayId,
                    boost::static_pointer_cast<BulkLeaseQuery4>(shared_from_this())));
}

void
BulkLeaseQuery4::bulkQueryByRemoteId() {
    if (!query_remote_id_) {
        isc_throw(InvalidOperation, "no query remote id");
    }

    auto const& remote_id = query_remote_id_->getData();
    Lease4Collection leases;

    // Database possible call: check if the hook was terminated.
    CHECK_TERMINATED;

    leases =
        LeaseMgrFactory::instance().getLeases4ByRemoteId(remote_id,
                                                         start_addr_,
                                                         LeasePageSize(page_size_),
                                                         query_start_time_,
                                                         query_end_time_);
    // when empty it is done.
    if (leases.empty()) {
        sendDone(BLQ_STATUS_Success);
        return;
    }

    // Record the last address to restart from this point.
    start_addr_ = leases.back()->addr_;

    // Send responses.
    for (auto const& lease : leases) {
        if (lease->state_ != Lease::STATE_DEFAULT) {
            // Not active.
            continue;
        }
        if (lease->expired()) {
            // Already expired.
            continue;
        }

        // Send response.
        sendActive(lease);
    }

    post_(std::bind(&BulkLeaseQuery4::doBulkQueryByRemoteId,
                    boost::static_pointer_cast<BulkLeaseQuery4>(shared_from_this())));
}

void
BulkLeaseQuery4::send(Pkt4Ptr response) {
    CHECK_TERMINATED;

    // Add the dhcp-server-identifier in the first response.
    if (sent_ == 0) {
        const OptionDefinition& def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();
        OptionCustomPtr opt(new OptionCustom(def, Option::V4));
        auto const& srv = BulkLeaseQueryService::instance();
        if (!srv) {
            isc_throw(Unexpected, "can't find bulk lease query service");
        }
        opt->writeAddress(srv->getLeaseQueryIp());
        response->addOption(opt);
    }
    ++sent_;

    // Send it.
    BlqResponsePtr resp(new BlqResponse(response));
    if (!push_to_send_(resp)) {
        isc_throw(QueryTerminated, "connection closed");
    }
}

void
BulkLeaseQuery4::sendDone(BLQStatusCode status, const std::string& message) {
    // Create and send done message.
    Pkt4Ptr done(new Pkt4(DHCPLEASEQUERYDONE, query4_->getTransid()));

    // Zero out the hwaddr type.
    done->setHWAddr(HWAddrPtr(new HWAddr(std::vector<uint8_t>{}, 0)));

    // Add the status.
    if ((status != BLQ_STATUS_Success) || !message.empty()) {
        const OptionDefinition& def = LibDHCP::DHO_STATUS_CODE_DEF();
        OptionCustomPtr opt(new OptionCustom(def, Option::V4));
        opt->writeInteger(static_cast<uint8_t>(status), 0);
        opt->writeString(message, 1);
        done->addOption(opt);
    }

    // Send it.
    send(done);

    // It is final.
    setDone();
}

void
BulkLeaseQuery4::sendActive(const Lease4Ptr& lease) {
    // Should not happen.
    if (!lease) {
        return;
    }

    // Get subnet.
    Subnet4Ptr subnet = CfgMgr::instance().getCurrentCfg()
                        ->getCfgSubnets4()->getSubnet(lease->subnet_id_);
    if (!subnet) {
        // Should not happen: simply ignore this lease.
        return;
    }

    // Create and send active message.
    Pkt4Ptr active(new Pkt4(DHCPLEASEACTIVE, query4_->getTransid()));

    // Add client IP address.
    active->setCiaddr(lease->addr_);

    // Add client hardware address.
    if (lease->hwaddr_) {
        active->setHWAddr(lease->hwaddr_);
    } else {
        active->setHWAddr(HWAddrPtr(new HWAddr(std::vector<uint8_t>{}, 0)));
    }

    // Add client identifier.
    if (lease->client_id_) {
        OptionPtr opt(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                 lease->client_id_->getClientId()));
        active->addOption(opt);
    }

    // Add base time.
    OptionPtr opt(new OptionUint32(Option::V4, DHO_BASE_TIME, time(0)));
    active->addOption(opt);

    // Add lease life time, T1 and T2.
    LeaseQueryImpl4::addLeaseTimes(active, lease, subnet);

    // Add relay-agent-info (82) from the extended info in the lease's
    // user-context and add it to the response.
    LeaseQueryImpl4::addRelayAgentInfo(active, lease);

    // Send it.
    send(active);
}
