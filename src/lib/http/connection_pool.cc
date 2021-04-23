// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <http/connection_pool.h>
#include <util/multi_threading_mgr.h>

namespace isc {
namespace http {

void
HttpConnectionPool::start(const HttpConnectionPtr& connection) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        connections_.insert(connections_.end(), connection);
    } else {
        connections_.insert(connections_.end(), connection);
    }

    connection->asyncAccept();
}

void
HttpConnectionPool::stop(const HttpConnectionPtr& connection) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        connections_.remove(connection);
    } else {
        connections_.remove(connection);
    }

    connection->close();
}

void
HttpConnectionPool::shutdown(const HttpConnectionPtr& connection) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        connections_.remove(connection);
    } else {
        connections_.remove(connection);
    }

    connection->shutdown();
}

void
HttpConnectionPool::stopAll() {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        stopAllInternal();
    } else {
        stopAllInternal();
    }
}

void
HttpConnectionPool::stopAllInternal() {
    for (auto connection = connections_.begin();
         connection != connections_.end();
         ++connection) {
        (*connection)->close();
    }

    connections_.clear();
}

}
}
