// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd_option.h>
#include <exceptions/exceptions.h>
#include <util/encode/hex.h>
#include <util/io_utilities.h>

#include <iomanip>
#include <list>
#include <sstream>

#include <stdint.h>
#include <string.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace slaac {

Option::Option(uint8_t type)
    : type_(type) {
}

Option::Option(uint8_t type, const OptionBuffer& data)
    : type_(type), data_(data) {
    check();
}

Option::Option(uint8_t type, OptionBufferConstIter first,
               OptionBufferConstIter last)
    : type_(type), data_(first, last) {
    check();
}

Option::Option(const Option& option)
    : type_(option.type_), data_(option.data_) {
}

Option&
Option::operator=(const Option& rhs) {
    if (&rhs != this) {
        type_ = rhs.type_;
        data_ = rhs.data_;
    }
    return (*this);
}

void
Option::check() const {
    size_t length = getHeaderLen() + data_.size();
    if (length == 0) {
        isc_throw(OutOfRange, "empty ND option");
    }
    if (length > 255) {
        isc_throw(OutOfRange, "too large ND option: " << length);
    }
    if ((length & 7) != 0) {
        isc_throw(BadValue, "length is not a multiple of 8: " << length);
    }
}

void Option::pack(isc::util::OutputBuffer& buf) const {
    // Avoid malformed options.
    check();
    // Write a header.
    packHeader(buf);
    // Write data.
    if (!data_.empty()) {
        buf.writeData(&data_[0], data_.size());
    }
}

void
Option::packHeader(isc::util::OutputBuffer& buf) const {
    buf.writeUint8(type_);
    buf.writeUint8(len() >> 3);
}

void Option::unpack(OptionBufferConstIter begin,
                    OptionBufferConstIter end) {
    setData(begin, end);
}

size_t Option::len() const {
    // Returns length of the complete option.

    // length of the whole option is header and data stored in this option...
    return (getHeaderLen() + data_.size());
}

bool
Option::valid() const {
    return (true);
}

string Option::toText(int indent) const {
    stringstream output;
    output << headerToText(indent) << ": ";

    for (unsigned int i = 0; i < data_.size(); i++) {
        if (i) {
            output << ":";
        }
        output << setfill('0') << setw(2) << hex
            << static_cast<unsigned short>(data_[i]);
    }

    return (output.str());
}

vector<uint8_t>
Option::toBinary(const bool include_header) const {
    OutputBuffer buf(len());
    try {
        // If the option is too long, exception will be thrown. We allow
        // for this exception to propagate to not mask this error.
        pack(buf);

    } catch (const std::exception &ex) {
        isc_throw(OutOfRange, "unable to obtain hexadecimal representation"
                  " of option " << getType() << ": " << ex.what());
    }
    const uint8_t* option_data = static_cast<const uint8_t*>(buf.getData());

    // Assign option data to a vector, with or without option header depending
    // on the value of "include_header" flag.
    vector<uint8_t> option_vec(option_data +
                               (include_header ? 0 : getHeaderLen()),
                               option_data + buf.getLength());
    return (option_vec);
}

string
Option::toHexString(const bool include_header) const {
    // Prepare binary version of the option.
    vector<uint8_t> option_vec = toBinary(include_header);

    // Return hexadecimal representation prepended with 0x or empty string
    // if option has no payload and the header fields are excluded.
    ostringstream s;
    if (!option_vec.empty()) {
        s << "0x" << encode::encodeHex(option_vec);
    }
    return (s.str());
}

string
Option::headerToText(const int indent, const string& type_name) const {
    stringstream output;
    for (int i = 0; i < indent; i++)
        output << " ";

    output << "type=" << setw(3) << setfill('0') << type_;

    if (!type_name.empty()) {
        output << "(" << type_name << ")";
    }

    output << ", len=" << setw(5) << setfill('0') << len();
    return (output.str());
}

size_t
Option::getHeaderLen() const {
    return OPTION_HDR_LEN; // header length for ND
}

uint8_t Option::getUint8() const {
    if (data_.size() < sizeof(uint8_t)) {
        isc_throw(OutOfRange, "Attempt to read uint8 from option " << type_
                  << " that has size " << data_.size());
    }
    return (data_[0]);
}

uint16_t Option::getUint16() const {
    // readUint16() checks and throws OutOfRange if data_ is too small.
    return (readUint16(&data_[0], data_.size()));
}

uint32_t Option::getUint32() const {
    // readUint32() checks and throws OutOfRange if data_ is too small.
    return (readUint32(&data_[0], data_.size()));
}

void Option::setUint8(uint8_t value) {
    data_.resize(sizeof(value));
    data_[0] = value;
}

void Option::setUint16(uint16_t value) {
    data_.resize(sizeof(value));
    writeUint16(value, &data_[0], data_.size());
}

void Option::setUint32(uint32_t value) {
    data_.resize(sizeof(value));
    writeUint32(value, &data_[0], data_.size());
}

bool Option::equals(const OptionPtr& other) const {
    return (equals(*other));
}

bool Option::equals(const Option& other) const {
    return ( (getType() == other.getType()) &&
             (getData() == other.getData()) );
}

Option::~Option() {

}

} // end of isc::slaac namespace
} // end of isc namespace
