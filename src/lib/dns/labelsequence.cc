// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/labelsequence.h>
#include <exceptions/exceptions.h>

#include <iostream>
namespace isc {
namespace dns {

LabelSequence::LabelSequence(const Name& name) : name_(name),
                             first_label_(0), offsets_(name.getLabelCount()) {
    offsets_[0] = 0;
    last_label_ = name.getLabelCount() - 1;
    // Walk through the wire format data and store all offsets
    for (size_t i = 1; i < offsets_.size(); ++i) {
        // Each offset is the previous offset plus the length of the
        // label plus 1 (for the label length octet)
        offsets_[i] = offsets_[i - 1] + name.at(offsets_[i - 1]) + 1;
    }
}

const char*
LabelSequence::getData(size_t *len) const {
    *len = offsets_[last_label_] - offsets_[first_label_];
    return (name_.at_p(offsets_[first_label_]));
}

bool
LabelSequence::equals(const LabelSequence& other, bool case_sensitive) const {
    size_t len, other_len;
    const char* data = getData(&len);
    const char* other_data = other.getData(&other_len);

    if (len != other_len) {
        return (false);
    }
    if (case_sensitive) {
        return (strncasecmp(data, other_data, len) == 0);
    } else {
        return (strncmp(data, other_data, len) == 0);
    }
}

void
LabelSequence::split(int i) {
    if (abs(i) > getLabelCount()) {
        isc_throw(OutOfRange, "Label " << i << " out of range (" <<
                              getLabelCount() << ")");
    }
    if (i > 0) {
        first_label_ += i;
    } else if (i < 0) {
        last_label_ += i;
    }
}

} // end namespace dns
} // end namespace isc

