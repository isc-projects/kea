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

#include <dhcp/option_string.h>

namespace isc {
namespace dhcp {

OptionString::OptionString(const Option::Universe u, const uint16_t type,
                           const std::string& value)
    : Option(u, type), value_(value) {
}

OptionString::OptionString(const Option::Universe u, const uint16_t type,
                           OptionBufferConstIter begin,
                           OptionBufferConstIter end)
    : Option(u, type) {
    // Decode the data. This will throw exception if the buffer is
    // truncated.
    unpack(begin, end);
}

uint16_t
OptionString::len() {
    return (getHeaderLen() + value_.size());
}

void
OptionString::pack(isc::util::OutputBuffer& buf) {
    // Sanity check that the string value is at least one byte long.
    // This is a requirement for all currently defined options which
    // carry a string value.
    if (value_.empty()) {
        isc_throw(isc::OutOfRange, "string value carried in the option"
                  << " must not be empty");
    }

    // Pack option header.
    packHeader(buf);
    // Pack data.
    buf.writeData(value_.c_str(), value_.size());

    // That's it. We don't pack any sub-options here, because this option
    // must not contain sub-options.
}

void
OptionString::unpack(OptionBufferConstIter/* begin */,
                     OptionBufferConstIter/* end*/) {
}

} // end of isc::dhcp namespace
} // end of isc namespace
