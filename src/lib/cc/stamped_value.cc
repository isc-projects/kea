// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/stamped_value.h>
#include <exceptions/exceptions.h>
#include <boost/lexical_cast.hpp>

namespace isc {
namespace data {

StampedValue::StampedValue(const std::string& value)
    : StampedElement(), value_(value) {
}

StampedValue::StampedValue(const int64_t value)
    : StampedElement(), value_() {
    try {
        value_ = boost::lexical_cast<std::string>(value);
    } catch (...) {
        isc_throw(BadValue, "unable to cast value " << value
                  << " to a string");
    }
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

} // end of namespace isc::data
} // end of namespace isc
