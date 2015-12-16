// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

Observation::Observation(const std::string& name, const int64_t value)
    :name_(name), type_(STAT_INTEGER) {
    setValue(value);
}

Observation::Observation(const std::string& name, const double value)
    :name_(name), type_(STAT_FLOAT) {
    setValue(value);
}

Observation::Observation(const std::string& name, const StatsDuration& value)
    :name_(name), type_(STAT_DURATION) {
    setValue(value);
}

Observation::Observation(const std::string& name, const std::string& value)
    :name_(name), type_(STAT_STRING) {
    setValue(value);
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

template<typename SampleType, typename StorageType>
void Observation::setValueInternal(SampleType value, StorageType& storage,
    Type exp_type) {
    if (type_ != exp_type) {
        isc_throw(InvalidStatType, "Invalid statistic type requested: "
                  << typeToText(exp_type) << ", but the actual type is "
                  << typeToText(type_) );
    }

    if (storage.empty()) {
        storage.push_back(make_pair(value, microsec_clock::local_time()));
    } else {

        /// @todo: Update once more than one sample is supported
        *storage.begin() = make_pair(value, microsec_clock::local_time());
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
                  << typeToText(type_) );
    }

    if (storage.empty()) {
        // That should never happen. The first element is always initialized in
        // the constructor. reset() sets its value to zero, but the element should
        // still be there.
        isc_throw(Unexpected, "Observation storage container empty");
    }
    return (*storage.begin());
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

    ElementPtr entry = isc::data::Element::createList(); // a single observation
    ElementPtr value;
    ElementPtr timestamp;

    /// @todo: Add support for retrieving more than one sample for a given
    /// observation

    switch (type_) {
    case STAT_INTEGER: {
        IntegerSample s = getInteger();
        value = isc::data::Element::create(static_cast<int64_t>(s.first));
        timestamp = isc::data::Element::create(isc::util::ptimeToText(s.second));
        break;
    }
    case STAT_FLOAT: {
        FloatSample s = getFloat();
        value = isc::data::Element::create(s.first);
        timestamp = isc::data::Element::create(isc::util::ptimeToText(s.second));
        break;
    }
    case STAT_DURATION: {
        DurationSample s = getDuration();
        value = isc::data::Element::create(isc::util::durationToText(s.first));
        timestamp = isc::data::Element::create(isc::util::ptimeToText(s.second));
        break;
    }
    case STAT_STRING: {
        StringSample s = getString();
        value = isc::data::Element::create(s.first);
        timestamp = isc::data::Element::create(isc::util::ptimeToText(s.second));
        break;
    }
    default:
        isc_throw(InvalidStatType, "Unknown statistic type: "
                  << typeToText(type_));
    };

    entry->add(value);
    entry->add(timestamp);

    ElementPtr list = isc::data::Element::createList(); // a single observation
    list->add(entry);

    return (list);
}

void Observation::reset() {
    switch(type_) {
    case STAT_INTEGER: {
        setValue(static_cast<int64_t>(0));
        return;
    }
    case STAT_FLOAT: {
        setValue(0.0);
        return;
    }
    case STAT_DURATION: {
        setValue(time_duration(0,0,0,0));
        return;
    }
    case STAT_STRING: {
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
