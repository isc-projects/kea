// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <d2/labeled_value.h>

namespace isc {
namespace d2 {

/**************************** LabeledValue ****************************/

LabeledValue::LabeledValue(const int value, const std::string& label)
    : value_(value), label_(label) {
    if (label.empty()) {
        isc_throw(LabeledValueError, "labels cannot be empty");
    }
}

LabeledValue::~LabeledValue(){
}

int
LabeledValue::getValue() const {
    return (value_);
}

std::string
LabeledValue::getLabel() const {
    return (label_);
}

bool
LabeledValue::operator==(const LabeledValue& other) const {
    return (this->value_ == other.value_);
}

bool
LabeledValue::operator!=(const LabeledValue& other) const {
    return (this->value_ != other.value_);
}

bool
LabeledValue::operator<(const LabeledValue& other) const {
    return (this->value_ < other.value_);
}

std::ostream& operator<<(std::ostream& os, const LabeledValue& vlp) {
    os << vlp.getLabel();
    return (os);
}

/**************************** LabeledValueSet ****************************/

const char* LabeledValueSet::UNDEFINED_LABEL = "UNDEFINED";

LabeledValueSet::LabeledValueSet(){
}

LabeledValueSet::~LabeledValueSet() {
}

void
LabeledValueSet::add(LabeledValuePtr entry) {
    if (!entry) {
        isc_throw(LabeledValueError, "cannot add an null entry to set");
    }

    const int value = entry->getValue();
    if (isDefined(value)) {
        isc_throw(LabeledValueError,
                  "value: " << value << " is already defined as: "
                  << getLabel(value));
        }

    map_[entry->getValue()]=entry;
}

void
LabeledValueSet::add(const int value, const std::string& label) {
    add (LabeledValuePtr(new LabeledValue(value,label)));
}

const LabeledValuePtr&
LabeledValueSet::get(int value) {
    static LabeledValuePtr undefined;
    LabeledValueMap::iterator it = map_.find(value);
    if (it != map_.end()) {
        return ((*it).second);
    }

    // Return an empty pointer when not found.
    return (undefined);
}

bool
LabeledValueSet::isDefined(const int value) const {
    LabeledValueMap::const_iterator it = map_.find(value);
    return (it != map_.end());
}

std::string
LabeledValueSet::getLabel(const int value) const {
    LabeledValueMap::const_iterator it = map_.find(value);
    if (it != map_.end()) {
        const LabeledValuePtr& ptr = (*it).second;
        return (ptr->getLabel());
    }

    return (std::string(UNDEFINED_LABEL));
}

} // namespace isc::d2
} // namespace isc
