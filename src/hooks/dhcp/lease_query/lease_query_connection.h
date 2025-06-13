// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_QUERY_CONNECTION_H
#define LEASE_QUERY_CONNECTION_H

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <dhcp/pkt6.h>
#include <tcp/tcp_listener.h>
#include <tcp/tcp_stream_msg.h>
#include <bulk_lease_query.h>

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/tag.hpp>

namespace isc {
namespace lease_query {

/// @brief Wrapper around a chronological list of queries, uniquely keyed by
/// transaction id.
///
/// New entries are added to the end.  The wrapper uses it's own mutex to
/// ensure thread-safety.
///
/// @tparam QueryType Either @c BlqQuery or @c BulkLeaseQuery type.
template <class QueryType>
class XidQueue {
public:
    /// @brief Type of pointers to QueryType.
    typedef boost::shared_ptr<QueryType> QueryPtrType;

    /// @brief Multi-index container for storing bulk lease queries.
    typedef boost::multi_index_container<
        // It stores pointers to BulkLeaseQuery.
        QueryPtrType,
        boost::multi_index::indexed_by<
            boost::multi_index::sequenced<>,
            boost::multi_index::ordered_unique<
                boost::multi_index::const_mem_fun<QueryType,
                                                  Xid,
                                                  &QueryType::getXid>
            >
        >
    > XidQueueContainer;

    /// @brief Adds a query to the end of the queue.
    ///
    /// @param query Pointer to the query to add.
    void add(QueryPtrType query) {
        std::lock_guard<std::mutex> lck(mutex_);
        queries_.push_back(query);
    }

    /// @brief Pops a query to the beginning of the queue.
    ///
    /// @return The first query of the queue or null when the queue is empty.
    QueryPtrType pop() {
        QueryPtrType query;
        {
            std::lock_guard<std::mutex> lck(mutex_);
            if (!queries_.empty()) {
                query = queries_.front();
                queries_.pop_front();
            }
        }
        return (query);
    }

    /// @brief Empty predicate.
    ///
    /// @return True is the queue is empty, False otherwise.
    bool empty() const {
        std::lock_guard<std::mutex> lck(mutex_);
        return (queries_.empty());
    }

    /// @brief Fetches the number of entries in the queue.
    ///
    /// @return Number of entries in the queue.
    size_t size() const {
        std::lock_guard<std::mutex> lck(mutex_);
        return (queries_.size());
    }

    /// @brief Fetches the query for a given transaction id.
    ///
    /// @param xid Transaction id for which to search.
    ///
    /// @return Pointer to the query if found, an empty pointer otherwise.
    QueryPtrType find(const Xid& xid) const {
        std::lock_guard<std::mutex> lck(mutex_);
        return (findInternal(xid));
    }

    /// @brief Removes a query from the queue for a given transaction id.
    ///
    /// @param xid Transaction id for which to search.
    void remove(const Xid& xid) {
        auto& xid_index = queries_.template get<1>();
        auto query = xid_index.find(xid);
        if (query != xid_index.end()) {
            xid_index.erase(query);
        }
    }

    /// @brief Removes all queries from the queue.
    void clear() {
        std::lock_guard<std::mutex> lck(mutex_);
        queries_.clear();
    }

private:
    /// @brief Fetches the query for a given transaction id.
    ///
    /// Internal version which does not the mutex.
    ///
    /// @param xid Transaction id for which to search.
    ///
    /// @return Pointer to the query if found, an empty pointer otherwise.
    QueryPtrType findInternal(const Xid& xid) const {
        auto const& xid_index = queries_.template get<1>();
        auto const query = xid_index.find(xid);
        if (query != xid_index.end()) {
            return (*query);
        }
        return (QueryPtrType());
    }

    /// @brief Container that houses the queries.
    XidQueueContainer queries_;

    /// @brief Mutex used for protect queue integrity.
    mutable std::mutex mutex_;
};

/// @brief Forward declaration of LeaseQueryConnection.
class LeaseQueryConnection;

/// @brief Defines a shared pointer to a LeaseQueryConnection.
typedef boost::shared_ptr<LeaseQueryConnection> LeaseQueryConnectionPtr;

/// @brief Defines a weak pointer to a LeaseQueryConnection.
typedef boost::weak_ptr<LeaseQueryConnection> LeaseQueryConnectionWPtr;

/// @brief Derivation of TcpConnection used for Bulk LeaseQuery.
class LeaseQueryConnection : public tcp::TcpConnection {
public:
    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the connection.
    /// @param acceptor Pointer to the TCP acceptor object used to listen for
    /// new TCP connections.
    /// @param tls_context TLS context.
    /// @param connection_pool Connection pool in which this connection is
    /// stored.
    /// @param acceptor_callback Callback invoked when new connection is accepted.
    /// @param filter_callback Callback invoked prior to handshake
    /// which can be used to qualify and reject connections.
    /// @param idle_timeout Timeout after which a TCP connection is
    /// closed by the server.
    /// @param family Protocol family, AF_INET or AF_INET6.
    /// @param max_concurrent_queries Maximum number of in-progress queries allowed.
    /// @param read_max maximum size of a single socket read. Defaults to 32K.
    LeaseQueryConnection(const asiolink::IOServicePtr& io_service,
                         const tcp::TcpConnectionAcceptorPtr& acceptor,
                         const asiolink::TlsContextPtr& tls_context,
                         tcp::TcpConnectionPool& connection_pool,
                         const tcp::TcpConnectionAcceptorCallback& acceptor_callback,
                         const tcp::TcpConnectionFilterCallback& filter_callback,
                         const long idle_timeout,
                         const uint16_t family,
                         const size_t max_concurrent_queries,
                         const size_t read_max = 32768);

    /// @brief Destructor.
    virtual ~LeaseQueryConnection() {
    }

    /// @brief Shutdown the socket.
    virtual void shutdown();

    /// @brief Closes the socket.
    virtual void close();

    /// @brief Stops current connection.
    ///
    /// Enforce sequencing with response sending.
    virtual void stopThisConnection();

    /// @brief Stopping flag.
    ///
    /// @return True if the connection is and will be stopped,
    /// False otherwise.
    bool isStopping() const {
        return (stopping_);
    }

    /// @brief Can send (aka stopped) flag.
    ///
    /// @return True if the connection can be used to send a response,
    /// False otherwise i.e. the connection was shutdown or closed.
    bool canSend() const {
        return (can_send_);
    }

    /// @brief Creates a new empty request ready to receive data.
    ///
    /// @return A new empty request.
    virtual tcp::TcpRequestPtr createRequest();

    /// @brief Sends the next response in the response queue.
    ///
    /// If there is currently no send in progress and there are
    /// entries in the response queue, it dequeues a response from
    /// the front of the queue and initiates an asynchronous send.
    virtual void sendNextResponse();

    /// @brief Class/static version of sendNextResponse.
    ///
    /// @param wptr Weak pointer to a lease query connection.
    static void doSendNextResponse(LeaseQueryConnectionWPtr wptr) {
        LeaseQueryConnectionPtr ptr = wptr.lock();
        if (!ptr) {
            return;
        }
        ptr->sendNextResponse();
    }

    /// @brief Constructs a ready to send TcpResponse from and BlqResponse.
    ///
    /// @param blq_response Pointer to the source BlqResponse, cannot be empty.
    /// @return A pointer to a TcpResponse.
    /// @throw BadValue if the input pointer is empty.
    tcp::TcpResponsePtr makeTcpResponse(BlqResponsePtr blq_response) const;

    /// @brief Processes a response once it has been sent.
    ///
    /// @param response Response that was sent to the remote endpoint.
    /// @return Always true, signifying that the connection should start
    /// the idle timer.
    virtual bool responseSent(tcp::TcpResponsePtr response);

    /// @brief Processes a completely received request.
    ///
    /// This function is invoked when the connection has completely received
    /// a TCP stream request message and performs the following:
    ///  - The stream request wire data is unpacked into a family-specific
    ///  bulk lease query message.
    ///  - the bulk lease query is processed or queued.
    ///
    /// @param request Request to process.
    virtual void requestReceived(tcp::TcpRequestPtr request);

    /// @brief Unpacks a DHCPv4 packet from a data buffer.
    ///
    /// @param buffer Buffer containing the packed DHCPv4 packet.
    /// @param length Number of bytes in contained in the buffer.
    ///
    /// @return A BlqQueryPtr containing the unpacked DHCPv4 packet.
    BlqQueryPtr unpackQuery4(const uint8_t* buffer, size_t length) const;

    /// @brief Unpacks a DHCPv6 packet from a data buffer.
    ///
    /// @param buffer Buffer containing the packed DHCPv6 packet.
    /// @param length Number of bytes in contained in the buffer.
    ///
    /// @return A BlqQueryPtr containing the unpacked DHCPv6 packet.
    BlqQueryPtr unpackQuery6(const uint8_t* buffer, size_t length) const;

    /// @brief Start query processing.
    ///
    /// A new BulkLeaseQuery instance is created and started.
    ///
    /// @param query_msg Query message to process.
    void startQuery(BlqQueryPtr query_msg);

    /// @brief Adds a query to the end of the list of in-progress queries.
    ///
    /// @param query Query to add.
    void addRunningQuery(BulkLeaseQueryPtr query) {
        running_queries_.add(query);
    }

    /// @brief Returns the number of queries in the in-progress list.
    size_t getNumRunningQueries() const {
        return (running_queries_.size());
    }

    /// @brief Removes a query from the in-progress query list.
    ///
    /// @param xid Xid of the query to remove.
    void removeRunningQuery(const Xid& xid) {
        running_queries_.remove(xid);
    }

    /// @brief Find queries based on Xid in the query list and queue.
    ///
    /// @param xid Xid of the query to find.
    /// @return True if there is a query with the Xid in the in-progress
    // query list or waiting query queue, False otherwise.
    bool findQuery(const Xid& xid) const {
        return (running_queries_.find(xid) || pending_queries_.find(xid));
    }

    ///  @brief Queues a query to the end of the queue of waiting queries.
    ///
    /// @param query Query to queue.
    void addPendingQuery(BlqQueryPtr query) {
        pending_queries_.add(query);
    }

    /// @brief Returns True if the queue of waiting queries is empty.
    bool noPendingQuery() const {
        return (pending_queries_.empty());
    }

    /// @brief Pops a query from the queue of waiting queries.
    BlqQueryPtr popPendingQuery();

    /// @brief Process next waiting query.
    virtual void processNextQuery();

    /// @brief Adds a response to the connection's outbound queue of responses.
    ///
    /// @param response Pointer to the response to send.
    /// @return True if the response can be sent, False otherwise.
    virtual bool pushToSend(BlqResponsePtr response);

    /// @brief Class/static version of pushToSend.
    ///
    /// @param wptr Weak pointer to a lease query connection.
    /// @param response Pointer to the response to send.
    /// @return True if the response can be sent, False otherwise.
    static bool doPushToSend(LeaseQueryConnectionWPtr wptr,
                             BlqResponsePtr response) {
        LeaseQueryConnectionPtr ptr = wptr.lock();
        if (!ptr) {
            return (false);
        }
        return (ptr->pushToSend(response));
    }

    /// @brief Posts an event callback to the connection's IOService.
    ///
    /// @param callback The callback to post.
    virtual void post(const BlqPostCbArg& callback);

    /// @brief Class/static version of post.
    ///
    /// @param wptr Weak pointer to a lease query connection.
    /// @param callback The callback to post.
    static void doPost(LeaseQueryConnectionWPtr wptr,
                       const BlqPostCbArg& callback) {
        LeaseQueryConnectionPtr ptr = wptr.lock();
        if (!ptr) {
            return;
        }
        ptr->post(callback);
    }

    /// @brief Finishes up when a query has been completed (e.g. reached
    /// EOF, failed, was terminated)
    ///
    /// @param xid Xid of the query that has finished.
    virtual void queryComplete(const Xid& xid);

    /// @brief Class/static version of queryComplete.
    ///
    /// @param wptr Weak pointer to a lease query connection.
    /// @param xid Xid of the query that has finished.
    static void doQueryComplete(LeaseQueryConnectionWPtr wptr, const Xid& xid) {
        LeaseQueryConnectionPtr ptr = wptr.lock();
        if (!ptr) {
            return;
        }
        ptr->queryComplete(xid);
    }

    /// @brief Returns the number of responses in the response queue.
    size_t getNumResponses() const;

    /// @brief Returns the requester's ip address.
    asiolink::IOAddress getRequesterAddress() const;

    /// @brief Export getRemoteEndpointAddressAsText.
    using tcp::TcpConnection::getRemoteEndpointAddressAsText;

protected:
    /// @brief Protocol family AF_INET or AF_INET6.
    uint16_t family_;

    /// @brief IOService that drives the connection events.
    asiolink::IOServicePtr io_service_;

    /// @brief Stopping flag.
    bool stopping_;

    /// @brief Can send flag.
    bool can_send_;

    /// @brief List of in-process queries.
    XidQueue<BulkLeaseQuery> running_queries_;

    /// @brief Queue of queries waiting to enter processing.
    ///
    /// When the in-process query list is full (size >= maximum),
    /// received queries are queued. When a query was processed
    /// a queued query is popped and processed.
    XidQueue<BlqMsg> pending_queries_;

    /// @brief List of responses waiting to be sent.
    BlqResponseList responses_;

    /// @brief Mutex used to lock during responses access.
    mutable std::mutex responses_mutex_;

    /// @brief Tracks the response currently being sent.
    BlqResponsePtr response_to_send_;

    /// @brief Maximum number of concurrent queries allowed. Zero means
    /// unlimited.
    size_t max_concurrent_queries_;
};

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // LEASE_QUERY_CONNECTION_H
