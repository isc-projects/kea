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

#include <dns/util/hex.h>

using namespace std;

namespace isc {
namespace dns {

namespace {
const char hexdigits[] = "0123456789ABCDEF";
}

std::string
encodeHex(const std::vector<uint8_t>& binary) {
    // calculate the resulting length.  it should be twice the
    // original data length
    const size_t len = (binary.size() * 2);
    std::ostringstream hex;

    BOOST_FOREACH(uint8_t octet, binary) {
        hex << hexdigits[octet >> 4] << hexdigits[octet & 0xf];
    }
    assert(len >= hex.str().length());
    return (hex.str());
}

void
decodeHex(const std::string& hex, std::vector<uint8_t>& result) {
    ostringstream comp;

    // compress input by removing whitespace
    const size_t len = hex.length();
    for (int i = 0; i < len; ++i) {
        char c = hex.at(i);
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            continue;
        }
        comp << c;
    }

    istringstream iss(comp.str());
    result.clear();
    char c1, c2;

    iss.width(1);
    if ((comp.str().length() % 2) == 1) {
        c2 = '0';
        iss >> c2;

        const char* pos = strchr(hexdigits, toupper(c2));
        if (pos == NULL) {
            isc_throw(BadHexString, "Invalid hex digit");
        }

        if (!iss.eof() && !iss.bad() && !iss.fail()) {
            result.push_back(pos - hexdigits);
        }
    }
    while (!iss.eof()) {
        c1 = c2 = '0';
        iss >> c1 >> c2;;

        if (iss.eof() || iss.fail() || iss.bad()) {
            break;
        }

        const char* pos1 = strchr(hexdigits, toupper(c1));
        const char* pos2 = strchr(hexdigits, toupper(c2));
        if (!pos1 || !pos2) {
            isc_throw(BadHexString, "Invalid hex digit");
        }

        const uint8_t n = ((pos1 - hexdigits) << 4) | (pos2 - hexdigits);
        result.push_back(n);
    }
}

}
}
