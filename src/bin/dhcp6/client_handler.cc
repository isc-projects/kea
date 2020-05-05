// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp6/client_handler.h>
#include <exceptions/exceptions.h>

using namespace std;

namespace isc {
namespace dhcp {

mutex ClientHandler::mutex_;

ClientHandler::ClientContainer ClientHandler::clients_;

ClientHandler::ClientHandler() : locked_() {
}

ClientHandler::~ClientHandler() {
    if (locked_) {
        lock_guard<mutex> lock_(mutex_);
        unLock();
    }
    locked_.reset();
}

ClientHandler::Client::Client(Pkt6Ptr query)
    : query_(query), thread_(this_thread::get_id()) {
    if (!query) {
        isc_throw(InvalidParameter, "null query in ClientHandler");
    }
    if (!query->getClientId()) {
        isc_throw(InvalidParameter, "query has no client Id in ClientHandler");
    }
}

Pkt6Ptr
ClientHandler::lookup(const DuidPtr& duid) {
    if (!duid) {
        isc_throw(InvalidParameter, "duid is null in ClientHandler::lookup");
    }
    auto it = clients_.find(duid->getDuid());
    if (it == clients_.end()) {
        return (Pkt6Ptr());
    }
    return (it->query_);
}

void
ClientHandler::lock() {
    if (!locked_) {
        isc_throw(Unexpected, "nothing to lock in ClientHandler::lock");
    }
    Client client(locked_);
    clients_.insert(Client(locked_));
}

void
ClientHandler::unLock() {
    if (!locked_) {
        isc_throw(Unexpected, "nothing to unlock in ClientHandler::unLock");
    }
    const DuidPtr& duid = locked_->getClientId();
    if (!duid) {
        isc_throw(Unexpected, "no duid unlock in ClientHandler::unLock");
    }
    auto it = clients_.find(duid->getDuid());
    if (it == clients_.end()) {
        // Should not happen
        return;
    }
    clients_.erase(it);
}

bool
ClientHandler::tryLock(Pkt6Ptr query) {
    if (!query) {
        isc_throw(InvalidParameter, "null query in ClientHandler::tryLock");
    }
    if (locked_) {
        isc_throw(Unexpected, "already handling in ClientHandler::tryLock");
    }
    const DuidPtr& duid = query->getClientId();
    if (!duid) {
        // Can't do something useful: cross fingers.
        return (false);
    }
    if (duid->getDuid().empty()) {
        // A lot of code assumes this will never happen...
        isc_throw(Unexpected, "empty DUID in ClientHandler::tryLock");
    }
    lock_guard<mutex> lock_(mutex_);
    const Pkt6Ptr& duplicate = lookup(duid);
    if (duplicate) {
        // Should log.
        return (true);
    }
    locked_ = query;
    lock();
    return (false);
}

}  // namespace dhcp
}  // namespace isc
