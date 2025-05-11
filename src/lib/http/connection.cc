// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <dhcp/iface_mgr.h>
#include <http/connection.h>
#include <http/connection_pool.h>
#include <http/http_log.h>
#include <http/http_messages.h>
#include <boost/make_shared.hpp>
#include <functional>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief Maximum size of the HTTP message that can be logged.
///
/// The part of the HTTP message beyond this value is truncated.
constexpr size_t MAX_LOGGED_MESSAGE_SIZE = 1024;

}

namespace isc {
namespace http {

HttpConnection::Transaction::Transaction(const HttpResponseCreatorPtr& response_creator,
                                         const HttpRequestPtr& request)
    : request_(request ? request : response_creator->createNewHttpRequest()),
      parser_(new HttpRequestParser(*request_)),
      input_buf_(),
      output_buf_() {
    parser_->initModel();
}

HttpConnection::TransactionPtr
HttpConnection::Transaction::create(const HttpResponseCreatorPtr& response_creator) {
    return (boost::make_shared<Transaction>(response_creator));
}

HttpConnection::TransactionPtr
HttpConnection::Transaction::spawn(const HttpResponseCreatorPtr& response_creator,
                                   const TransactionPtr& transaction) {
    if (transaction) {
        return (boost::make_shared<Transaction>(response_creator,
                                                transaction->getRequest()));
    }
    return (create(response_creator));
}

void
HttpConnection::
SocketCallback::operator()(boost::system::error_code ec, size_t length) {
    if (ec.value() == boost::asio::error::operation_aborted) {
        return;
    }
    callback_(ec, length);
}

HttpConnection::HttpConnection(const asiolink::IOServicePtr& io_service,
                               const HttpAcceptorPtr& acceptor,
                               const TlsContextPtr& tls_context,
                               HttpConnectionPoolPtr connection_pool,
                               const HttpResponseCreatorPtr& response_creator,
                               const HttpAcceptorCallback& callback,
                               const long request_timeout,
                               const long idle_timeout)
    : io_service_(io_service), request_timer_(io_service_),
      request_timeout_(request_timeout), tls_context_(tls_context),
      idle_timeout_(idle_timeout), tcp_socket_(), tls_socket_(),
      acceptor_(acceptor), connection_pool_(connection_pool),
      response_creator_(response_creator), acceptor_callback_(callback),
      use_external_(false), watch_socket_(), defer_shutdown_(false) {
    if (!tls_context) {
        tcp_socket_.reset(new asiolink::TCPSocket<SocketCallback>(io_service));
    } else {
        tls_socket_.reset(new asiolink::TLSSocket<SocketCallback>(io_service,
                                                                  tls_context));
    }
}

HttpConnection::~HttpConnection() {
    close();
}

void
HttpConnection::addExternalSockets(bool use_external) {
    use_external_ = use_external;
}

void
HttpConnection::recordParameters(const HttpRequestPtr& request) const {
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
    if (HttpRequest::recordSubject_) {
        request->setSubject(tls_socket_->getTlsStream().getSubject());
    }

    // Record the first commonName of the issuerName of the client
    // certificate when wanted.
    if (HttpRequest::recordIssuer_) {
        request->setIssuer(tls_socket_->getTlsStream().getIssuer());
    }
}

void
HttpConnection::shutdownCallback(const boost::system::error_code&) {
    if (use_external_) {
        IfaceMgr::instance().deleteExternalSocket(tls_socket_->getNative());
        closeWatchSocket();
    }

    tls_socket_->close();
}

void
HttpConnection::shutdown() {
    request_timer_.cancel();
    if (tcp_socket_) {
        if (use_external_) {
            IfaceMgr::instance().deleteExternalSocket(tcp_socket_->getNative());
            closeWatchSocket();
        }
        tcp_socket_->close();
        return;
    }
    if (tls_socket_) {
        // Create instance of the callback to close the socket.
        SocketCallback cb(std::bind(&HttpConnection::shutdownCallback,
                                    shared_from_this(),
                                    ph::_1)); // error_code
        tls_socket_->shutdown(cb);
        return;
    }
    // Not reachable?
    isc_throw(Unexpected, "internal error: unable to shutdown the socket");
}

void
HttpConnection::markWatchSocketReady() {
    if (!watch_socket_) {
        /// Should not happen...
        return;
    }
    try {
        watch_socket_->markReady();
    } catch (const std::exception& ex) {
        LOG_ERROR(http_logger, HTTP_CONNECTION_WATCH_SOCKET_MARK_READY_ERROR)
            .arg(ex.what());
    }
}

void
HttpConnection::clearWatchSocket() {
    if (!watch_socket_) {
        /// Should not happen...
        return;
    }
    try {
        watch_socket_->clearReady();
    } catch (const std::exception& ex) {
        LOG_ERROR(http_logger, HTTP_CONNECTION_WATCH_SOCKET_CLEAR_ERROR)
            .arg(ex.what());
    }
}

void
HttpConnection::closeWatchSocket() {
    if (!watch_socket_) {
        /// Should not happen...
        return;
    }
    IfaceMgr::instance().deleteExternalSocket(watch_socket_->getSelectFd());
    // Close watch socket and log errors if occur.
    std::string watch_error;
    if (!watch_socket_->closeSocket(watch_error)) {
        LOG_ERROR(http_logger, HTTP_CONNECTION_WATCH_SOCKET_CLOSE_ERROR)
            .arg(watch_error);
    }
}

void
HttpConnection::close() {
    if (defer_shutdown_) {
        io_service_->post(std::bind([](HttpConnectionPtr c) { c->close(); }, shared_from_this()));
        return;
    }
    request_timer_.cancel();
    if (tcp_socket_) {
        if (use_external_) {
            IfaceMgr::instance().deleteExternalSocket(tcp_socket_->getNative());
            closeWatchSocket();
        }
        tcp_socket_->close();
        return;
    }
    if (tls_socket_) {
        if (use_external_) {
            IfaceMgr::instance().deleteExternalSocket(tls_socket_->getNative());
            closeWatchSocket();
        }
        tls_socket_->close();
        return;
    }
    // Not reachable?
    isc_throw(Unexpected, "internal error: unable to close the socket");
}

void
HttpConnection::shutdownConnection() {
    auto connection_pool = connection_pool_.lock();
    try {
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                  HTTP_CONNECTION_SHUTDOWN)
            .arg(getRemoteEndpointAddressAsText());
        if (connection_pool) {
            connection_pool->shutdown(shared_from_this());
        } else {
            shutdown();
        }
    } catch (...) {
        LOG_ERROR(http_logger, HTTP_CONNECTION_SHUTDOWN_FAILED);
    }
}

void
HttpConnection::stopThisConnection() {
    auto connection_pool = connection_pool_.lock();
    try {
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                  HTTP_CONNECTION_STOP)
            .arg(getRemoteEndpointAddressAsText());
        if (connection_pool) {
            connection_pool->stop(shared_from_this());
        } else {
            close();
        }
    } catch (...) {
        LOG_ERROR(http_logger, HTTP_CONNECTION_STOP_FAILED);
    }
}

void
HttpConnection::asyncAccept() {
    // Create instance of the callback. It is safe to pass the local instance
    // of the callback, because the underlying boost functions make copies
    // as needed.
    HttpAcceptorCallback cb = std::bind(&HttpConnection::acceptorCallback,
                                        shared_from_this(),
                                        ph::_1); // error
    try {
        HttpsAcceptorPtr tls_acceptor =
            boost::dynamic_pointer_cast<HttpsAcceptor>(acceptor_);
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
        isc_throw(HttpConnectionError, "unable to start accepting TCP "
                  "connections: " << ex.what());
    }
}

void
HttpConnection::doHandshake() {
    // Skip the handshake if the socket is not a TLS one.
    if (!tls_socket_) {
        doRead();
        return;
    }

    // Create instance of the callback. It is safe to pass the local instance
    // of the callback, because the underlying boost functions make copies
    // as needed.
    SocketCallback cb(std::bind(&HttpConnection::handshakeCallback,
                                shared_from_this(),
                                ph::_1)); // error
    try {
        tls_socket_->handshake(cb);
        if (use_external_) {
            markWatchSocketReady();
        }
    } catch (const std::exception& ex) {
        isc_throw(HttpConnectionError, "unable to perform TLS handshake: "
                  << ex.what());
    }
}

void
HttpConnection::doRead(TransactionPtr transaction) {
    try {
        TCPEndpoint endpoint;

        // Transaction hasn't been created if we are starting to read the
        // new request.
        if (!transaction) {
            transaction = Transaction::create(response_creator_);
            recordParameters(transaction->getRequest());
        }

        // Create instance of the callback. It is safe to pass the local instance
        // of the callback, because the underlying std functions make copies
        // as needed.
        SocketCallback cb(std::bind(&HttpConnection::socketReadCallback,
                                    shared_from_this(),
                                    transaction,
                                    ph::_1,   // error
                                    ph::_2)); //bytes_transferred
        if (tcp_socket_) {
            tcp_socket_->asyncReceive(static_cast<void*>(transaction->getInputBufData()),
                                      transaction->getInputBufSize(),
                                      0, &endpoint, cb);
            return;
        }
        if (tls_socket_) {
            tls_socket_->asyncReceive(static_cast<void*>(transaction->getInputBufData()),
                                      transaction->getInputBufSize(),
                                      0, &endpoint, cb);
            return;
        }
    } catch (...) {
        stopThisConnection();
    }
}

void
HttpConnection::doWrite(HttpConnection::TransactionPtr transaction) {
    try {
        if (transaction->outputDataAvail()) {
            // Create instance of the callback. It is safe to pass the local instance
            // of the callback, because the underlying std functions make copies
            // as needed.
            SocketCallback cb(std::bind(&HttpConnection::socketWriteCallback,
                                        shared_from_this(),
                                        transaction,
                                        ph::_1,   // error
                                        ph::_2)); // bytes_transferred
            if (tcp_socket_) {
                tcp_socket_->asyncSend(transaction->getOutputBufData(),
                                       transaction->getOutputBufSize(),
                                       cb);
                if (use_external_) {
                    markWatchSocketReady();
                }
                return;
            }
            if (tls_socket_) {
                tls_socket_->asyncSend(transaction->getOutputBufData(),
                                       transaction->getOutputBufSize(),
                                       cb);
                if (use_external_) {
                    markWatchSocketReady();
                }
                return;
            }
        } else {
            // The isPersistent() function may throw if the request hasn't
            // been created, i.e. the HTTP headers weren't parsed. We catch
            // this exception below and close the connection since we're
            // unable to tell if the connection should remain persistent
            // or not. The default is to close it.
            if (!transaction->getRequest()->isPersistent()) {
                stopThisConnection();

            } else {
                // The connection is persistent and we are done sending
                // the previous response. Start listening for the next
                // requests.
                setupIdleTimer();
                doRead();
            }
        }
    } catch (...) {
        stopThisConnection();
    }
}

void
HttpConnection::asyncSendResponse(const ConstHttpResponsePtr& response,
                                  TransactionPtr transaction) {
    transaction->setOutputBuf(response->toString());
    doWrite(transaction);
}

void
HttpConnection::acceptorCallback(const boost::system::error_code& ec) {
    if (!acceptor_->isOpen()) {
        return;
    }

    if (ec) {
        stopThisConnection();
    }

    acceptor_callback_(ec);

    if (!ec) {
        if (!tls_context_) {
            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL,
                      HTTP_REQUEST_RECEIVE_START)
                .arg(getRemoteEndpointAddressAsText())
                .arg(static_cast<unsigned>(request_timeout_/1000));
        } else {
            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL,
                      HTTP_CONNECTION_HANDSHAKE_START)
                .arg(getRemoteEndpointAddressAsText())
                .arg(static_cast<unsigned>(request_timeout_/1000));
        }

        if (use_external_) {
            auto& iface_mgr = IfaceMgr::instance();
            if (tcp_socket_) {
                iface_mgr.addExternalSocket(tcp_socket_->getNative(), 0);
            }
            if (tls_socket_) {
                iface_mgr.addExternalSocket(tls_socket_->getNative(), 0);
            }
            watch_socket_.reset(new WatchSocket());
            iface_mgr.addExternalSocket(watch_socket_->getSelectFd(), 0);
        }

        setupRequestTimer();
        doHandshake();
    }
}

void
HttpConnection::handshakeCallback(const boost::system::error_code& ec) {
    if (use_external_) {
        clearWatchSocket();
    }
    if (ec) {
        LOG_INFO(http_logger, HTTP_CONNECTION_HANDSHAKE_FAILED)
            .arg(getRemoteEndpointAddressAsText())
            .arg(ec.message());
        stopThisConnection();
    } else {
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  HTTPS_REQUEST_RECEIVE_START)
            .arg(getRemoteEndpointAddressAsText());

        doRead();
    }
}

void
HttpConnection::socketReadCallback(HttpConnection::TransactionPtr transaction,
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

    // Receiving is in progress, so push back the timeout.
    setupRequestTimer(transaction);

    if (length != 0) {
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
                  HTTP_DATA_RECEIVED)
            .arg(length)
            .arg(getRemoteEndpointAddressAsText());

        transaction->getParser()->postBuffer(static_cast<void*>(transaction->getInputBufData()),
                                             length);
        transaction->getParser()->poll();
    }

    if (transaction->getParser()->needData()) {
        // The parser indicates that the some part of the message being
        // received is still missing, so continue to read.
        doRead(transaction);

    } else {
        try {
            // The whole message has been received, so let's finalize it.
            transaction->getRequest()->finalize();

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                      HTTP_CLIENT_REQUEST_RECEIVED)
                .arg(getRemoteEndpointAddressAsText());

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                      HTTP_CLIENT_REQUEST_RECEIVED_DETAILS)
                .arg(getRemoteEndpointAddressAsText())
                .arg(transaction->getParser()->getBufferAsString(MAX_LOGGED_MESSAGE_SIZE));

        } catch (const std::exception& ex) {
            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                      HTTP_BAD_CLIENT_REQUEST_RECEIVED)
                .arg(getRemoteEndpointAddressAsText())
                .arg(ex.what());

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                      HTTP_BAD_CLIENT_REQUEST_RECEIVED_DETAILS)
                .arg(getRemoteEndpointAddressAsText())
                .arg(transaction->getParser()->getBufferAsString(MAX_LOGGED_MESSAGE_SIZE));
        }

        // Don't want to timeout if creation of the response takes long.
        request_timer_.cancel();

        defer_shutdown_ = true;

        std::unique_ptr<HttpConnection, void(*)(HttpConnection*)> p(this, [](HttpConnection* p) { p->defer_shutdown_ = false; });

        // Create the response from the received request using the custom
        // response creator.
        HttpResponsePtr response = response_creator_->createHttpResponse(transaction->getRequest());
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                  HTTP_SERVER_RESPONSE_SEND)
            .arg(response->toBriefString())
            .arg(getRemoteEndpointAddressAsText());

        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                  HTTP_SERVER_RESPONSE_SEND_DETAILS)
            .arg(getRemoteEndpointAddressAsText())
            .arg(HttpMessageParserBase::logFormatHttpMessage(response->toString(),
                                                             MAX_LOGGED_MESSAGE_SIZE));

        // Response created. Activate the timer again.
        setupRequestTimer(transaction);

        // Start sending the response.
        asyncSendResponse(response, transaction);
    }
}

void
HttpConnection::socketWriteCallback(HttpConnection::TransactionPtr transaction,
                                    boost::system::error_code ec, size_t length) {
    if (use_external_) {
        clearWatchSocket();
    }
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
        // read something from the socket on the next attempt.
        } else {
            // Sending is in progress, so push back the timeout.
            setupRequestTimer(transaction);

            doWrite(transaction);
        }
    }

    // Since each transaction has its own output buffer, it is not really
    // possible that the number of bytes written is larger than the size
    // of the buffer. But, let's be safe and set the length to the size
    // of the buffer if that unexpected condition occurs.
    if (length > transaction->getOutputBufSize()) {
        length = transaction->getOutputBufSize();
    }

    if (length <= transaction->getOutputBufSize()) {
        // Sending is in progress, so push back the timeout.
        setupRequestTimer(transaction);
    }

    // Eat the 'length' number of bytes from the output buffer and only
    // leave the part of the response that hasn't been sent.
    transaction->consumeOutputBuf(length);

    // Schedule the write of the unsent data.
    doWrite(transaction);
}

void
HttpConnection::setupRequestTimer(TransactionPtr transaction) {
    // Pass raw pointer rather than shared_ptr to this object,
    // because IntervalTimer already passes shared pointer to the
    // IntervalTimerImpl to make sure that the callback remains
    // valid.
    request_timer_.setup(std::bind(&HttpConnection::requestTimeoutCallback,
                                   this, transaction),
                         request_timeout_, IntervalTimer::ONE_SHOT);
}

void
HttpConnection::setupIdleTimer() {
    request_timer_.setup(std::bind(&HttpConnection::idleTimeoutCallback,
                                   this),
                         idle_timeout_, IntervalTimer::ONE_SHOT);
}

void
HttpConnection::requestTimeoutCallback(TransactionPtr transaction) {
    LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL,
              HTTP_CLIENT_REQUEST_TIMEOUT_OCCURRED)
        .arg(getRemoteEndpointAddressAsText());

    // We need to differentiate the transactions between a normal response and the
    // timeout. We create new transaction from the current transaction. It is
    // to preserve the request we're responding to.
    auto spawned_transaction = Transaction::spawn(response_creator_, transaction);

    // The new transaction inherits the request from the original transaction
    // if such transaction exists.
    auto request = spawned_transaction->getRequest();

    // Depending on when the timeout occurred, the HTTP version of the request
    // may or may not be available. Therefore we check if the HTTP version is
    // set in the request. If it is not available, we need to create a dummy
    // request with the default HTTP/1.0 version. This version will be used
    // in the response.
    if (request->context()->http_version_major_ == 0) {
        request.reset(new HttpRequest(HttpRequest::Method::HTTP_POST, "/",
                                      HttpVersion::HTTP_10(),
                                      HostHttpHeader("dummy")));
        request->finalize();
    }

    // Create the timeout response.
    HttpResponsePtr response =
        response_creator_->createStockHttpResponse(request,
                                                   HttpStatusCode::REQUEST_TIMEOUT);

    // Send the HTTP 408 status.
    asyncSendResponse(response, spawned_transaction);
}

void
HttpConnection::idleTimeoutCallback() {
    LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL,
              HTTP_IDLE_CONNECTION_TIMEOUT_OCCURRED)
        .arg(getRemoteEndpointAddressAsText());
    // In theory we should shutdown first and stop/close after but
    // it is better to put the connection management responsibility
    // on the client... so simply drop idle connections.
    stopThisConnection();
}

std::string
HttpConnection::getRemoteEndpointAddressAsText() const {
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

} // end of namespace isc::http
} // end of namespace isc
