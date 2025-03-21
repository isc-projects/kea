// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config_cache.h>
#include <util/multi_threading_mgr.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace isc {
namespace ping_check {

PingCheckConfigPtr&
ConfigCache::getGlobalConfig() {
    return (global_config_);
}

void
ConfigCache::setGlobalConfig(PingCheckConfigPtr& config) {
    if (!config) {
        isc_throw(BadValue, "ConfigCache - global config cannot be empty");
    }

    global_config_ = config;
}

bool
ConfigCache::findConfig(const SubnetID& subnet_id, PingCheckConfigPtr& config) {
    MultiThreadingLock lock(*mutex_);
    return (findConfigInternal(subnet_id, config));
}

bool
ConfigCache::findConfigInternal(const SubnetID& subnet_id, PingCheckConfigPtr& config) const {
    auto it = configs_.find(subnet_id);
    if (it != configs_.end()) {
        config = it->second;
        return (true);
    }

    config = PingCheckConfigPtr();
    return (false);
}

PingCheckConfigPtr
ConfigCache::parseAndCacheConfig(const SubnetID& subnet_id, ConstElementPtr& user_context) {
    PingCheckConfigPtr config;
    if (user_context) {
        ConstElementPtr ping_check_params = user_context->get("ping-check");
        if (ping_check_params) {
            // Copy construct from global to start with.
            config.reset(new PingCheckConfig(*getGlobalConfig()));

            // Now parse in subnet-specific values.  This may throw a DhcpConfigError but
            // that's OK, dealt with by the caller.
            try {
                config->parse(ping_check_params);
            } catch (...) {
                throw;
            }
        }
    }

    // Cache the config. We allow empty configs so higher precedence scopes may
    // override lower precedence scopes.
    cacheConfig(subnet_id, config);
    return (config);
}

void
ConfigCache::cacheConfig(const SubnetID& subnet_id, PingCheckConfigPtr& config) {
    MultiThreadingLock lock(*mutex_);
    configs_[subnet_id] = config;
}

void
ConfigCache::flush() {
    MultiThreadingLock lock(*mutex_);
    // Discard the contents.
    configs_.clear();

    // We use modification time to remember the last time we flushed.
    updateModificationTime();
}

size_t
ConfigCache::size() {
    MultiThreadingLock lock(*mutex_);
    return (configs_.size());
}

boost::posix_time::ptime
ConfigCache::getLastFlushTime() {
    MultiThreadingLock lock(*mutex_);
    return (BaseStampedElement::getModificationTime());
}

} // end of namespace ping_check
} // end of namespace isc
