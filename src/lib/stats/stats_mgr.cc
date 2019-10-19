// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <util/lock_guard.h>
#include <util/boost_time_utils.h>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace isc::data;
using namespace isc::config;
using namespace isc::util;

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
    return; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    setValueInternal(name, value);
}

void StatsMgr::setValue(const std::string& name, const double value, bool lock) {
    return; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    setValueInternal(name, value);
}

void StatsMgr::setValue(const std::string& name, const StatsDuration& value, bool lock) {
    return; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    setValueInternal(name, value);
}

void StatsMgr::setValue(const std::string& name, const std::string& value, bool lock) {
    return; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    setValueInternal(name, value);
}

void StatsMgr::addValue(const std::string& name, const int64_t value, bool lock) {
    return; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    addValueInternal(name, value);
}

void StatsMgr::addValue(const std::string& name, const double value, bool lock) {
    return; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    addValueInternal(name, value);
}

void StatsMgr::addValue(const std::string& name, const StatsDuration& value, bool lock) {
    return; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    addValueInternal(name, value);
}

void StatsMgr::addValue(const std::string& name, const std::string& value, bool lock) {
    return; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    addValueInternal(name, value);
}

ObservationPtr StatsMgr::getObservation(const std::string& name, bool lock) const {
    return ObservationPtr(); // to use rw locks
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
    return; // to use rw locks
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
    return true; // to use rw locks
    std::mutex* mlock = nullptr;
    if (lock) {
        mlock = mutex_.get();
    }
    LockGuard<std::mutex> lockGuard(mlock);
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->del(name));
}

bool StatsMgr::setMaxSampleAge(const std::string& name,
                               const StatsDuration& duration) {
    return true; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    ObservationPtr obs = getObservation(name, false);
    if (obs) {
        obs->setMaxSampleAge(duration);
        return (true);
    } else {
        return (false);
    }
}

bool StatsMgr::setMaxSampleCount(const std::string& name,
                                 uint32_t max_samples) {
    return true; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    ObservationPtr obs = getObservation(name, false);
    if (obs) {
        obs->setMaxSampleCount(max_samples);
        return (true);
    } else {
        return (false);
    }
}

void StatsMgr::setMaxSampleAgeAll(const StatsDuration& duration) {
    return; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    // Let's iterate over all stored statistics...
    for (std::map<std::string, ObservationPtr>::iterator s = global_->stats_.begin();
         s != global_->stats_.end(); ++s) {

        // ... and set duration limit for each statistic.
        s->second->setMaxSampleAge(duration);
    }
}

void StatsMgr::setMaxSampleCountAll(uint32_t max_samples) {
    return; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    // Let's iterate over all stored statistics...
    for (std::map<std::string, ObservationPtr>::iterator s = global_->stats_.begin();
         s != global_->stats_.end(); ++s) {

        // ... and set count limit for each statistic.
        s->second->setMaxSampleCount(max_samples);
    }
}

bool StatsMgr::reset(const std::string& name) {
    return true; // to use rw locks
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
    return true; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    return (global_->del(name));
}

void StatsMgr::removeAll() {
    return; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    global_->stats_.clear();
}

isc::data::ConstElementPtr StatsMgr::get(const std::string& name) const {
    return ConstElementPtr(); // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    isc::data::ElementPtr response = isc::data::Element::createMap(); // a map
    ObservationPtr obs = getObservation(name, false);
    if (obs) {
        response->set(name, obs->getJSON()); // that contains observations
    }
    return (response);
}

isc::data::ConstElementPtr StatsMgr::getAll() const {
    return ConstElementPtr(); // to use rw locks
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
    return; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    // Let's iterate over all stored statistics...
    for (std::map<std::string, ObservationPtr>::iterator s = global_->stats_.begin();
         s != global_->stats_.end(); ++s) {

        // ... and reset each statistic.
        s->second->reset();
    }
}

size_t StatsMgr::getSize(const std::string& name) const {
    return 0; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    ObservationPtr obs = getObservation(name, false);
    size_t size = 0;
    if (obs) {
        size = obs->getSize();
    }
    return (size);
}

size_t StatsMgr::count() const {
    return 0; // to use rw locks
    LockGuard<std::mutex> lock(mutex_.get());
    return (global_->stats_.size());
}

isc::data::ConstElementPtr
StatsMgr::statisticSetMaxSampleAgeHandler(const std::string& /*name*/,
                                          const isc::data::ConstElementPtr& params) {
    std::string name, error;
    StatsDuration duration;
    if (!StatsMgr::getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    if (!StatsMgr::getStatDuration(params, duration, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    if (StatsMgr::instance().setMaxSampleAge(name, duration)) {
        return (createAnswer(CONTROL_RESULT_SUCCESS,
                            "Statistic '" + name + "' duration limit is set."));
    } else {
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "No '" + name + "' statistic found"));
    }
}

isc::data::ConstElementPtr
StatsMgr::statisticSetMaxSampleCountHandler(const std::string& /*name*/,
                                            const isc::data::ConstElementPtr& params) {
    std::string name, error;
    uint32_t max_samples;
    if (!StatsMgr::getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    if (!StatsMgr::getStatMaxSamples(params, max_samples, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    if (StatsMgr::instance().setMaxSampleCount(name, max_samples)) {
        return (createAnswer(CONTROL_RESULT_SUCCESS,
                            "Statistic '" + name + "' count limit is set."));
    } else {
        return (createAnswer(CONTROL_RESULT_ERROR,
                           "No '" + name + "' statistic found"));
    }
}

isc::data::ConstElementPtr
StatsMgr::statisticGetHandler(const std::string& /*name*/,
                              const isc::data::ConstElementPtr& params) {
    std::string name, error;
    if (!StatsMgr::getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         StatsMgr::instance().get(name)));
}

isc::data::ConstElementPtr
StatsMgr::statisticResetHandler(const std::string& /*name*/,
                                const isc::data::ConstElementPtr& params) {
    std::string name, error;
    if (!StatsMgr::getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }

    if (StatsMgr::instance().reset(name)) {
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
    if (!StatsMgr::getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    if (StatsMgr::instance().del(name)) {
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
    StatsMgr::instance().removeAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics removed."));
}

isc::data::ConstElementPtr
StatsMgr::statisticGetAllHandler(const std::string& /*name*/,
                                 const isc::data::ConstElementPtr& /*params*/) {
    ConstElementPtr all_stats = StatsMgr::instance().getAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS, all_stats));
}

isc::data::ConstElementPtr
StatsMgr::statisticResetAllHandler(const std::string& /*name*/,
                                   const isc::data::ConstElementPtr& /*params*/) {
    StatsMgr::instance().resetAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics reset to neutral values."));
}

isc::data::ConstElementPtr
StatsMgr::statisticSetMaxSampleAgeAllHandler(const std::string& /*name*/,
                                             const isc::data::ConstElementPtr& params) {
    std::string error;
    StatsDuration duration;
    if (!StatsMgr::getStatDuration(params, duration, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    StatsMgr::instance().setMaxSampleAgeAll(duration);
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics duration limit are set."));
}

isc::data::ConstElementPtr
StatsMgr::statisticSetMaxSampleCountAllHandler(const std::string& /*name*/,
                                               const isc::data::ConstElementPtr& params) {
    std::string error;
    uint32_t max_samples;
    if (!StatsMgr::getStatMaxSamples(params, max_samples, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    StatsMgr::instance().setMaxSampleCountAll(max_samples);
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics count limit are set."));
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

bool
StatsMgr::getStatDuration(const isc::data::ConstElementPtr& params,
                          StatsDuration& duration,
                          std::string& reason) {
    if (!params) {
        reason = "Missing mandatory 'duration' parameter.";
        return (false);
    }
    ConstElementPtr stat_duration = params->get("duration");
    if (!stat_duration) {
        reason = "Missing mandatory 'duration' parameter.";
        return (false);
    }

    int64_t time_duration = stat_duration->intValue();

    int64_t hours = time_duration / 3600;
    time_duration -= hours * 3600;

    int64_t minutes = time_duration / 60;
    time_duration -= minutes * 60;

    int64_t seconds = time_duration;
    duration = boost::posix_time::time_duration(hours, minutes, seconds, 0);
    return (true);
}

bool
StatsMgr::getStatMaxSamples(const isc::data::ConstElementPtr& params,
                            uint32_t& max_samples,
                            std::string& reason) {
    if (!params) {
        reason = "Missing mandatory 'max-samples' parameter.";
        return (false);
    }
    ConstElementPtr stat_max_samples = params->get("max-samples");
    if (!stat_max_samples) {
        reason = "Missing mandatory 'max-samples' parameter.";
        return (false);
    }
    if (stat_max_samples->getType() != Element::integer) {
        reason = "'max-samples' parameter expected to be an integer.";
        return (false);
    }

    max_samples = stat_max_samples->intValue();
    return (true);
}

};
};
