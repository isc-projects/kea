// Copyright (C) 2013,2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/option_string.h>
#include <sstream>

namespace isc {
namespace dhcp {

OptionString::OptionString(const Option::Universe u, const uint16_t type,
                           const std::string& value)
    : Option(u, type) {
    // Try to assign the provided string value. This will throw exception
    // if the provided value is empty.
    setValue(value);
}

OptionString::OptionString(const Option::Universe u, const uint16_t type,
                           OptionBufferConstIter begin,
                           OptionBufferConstIter end)
    : Option(u, type) {
    // Decode the data. This will throw exception if the buffer is
    // truncated.
    unpack(begin, end);
}

std::string
OptionString::getValue() const {
    const OptionBuffer& data = getData();
    return (std::string(data.begin(), data.end()));
}

void
OptionString::setValue(const std::string& value) {
    // Sanity check that the string value is at least one byte long.
    // This is a requirement for all currently defined options which
    // carry a string value.
    if (value.empty()) {
        isc_throw(isc::OutOfRange, "string value carried by the option '"
                  << getType() << "' must not be empty");
    }

    setData(value.begin(), value.end());
}


uint16_t
OptionString::len() {
    return (getHeaderLen() + getData().size());
}

void
OptionString::pack(isc::util::OutputBuffer& buf) {
    // Pack option header.
    packHeader(buf);
    // Pack data.
    const OptionBuffer& data = getData();
    buf.writeData(&data[0], data.size());

    // That's it. We don't pack any sub-options here, because this option
    // must not contain sub-options.
}

void
OptionString::unpack(OptionBufferConstIter begin,
                     OptionBufferConstIter end) {
    if (std::distance(begin, end) == 0) {
        isc_throw(isc::OutOfRange, "failed to parse an option '"
                  << getType() << "' holding string value"
                  << " - empty value is not accepted");
    }
    setData(begin, end);
}

std::string
OptionString::toText(int indent) {
    std::ostringstream output;
    output << headerToText(indent) << ": "
           << "\"" << getValue() << "\" (string)";

    return (output.str());
}

} // end of isc::dhcp namespace
} // end of isc namespace
