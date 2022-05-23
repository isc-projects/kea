// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option_string.h>
#include <util/strutil.h>
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

OptionPtr
OptionString::clone() const {
    return (cloneInternal<OptionString>());
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

    // Trim off any trailing nuls.
    auto begin = value.begin();
    auto end = util::str::seekTrimmed(begin, value.end(), 0x0);

    if (std::distance(begin, end) == 0) {
        isc_throw(isc::OutOfRange, "string value carried by the option '"
                  << getType() << "' contained only nuls");
    }

    // Now set the value.
    setData(begin, end);
}


uint16_t
OptionString::len() const {
    return (getHeaderLen() + getData().size());
}

void
OptionString::pack(isc::util::OutputBuffer& buf, bool check) const {
    // Pack option header.
    packHeader(buf, check);
    // Pack data.
    const OptionBuffer& data = getData();
    buf.writeData(&data[0], data.size());

    // That's it. We don't pack any sub-options here, because this option
    // must not contain sub-options.
}

void
OptionString::unpack(OptionBufferConstIter begin,
                     OptionBufferConstIter end) {
    // Trim off trailing nul(s)
    end = util::str::seekTrimmed(begin, end, 0x0);
    if (std::distance(begin, end) == 0) {
        isc_throw(isc::dhcp::SkipThisOptionError, "failed to parse an option '"
                  << getType() << "' holding string value"
                  << "' was empty or contained only nuls");
    }

    // Now set the data.
    setData(begin, end);
}

std::string
OptionString::toText(int indent) const {
    std::ostringstream output;
    output << headerToText(indent) << ": "
           << "\"" << getValue() << "\" (string)";

    return (output.str());
}

std::string
OptionString::toString() const {
    return (getValue());
}

} // end of isc::dhcp namespace
} // end of isc namespace
