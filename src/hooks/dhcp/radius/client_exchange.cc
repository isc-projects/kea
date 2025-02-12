// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
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

Exchange::Exchange(const asiolink::IOServicePtr io_service,
                   const MessagePtr& request,
                   unsigned maxretries,
                   const Servers& servers,
                   Handler handler)
    : identifier_(""), io_service_(io_service), sync_(false),
      started_(false), terminated_(false), rc_(ERROR_RC),
      start_time_(std::chrono::steady_clock().now()),
      socket_(), ep_(), timer_(), server_(), idx_(0),
      request_(request), sent_(), received_(), buffer_(), size_(0),
      retries_(0), maxretries_(maxretries), servers_(servers),
      postponed_(), handler_(handler), mutex_(new std::mutex()) {
    if (!io_service) {
        isc_throw(BadValue, "null IO service");
    }
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
    : identifier_(""), io_service_(new IOService()), sync_(true),
      started_(false), terminated_(false), rc_(ERROR_RC),
      start_time_(std::chrono::steady_clock().now()),
      socket_(), ep_(), timer_(), server_(), idx_(0),
      request_(request), sent_(), received_(), buffer_(), size_(0),
      retries_(0), maxretries_(maxretries), servers_(servers), postponed_(),
      handler_(), mutex_(new std::mutex()) {

    if (!request) {
        isc_throw(BadValue, "null request");
    }
    if (servers.empty()) {
        isc_throw(BadValue, "no server");
    }
    createIdentifier();
}

Exchange::~Exchange() {
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
Exchange::start() {
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
Exchange::shutdown() {
    // Avoid multiple terminations.
    MultiThreadingLock lock(*mutex_);
    shutdownInternal();
}

void
Exchange::shutdownInternal() {
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
Exchange::buildRequest() {
    if (!server_) {
        isc_throw(Unexpected, "no server");
    }

    // Prepare message to send.
    sent_.reset(new Message(*request_));

    // Randomize the identifier.
    sent_->randomIdentifier();

    // Randomize or zero the authenticator.
    if (sent_->getCode() == PW_ACCESS_REQUEST) {
        sent_->randomAuth();
    } else {
        sent_->zeroAuth();
    }

    // Set the secret.
    sent_->setSecret(server_->getSecret());

    // Get attributes.
    AttributesPtr attrs = sent_->getAttributes();
    if (!attrs) {
        attrs.reset(new Attributes());
        sent_->setAttributes(attrs);
    }

    // Add Acct-Delay-Time to Accounting-Request message.
    if ((sent_->getCode() == PW_ACCOUNTING_REQUEST) &&
        (attrs->count(PW_ACCT_DELAY_TIME) == 0)) {
        auto delta = steady_clock().now() - start_time_;
        seconds secs = duration_cast<seconds>(delta);
        attrs->add(Attribute::fromInt(PW_ACCT_DELAY_TIME,
                                      static_cast<uint32_t>(secs.count())));
    }

    // Add NAS-IP[v6]-Address with the local address.
    IOAddress local_addr = server_->getLocalAddress();
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

    // Encode the request.
    sent_->encode();
}

void
Exchange::open() {
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
                io_service_->post(std::bind(&Exchange::openNext,
                                            shared_from_this()));
                return;
            }
        } else {
            // Second pass: try postponed servers.
            if (postponed_.empty()) {
                io_service_->post(std::bind(&Exchange::terminate,
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
                               std::bind(&Exchange::sentHandler,
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
            io_service_->post(std::bind(&Exchange::openNext,
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
                io_service_->post(std::bind(&Exchange::terminate,
                                            shared_from_this()));
                return;
            }
            // Try next postponed server.
            postponed_.pop_front();
        } else {
            // Try next server.
            ++idx_;
            if ((idx_ == servers_.size()) && (postponed_.empty())) {
                io_service_->post(std::bind(&Exchange::terminate,
                                            shared_from_this()));
                return;
            }
        }
        // Call again open to try the next server.
        io_service_->post(std::bind(&Exchange::openNext,
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
                                std::bind(&Exchange::sentHandler,
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
        io_service_->post(std::bind(&Exchange::openNext,
                                    shared_from_this()));
        return;
    }
}

void
Exchange::sentHandler(ExchangePtr ex,
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
        ex->io_service_->post(std::bind(&Exchange::openNext, ex));
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
                              std::bind(&Exchange::receivedHandler, ex,
                                        ph::_1,   // error_code.
                                        ph::_2)); // size.
}

void
Exchange::receivedHandler(ExchangePtr ex,
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
        ex->io_service_->post(std::bind(&Exchange::openNext, ex));
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

    // Decode message.
    ex->rc_ = OK_RC;
    try {
        // In order:
        //  - decode message.
        //  - verify that identifiers match.
        //  - verify that message codes match.
        ex->received_->decode();
        unsigned got = ex->received_->getIdentifier();
        unsigned expected = ex->sent_->getIdentifier();
        if (got != expected) {
            LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_MISMATCH)
                .arg(ex->identifier_)
                .arg(got)
                .arg(expected);
            ex->rc_ = BADRESP_RC;
        } else if (ex->request_->getCode() == PW_ACCESS_REQUEST) {
            if (ex->received_->getCode() == PW_ACCESS_REJECT) {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCESS_REJECT)
                    .arg(ex->identifier_);
                ex->rc_ = REJECT_RC;
            } else if (ex->received_->getCode() != PW_ACCESS_ACCEPT) {
                LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_UNEXPECTED)
                    .arg(ex->identifier_)
                    .arg(msgCodeToText(ex->request_->getCode()))
                    .arg(msgCodeToText(ex->received_->getCode()));
                ex->rc_ = BADRESP_RC;
            } else {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCESS_ACCEPT)
                    .arg(ex->identifier_);
            }
        } else if (ex->request_->getCode() == PW_ACCOUNTING_REQUEST) {
            if (ex->received_->getCode() != PW_ACCOUNTING_RESPONSE) {
                LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_UNEXPECTED)
                    .arg(ex->identifier_)
                    .arg(msgCodeToText(ex->request_->getCode()))
                    .arg(msgCodeToText(ex->received_->getCode()));
                ex->rc_ = BADRESP_RC;
            } else {
                LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                          RADIUS_EXCHANGE_RECEIVED_ACCOUNTING_RESPONSE)
                    .arg(ex->identifier_);
            }
        }
    } catch (const Exception& exc) {
        LOG_ERROR(radius_logger, RADIUS_EXCHANGE_RECEIVED_BAD_RESPONSE)
            .arg(ex->identifier_)
            .arg(exc.what());
        ex->rc_ = BADRESP_RC;
    }

    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
              RADIUS_EXCHANGE_RECEIVED_RESPONSE)
        .arg(ex->identifier_)
        .arg(exchangeRCtoText(ex->rc_));

    // If bad then retry, if not including reject it is done.
    if ((ex->rc_ != OK_RC) && ( ex->rc_ != REJECT_RC)) {
        ex->io_service_->post(std::bind(&Exchange::openNext, ex));
    } else {
        ex->logReplyMessages();
        ex->io_service_->post(std::bind(&Exchange::terminate, ex));
    }
}

void
Exchange::terminate() {
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
Exchange::setTimer() {
    cancelTimer();
    timer_.reset(new IntervalTimer(io_service_));
    timer_->setup(std::bind(&Exchange::timeoutHandler, shared_from_this()),
                  server_->getTimeout() * 1000, IntervalTimer::ONE_SHOT);
}

void
Exchange::cancelTimer() {
    if (timer_) {
        timer_->cancel();
        timer_.reset();
    }
}

void
Exchange::timeoutHandler(ExchangePtr ex) {
    MultiThreadingLock lock(*ex->mutex_);
    LOG_ERROR(radius_logger, RADIUS_EXCHANGE_TIMEOUT)
        .arg(ex->identifier_);
    ex->rc_ = TIMEOUT_RC;
    ex->cancelTimer();
    if (ex->socket_) {
        ex->socket_->cancel();
    }
}

} // end of namespace isc::radius
} // end of namespace isc
