// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <stats/context.h>
#include <util/multi_threading_mgr.h>
#include <map>

using namespace std;
using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace stats {

ObservationPtr StatContext::get(const std::string& name) const {
    ObservationPtr result;
    auto lambda = [&]() {
        auto obs = stats_.find(name);
        if (obs != stats_.end()) {
            result = obs->second;
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
    return (result);
}

void StatContext::add(const ObservationPtr& obs) {
    auto lambda = [&]() {
        auto existing = stats_.find(obs->getName());
        if (existing == stats_.end()) {
            stats_.insert(make_pair(obs->getName() ,obs));
        } else {
            isc_throw(DuplicateStat, "Statistic named " << obs->getName()
                      << " already exists.");
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
}

bool StatContext::del(const std::string& name) {
    bool result = false;
    auto lambda = [&]() {
        auto obs = stats_.find(name);
        if (obs != stats_.end()) {
            stats_.erase(obs);
            result = true;
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
    return (result);
}

size_t StatContext::size() {
    size_t size;
    MultiThreadingMgr::call(mutex_, [&]() {size = stats_.size();});
    return (size);
}

void StatContext::clear() {
    MultiThreadingMgr::call(mutex_, [&]() {stats_.clear();});
}

void StatContext::reset() {
    auto lambda = [&]() {
        // Let's iterate over all stored statistics...
        for (auto s : stats_) {
            // ... and reset each statistic.
            s.second->reset();
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
}

ConstElementPtr
StatContext::getAll() const {
    ElementPtr map = Element::createMap(); // a map
    auto lambda = [&]() {
        // Let's iterate over all stored statistics...
        for (auto s : stats_) {
            // ... and add each of them to the map.
            map->set(s.first, s.second->getJSON());
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
    return (map);
}

void
StatContext::setMaxSampleAgeAll(const StatsDuration& duration) {
    auto lambda = [&]() {
        // Let's iterate over all stored statistics...
        for (auto s : stats_) {
            // ... and set duration limit for each statistic.
            s.second->setMaxSampleAge(duration);
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
}

void
StatContext::setMaxSampleCountAll(uint32_t max_samples) {
    auto lambda = [&]() {
        // Let's iterate over all stored statistics...
        for (auto s : stats_) {
            // ... and set count limit for each statistic.
            s.second->setMaxSampleCount(max_samples);
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
}

};
};
