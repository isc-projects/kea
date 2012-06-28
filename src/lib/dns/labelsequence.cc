// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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
#include <dns/name_internal.h>
#include <exceptions/exceptions.h>

#include <boost/functional/hash.hpp>

#include <cstring>

namespace isc {
namespace dns {

const uint8_t*
LabelSequence::getData(size_t *len) const {
    *len = getDataLength();
    return (&name_.ndata_[name_.offsets_[first_label_]]);
}

size_t
LabelSequence::getDataLength() const {
    // If the labelsequence is absolute, the current last_label_ falls
    // out of the vector (since it points to the 'label' after the
    // root label, which doesn't exist; in that case, return
    // the length for the 'previous' label (the root label) plus
    // one (for the root label zero octet)
    if (isAbsolute()) {
        return (name_.offsets_[last_label_ - 1] -
                name_.offsets_[first_label_] + 1);
    } else {
        return (name_.offsets_[last_label_] - name_.offsets_[first_label_]);
    }
}

bool
LabelSequence::equals(const LabelSequence& other, bool case_sensitive) const {
    size_t len, other_len;
    const uint8_t* data = getData(&len);
    const uint8_t* other_data = other.getData(&other_len);

    if (len != other_len) {
        return (false);
    }
    if (case_sensitive) {
        return (std::memcmp(data, other_data, len) == 0);
    }

    // As long as the data was originally validated as (part of) a name,
    // label length must never be a capital ascii character, so we can
    // simply compare them after converting to lower characters.
    for (size_t i = 0; i < len; ++i) {
        const uint8_t ch = data[i];
        const uint8_t other_ch = other_data[i];
        if (isc::dns::name::internal::maptolower[ch] !=
            isc::dns::name::internal::maptolower[other_ch]) {
            return (false);
        }
    }
    return (true);
}

void
LabelSequence::stripLeft(size_t i) {
    if (i >= getLabelCount()) {
        isc_throw(OutOfRange, "Cannot strip to zero or less labels; " << i <<
                              " (labelcount: " << getLabelCount() << ")");
    }
    first_label_ += i;
}

void
LabelSequence::stripRight(size_t i) {
    if (i >= getLabelCount()) {
        isc_throw(OutOfRange, "Cannot strip to zero or less labels; " << i <<
                              " (labelcount: " << getLabelCount() << ")");
    }
    last_label_ -= i;
}

bool
LabelSequence::isAbsolute() const {
    return (last_label_ == name_.offsets_.size());
}

size_t
LabelSequence::getHash(bool case_sensitive) const {
    size_t length;
    const uint8_t* s = getData(&length);
    if (length > 16) {
        length = 16;
    }

    size_t hash_val = 0;
    while (length > 0) {
        const uint8_t c = *s++;
        boost::hash_combine(hash_val, case_sensitive ? c :
                            isc::dns::name::internal::maptolower[c]);
        --length;
    }
    return (hash_val);
}

std::string
LabelSequence::toText() const {
    return (name_.toText(!isAbsolute(), first_label_, last_label_));
}

} // end namespace dns
} // end namespace isc
