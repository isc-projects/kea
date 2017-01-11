// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_CONNECTION_POOL_H
#define HTTP_CONNECTION_POOL_H

#include <http/connection.h>
#include <set>

namespace isc {
namespace http {

class HttpConnectionPool {
public:

    void start(const HttpConnectionPtr& connection);

    void stop(const HttpConnectionPtr& connection);

    void stopAll();

private:

    std::set<HttpConnectionPtr> connections_;

};

}
}

#endif

