// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <stdint.h>

#include <vector>

#include <dns/exceptions.h>

using namespace std;

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {
namespace nsec {
void
buildRRTypeBitmap(const char* const rrtype_name,
                  const size_t total_len, vector<uint8_t>& typebits)
{
    int len = 0;
    bool first = true;
    unsigned int block, lastblock = 0;
    for (int i = 0; i < total_len; i += len) {
        if (i + 2 > total_len) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: incomplete bit map field");
        }
        block = typebits[i];
        len = typebits[i + 1];
        // Check that bitmap window blocks are in the correct order.
        if (!first && block <= lastblock) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: Disordered window blocks found: "
                      << lastblock << " then " << block);
        }
        // Check for legal length
        if (len < 1 || len > 32) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: Invalid bitmap length: " << len);
        }
        // Check for overflow.
        i += 2;
        if (i + len > total_len) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: bitmap length too large: " << len);
        }
        // The last octet of the bitmap must be non zero.
        if (typebits[i + len - 1] == 0) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: bitmap ending an all-zero byte");
        }

        lastblock = block;
        first = false;
    }
}
}
}
}
}
}
}
