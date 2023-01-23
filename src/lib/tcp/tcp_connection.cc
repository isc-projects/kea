// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/strutil.h>
#include <boost/make_shared.hpp>

#include <iomanip>
#include <sstream>
#include <functional>

using namespace isc::asiolink;
namespace ph = std::placeholders;

namespace {

/// @brief Maximum size of a message that can be logged.
///
/// The part of the message beyond this value is truncated.
const size_t MAX_LOGGED_MESSAGE_SIZE = 1024;

}

namespace isc {
namespace tcp {

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
                             const TcpConnectionAcceptorCallback& acceptor_callback,
                             const TcpConnectionFilterCallback& connection_filter,
                             const long idle_timeout,
                             const size_t read_max /* = 32768 */)
    : tls_context_(tls_context),
      idle_timeout_(idle_timeout),
      idle_timer_(io_service),
      tcp_socket_(),
      tls_socket_(),
      acceptor_(acceptor),
      connection_pool_(connection_pool),
      acceptor_callback_(acceptor_callback),
      connection_filter_(connection_filter),
      input_buf_(read_max) {
    if (!tls_context) {
        tcp_socket_.reset(new asiolink::TCPSocket<SocketCallback>(io_service));
    } else {
        tls_socket_.reset(new asiolink::TLSSocket<SocketCallback>(io_service,
                                                                  tls_context));
    }
}

TcpConnection::~TcpConnection() {
    close();
}

void
TcpConnection::shutdownCallback(const boost::system::error_code&) {
    tls_socket_->close();
}

void
TcpConnection::shutdown() {
    idle_timer_.cancel();
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
    idle_timer_.cancel();
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
                                                 shared_from_this(),
                                                 ph::_1);
    try {
        TlsConnectionAcceptorPtr tls_acceptor =
            boost::dynamic_pointer_cast<TlsConnectionAcceptor>(acceptor_);
        if (!tls_acceptor) {
            if (!tcp_socket_) {
                isc_throw(Unexpected, "internal error: TCP socket is null");
            }
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
        doRead();
        return;
    }

    setupIdleTimer();

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
        TCPEndpoint endpoint;

        setupIdleTimer();

        // Request hasn't been created if we are starting to read the
        // new request.
        if (!request) {
            request = createRequest();
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
            tcp_socket_->asyncReceive(static_cast<void*>(getInputBufData()),
                                      getInputBufSize(), 0, &endpoint, cb);
            return;
        }

        if (tls_socket_) {
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
            // Create instance of the callback. It is safe to pass the
            // local instance of the callback, because the underlying
            // std functions make copies as needed.
            SocketCallback cb(std::bind(&TcpConnection::socketWriteCallback,
                                        shared_from_this(),
                                        response,
                                        ph::_1,   // error
                                        ph::_2)); // bytes_transferred
            if (tcp_socket_) {
                LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                          TCP_SERVER_RESPONSE_SEND)
                    .arg(getRemoteEndpointAddressAsText());
                tcp_socket_->asyncSend(response->getWireData(),
                                       response->getWireDataSize(),
                                       cb);
                return;
            }
            if (tls_socket_) {
                LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                          TLS_SERVER_RESPONSE_SEND)
                    .arg(getRemoteEndpointAddressAsText());
                tls_socket_->asyncSend(response->getWireData(),
                                       response->getWireDataSize(),
                                       cb);
                return;
            }
        } else {
            // The connection remains open and we are done sending the response.
            // If the response sent handler returns true then we should start the
            // idle timer.
            if (responseSent(response)) {
                setupIdleTimer();
            }
        }
    } catch (...) {
        // The connection is dead and there can't be a pending write as
        // they are in sequence.
        TcpConnection::stopThisConnection();
    }
}

void
TcpConnection::asyncSendResponse(TcpResponsePtr response) {
    doWrite(response);
}


void
TcpConnection::acceptorCallback(const boost::system::error_code& ec) {
    if (!acceptor_->isOpen()) {
        return;
    }

    if (ec) {
        stopThisConnection();
    }

    // Stage a new connection to listen for next client.
    acceptor_callback_(ec);

    if (!ec) {
        try {
            if (tcp_socket_ && tcp_socket_->getASIOSocket().is_open()) {
                remote_endpoint_ =
                    tcp_socket_->getASIOSocket().remote_endpoint();
            } else if (tls_socket_ && tls_socket_->getASIOSocket().is_open()) {
                remote_endpoint_ =
                    tls_socket_->getASIOSocket().remote_endpoint();
            }
        } catch (...) {
            // Let's it to fail later.
        }

        // In theory, we should not get here with an unopened socket
        // but just in case, we'll check for NO_ENDPOINT.
        if ((remote_endpoint_ == NO_ENDPOINT()) ||
            (connection_filter_ && !connection_filter_(remote_endpoint_))) {
            LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
                      TCP_CONNECTION_REJECTED_BY_FILTER)
                .arg(getRemoteEndpointAddressAsText());
            TcpConnectionPool::rejected_counter_ += 1;
            stopThisConnection();
            return;
        }

        if (!tls_context_) {
            LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
                      TCP_REQUEST_RECEIVE_START)
                .arg(getRemoteEndpointAddressAsText())
                .arg(static_cast<unsigned>(idle_timeout_/1000));
        } else {
            LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
                      TLS_CONNECTION_HANDSHAKE_START)
                .arg(getRemoteEndpointAddressAsText())
                .arg(static_cast<unsigned>(idle_timeout_/1000));
        }

        doHandshake();
    }
}

void
TcpConnection::handshakeCallback(const boost::system::error_code& ec) {
    if (ec) {
        LOG_INFO(tcp_logger, TLS_CONNECTION_HANDSHAKE_FAILED)
            .arg(getRemoteEndpointAddressAsText())
            .arg(ec.message());
        stopThisConnection();
    } else {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  TLS_REQUEST_RECEIVE_START)
            .arg(getRemoteEndpointAddressAsText())
            .arg(static_cast<unsigned>(idle_timeout_/1000));
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
            return;

        // We got EWOULDBLOCK or EAGAIN which indicate that we may be able to
        // read something from the socket on the next attempt. Just make sure
        // we don't try to read anything now in case there is any garbage
        // passed in length.
        } else {
            length = 0;
        }
    }

    // Data received, Restart the request timer.
    setupIdleTimer();

    TcpRequestPtr next_request = request;
    if (length) {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
                  TCP_DATA_RECEIVED)
            .arg(length)
            .arg(getRemoteEndpointAddressAsText());
        WireData input_data(input_buf_.begin(), input_buf_.begin() + length);
        next_request = postData(request, input_data);
    }

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
        // Current request is incomplete and we're out of data
        // return the incomplete request and we'll read again.
        return (request);
    }

    try {
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                  TCP_CLIENT_REQUEST_RECEIVED)
                .arg(getRemoteEndpointAddressAsText());

        // Request complete, stop the timer.
        idle_timer_.cancel();

        // Process the completed request.
        requestReceived(request);
    } catch (const std::exception& ex) {
        LOG_ERROR(tcp_logger, TCP_REQUEST_RECEIVED_FAILED)
                .arg(getRemoteEndpointAddressAsText())
                .arg(ex.what());
    }

    // Create a new, empty request.
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
            // The connection is dead and there can't be a pending write as
            // they are in sequence.
            TcpConnection::stopThisConnection();
            return;

        // We got EWOULDBLOCK or EAGAIN which indicate that we may be able to
        // read something from the socket on the next attempt.
        } else {
            doWrite(response);
        }
    }

    LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA, TCP_DATA_SENT)
        .arg(length)
        .arg(getRemoteEndpointAddressAsText());

    // Since each response has its own wire data, it is not really
    // possible that the number of bytes written is larger than the size
    // of the buffer. But, let's be safe and set the length to the size
    // of the buffer if that unexpected condition occurs.
    if (length > response->getWireDataSize()) {
        length = response->getWireDataSize();
    }

    // Eat the 'length' number of bytes from the output buffer and only
    // leave the part of the response that hasn't been sent.
    response->consumeWireData(length);

    // Schedule the write of the unsent data.
    doWrite(response);
}

void
TcpConnection::setupIdleTimer() {
    idle_timer_.setup(std::bind(&TcpConnection::idleTimeoutCallback, this),
                      idle_timeout_, IntervalTimer::ONE_SHOT);
}

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
    if (remote_endpoint_ != NO_ENDPOINT()) {
        return (remote_endpoint_.address().to_string());
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
