// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <sstream>

#include <cfgrpt/config_report.h>

namespace isc {
namespace detail {

// The config_report array finished by an empty line ("")
// Each line before this final one begins by four semicolons (;;;;)
// in order to be easy to extract from binaries.
std::string
getConfigReport() {
    std::stringstream tmp;

    size_t linenum = 0;
    for (;;) {
        const char* const line = config_report[linenum++];
        if (line[0] == '\0')
            break;
        tmp << line + 4 << std::endl;
    }
    return (tmp.str());
}

}
}
