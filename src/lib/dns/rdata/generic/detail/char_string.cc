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

#include <dns/master_lexer.h>
#include <dns/rdata/generic/detail/char_string.h>

#include <vector>
#include <stdint.h>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {

void
strToCharString(const MasterToken::StringRegion& str_region,
                CharString& result)
{
    result.push_back(0);
    size_t n = str_region.len;
    const char* s = str_region.beg;
    while (n-- != 0) {
        const int c = (*s++) & 0xff;
        result.push_back(c);
    }
    result[0] = str_region.len; // FIXME: this is not always correct
}

} // end of detail
} // end of generic
} // end of rdata
} // end of dns
} // end of isc
