// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/resource_handler.h>
#include <exceptions/exceptions.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

mutex ResourceHandler::mutex_;

ResourceHandler::ResourceContainer ResourceHandler::resources_;

ResourceHandler::ResourceHandler() : owned_() {
}

ResourceHandler::~ResourceHandler() {
    lock_guard<mutex> lock_(mutex_);
    for (auto res : owned_) {
        unLockInternal(res->type_, res->addr_);
    }
    owned_.clear();
}

ResourceHandler::ResourcePtr
ResourceHandler::lookup(Lease::Type type, const asiolink::IOAddress& addr) {
    auto key = boost::make_tuple(type, addr.toBytes());
    auto it = resources_.find(key);
    if (it == resources_.end()) {
        return (ResourcePtr());
    }
    return (*it);
}

void
ResourceHandler::lock(Lease::Type type, const asiolink::IOAddress& addr) {
    ResourcePtr res(new Resource(type, addr));
    // Assume insert will never fail so not checking its result.
    resources_.insert(res);
    owned_.insert(res);
}

void
ResourceHandler::unLockInternal(Lease::Type type,
                                const asiolink::IOAddress& addr) {
    auto key = boost::make_tuple(type, addr.toBytes());
    auto it = resources_.find(key);
    if (it == resources_.end()) {
        return;
    }
    resources_.erase(it);
}

bool
ResourceHandler::tryLock(Lease::Type type, const asiolink::IOAddress& addr) {
    ResourcePtr holder;
    // Try to acquire the lock and return the holder when it failed.
    lock_guard<mutex> lock_(mutex_);
    holder = lookup(type, addr);
    if (holder) {
        return (false);
    }
    lock(type, addr);
    return (true);
}

bool
ResourceHandler::isLocked(Lease::Type type, const asiolink::IOAddress& addr) {
    auto key = boost::make_tuple(type, addr.toBytes());
    lock_guard<mutex> lock_(mutex_);
    auto it = owned_.find(key);
    return (it != owned_.end());
}

void
ResourceHandler::unLock(Lease::Type type, const asiolink::IOAddress& addr) {
    auto key = boost::make_tuple(type, addr.toBytes());
    lock_guard<mutex> lock_(mutex_);
    auto it = owned_.find(key);
    if (it == owned_.end()) {
        isc_throw(NotFound, "does not own " << Lease::typeToText(type)
                  << " " << addr.toText());
    }
    unLockInternal(type, addr);
    owned_.erase(it);
}

}  // namespace dhcp
}  // namespace isc
