// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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
#include <bulk_lease_query6.h>
#include <lease_query_impl_factory.h>
#include <lease_query_impl6.h>
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
BulkLeaseQuery6::leaseQueryLabel(const BlqMsgPtr& msg) {
    Pkt6Ptr pkt = boost::dynamic_pointer_cast<Pkt6>(msg->getPkt());
    if (!pkt) {
        return ("<none>");
    }
    return (LeaseQueryImpl6::leaseQueryLabel(pkt));
}

void
BulkLeaseQuery6::init() {
    // Take the page size from the MT LQ listener manager.
    auto service = BulkLeaseQueryService::instance();
    if (service) {
        page_size_ = service->getMaxLeasePerFetch();
    }

    query6_ = boost::dynamic_pointer_cast<Pkt6>(query_->getQuery());
    if (!query6_) {
        // Shouldn't happen
        isc_throw(BadValue, "BulkLeaseQuery6 has no DHCPv6 query");
    }

    // The query must have a client id option.
    DuidPtr req_clientid = query6_->getClientId();
    if (!req_clientid) {
        isc_throw(BadValue, "DHCPV6_LEASEQUERY must supply a D6O_CLIENTID");
    }

    // If the query has a server id option it should be for us.
    LeaseQueryImpl6::testServerId(query6_);

    // Get the lease query option.
    lq_option_ = boost::dynamic_pointer_cast<OptionCustom>
        (query6_->getOption(D6O_LQ_QUERY));
    if (!lq_option_) {
        isc_throw(BadValue, "DHCPV6_LEASEQUERY must supply a D6O_LQ_QUERY option");
    }

    // Extract the type and link fields.
    try {
        query_type_ = lq_option_->readInteger<uint8_t>(0);
        link_addr_ = lq_option_->readAddress(1);
    } catch (const std::exception& ex) {
        // unpack() should catch this?
        isc_throw(BadValue, "error reading query field(s): " << ex.what());
    }

    // Based on the query type, extract the requisite options.
    Option6StatusCodePtr status;
    OptionPtr opt;
    switch (query_type_) {
    case LQ6QT_BY_ADDRESS:
        opt = lq_option_->getOption(D6O_IAADDR);
        query_iaaddr_ = boost::dynamic_pointer_cast<Option6IAAddr>(opt);
        if (!query_iaaddr_) {
            status = LeaseQueryImpl6::makeStatusOption(STATUS_MalformedQuery,
                                                       "missing D6O_IAADDR");
            sendReply(status);
            return;
        }
        break;
    case LQ6QT_BY_CLIENTID:
        opt = lq_option_->getOption(D6O_CLIENTID);
        if (!opt) {
            status = LeaseQueryImpl6::makeStatusOption(STATUS_MalformedQuery,
                                                       "missing D6O_CLIENTID");
            sendReply(status);
            return;
        }
        try {
            query_client_id_.reset(new DUID(opt->getData()));
        } catch (const std::exception& ex) {
            status = LeaseQueryImpl6::makeStatusOption(STATUS_MalformedQuery,
                                                       "malformed D6O_CLIENTID");
            sendReply(status);
            return;
        }
        break;
    case LQ6QT_BY_RELAY_ID:
        opt = lq_option_->getOption(D6O_RELAY_ID);
        if (!opt) {
            status = LeaseQueryImpl6::makeStatusOption(STATUS_MalformedQuery,
                                                       "missing D6O_RELAY_ID");
            sendReply(status);
            return;
        }
        try {
            query_relay_id_.reset(new DUID(opt->getData()));
        } catch (const std::exception& ex) {
            status = LeaseQueryImpl6::makeStatusOption(STATUS_MalformedQuery,
                                                        "malformed D6O_RELAY_ID");
            sendReply(status);
            return;
        }
        break;
    case LQ6QT_BY_REMOTE_ID:
        query_remote_id_ = lq_option_->getOption(D6O_REMOTE_ID);
        if (!query_remote_id_) {
            status = LeaseQueryImpl6::makeStatusOption(STATUS_MalformedQuery,
                                                       "missing D6O_REMOTE_ID");
            sendReply(status);
            return;
        } else if (query_remote_id_->getData().empty()) {
            status = LeaseQueryImpl6::makeStatusOption(STATUS_MalformedQuery,
                                                       "empty D6O_REMOTE_ID");
            sendReply(status);
            return;
        }
        break;
    case LQ6QT_BY_LINK_ADDRESS:
        if (link_addr_.isV6Zero()) {
            status = LeaseQueryImpl6::makeStatusOption(STATUS_MalformedQuery,
                                                       "undefined link address");
            sendReply(status);
            return;
        }
        break;
    default:
        status = LeaseQueryImpl6::makeStatusOption(STATUS_UnknownQueryType,
                                                   "unknown query-type");
        sendReply(status);
        return;
    }
}

void
BulkLeaseQuery6::start() {
    if (started_) {
        isc_throw(InvalidOperation, "BulkLeaseQuery6 already in progress");
    }
    started_ = true;

    switch (query_type_) {
    case LQ6QT_BY_ADDRESS:
        bulkQueryByIpAddress();
        return;
    case LQ6QT_BY_CLIENTID:
        bulkQueryByClientId();
        return;
    case LQ6QT_BY_RELAY_ID:
        bulkQueryByRelayId();
        return;
    case LQ6QT_BY_REMOTE_ID:
        bulkQueryByRemoteId();
        return;
    case LQ6QT_BY_LINK_ADDRESS:
        bulkQueryByLinkAddress();
        return;
    default:
        isc_throw(InvalidOperation, "unknown query-type");
    }
}

void
BulkLeaseQuery6::bulkQueryByIpAddress() {
    if (!query_iaaddr_) {
        isc_throw(InvalidOperation, "no query ip address");
    }
    Lease6Collection leases;
    Option6StatusCodePtr status;

    const LeaseQueryImpl6& impl6 = dynamic_cast<const LeaseQueryImpl6&>(LeaseQueryImplFactory::getImpl());
    status = LeaseQueryImpl6::queryByIpAddress(query_iaaddr_->getAddress(),
                                               leases, impl6.getPrefixLengthList());
    if (leases.empty()) {
        // Error case.
        sendReply(status);
        return;
    }
    if (leases.size() > 1) {
        isc_throw(Unexpected, "more than one lease for an address");
    }

    // Construct and send the reply message.
    Pkt6Ptr reply = LeaseQueryImpl6::initReply(query6_);
    // Add the client option.
    reply->addOption(LeaseQueryImpl6::makeClientOption(leases.front()));
    // Add the status.
    reply->addOption(status);
    // Send the reply.
    send(reply);

    // Construct and send the done message.
    Pkt6Ptr done = LeaseQueryImpl6::initDone(query6_);
    send(done);

    // Done.
    setDone();
}

void
BulkLeaseQuery6::bulkQueryByClientId() {
    if (!query_client_id_) {
        isc_throw(InvalidOperation, "no query client id");
    }
    Lease6Collection leases;
    Option6StatusCodePtr status;
    status = LeaseQueryImpl6::queryByClientId(query_client_id_,
                                              link_addr_,
                                              leases);

    if (leases.empty()) {
        // Error case.
        sendReply(status);
        return;
    }

    bool first = true;
    for (auto const& lease : leases) {
        if (first) {
            first = false;
            // Create and send the reply message.
            Pkt6Ptr reply = LeaseQueryImpl6::initReply(query6_);
            // Add the client option.
            reply->addOption(LeaseQueryImpl6::makeClientOption(lease));
            // Add the status.
            reply->addOption(status);
            // Send the reply.
            send(reply);
            continue;
        }
        // Create and send the response.
        Pkt6Ptr response = LeaseQueryImpl6::initData(query6_);
        // Add the client option.
        response->addOption(LeaseQueryImpl6::makeClientOption(lease));
        // Send the response.
        send(response);
    }

    // Construct and send the done message.
    Pkt6Ptr done = LeaseQueryImpl6::initDone(query6_);
    send(done);

    // Done.
    setDone();
}

void
BulkLeaseQuery6::bulkQueryByRelayId() {
    if (!query_relay_id_) {
        isc_throw(InvalidOperation, "no query relay id");
    }
    Option6StatusCodePtr status;
    if (!LeaseMgrFactory::instance().getExtendedInfoTablesEnabled()) {
        status = LeaseQueryImpl6::makeStatusOption(STATUS_NotAllowed,
                                                   "extended info tables are disabled");
        sendReply(status);
        return;
    }

    Lease6Collection leases;
    status = LeaseQueryImpl6::queryByRelayIdStart(query_relay_id_,
                                                  start_addr_,
                                                  page_size_,
                                                  link_addr_,
                                                  links_,
                                                  leases);
    if (leases.empty()) {
        // Error case.
        sendReply(status);
        return;
    }

    bool first = true;
    for (auto const& lease : leases) {
        if (first) {
            first = false;
            // Create and send the reply message.
            Pkt6Ptr reply = LeaseQueryImpl6::initReply(query6_);
            // Add the client option.
            reply->addOption(LeaseQueryImpl6::makeClientOption(lease));
            // Add the status.
            reply->addOption(status);
            // Send the reply.
            send(reply);
            continue;
        }
        // Create and send the response.
        Pkt6Ptr response = LeaseQueryImpl6::initData(query6_);
        // Add the client option.
        response->addOption(LeaseQueryImpl6::makeClientOption(lease));
        // Send the response.
        send(response);
    }

    post_(std::bind(&BulkLeaseQuery6::doBulkQueryByRelayIdNext,
                    boost::static_pointer_cast<BulkLeaseQuery6>(shared_from_this())));
}

void
BulkLeaseQuery6::bulkQueryByRelayIdNext() {
    if (!query_relay_id_) {
        isc_throw(InvalidOperation, "no query relay id");
    }
    Lease6Collection leases;
    const IOAddress position = start_addr_;
    LeaseQueryImpl6::queryByRelayIdNext(query_relay_id_,
                                        start_addr_,
                                        page_size_,
                                        links_,
                                        leases);
    if (start_addr_ == position) {
        // Construct and send the done message.
        Pkt6Ptr done = LeaseQueryImpl6::initDone(query6_);
        send(done);

        // Done.
        setDone();

        return;
    }

    for (auto const& lease : leases) {
        // Create and send the response
        Pkt6Ptr response = LeaseQueryImpl6::initData(query6_);
        // Add the client option.
        response->addOption(LeaseQueryImpl6::makeClientOption(lease));
        // Send the response.
        send(response);
    }

    post_(std::bind(&BulkLeaseQuery6::doBulkQueryByRelayIdNext,
                    boost::static_pointer_cast<BulkLeaseQuery6>(shared_from_this())));
}

void
BulkLeaseQuery6::bulkQueryByRemoteId() {
    if (!query_remote_id_) {
        isc_throw(InvalidOperation, "no query remote id");
    }
    Option6StatusCodePtr status;
    if (!LeaseMgrFactory::instance().getExtendedInfoTablesEnabled()) {
        status = LeaseQueryImpl6::makeStatusOption(STATUS_NotAllowed,
                                                   "extended info tables are disabled");
        sendReply(status);
        return;
    }

    Lease6Collection leases;
    status = LeaseQueryImpl6::queryByRemoteIdStart(query_remote_id_->getData(),
                                                   start_addr_,
                                                   page_size_,
                                                   link_addr_,
                                                   links_,
                                                   leases);
    if (leases.empty()) {
        // Error case.
        sendReply(status);
        return;
    }

    bool first = true;
    for (auto const& lease : leases) {
        if (first) {
            first = false;
            // Create and send the reply message.
            Pkt6Ptr reply = LeaseQueryImpl6::initReply(query6_);
            // Add the client option.
            reply->addOption(LeaseQueryImpl6::makeClientOption(lease));
            // Add the status.
            reply->addOption(status);
            // Send the reply.
            send(reply);
            continue;
        }
        // Create and send the response.
        Pkt6Ptr response = LeaseQueryImpl6::initData(query6_);
        // Add the client option.
        response->addOption(LeaseQueryImpl6::makeClientOption(lease));
        // Send the response.
        send(response);
    }

    post_(std::bind(&BulkLeaseQuery6::doBulkQueryByRemoteIdNext,
                    boost::static_pointer_cast<BulkLeaseQuery6>(shared_from_this())));
}


void
BulkLeaseQuery6::bulkQueryByRemoteIdNext() {
    if (!query_remote_id_) {
        isc_throw(InvalidOperation, "no query remote id");
    }
    Lease6Collection leases;
    const IOAddress position = start_addr_;
    LeaseQueryImpl6::queryByRemoteIdNext(query_remote_id_->getData(),
                                         start_addr_,
                                         page_size_,
                                         links_,
                                         leases);
    if (start_addr_ == position) {
        // Construct and send the done message.
        Pkt6Ptr done = LeaseQueryImpl6::initDone(query6_);
        send(done);

        // Done.
        setDone();

        return;
    }

    for (auto const& lease : leases) {
        // Create and send the response
        Pkt6Ptr response = LeaseQueryImpl6::initData(query6_);
        // Add the client option.
        response->addOption(LeaseQueryImpl6::makeClientOption(lease));
        // Send the response.
        send(response);
    }

    post_(std::bind(&BulkLeaseQuery6::doBulkQueryByRemoteIdNext,
                    boost::static_pointer_cast<BulkLeaseQuery6>(shared_from_this())));
}

void
BulkLeaseQuery6::bulkQueryByLinkAddress() {
    // In fact by-link-address does not use extended info tables,
    // more it can be supported by SQL lease backends.
    Option6StatusCodePtr status;
    if (!LeaseMgrFactory::instance().getExtendedInfoTablesEnabled()) {
        status = LeaseQueryImpl6::makeStatusOption(STATUS_NotAllowed,
                                                   "extended info tables are disabled");
        sendReply(status);
        return;
    }

    Lease6Collection leases;
    status = LeaseQueryImpl6::queryByLinkStart(start_addr_,
                                               page_size_,
                                               link_addr_,
                                               links_,
                                               leases);
    if (leases.empty()) {
        // Error case.
        sendReply(status);
        return;
    }

    bool first = true;
    for (auto const& lease : leases) {
        if (first) {
            first = false;
            // Create and send the reply message.
            Pkt6Ptr reply = LeaseQueryImpl6::initReply(query6_);
            // Add the client option.
            reply->addOption(LeaseQueryImpl6::makeClientOption(lease));
            // Add the status.
            reply->addOption(status);
            // Send the reply.
            send(reply);
            continue;
        }
        // Create and send the response.
        Pkt6Ptr response = LeaseQueryImpl6::initData(query6_);
        // Add the client option.
        response->addOption(LeaseQueryImpl6::makeClientOption(lease));
        // Send the response.
        send(response);
    }

    post_(std::bind(&BulkLeaseQuery6::doBulkQueryByLinkAddressNext,
                    boost::static_pointer_cast<BulkLeaseQuery6>(shared_from_this())));
}

void
BulkLeaseQuery6::bulkQueryByLinkAddressNext() {
    Lease6Collection leases;
    const IOAddress position = start_addr_;
    LeaseQueryImpl6::queryByLinkNext(start_addr_,
                                     page_size_,
                                     links_,
                                     leases);
    if (start_addr_ == position) {
        // Construct and send the done message.
        Pkt6Ptr done = LeaseQueryImpl6::initDone(query6_);
        send(done);

        // Done.
        setDone();

        return;
    }

    for (auto const& lease : leases) {
        // Create and send the response
        Pkt6Ptr response = LeaseQueryImpl6::initData(query6_);
        // Add the client option.
        response->addOption(LeaseQueryImpl6::makeClientOption(lease));
        // Send the response.
        send(response);
    }

    post_(std::bind(&BulkLeaseQuery6::doBulkQueryByLinkAddressNext,
                    boost::static_pointer_cast<BulkLeaseQuery6>(shared_from_this())));
}

void
BulkLeaseQuery6::send(Pkt6Ptr response) const {
    CHECK_TERMINATED;
    BlqResponsePtr resp(new BlqResponse(response));
    if (!push_to_send_(resp)) {
        isc_throw(QueryTerminated, "connection closed");
    }
}

void
BulkLeaseQuery6::sendReply(OptionPtr status) {
    // Create and send reply message.
    Pkt6Ptr reply = LeaseQueryImpl6::initReply(query6_);
    // Add the status.
    reply->addOption(status);
    // Send the reply.
    send(reply);

    // It is final.
    setDone();
}
