// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#define KEA_DHCP_EXPORT

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
    if (getLength() == 0) {
        isc_throw(OpaqueDataTupleError, "failed to create on-wire format of the"
                  " opaque data field, because the field appears to be empty");
    } else if ((1 << (getDataFieldSize() * 8)) <= getLength()) {
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

    buf.writeData(&getData()[0], getLength());
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

KEA_DHCP_API
std::ostream& operator<<(std::ostream& os, const OpaqueDataTuple& tuple) {
    os << tuple.getText();
    return (os);
}

KEA_DHCP_API
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

}
}
