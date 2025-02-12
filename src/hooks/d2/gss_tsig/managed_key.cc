// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink/crypto_rng.h>
#include <gss_tsig_context.h>
#include <gss_tsig_log.h>
#include <managed_key.h>
#include <util/chrono_time_utils.h>
#include <cstring>
#include <iostream>

using namespace isc;
using namespace isc::data;
using namespace isc::dns;
using namespace isc::util;
using namespace std;

namespace isc {
namespace gss_tsig {

string
ManagedKey::statusToText(Status status) {
    switch (status) {
    case NOT_READY:
        return ("not yet ready");
    case USABLE:
        return ("usable");
    case EXPIRED:
        return ("expired");
    default:
        return ("in error");
    }
}

string
ManagedKey::genName(const string& suffix) {
    uint32_t n;
    vector<uint8_t> r = isc::cryptolink::random(sizeof(uint32_t));
    memmove(&n, &r[0], sizeof(uint32_t));
    ostringstream s;
    s << n << "." << suffix;
    return (s.str());
}

ManagedKey::ManagedKey(const string& name)
    : GssTsigKey(name), parent_id_(""), status_(NOT_READY),
      tkey_status_(TKeyExchange::OTHER), tkey_ex_(), mutex_(new mutex()) {
}

void
ManagedKey::operator()(TKeyExchange::Status tkey_status) {
    bool success = true;
    {
        lock_guard<mutex> lock(*mutex_);
        setTKeyStatus(tkey_status);
        if (tkey_status == TKeyExchange::SUCCESS) {
            setStatus(USABLE);
        } else {
            setStatus(IN_ERROR);
            success = false;
        }
    }
    if (success) {
        LOG_DEBUG(gss_tsig_logger, log::DBGLVL_TRACE_BASIC,
                  GSS_TSIG_NEW_KEY_SETUP_SUCCEED)
            .arg(getKeyName().toText(true));
    } else {
        LOG_WARN(gss_tsig_logger, GSS_TSIG_NEW_KEY_SETUP_FAILED)
            .arg(getKeyName().toText(true))
            .arg(TKeyExchange::statusToText(tkey_status));
    }
    if (getTKeyExchange() && getTKeyExchange()->getIOService()) {
        getTKeyExchange()->getIOService()->post([this]() { getTKeyExchange().reset(); });
    }
}

ElementPtr
ManagedKey::toElement() const {
    ElementPtr map = Element::createMap();

    // Name.
    map->set("name", Element::create(getKeyNameStr()));

    // Parent.
    map->set("server-id", Element::create(getParentID()));

    // Status.
    map->set("status", Element::create(ManagedKey::statusToText(status_)));

    // Per status extra information.
    switch (status_) {
    case USABLE:
    case EXPIRED:
        // Security context lifetime.
        try {
            if (sec_ctx_.get()) {
                uint32_t lifetime = sec_ctx_->getLifetime();
                map->set("security-context-lifetime",
                         Element::create(static_cast<long long>(lifetime)));
            }
        } catch (...) {
            // Just ignore errors.
        }
        break;
    case IN_ERROR:
        // TKEY status.
        map->set("tkey-status",
                 Element::create(TKeyExchange::statusToText(tkey_status_)));
        break;
    default:
        // TKEY exchange.
        map->set("tkey-exchange", Element::create(!!tkey_ex_));
        break;
    }

    // Inception date.
    map->set("inception-date", Element::create(clockToText(inception_)));

    // Expire date.
    map->set("expire-date", Element::create(clockToText(expire_)));

    return (map);
}

TSIGContextPtr
ManagedKey::createContext() {
    return (GssTsigContextPtr(new GssTsigContext(*this)));
}

} // end of namespace isc::gss_tsig
} // end of namespace isc
