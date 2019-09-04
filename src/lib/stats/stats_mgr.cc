// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <util/threads/lock_guard.h>

using namespace std;
using namespace isc::data;
using namespace isc::config;
using namespace isc::util::thread;

namespace isc {
namespace stats {

StatsMgr& StatsMgr::instance() {
    static StatsMgr stats_mgr;
    return (stats_mgr);
}

StatsMgr::StatsMgr() :
    global_(new StatContext()) {
    mutex_.reset(new std::mutex());
}

void StatsMgr::setValue(const std::string& name, const int64_t value, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    setValueInternal(name, value);
}

void StatsMgr::setValue(const std::string& name, const double value, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    setValueInternal(name, value);
}

void StatsMgr::setValue(const std::string& name, const StatsDuration& value, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    setValueInternal(name, value);
}

void StatsMgr::setValue(const std::string& name, const std::string& value, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    setValueInternal(name, value);
}

void StatsMgr::addValue(const std::string& name, const int64_t value, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    addValueInternal(name, value);
}

void StatsMgr::addValue(const std::string& name, const double value, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    addValueInternal(name, value);
}

void StatsMgr::addValue(const std::string& name, const StatsDuration& value, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    addValueInternal(name, value);
}

void StatsMgr::addValue(const std::string& name, const std::string& value, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    addValueInternal(name, value);
}

ObservationPtr StatsMgr::getObservation(const std::string& name, bool lock) const {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->get(name));
}

void StatsMgr::addObservation(const ObservationPtr& stat, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->add(stat));
}

bool StatsMgr::deleteObservation(const std::string& name, bool lock) {
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->del(name));
}

void StatsMgr::setMaxSampleAge(const std::string& ,
                               const StatsDuration&) {
    LockGuard<std::mutex> lock(mutex_.get());
    isc_throw(NotImplemented, "setMaxSampleAge not implemented");
}

void StatsMgr::setMaxSampleCount(const std::string& , uint32_t){
    LockGuard<std::mutex> lock(mutex_.get());
    isc_throw(NotImplemented, "setMaxSampleCount not implemented");
}

bool StatsMgr::reset(const std::string& name) {
    LockGuard<std::mutex> lock(mutex_.get());
    ObservationPtr obs = getObservation(name, false);
    if (obs) {
        obs->reset();
        return (true);
    } else {
        return (false);
    }
}

bool StatsMgr::del(const std::string& name) {
    LockGuard<std::mutex> lock(mutex_.get());
    return (global_->del(name));
}

void StatsMgr::removeAll() {
    LockGuard<std::mutex> lock(mutex_.get());
    global_->stats_.clear();
}

isc::data::ConstElementPtr StatsMgr::get(const std::string& name) const {
    LockGuard<std::mutex> lock(mutex_.get());
    isc::data::ElementPtr response = isc::data::Element::createMap(); // a map
    ObservationPtr obs = getObservation(name, false);
    if (obs) {
        response->set(name, obs->getJSON()); // that contains the observation
    }
    return (response);
}

isc::data::ConstElementPtr StatsMgr::getAll() const {
    LockGuard<std::mutex> lock(mutex_.get());
    isc::data::ElementPtr map = isc::data::Element::createMap(); // a map

    // Let's iterate over all stored statistics...
    for (std::map<std::string, ObservationPtr>::iterator s = global_->stats_.begin();
         s != global_->stats_.end(); ++s) {

        // ... and add each of them to the map.
        map->set(s->first, s->second->getJSON());
    }
    return (map);
}

void StatsMgr::resetAll() {
    LockGuard<std::mutex> lock(mutex_.get());
    // Let's iterate over all stored statistics...
    for (std::map<std::string, ObservationPtr>::iterator s = global_->stats_.begin();
         s != global_->stats_.end(); ++s) {

        // ... and reset each statistic.
        s->second->reset();
    }
}

size_t StatsMgr::count() const {
    LockGuard<std::mutex> lock(mutex_.get());
    return (global_->stats_.size());
}

isc::data::ConstElementPtr
StatsMgr::statisticGetHandler(const std::string& /*name*/,
                              const isc::data::ConstElementPtr& params) {
    std::string name, error;
    if (!getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         instance().get(name)));
}

isc::data::ConstElementPtr
StatsMgr::statisticResetHandler(const std::string& /*name*/,
                                const isc::data::ConstElementPtr& params) {
    std::string name, error;
    if (!getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }

    if (instance().reset(name)) {
        return (createAnswer(CONTROL_RESULT_SUCCESS,
                             "Statistic '" + name + "' reset."));
    } else {
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "No '" + name + "' statistic found"));
    }
}

isc::data::ConstElementPtr
StatsMgr::statisticRemoveHandler(const std::string& /*name*/,
                                 const isc::data::ConstElementPtr& params) {
    std::string name, error;
    if (!getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    if (instance().del(name)) {
        return (createAnswer(CONTROL_RESULT_SUCCESS,
                             "Statistic '" + name + "' removed."));
    } else {
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "No '" + name + "' statistic found"));
    }

}

isc::data::ConstElementPtr
StatsMgr::statisticRemoveAllHandler(const std::string& /*name*/,
                                    const isc::data::ConstElementPtr& /*params*/) {
    instance().removeAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics removed."));
}

isc::data::ConstElementPtr
StatsMgr::statisticGetAllHandler(const std::string& /*name*/,
                                 const isc::data::ConstElementPtr& /*params*/) {
    ConstElementPtr all_stats = instance().getAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS, all_stats));
}

isc::data::ConstElementPtr
StatsMgr::statisticResetAllHandler(const std::string& /*name*/,
                                   const isc::data::ConstElementPtr& /*params*/) {
    instance().resetAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics reset to neutral values."));
}

bool
StatsMgr::getStatName(const isc::data::ConstElementPtr& params,
                      std::string& name,
                      std::string& reason) {
    if (!params) {
        reason = "Missing mandatory 'name' parameter.";
        return (false);
    }
    ConstElementPtr stat_name = params->get("name");
    if (!stat_name) {
        reason = "Missing mandatory 'name' parameter.";
        return (false);
    }
    if (stat_name->getType() != Element::string) {
        reason = "'name' parameter expected to be a string.";
        return (false);
    }

    name = stat_name->stringValue();
    return (true);
}

};
};
