// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
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

ObservationPtr
StatContext::get(const std::string& name) const {
    auto obs = stats_.find(name);
    if (obs != stats_.end()) {
        return (obs->second);
    }
    return (ObservationPtr());
}

void
StatContext::add(const ObservationPtr& obs) {
    auto existing = stats_.find(obs->getName());
    if (existing == stats_.end()) {
        stats_.insert(make_pair(obs->getName() ,obs));
    } else {
        isc_throw(DuplicateStat, "Statistic named " << obs->getName()
                  << " already exists.");
    }
}

bool
StatContext::del(const std::string& name) {
    auto obs = stats_.find(name);
    if (obs != stats_.end()) {
        stats_.erase(obs);
        return (true);
    }
    return (false);
}

size_t
StatContext::size() {
    return (stats_.size());
}

void
StatContext::clear() {
    stats_.clear();
}

void
StatContext::resetAll() {
    // Let's iterate over all stored statistics...
    for (auto s : stats_) {
        // ... and reset each statistic.
        s.second->reset();
    }
}

ConstElementPtr
StatContext::getAll() const {
    ElementPtr map = Element::createMap(); // a map
    // Let's iterate over all stored statistics...
    for (auto s : stats_) {
        // ... and add each of them to the map.
        map->set(s.first, s.second->getJSON());
    }
    return (map);
}

void
StatContext::setMaxSampleCountAll(uint32_t max_samples) {
    // Let's iterate over all stored statistics...
    for (auto s : stats_) {
        // ... and set count limit for each statistic.
        s.second->setMaxSampleCount(max_samples);
    }
}

void
StatContext::setMaxSampleAgeAll(const StatsDuration& duration) {
    // Let's iterate over all stored statistics...
    for (auto s : stats_) {
        // ... and set duration limit for each statistic.
        s.second->setMaxSampleAge(duration);
    }
}

}  // namespace stats
}  // namespace isc
