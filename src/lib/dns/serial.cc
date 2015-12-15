// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/serial.h>

namespace isc {
namespace dns {

bool
Serial::operator==(const Serial& other) const {
    return (value_ == other.getValue());
}

bool
Serial::operator!=(const Serial& other) const {
    return (value_ != other.getValue());
}

bool
Serial::operator<(const Serial& other) const {
    uint32_t other_val = other.getValue();
    bool result = false;
    if (value_ < other_val) {
        result = ((other_val - value_) <= MAX_SERIAL_INCREMENT);
    } else if (other_val < value_) {
        result = ((value_ - other_val) > MAX_SERIAL_INCREMENT);
    }
    return (result);
}

bool
Serial::operator<=(const Serial& other) const {
    return (operator==(other) || operator<(other));
}

bool
Serial::operator>(const Serial& other) const {
    return (!operator==(other) && !operator<(other));
}

bool
Serial::operator>=(const Serial& other) const {
    return (!operator<(other));
}

Serial
Serial::operator+(uint32_t other_val) const {
    uint64_t new_val = static_cast<uint64_t>(value_) +
                       static_cast<uint64_t>(other_val);
    return Serial(static_cast<uint32_t>(new_val % MAX_SERIAL_VALUE));
}

Serial
Serial::operator+(const Serial& other) const {
    return (operator+(other.getValue()));
}

std::ostream&
operator<<(std::ostream& os, const Serial& serial) {
    return (os << serial.getValue());
}

} // end namespace dns
} // end namespace isc

