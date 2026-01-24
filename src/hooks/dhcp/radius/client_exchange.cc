// Copyright (C) 2023-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/udp_endpoint.h>
#include <asiolink/udp_socket.h>
#include <cryptolink/crypto_rng.h>
#include <util/multi_threading_mgr.h>
#include <util/unlock_guard.h>
#include <client_exchange.h>
#include <radius.h>
#include <radius_log.h>

#include <cerrno>
#include <chrono>
#include <limits>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::tcp;
using namespace isc::util;
using namespace std;
using namespace std::chrono;
namespace ph = std::placeholders;

namespace isc {
namespace radius {

string
exchangeRCtoText(const int rc) {
    ostringstream result;
    switch (rc) {
    case BADRESP_RC:
        return ("bad response");
    case ERROR_RC:
        return ("error");
    case OK_RC:
        return ("ok");
    case TIMEOUT_RC:
        return ("timeout");
    case REJECT_RC:
        return ("reject");
    case READBLOCK_RC:
        return ("temporarily unavailable");
    default:
        result << (rc < 0 ? "error " : "unknown ") << rc;
        return (result.str());
    }
}

Exchange::Exchange(const MessagePtr& request,
                   unsigned maxretries,
                   const Servers& servers,
                   Handler handler)
    : identifier_(""), sync_(false), rc_(ERROR_RC),
      request_(request), sent_(), received_(),
      maxretries_(maxretries), servers_(servers), handler_(handler) {
    if (!request) {
        isc_throw(BadValue, "null request");
    }
    if (servers.empty()) {
        isc_throw(BadValue, "no server");
    }
    if (!handler) {
        isc_throw(BadValue, "null handler");
    }
    createIdentifier();
}

Exchange::Exchange(const MessagePtr& request,
                   unsigned maxretries,
                   const Servers& servers)
    : identifier_(""), sync_(true), rc_(ERROR_RC),
      request_(request), sent_(), received_(),
      maxretries_(maxretries), servers_(servers), handler_() {
    if (!request) {
        isc_throw(BadValue, "null request");
    }
    if (servers.empty()) {
        isc_throw(BadValue, "no server");
    }
    createIdentifier();
}

ExchangePtr
Exchange::create(const asiolink::IOServicePtr io_service,
                 const MessagePtr& request,
                 unsigned maxretries,
                 const Servers& servers,
                 Handler handler,
                 RadiusProtocol protocol) {
    if (protocol == PW_PROTO_UDP) {
        return (UdpExchangePtr(new UdpExchange(io_service, request, maxretries,
                                               servers, handler)));
    } else {
        return (TcpExchangePtr(new TcpExchange(request, maxretries,
                                               servers, handler)));
    }
}

ExchangePtr
Exchange::create(const MessagePtr& request,
                 unsigned maxretries,
                 const Servers& servers) {
    return (UdpExchangePtr(new UdpExchange(request, maxretries, servers)));
}

UdpExchange::UdpExchange(const asiolink::IOServicePtr io_service,
                         const MessagePtr& request,
                         unsigned maxretries,
                         const Servers& servers,
                         Handler handler)
    : Exchange(request, maxretries, servers, handler),
      io_service_(io_service), started_(false), terminated_(false),
      start_time_(std::chrono::steady_clock().now()),
      socket_(), ep_(), timer_(), server_(), idx_(0),
      buffer_(), size_(0), retries_(0), postponed_(),
      mutex_(new std::mutex()) {
    if (!io_service) {
        isc_throw(BadValue, "null IO service");
    }
}

UdpExchange::UdpExchange(const MessagePtr& request,
                         unsigned maxretries,
                         const Servers& servers)
    : Exchange(request, maxretries, servers),
      io_service_(new IOService()),
      started_(false), terminated_(false),
      start_time_(std::chrono::steady_clock().now()),
      socket_(), ep_(), timer_(), server_(), idx_(0),
      buffer_(), size_(0), retries_(0), postponed_(),
      mutex_(new std::mutex()) {
}

UdpExchange::~UdpExchange() {
    MultiThreadingLock lock(*mutex_);
    shutdownInternal();
    timer_.reset();
    socket_.reset();
    if (sync_ && io_service_) {
        // As a best practice, call any remaining handlers.
        io_service_->stopAndPoll();
        io_service_.reset();
    }
}

void
Exchange::createIdentifier() {
    vector<uint8_t> rv = cryptolink::random(sizeof(uint32_t));
    if (rv.size() != sizeof(uint32_t)) {
        isc_throw(Unexpected, "random failed");
    }
    uint32_t ri;
    memmove(&ri, &rv[0], sizeof(uint32_t));
    ostringstream rs;
    rs << hex << setfill('0') << setw(8) << ri;
    identifier_ = rs.str();
}
void
Exchange::logReplyMessages() const {
    if (!received_) {
        return;
    }
    const AttributesPtr& attrs = received_->getAttributes();
    if (!attrs || (attrs->count(PW_REPLY_MESSAGE) == 0)) {
        return;
    }
    for (const ConstAttributePtr& attr : *attrs) {
        if (!attr || (attr->getType() != PW_REPLY_MESSAGE)) {
            continue;
        }
        LOG_INFO(radius_logger, RADIUS_REPLY_MESSAGE_ATTRIBUTE)
            .arg(static_cast<int>(received_->getIdentifier()))
            .arg(identifier_)
            .arg(attr->toString());
    }
}

void
UdpExchange::start() {
    MultiThreadingLock lock(*mutex_);

    if (started_) {
        return;
    } else {
        started_ = true;
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_EXCHANGE_START)
      .arg(identifier_);

    open();

    if (sync_) {
        // Run() will return when syncHandler will be called.
        io_service_->run();

        // Done.
        io_service_.reset();

        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_EXCHANGE_SYNC_RETURN)
            .arg(identifier_)
            .arg(rc_);
    }
}

void
UdpExchange::shutdown() {
    // Avoid multiple terminations.
    MultiThreadingLock lock(*mutex_);
    shutdownInternal();
}

void
UdpExchange::shutdownInternal() {
    if (terminated_) {
        return;
    } else {
        terminated_ = true;
    }
    // Same as terminate but not calling callback.
    cancelTimer();
    if (socket_) {
        socket_->cancel();
    }
    handler_ = Handler();

    if (io_service_) {
        if (sync_) {
            io_service_->stopWork();
        } else {
            io_service_.reset();
        }
    }
}

void
Exchange::buildRequest(const ServerPtr& server,
                       std::chrono::steady_clock::time_point start_time) {
    if (!server) {
        isc_throw(Unexpected, "no server");
    }

    // Prepare message to send.
    sent_.reset(new Message(*request_));

    // Randomize the identifier.
    sent_->randomIdentifier();

    // Randomize or zero the authenticator.
    if ((sent_->getCode() == PW_ACCESS_REQUEST) ||
        (sent_->getCode() == PW_STATUS_SERVER))  {
        sent_->randomAuth();
    } else {
        sent_->zeroAuth();
    }

    // Set the secret.
    sent_->setSecret(server->getSecret());

    // Get attributes.
    AttributesPtr attrs = sent_->getAttributes();
    if (!attrs) {
        attrs.reset(new Attributes());
        sent_->setAttributes(attrs);
    }

    // Add Acct-Delay-Time to Accounting-Request message.
    if ((sent_->getCode() == PW_ACCOUNTING_REQUEST) &&
        (attrs->count(PW_ACCT_DELAY_TIME) == 0)) {
        auto delta = steady_clock().now() - start_time;
        seconds secs = duration_cast<seconds>(delta);
        attrs->add(Attribute::fromInt(PW_ACCT_DELAY_TIME,
                                      static_cast<uint32_t>(secs.count())));
    }

    // Add NAS-IP[v6]-Address with the local address.
    IOAddress local_addr = server->getLocalAddress();
    short family = local_addr.getFamily();
    if (family == AF_INET) {
        if (attrs->count(PW_NAS_IP_ADDRESS) == 0) {
            attrs->add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS, local_addr));
        }
    } else if (family == AF_INET6) {
        if (attrs->count(PW_NAS_IPV6_ADDRESS) == 0) {
            attrs->add(Attribute::fromIpv6Addr(PW_NAS_IPV6_ADDRESS,
                                               local_addr));
        }
    }

    // Add Message-Authenticator to Status-Server message.
    if ((sent_->getCode() == PW_STATUS_SERVER) &&
        (attrs->count(PW_MESSAGE_AUTHENTICATOR) == 0)) {
        const vector<uint8_t> zero(AUTH_VECTOR_LEN);
        // The FreeRADIUS server prefers to get it first.
        attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, zero),
                   false);
    }

    // Encode the request.
    sent_->encode();
}

void
UdpExchange::buildRequest() {
    Exchange::buildRequest(server_, start_time_);
}

void
TcpExchange::buildRequest() {
    Exchange::buildRequest(server_, start_time_);
}

void
UdpExchange::open() {
    if (RadiusImpl::shutdown_) {
        shutdownInternal();
        return;
    }

    if (terminated_) {
        return;
    }
    // In order:
    //  - no current server: open the next one.
    //  - last try.
    //  - next try.

    if (!server_) {
        // No server: get the next server.
        if (idx_ < servers_.size()) {
            // First pass.
            server_ = servers_[idx_];
            // Null pointer (should not happen).
            if (!server_) {
                isc_throw(Unexpected, "null server at " << idx_);
            }
            // Server still in hold-down: postpone it.
            if ((server_->getDeadtime() > 0) &&
                (server_->getDeadtimeEnd() > start_time_)) {
                postponed_.push_back(idx_);
                ++idx_;
                io_service_->post(std::bind(&UdpExchange::openNext,
                                            shared_from_this()));
                return;
            }
        } else {
            // Second pass: try postponed servers.
            if (postponed_.empty()) {
                io_service_->post(std::bind(&UdpExchange::terminate,
                                            shared_from_this()));
                return;
            }
            size_t cur_idx = postponed_.front();
            // Out-of-range (should not happen).
            if (cur_idx >= servers_.size()) {
                isc_throw(Unexpected, "out of range server " << cur_idx
                          << " >= " << servers_.size());
            }
            server_ = servers_[cur_idx];
            // Null pointer (should not happen).
            if (!server_) {
                isc_throw(Unexpected, "null server at " <<  cur_idx);
            }
        }

        // Have a new server.
        try {
            // Reset error code.
            rc_ = ERROR_RC;

            // Build to be send request message.
            buildRequest();

            // Set end-point.
            ep_.reset(new UDPEndpoint(server_->getPeerAddress(),
                                      server_->getPeerPort()));

            // Set socket.
            if (socket_) {
                socket_->close();
            }
            socket_.reset(new RadiusSocket(io_service_));

            // Launch timer.
            setTimer();

            // Open socket.
            socket_->open(ep_.get(), SocketCallback());

            // Should bind the socket but it is not (yet) in the API.
            // Anyway the kernel should choose the same address...

            // Better to use a connected socket...

            // Send request message.
            buffer_ = sent_->getBuffer();
            size_ = buffer_.size();

            LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                      RADIUS_EXCHANGE_SEND_NEW)
                .arg(identifier_)
                .arg(buffer_.size())
                .arg(idx_)
                .arg(ep_->getAddress().toText())
                .arg(ep_->getPort());

            socket_->asyncSend(&buffer_[0], buffer_.size(), ep_.get(),
                               std::bind(&UdpExchange::sentHandler,
                                         shared_from_this(),
                                         ph::_1,   // error_code.
                                         ph::_2)); // size.
            return;
        } catch (const Exception& exc) {
            LOG_ERROR(radius_logger, RADIUS_EXCHANGE_OPEN_FAILED)
                .arg(identifier_)
                .arg(exc.what());
            cancelTimer();
            rc_ = ERROR_RC;
            if (socket_) {
                socket_->close();
                socket_.reset();
            }
            io_service_->post(std::bind(&UdpExchange::openNext,
                                        shared_from_this()));
            return;
        }
    }

    // No other try?
    if (retries_++ >= maxretries_) {
        if ((rc_ == TIMEOUT_RC) && (idx_ < servers_.size())) {
            // On timeout hold-down the server.
            unsigned deadtime = server_->getDeadtime();
            if (deadtime > 0) {
                server_->setDeadtimeEnd(start_time_ + seconds(deadtime));
            }
        }
        retries_ = 0;
        server_.reset();
        ep_.reset();
        // Try postponed servers?
        if (idx_ == servers_.size()) {
            // Postponed servers are exhausted.
            if (postponed_.size() < 2) {
                io_service_->post(std::bind(&UdpExchange::terminate,
                                            shared_from_this()));
                return;
            }
            // Try next postponed server.
            postponed_.pop_front();
        } else {
            // Try next server.
            ++idx_;
            if ((idx_ == servers_.size()) && (postponed_.empty())) {
                io_service_->post(std::bind(&UdpExchange::terminate,
                                            shared_from_this()));
                return;
            }
        }
        // Call again open to try the next server.
        io_service_->post(std::bind(&UdpExchange::openNext,
                                    shared_from_this()));
        return;
    }

    // Next try.
    try {
        if (!ep_) {
            isc_throw(Unexpected, "endpoint is null");
        }

        // Build to be send request message.
        buildRequest();

        // Set socket.
        if (socket_) {
            socket_->close();
        }
        socket_.reset(new RadiusSocket(io_service_));

        // Launch timer.
        setTimer();

        // Open socket.
        socket_->open(ep_.get(), SocketCallback());

        // Should bind the socket but it is not (yet) in the API.
        // Anyway the kernel should choose the same address...

        // Better to use a connected socket...

        // Send request message.
        buffer_ = sent_->getBuffer();
        size_ = buffer_.size();

        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_EXCHANGE_SEND_RETRY)
            .arg(identifier_)
            .arg(buffer_.size())
            .arg(retries_);

        socket_->asyncSend(&buffer_[0],
                           buffer_.size(),
                           ep_.get(),
                           std::bind(&UdpExchange::sentHandler,
                                     shared_from_this(),
                                     ph::_1,   // error_code.
                                     ph::_2)); // size.
        return;
    } catch (const Exception& exc) {
        LOG_ERROR(radius_logger, RADIUS_EXCHANGE_OPEN_FAILED)
            .arg(identifier_)
            .arg(exc.what());
        cancelTimer();
        rc_ = ERROR_RC;
        if (socket_) {
            socket_->close();
            socket_.reset();
        }
        io_service_->post(std::bind(&UdpExchange::openNext,
                                    shared_from_this()));
        return;
    }
}

void
UdpExchange::sentHandler(UdpExchangePtr ex,
                         const boost::system::error_code ec,
                         const size_t size) {
    if (!ex) {
        isc_throw(Unexpected, "null exchange in sentHandler");
    }

    if (RadiusImpl::shutdown_) {
        ex->shutdown();
        return;
    }

    MultiThreadingLock lock(*ex->mutex_);

    if (ex->terminated_) {
        return;
    }

    // Check error code.
    if (ec) {
        LOG_ERROR(radius_logger, RADIUS_EXCHANGE_SEND_FAILED)
            .arg(ex->identifier_)
            .arg(ec.message());
        ex->cancelTimer();
        if (ex->socket_) {
            ex->socket_->close();
            ex->socket_.reset();
        }
        ex->io_service_->post(std::bind(&UdpExchange::openNext, ex));
        return;
    }

    // No error: receive response.
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_EXCHANGE_SENT)
        .arg(ex->identifier_)
        .arg(size);
    ex->buffer_.clear();
    ex->buffer_.resize(BUF_LEN);
    ex->size_ = ex->buffer_.size();
    ex->socket_->asyncReceive(&(ex->buffer_)[0], ex->size_, 0, ex->ep_.get(),
                              std::bind(&UdpExchange::receivedHandler,
                                        ex,
                                        ph::_1,   // error_code.
                                        ph::_2)); // size.
}

void
Exchange::processResponse() {
    // Decode message.
    rc_ = OK_RC;
    try {
        // In order:
        //  - decode message.
        //  - verify that identifiers match.
        //  - verify that message codes match.
        received_->decode();
        unsigned got = received_->getIdentifier();
        unsigned expected = sent_->getIdentifier();
        if (got != expected) {
            LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_MISMATCH)
                .arg(identifier_)
                .arg(got)
                .arg(expected);
            rc_ = BADRESP_RC;
        } else if (request_->getCode() == PW_ACCESS_REQUEST) {
            if (received_->getCode() == PW_ACCESS_REJECT) {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCESS_REJECT)
                    .arg(identifier_);
                rc_ = REJECT_RC;
            } else if (received_->getCode() != PW_ACCESS_ACCEPT) {
                LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_UNEXPECTED)
                    .arg(identifier_)
                    .arg(msgCodeToText(request_->getCode()))
                    .arg(msgCodeToText(received_->getCode()));
                rc_ = BADRESP_RC;
            } else {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCESS_ACCEPT)
                    .arg(identifier_);
            }
        } else if (request_->getCode() == PW_ACCOUNTING_REQUEST) {
            if (received_->getCode() != PW_ACCOUNTING_RESPONSE) {
                LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_UNEXPECTED)
                    .arg(identifier_)
                    .arg(msgCodeToText(request_->getCode()))
                    .arg(msgCodeToText(received_->getCode()));
                rc_ = BADRESP_RC;
            } else {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCOUNTING_RESPONSE)
                    .arg(identifier_);
            }
        } else if (request_->getCode() == PW_STATUS_SERVER) {
            if (received_->getCode() == PW_ACCESS_ACCEPT) {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCESS_ACCEPT)
                    .arg(identifier_);
            } else if (received_->getCode() == PW_ACCESS_REJECT) {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCESS_REJECT)
                    .arg(identifier_);
            } else if (received_->getCode() == PW_ACCOUNTING_RESPONSE) {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCOUNTING_RESPONSE)
                    .arg(identifier_);
            } else {
                LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_UNEXPECTED)
                    .arg(identifier_)
                    .arg(msgCodeToText(request_->getCode()))
                    .arg(msgCodeToText(received_->getCode()));
                rc_ = BADRESP_RC;
            }
        }
    } catch (const Exception& exc) {
        LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_BAD_RESPONSE)
            .arg(identifier_)
            .arg(exc.what());
        rc_ = BADRESP_RC;
    }

    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
              RADIUS_EXCHANGE_RECEIVED_RESPONSE)
        .arg(identifier_)
        .arg(exchangeRCtoText(rc_));
}

void
UdpExchange::receivedHandler(UdpExchangePtr ex,
                             const boost::system::error_code ec,
                             const size_t size) {
    if (!ex) {
        isc_throw(Unexpected, "null exchange in receivedHandler");
    }

    if (RadiusImpl::shutdown_) {
        ex->shutdown();
        return;
    }

    MultiThreadingLock lock(*ex->mutex_);

    // This was the action on the socket.
    ex->cancelTimer();
    if (ex->socket_) {
        ex->socket_->close();
        ex->socket_.reset();
    }

    if (ex->terminated_) {
        return;
    }

    // Check error code.
    if (ec) {
        LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVE_FAILED)
            .arg(ex->identifier_)
            .arg(ec.message());
        ex->io_service_->post(std::bind(&UdpExchange::openNext, ex));
        return;
    }

    // Remove the server from hold-down.
    if (ex->server_ &&
        (ex->server_->getDeadtime() > 0) &&
        (ex->server_->getDeadtimeEnd() > ex->start_time_)) {
        ex->server_->setDeadtimeEnd(ex->start_time_);
    }

    // Create message.
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_EXCHANGE_RECEIVED)
        .arg(ex->identifier_)
        .arg(size);
    ex->buffer_.resize(size);
    ex->received_.reset(new Message(ex->buffer_, ex->sent_->getAuth(),
                                    ex->server_->getSecret()));

    ex->processResponse();

    // If bad then retry, if not including reject it is done.
    if ((ex->rc_ != OK_RC) && (ex->rc_ != REJECT_RC)) {
        ex->io_service_->post(std::bind(&UdpExchange::openNext, ex));
    } else {
        ex->logReplyMessages();
        ex->io_service_->post(std::bind(&UdpExchange::terminate, ex));
    }
}

void
UdpExchange::terminate() {
    // Avoid multiple terminations.
    MultiThreadingLock lock(*mutex_);

    if (terminated_) {
        return;
    } else {
        terminated_ = true;
    }

    // Should have been done before.
    cancelTimer();
    if (socket_) {
        socket_->close();
        socket_.reset();
    }

    if ((rc_ != OK_RC) && (rc_ != REJECT_RC)) {
        LOG_ERROR(radius_logger, RADIUS_EXCHANGE_FAILED)
            .arg(identifier_)
            .arg(exchangeRCtoText(rc_));
    } else {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_EXCHANGE_TERMINATE)
            .arg(identifier_)
            .arg(exchangeRCtoText(rc_));
    }

    if (io_service_) {
        if (sync_) {
            io_service_->stopWork();
        } else {
            io_service_.reset();
        }
    }

    // Call handler.
    if (handler_) {
        auto handler = handler_;
        // Avoid to keep a circular reference.
        handler_ = Handler();
        if (MultiThreadingMgr::instance().getMode()) {
            UnlockGuard<std::mutex> unlock(*mutex_);
            handler(shared_from_this());
        } else {
            handler(shared_from_this());
        }
    }
}

void
UdpExchange::setTimer() {
    cancelTimer();
    timer_.reset(new IntervalTimer(io_service_));
    timer_->setup(std::bind(&UdpExchange::timeoutHandler, shared_from_this()),
                  server_->getTimeout() * 1000, IntervalTimer::ONE_SHOT);
}

void
UdpExchange::cancelTimer() {
    if (timer_) {
        timer_->cancel();
        timer_.reset();
    }
}

void
UdpExchange::timeoutHandler(UdpExchangePtr ex) {
    MultiThreadingLock lock(*ex->mutex_);
    LOG_ERROR(radius_logger, RADIUS_EXCHANGE_TIMEOUT)
        .arg(ex->identifier_);
    ex->rc_ = TIMEOUT_RC;
    ex->cancelTimer();
    if (ex->socket_) {
        ex->socket_->cancel();
    }
}

TcpExchange::TcpExchange(const MessagePtr& request,
                         unsigned maxretries,
                         const Servers& servers,
                         Handler handler)
    : Exchange(request, maxretries, servers, handler),
      start_time_(std::chrono::steady_clock().now()),
      server_(), resp_() {
    server_ = servers_[0];
}

void
TcpExchange::start() {
    if (RadiusImpl::shutdown_) {
        shutdown();
    }

    if (!server_) {
        isc_throw(Unexpected, "no server");
    }

    try {
        // Reset error code.
        rc_ = ERROR_RC;

        // Build to be send request message.
        buildRequest();

        // Build write data request.
        WireDataPtr request(new WireData(sent_->getBuffer()));

        ///// Log.

        RadiusImpl::instance().tcp_client_->asyncSendRequest(
            server_->getPeerAddress(),
            server_->getPeerPort(),
            server_->getTlsContext(),
            request,
            resp_,
            true,
            TcpExchange::CompleteCheck,
            std::bind(&TcpExchange::RequestHandler,
                      shared_from_this(),
                      ph::_1,   // error_code
                      ph::_2,   // response
                      ph::_3),  // error_msg
            TcpClient::RequestTimeout(server_->getTimeout() * 1000));
    } catch (const Exception& exc) {
        ///// Log.
        rc_ = ERROR_RC;
        // Call handler.
        if (handler_) {
            auto handler = handler_;
            // Avoid to keep a circular reference.
            handler_ = Handler();
            handler(shared_from_this());
        }
    }
}

void
TcpExchange::shutdown() {
    handler_ = Handler();
}

void
TcpExchange::RequestHandler(TcpExchangePtr ex,
                            const boost::system::error_code& ec,
                            const WireDataPtr& response,
                            const string& error_msg) {
    if (!ex) {
        isc_throw(Unexpected, "null exchange in receivedHandler");
    }

    if (RadiusImpl::shutdown_) {
        return;
    }

    // Check error code.
    if (ec) {
        ///// log
        if (ec == boost::asio::error::timed_out) {
            ex->rc_ = TIMEOUT_RC;
        } else {
            ex->rc_ = ERROR_RC;
        }
        // Call handler.
        if (ex->handler_) {
            auto handler = ex->handler_;
            // Avoid to keep a circular reference.
            ex->handler_ = Handler();
            handler(ex);
        }
        return;
    }

    //// log
    const WireData& buffer = *response;
    ex->received_.reset(new Message(buffer, ex->sent_->getAuth(),
                                    ex->server_->getSecret()));

    ex->processResponse();

    if ((ex->rc_ == OK_RC) || (ex->rc_ == REJECT_RC)) {
        ex->logReplyMessages();
    }
    // Call handler.
    if (ex->handler_) {
        auto handler = ex->handler_;
        // Avoid to keep a circular reference.
        ex->handler_ = Handler();
        handler(ex);
    }
}

int
TcpExchange::CompleteCheck(const WireDataPtr& response, string& error_msg) {
    if (!response) {
        error_msg = "null response";
        return (-1);
    }
    const WireData& buffer = *response;
    if (buffer.size() < AUTH_HDR_LEN) {
        return (0);
    }
    uint16_t length = static_cast<uint16_t>(buffer[2]) << 8;
    length |= static_cast<uint16_t>(buffer[3]);
    if (length > buffer.size()) {
        return (0);
    } else if (length == buffer.size()) {
        return (1);
    } else {
        error_msg = "overflow";
        return (-2);
    }
}

} // end of namespace isc::radius
} // end of namespace isc
