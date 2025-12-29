// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <radius_request.h>
#include <radius_access.h>
#include <radius_accounting.h>
#include <radius_log.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace std;
namespace ph = std::placeholders;

namespace isc {
namespace radius {

uint32_t getNASPort(uint32_t subnet_id) {
    const map<uint32_t, uint32_t>& remap = RadiusImpl::instance().remap_;
    auto const by_id = remap.find(subnet_id);
    if (by_id != remap.end()) {
        return (by_id->second);
    }
    auto const by_id0 = remap.find(SUBNET_ID_DEFAULT);
    if (by_id0 != remap.end()) {
        return (by_id0->second);
    }
    return (subnet_id);
}

RadiusRequest::RadiusRequest(const MsgCode code,
                             uint32_t subnet_id,
                             const AttributesPtr& send_attrs,
                             bool sync,
                             const Exchange::Handler& handler) {
    AttributesPtr attrs;
    if (send_attrs) {
        attrs.reset(new Attributes(*send_attrs));
    } else {
        attrs.reset(new Attributes());
    }
    nas_port_ = getNASPort(subnet_id);
    if (!attrs->get(PW_NAS_PORT)) {
        attrs->add(Attribute::fromInt(PW_NAS_PORT, nas_port_));
    }
    MessagePtr request(new Message(code, 0, vector<uint8_t>(),
                                   "to-be-set", attrs));
    unsigned maxretries = RadiusImpl::instance().retries_;
    Servers servers;
    if (code == PW_ACCESS_REQUEST) {
        servers = RadiusImpl::instance().auth_->servers_;
    } else {
        servers = RadiusImpl::instance().acct_->servers_;
    }
    if (sync) {
        exchange_.reset(new Exchange(request, maxretries, servers));
    } else {
        exchange_.reset(new Exchange(RadiusImpl::instance().getIOContext(),
                                     request, maxretries, servers,
                                     handler));
    }
}

void
RadiusSyncAuth::start() {
    AttributesPtr send_attrs;
    MessagePtr request = exchange_->getRequest();
    if (request) {
        send_attrs = request->getAttributes();
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_AUTHENTICATION_SYNC)
        .arg(nas_port_)
        .arg(send_attrs ? send_attrs->toText() : "no attributes");

    RadiusRequest::start();

    int result = getRC();
    AttributesPtr recv_attrs = getRespAttrs();
    if (result == OK_RC) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_AUTHENTICATION_SYNC_ACCEPTED)
            .arg(recv_attrs ? recv_attrs->toText() : "no attributes");
        RadiusImpl::instance().auth_->setIdleTimer();
    } else if (result == REJECT_RC) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_AUTHENTICATION_SYNC_REJECTED)
            .arg(recv_attrs ? recv_attrs->toText() : "no attributes");
        RadiusImpl::instance().auth_->setIdleTimer();
    } else {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_AUTHENTICATION_SYNC_FAILED)
            .arg(result)
            .arg(exchangeRCtoText(result));
    }

    if (callback_) {
        try {
            callback_(result, recv_attrs);
        } catch (...) {
        }
    }
    exchange_->shutdown();
}

RadiusAsyncAuth::RadiusAsyncAuth(uint32_t subnet_id,
                                 const AttributesPtr& send_attrs,
                                 const CallbackAuth& callback)
    : RadiusAuth(subnet_id, send_attrs, false,
                 std::bind(&RadiusAsyncAuth::invokeCallback,
                           callback, ph::_1)) {
}

void
RadiusAsyncAuth::start() {
    AttributesPtr send_attrs;
    MessagePtr request = exchange_->getRequest();
    if (request) {
        send_attrs = request->getAttributes();
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_AUTHENTICATION_ASYNC)
        .arg(nas_port_)
        .arg(send_attrs ? send_attrs->toText() : "no attributes");

    RadiusRequest::start();
}

void
RadiusAsyncAuth::invokeCallback(const CallbackAuth& callback,
                                const ExchangePtr exchange) {
    // Should no happen...
    if (!exchange) {
        return;
    }
    int result = exchange->getRC();
    AttributesPtr recv_attrs;
    MessagePtr response = exchange->getResponse();
    if (response) {
        recv_attrs = response->getAttributes();
    }
    if (result == OK_RC) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_AUTHENTICATION_ASYNC_ACCEPTED)
            .arg(recv_attrs ? recv_attrs->toText() : "no attributes");
        RadiusImpl::instance().auth_->setIdleTimer();
    } else if (result == REJECT_RC) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_AUTHENTICATION_ASYNC_REJECTED)
            .arg(recv_attrs ? recv_attrs->toText() : "no attributes");
        RadiusImpl::instance().auth_->setIdleTimer();
    } else {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_AUTHENTICATION_ASYNC_FAILED)
            .arg(result)
            .arg(exchangeRCtoText(result));
    }

    if (callback) {
        try {
            callback(result, recv_attrs);
        } catch (...) {
        }
    }
    exchange->shutdown();
    RadiusImpl::instance().unregisterExchange(exchange);
}

void
RadiusSyncAcct::start() {
    AttributesPtr send_attrs;
    MessagePtr request = exchange_->getRequest();
    if (request) {
        send_attrs = request->getAttributes();
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCOUNTING_SYNC)
        .arg(nas_port_)
        .arg(send_attrs ? send_attrs->toText() : "no attributes");

    RadiusRequest::start();

    int result = getRC();
    if (result == OK_RC) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCOUNTING_SYNC_SUCCEED);
        RadiusImpl::instance().acct_->setIdleTimer();
    } else {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCOUNTING_SYNC_FAILED)
            .arg(result)
            .arg(exchangeRCtoText(result));
    }

    if (callback_) {
        try {
            callback_(result);
        } catch (...) {
        }
    }
    exchange_->shutdown();
}

RadiusAsyncAcct::RadiusAsyncAcct(uint32_t subnet_id,
                                 const AttributesPtr& send_attrs,
                                 const CallbackAcct& callback)
    : RadiusAcct(subnet_id, send_attrs, false,
                 std::bind(&RadiusAsyncAcct::invokeCallback,
                           callback, ph::_1)) {
}

void
RadiusAsyncAcct::start() {
    AttributesPtr send_attrs;
    MessagePtr request = exchange_->getRequest();
    if (request) {
        send_attrs = request->getAttributes();
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCOUNTING_ASYNC)
        .arg(nas_port_)
        .arg(send_attrs ? send_attrs->toText() : "no attributes");

    RadiusRequest::start();
}

void
RadiusAsyncAcct::invokeCallback(const CallbackAcct& callback,
                                const ExchangePtr exchange) {
    // Should not happen...
    if (!exchange) {
        return;
    }
    int result = exchange->getRC();
    if (result == OK_RC) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCOUNTING_ASYNC_SUCCEED);
        RadiusImpl::instance().acct_->setIdleTimer();
    } else {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCOUNTING_ASYNC_FAILED)
            .arg(result)
            .arg(exchangeRCtoText(result));
    }

    if (callback) {
        try {
            callback(result);
        } catch (...) {
        }
    }
    exchange->shutdown();
    RadiusImpl::instance().unregisterExchange(exchange);
}

} // end of namespace radius
} // end of namespace isc
