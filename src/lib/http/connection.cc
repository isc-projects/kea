// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
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

using namespace isc::asiolink;

namespace {

/// @brief Maximum size of the HTTP message that can be logged.
///
/// The part of the HTTP message beyond this value is truncated.
constexpr size_t MAX_LOGGED_MESSAGE_SIZE = 1024;

}

namespace isc {
namespace http {

void
HttpConnection::
SocketCallback::operator()(boost::system::error_code ec, size_t length) {
    if (ec.value() == boost::asio::error::operation_aborted) {
        return;
    }
    callback_(ec, length);
}

HttpConnection:: HttpConnection(asiolink::IOService& io_service,
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
      request_(response_creator_->createNewHttpRequest()),
      parser_(new HttpRequestParser(*request_)),
      acceptor_callback_(callback),
      buf_(),
      output_buf_() {
    parser_->initModel();
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
HttpConnection::doRead() {
    try {
        TCPEndpoint endpoint;
        // Create instance of the callback. It is safe to pass the local instance
        // of the callback, because the underlying boost functions make copies
        // as needed.
        SocketCallback cb(boost::bind(&HttpConnection::socketReadCallback,
                                      shared_from_this(),
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
        socket_.asyncReceive(static_cast<void*>(buf_.data()), buf_.size(),
                             0, &endpoint, cb);

    } catch (...) {
        stopThisConnection();
    }
}

void
HttpConnection::doWrite() {
    try {
        if (!output_buf_.empty()) {
            // Create instance of the callback. It is safe to pass the local instance
            // of the callback, because the underlying boost functions make copies
            // as needed.
            SocketCallback cb(boost::bind(&HttpConnection::socketWriteCallback,
                                          shared_from_this(),
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));
            socket_.asyncSend(output_buf_.data(),
                              output_buf_.length(),
                              cb);
        } else {
            if (!request_->isPersistent()) {
                stopThisConnection();

            } else {
                reinitProcessingState();
                doRead();
            }
        }
    } catch (...) {
        stopThisConnection();
    }
}

void
HttpConnection::asyncSendResponse(const ConstHttpResponsePtr& response) {
    output_buf_ = response->toString();
    doWrite();
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
HttpConnection::socketReadCallback(boost::system::error_code ec, size_t length) {
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
    setupRequestTimer();

    if (length != 0) {
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
                  HTTP_DATA_RECEIVED)
            .arg(length)
            .arg(getRemoteEndpointAddressAsText());

        std::string s(&buf_[0], buf_[0] + length);
        parser_->postBuffer(static_cast<void*>(buf_.data()), length);
        parser_->poll();
    }

    if (parser_->needData()) {
        doRead();

    } else {
        try {
            request_->finalize();

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                      HTTP_CLIENT_REQUEST_RECEIVED)
                .arg(getRemoteEndpointAddressAsText());

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                      HTTP_CLIENT_REQUEST_RECEIVED_DETAILS)
                .arg(getRemoteEndpointAddressAsText())
                .arg(parser_->getBufferAsString(MAX_LOGGED_MESSAGE_SIZE));

        } catch (const std::exception& ex) {
            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                      HTTP_BAD_CLIENT_REQUEST_RECEIVED)
                .arg(getRemoteEndpointAddressAsText())
                .arg(ex.what());

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                      HTTP_BAD_CLIENT_REQUEST_RECEIVED_DETAILS)
                .arg(getRemoteEndpointAddressAsText())
                .arg(parser_->getBufferAsString(MAX_LOGGED_MESSAGE_SIZE));
        }

        // Don't want to timeout if creation of the response takes long.
        request_timer_.cancel();

        HttpResponsePtr response = response_creator_->createHttpResponse(request_);
        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                  HTTP_SERVER_RESPONSE_SEND)
            .arg(response->toBriefString())
            .arg(getRemoteEndpointAddressAsText());

        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                  HTTP_SERVER_RESPONSE_SEND_DETAILS)
            .arg(getRemoteEndpointAddressAsText())
            .arg(HttpMessageParserBase::logFormatHttpMessage(response->toString(),
                                                             MAX_LOGGED_MESSAGE_SIZE));

        // Response created. Active timer again.
        setupRequestTimer();

        asyncSendResponse(response);
    }
}

void
HttpConnection::socketWriteCallback(boost::system::error_code ec, size_t length) {
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
            setupRequestTimer();

            doWrite();
        }
    }


    if (length <= output_buf_.size()) {
        // Sending is in progress, so push back the timeout.
        setupRequestTimer();

        output_buf_.erase(0, length);
        doWrite();

    } else {
        output_buf_.clear();

        if (!request_->isPersistent()) {
            stopThisConnection();

        } else {
            reinitProcessingState();
            doRead();
        }
    }
}

void
HttpConnection::reinitProcessingState() {
    request_ = response_creator_->createNewHttpRequest();
    parser_.reset(new HttpRequestParser(*request_));
    parser_->initModel();
    setupIdleTimer();
}

void
HttpConnection::setupRequestTimer() {
    // Pass raw pointer rather than shared_ptr to this object,
    // because IntervalTimer already passes shared pointer to the
    // IntervalTimerImpl to make sure that the callback remains
    // valid.
    request_timer_.setup(boost::bind(&HttpConnection::requestTimeoutCallback,
                                     this),
                         request_timeout_, IntervalTimer::ONE_SHOT);
}

void
HttpConnection::setupIdleTimer() {
    request_timer_.setup(boost::bind(&HttpConnection::idleTimeoutCallback,
                                     this),
                         idle_timeout_, IntervalTimer::ONE_SHOT);
}

void
HttpConnection::requestTimeoutCallback() {
    LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL,
              HTTP_CLIENT_REQUEST_TIMEOUT_OCCURRED)
        .arg(getRemoteEndpointAddressAsText());
    HttpResponsePtr response =
        response_creator_->createStockHttpResponse(request_,
                                                   HttpStatusCode::REQUEST_TIMEOUT);
    asyncSendResponse(response);
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

