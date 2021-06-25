// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
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
using namespace isc::log;

namespace isc {
namespace dhcp {

ClientHandler::Client::Client(Pkt4Ptr query, DuidPtr client_id,
                              HWAddrPtr hwaddr)
    : query_(query), htype_(HTYPE_ETHER), thread_(this_thread::get_id()) {
    // Sanity checks.
    if (!query) {
        isc_throw(InvalidParameter, "null query in ClientHandler");
    }
    if (!client_id && (!hwaddr || hwaddr->hwaddr_.empty())) {
        isc_throw(InvalidParameter,
                  "null client-id and hwaddr in ClientHandler");
    }

    if (client_id) {
        duid_ = client_id->getDuid();
    }
    if (hwaddr && !hwaddr->hwaddr_.empty()) {
        htype_ = hwaddr->htype_;
        hwaddr_ = hwaddr->hwaddr_;
    }
}

mutex ClientHandler::mutex_;

ClientHandler::ClientByIdContainer ClientHandler::clients_client_id_;

ClientHandler::ClientByHWAddrContainer ClientHandler::clients_hwaddr_;

ClientHandler::ClientPtr
ClientHandler::lookup(const DuidPtr& duid) {
    // Sanity check.
    if (!duid) {
        isc_throw(InvalidParameter, "null duid in ClientHandler::lookup");
    }

    auto it = clients_client_id_.find(duid->getDuid());
    if (it == clients_client_id_.end()) {
        return (ClientPtr());
    }
    return (*it);
}

ClientHandler::ClientPtr
ClientHandler::lookup(const HWAddrPtr& hwaddr) {
    // Sanity checks.
    if (!hwaddr) {
        isc_throw(InvalidParameter, "null hwaddr in ClientHandler::lookup");
    }
    if (hwaddr->hwaddr_.empty()) {
        isc_throw(InvalidParameter, "empty hwaddr in ClientHandler::lookup");
    }

    auto key = boost::make_tuple(hwaddr->htype_, hwaddr->hwaddr_);
    auto it = clients_hwaddr_.find(key);
    if (it == clients_hwaddr_.end()) {
        return (ClientPtr());
    }
    return (*it);
}

void
ClientHandler::addById(const ClientPtr& client) {
    // Sanity check.
    if (!client) {
        isc_throw(InvalidParameter, "null client in ClientHandler::addById");
    }

    // Assume insert will never fail so not checking its result.
    clients_client_id_.insert(client);
}

void
ClientHandler::addByHWAddr(const ClientPtr& client) {
    // Sanity check.
    if (!client) {
        isc_throw(InvalidParameter,
                  "null client in ClientHandler::addByHWAddr");
    }

    // Assume insert will never fail so not checking its result.
    clients_hwaddr_.insert(client);
}

void
ClientHandler::del(const DuidPtr& duid) {
    // Sanity check.
    if (!duid) {
        isc_throw(InvalidParameter, "null duid in ClientHandler::del");
    }

    // Assume erase will never fail so not checking its result.
    clients_client_id_.erase(duid->getDuid());
}

void
ClientHandler::del(const HWAddrPtr& hwaddr) {
    // Sanity checks.
    if (!hwaddr) {
        isc_throw(InvalidParameter, "null hwaddr in ClientHandler::del");
    }
    if (hwaddr->hwaddr_.empty()) {
        isc_throw(InvalidParameter, "empty hwaddr in ClientHandler::del");
    }

    auto key = boost::make_tuple(hwaddr->htype_, hwaddr->hwaddr_);
    // Assume erase will never fail so not checking its result.
    auto it = clients_hwaddr_.find(key);
    if (it == clients_hwaddr_.end()) {
        // Should not happen.
        return;
    }
    clients_hwaddr_.erase(it);
}

ClientHandler::ClientHandler()
    : client_(), locked_client_id_(), locked_hwaddr_() {
}

ClientHandler::~ClientHandler() {
    bool unlocked = false;
    lock_guard<mutex> lk(mutex_);
    if (locked_client_id_) {
        unlocked = true;
        unLockById();
    }
    if (locked_hwaddr_) {
        unlocked = true;
        unLockByHWAddr();
    }
    if (!unlocked || !client_ || !client_->cont_) {
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
    Pkt4Ptr next_query_id;
    Pkt4Ptr next_query_hw;
    client_.reset(new Client(query, duid, hwaddr));

    {
        lock_guard<mutex> lk(mutex_);
        // Try first duid.
        if (duid) {
            // Try to acquire the by-client-id lock and return the holder
            // when it failed.
            holder_id = lookup(duid);
            if (!holder_id) {
                locked_client_id_ = duid;
                lockById();
            } else if (cont) {
                next_query_id = holder_id->next_query_;
                holder_id->next_query_ = query;
                holder_id->cont_ = cont;
            }
        }
        if (!holder_id) {
            if (!hwaddr) {
                return (true);
            }
            // Try to acquire the by-hw-addr lock and return the holder
            // when it failed.
            holder_hw = lookup(hwaddr);
            if (!holder_hw) {
                locked_hwaddr_ = hwaddr;
                lockByHWAddr();
                return (true);
            } else if (cont) {
                next_query_hw = holder_hw->next_query_;
                holder_hw->next_query_ = query;
                holder_hw->cont_ = cont;
            }
        }
    }

    if (holder_id) {
        // This query is a by-id duplicate so put the continuation.
        if (cont) {
            if (next_query_id) {
                // Logging a warning as it is supposed to be a rare event
                // with well behaving clients...
                LOG_DEBUG(bad_packet4_logger, DBGLVL_PKT_HANDLING, DHCP4_PACKET_DROP_0011)
                    .arg(next_query_id->toText())
                    .arg(this_thread::get_id())
                    .arg(holder_id->query_->toText())
                    .arg(holder_id->thread_);
                stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                     static_cast<int64_t>(1));
            }
        } else {
            // Logging a warning as it is supposed to be a rare event
            // with well behaving clients...
            LOG_DEBUG(bad_packet4_logger, DBGLVL_PKT_HANDLING, DHCP4_PACKET_DROP_0011)
                .arg(query->toText())
                .arg(this_thread::get_id())
                .arg(holder_id->query_->toText())
                .arg(holder_id->thread_);
            stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                 static_cast<int64_t>(1));
        }
    } else {
        // This query is a by-hw duplicate so put the continuation.
        if (cont) {
            if (next_query_hw) {
                // Logging a warning as it is supposed to be a rare event
                // with well behaving clients...
                LOG_DEBUG(bad_packet4_logger, DBGLVL_PKT_HANDLING, DHCP4_PACKET_DROP_0012)
                    .arg(next_query_hw->toText())
                    .arg(this_thread::get_id())
                    .arg(holder_hw->query_->toText())
                    .arg(holder_hw->thread_);
                stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                     static_cast<int64_t>(1));
            }
        } else {
            // Logging a warning as it is supposed to be a rare event
            // with well behaving clients...
            LOG_DEBUG(bad_packet4_logger, DBGLVL_PKT_HANDLING, DHCP4_PACKET_DROP_0012)
                .arg(query->toText())
                .arg(this_thread::get_id())
                .arg(holder_hw->query_->toText())
                .arg(holder_hw->thread_);
            stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                 static_cast<int64_t>(1));
        }
    }
    return (false);
}

void
ClientHandler::lockById() {
    // Sanity check.
    if (!locked_client_id_) {
        isc_throw(Unexpected, "nothing to lock in ClientHandler::lockById");
    }

    addById(client_);
}

void
ClientHandler::lockByHWAddr() {
    // Sanity check.
    if (!locked_hwaddr_) {
        isc_throw(Unexpected,
                  "nothing to lock in ClientHandler::lockByHWAddr");
    }

    addByHWAddr(client_);
}

void
ClientHandler::unLockById() {
    // Sanity check.
    if (!locked_client_id_) {
        isc_throw(Unexpected,
                  "nothing to unlock in ClientHandler::unLockById");
    }

    del(locked_client_id_);
    locked_client_id_.reset();
}

void
ClientHandler::unLockByHWAddr() {
    // Sanity check.
    if (!locked_hwaddr_) {
        isc_throw(Unexpected,
                  "nothing to unlock in ClientHandler::unLockByHWAddr");
    }

    del(locked_hwaddr_);
    locked_hwaddr_.reset();
}

}  // namespace dhcp
}  // namespace isc
