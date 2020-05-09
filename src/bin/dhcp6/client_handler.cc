// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp6/client_handler.h>
#include <dhcp6/dhcp6_log.h>
#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>

using namespace std;

namespace isc {
namespace dhcp {

mutex ClientHandler::mutex_;

ClientHandler::ClientContainer ClientHandler::clients_;

ClientHandler::ClientHandler() : client_(), locked_() {
}

ClientHandler::~ClientHandler() {
    if (locked_) {
        lock_guard<mutex> lock_(mutex_);
        unLock();
    }
    locked_.reset();
    client_.reset();
}

ClientHandler::Client::Client(Pkt6Ptr query, DuidPtr client_id)
    : query_(query), thread_(this_thread::get_id()) {
    if (!query) {
        isc_throw(InvalidParameter, "null query in ClientHandler");
    }
    if (!client_id) {
        isc_throw(InvalidParameter, "null client-id in ClientHandler");
    }
    duid_ = client_id->getDuid();
}

ClientHandler::ClientPtr
ClientHandler::lookup(const DuidPtr& duid) {
    if (!duid) {
        isc_throw(InvalidParameter, "duid is null in ClientHandler::lookup");
    }
    auto it = clients_.find(duid->getDuid());
    if (it == clients_.end()) {
        return (0);
    }
    return (*it);
}

void
ClientHandler::lock() {
    if (!locked_) {
        isc_throw(Unexpected, "nothing to lock in ClientHandler::lock");
    }
    // Assume insert will never fail so not checking its result.
    clients_.insert(client_);
}

void
ClientHandler::unLock() {
    if (!locked_) {
        isc_throw(Unexpected, "nothing to unlock in ClientHandler::unLock");
    }
    // Assume erase will never fail so not checking its result.
    clients_.erase(locked_->getDuid());
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
    ClientPtr holder;
    {
        // Try to acquire the lock and return the holder when it failed.
        lock_guard<mutex> lock_(mutex_);
        holder = lookup(duid);
        if (!holder) {
            locked_ = duid;
            client_.reset(new Client(query, duid));
            lock();
            return (false);
        }
    }
    // This query is a duplicate: currently it is simply dropped.
    // Logging a warning as it is supposed to be a rare event
    // with well behaving clients...
    LOG_WARN(bad_packet6_logger, DHCP6_PACKET_DROP_DUPLICATE)
        .arg(query->toText())
        .arg(this_thread::get_id())
        .arg(holder->query_->toText())
        .arg(holder->thread_);
    stats::StatsMgr::instance().addValue("pkt6-receive-drop",
                                         static_cast<int64_t>(1));
    return (true);
}

}  // namespace dhcp
}  // namespace isc
