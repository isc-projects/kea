// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <database/server_collection.h>

using namespace isc::data;

namespace isc {
namespace db {

ServerPtr
ServerFetcher::get(const ServerCollection& collection,
                   const ServerTag& server_tag) {
    auto& index = collection.get<ServerTagIndexTag>();
    auto s = index.find(server_tag.get());
    if (s != index.end()) {
        return (*s);
    }
    return (ServerPtr());
}

} // end of namespace isc::db
} // end of namespace isc
