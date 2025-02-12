// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_QUERY_TEST_CLIENT_H
#define LEASE_QUERY_TEST_CLIENT_H

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcp/pkt.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <lease_query_connection.h>
#include <boost/asio/read.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <gtest/gtest.h>

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::tcp;
using namespace isc::lease_query;

/// @brief Entity which can connect to a LeaseQuery TCP server endpoint.
class LeaseQueryTestClient : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates new socket instance. It doesn't connect. Call
    /// connect() to connect to the server.
    ///
    /// @param io_service IO service to be stopped on error or completion.
    /// @param server_address string containing the IP address of the server.
    /// @param port port number of the server.
    explicit LeaseQueryTestClient(const IOServicePtr& io_service,
                                  std::function<void()> done_callback,
                                  uint16_t family,
                                  const std::string& server_address = "127.0.0.1",
                                  uint16_t port = 18123)
        : io_service_(io_service), socket_(io_service_->getInternalIOService()), buf_(),
          response_(), done_callback_(done_callback), family_(family),
          server_address_(server_address), server_port_(port),
          receive_done_(false), expected_eof_(true), next_xid_(76) {
    }

    /// @brief Destructor.
    ///
    /// Closes the underlying socket if it is open.
    virtual ~LeaseQueryTestClient() {
        close();
    }

    /// @brief Connect to the listener.
    ///
    /// @param request request string to send.
    void connect() {
        tcp::endpoint endpoint(make_address(server_address_), server_port_);
        socket_.async_connect(endpoint,
        [this](const boost::system::error_code& ec) {
            receive_done_ = false;
            expected_eof_ = false;
            if (ec) {
                // One would expect that async_connect wouldn't return
                // EINPROGRESS error code, but simply wait for the
                // connection to get established before the handler is
                // invoked. It turns out, however, that on some OSes
                // the connect handler may receive this error code
                // which doesn't necessarily indicate a problem.
                // Making an attempt to write and read from this
                // socket will typically succeed. So, we ignore this error.
                if (ec.value() != boost::asio::error::in_progress) {
                    ADD_FAILURE() << "error occurred while connecting: "
                                  << ec.message();
                    done_callback_();
                    return;
                }
            }
        });
    }

    /// @brief Creates a client connection and sends the given request.
    ///
    /// @param request BlqQuery containing the request to send. If the
    /// request is empty, the client will expect the server to idle
    /// timeout the connection.
    void startRequest(BlqQueryPtr request) {

        tcp::endpoint endpoint(make_address(server_address_), server_port_);
        socket_.async_connect(endpoint,
        [this, request](const boost::system::error_code& ec) {
            receive_done_ = false;
            expected_eof_ = false;
            if (ec) {
                // One would expect that async_connect wouldn't return
                // EINPROGRESS error code, but simply wait for the
                // connection to get established before the handler is
                // invoked. It turns out, however, that on some OSes
                // the connect handler may receive this error code
                // which doesn't necessarily indicate a problem.
                // Making an attempt to write and read from this
                // socket will typically succeed. So, we ignore this error.
                if (ec.value() != boost::asio::error::in_progress) {
                    ADD_FAILURE() << "error occurred while connecting: "
                                  << ec.message();
                    done_callback_();
                    return;
                }
            }

            if (!request) {
                waitForEof();
            } else {
                sendRequest(request);
            }
        });
    }

    /// @brief Creates a client connection and sends a list of requests.
    ///
    /// The client will work its way through the list of requests, waiting
    /// for a response after each request before sending the next.  Once
    /// the list of requests is exhausted the client calls the done callback.
    ///
    /// @param requests a list BlqQuerys to send.
    void startRequests(const std::list<BlqQueryPtr>& requests) {
        requests_to_send_ = requests;

        tcp::endpoint endpoint(make_address(server_address_), server_port_);
        socket_.async_connect(endpoint,
        [this](const boost::system::error_code& ec) {
            receive_done_ = false;
            expected_eof_ = false;
            if (ec) {
                // One would expect that async_connect wouldn't return
                // EINPROGRESS error code, but simply wait for the
                // connection to get established before the handler is
                // invoked. It turns out, however, that on some OSes
                // the connect handler may receive this error code
                // which doesn't necessarily indicate a problem.
                // Making an attempt to write and read from this
                // socket will typically succeed. So, we ignore this error.
                if (ec.value() != boost::asio::error::in_progress) {
                    ADD_FAILURE() << "error occurred while connecting: "
                                  << ec.message();
                    done_callback_();
                    return;
                }
            }

            sendNextRequest();
        });
    }

    /// @brief Sends the next request from the list of requests to send.
    void sendNextRequest() {
        // If there are any requests left to send, send them.
        if (!requests_to_send_.empty()) {
            BlqQueryPtr request = requests_to_send_.front();
            requests_to_send_.pop_front();
            sendRequest(request);
        }
    }

    /// @brief Send query request.
    ///
    /// @param request query to send
    /// @param send_length  number of bytes to send.  If not zero, can be used
    /// to truncate the amount of data sent.
    void sendRequest(BlqQueryPtr request, const size_t send_length = 0) {
        if (!request) {
            return;
        }

        // Set the transaction id.
        request->getQuery()->setTransid(++next_xid_);

        // Pack it.
        request->pack();
        auto size = request->getWireSize();
        ASSERT_TRUE(size);
        WireData& wire_data = request->getWireData();

        // Keep track of the request we are sending.
        request_in_send_ = request;

        // Ship it.
        sendPartialRequest(wire_data, (send_length ? send_length : size));
    }

    /// @brief Wait for a server to close the connection.
    void waitForEof() {
        stream_response_.reset(new TcpStreamRequest());
        receivePartialResponse(true);
    }

    /// @brief Send part of the request.
    ///
    /// @param request part of the request to be sent.
    /// @param send_length  number of bytes to send.  If not zero, can be used
    /// to truncate the amount of data sent.
    void sendPartialRequest(WireData& wire_request, size_t send_length = 0) {
        if (!send_length) {
            send_length = wire_request.size();
        } else {
            ASSERT_LE(send_length, wire_request.size())
                      << "broken test, send_length exceeds wire size";
        }

        socket_.async_send(boost::asio::buffer(wire_request.data(), send_length),
                           [this, wire_request]
                               (const boost::system::error_code& ec,
                                size_t bytes_transferred) mutable {
            if (ec) {
                if (ec.value() == boost::asio::error::operation_aborted) {
                    return;

                } else if ((ec.value() == boost::asio::error::try_again) ||
                           (ec.value() == boost::asio::error::would_block)) {
                    // If we should try again make sure there is no
                    // garbage in the bytes_transferred.
                    bytes_transferred = 0;

                } else {
                    ADD_FAILURE() << "error occurred while connecting: "
                                  << ec.message();
                    done_callback_();
                    return;
                }
            }

            // Remove the part of the request which has been sent.
            if (bytes_transferred > 0 && (wire_request.size() <= bytes_transferred)) {
                wire_request.erase(wire_request.begin(), wire_request.begin() + bytes_transferred);
            }

            // Continue sending request data if there are still some
            // to be sent.
            if (!wire_request.empty()) {
                sendPartialRequest(wire_request);
            } else {
                // Request has been sent. Start receiving response.
                requests_sent_.push_back(request_in_send_);
                request_in_send_.reset();
                receivePartialResponse();
            }
       });
    }

    /// @brief Receive response from the server.
    void receivePartialResponse(bool expect_eof = false) {
        socket_.async_read_some(boost::asio::buffer(buf_.data(), buf_.size()),
                                [this, expect_eof]
                                    (const boost::system::error_code& ec,
                                     size_t bytes_transferred) {
            if (!stream_response_) {
                stream_response_.reset(new TcpStreamRequest());
            }

            if (ec) {
                // IO service stopped so simply return.
                if (ec.value() == boost::asio::error::operation_aborted) {
                    return;
                } else if ((ec.value() == boost::asio::error::try_again) ||
                           (ec.value() == boost::asio::error::would_block)) {
                    // If we should try again, make sure that there is
                    // no garbage in the bytes_transferred.
                    bytes_transferred = 0;
                } else if (ec.value() == boost::asio::error::eof && expect_eof)  {
                    expected_eof_ = true;
                    done_callback_();
                    return;
                } else {
                    // Error occurred, bail...
                    ADD_FAILURE() << "client: " << this
                                  << " error occurred while receiving TCP"
                                  << " response from the server: "
                                  << ec.message();
                    done_callback_();
                    return;
                }
            }

            // Post received data to the current response.
            if (bytes_transferred > 0) {
                stream_response_->postBuffer(buf_.data(), bytes_transferred);
            }

            if (stream_response_->needData()) {
                // Response is incomplete, keep reading.
                receivePartialResponse();
            } else {
                // Response is complete, process it.
                responseReceived();
            }
        });
    }

    /// @brief Process a completed response received from the server.
    virtual void responseReceived() {
        /// Unpack wire data.
        ASSERT_NO_THROW(stream_response_->unpack());
        PktPtr response;

        if (family_ == AF_INET) {
            // Now! create a Pkt4 from the wire data and unpack it.
            response.reset(new Pkt4(stream_response_->getRequest(),
                                    stream_response_->getRequestSize()));
            response->unpack();
        } else {
            // Now! create a Pkt6 from the wire data and unpack it.
            response.reset(new Pkt6(stream_response_->getRequest(),
                                    stream_response_->getRequestSize()));
            response->unpack();
        }

        responses_received_.push_back(BlqResponsePtr(new BlqResponse(response)));

        // For now we'll quit if there's nothing left to send
        // we'll need to be more sophisticated later, like checking
        // for query done or error AND nothing left to send ...
        if (requests_to_send_.empty()) {
            receive_done_ = true;
            done_callback_();
            return;
        }

        // Clear out for the next one.
        stream_response_.reset();
        sendNextRequest();
    }

    /// @brief Close connection.
    void close() {
        socket_.close();
    }

    /// @brief Returns true if the receive completed without error.
    ///
    /// @return True if the receive completed successfully, false otherwise.
    bool receiveDone() {
        return (receive_done_);
    }

    /// @brief Returns true if the receive ended with expected EOF.
    ///
    /// @return True if the receive ended with EOF, false otherwise.
    bool expectedEof() {
        return (expected_eof_);
    }

    /// @brief Returns the list of received responses.
    ///
    /// @return list of string responses.
    const std::list<BlqResponsePtr>& getResponses() {
        return (responses_received_);
    }

    /// @brief Returns the next transaction id value to use.
    Xid getNextXid() const {
        return (next_xid_);
    }

    /// @brief Basic check of the list of responses received against
    /// the list of requests sent.
    void checkResponses() {
        ASSERT_EQ(responses_received_.size(), requests_sent_.size());
        if (family_ == AF_INET) {
            checkResponses4();
        } else {
            checkResponses6();
        }
    }

private:

    /// @brief Basic check of the list of responses (v4).
    ///
    /// Each request is expected to be a DHCPBULKLEASEQUERY, each response is
    /// expected to be DHCPLEASEQUERYDONE whose xid matches the corresponding
    /// request.
    void checkResponses4() {
        auto response = responses_received_.begin();
        for (auto const& request : requests_sent_) {
            EXPECT_EQ(DHCPBULKLEASEQUERY, request->getQuery()->getType());
            EXPECT_EQ(DHCPLEASEQUERYDONE, (*response)->getResponse()->getType());
            EXPECT_EQ(request->getXid(), (*response)->getXid());
            ++response;
        }
    }

    /// @brief Basic check of the list of responses (v6).
    ///
    /// Each request is expected to be a DHCPV6_LEASEQUERY, each response is
    /// expected to be DHCPV6_LEASEQUERY_REPLY whose xid matches the
    /// corresponding request.
    void checkResponses6() {
        auto response = responses_received_.begin();
        for (auto const& request : requests_sent_) {
            EXPECT_EQ(DHCPV6_LEASEQUERY, request->getQuery()->getType());
            EXPECT_EQ(DHCPV6_LEASEQUERY_REPLY, (*response)->getResponse()->getType());
            EXPECT_EQ(request->getXid(), (*response)->getXid());
            ++response;
        }
    }

    /// @brief Holds reference to the IO service.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief A socket used for the connection.
    boost::asio::ip::tcp::socket socket_;

    /// @brief Buffer into which response is written.
    std::array<char, 8192> buf_;

    /// @brief Response in the textual format.
    std::string response_;

    /// @brief Callback to invoke when the client has finished its work or
    /// failed.
    std::function<void()> done_callback_;

    /// @brief protocol family of the list (AF_INET or AF_INET6).
    uint16_t family_;

    /// @brief IP address of the server.
    std::string server_address_;

    /// @brief IP port of the server.
    uint16_t server_port_;

    /// @brief Set to true when the receive has completed successfully.
    bool receive_done_;

    /// @brief Set to true when the receive ended in EOF as expected. In other
    /// words, the server closed the connection while we were reading as we
    /// expected it to do.
    bool expected_eof_;

    /// @brief Tracks the next transaction id the client should use.
    Xid next_xid_;

    /// @brief Pointer to the server response currently being received.
    TcpStreamRequestPtr stream_response_;

    /// @brief List of requests to send.
    std::list<BlqQueryPtr> requests_to_send_;

    /// @brief List of requests sent.
    std::list<BlqQueryPtr> requests_sent_;

    /// @brief Tracks the request currently being sent (if one).
    BlqQueryPtr request_in_send_;

    /// @brief List of responses received.
    std::list<BlqResponsePtr> responses_received_;
};

/// @brief Pointer to the LeaseQueryTestClient.
typedef boost::shared_ptr<LeaseQueryTestClient> LeaseQueryTestClientPtr;

#endif
