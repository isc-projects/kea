// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef TCP_TEST_LISTENER_H
#define TCP_TEST_LISTENER_H

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <tcp/tcp_listener.h>
#include <tcp_test_client.h>

#include <gtest/gtest.h>

#include <sstream>

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::tcp;

/// @brief Describes stream message sent over a connection.
class AuditEntry {
public:
    enum Direction {
        INBOUND,  // data received
        OUTBOUND  // data sent
    };

    /// @brief Constructor
    ///
    /// @param connection_id Id of the client to whom the entry pertains
    /// @param direction INBOUND for data received, OUTBOUND for data sent
    /// @param data string form of the data involved
    AuditEntry(size_t connection_id,
               const AuditEntry::Direction& direction,
               const std::string& data)
        : connection_id_(connection_id), direction_(direction), data_(data) {
    }

    /// @brief Equality operator.
    ///
    /// @param other value to be compared.
    bool operator==(const AuditEntry& other) const {
        return ((connection_id_ == other.connection_id_) &&
                (direction_ == other.direction_) &&
                (data_ == other.data_));
    }

    /// @brief Unique client identifier.
    size_t connection_id_;

    /// @brief Indicates which direction the data traveled
    Direction direction_;

    /// @brief Contains the data sent or received.
    std::string data_;
};

std::ostream&
operator<<(std::ostream& os, const AuditEntry& entry);

/// @brief Contains the data receipt/transmission history for an arbitrary
/// number of connections.
class AuditTrail {
public:
    /// @brief Adds an entry to the audit trail.
    ///
    /// @param connection_id Id of the client to whom the entry pertains
    /// @param direction INBOUND for data received, OUTBOUND for data sent
    /// @param data string form of the data involved
    void addEntry(size_t connection_id,
                  const AuditEntry::Direction& direction,
                  const std::string& data) {
        std::unique_lock<std::mutex> lck(mutex_);
        entries_.push_back(AuditEntry(connection_id, direction, data));
    }

    /// @brief Returns a list of AuditEntry(s) for a given connection.
    ///
    /// @param connection_id Id of the desired connection
    /// @return A list of entries for the connection or an empty list if none are found.
    std::list<AuditEntry> getConnectionTrail(size_t connection_id) {
        std::unique_lock<std::mutex> lck(mutex_);
        std::list<AuditEntry> conn_entries;
        for (auto entry : entries_) {
            if (entry.connection_id_ == connection_id) {
                conn_entries.push_back(entry);
            }
        }

        return (conn_entries);
    }

    /// @brief Dumps the audit trail as a string.
    std::string dump() {
        std::unique_lock<std::mutex> lck(mutex_);
        std::stringstream ss;
        for (auto entry : entries_) {
            ss << entry << std::endl;
        }

        return (ss.str());
    }

    /// @brief Contains the audit entries.
    std::list<AuditEntry> entries_;

    /// @brief Mutex used to lock during access.
    std::mutex mutex_;
};

/// @brief Defines a pointer to an AuditTrail
typedef boost::shared_ptr<AuditTrail> AuditTrailPtr;

/// @brief Derivation of TcpConnection used for testing.
class TcpTestConnection : public TcpConnection {
public:
    typedef std::function<std::string(const std::string&)> ResponseHandler;

    /// @brief Constructor
    TcpTestConnection(IOService& io_service,
                      const TcpConnectionAcceptorPtr& acceptor,
                      const TlsContextPtr& tls_context,
                      TcpConnectionPool& connection_pool,
                      const TcpConnectionAcceptorCallback& acceptor_callback,
                      const TcpConnectionFilterCallback& filter_callback,
                      const long idle_timeout,
                      size_t connection_id,
                      AuditTrailPtr audit_trail,
                      ResponseHandler response_handler)
     : TcpConnection(io_service, acceptor, tls_context, connection_pool,
                     acceptor_callback, filter_callback, idle_timeout),
                     connection_id_(connection_id), audit_trail_(audit_trail),
                     response_handler_(response_handler) {
    }

    /// @brief Creates a new empty request ready to receive data.
    virtual TcpRequestPtr createRequest() {
        return (TcpStreamRequestPtr(new TcpStreamRequest()));
    }

    /// @brief Processes a completely received request.
    ///
    /// Adds the request to the audit trail, then forms and sends a response.
    /// If the request is "I am done", the response is "good bye" which should
    /// instruct the client to disconnect.
    ///
    /// @param request Request to process.
    virtual void requestReceived(TcpRequestPtr request) {
        TcpStreamRequestPtr stream_req = boost::dynamic_pointer_cast<TcpStreamRequest>(request);
        if (!stream_req) {
            isc_throw(isc::Unexpected, "request not a TcpStreamRequest");
        }

        // Unpack the request and add it to the audit trail.
        stream_req->unpack();
        auto request_str = stream_req->getRequestString();
        audit_trail_->addEntry(connection_id_, AuditEntry::INBOUND, request_str);

        // Create the response.
        std::string response_str;

        // If there's a response handler, use it
        if (response_handler_) {
            response_str = response_handler_(request_str);
        } else {
            std::ostringstream os;
            if (request_str.find("I am done", 0) != std::string::npos) {
                os << "good bye";
            } else {
                os << "echo " << request_str;
            }

            response_str = os.str();
        }

        // Ship the response if it's not empty.
        TcpStreamResponsePtr response;
        if (!response_str.empty()) {
            response.reset(new TcpStreamResponse());
            response->setResponseData(response_str);
            response->pack();
            asyncSendResponse(response);
        }
    }

    /// @brief Processes a response once it has been sent.
    ///
    /// Adds the response to the audit trail and returns true, signifying
    /// that the connection should start the idle timer.
    ///
    /// @param response Response that was sent to the remote endpoint.
    virtual bool responseSent(TcpResponsePtr response) {
        TcpStreamResponsePtr resp = boost::dynamic_pointer_cast<TcpStreamResponse>(response);
        if (!resp) {
            isc_throw(isc::Unexpected, "resp not a TcpStreamResponse");
        }

        audit_trail_->addEntry(connection_id_, AuditEntry::OUTBOUND, resp->getResponseString());
        return (true);
    }

    /// @brief Set the response handler
    ///
    /// Sets the response handler invoked by requestReceived.
    ///
    /// @param response_handler Handler function to invoke
    void setResponseHandler(ResponseHandler response_handler) {
        response_handler_ = response_handler;
    };

private:
    /// @brief Id of this connection.
    size_t connection_id_;

    /// @brief Provides request/response history.
    AuditTrailPtr audit_trail_;

    /// @brief Reponse handler to pass into each connection.
    ResponseHandler response_handler_;
};

/// @brief Defines a shared pointer to a TcpTestConnection.
typedef boost::shared_ptr<TcpTestConnection> TcpTestConnectionPtr;

/// @brief Implementation of the TCPListener used in tests.
///
/// Implements simple stream in/out listener.
class TcpTestListener : public TcpListener {
public:
    /// @brief Constructor
    TcpTestListener(IOService& io_service,
                    const IOAddress& server_address,
                    const unsigned short server_port,
                    const TlsContextPtr& tls_context,
                    const IdleTimeout& idle_timeout,
                    const TcpConnectionFilterCallback& filter_callback = 0,
                    const size_t read_max = 32 * 1024)
        : TcpListener(io_service, server_address, server_port,
                      tls_context, idle_timeout, filter_callback),
                      read_max_(read_max), next_connection_id_(0),
                      audit_trail_(new AuditTrail()) {
    }

protected:
    /// @brief Creates an instance of the @c TcpConnection.
    ///
    /// @param callback Callback invoked when new connection is accepted.
    /// @param connection_filter Callback invoked during connection acceptance
    /// that can allow or deny connections based on the remote endpoint.
    /// @return Pointer to the created connection.
    virtual TcpConnectionPtr createConnection(
            const TcpConnectionAcceptorCallback& acceptor_callback,
            const TcpConnectionFilterCallback& connection_filter) {
        return(createTestConnection(acceptor_callback, connection_filter, response_handler_));
    }

    /// @brief Creates an instance of the @c TcpTestConnection.
    ///
    /// @param acceptor_callback Callback invoked when new connection is accepted.
    /// @param connection_filter Callback invoked during connection acceptance
    /// that can allow or deny connections based on the remote endpoint.
    /// @param callback invoked by requestReceived() to build a response
    ///
    /// @return Pointer to the created connection.
    virtual TcpTestConnectionPtr createTestConnection(
            const TcpConnectionAcceptorCallback& acceptor_callback,
            const TcpConnectionFilterCallback& connection_filter,
            TcpTestConnection::ResponseHandler response_handler) {
        TcpTestConnectionPtr conn(new TcpTestConnection(io_service_,
                                                        acceptor_,
                                                        tls_context_,
                                                        connections_,
                                                        acceptor_callback,
                                                        connection_filter,
                                                        idle_timeout_,
                                                        ++next_connection_id_,
                                                        audit_trail_,
                                                        response_handler));
        conn->setReadMax(read_max_);
        return (conn);
    }

    /// @brief Maximum size of a single socket read
    size_t read_max_;

    /// @brief Id to use for the next connection.
    size_t next_connection_id_;

    /// @brief Callback connection invokes in requestReceived to construct a response.
    TcpTestConnection::ResponseHandler response_handler_;

public:

    /// @brief Set the response handler
    ///
    /// Sets the response handler invoked by requestReceived.
    ///
    /// @param response_handler Handler function to invoke
    void setResponseHandler(TcpTestConnection::ResponseHandler response_handler) {
        response_handler_ = response_handler;
    };


    /// @brief Tracks the input/output history of all connections.
    AuditTrailPtr audit_trail_;
};

/// @brief Defines a pointer to a TcpTestListener.
typedef boost::shared_ptr<TcpTestListener> TcpTestListenerPtr;

#endif // TCP_TEST_LISTENER_H
