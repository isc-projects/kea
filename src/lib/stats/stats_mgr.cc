// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <util/multi_threading_mgr.h>
#include <util/bigints.h>

#include <boost/make_shared.hpp>

#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace isc::data;
using namespace isc::config;
using namespace isc::util;

namespace isc {
namespace stats {

StatsMgr&
StatsMgr::instance() {
    static StatsMgr stats_mgr;
    return (stats_mgr);
}

StatsMgr::StatsMgr() :
    global_(boost::make_shared<StatContext>()), mutex_(new mutex()) {
}

void
StatsMgr::setValue(const string& name, const int64_t value) {
    MultiThreadingLock lock(*mutex_);
    setValueInternal(name, value);
}

void
StatsMgr::setValue(const string& name, const int128_t& value) {
    MultiThreadingLock lock(*mutex_);
    setValueInternal(name, value);
}

void
StatsMgr::setValue(const string& name, const double value) {
    MultiThreadingLock lock(*mutex_);
    setValueInternal(name, value);
}

void
StatsMgr::setValue(const string& name, const StatsDuration& value) {
    MultiThreadingLock lock(*mutex_);
    setValueInternal(name, value);
}

void
StatsMgr::setValue(const string& name, const string& value) {
    MultiThreadingLock lock(*mutex_);
    setValueInternal(name, value);
}

void
StatsMgr::addValue(const string& name, const int64_t value) {
    MultiThreadingLock lock(*mutex_);
    addValueInternal(name, value);
}

void
StatsMgr::addValue(const string& name, const int128_t& value) {
    MultiThreadingLock lock(*mutex_);
    addValueInternal(name, value);
}

void
StatsMgr::addValue(const string& name, const double value) {
    MultiThreadingLock lock(*mutex_);
    addValueInternal(name, value);
}

void
StatsMgr::addValue(const string& name, const StatsDuration& value) {
    MultiThreadingLock lock(*mutex_);
    addValueInternal(name, value);
}

void
StatsMgr::addValue(const string& name, const string& value) {
    MultiThreadingLock lock(*mutex_);
    addValueInternal(name, value);
}

ObservationPtr
StatsMgr::getObservation(const string& name) const {
    MultiThreadingLock lock(*mutex_);
    return (getObservationInternal(name));
}

ObservationPtr
StatsMgr::getObservationInternal(const string& name) const {
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->get(name));
}

void
StatsMgr::addObservation(const ObservationPtr& stat) {
    MultiThreadingLock lock(*mutex_);
    addObservationInternal(stat);
}

void
StatsMgr::addObservationInternal(const ObservationPtr& stat) {
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    global_->add(stat);
}

bool
StatsMgr::deleteObservation(const string& name) {
    MultiThreadingLock lock(*mutex_);
    return (deleteObservationInternal(name));
}

bool
StatsMgr::deleteObservationInternal(const string& name) {
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->del(name));
}

bool
StatsMgr::setMaxSampleAge(const string& name, const StatsDuration& duration) {
    MultiThreadingLock lock(*mutex_);
    return (setMaxSampleAgeInternal(name, duration));
}

bool
StatsMgr::setMaxSampleAgeInternal(const string& name,
                                  const StatsDuration& duration) {
    ObservationPtr obs = getObservationInternal(name);
    if (obs) {
        obs->setMaxSampleAge(duration);
        return (true);
    }
    return (false);
}

bool
StatsMgr::setMaxSampleCount(const string& name, uint32_t max_samples) {
    MultiThreadingLock lock(*mutex_);
    return (setMaxSampleCountInternal(name, max_samples));
}

bool
StatsMgr::setMaxSampleCountInternal(const string& name,
                                    uint32_t max_samples) {
    ObservationPtr obs = getObservationInternal(name);
    if (obs) {
        obs->setMaxSampleCount(max_samples);
        return (true);
    }
    return (false);
}

void
StatsMgr::setMaxSampleAgeAll(const StatsDuration& duration) {
    MultiThreadingLock lock(*mutex_);
    setMaxSampleAgeAllInternal(duration);
}

void
StatsMgr::setMaxSampleAgeAllInternal(const StatsDuration& duration) {
    global_->setMaxSampleAgeAll(duration);
}

void
StatsMgr::setMaxSampleCountAll(uint32_t max_samples) {
    MultiThreadingLock lock(*mutex_);
    setMaxSampleCountAllInternal(max_samples);
}

void
StatsMgr::setMaxSampleCountAllInternal(uint32_t max_samples) {
    global_->setMaxSampleCountAll(max_samples);
}

void
StatsMgr::setMaxSampleAgeDefault(const StatsDuration& duration) {
    MultiThreadingLock lock(*mutex_);
    setMaxSampleAgeDefaultInternal(duration);
}

void
StatsMgr::setMaxSampleAgeDefaultInternal(const StatsDuration& duration) {
    Observation::setMaxSampleAgeDefault(duration);
}

void
StatsMgr::setMaxSampleCountDefault(uint32_t max_samples) {
    MultiThreadingLock lock(*mutex_);
    setMaxSampleCountDefaultInternal(max_samples);
}

void
StatsMgr::setMaxSampleCountDefaultInternal(uint32_t max_samples) {
    Observation::setMaxSampleCountDefault(max_samples);
}

const StatsDuration&
StatsMgr::getMaxSampleAgeDefault() const {
    MultiThreadingLock lock(*mutex_);
    return (getMaxSampleAgeDefaultInternal());
}

const StatsDuration&
StatsMgr::getMaxSampleAgeDefaultInternal() const {
    return (Observation::getMaxSampleAgeDefault());
}

uint32_t
StatsMgr::getMaxSampleCountDefault() const {
    MultiThreadingLock lock(*mutex_);
    return (getMaxSampleCountDefaultInternal());
}

uint32_t
StatsMgr::getMaxSampleCountDefaultInternal() const {
    return (Observation::getMaxSampleCountDefault());
}

bool
StatsMgr::reset(const string& name) {
    MultiThreadingLock lock(*mutex_);
    return (resetInternal(name));
}

bool
StatsMgr::resetInternal(const string& name) {
    ObservationPtr obs = getObservationInternal(name);
    if (obs) {
        obs->reset();
        return (true);
    }
    return (false);
}

bool
StatsMgr::del(const string& name) {
    MultiThreadingLock lock(*mutex_);
    return (delInternal(name));
}

bool
StatsMgr::delInternal(const string& name) {
    return (global_->del(name));
}

void
StatsMgr::removeAll() {
    MultiThreadingLock lock(*mutex_);
    removeAllInternal();
}

void
StatsMgr::removeAllInternal() {
    global_->clear();
}

ConstElementPtr
StatsMgr::get(const string& name) const {
    MultiThreadingLock lock(*mutex_);
    return (getInternal(name));
}

ConstElementPtr
StatsMgr::getInternal(const string& name) const {
    ElementPtr map = Element::createMap(); // a map
    ObservationPtr obs = getObservationInternal(name);
    if (obs) {
        map->set(name, obs->getJSON()); // that contains observations
    }
    return (map);
}

ConstElementPtr
StatsMgr::getAll() const {
    MultiThreadingLock lock(*mutex_);
    return (getAllInternal());
}

ConstElementPtr
StatsMgr::getAllInternal() const {
    return (global_->getAll());
}

void
StatsMgr::resetAll() {
    MultiThreadingLock lock(*mutex_);
    resetAllInternal();
}

void
StatsMgr::resetAllInternal() {
    global_->resetAll();
}

size_t
StatsMgr::getSize(const string& name) const {
    MultiThreadingLock lock(*mutex_);
    return (getSizeInternal(name));
}

size_t
StatsMgr::getSizeInternal(const string& name) const {
    ObservationPtr obs = getObservationInternal(name);
    if (obs) {
        return (obs->getSize());
    }
    return (0);
}

size_t
StatsMgr::count() const {
    MultiThreadingLock lock(*mutex_);
    return (countInternal());
}

size_t
StatsMgr::countInternal() const {
    return (global_->size());
}

ConstElementPtr
StatsMgr::statisticSetMaxSampleAgeHandler(const string& /*name*/,
                                          const ConstElementPtr& params) {
    string name, error;
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

ConstElementPtr
StatsMgr::statisticSetMaxSampleCountHandler(const string& /*name*/,
                                            const ConstElementPtr& params) {
    string name, error;
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

ConstElementPtr
StatsMgr::statisticGetHandler(const string& /*name*/,
                              const ConstElementPtr& params) {
    string name, error;
    if (!StatsMgr::getStatName(params, name, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         StatsMgr::instance().get(name)));
}

ConstElementPtr
StatsMgr::statisticResetHandler(const string& /*name*/,
                                const ConstElementPtr& params) {
    string name, error;
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

ConstElementPtr
StatsMgr::statisticRemoveHandler(const string& /*name*/,
                                 const ConstElementPtr& params) {
    string name, error;
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

ConstElementPtr
StatsMgr::statisticRemoveAllHandler(const string& /*name*/,
                                    const ConstElementPtr& /*params*/) {
    StatsMgr::instance().removeAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "Warning: statistic-remove-all command is deprecated."
                         " All statistics removed."));
}

ConstElementPtr
StatsMgr::statisticGetAllHandler(const string& /*name*/,
                                 const ConstElementPtr& /*params*/) {
    ConstElementPtr all_stats = StatsMgr::instance().getAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS, all_stats));
}

ConstElementPtr
StatsMgr::statisticResetAllHandler(const string& /*name*/,
                                   const ConstElementPtr& /*params*/) {
    StatsMgr::instance().resetAll();
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics reset to neutral values."));
}

ConstElementPtr
StatsMgr::statisticSetMaxSampleAgeAllHandler(const ConstElementPtr& params) {
    string error;
    StatsDuration duration;
    if (!StatsMgr::getStatDuration(params, duration, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    MultiThreadingLock lock(*mutex_);
    StatsMgr::instance().setMaxSampleCountDefaultInternal(0);
    StatsMgr::instance().setMaxSampleAgeDefaultInternal(duration);
    StatsMgr::instance().setMaxSampleAgeAllInternal(duration);
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics duration limit are set."));
}

ConstElementPtr
StatsMgr::statisticSetMaxSampleCountAllHandler(const ConstElementPtr& params) {
    string error;
    uint32_t max_samples;
    if (!StatsMgr::getStatMaxSamples(params, max_samples, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    if (max_samples == 0) {
        error = "'max-samples' parameter must not be zero";
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    MultiThreadingLock lock(*mutex_);
    StatsMgr::instance().setMaxSampleCountDefaultInternal(max_samples);
    StatsMgr::instance().setMaxSampleCountAllInternal(max_samples);
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics count limit are set."));
}

bool
StatsMgr::getStatName(const ConstElementPtr& params,
                      string& name,
                      string& reason) {
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
StatsMgr::getStatDuration(const ConstElementPtr& params,
                          StatsDuration& duration,
                          string& reason) {
    if (!params) {
        reason = "Missing mandatory 'duration' parameter.";
        return (false);
    }
    ConstElementPtr stat_duration = params->get("duration");
    if (!stat_duration) {
        reason = "Missing mandatory 'duration' parameter.";
        return (false);
    }
    duration = std::chrono::seconds(stat_duration->intValue());
    return (true);
}

bool
StatsMgr::getStatMaxSamples(const ConstElementPtr& params,
                            uint32_t& max_samples,
                            string& reason) {
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

} // end of namespace stats
} // end of namespace isc
