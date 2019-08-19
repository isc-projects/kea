// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <stats/observation.h>
#include <util/boost_time_utils.h>
#include <cc/data.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <utility>

using namespace std;
using namespace isc::data;
using namespace boost::posix_time;

namespace isc {
namespace stats {

Observation::Observation(const std::string& name, const int64_t value) :
    name_(name), type_(STAT_INTEGER) {
    setValue(value);
}

Observation::Observation(const std::string& name, const double value) :
    name_(name), type_(STAT_FLOAT) {
    setValue(value);
}

Observation::Observation(const std::string& name, const StatsDuration& value) :
    name_(name), type_(STAT_DURATION) {
    setValue(value);
}

Observation::Observation(const std::string& name, const std::string& value) :
    name_(name), type_(STAT_STRING) {
    setValue(value);
}

void Observation::setMaxSampleAge(const StatsDuration& duration) {
    switch(type_) {
    case STAT_INTEGER: {
        setMaxSampleAgeInternal(integer_samples_, duration, STAT_INTEGER);
        return;
    }
    case STAT_FLOAT: {
        setMaxSampleAgeInternal(float_samples_, duration, STAT_FLOAT);
        return;
    }
    case STAT_DURATION: {
        setMaxSampleAgeInternal(duration_samples_, duration, STAT_DURATION);
        return;
    }
    case STAT_STRING: {
        setMaxSampleAgeInternal(string_samples_, duration, STAT_STRING);
        return;
    }
    default:
        isc_throw(InvalidStatType, "Unknown statistic type: "
                  << typeToText(type_));
    };
}

void Observation::setMaxSampleCount(uint32_t max_samples) {
    switch(type_) {
    case STAT_INTEGER: {
        setMaxSampleCountInternal(integer_samples_, max_samples, STAT_INTEGER);
        return;
    }
    case STAT_FLOAT: {
        setMaxSampleCountInternal(float_samples_, max_samples, STAT_FLOAT);
        return;
    }
    case STAT_DURATION: {
        setMaxSampleCountInternal(duration_samples_, max_samples, STAT_DURATION);
        return;
    }
    case STAT_STRING: {
        setMaxSampleCountInternal(string_samples_, max_samples, STAT_STRING);
        return;
    }
    default:
        isc_throw(InvalidStatType, "Unknown statistic type: "
                  << typeToText(type_));
    };
}

void Observation::addValue(const int64_t value) {
    IntegerSample current = getInteger();
    setValue(current.first + value);
}

void Observation::addValue(const double value) {
    FloatSample current = getFloat();
    setValue(current.first + value);
}

void Observation::addValue(const StatsDuration& value) {
    DurationSample current = getDuration();
    setValue(current.first + value);
}

void Observation::addValue(const std::string& value) {
    StringSample current = getString();
    setValue(current.first + value);
}

void Observation::setValue(const int64_t value) {
    setValueInternal(value, integer_samples_, STAT_INTEGER);
}

void Observation::setValue(const double value) {
    setValueInternal(value, float_samples_, STAT_FLOAT);
}

void Observation::setValue(const StatsDuration& value) {
    setValueInternal(value, duration_samples_, STAT_DURATION);
}

void Observation::setValue(const std::string& value) {
    setValueInternal(value, string_samples_, STAT_STRING);
}

size_t Observation::getSize() const {
    size_t size = 0;
    switch(type_) {
    case STAT_INTEGER: {
        size = getSizeInternal(integer_samples_, STAT_INTEGER);
        return (size);
    }
    case STAT_FLOAT: {
        size = getSizeInternal(float_samples_, STAT_FLOAT);
        return (size);
    }
    case STAT_DURATION: {
        size = getSizeInternal(duration_samples_, STAT_DURATION);
        return (size);
    }
    case STAT_STRING: {
        size = getSizeInternal(string_samples_, STAT_STRING);
        return (size);
    }
    default:
        isc_throw(InvalidStatType, "Unknown statistic type: "
                  << typeToText(type_));
    };
    return (size);
}

std::pair<bool, StatsDuration> Observation::getMaxSampleAge() const {
    return (max_sample_age_);
}

std::pair<bool, uint32_t> Observation::getMaxSampleCount() const {
    return (max_sample_count_);
}

template<typename StorageType>
size_t Observation::getSizeInternal(StorageType& storage, Type exp_type) const {
    if (type_ != exp_type) {
        isc_throw(InvalidStatType, "Invalid statistic type requested: "
                  << typeToText(exp_type) << ", but the actual type is "
                  << typeToText(type_));
    } else {
        return (storage.size());
    }
    return (0); // to avoid compilation error
}

template<typename SampleType, typename StorageType>
void Observation::setValueInternal(SampleType value, StorageType& storage,
                                   Type exp_type) {
    if (type_ != exp_type) {
        isc_throw(InvalidStatType, "Invalid statistic type requested: "
                  << typeToText(exp_type) << ", but the actual type is "
                  << typeToText(type_));
    }

    if (storage.empty()) {
        storage.push_back(make_pair(value, microsec_clock::local_time()));
    } else {
        // Storing of more than one sample
        storage.push_front(make_pair(value, microsec_clock::local_time()));

        if (max_sample_count_.first) {
            // if max_sample_count_ is set to true
            // and size of storage is equal to max_sample_count_
            if (storage.size() > max_sample_count_.second) {
                storage.pop_back(); // removing the last element
            }
        } else {
            StatsDuration range_of_storage =
                storage.front().second - storage.back().second;
            // removing samples until the range_of_storage
            // stops exceeding the duration limit
            while (range_of_storage > max_sample_age_.second) {
                storage.pop_back();
                range_of_storage =
                    storage.front().second - storage.back().second;
            }
        }
    }
}

IntegerSample Observation::getInteger() const {
    return (getValueInternal<IntegerSample>(integer_samples_, STAT_INTEGER));
}

FloatSample Observation::getFloat() const {
    return (getValueInternal<FloatSample>(float_samples_, STAT_FLOAT));
}

DurationSample Observation::getDuration() const {
    return (getValueInternal<DurationSample>(duration_samples_, STAT_DURATION));
}

StringSample Observation::getString() const {
    return (getValueInternal<StringSample>(string_samples_, STAT_STRING));
}

template<typename SampleType, typename Storage>
SampleType Observation::getValueInternal(Storage& storage, Type exp_type) const {
    if (type_ != exp_type) {
        isc_throw(InvalidStatType, "Invalid statistic type requested: "
                  << typeToText(exp_type) << ", but the actual type is "
                  << typeToText(type_));
    }

    if (storage.empty()) {
        // That should never happen. The first element is always initialized in
        // the constructor. reset() sets its value to zero, but the element should
        // still be there.
        isc_throw(Unexpected, "Observation storage container empty");
    }
    return (*storage.begin());
}

std::list<IntegerSample> Observation::getIntegers() const {
    return (getValuesInternal<IntegerSample>(integer_samples_, STAT_INTEGER));
}

std::list<FloatSample> Observation::getFloats() const {
    return (getValuesInternal<FloatSample>(float_samples_, STAT_FLOAT));
}

std::list<DurationSample> Observation::getDurations() const {
    return (getValuesInternal<DurationSample>(duration_samples_, STAT_DURATION));
}

std::list<StringSample> Observation::getStrings() const {
    return (getValuesInternal<StringSample>(string_samples_, STAT_STRING));
}

template<typename SampleType, typename Storage>
std::list<SampleType> Observation::getValuesInternal(Storage& storage,
                                                     Type exp_type) const {
    if (type_ != exp_type) {
        isc_throw(InvalidStatType, "Invalid statistic type requested: "
                  << typeToText(exp_type) << ", but the actual type is "
                  << typeToText(type_));
    }

    if (storage.empty()) {
        // That should never happen. The first element is always initialized in
        // the constructor. reset() sets its value to zero, but the element should
        // still be there.
        isc_throw(Unexpected, "Observation storage container empty");
    }
    return (storage);
}

template<typename StorageType>
void Observation::setMaxSampleAgeInternal(StorageType& storage,
                                          const StatsDuration& duration,
                                          Type exp_type) {
    if (type_ != exp_type) {
        isc_throw(InvalidStatType, "Invalid statistic type requested: "
                  << typeToText(exp_type) << ", but the actual type is "
                  << typeToText(type_));
    }
    // setting new value of max_sample_age_
    max_sample_age_.first = true;
    max_sample_age_.second = duration;
    // deactivating the max_sample_count_ limit
    max_sample_count_.first = false;

    StatsDuration range_of_storage =
        storage.front().second - storage.back().second;

    while (range_of_storage > duration) {
        // deleting elements which are exceeding the duration limit
        storage.pop_back();
        range_of_storage = storage.front().second - storage.back().second;
    }
}

template<typename StorageType>
void Observation::setMaxSampleCountInternal(StorageType& storage,
                                            uint32_t max_samples,
                                            Type exp_type) {
    if (type_ != exp_type) {
        isc_throw(InvalidStatType, "Invalid statistic type requested: "
                  << typeToText(exp_type) << ", but the actual type is "
                  << typeToText(type_));
    }
    // setting new value of max_sample_count_
    max_sample_count_.first = true;
    max_sample_count_.second = max_samples;
    // deactivating the max_sample_age_ limit
    max_sample_age_.first = false;

    while (storage.size() > max_samples) {
        // deleting elements which are exceeding the max_samples limit
        storage.pop_back();
    }
}

std::string Observation::typeToText(Type type) {
    std::stringstream tmp;
    switch (type) {
    case STAT_INTEGER:
        tmp << "integer";
        break;
    case STAT_FLOAT:
        tmp << "float";
        break;
    case STAT_DURATION:
        tmp << "duration";
        break;
    case STAT_STRING:
        tmp << "string";
        break;
    default:
        tmp << "unknown";
        break;
    }
    tmp << "(" << type << ")";
    return (tmp.str());
}

isc::data::ConstElementPtr
Observation::getJSON() const {

    ElementPtr list = isc::data::Element::createList(); // multiple observations
    ElementPtr entry;
    ElementPtr value;
    ElementPtr timestamp;

    // Support for retrieving more than one sample
    // retrieving all samples of indicated observation
    switch (type_) {
    case STAT_INTEGER: {
        std::list<IntegerSample> s = getIntegers(); // List of all integer samples

        // Iteration over all elements in the list
        // and adding alternately value and timestamp to the entry
        for (std::list<IntegerSample>::iterator it = s.begin(); it != s.end(); ++it) {
            entry = isc::data::Element::createList();
            value = isc::data::Element::create(static_cast<int64_t>((*it).first));
            timestamp = isc::data::Element::create(isc::util::ptimeToText((*it).second));

            entry->add(value);
            entry->add(timestamp);

            list->add(entry);
        }
        break;
    }
    case STAT_FLOAT: {
        std::list<FloatSample> s = getFloats();

        // Iteration over all elements in the list
        // and adding alternately value and timestamp to the entry
        for (std::list<FloatSample>::iterator it = s.begin(); it != s.end(); ++it) {
            entry = isc::data::Element::createList();
            value = isc::data::Element::create((*it).first);
            timestamp = isc::data::Element::create(isc::util::ptimeToText((*it).second));

            entry->add(value);
            entry->add(timestamp);

            list->add(entry);
        }
        break;
    }
    case STAT_DURATION: {
        std::list<DurationSample> s = getDurations();

        // Iteration over all elements in the list
        // and adding alternately value and timestamp to the entry
        for (std::list<DurationSample>::iterator it = s.begin(); it != s.end(); ++it) {
            entry = isc::data::Element::createList();
            value = isc::data::Element::create(isc::util::durationToText((*it).first));
            timestamp = isc::data::Element::create(isc::util::ptimeToText((*it).second));

            entry->add(value);
            entry->add(timestamp);

            list->add(entry);
        }
        break;
    }
    case STAT_STRING: {
        std::list<StringSample> s = getStrings();

        // Iteration over all elements in the list
        // and adding alternately value and timestamp to the entry
        for (std::list<StringSample>::iterator it = s.begin(); it != s.end(); ++it) {
            entry = isc::data::Element::createList();
            value = isc::data::Element::create((*it).first);
            timestamp = isc::data::Element::create(isc::util::ptimeToText((*it).second));

            entry->add(value);
            entry->add(timestamp);

            list->add(entry);
        }
        break;
    }
    default:
        isc_throw(InvalidStatType, "Unknown statistic type: "
                  << typeToText(type_));
    };

    return (list);
}

void Observation::reset() {
    switch(type_) {
    case STAT_INTEGER: {
        integer_samples_.clear();
        setValue(static_cast<int64_t>(0));
        return;
    }
    case STAT_FLOAT: {
        float_samples_.clear();
        setValue(0.0);
        return;
    }
    case STAT_DURATION: {
        duration_samples_.clear();
        setValue(time_duration(0, 0, 0, 0));
        return;
    }
    case STAT_STRING: {
        string_samples_.clear();
        setValue(string(""));
        return;
    }
    default:
        isc_throw(InvalidStatType, "Unknown statistic type: "
                  << typeToText(type_));
    };
}

};
};
