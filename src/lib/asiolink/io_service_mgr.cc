// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service_mgr.h>

namespace isc {
namespace asiolink {

IOServiceMgr& IOServiceMgr::instance() {
    static IOServiceMgr instance;
    return (instance);
}

void
IOServiceMgr::registerIOService(IOServicePtr io_service) {
    if (!io_service) {
        return;
    }
    auto it = std::find(io_services_.begin(), io_services_.end(), io_service);
    if (it == io_services_.end()) {
        io_services_.push_back(io_service);
    }
}

void
IOServiceMgr::unregisterIOService(IOServicePtr io_service) {
    auto it = std::find(io_services_.begin(), io_services_.end(), io_service);
    if (it != io_services_.end()) {
        io_services_.erase(it);
    }
}

void
IOServiceMgr::pollIOServices() {
    for (auto& io_service : io_services_) {
        io_service->poll();
    }
}

} // namespace asiolink
} // namespace isc
