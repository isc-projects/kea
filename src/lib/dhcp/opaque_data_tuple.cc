// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/opaque_data_tuple.h>

namespace isc {
namespace dhcp {

OpaqueDataTuple::OpaqueDataTuple(LengthFieldType length_field_type)
    : length_field_type_(length_field_type) {
}

void
OpaqueDataTuple::append(const std::string& text) {
    // Don't do anything if text is empty.
    if (!text.empty()) {
        append(&text[0], text.size());
    }
}

void
OpaqueDataTuple::assign(const std::string& text) {
    // If empty string is being assigned, reset the buffer.
    if (text.empty()) {
        clear();
    } else {
        assign(&text[0], text.size());
    }
}

void
OpaqueDataTuple::clear() {
    data_.clear();
}

bool
OpaqueDataTuple::equals(const std::string& other) const {
    return (getText() == other);
}

std::string
OpaqueDataTuple::getText() const {
    // Convert the data carried in the buffer to a string.
    return (std::string(data_.begin(), data_.end()));
}

void
OpaqueDataTuple::pack(isc::util::OutputBuffer& buf) const {
    if ((1 << (getDataFieldSize() * 8)) <= getLength()) {
        isc_throw(OpaqueDataTupleError, "failed to create on-wire format of the"
                  " opaque data field, because current data length "
                  << getLength() << " exceeds the maximum size for the length"
                  << " field size " << getDataFieldSize());
    }

    if (getDataFieldSize() == 1) {
        buf.writeUint8(static_cast<uint8_t>(getLength()));
    } else {
        buf.writeUint16(getLength());
    }

    if (getLength() > 0) {
        buf.writeData(&getData()[0], getLength());
    }
}

int
OpaqueDataTuple::getDataFieldSize() const {
    return (length_field_type_ == LENGTH_1_BYTE ? 1 : 2);
}

OpaqueDataTuple&
OpaqueDataTuple::operator=(const std::string& other) {
    // Replace existing data with the new data converted from a string.
    assign(&other[0], other.length());
    return (*this);
}

bool
OpaqueDataTuple::operator==(const std::string& other) const {
    return (equals(other));
}

bool
OpaqueDataTuple::operator!=(const std::string& other) {
    return (!equals(other));
}

std::ostream& operator<<(std::ostream& os, const OpaqueDataTuple& tuple) {
    os << tuple.getText();
    return (os);
}

std::istream& operator>>(std::istream& is, OpaqueDataTuple& tuple) {
    // We will replace the current data with new data.
    tuple.clear();
    char buf[256];
    // Read chunks of data as long as we haven't reached the end of the stream.
    while (!is.eof()) {
        is.read(buf, sizeof(buf));
        // Append the chunk of data we have just read. It is fine if the
        // gcount is 0, because append() function will check that.
        tuple.append(buf, is.gcount());
    }
    // Clear eof flag, so as the stream can be read again.
    is.clear();
    return (is);
}

void
OpaqueDataTuple::unpack(OpaqueDataTuple::InputIterator begin, OpaqueDataTuple::InputIterator end) {
    // The buffer must at least hold the size of the data.
    if (std::distance(begin, end) < getDataFieldSize()) {
        isc_throw(OpaqueDataTupleError,
                    "unable to parse the opaque data tuple, the buffer"
                    " length is " << std::distance(begin, end)
                    << ", expected at least " << getDataFieldSize());
    }
    // Read the data length from the length field, depending on the
    // size of the data field (1 or 2 bytes).
    size_t len = getDataFieldSize() == 1 ? *begin :
        isc::util::readUint16(&(*begin), std::distance(begin, end));
    // Now that we have the expected data size, let's check that the
    // reminder of the buffer is long enough.
    begin += getDataFieldSize();
    // Attempt to parse as a length-value pair.
    if (std::distance(begin, end) < len) {
        if (Option::lenient_parsing_) {
            // Fallback to parsing the rest of the option as a single value.
            len = std::distance(begin, end);
        } else {
            isc_throw(OpaqueDataTupleError,
                        "unable to parse the opaque data tuple, "
                        "the buffer length is " << std::distance(begin, end)
                        << ", but the tuple length is " << len);
        }
    }
    // The buffer length is long enough to read the desired amount of data.
    assign(begin, len);
}

}  // namespace dhcp
}  // namespace isc
