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

#include <exceptions/exceptions.h>

#include <dns/rdata.h>
#include <dns/master_lexer.h>
#include <dns/rdata/generic/detail/char_string.h>

#include <boost/lexical_cast.hpp>

#include <cassert>
#include <cctype>
#include <cstring>
#include <vector>

#include <stdint.h>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {

namespace {
// Convert a DDD form to the corresponding integer
int
decimalToNumber(const char* s, const char* s_end) {
    if (s_end - s < 3) {
        isc_throw(InvalidRdataText, "Escaped digits too short");
    }

    const std::string num_str(s, s + 3);
    try {
        const int i = boost::lexical_cast<int>(num_str);
        if (i > 255) {
            isc_throw(InvalidRdataText, "Escaped digits too large: "
                      << num_str);
        }
        return (i);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(InvalidRdataText,
                  "Invalid form for escaped digits: " << num_str);
    }
}
}

void
strToCharString(const MasterToken::StringRegion& str_region,
                CharString& result)
{
    // make a space for the 1-byte length field; filled in at the end
    result.push_back(0);

    bool escape = false;
    const char* s = str_region.beg;
    const char* const s_end = str_region.beg + str_region.len;

    for (size_t n = str_region.len; n != 0; --n, ++s) {
        int c = (*s & 0xff);
        if (escape && std::isdigit(c) != 0) {
            c = decimalToNumber(s, s_end);
            assert(n >= 3);
            n -= 2;
            s += 2;
        } else if (!escape && c == '\\') {
            escape = true;
            continue;
        }
        escape = false;
        result.push_back(c);
    }
    if (escape) {               // terminated by non-escaped '\'
        isc_throw(InvalidRdataText, "character-string ends with '\\'");
    }
    if (result.size() > MAX_CHARSTRING_LEN + 1) { // '+ 1' due to the len field
        isc_throw(CharStringTooLong, "character-string is too long: " <<
                  (result.size() - 1) << "(+1) characters");
    }
    result[0] = result.size() - 1;
}

} // end of detail
} // end of generic
} // end of rdata
} // end of dns
} // end of isc
