// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <radius_service.h>

using namespace std;
using namespace isc;
using namespace isc::data;

namespace isc {
namespace radius {

RadiusService::RadiusService(const std::string& name)
    : name_(name), enabled_(false), peer_updates_(true),
      max_pending_requests_(0) {
}

ElementPtr
RadiusService::toElement() const {
    ElementPtr result = Element::createMap();

    // servers.
    if (!servers_.empty()) {
        ElementPtr servers = Element::createList();
        for (auto const& server : servers_) {
            if (server) {
                servers->add(server->toElement());
            }
        }
        result->set("servers", servers);
    }

    // attributes.
    result->set("attributes", attributes_.toElement());

    return (result);
}

} // end of namespace isc::radius
} // end of namespace isc
