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
    return MultiThreadingMgr::call(mutex_, [&]() {return getInternal(name);});
}

ObservationPtr StatContext::getInternal(const std::string& name) const {
    auto obs = stats_.find(name);
    if (obs != stats_.end()) {
        return (obs->second);
    }
    return (ObservationPtr());
}

void StatContext::add(const ObservationPtr& obs) {
    MultiThreadingMgr::call(mutex_, [&]() {addInternal(obs);});
}

void StatContext::addInternal(const ObservationPtr& obs) {
    auto existing = stats_.find(obs->getName());
    if (existing == stats_.end()) {
        stats_.insert(make_pair(obs->getName() ,obs));
    } else {
        isc_throw(DuplicateStat, "Statistic named " << obs->getName()
                  << " already exists.");
    }
}

bool StatContext::del(const std::string& name) {
    return (MultiThreadingMgr::call(mutex_, [&]() {return delInternal(name);}));
}

bool StatContext::delInternal(const std::string& name) {
    auto obs = stats_.find(name);
    if (obs != stats_.end()) {
        stats_.erase(obs);
        return (true);
    }
    return (false);
}

size_t StatContext::size() {
    return (MultiThreadingMgr::call(mutex_, [&]() {return sizeInternal();}));
}

size_t StatContext::sizeInternal() {
    return (stats_.size());
}

void StatContext::clear() {
    MultiThreadingMgr::call(mutex_, [&]() {clearInternal();});
}

void StatContext::clearInternal() {
    stats_.clear();
}

void StatContext::resetAll() {
    MultiThreadingMgr::call(mutex_, [&]() {resetAllInternal();});
}

void StatContext::resetAllInternal() {
    // Let's iterate over all stored statistics...
    for (auto s : stats_) {
        // ... and reset each statistic.
        s.second->reset();
    }
}

ConstElementPtr StatContext::getAll() const {
    return (MultiThreadingMgr::call(mutex_, [&]() {return getAllInternal();}));
}

ConstElementPtr StatContext::getAllInternal() const {
    ElementPtr map = Element::createMap(); // a map
    // Let's iterate over all stored statistics...
    for (auto s : stats_) {
        // ... and add each of them to the map.
        map->set(s.first, s.second->getJSON());
    }
    return (map);
}

void StatContext::setMaxSampleCountAll(uint32_t max_samples) {
    MultiThreadingMgr::call(mutex_, [&]() {setMaxSampleCountAllInternal(max_samples);});
}

void StatContext::setMaxSampleCountAllInternal(uint32_t max_samples) {
    // Let's iterate over all stored statistics...
    for (auto s : stats_) {
        // ... and set count limit for each statistic.
        s.second->setMaxSampleCount(max_samples);
    }
}

void StatContext::setMaxSampleAgeAll(const StatsDuration& duration) {
    MultiThreadingMgr::call(mutex_, [&]() {setMaxSampleAgeAllInternal(duration);});
}

void StatContext::setMaxSampleAgeAllInternal(const StatsDuration& duration) {
    // Let's iterate over all stored statistics...
    for (auto s : stats_) {
        // ... and set duration limit for each statistic.
        s.second->setMaxSampleAge(duration);
    }
}

};
};
