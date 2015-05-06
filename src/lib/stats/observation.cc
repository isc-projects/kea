
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stats/observation.h>
#include <cc/data.h>
#include <utility>

using namespace std;
using namespace isc::data;
using namespace boost::posix_time;

namespace isc {
namespace stats {

Observation::Observation(uint64_t value)
    :type_(STAT_INTEGER), max_samples_(1) {
    setValue(value);
}

Observation::Observation(double value)
    :type_(STAT_FLOAT), max_samples_(1) {
    setValue(value);
}

Observation::Observation(StatsDuration value)
    :type_(STAT_DURATION), max_samples_(1) {
    setValue(value);
}

Observation::Observation(const std::string& value)
    :type_(STAT_STRING), max_samples_(1) {
    setValue(value);
}

void Observation::addValue(uint64_t value) {
    IntegerSample current = getInteger();
    setValue(current.first + value);
}

void Observation::addValue(double value) {
    FloatSample current = getFloat();
    setValue(current.first + value);
}

void Observation::addValue(StatsDuration value) {
    DurationSample current = getDuration();
    setValue(current.first + value);
}

void Observation::addValue(const std::string& value) {
    StringSample current = getString();
    setValue(current.first + value);
}

void Observation::setValue(uint64_t value) {
    setValueInternal(value, integer_samples_, STAT_INTEGER);
}

void Observation::setValue(double value) {
    setValueInternal(value, float_samples_, STAT_FLOAT);
}

void Observation::setValue(StatsDuration value) {
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

IntegerSample Observation::getInteger() {
    return (getValueInternal<IntegerSample>(integer_samples_, STAT_INTEGER));
}

FloatSample Observation::getFloat() {
    return (getValueInternal<FloatSample>(float_samples_, STAT_FLOAT));
}

DurationSample Observation::getDuration() {
    return (getValueInternal<DurationSample>(duration_samples_, STAT_DURATION));
}

StringSample Observation::getString() {
    return (getValueInternal<StringSample>(string_samples_, STAT_STRING));
}

template<typename SampleType, typename Storage>
SampleType Observation::getValueInternal(Storage& storage, Type exp_type) {
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

std::string
Observation::ptimeToText(ptime t) {

    // The alternative would be to call to_simple_string(ptime), but unfortunately
    // that requires linking with boost libraries.

    return (to_simple_string(t));
}

std::string
Observation::durationToText(StatsDuration dur) {
    return (to_simple_string(dur));
}

isc::data::ConstElementPtr
Observation::getJSON() {

    ElementPtr list = isc::data::Element::createList();
    ElementPtr value;
    ElementPtr timestamp;

    switch (type_) {
    case STAT_INTEGER: {
        IntegerSample s = getInteger();
        value = isc::data::Element::create(static_cast<int64_t>(s.first));
        timestamp = isc::data::Element::create(ptimeToText(s.second));
        break;
    }
    case STAT_FLOAT: {
        FloatSample s = getFloat();
        value = isc::data::Element::create(s.first);
        timestamp = isc::data::Element::create(ptimeToText(s.second));
        break;
    }
    case STAT_DURATION: {
        DurationSample s = getDuration();
        value = isc::data::Element::create(durationToText(s.first));
        timestamp = isc::data::Element::create(ptimeToText(s.second));
        break;
    }
    case STAT_STRING: {
        StringSample s = getString();
        value = isc::data::Element::create(s.first);
        timestamp = isc::data::Element::create(ptimeToText(s.second));
        break;
    }
    default:
        isc_throw(InvalidStatType, "Unknown stat type: " << typeToText(type_));
    };

    list->add(value);
    list->add(timestamp);

    return (list);
}

void Observation::reset() {
    switch(type_) {
    case STAT_INTEGER: {
        setValue(static_cast<uint64_t>(0));
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
        isc_throw(InvalidStatType, "Unknown stat type: " << typeToText(type_));
    };
}

};
};
