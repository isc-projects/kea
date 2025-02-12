// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <bulk_lease_query4.h>
#include <bulk_lease_query6.h>
#include <lease_query_connection.h>
#include <lease_query_log.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::log;
using namespace isc::tcp;
namespace ph = std::placeholders;

namespace isc {
namespace lease_query {

LeaseQueryConnection::
LeaseQueryConnection(const IOServicePtr& io_service,
                     const tcp::TcpConnectionAcceptorPtr& acceptor,
                     const TlsContextPtr& tls_context,
                     TcpConnectionPool& connection_pool,
                     const TcpConnectionAcceptorCallback& acceptor_callback,
                     const TcpConnectionFilterCallback& filter_callback,
                     const long idle_timeout,
                     const uint16_t family,
                     const size_t max_concurrent_queries,
                     const size_t read_max)
    : TcpConnection(io_service,
                    acceptor,
                    tls_context,
                    connection_pool,
                    acceptor_callback,
                    filter_callback,
                    idle_timeout,
                    read_max),
      family_(family),
      io_service_(io_service),
      stopping_(false),
      can_send_(true),
      max_concurrent_queries_(max_concurrent_queries) {
}

void
LeaseQueryConnection::shutdown() {
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        can_send_ = false;
        responses_.clear();
        response_to_send_.reset();
    }
    running_queries_.clear();
    pending_queries_.clear();
    TcpConnection::shutdown();
}

void
LeaseQueryConnection::close() {
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        can_send_ = false;
        responses_.clear();
        response_to_send_.reset();
    }
    running_queries_.clear();
    pending_queries_.clear();
    TcpConnection::close();
}

void
LeaseQueryConnection::stopThisConnection() {
    bool stop_now = false;
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        if (stopping_ || !can_send_) {
            return;
        }
        stopping_ = true;
        if (!response_to_send_) {
            stop_now = true;
            can_send_ = false;
        }
    }
    if (stop_now) {
        TcpConnection::stopThisConnection();
    }
}

TcpRequestPtr
LeaseQueryConnection::createRequest() {
    return (TcpStreamRequestPtr(new TcpStreamRequest()));
}

void
LeaseQueryConnection::requestReceived(TcpRequestPtr request) {
    TcpStreamRequestPtr stream_req =
        boost::dynamic_pointer_cast<TcpStreamRequest>(request);
    if (!stream_req) {
        // Should never happen.
        isc_throw(isc::Unexpected, "request not a TcpStreamRequest");
    }

    // Unpack the stream request.
    stream_req->unpack();
    auto length  = stream_req->getRequestSize();
    if (!length) {
        // log an error and get out.
        LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY_EMPTY_REQUEST)
            .arg(getRemoteEndpointAddressAsText());
        stopThisConnection();
        return;
    }

    const uint8_t* data = stream_req->getRequest();

    // The request data is a packed DHCP<family> packet.  We need to unpack it.
    BlqQueryPtr query;
    try {
        if (family_ == AF_INET) {
            query = unpackQuery4(data, length);
        } else {
            query = unpackQuery6(data, length);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY_UNPACK_ERROR)
            .arg(getRemoteEndpointAddressAsText())
            .arg(ex.what());
        stopThisConnection();
        return;
    }

    if (!query) {
        stopThisConnection();
        return;
    }

    LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC,
              BULK_LEASE_QUERY_QUERY_RECEIVED)
        .arg(getRemoteEndpointAddressAsText())
        .arg(query->getQuery()->toText());

    if (findQuery(query->getXid())) {
        LOG_WARN(lease_query_logger, BULK_LEASE_QUERY_DUPLICATE_XID)
            .arg(getRemoteEndpointAddressAsText())
            .arg(query->getXid());
        return;
    }

    if (noPendingQuery() &&
        ((max_concurrent_queries_ == 0) ||
         (max_concurrent_queries_ > getNumRunningQueries()))) {
        startQuery(query);
    } else {
        LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC,
                  BULK_LEASE_QUERY_AT_MAX_CONCURRENT_QUERIES)
            .arg(getRemoteEndpointAddressAsText())
            .arg(BulkLeaseQuery6::leaseQueryLabel(query))
            .arg(max_concurrent_queries_);
        addPendingQuery(query);
    }
}

void
LeaseQueryConnection::sendNextResponse() {
    bool deferred_stop = false;
    BlqResponsePtr do_send;
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        if (!can_send_) {
            return;
        }
        if (!response_to_send_) {
            if (stopping_) {
                deferred_stop = true;
                can_send_ = false;
            } else if (responses_.size()) {
                do_send = response_to_send_ = responses_.front();
                responses_.pop_front();
            }
        }
    }

    // Deferred stop.
    if (deferred_stop) {
        TcpConnection::stopThisConnection();
    } else

    // Start sending the next response (if one).
    if (do_send) {
        try {
            asyncSendResponse(makeTcpResponse(do_send));
            LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC,
                      BULK_LEASE_QUERY_RESPONSE_SENT)
                .arg(getRemoteEndpointAddressAsText())
                .arg(do_send->getResponse()->toText());
        } catch (const std::exception& ex) {
            LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY_RESPONSE_SEND_ERROR)
                .arg(getRemoteEndpointAddressAsText())
                .arg(BulkLeaseQuery6::leaseQueryLabel(do_send))
                .arg(ex.what());
            std::lock_guard<std::mutex> lck(responses_mutex_);
            response_to_send_.reset();
            do_send.reset();
        }
    }
}

TcpResponsePtr
LeaseQueryConnection::makeTcpResponse(BlqResponsePtr blq_response) const {
    if (!blq_response) {
        isc_throw(BadValue, "LeaseQueryConnection::makeTcpResponse blq_response cannot be empty");
    }

    // We need the v6 packet in wire form, so pack it.
    blq_response->getResponse()->pack();
    auto buffer = blq_response->getResponse()->getBuffer();
    const uint8_t* data = buffer.getData();
    auto length = buffer.getLength();

    // Create the stream response from the packet data.
    TcpStreamResponsePtr tcp_response(new TcpStreamResponse());
    tcp_response->setResponseData(data, length);

    // Pack the stream response, making it ready to send.
    tcp_response->pack();
    return (tcp_response);
}

bool
LeaseQueryConnection::responseSent(TcpResponsePtr /* response */) {
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        response_to_send_.reset();
    }
    sendNextResponse();
    // Return true if we're sending again, to skip starting idle timer.
    std::lock_guard<std::mutex> lck(responses_mutex_);
    return ((response_to_send_ != 0));
}

BlqQueryPtr
LeaseQueryConnection::unpackQuery4(const uint8_t* data, size_t length) const {
    Pkt4Ptr pkt(new Pkt4(data, length));
    pkt->updateTimestamp();
    auto endpoint = getRemoteEndpoint();
    pkt->setRemoteAddr(IOAddress(endpoint.address()));
    pkt->setRemotePort(endpoint.port());
    pkt->unpack();
    if (pkt->getType() != DHCPBULKLEASEQUERY) {
        LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY4_UNSUPPORTED_MSG_TYPE)
            .arg(getRemoteEndpointAddressAsText())
            .arg(pkt->getName());
        return (BlqQueryPtr());
    }

    return (BlqQueryPtr(new BlqQuery(pkt)));
}

BlqQueryPtr
LeaseQueryConnection::unpackQuery6(const uint8_t* data, size_t length) const {
    Pkt6Ptr pkt(new Pkt6(data, length));
    pkt->updateTimestamp();
    auto endpoint = getRemoteEndpoint();
    pkt->setRemoteAddr(IOAddress(endpoint.address()));
    pkt->setRemotePort(endpoint.port());
    pkt->unpack();
    if (pkt->getType() != DHCPV6_LEASEQUERY) {
        LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY6_UNSUPPORTED_MSG_TYPE)
            .arg(getRemoteEndpointAddressAsText())
            .arg(pkt->getName());
        return (BlqQueryPtr());
    }

    return (BlqQueryPtr(new BlqQuery(pkt)));
}

void
LeaseQueryConnection::startQuery(BlqQueryPtr query) {
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        if (stopping_ || !can_send_) {
            return;
        }
    }
    // Create a BulkLeaseQuery instance
    BulkLeaseQueryPtr bulk_lease_query;
    LeaseQueryConnectionWPtr wptr =
        boost::static_pointer_cast<LeaseQueryConnection>(shared_from_this());
    BlqPostCb post_cb = std::bind(&LeaseQueryConnection::doPost, wptr, ph::_1);
    BlqPushToSendCb push_to_send_cb =
        std::bind(&LeaseQueryConnection::doPushToSend, wptr, ph::_1);
    BlqQueryCompleteCb query_complete_cb =
        std::bind(&LeaseQueryConnection::doQueryComplete, wptr, ph::_1);
    try {
        if (family_ == AF_INET) {
            bulk_lease_query.reset(new BulkLeaseQuery4(query,
                                                       post_cb,
                                                       push_to_send_cb,
                                                       query_complete_cb));
        } else {
            bulk_lease_query.reset(new BulkLeaseQuery6(query,
                                                       post_cb,
                                                       push_to_send_cb,
                                                       query_complete_cb));
        }
    } catch (const lease_query::QueryTerminated&) {
        return;
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY_INVALID_REQUEST)
            .arg(getRemoteEndpointAddressAsText())
            .arg(family_ == AF_INET ?
                 BulkLeaseQuery4::leaseQueryLabel(query) :
                 BulkLeaseQuery6::leaseQueryLabel(query))
            .arg(ex.what());
        stopThisConnection();
        return;
    }

    // Check for early errors.
    if (bulk_lease_query->isProcessed()) {
        return;
    }

    // Add the query to the list of in-progress queries.
    addRunningQuery(bulk_lease_query);

    // Start processing.
    post(std::bind(&BulkLeaseQuery::processStart, bulk_lease_query));
}

BlqQueryPtr
LeaseQueryConnection::popPendingQuery() {
    BlqQueryPtr query =
        boost::dynamic_pointer_cast<BlqQuery>(pending_queries_.pop());
    if (query) {
        LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC,
                  BULK_LEASE_QUERY_DEQUEUED)
            .arg(getRemoteEndpointAddressAsText())
            .arg(BulkLeaseQuery6::leaseQueryLabel(query));
    }
    return (query);
}

void
LeaseQueryConnection::processNextQuery() {
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        if (stopping_ || !can_send_) {
            return;
        }
    }
    // Something to do?
    if (noPendingQuery()) {
        return;
    }
    // Pop and process waiting queries until queue is empty or list full.
    while ((max_concurrent_queries_ == 0) ||
           (max_concurrent_queries_ <= getNumRunningQueries())) {
        BlqQueryPtr query = popPendingQuery();
        if (!query) {
            return;
        }
        startQuery(query);
    }
}

bool
LeaseQueryConnection::pushToSend(BlqResponsePtr response) {
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        if (stopping_ || !can_send_) {
            return (false);
        }
        responses_.push_back(response);
    }
    LeaseQueryConnectionWPtr wptr =
        boost::static_pointer_cast<LeaseQueryConnection>(shared_from_this());
    io_service_->post(std::bind(&LeaseQueryConnection::doSendNextResponse, wptr));
    return (true);
}

void
LeaseQueryConnection::post(const BlqPostCbArg& callback) {
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        if (stopping_ || !can_send_) {
            return;
        }
    }
    io_service_->post([callback]() {
        try {
            callback();
        } catch (const lease_query::QueryTerminated&) {
            return;
        } catch (const std::exception& ex) {
            LOG_ERROR(lease_query_logger,
                      BULK_LEASE_QUERY_PROCESSING_UNEXPECTED_FAILURE)
                .arg(ex.what());
            return;
        }
    });
}

void
LeaseQueryConnection::queryComplete(const Xid& xid) {
    {
        std::lock_guard<std::mutex> lck(responses_mutex_);
        if (stopping_ || !can_send_) {
            return;
        }
    }
    removeRunningQuery(xid);
    processNextQuery();
}

size_t
LeaseQueryConnection::getNumResponses() const {
    std::lock_guard<std::mutex> lck(responses_mutex_);
    return (responses_.size());
}

IOAddress
LeaseQueryConnection::getRequesterAddress() const {
    auto endpoint = getRemoteEndpoint();
    if (endpoint != NO_ENDPOINT()) {
        return (endpoint.address());
    }

    return (family_ == AF_INET ? IOAddress::IPV4_ZERO_ADDRESS()
                               : IOAddress::IPV6_ZERO_ADDRESS());
}

} // end of namespace isc::lease_query
} // end of namespace isc
