// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <sstream>
#include <ostream>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrttl.h>

#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace isc::dns;
using namespace isc::util;

namespace {

// We wrap the C isalpha, because it seems to be overloaded with something.
// Then the find_if doesn't work.
bool
myIsalpha(char c) {
    return (isalpha(c) != 0);
}

// The conversion of units to their size
struct Unit {
    char unit;
    uint32_t multiply;
    uint32_t max_allowed;
};

Unit units[] = {
    { 'S', 1,                0xffffffff / 1 },
    { 'M', 60,               0xffffffff / 60 },
    { 'H', 60 * 60,          0xffffffff / (60 * 60) },
    { 'D', 24 * 60 * 60,     0xffffffff / (24 * 60 * 60) },
    { 'W', 7 * 24 * 60 * 60, 0xffffffff / (7 * 24 * 60 * 60) }
};

}

namespace isc {
namespace dns {

namespace {
bool
parseTTLString(const string& ttlstr, uint32_t& ttlval, string* error_txt) {
    if (ttlstr.empty()) {
        if (error_txt != NULL) {
            *error_txt = "Empty TTL string";
        }
        return (false);
    }

    // We use a larger data type to handle negative number cases.
    uint64_t val = 0;
    const string::const_iterator end = ttlstr.end();
    string::const_iterator pos = ttlstr.begin();

    try {
        // When we detect we have some units
        bool units_mode = false;

        while (pos != end) {
            // Find the first unit, if there's any.
            const string::const_iterator unit = find_if(pos, end, myIsalpha);
            // No unit
            if (unit == end) {
                if (units_mode) {
                    // We had some units before. The last one is missing unit.
                    if (error_txt != NULL) {
                        *error_txt = "Missing the last unit: " + ttlstr;
                    }
                    return (false);
                } else {
                    // Case without any units at all. Just convert and store
                    // it.
                    val = boost::lexical_cast<uint64_t>(ttlstr);
                    break;
                }
            }
            // There's a unit now.
            units_mode = true;
            // Find the unit and get the size.
            uint32_t multiply = 1;  // initialize to silence compiler warnings
            uint32_t max_allowed = 0xffffffff;
            bool found = false;
            for (size_t i = 0; i < sizeof(units) / sizeof(*units); ++i) {
                if (toupper(*unit) == units[i].unit) {
                    found = true;
                    multiply = units[i].multiply;
                    max_allowed = units[i].max_allowed;
                    break;
                }
            }
            if (!found) {
                if (error_txt != NULL) {
                    *error_txt = "Unknown unit used: " +
                        boost::lexical_cast<string>(*unit) + " in: " + ttlstr;
                }
                return (false);
            }
            // Now extract the number.
            if (unit == pos) {
                if (error_txt != NULL) {
                    *error_txt = "Missing number in TTL: " + ttlstr;
                }
                return (false);
            }
            const uint64_t value =
                boost::lexical_cast<uint64_t>(string(pos, unit));
            if (value > max_allowed) {
                if (error_txt != NULL) {
                    *error_txt = "Part of TTL out of range: "  + ttlstr;
                }
                return (false);
            }

            // seconds cannot be out of range at this point.
            const uint64_t seconds = value * multiply;
            assert(seconds <= 0xffffffff);

            // Add what we found
            val += seconds;
            // Check the partial value is still in range (the value can only
            // grow, so if we get out of range now, it won't get better, so
            // there's no need to continue).
            if (val < seconds || val > 0xffffffff) {
                if (error_txt != NULL) {
                    *error_txt = "Part of TTL out of range: "  + ttlstr;
                }
                return (false);
            }
            // Move to after the unit.
            pos = unit + 1;
        }
    } catch (const boost::bad_lexical_cast&) {
        if (error_txt != NULL) {
            *error_txt = "invalid TTL: " + ttlstr;
        }
        return (false);
    }

    if (val <= 0xffffffff) {
        ttlval = val;
    } else {
        // This could be due to negative numbers in input, etc.
        if (error_txt != NULL) {
            *error_txt = "TTL out of range: " + ttlstr;
        }
        return (false);
    }

    return (true);
}
}

RRTTL::RRTTL(const std::string& ttlstr) {
    string error_txt;
    if (!parseTTLString(ttlstr, ttlval_, &error_txt)) {
        isc_throw(InvalidRRTTL, error_txt);
    }
}

RRTTL*
RRTTL::createFromText(const string& ttlstr) {
    uint32_t ttlval;
    if (parseTTLString(ttlstr, ttlval, NULL)) {
        return (new RRTTL(ttlval));
    }
    return (NULL);
}

RRTTL::RRTTL(InputBuffer& buffer) {
    if (buffer.getLength() - buffer.getPosition() < sizeof(uint32_t)) {
        isc_throw(IncompleteRRTTL, "incomplete wire-format TTL value");
    }
    ttlval_ = buffer.readUint32();
}

const string
RRTTL::toText() const {
    ostringstream oss;
    oss << ttlval_;
    return (oss.str());
}

void
RRTTL::toWire(OutputBuffer& buffer) const {
    buffer.writeUint32(ttlval_);
}

void
RRTTL::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint32(ttlval_);
}

ostream&
operator<<(ostream& os, const RRTTL& rrttl) {
    os << rrttl.toText();
    return (os);
}
}
}
