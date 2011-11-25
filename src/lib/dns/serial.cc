// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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
        result = ((other_val - value_) <= MAX_INCREMENT);
    } else if (other_val < value_) {
        result = ((value_ - other_val) > MAX_INCREMENT);
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
    return (operator==(other) || !operator>(other));
}

Serial
Serial::operator+(uint32_t other_val) const {
    if (value_ <= MAX_INCREMENT) {
        // just add
        return (Serial(value_ + other_val));
    } else {
        // check whether it wouldn't wrap
        // Note the +1 here and the -2 below, these operations use
        // the MAX_INCREMENT constant, which is 2^31-1, while it really
        // needs 2^31 itself.
        if (value_ - MAX_INCREMENT + other_val <= MAX_INCREMENT + 1) {
            return (Serial(value_ + other_val));
        } else {
            return (Serial(value_ - MAX_INCREMENT + 
                           other_val - MAX_INCREMENT - 2));
        }
    }
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

