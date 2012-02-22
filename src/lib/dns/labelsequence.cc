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

/// Light-weight Accessor to Name object
///
/// The purpose of this class is to easily match Names and parts of Names,
/// without needing to copy the underlying data on each split.
///
/// It can only work on existing Name objects, and the Name object MUST
/// remain in scope during the entire lifetime of its associated
/// LabelSequence(s)
///
/// Upon creation of a LabelSequence, it records the offsets of the
/// labels in the wireformat data of the Name. When split() is called on
/// the LabelSequence, no changes in the Name's data occur, but the
/// internal pointers of the LabelSequence are modified.
///
/// LabelSequences can be compared to other LabelSequences, and their
/// data can be requested (which then points to part of the original
/// data of the associated Name object).
///

namespace isc {
namespace dns {

/// \brief Constructs a LabelSequence for the given name
///
/// The associated Name MUST remain in scope during the lifetime of
/// this LabelSequence, since getData() refers to data from the
/// Name object (the only data the LabelSequence stores are pointers
/// to the labels in the Name object).
LabelSequence::LabelSequence(const Name& name) : name_(name),
                             first_label_(0) {
    size_t label_count_ = name.getLabelCount();
    last_label_ = label_count_ - 1;
    offsets_ = new size_t[label_count_];
    offsets_[0] = 0;
    for (size_t i = 1; i < label_count_; ++i) {
        offsets_[i] = offsets_[i - 1] + name.at(offsets_[i - 1]) + 1;
    }
}

LabelSequence::~LabelSequence() {
    delete[] offsets_;
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
    if (i > 0) {
        if (i > getLabelCount()) {
            isc_throw(OutOfRange, "Label " << i << " out of range (" <<
                                  getLabelCount() << ")");
        } else {
            first_label_ += i;
        }
    } else if (i < 0) {
        if (-i > getLabelCount()) {
            isc_throw(OutOfRange, "Label " << i << " out of range (" <<
                                  getLabelCount() << ")");
        } else {
            last_label_ += i;
        }
    }
}

} // end namespace dns
} // end namespace isc

