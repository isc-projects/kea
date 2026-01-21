// Copyright (C) 2023-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <radius_service.h>
#include <util/multi_threading_mgr.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace radius {

std::mutex
RadiusService::idle_timer_mutex_;

RadiusService::RadiusService(const std::string& name)
    : name_(name), enabled_(false), peer_updates_(true),
      max_pending_requests_(0), idle_timer_interval_(), idle_timer_() {
}

RadiusService::~RadiusService() {
    MultiThreadingLock lock(idle_timer_mutex_);
    cancelIdleTimer();
}

ElementPtr
RadiusService::toElement() const {
    ElementPtr result = Element::createMap();

    // enabled.
    result->set("enabled", Element::create(enabled_));

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
    if (!attributes_.empty()) {
        result->set("attributes", attributes_.toElement());
    }

    // idle-timer-interval.
    result->set("idle-timer-interval", Element::create(idle_timer_interval_));

    return (result);
}

void
RadiusService::cancelIdleTimer() {
    if (idle_timer_) {
        idle_timer_->cancel();
        idle_timer_.reset();
    }
}

} // end of namespace isc::radius
} // end of namespace isc
