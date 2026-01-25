// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_CLIENT_EXCHANGE_H
#define RADIUS_CLIENT_EXCHANGE_H

#include <client_attribute.h>
#include <client_message.h>
#include <client_server.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/udp_socket.h>
#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <chrono>
#include <functional>
#include <list>
#include <mutex>
#include <string>
#include <vector>

namespace isc {
namespace radius {

/// @brief Exchange error codes.
///
/// @todo Move to Exchange class.
enum ExchangeRC {
    BADRESP_RC = -2,        // Got a bad response.
    ERROR_RC = -1,          // General error.
    OK_RC = 0,              // OK: no error.
    TIMEOUT_RC = 1,         // Timeout occurred.
    REJECT_RC = 2,          // Got an Access-Reject response.
    READBLOCK_RC = 3        // Get AGAIN or EWOULDBLOCK.
};

/// @brief ExchangeRC value -> name function.
///
/// @param rc the error code.
std::string exchangeRCtoText(const int rc);

/// @brief RADIUS exchange (forward declaration).
class Exchange;

/// @brief Type of shared pointers to RADIUS exchange object.
typedef boost::shared_ptr<Exchange> ExchangePtr;

/// @brief RADIUS Base Exchange.
class Exchange {
public:
    /// @brief Receive buffer size.
    static constexpr size_t BUF_LEN = 8192;

    /// @brief Type of UDP socket callback functions.
    typedef std::function<void(const boost::system::error_code ec,
                               const size_t size)> SocketCallback;

    /// @brief Type of RADIUS UDP sockets.
    typedef asiolink::UDPSocket<const SocketCallback> RadiusSocket;

    /// @brief Termination handler.
    typedef std::function<void(const ExchangePtr ex)> Handler;

    /// @brief Factory.
    ///
    /// Async version.
    ///
    /// @param io_service Reference to the IO service.
    /// @param request request message to send.
    /// @param maxretries maximum number of retries for a server.
    /// @param servers Servers.
    /// @param handler Termination handler.
    /// @param protocol Protocol (default to UDP).
    static ExchangePtr create(const asiolink::IOServicePtr io_service,
                              const MessagePtr& request,
                              unsigned maxretries,
                              const Servers& servers,
                              Handler handler,
                              RadiusProtocol protocol = PW_PROTO_UDP);

    /// @brief Factory.
    ///
    /// Sync version (UDP only).
    ///
    /// @param request request message to send.
    /// @param maxretries maximum number of retries for a server.
    /// @param servers Servers.
    static ExchangePtr create(const MessagePtr& request,
                              unsigned maxretries,
                              const Servers& servers);

    /// @brief Destructor.
    virtual ~Exchange() = default;

    /// @brief Get identifier.
    ///
    /// @return the identifier.
    const std::string& getId() const {
        return (identifier_);
    }

    /// @brief Get the error code.
    ///
    /// @return the error code.
    int getRC() const {
        return (rc_);
    }

    /// @brief Get the request.
    ///
    /// @return the request.
    MessagePtr getRequest() const {
        return (request_);
    }

    /// @brief Get the response.
    ///
    /// @return the response.
    MessagePtr getResponse() const {
        return (received_);
    }

    /// @brief Log reply messages.
    void logReplyMessages() const;

    /// @brief Start.
    virtual void start() = 0;

    /// @brief Shutdown.
    virtual void shutdown() = 0;

    /// @brief Process response.
    void processResponse();

protected:
    /// @brief Constructor.
    ///
    /// Async version.
    ///
    /// @param request request message to send.
    /// @param maxretries maximum number of retries for a server.
    /// @param servers Servers.
    /// @param handler Termination handler.
    Exchange(const MessagePtr& request,
             unsigned maxretries,
             const Servers& servers,
             Handler handler);

    /// @brief Constructor.
    ///
    /// Sync version.
    ///
    /// @param request request message to send.
    /// @param maxretries maximum number of retries for a server.
    /// @param servers Servers.
    Exchange(const MessagePtr& request,
             unsigned maxretries,
             const Servers& servers);

    /// @brief The identifier (random value in hexadecimal).
    std::string identifier_;

    /// @brief Sync / async flag.
    bool sync_;

    /// @brief Error/return code.
    int rc_;

    /// @brief Request message.
    MessagePtr request_;

    /// @brief Sent message.
    MessagePtr sent_;

    /// @brief Received message.
    MessagePtr received_;

    /// @brief Maximum number of retries for a server.
    /// @note 0 is a valid value which means no retry.
    unsigned maxretries_;

    /// @brief Servers (a copy which is what we need).
    Servers servers_;

    /// @brief Termination handler.
    Handler handler_;

    /// @brief Create identifier.
    void createIdentifier();

    /// @brief Build request.
    ///
    /// @param server Server where to send the request.
    /// @param start_time Start time of the exchange.
    void buildRequest(const ServerPtr& server,
                      std::chrono::steady_clock::time_point start_time);
};

/// @brief RADIUS/UDP exchange (forward declaration).
class UdpExchange;

/// @brief Type of shared pointers to RADIUS/UDP exchange object.
typedef boost::shared_ptr<UdpExchange> UdpExchangePtr;

/// @brief RADIUS/UDP Exchange.
class UdpExchange : public Exchange,
                    public boost::enable_shared_from_this<UdpExchange> {
public:
    /// @brief Constructor.
    ///
    /// Async version.
    ///
    /// @param io_service Reference to the IO service.
    /// @param request request message to send.
    /// @param maxretries maximum number of retries for a server.
    /// @param servers Servers.
    /// @param handler Termination handler.
    UdpExchange(const asiolink::IOServicePtr io_service,
                const MessagePtr& request,
                unsigned maxretries,
                const Servers& servers,
                Handler handler);

    /// @brief Constructor.
    ///
    /// Sync version.
    ///
    /// @param request request message to send.
    /// @param maxretries maximum number of retries for a server.
    /// @param servers Servers.
    UdpExchange(const MessagePtr& request,
                unsigned maxretries,
                const Servers& servers);

    /// @brief Destructor.
    virtual ~UdpExchange();

    /// @brief Start.
    virtual void start();

    /// @brief Shutdown.
    virtual void shutdown();

protected:
    /// @brief IO service (argument for async or internal for sync).
    asiolink::IOServicePtr io_service_;

    /// @brief Started flag.
    bool started_;

    /// @brief Terminated flag.
    bool terminated_;

    /// @brief Start time.
    std::chrono::steady_clock::time_point start_time_;

    /// @brief Socket.
    boost::scoped_ptr<RadiusSocket> socket_;

    /// @brief UDP endpoint.
    boost::scoped_ptr<asiolink::UDPEndpoint> ep_;

    /// @brief Interval timer.
    asiolink::IntervalTimerPtr timer_;

    /// @brief Current server.
    ServerPtr server_;

    /// @brief Current server index.
    ///
    /// The current server is either the server indexed by this in the table
    /// or when greater than the table size the first postponed server.
    size_t idx_;

    /// @brief Buffer.
    std::vector<uint8_t> buffer_;

    /// @brief Number of transmitted octests;
    size_t size_;

    /// @brief Retry counter.
    unsigned retries_;

    /// @brief List of postponed server indexes.
    std::list<size_t> postponed_;

    /// @brief State change mutex.
    boost::scoped_ptr<std::mutex> mutex_;

    /// @brief Build request.
    void buildRequest();

    /// @brief Instance open.
    void open();

    /// @brief Shutdown.
    virtual void shutdownInternal();

    /// @brief Class open / open next.
    ///
    /// @param ex the exchange.
    static void openNext(UdpExchangePtr ex) {
        ex->open();
    }

    /// @brief Sent handler.
    ///
    /// @param ex the exchange.
    /// @param ec Boost ASIO error code.
    /// @param size number of sent octets.
    static void sentHandler(UdpExchangePtr ex,
                            const boost::system::error_code ec,
                            const size_t size);

    /// @brief Received handler.
    ///
    /// @param ex the exchange.
    /// @param ec Boost ASIO error code.
    /// @param size number of received octets.
    static void receivedHandler(UdpExchangePtr ex,
                                const boost::system::error_code ec,
                                const size_t size);

    /// @brief Set timer.
    void setTimer();

    /// @brief Cancel timer.
    void cancelTimer();

    /// @brief Timeout handler.
    ///
    /// @param ex the exchange.
    static void timeoutHandler(UdpExchangePtr ex);

    /// @brief Terminate.
    void terminate();
};

/// @brief RADIUS/TCP exchange (forward declaration).
class TcpExchange;

/// @brief Type of shared pointers to RADIUS/TCP exchange object.
typedef boost::shared_ptr<TcpExchange> TcpExchangePtr;

/// @brief RADIUS/TCP (or RADIUS/TLS) Exchange.
class TcpExchange : public Exchange,
                    public boost::enable_shared_from_this<TcpExchange> {
public:
    /// @brief Constructor.
    ///
    /// Async version.
    ///
    /// @param request request message to send.
    /// @param maxretries maximum number of retries for a server.
    /// @param servers Servers.
    /// @param handler Termination handler.
    TcpExchange(const MessagePtr& request,
                unsigned maxretries,
                const Servers& servers,
                Handler handler);

    /// @note: no sync version.

    /// @brief Destructor.
    virtual ~TcpExchange() = default;

    /// @brief Start.
    virtual void start();

    /// @brief Shutdown.
    virtual void shutdown();

protected:
    /// @brief Start time.
    std::chrono::steady_clock::time_point start_time_;

    /// @brief Current server.
    ServerPtr server_;

    /// @brief Response wire data.
    isc::tcp::WireDataPtr response_;

    /// @brief Build request.
    void buildRequest();

    /// @brief Request handler.
    ///
    /// @param ex Point to the Exchange.
    /// @param ec Boost error code.
    /// @param response Pointer to response wire data.
    /// @param error_msg Error message.
    static void RequestHandler(TcpExchangePtr ex,
                               const boost::system::error_code& ec,
                               const isc::tcp::WireDataPtr& response,
                               const std::string& error_msg);

    /// @brief Complete check.
    ///
    /// @param response Pointer to response wire data.
    /// @param error_msg Reference to the error message.
    /// @return status (>0 complete, 0 incomplete, <0 error).
    static int CompleteCheck(const isc::tcp::WireDataPtr& response,
                             std::string& error_msg);
};

} // end of namespace isc::radius
} // end of namespace isc

#endif
