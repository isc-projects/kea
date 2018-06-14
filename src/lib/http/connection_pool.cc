// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <http/connection_pool.h>

namespace isc {
namespace http {

void
HttpConnectionPool::start(const HttpConnectionPtr& connection) {
    connections_.insert(connections_.end(), connection);
    connection->asyncAccept();
}

void
HttpConnectionPool::stop(const HttpConnectionPtr& connection) {
    connections_.remove(connection);
    connection->close();
}

void
HttpConnectionPool::stopAll() {
    for (auto connection = connections_.begin();
         connection != connections_.end();
         ++connection) {
        (*connection)->close();
    }
    connections_.clear();
}

}
}
