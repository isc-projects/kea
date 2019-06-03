// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <database/server.h>
#include <exceptions/exceptions.h>
#include <boost/make_shared.hpp>

using namespace isc::db;
using namespace isc::data;

namespace isc {
namespace db {

Server::Server(const ServerTag& tag, const std::string& description)
    : StampedElement(), description_(description) {

    if (description_.length() > 65536) {
        isc_throw(BadValue, "server description must not be longer than"
                  " 65536 characters");
    }

    setServerTag(tag.get());
}

ServerPtr
Server::create(const ServerTag& tag, const std::string& description) {
    return (boost::make_shared<Server>(tag, description));
}

} // end of namespace isc::db
} // end of namespace isc
