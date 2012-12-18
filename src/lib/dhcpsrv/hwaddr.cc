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


#include <dhcpsrv/hwaddr.h>

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace isc {
namespace dhcp {

std::string
hardwareAddressString(const HWAddr& hwaddr) {
    std::ostringstream stream;

    for (size_t i = 0; i < hwaddr.size(); ++i) {
        if (i > 0) {
            stream << ":";
        }
        stream << std::setw(2) << std::hex << std::setfill('0')
               << static_cast<unsigned int>(hwaddr[i]);
    }

    return (stream.str());
}

};  // namespace dhcp
};  // namespace isc
