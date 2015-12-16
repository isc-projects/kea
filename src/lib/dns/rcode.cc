// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>
#include <sstream>
#include <ostream>

#include <exceptions/exceptions.h>

#include <dns/rcode.h>

using namespace std;

namespace isc {
namespace dns {
namespace {
// This diagram shows the wire-format representation of the 12-bit extended
// form RCODEs and its relationship with implementation specific parameters.
//
//     0     3               11      15
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//    |UNUSED | EXTENDED-RCODE | RCODE |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                            <= EXTRCODE_SHIFT (4 bits)
const unsigned int EXTRCODE_SHIFT = 4;
const unsigned int RCODE_MASK = 0x000f;


// EDNS-extended RCODEs are 12-bit unsigned integers.  0xfff is the highest.
const uint16_t MAX_RCODE = 0xfff;

const char* const rcodetext[] = {
    "NOERROR",
    "FORMERR",
    "SERVFAIL",
    "NXDOMAIN",
    "NOTIMP",
    "REFUSED",
    "YXDOMAIN",
    "YXRRSET",
    "NXRRSET",
    "NOTAUTH",
    "NOTZONE",
    "RESERVED11",
    "RESERVED12",
    "RESERVED13",
    "RESERVED14",
    "RESERVED15",
    "BADVERS"
};
}

Rcode::Rcode(const uint16_t code) : code_(code) {
    if (code_ > MAX_RCODE) {
        isc_throw(OutOfRange, "Rcode is too large to construct");
    }
}

Rcode::Rcode(const uint8_t code, const uint8_t extended_code) :
    code_((extended_code << EXTRCODE_SHIFT) | (code & RCODE_MASK))
{
    if (code > RCODE_MASK) {
        isc_throw(OutOfRange,
                  "Base Rcode is too large to construct: "
                  << static_cast<unsigned int>(code));
    }
}

uint8_t
Rcode::getExtendedCode() const {
    return (code_ >> EXTRCODE_SHIFT);
}

string
Rcode::toText() const {
    if (code_ < sizeof(rcodetext) / sizeof (const char*)) {
        return (rcodetext[code_]);
    }

    ostringstream oss;
    oss << code_;
    return (oss.str());
}

ostream&
operator<<(std::ostream& os, const Rcode& rcode) {
    return (os << rcode.toText());
}
}
}
