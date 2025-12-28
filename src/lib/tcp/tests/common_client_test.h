// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMON_CLIENT_TEST_H
#define COMMON_CLIENT_TEST_H

using namespace isc;
using namespace isc::asiolink;
using namespace isc::tcp;
using namespace isc::util;
namespace ph = std::placeholders;

namespace isc {
namespace tcp {
namespace test {

/// @brief IP address to which TCP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief IPv6 address to whch TCP service is bound.
const std::string IPV6_SERVER_ADDRESS = "::1";

/// @brief Port number to which TCP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Persistent connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in tests where idle connections
/// are tested (ms).
const long SHORT_IDLE_TIMEOUT = 200;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Completion checker.
///
/// Messages are by 2 byte length header and data of this length.
///
/// @param response Response to check.
/// @param error_msg Reference to the error message.
/// @return status (0 not complete, > 0 complete, < 0 error).
int TestCompleteCheck(const WireDataPtr& response, std::string& error_msg);

/// @brief Derivation of TcpResponse used for testing.
class TcpTestResponse : public TcpResponse {
public:
    /// @brief Constructor.
    TcpTestResponse(const WireData& data) {
        wire_data_ = data;
    }

    /// Destructor.
    virtual ~TcpTestResponse() = default;

    /// @brief Packs the response content into wire data buffer.
    virtual void pack() {
    }
};

/// @brief Defines a smart pointer to a TcpTestResponse.
typedef boost::shared_ptr<TcpTestResponse> TcpTestResponsePtr;

/// @brief Derivation of TcpConnection used for testing.
class TcpTestConnection : public TcpConnection {
public:
    /// @brief Constructor.
    TcpTestConnection(const IOServicePtr& io_service,
                      const TcpConnectionAcceptorPtr& acceptor,
                      const TlsContextPtr& tls_context,
                      TcpConnectionPool& connection_pool,
                      const TcpConnectionAcceptorCallback& acceptor_callback,
                      const TcpConnectionFilterCallback& filter_callback,
                      const long idle_timeout)
     : TcpConnection(io_service, acceptor, tls_context, connection_pool,
                     acceptor_callback, filter_callback, idle_timeout) {
    }

    /// @brief Creates a new empty request ready to receive data.
    virtual TcpRequestPtr createRequest() {
        return (TcpStreamRequestPtr(new TcpStreamRequest()));
    }

    /// @brief Processes a completely received request.
    ///
    /// Forms and sends a response.
    ///
    /// @param request Request to process.
    virtual void requestReceived(TcpRequestPtr request) {
        TcpStreamRequestPtr stream_req = boost::dynamic_pointer_cast<TcpStreamRequest>(request);
        if (!stream_req) {
            isc_throw(isc::Unexpected, "request not a TcpStreamRequest");
        }

        // Unpack the request.
        stream_req->unpack();
        std::string request_str = stream_req->getRequestString();

        // Create the response.
        std::string response_str;

        if (request_str.find("Malformed", 0) != std::string::npos) {
            TcpTestResponsePtr response;
            WireData bad = { 0, 0, 0, 0 };
            response.reset(new TcpTestResponse(bad));
            asyncSendResponse(response);
            return;
        } else if (request_str.find("Partial", 0) != std::string::npos) {
            TcpTestResponsePtr response;
            WireData bad = { 1, 0, 0, 0 };
            response.reset(new TcpTestResponse(bad));
            asyncSendResponse(response);
            return;
        } else if (request_str.find("Large", 0) != std::string::npos) {
            response_str.resize(0xffff);
        } else if (request_str.size() > 60000) {
            response_str = "large!";
        } else {
            response_str = request_str;
        }
        std::ostringstream os;


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
    /// Returns true, signifying that the connection should start
    /// the idle timer.
    ///
    /// @param response Response that was sent to the remote endpoint.
    virtual bool responseSent(TcpResponsePtr response) {
        return (true);
    }
};

/// @brief Defines a shared pointer to a TcpTestConnection.
typedef boost::shared_ptr<TcpTestConnection> TcpTestConnectionPtr;

/// @brief Implementation of the TCPListener used in tests.
///
/// Implements simple stream in/out listener.
class TcpTestListener : public TcpListener {
public:
    /// @brief Constructor
    TcpTestListener(const IOServicePtr& io_service,
                    const IOAddress& server_address,
                    const unsigned short server_port,
                    const TlsContextPtr& tls_context,
                    const IdleTimeout& idle_timeout,
                    const TcpConnectionFilterCallback& filter_callback = 0,
                    const size_t read_max = 32 * 1024)
        : TcpListener(io_service, server_address, server_port,
                      tls_context, idle_timeout, filter_callback),
          read_max_(read_max) {
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
        return(createTestConnection(acceptor_callback, connection_filter));
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
            const TcpConnectionFilterCallback& connection_filter) {
        TcpTestConnectionPtr conn(new TcpTestConnection(io_service_,
                                                        acceptor_,
                                                        tls_context_,
                                                        connections_,
                                                        acceptor_callback,
                                                        connection_filter,
                                                        idle_timeout_));
        conn->setReadMax(read_max_);
        return (conn);
    }

    /// @brief Maximum size of a single socket read
    size_t read_max_;
};

/// @brief Defines a pointer to a TcpTestListener.
typedef boost::shared_ptr<TcpTestListener> TcpTestListenerPtr;

}
}
}
#endif // COMMON_CLIENT_TEST_H
