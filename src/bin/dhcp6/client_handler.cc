// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp6/client_handler.h>
#include <dhcp6/dhcp6_log.h>
#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>
#include <util/multi_threading_mgr.h>

using namespace std;
using namespace isc::util;
using namespace isc::log;

namespace isc {
namespace dhcp {

ClientHandler::Client::Client(Pkt6Ptr query, DuidPtr client_id)
    : query_(query), thread_(this_thread::get_id()) {
    // Sanity checks.
    if (!query) {
        isc_throw(InvalidParameter, "null query in ClientHandler");
    }
    if (!client_id) {
        isc_throw(InvalidParameter, "null client-id in ClientHandler");
    }

    duid_ = client_id->getDuid();
}

mutex ClientHandler::mutex_;

ClientHandler::ClientContainer ClientHandler::clients_;

ClientHandler::ClientPtr
ClientHandler::lookup(const DuidPtr& duid) {
    // Sanity check.
    if (!duid) {
        isc_throw(InvalidParameter, "null duid in ClientHandler::lookup");
    }

    auto it = clients_.find(duid->getDuid());
    if (it == clients_.end()) {
        return (ClientPtr());
    }
    return (*it);
}

void
ClientHandler::add(const ClientPtr& client) {
    // Sanity check.
    if (!client) {
        isc_throw(InvalidParameter, "null client in ClientHandler::add");
    }

    // Assume insert will never fail so not checking its result.
    clients_.insert(client);
}

void
ClientHandler::del(const DuidPtr& duid) {
    // Sanity check.
    if (!duid) {
        isc_throw(InvalidParameter, "null duid in ClientHandler::del");
    }

    // Assume erase will never fail so not checking its result.
    clients_.erase(duid->getDuid());
}

ClientHandler::ClientHandler() : client_(), locked_() {
}

ClientHandler::~ClientHandler() {
    if (locked_) {
        lock_guard<mutex> lk(mutex_);
        unLock();
    }
}

bool
ClientHandler::tryLock(Pkt6Ptr query, ContinuationPtr cont) {
    // Sanity checks.
    if (!query) {
        isc_throw(InvalidParameter, "null query in ClientHandler::tryLock");
    }
    if (locked_) {
        isc_throw(Unexpected, "already handling in ClientHandler::tryLock");
    }

    const DuidPtr& duid = query->getClientId();
    if (!duid) {
        // Can't do something useful: cross fingers.
        return (true);
    }
    if (duid->getDuid().empty()) {
        // A lot of code assumes this will never happen...
        isc_throw(Unexpected, "empty DUID in ClientHandler::tryLock");
    }

    ClientPtr holder;
    Pkt6Ptr next_query;
    client_.reset(new Client(query, duid));

    {
        // Try to acquire the lock and return the holder when it failed.
        lock_guard<mutex> lk(mutex_);
        holder = lookup(duid);
        if (!holder) {
            locked_ = duid;
            lock();
            return (true);
        }
        // This query can be a duplicate so put the continuation.
        if (cont) {
            next_query = holder->next_query_;
            holder->next_query_ = query;
            holder->cont_ = cont;
        }
    }

    if (cont) {
        if (next_query) {
            // Logging a warning as it is supposed to be a rare event
            // with well behaving clients...
            LOG_DEBUG(bad_packet6_logger, DBGLVL_PKT_HANDLING, DHCP6_PACKET_DROP_DUPLICATE)
                .arg(next_query->toText())
                .arg(this_thread::get_id())
                .arg(holder->query_->toText())
                .arg(holder->thread_);
            stats::StatsMgr::instance().addValue("pkt6-receive-drop",
                                                 static_cast<int64_t>(1));
        }
    } else {
        // Logging a warning as it is supposed to be a rare event
        // with well behaving clients...
        LOG_DEBUG(bad_packet6_logger, DBGLVL_PKT_HANDLING, DHCP6_PACKET_DROP_DUPLICATE)
            .arg(query->toText())
            .arg(this_thread::get_id())
            .arg(holder->query_->toText())
            .arg(holder->thread_);
        stats::StatsMgr::instance().addValue("pkt6-receive-drop",
                                             static_cast<int64_t>(1));
    }
    return (false);
}

void
ClientHandler::lock() {
    // Sanity check.
    if (!locked_) {
        isc_throw(Unexpected, "nothing to lock in ClientHandler::lock");
    }

    add(client_);
}

void
ClientHandler::unLock() {
    // Sanity check.
    if (!locked_) {
        isc_throw(Unexpected, "nothing to unlock in ClientHandler::unLock");
    }

    del(locked_);
    locked_.reset();

    if (!client_ || !client_->cont_) {
        return;
    }

    // Try to process next query. As the caller holds the mutex of
    // the handler class the continuation will be resumed after.
    MultiThreadingMgr& mt_mgr = MultiThreadingMgr::instance();
    if (mt_mgr.getMode()) {
        if (!mt_mgr.getThreadPool().addFront(client_->cont_)) {
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_PACKET_QUEUE_FULL);
        }
    }
}

}  // namespace dhcp
}  // namespace isc
