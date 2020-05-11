// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp4/client_handler.h>
#include <dhcp4/dhcp4_log.h>
#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>
#include <util/multi_threading_mgr.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace dhcp {

mutex ClientHandler::mutex_;

ClientHandler::ClientByIdContainer ClientHandler::clients_client_id_;

ClientHandler::ClientByHWAddrContainer ClientHandler::clients_hwaddr_;

ClientHandler::ClientHandler()
    : client_(), locked_client_id_(), locked_hwaddr_() {
}

ClientHandler::~ClientHandler() {
    bool unlocked = false;
    lock_guard<mutex> lock_(mutex_);
    if (locked_client_id_) {
        unlocked = true;
        unLockById();
    }
    locked_client_id_.reset();
    if (locked_hwaddr_) {
        unlocked = true;
        unLockByHWAddr();
    }
    locked_hwaddr_.reset();
    if (!client_) {
        return;
    }
    if (!unlocked || !client_->cont_) {
        client_.reset();
        return;
    }
    // Try to process next query. As the caller holds the mutex of
    // the handler class the continuation will be resumed after.
    MultiThreadingMgr& mt_mgr = MultiThreadingMgr::instance();
    if (mt_mgr.getMode()) {
        if (!mt_mgr.getThreadPool().addFront(client_->cont_)) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_PACKET_QUEUE_FULL);
        }
    }
    client_->cont_.reset();
    client_.reset();
}

ClientHandler::Client::Client(Pkt4Ptr query, DuidPtr client_id,
                              HWAddrPtr hwaddr)
    : query_(query), thread_(this_thread::get_id()) {
    if (!query) {
        isc_throw(InvalidParameter, "null query in ClientHandler (id)");
    }
    if (!client_id && !hwaddr) {
        isc_throw(InvalidParameter, "null client-id and hwaddr in ClientHandler");
    }
    if (client_id) {
        duid_ = client_id->getDuid();
    }
    if (hwaddr) {
        htype_ = hwaddr->htype_;
        hwaddr_ = hwaddr->hwaddr_;
    }
}

ClientHandler::ClientPtr
ClientHandler::lookup(const DuidPtr& duid) {
    if (!duid) {
        isc_throw(InvalidParameter, "duid is null in ClientHandler::lookup");
    }
    auto it = clients_client_id_.find(duid->getDuid());
    if (it == clients_client_id_.end()) {
        return (0);
    }
    return (*it);
}

ClientHandler::ClientPtr
ClientHandler::lookup(const HWAddrPtr& hwaddr) {
    if (!hwaddr) {
        isc_throw(InvalidParameter, "hwaddr is null in ClientHandler::lookup");
    }
    if (hwaddr->hwaddr_.empty()) {
        isc_throw(InvalidParameter, "hwaddr is empty in ClientHandler::lookup");
    }
    auto key = boost::make_tuple(hwaddr->htype_, hwaddr->hwaddr_);
    auto it = clients_hwaddr_.find(key);
    if (it == clients_hwaddr_.end()) {
        return (0);
    }
    return (*it);
}

void
ClientHandler::lockById() {
    if (!locked_client_id_) {
        isc_throw(Unexpected, "nothing to lock in ClientHandler::lock (id)");
    }
    // Assume insert will never fail so not checking its result.
    clients_client_id_.insert(client_);
}

void
ClientHandler::lockByHWAddr() {
    if (!locked_hwaddr_) {
        isc_throw(Unexpected, "nothing to lock in ClientHandler::lock (hw)");
    }
    // Assume insert will never fail so not checking its result.
    clients_hwaddr_.insert(client_);
}

void
ClientHandler::unLockById() {
    if (!locked_client_id_) {
        isc_throw(Unexpected, "nothing to unlock in ClientHandler::unLock (id)");
    }
    // Assume erase will never fail so not checking its result.
    clients_client_id_.erase(locked_client_id_->getDuid());
}

void
ClientHandler::unLockByHWAddr() {
    if (!locked_hwaddr_) {
        isc_throw(Unexpected, "nothing to unlock in ClientHandler::unLock (hw)");
    }
    auto key = boost::make_tuple(locked_hwaddr_->htype_, locked_hwaddr_->hwaddr_);
    // Assume erase will never fail so not checking its result.
    auto it = clients_hwaddr_.find(key);
    if (it == clients_hwaddr_.end()) {
        // Should not happen.
        return;
    }
    clients_hwaddr_.erase(it);
}

bool
ClientHandler::tryLock(Pkt4Ptr query, ContinuationPtr cont) {
    // Sanity checks.
    if (!query) {
        isc_throw(InvalidParameter, "null query in ClientHandler::tryLock");
    }
    if (locked_client_id_) {
        isc_throw(Unexpected,
                  "already handling client-id in ClientHandler::tryLock");
    }
    if (locked_hwaddr_) {
        isc_throw(Unexpected,
                  "already handling hwaddr in ClientHandler::tryLock");
    }

    // Get identifiers.
    OptionPtr opt_client_id = query->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    DuidPtr duid;
    if (opt_client_id) {
        duid.reset(new ClientId(opt_client_id->getData()));
    }
    HWAddrPtr hwaddr = query->getHWAddr();
    if (hwaddr && hwaddr->hwaddr_.empty()) {
        hwaddr.reset();
    }
    if (!duid && !hwaddr) {
        // Can't do something useful: cross fingers.
        return (true);
    }

    ClientPtr holder_id;
    ClientPtr holder_hw;
    client_.reset(new Client(query, duid, hwaddr));

    // Try first duid.
    if (duid) {
        // Try to acquire the by-client-id lock and return the holder
        // when it failed.
        lock_guard<mutex> lock_(mutex_);
        holder_id = lookup(duid);
        if (!holder_id) {
            locked_client_id_ = duid;
            lockById();
        }
    }
    if (!holder_id) {
        if (!hwaddr) {
            return (true);
        }
        // Try to acquire the by-hw-addr lock and return the holder
        // when it failed.
        lock_guard<mutex> lock_(mutex_);
        holder_hw = lookup(hwaddr);
        if (!holder_hw) {
            locked_hwaddr_ = hwaddr;
            lockByHWAddr();
            return (true);
        }
    }

    if (holder_id) {
        // This query is a by-id duplicate so put the continuation.
        if (cont) {
            Pkt4Ptr next_query = holder_id->next_query_;
            holder_id->next_query_ = query;
            holder_id->cont_ = cont;
            if (next_query) {
                // Logging a warning as it is supposed to be a rare event
                // with well behaving clients...
                LOG_WARN(bad_packet4_logger, DHCP4_PACKET_DROP_0011)
                    .arg(next_query->toText())
                    .arg(this_thread::get_id())
                    .arg(query->toText())
                    .arg(this_thread::get_id());
                stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                     static_cast<int64_t>(1));
            }
            return (false);
        }
        // Logging a warning as it is supposed to be a rare event
        // with well behaving clients...
        LOG_WARN(bad_packet4_logger, DHCP4_PACKET_DROP_0011)
            .arg(query->toText())
            .arg(this_thread::get_id())
            .arg(holder_id->query_->toText())
            .arg(holder_id->thread_);
        stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                             static_cast<int64_t>(1));
    } else {
        // This query is a by-hw duplicate so put the continuation.
        if (cont) {
            Pkt4Ptr next_query = holder_hw->next_query_;
            holder_hw->next_query_ = query;
            holder_hw->cont_ = cont;
            if (next_query) {
                // Logging a warning as it is supposed to be a rare event
                // with well behaving clients...
                LOG_WARN(bad_packet4_logger, DHCP4_PACKET_DROP_0012)
                    .arg(next_query->toText())
                    .arg(this_thread::get_id())
                    .arg(query->toText())
                    .arg(this_thread::get_id());
                stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                     static_cast<int64_t>(1));
            }
            return (false);
        }
        // Logging a warning as it is supposed to be a rare event
        // with well behaving clients...
        LOG_WARN(bad_packet4_logger, DHCP4_PACKET_DROP_0012)
            .arg(query->toText())
            .arg(this_thread::get_id())
            .arg(holder_hw->query_->toText())
            .arg(holder_hw->thread_);
        stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                             static_cast<int64_t>(1));
    }
    return (false);
}

}  // namespace dhcp
}  // namespace isc
