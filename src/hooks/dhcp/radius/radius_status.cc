// Copyright (C) 2020-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <radius_access.h>
#include <radius_accounting.h>
#include <radius_status.h>
#include <radius_log.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace std;
namespace ph = std::placeholders;

namespace isc {
namespace radius {

RadiusAuthStatus::RadiusAuthStatus(const AttributesPtr& send_attrs,
                                   const CallbackStatus& handler)
  : RadiusStatus() {
    AttributesPtr attrs;
    if (send_attrs) {
        attrs.reset(new Attributes(*send_attrs));
    } else {
        attrs.reset(new Attributes());
    }
    MessagePtr request(new Message(PW_STATUS_SERVER, 0, vector<uint8_t>(),
                                   "to-be-set", attrs));
    unsigned maxretries = RadiusImpl::instance().retries_;
    Servers servers = RadiusImpl::instance().auth_->servers_;
    exchange_.reset(new Exchange(RadiusImpl::instance().getIOContext(),
                                 request, maxretries, servers,
                                 std::bind(&RadiusAuthStatus::invokeCallback,
                                           handler, ph::_1)));
}

void
RadiusAuthStatus::start() {
    AttributesPtr send_attrs;
    MessagePtr request = exchange_->getRequest();
    if (request) {
        send_attrs = request->getAttributes();
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_AUTHENTICATION_STATUS)
        .arg(send_attrs ? send_attrs->toText() : "no attributes");

    RadiusStatus::start();
}

void
RadiusAuthStatus::invokeCallback(const CallbackAcct& callback,
                                 const ExchangePtr exchange) {
    // Should not happen...
    if (!exchange) {
        return;
    }
    int result = exchange->getRC();
    if (result == OK_RC) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_AUTHENTICATION_STATUS_SUCCEED);
        RadiusImpl::instance().auth_->setIdleTimer();

        MessagePtr response = exchange->getResponse();
        AttributesPtr resp_attrs;
        uint8_t code = 0;
        if (response) {
            resp_attrs = response->getAttributes();
            code = response->getCode();
        }
        if (((code != 0) && (code != PW_ACCESS_ACCEPT)) ||
            (resp_attrs && (resp_attrs->count(PW_ERROR_CAUSE) > 0))) {
            LOG_ERROR(radius_logger, RADIUS_AUTHENTICATION_STATUS_ERROR)
                .arg(msgCodeToText(code))
                .arg(static_cast<unsigned>(code))
                .arg(resp_attrs ? resp_attrs->toText() : "no attributes");
        }
    } else {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_AUTHENTICATION_STATUS_FAILED)
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

RadiusAcctStatus::RadiusAcctStatus(const AttributesPtr& send_attrs,
                                   const CallbackStatus& handler)
  : RadiusStatus() {
    AttributesPtr attrs;
    if (send_attrs) {
        attrs.reset(new Attributes(*send_attrs));
    } else {
        attrs.reset(new Attributes());
    }
    MessagePtr request(new Message(PW_STATUS_SERVER, 0, vector<uint8_t>(),
                                   "to-be-set", attrs));
    unsigned maxretries = RadiusImpl::instance().retries_;
    Servers servers = RadiusImpl::instance().acct_->servers_;
    exchange_.reset(new Exchange(RadiusImpl::instance().getIOContext(),
                                 request, maxretries, servers,
                                 std::bind(&RadiusAcctStatus::invokeCallback,
                                           handler, ph::_1)));
}

void
RadiusAcctStatus::start() {
    AttributesPtr send_attrs;
    MessagePtr request = exchange_->getRequest();
    if (request) {
        send_attrs = request->getAttributes();
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCOUNTING_STATUS)
        .arg(send_attrs ? send_attrs->toText() : "no attributes");

    RadiusStatus::start();
}

void
RadiusAcctStatus::invokeCallback(const CallbackAcct& callback,
                                 const ExchangePtr exchange) {
    // Should not happen...
    if (!exchange) {
        return;
    }
    int result = exchange->getRC();
    if (result == OK_RC) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCOUNTING_STATUS_SUCCEED);
        RadiusImpl::instance().acct_->setIdleTimer();

        MessagePtr response = exchange->getResponse();
        AttributesPtr resp_attrs;
        uint8_t code = 0;
        if (response) {
            resp_attrs = response->getAttributes();
            code = response->getCode();
        }
        if (((code != 0) && (code != PW_ACCOUNTING_RESPONSE)) ||
            (resp_attrs && (resp_attrs->count(PW_ERROR_CAUSE) > 0))) {
            LOG_ERROR(radius_logger, RADIUS_ACCOUNTING_STATUS_ERROR)
                .arg(msgCodeToText(code))
                .arg(static_cast<unsigned>(code))
                .arg(resp_attrs ? resp_attrs->toText() : "no attributes");
        }
    } else {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCOUNTING_STATUS_FAILED)
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
