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

#include "base32.h"

using namespace std;

namespace isc {
namespace dns {

static const char base32hex[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

string
encodeBase32(const vector<uint8_t>& binary)
{
    ostringstream base32;
    size_t len = binary.size();
    size_t pos = 0;
    while (len > 0) {
        char buf[9];
        memset(buf, '=', 8);
        buf[8] = '\0';

        uint8_t digit = (binary.at(pos) >> 3) & 0x1f;
        buf[0] = base32hex[digit];

        if (len == 1) {
            digit = (binary.at(pos) << 2) & 0x1c;
            buf[1] = base32hex[digit];
            base32 << buf;
            break;
        }

        digit = ((binary.at(pos) << 2) & 0x1c) |
                ((binary.at(pos + 1) >> 6) & 0x03);
        buf[1] = base32hex[digit];

        digit = (binary.at(pos + 1) >> 1) & 0x1f;
        buf[2] = base32hex[digit];

        if (len == 2) {
            digit = (binary.at(pos + 1) << 4) & 0x10;
            buf[3] = base32hex[digit];
            base32 << buf;
            break;
        }

        digit = ((binary.at(pos + 1) << 4) & 0x10) |
                ((binary.at(pos + 2) >> 4) & 0x0f);
        buf[3] = base32hex[digit];
        if (len == 3) {
            digit = (binary.at(pos + 2) << 1) & 0x1e;
            buf[4] = base32hex[digit];
            base32 << buf;
            break;
        }

        digit = ((binary.at(pos + 2) << 1) & 0x1e) |
                ((binary.at(pos + 3) >> 7) & 0x01);
        buf[4] = base32hex[digit];

        digit = (binary.at(pos + 3) >> 2) & 0x1f;
        buf[5] = base32hex[digit];

        if (len == 4) {
            digit = (binary.at(pos + 3) << 3) & 0x18;
            buf[6] = base32hex[digit];
            base32 << buf;
            break;
        }

        digit = ((binary.at(pos + 3) << 3) & 0x18) |
                ((binary.at(pos + 4) >> 5) & 0x07);
        buf[6] = base32hex[digit];

        digit = binary.at(pos + 4) & 0x1f;
        buf[7] = base32hex[digit];

        len -= 5;
        pos += 5;

        base32 << buf;
    }

    return (base32.str());
}

void
decodeBase32(const string& base32, vector<uint8_t>& result)
{
    ostringstream comp;

    // compress input by removing whitespace
    size_t len = base32.length();
    for (int i = 0; i < len; i++) {
        char c = base32.at(i);
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            continue;
        }
        comp << c;
    }

    // base32 text should be a multiple of 8 bytes long
    if (comp.str().length() % 8 != 0) {
        dns_throw (BadBase32String, "Invalid length");
    }

    istringstream iss(comp.str());
    result.clear();
    bool seenpad = false;
    while (!iss.eof()) {
        string group;

        iss >> setw(8) >> group;
        if (iss.bad() || iss.fail()) {
            dns_throw (BadBase32String, "Could not parse base32 input");
        }

        uint8_t octet = 0;
        for (int i = 0; i < 8; i ++) {
            char c = toupper(group.at(i));
            int value;

            if (c != '=' && seenpad) {
                dns_throw (BadBase32String, "Invalid base32 input");
            } else 

            if (c == '=' && !seenpad) {
                value = 0;
                seenpad = true;
            } else {
                const char* pos = strchr(base32hex, c);
                if (!pos) {
                    dns_throw (BadBase32String, "Invalid base32 input");
                }
                value = pos - base32hex;
                assert (value < 32);
            }

            switch (i) {
            case 0: octet |= value << 3;
                    break;
            case 1: octet |= value >> 2;
                    result.push_back(octet);
                    octet = (value & 0x03) << 6;
                    break;
            case 2: octet |= value << 1;
                    break;
            case 3: octet |= value >> 4;
                    result.push_back(octet);
                    octet = (value & 0x0f) << 4;
                    break;
            case 4: octet |= value >> 1;
                    result.push_back(octet);
                    octet = (value & 0x01) << 7;
                    break;
            case 5: octet |= value << 2;
                    break;
            case 6: octet |= value >> 3;
                    result.push_back(octet);
                    octet = (value & 0x07) << 5;
                    break;
            case 7: octet |= value;
                    result.push_back(octet);
            }
        }
    }
}

}
}
