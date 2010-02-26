// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <cassert>
#include <iterator>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include <exceptions/exceptions.h>
#include <boost/foreach.hpp>
#include <ctype.h>
#include <stdint.h>

#include "hex.h"

using namespace std;

namespace isc {
namespace dns {

static const char hexdigits[] = "0123456789ABCDEF";

std::string
encodeHex(const std::vector<uint8_t>& binary)
{
    // calculate the resulting length.  it should be twice the
    // original data length
    size_t len = (binary.size() * 2);
    std::ostringstream hex;

    BOOST_FOREACH(uint8_t octet, binary) {
        hex << hexdigits[octet >> 4] << hexdigits[octet & 0xf];
    }
    assert(len >= hex.str().length());
    return (hex.str());
}

void
decodeHex(const std::string& hex, std::vector<uint8_t>& result)
{
    result.clear();
    std::istringstream iss(hex);
    char c1, c2;
    uint8_t n;

    iss.width(1);
    if ((hex.size() % 2) == 1) {
        iss >> c2;
        n = strchr(hexdigits, c2) - hexdigits;
        result.push_back(n);
    }
    while (!iss.eof()) {
        iss >> c1 >> c2;;
        n = (strchr(hexdigits, c1) - hexdigits) << 4;
        n |= (strchr(hexdigits, c2) - hexdigits);

        if (!iss.bad() && !iss.fail()) {
            result.push_back(n);
        }
    }
}

}
}
