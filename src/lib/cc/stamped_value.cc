// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/stamped_value.h>
#include <exceptions/exceptions.h>
#include <boost/lexical_cast.hpp>

namespace isc {
namespace data {

StampedValue::StampedValue(const std::string& name)
    : StampedElement(), name_(name), value_() {
}

StampedValue::StampedValue(const std::string& name, const ElementPtr& value)
    : StampedElement(), name_(name), value_(value) {
    validateConstruct();
}

StampedValue::StampedValue(const std::string& name, const std::string& value)
    : StampedElement(), name_(name), value_(Element::create(value)) {
    validateConstruct();
}

StampedValuePtr
StampedValue::create(const std::string& name) {
    return (StampedValuePtr(new StampedValue(name)));
}

StampedValuePtr
StampedValue::create(const std::string& name, const ElementPtr& value) {
    return (StampedValuePtr(new StampedValue(name, value)));
}

StampedValuePtr
StampedValue::create(const std::string& name, const std::string& value) {
    return (StampedValuePtr(new StampedValue(name, value)));
}

StampedValuePtr
StampedValue::create(const std::string& name, const std::string& value,
                     Element::types parameter_type) {
    StampedValuePtr stamped_value;

    try {
        switch (parameter_type) {
        case Element::string:
            stamped_value = StampedValue::create(name, value);
            break;

        case Element::integer:
            stamped_value = StampedValue::create(name,
                Element::create(boost::lexical_cast<int64_t>(value)));
            break;

        case Element::boolean:
            // We only allow "1" and "0" as input to this function.
            if ((value != "0") && (value != "1")) {
                isc_throw(BadValue, "StampedValue: invalid value " << value
                          << " specified as boolean. Expected \"0\" or \"1\"");
            }
            stamped_value = StampedValue::create(name,
                Element::create((value == "0") ? false : true));
            break;

        case Element::real:
            stamped_value = StampedValue::create(name,
                Element::create(boost::lexical_cast<double>(value)));
            break;

        default:
            // Invalid data type provided as argument.
            isc_throw(TypeError, "StampedValue: unsupported type '"
                      << Element::typeToName(parameter_type)
                      << " of the parameter '" << name);
        }

    } catch (const boost::bad_lexical_cast& ex) {
        // Failed to cast the value to a given type.
        isc_throw(BadValue, "StampedValue: the value of the parameter '"
                  << Element::typeToName(parameter_type)
                  << "' can't be converted to "
                  << Element::typeToName(parameter_type)
                  << " type");
    }

    return (stamped_value);
}

int
StampedValue::getType() const {
    if (!value_) {
        isc_throw(InvalidOperation, "StampedValue: attempt to retrieve the "
                  "type of the null value for the '" << name_
                  << "' parameter");
    }

    return (value_->getType());
}

std::string
StampedValue::getValue() const {
    validateAccess(Element::string);

    try {
        switch (static_cast<Element::types>(value_->getType())) {
        case Element::string:
            return (value_->stringValue());
        case Element::integer:
            return (boost::lexical_cast<std::string>(value_->intValue()));
        case Element::boolean:
            return (value_->boolValue() ? "1" : "0");
        case Element::real:
            {
                std::string repr =
                    boost::lexical_cast<std::string>(value_->doubleValue());
                if (repr.find_first_of('.') == std::string::npos) {
                    repr += ".0";
                }
                return (repr);
            }
        default:
            // Impossible condition.
            isc_throw(TypeError, "StampedValue: invalid type of the '"
                      << name_ << "' parameter");
        }

    } catch (const boost::bad_lexical_cast& ex) {
        isc_throw(BadValue, "StampedValue: unable to convert the value of "
                  "the parameter '" << name_ << "' to string");
    }
    // unreachable
    return (value_->stringValue());
}

int64_t
StampedValue::getIntegerValue() const {
    validateAccess(Element::integer);
    return (value_->intValue());
}

bool
StampedValue::getBoolValue() const {
    validateAccess(Element::boolean);
    return (value_->boolValue());
}

double
StampedValue::getDoubleValue() const {
    validateAccess(Element::real);
    return (value_->doubleValue());
}

void
StampedValue::validateConstruct() const {
    if (!value_) {
        isc_throw(BadValue, "StampedValue: provided value of the '"
                  << name_ << "' parameter is NULL");
    }

    if ((value_->getType() != Element::string) &&
        (value_->getType() != Element::integer) &&
        (value_->getType() != Element::boolean) &&
        (value_->getType() != Element::real)) {
        isc_throw(TypeError, "StampedValue: provided value of the '"
                  << name_ << "' parameter has invalid type: "
                  << Element::typeToName(static_cast<Element::types>(value_->getType())));
    }
}

void
StampedValue::validateAccess(Element::types type) const {
    if (!value_) {
        isc_throw(InvalidOperation, "StampedValue: attempt to get null value "
                  "of the '" << name_ << "' parameter");
    }

    if ((type != Element::string) && (type != value_->getType())) {
        isc_throw(TypeError, "StampedValue: attempt to access a '"
                  << name_ << "' parameter as " << Element::typeToName(type)
                  << ", but this parameter has "
                  << Element::typeToName(static_cast<Element::types>(value_->getType()))
                  << " type");
    }
}

} // end of namespace isc::data
} // end of namespace isc
