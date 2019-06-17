// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <http/connection.h>
#include <http/connection_pool.h>
#include <http/http_log.h>
#include <http/http_messages.h>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

using namespace isc::asiolink;

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

HttpConnection::HttpConnection(asiolink::IOService& io_service,
                               HttpAcceptor& acceptor,
                               HttpConnectionPool& connection_pool,
                               const HttpResponseCreatorPtr& response_creator,
                               const HttpAcceptorCallback& callback,
                               const long request_timeout,
                               const long idle_timeout)
    : request_timer_(io_service),
      request_timeout_(request_timeout),
      idle_timeout_(idle_timeout),
      socket_(io_service),
      acceptor_(acceptor),
      connection_pool_(connection_pool),
      response_creator_(response_creator),
      acceptor_callback_(callback) {
}

HttpConnection::~HttpConnection() {
    close();
}

void
HttpConnection::close() {
    request_timer_.cancel();
    socket_.close();
}

void
HttpConnection::stopThisConnection() {
    try {
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                  HTTP_CONNECTION_STOP)
            .arg(getRemoteEndpointAddressAsText());
        connection_pool_.stop(shared_from_this());
    } catch (...) {
        LOG_ERROR(http_logger, HTTP_CONNECTION_STOP_FAILED);
    }
}

void
HttpConnection::asyncAccept() {
    // Create instance of the callback. It is safe to pass the local instance
    // of the callback, because the underlying boost functions make copies
    // as needed.
    HttpAcceptorCallback cb = boost::bind(&HttpConnection::acceptorCallback,
                                          shared_from_this(),
                                          boost::asio::placeholders::error);
    try {
        acceptor_.asyncAccept(socket_, cb);

    } catch (const std::exception& ex) {
        isc_throw(HttpConnectionError, "unable to start accepting TCP "
                  "connections: " << ex.what());
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
        }

        // Create instance of the callback. It is safe to pass the local instance
        // of the callback, because the underlying boost functions make copies
        // as needed.
        SocketCallback cb(boost::bind(&HttpConnection::socketReadCallback,
                                      shared_from_this(),
                                      transaction,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
        socket_.asyncReceive(static_cast<void*>(transaction->getInputBufData()),
                             transaction->getInputBufSize(),
                             0, &endpoint, cb);

    } catch (...) {
        stopThisConnection();
    }
}

void
HttpConnection::doWrite(HttpConnection::TransactionPtr transaction) {
    try {
        if (transaction->outputDataAvail()) {
            // Create instance of the callback. It is safe to pass the local instance
            // of the callback, because the underlying boost functions make copies
            // as needed.
            SocketCallback cb(boost::bind(&HttpConnection::socketWriteCallback,
                                          shared_from_this(),
                                          transaction,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));
            socket_.asyncSend(transaction->getOutputBufData(),
                              transaction->getOutputBufSize(),
                              cb);
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
    if (!acceptor_.isOpen()) {
        return;
    }

    if (ec) {
        stopThisConnection();
    }

    acceptor_callback_(ec);

    if (!ec) {
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  HTTP_REQUEST_RECEIVE_START)
            .arg(getRemoteEndpointAddressAsText())
            .arg(static_cast<unsigned>(request_timeout_/1000));

        setupRequestTimer();
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
    request_timer_.setup(boost::bind(&HttpConnection::requestTimeoutCallback,
                                     this, transaction),
                         request_timeout_, IntervalTimer::ONE_SHOT);
}

void
HttpConnection::setupIdleTimer() {
    request_timer_.setup(boost::bind(&HttpConnection::idleTimeoutCallback,
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

    // Depending on when the timeout occured, the HTTP version of the request
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
    stopThisConnection();
}

std::string
HttpConnection::getRemoteEndpointAddressAsText() const {
    try {
        if (socket_.getASIOSocket().is_open()) {
            return (socket_.getASIOSocket().remote_endpoint().address().to_string());
        }
    } catch (...) {
    }
    return ("(unknown address)");
}


} // end of namespace isc::http
} // end of namespace isc

