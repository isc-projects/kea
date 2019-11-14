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
#include <util/boost_time_utils.h>
#include <util/multi_threading_mgr.h>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
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
    global_(new StatContext()) {
}

void
StatsMgr::setValue(const string& name, const int64_t value) {
    MultiThreadingMgr::call(mutex_, [&]() {setValueInternal(name, value);});
}

void
StatsMgr::setValue(const string& name, const double value) {
    MultiThreadingMgr::call(mutex_, [&]() {setValueInternal(name, value);});
}

void
StatsMgr::setValue(const string& name, const StatsDuration& value) {
    MultiThreadingMgr::call(mutex_, [&]() {setValueInternal(name, value);});
}

void
StatsMgr::setValue(const string& name, const string& value) {
    MultiThreadingMgr::call(mutex_, [&]() {setValueInternal(name, value);});
}

void
StatsMgr::addValue(const string& name, const int64_t value) {
    MultiThreadingMgr::call(mutex_, [&]() {addValueInternal(name, value);});
}

void
StatsMgr::addValue(const string& name, const double value) {
    MultiThreadingMgr::call(mutex_, [&]() {addValueInternal(name, value);});
}

void
StatsMgr::addValue(const string& name, const StatsDuration& value) {
    MultiThreadingMgr::call(mutex_, [&]() {addValueInternal(name, value);});
}

void
StatsMgr::addValue(const string& name, const string& value) {
    MultiThreadingMgr::call(mutex_, [&]() {addValueInternal(name, value);});
}

ObservationPtr
StatsMgr::getObservation(const string& name) const {
    ObservationPtr result;
    MultiThreadingMgr::call(mutex_, [&]() {result = getObservationInternal(name);});
    return (result);
}

ObservationPtr
StatsMgr::getObservationInternal(const string& name) const {
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->get(name));
}

void
StatsMgr::addObservation(const ObservationPtr& stat) {
    MultiThreadingMgr::call(mutex_, [&]() {addObservationInternal(stat);});
}

void
StatsMgr::addObservationInternal(const ObservationPtr& stat) {
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->add(stat));
}

bool
StatsMgr::deleteObservation(const string& name) {
    bool result;
    MultiThreadingMgr::call(mutex_, [&]() {result = deleteObservationInternal(name);});
    return (result);
}

bool
StatsMgr::deleteObservationInternal(const string& name) {
    /// @todo: Implement contexts.
    // Currently we keep everything in a global context.
    return (global_->del(name));
}

bool
StatsMgr::setMaxSampleAge(const string& name, const StatsDuration& duration) {
    bool result = false;
    auto lambda = [&]() {
        ObservationPtr obs = getObservationInternal(name);
        if (obs) {
            obs->setMaxSampleAge(duration);
            result = true;
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
    return (result);
}

bool
StatsMgr::setMaxSampleCount(const string& name, uint32_t max_samples) {
    bool result = false;
    auto lambda = [&]() {
        ObservationPtr obs = getObservationInternal(name);
        if (obs) {
            obs->setMaxSampleCount(max_samples);
            result = true;
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
    return (result);
}

void
StatsMgr::setMaxSampleAgeAll(const StatsDuration& duration) {
    MultiThreadingMgr::call(mutex_, [&]() {global_->setMaxSampleAgeAll(duration);});
}

void
StatsMgr::setMaxSampleCountAll(uint32_t max_samples) {
    MultiThreadingMgr::call(mutex_, [&]() {global_->setMaxSampleCountAll(max_samples);});
}

bool
StatsMgr::reset(const string& name) {
    bool result = false;
    auto lambda = [&]() {
        ObservationPtr obs = getObservationInternal(name);
        if (obs) {
            obs->reset();
            result = true;
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
    return (result);
}

bool
StatsMgr::del(const string& name) {
    bool result;
    MultiThreadingMgr::call(mutex_, [&]() {result = global_->del(name);});
    return (result);
}

void
StatsMgr::removeAll() {
    MultiThreadingMgr::call(mutex_, [&]() {global_->clear();});
}

ConstElementPtr
StatsMgr::get(const string& name) const {
    ElementPtr response = Element::createMap(); // a map
    auto lambda = [&]() {
        ObservationPtr obs = getObservationInternal(name);
        if (obs) {
            response->set(name, obs->getJSON()); // that contains observations
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
    return (response);
}

ConstElementPtr
StatsMgr::getAll() const {
    ConstElementPtr result;
    MultiThreadingMgr::call(mutex_, [&]() {result = global_->getAll();});
    return (result);
}

void
StatsMgr::resetAll() {
    MultiThreadingMgr::call(mutex_, [&]() {global_->reset();});
}

size_t
StatsMgr::getSize(const string& name) const {
    size_t size = 0;
    auto lambda = [&]() {
        ObservationPtr obs = getObservationInternal(name);
        if (obs) {
            size = obs->getSize();
        }
    };
    MultiThreadingMgr::call(mutex_, lambda);
    return (size);
}

size_t
StatsMgr::count() const {
    size_t result;
    MultiThreadingMgr::call(mutex_, [&]() {result = global_->size();});
    return (result);
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
                         "All statistics removed."));
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
StatsMgr::statisticSetMaxSampleAgeAllHandler(const string& /*name*/,
                                             const ConstElementPtr& params) {
    string error;
    StatsDuration duration;
    if (!StatsMgr::getStatDuration(params, duration, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    StatsMgr::instance().setMaxSampleAgeAll(duration);
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "All statistics duration limit are set."));
}

ConstElementPtr
StatsMgr::statisticSetMaxSampleCountAllHandler(const string& /*name*/,
                                               const ConstElementPtr& params) {
    string error;
    uint32_t max_samples;
    if (!StatsMgr::getStatMaxSamples(params, max_samples, error)) {
        return (createAnswer(CONTROL_RESULT_ERROR, error));
    }
    StatsMgr::instance().setMaxSampleCountAll(max_samples);
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

};
};
