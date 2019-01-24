// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/stamped_value.h>
#include <exceptions/exceptions.h>
#include <boost/lexical_cast.hpp>

namespace isc {
namespace data {

StampedValue::StampedValue(const std::string& name,
                           const std::string& value)
    : StampedElement(), name_(name), value_(value) {
}

StampedValue::StampedValue(const std::string& name,
                           const int64_t value)
    : StampedElement(), name_(name), value_() {

    try {
        value_ = boost::lexical_cast<std::string>(value);
    } catch (...) {
        isc_throw(BadValue, "unable to cast value " << value
                  << " to a string");
    }
}

StampedValuePtr
StampedValue::create(const std::string& name,
                     const std::string& value) {
    return (StampedValuePtr(new StampedValue(name, value)));
}

StampedValuePtr
StampedValue::create(const std::string& name,
                     const int64_t value) {
    return (StampedValuePtr(new StampedValue(name, value)));
}


int64_t
StampedValue::getSignedIntegerValue() const {
    if (!value_.empty()) {
        try {
            return (boost::lexical_cast<int64_t>(value_));
        } catch (...) {
            isc_throw(BadValue, "unable to cast value " << value_
                      << " to a signed integer");
        }
    }

    return (0);
}

ElementPtr
StampedValue::toElement(Element::types elem_type) {
    ElementPtr element;
    switch(elem_type) {
    case Element::string: {
        element.reset(new StringElement(value_));
        break;
    }
    case Element::integer: {
        try {
            int int_value = boost::lexical_cast<int>(value_);
            element.reset(new IntElement(int_value));
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "StampedValue::toElement:  integer value expected for: "
                                 << name_ << ", value is: " << value_ );
        }
        break;
    }
    case Element::boolean: {
        bool bool_value;
        if (value_ == std::string("true")) {
            bool_value = true;
        } else if (value_ == std::string("false")) {
            bool_value = false;
        } else {
            isc_throw(BadValue, "StampedValue::toElement: boolean value specified as "
                      << name_ << ", value is: " << value_
                      << ", expected true or false");
        }

        element.reset(new BoolElement(bool_value));
        break;
    }
    case Element::real: {
        try {
            double dbl_value = boost::lexical_cast<double>(value_);
            element.reset(new DoubleElement(dbl_value));
        }
        catch (const std::exception& ex) {
            isc_throw(BadValue, "StampedValue::toElement: real number value expected for: "
                      << name_ << ", value is: " << value_ );
        }

    break;
    }
    default:
        isc_throw (BadValue, "StampedValue::toElement: unsupported element type "
                   << elem_type << " for: " << name_);
        break;
    }

    return (element);
}

} // end of namespace isc::data
} // end of namespace isc
