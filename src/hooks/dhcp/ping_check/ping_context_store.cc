// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ping_context_store.h>
#include <util/multi_threading_mgr.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;
using namespace std::chrono;

namespace isc {
namespace ping_check {

PingContextPtr
PingContextStore::addContext(Lease4Ptr& lease, Pkt4Ptr& query,
                             uint32_t min_echos, uint32_t reply_timeout,
                             ParkingLotHandlePtr& parking_lot) {

    MultiThreadingLock lock(*mutex_);
    PingContextPtr context;
    try {
        context.reset(new PingContext(lease, query, min_echos, reply_timeout, parking_lot));
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "PingContextStore::addContext failed: " << ex.what());
    }

    context->beginWaitingToSend();
    auto ret = pings_.insert(context);
    if (ret.second == false) {
        isc_throw(DuplicateContext, "PingContextStore::addContex: context already exists for: "
                  << lease->addr_);
    }

    return (context);
}

void
PingContextStore::updateContext(const PingContextPtr& context) {
    MultiThreadingLock lock(*mutex_);
    auto& index = pings_.get<AddressIndexTag>();
    auto context_iter = index.find(context->getTarget());
    if (context_iter == index.end()) {
        isc_throw(InvalidOperation, "PingContextStore::updateContext failed for address: "
                  << context->getTarget() << ", not in store");
    }

    // Use replace() to re-index contexts.
    index.replace(context_iter, PingContextPtr(new PingContext(*context)));
}

void
PingContextStore::deleteContext(const PingContextPtr& context) {
    MultiThreadingLock lock(*mutex_);
    auto& index = pings_.get<AddressIndexTag>();
    auto context_iter = index.find(context->getTarget());
    if (context_iter == index.end()) {
        // Not there, just return.
        return;
    }

    // Remove the context from the store.
    pings_.erase(context_iter);
}

PingContextPtr
PingContextStore::getContextByAddress(const IOAddress& address) {
    MultiThreadingLock lock(*mutex_);
    auto const& index = pings_.get<AddressIndexTag>();
    auto context_iter = index.find(address);
    return (context_iter == index.end() ? PingContextPtr()
            : PingContextPtr(new PingContext(**context_iter)));
}

PingContextPtr
PingContextStore::getContextByQuery(Pkt4Ptr& query) {
    MultiThreadingLock lock(*mutex_);
    auto const& index = pings_.get<QueryIndexTag>();
    auto context_iter = index.find(query);
    return (context_iter == index.end() ? PingContextPtr()
            : PingContextPtr(new PingContext(**context_iter)));
}

PingContextPtr
PingContextStore::getNextToSend() {
    MultiThreadingLock lock(*mutex_);
    auto const& index = pings_.get<NextToSendIndexTag>();
    auto context_iter = index.lower_bound(boost::make_tuple(true, PingContext::MIN_TIME()));
    return (context_iter == index.end() ? PingContextPtr()
            : PingContextPtr(new PingContext(**context_iter)));
}

PingContextPtr
PingContextStore::getExpiresNext() {
    MultiThreadingLock lock(*mutex_);
    auto const& index = pings_.get<ExpirationIndexTag>();
    auto context_iter = index.lower_bound(boost::make_tuple(true, PingContext::now() + milliseconds(1)));
    return (context_iter == index.end() ? PingContextPtr()
            : PingContextPtr(new PingContext(**context_iter)));
}

PingContextCollectionPtr
PingContextStore::getExpiredSince(const TimeStamp& since) {
    MultiThreadingLock lock(*mutex_);
    auto const& index = pings_.get<ExpirationIndexTag>();
    auto lower_limit = index.lower_bound(boost::make_tuple(true, PingContext::MIN_TIME()));
    auto upper_limit = index.upper_bound(boost::make_tuple(true, since));

    PingContextCollectionPtr collection(new PingContextCollection());
    for (auto context_iter = lower_limit; context_iter != upper_limit; ++context_iter) {
        PingContextPtr context(new PingContext(**context_iter));
        collection->push_back(context);
    }

    return (collection);
}

PingContextCollectionPtr
PingContextStore::getAll() {
    MultiThreadingLock lock(*mutex_);
    auto const& index = pings_.get<AddressIndexTag>();
    PingContextCollectionPtr collection(new PingContextCollection());
    for (auto const& context_iter : index) {
        collection->push_back(PingContextPtr(new PingContext(*context_iter)));
    }

    return (collection);
}

void PingContextStore::clear() {
    MultiThreadingLock lock(*mutex_);
    pings_.clear();
}

} // end of namespace ping_check
} // end of namespace isc
