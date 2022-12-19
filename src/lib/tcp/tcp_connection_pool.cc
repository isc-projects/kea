// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <tcp/tcp_connection_pool.h>
#include <util/multi_threading_mgr.h>

using namespace isc::asiolink;

namespace isc {
namespace tcp {

std::atomic<uint64_t>
TcpConnectionPool::started_counter_(0);

std::atomic<uint64_t>
TcpConnectionPool::stopped_counter_(0);

std::atomic<uint64_t>
TcpConnectionPool::rejected_counter_(0);

void
TcpConnectionPool::start(const TcpConnectionPtr& connection) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        connections_.insert(connections_.end(), connection);
        started_counter_ += 1;
    } else {
        connections_.insert(connections_.end(), connection);
        started_counter_ += 1;
    }

    connection->asyncAccept();
}

void
TcpConnectionPool::stop(const TcpConnectionPtr& connection) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        size_t before = connections_.size();
        connections_.remove(connection);
        size_t after = connections_.size();
        stopped_counter_ += before - after;
    } else {
        size_t before = connections_.size();
        connections_.remove(connection);
        size_t after = connections_.size();
        stopped_counter_ += before - after;
    }

    connection->close();
}

void
TcpConnectionPool::shutdown(const TcpConnectionPtr& connection) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        size_t before = connections_.size();
        connections_.remove(connection);
        size_t after = connections_.size();
        stopped_counter_ += before - after;
    } else {
        size_t before = connections_.size();
        connections_.remove(connection);
        size_t after = connections_.size();
        stopped_counter_ += before - after;
    }

    connection->shutdown();
}

void
TcpConnectionPool::stopAll() {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        stopAllInternal();
    } else {
        stopAllInternal();
    }
}

void
TcpConnectionPool::stopAllInternal() {
    for (auto connection = connections_.begin();
         connection != connections_.end();
         ++connection) {
        (*connection)->close();
    }

    size_t cnt = connections_.size();
    connections_.clear();
    stopped_counter_ += cnt;
}

size_t
TcpConnectionPool::usedByRemoteIp(const IOAddress& remote_ip,
                                  size_t& total_connections) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        return (usedByRemoteIpInternal(remote_ip, total_connections));
    } else {
        return (usedByRemoteIpInternal(remote_ip, total_connections));
    }
}

size_t
TcpConnectionPool::usedByRemoteIpInternal(const IOAddress& remote_ip,
                                          size_t& total_connections) {
    total_connections = connections_.size();
    size_t cnt = 0;
    for (const auto& conn : connections_) {
        const auto& ep = conn->getRemoteEndpoint();
        if ((ep != TcpConnection::NO_ENDPOINT()) &&
            (IOAddress(ep.address()) == remote_ip)) {
            ++cnt;
        }
    }
    return (cnt);
}

}
}
