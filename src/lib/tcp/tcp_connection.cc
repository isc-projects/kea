// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <tcp/tcp_connection.h>
#include <tcp/tcp_connection_pool.h>
#include <tcp/tcp_log.h>
#include <tcp/tcp_messages.h>
#include <boost/make_shared.hpp>

#include <iomanip>
#include <sstream>
#include <functional>

using namespace isc::asiolink;
namespace ph = std::placeholders;

namespace {

/// @brief Maximum size of the HTTP message that can be logged.
///
/// The part of the HTTP message beyond this value is truncated.
constexpr size_t MAX_LOGGED_MESSAGE_SIZE = 1024;

}

namespace isc {
namespace tcp {

std::string 
TcpRequest::dumpAsHex(const uint8_t* data, size_t len) {
    std::stringstream output;
    for (unsigned int i = 0; i < len; i++) {
        if (i) {
            output << ":";
        }

        output << std::setfill('0') << std::setw(2) << std::hex
               << static_cast<unsigned short>(data[i]);
    }

    return (output.str());
}

void 
TcpResponse::consumeWireData(const size_t length) {
    send_in_progress_ = true;
    wire_data_.erase(wire_data_.begin(), wire_data_.begin() + length);
}

void
TcpConnection::
SocketCallback::operator()(boost::system::error_code ec, size_t length) {
    if (ec.value() == boost::asio::error::operation_aborted) {
        return;
    }
    callback_(ec, length);
}

TcpConnection::TcpConnection(asiolink::IOService& io_service,
                               const TcpConnectionAcceptorPtr& acceptor,
                               const TlsContextPtr& tls_context,
                               TcpConnectionPool& connection_pool,
                               const TcpConnectionAcceptorCallback& callback,
                               const long request_timeout,
                               const long idle_timeout,
                               const size_t read_max /* = 32768 */)
    : request_timer_(io_service),
      request_timeout_(request_timeout),
      tls_context_(tls_context),
      idle_timeout_(idle_timeout),
      tcp_socket_(),
      tls_socket_(),
      acceptor_(acceptor),
      connection_pool_(connection_pool),
      acceptor_callback_(callback),
      input_buf_(read_max) {
    if (!tls_context) {
        HERE("");
        tcp_socket_.reset(new asiolink::TCPSocket<SocketCallback>(io_service));
    } else {
        tls_socket_.reset(new asiolink::TLSSocket<SocketCallback>(io_service,
                                                                  tls_context));
    }
}

TcpConnection::~TcpConnection() {
    HERE("");
    close();
}

#if 0
void
TcpConnection::recordParameters(const TcpRequestPtr& request) const {
    if (!request) {
        // Should never happen.
        return;
    }

    // Record the remote address.
    request->setRemote(getRemoteEndpointAddressAsText());

    // Record TLS parameters.
    if (!tls_socket_) {
        return;
    }

    // The connection uses HTTPS aka HTTP over TLS.
    request->setTls(true);

    // Record the first commonName of the subjectName of the client
    // certificate when wanted.
    if (TcpRequest::recordSubject_) {
        request->setSubject(tls_socket_->getTlsStream().getSubject());
    }

    // Record the first commonName of the issuerName of the client
    // certificate when wanted.
    if (TcpRequest::recordIssuer_) {
        request->setIssuer(tls_socket_->getTlsStream().getIssuer());
    }
}
#endif

void
TcpConnection::shutdownCallback(const boost::system::error_code&) {
    tls_socket_->close();
}

void
TcpConnection::shutdown() {
    request_timer_.cancel();
    if (tcp_socket_) {
        tcp_socket_->close();
        return;
    }

    if (tls_socket_) {
        // Create instance of the callback to close the socket.
        SocketCallback cb(std::bind(&TcpConnection::shutdownCallback,
                                    shared_from_this(),
                                    ph::_1)); // error_code
        tls_socket_->shutdown(cb);
        return;
    }

    // Not reachable?
    isc_throw(Unexpected, "internal error: unable to shutdown the socket");
}

void
TcpConnection::close() {
    request_timer_.cancel();
    if (tcp_socket_) {
        tcp_socket_->close();
        return;
    }

    if (tls_socket_) {
        tls_socket_->close();
        return;
    }

    // Not reachable?
    isc_throw(Unexpected, "internal error: unable to close the socket");
}

void
TcpConnection::shutdownConnection() {
    try {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                  TCP_CONNECTION_SHUTDOWN)
            .arg(getRemoteEndpointAddressAsText());
        connection_pool_.shutdown(shared_from_this());
    } catch (...) {
        LOG_ERROR(tcp_logger, TCP_CONNECTION_SHUTDOWN_FAILED);
    }
}

void
TcpConnection::stopThisConnection() {
    try {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                  TCP_CONNECTION_STOP)
            .arg(getRemoteEndpointAddressAsText());
        connection_pool_.stop(shared_from_this());
    } catch (...) {
        LOG_ERROR(tcp_logger, TCP_CONNECTION_STOP_FAILED);
    }
}

void
TcpConnection::asyncAccept() {
    // Create instance of the callback. It is safe to pass the local instance
    // of the callback, because the underlying boost functions make copies
    // as needed.
    TcpConnectionAcceptorCallback cb = std::bind(&TcpConnection::acceptorCallback,
                                                 shared_from_this(), ph::_1); // error
    try {
        TlsConnectionAcceptorPtr tls_acceptor =
            boost::dynamic_pointer_cast<TlsConnectionAcceptor>(acceptor_);
        if (!tls_acceptor) {
            if (!tcp_socket_) {
                isc_throw(Unexpected, "internal error: TCP socket is null");
            }
            HERE("");
            acceptor_->asyncAccept(*tcp_socket_, cb);
        } else {
            if (!tls_socket_) {
                isc_throw(Unexpected, "internal error: TLS socket is null");
            }
            tls_acceptor->asyncAccept(*tls_socket_, cb);
        }
    } catch (const std::exception& ex) {
        isc_throw(TcpConnectionError, "unable to start accepting TCP "
                  "connections: " << ex.what());
    }
}

void
TcpConnection::doHandshake() {
    // Skip the handshake if the socket is not a TLS one.
    if (!tls_socket_) {
        HERE("");
        doRead();
        return;
    }

    // Create instance of the callback. It is safe to pass the local instance
    // of the callback, because the underlying boost functions make copies
    // as needed.
    SocketCallback cb(std::bind(&TcpConnection::handshakeCallback,
                                shared_from_this(),
                                ph::_1)); // error
    try {
        tls_socket_->handshake(cb);

    } catch (const std::exception& ex) {
        isc_throw(TcpConnectionError, "unable to perform TLS handshake: "
                  << ex.what());
    }
}

void
TcpConnection::doRead(TcpRequestPtr request) {
    try {
        HERE("");
        TCPEndpoint endpoint;

        // Request hasn't been created if we are starting to read the
        // new request.
        if (!request) {
            HERE("");
            request = createRequest();
#if 0
            recordParameters(transaction->getRequest());
#endif
        }

        // Create instance of the callback. It is safe to pass the local instance
        // of the callback, because the underlying std functions make copies
        // as needed.
        SocketCallback cb(std::bind(&TcpConnection::socketReadCallback,
                                    shared_from_this(),
                                    request,
                                    ph::_1,   // error
                                    ph::_2)); // bytes_transferred
        if (tcp_socket_) {
            HERE("tcp_socket read max bytes:" << getInputBufSize());
            tcp_socket_->asyncReceive(static_cast<void*>(getInputBufData()),
                                      getInputBufSize(), 0, &endpoint, cb);
            return;
        }

        if (tls_socket_) {
            HERE("tls_socket read max bytes:" << getInputBufSize());
            tls_socket_->asyncReceive(static_cast<void*>(getInputBufData()),
                                      getInputBufSize(), 0, &endpoint, cb);
            return;
        }
    } catch (...) {
        stopThisConnection();
    }
}

void
TcpConnection::doWrite(TcpResponsePtr response) {
    try {
        if (response->wireDataAvail()) {
            HERE("send:" << TcpRequest::dumpAsHex(response->getWireData(), response->getWireDataSize()));
            // Create instance of the callback. It is safe to pass the local instance
            // of the callback, because the underlying std functions make copies
            // as needed.
            SocketCallback cb(std::bind(&TcpConnection::socketWriteCallback,
                                        shared_from_this(),
                                        response,
                                        ph::_1,   // error
                                        ph::_2)); // bytes_transferred
            if (tcp_socket_) {
                tcp_socket_->asyncSend(response->getWireData(),
                                       response->getWireDataSize(),
                                       cb);
                return;
            }
            if (tls_socket_) {
                tls_socket_->asyncSend(response->getWireData(),
                                       response->getWireDataSize(),
                                       cb);
                return;
            }
        } else {
            // The connection is persistent and we are done sending
            // the previous response. Start listening for the next
            // requests.
            setupIdleTimer();
        }
    } catch (...) {
        stopThisConnection();
    }
}

void
TcpConnection::asyncSendResponse(TcpResponsePtr response) {
    HERE("");
    doWrite(response);
}


void
TcpConnection::acceptorCallback(const boost::system::error_code& ec) {
    HERE("");
    if (!acceptor_->isOpen()) {
        return;
    }

    if (ec) {
        stopThisConnection();
    }

    acceptor_callback_(ec);

    if (!ec) {
        if (!tls_context_) {
            LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
                      TCP_REQUEST_RECEIVE_START)
                .arg(getRemoteEndpointAddressAsText())
                .arg(static_cast<unsigned>(request_timeout_/1000));
        } else {
            LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
                      TCP_CONNECTION_HANDSHAKE_START)
                .arg(getRemoteEndpointAddressAsText())
                .arg(static_cast<unsigned>(request_timeout_/1000));
        }

#if 0
        setupRequestTimer();
#endif
        doHandshake();
    }
}

void
TcpConnection::handshakeCallback(const boost::system::error_code& ec) {
    if (ec) {
        LOG_INFO(tcp_logger, TCP_CONNECTION_HANDSHAKE_FAILED)
            .arg(getRemoteEndpointAddressAsText())
            .arg(ec.message());
        stopThisConnection();
    } else {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  TCP_REQUEST_RECEIVE_START)
            .arg(getRemoteEndpointAddressAsText());

        HERE("");
        doRead();
    }
}

void
TcpConnection::socketReadCallback(TcpRequestPtr request,
                                  boost::system::error_code ec, size_t length) {
    if (ec) {
        // IO service has been stopped and the connection is probably
        // going to be shutting down.
        if (ec.value() == boost::asio::error::operation_aborted) {
            return;

        // EWOULDBLOCK and EAGAIN are special cases. Everything else is
        // treated as fatal error.
        } else if ((ec.value() != boost::asio::error::try_again) &&
                   (ec.value() != boost::asio::error::would_block)) {
            stopThisConnection();

        // We got EWOULDBLOCK or EAGAIN which indicate that we may be able to
        // read something from the socket on the next attempt. Just make sure
        // we don't try to read anything now in case there is any garbage
        // passed in length.
        } else {
            length = 0;
        }
    }

#if 0
    // Receiving is in progress, so push back the timeout.
    // Not sure this makes sense anymore
    setupRequestTimer(transaction);
#endif

    TcpRequestPtr next_request = request;
    if (length) {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA, TCP_DATA_RECEIVED)
            .arg(length)
            .arg(getRemoteEndpointAddressAsText());
        WireData input_data(input_buf_.begin(), input_buf_.begin() + length);
        next_request = postData(request, input_data);
    }

#if 0
    // Data processed. Activate the timer again.
    setupRequestTimer(transaction);
#endif

    // Start next read.
    doRead(next_request);
}

TcpRequestPtr
TcpConnection::postData(TcpRequestPtr request, WireData& input_data) {
    size_t bytes_left = 0;
    size_t length = input_data.size();
    if (length) {
        // Add data to the current request.
        size_t bytes_used = request->postBuffer(static_cast<void*>(input_data.data()), length);
        // Remove bytes used.
        bytes_left = length - bytes_used; 
        input_data.erase(input_data.begin(), input_data.begin() + length);
    }

    if (request->needData()) {
        // Current request is incomplete and we're out of data.
        return (request);
    }

    try {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                  TCP_CLIENT_REQUEST_RECEIVED)
                .arg(getRemoteEndpointAddressAsText());

        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                  TCP_CLIENT_REQUEST_RECEIVED_DETAILS)
                .arg(getRemoteEndpointAddressAsText())
                .arg(request->logFormatRequest(MAX_LOGGED_MESSAGE_SIZE));
        requestReceived(request);
    } catch (const std::exception& ex) {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                  TCP_BAD_CLIENT_REQUEST_RECEIVED)
                .arg(getRemoteEndpointAddressAsText())
                .arg(ex.what());
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                  TCP_BAD_CLIENT_REQUEST_RECEIVED_DETAILS)
                .arg(getRemoteEndpointAddressAsText())
                .arg(request->logFormatRequest(MAX_LOGGED_MESSAGE_SIZE));
    }

    // Start a new request.
    request = createRequest();
    if (bytes_left) {
        // The input buffer spanned messages. Recurse to post the remainder to the
        // new request.
        request = postData(request, input_data);
    }  

    return (request);
}

void
TcpConnection::socketWriteCallback(TcpResponsePtr response,
                                    boost::system::error_code ec, size_t length) {
    if (ec) {
        // IO service has been stopped and the connection is probably
        // going to be shutting down.
        if (ec.value() == boost::asio::error::operation_aborted) {
            return;

        // EWOULDBLOCK and EAGAIN are special cases. Everything else is
        // treated as fatal error.
        } else if ((ec.value() != boost::asio::error::try_again) &&
                   (ec.value() != boost::asio::error::would_block)) {
            stopThisConnection();
            // @todo TKM shouldn't there be a return here?

        // We got EWOULDBLOCK or EAGAIN which indicate that we may be able to
        // read something from the socket on the next attempt.
        } else {
#if 0
            // Sending is in progress, so push back the timeout.
            setupRequestTimer(transaction);
#endif
            doWrite(response);
        }
    }

    // Since each response has its own wire data, it is not really
    // possible that the number of bytes written is larger than the size
    // of the buffer. But, let's be safe and set the length to the size
    // of the buffer if that unexpected condition occurs.
    if (length > response->getWireDataSize()) {
        length = response->getWireDataSize();
    }

    if (length <= response->getWireDataSize()) {
#if 0
        // Sending is in progress, so push back the timeout.
        setupRequestTimer(transaction);
#endif
    }

    // Eat the 'length' number of bytes from the output buffer and only
    // leave the part of the response that hasn't been sent.
    response->consumeWireData(length);

    // Schedule the write of the unsent data.
    doWrite(response);
}

#if 0
void
TcpConnection::setupRequestTimer(TransactionPtr transaction) {
    // Pass raw pointer rather than shared_ptr to this object,
    // because IntervalTimer already passes shared pointer to the
    // IntervalTimerImpl to make sure that the callback remains
    // valid.
    request_timer_.setup(std::bind(&TcpConnection::requestTimeoutCallback,
                                   this, transaction),
                         request_timeout_, IntervalTimer::ONE_SHOT);
}
#endif

void
TcpConnection::setupIdleTimer() {
    request_timer_.setup(std::bind(&TcpConnection::idleTimeoutCallback,
                                   this),
                         idle_timeout_, IntervalTimer::ONE_SHOT);
}

#if 0
void
TcpConnection::requestTimeoutCallback(TransactionPtr transaction) {
    LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
              TCP_CLIENT_REQUEST_TIMEOUT_OCCURRED)
        .arg(getRemoteEndpointAddressAsText());

    // We need to differentiate the transactions between a normal response and the
    // timeout. We create new transaction from the current transaction. It is
    // to preserve the request we're responding to.
    auto spawned_transaction = Transaction::spawn(response_creator_, transaction);

    // The new transaction inherits the request from the original transaction
    // if such transaction exists.
    auto request = spawned_transaction->getRequest();

    // Depending on when the timeout occurred, the TCP version of the request
    // may or may not be available. Therefore we check if the HTTP version is
    // set in the request. If it is not available, we need to create a dummy
    // request with the default HTTP/1.0 version. This version will be used
    // in the response.
    if (request->context()->http_version_major_ == 0) {
        request.reset(new TcpRequest(TcpRequest::Method::HTTP_POST, "/",
                                      TcpVersion::HTTP_10(),
                                      HostTcpHeader("dummy")));
        request->finalize();
    }

    // Create the timeout response.
    TcpResponsePtr response =
        response_creator_->createStockTcpResponse(request,
                                                   TcpStatusCode::REQUEST_TIMEOUT);

    // Send the HTTP 408 status.
    asyncSendResponse(response, spawned_transaction);
}
#endif

void
TcpConnection::idleTimeoutCallback() {
    LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
              TCP_IDLE_CONNECTION_TIMEOUT_OCCURRED)
        .arg(getRemoteEndpointAddressAsText());
    // In theory we should shutdown first and stop/close after but
    // it is better to put the connection management responsibility
    // on the client... so simply drop idle connections.
    stopThisConnection();
}

std::string
TcpConnection::getRemoteEndpointAddressAsText() const {
    try {
        if (tcp_socket_) {
            if (tcp_socket_->getASIOSocket().is_open()) {
                return (tcp_socket_->getASIOSocket().remote_endpoint().address().to_string());
            }
        } else if (tls_socket_) {
            if (tls_socket_->getASIOSocket().is_open()) {
                return (tls_socket_->getASIOSocket().remote_endpoint().address().to_string());
            }
        }
    } catch (...) {
    }
    return ("(unknown address)");
}

void 
TcpConnection::setReadMax(const size_t read_max) {
    if (!read_max) {
        isc_throw(BadValue, "TcpConnection read_max must be > 0");
    }

    read_max_ = read_max;
    input_buf_.resize(read_max);
}

} // end of namespace isc::tcp
} // end of namespace isc
