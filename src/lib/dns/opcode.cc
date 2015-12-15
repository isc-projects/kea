// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>
#include <ostream>

#include <exceptions/exceptions.h>

#include <dns/opcode.h>

using namespace std;

namespace isc {
namespace dns {
namespace {
const char *opcodetext[] = {
    "QUERY",
    "IQUERY",
    "STATUS",
    "RESERVED3",
    "NOTIFY",
    "UPDATE",
    "RESERVED6",
    "RESERVED7",
    "RESERVED8",
    "RESERVED9",
    "RESERVED10",
    "RESERVED11",
    "RESERVED12",
    "RESERVED13",
    "RESERVED14",
    "RESERVED15"
};

// OPCODEs are 4-bit values.  So 15 is the highest code.
const uint8_t MAX_OPCODE = 15;
}

Opcode::Opcode(const uint8_t code) : code_(static_cast<CodeValue>(code)) {
    if (code > MAX_OPCODE) {
        isc_throw(OutOfRange,
                  "DNS Opcode is too large to construct: "
		  << static_cast<unsigned>(code));
    }
}

string
Opcode::toText() const {
    return (opcodetext[code_]);
}

ostream&
operator<<(std::ostream& os, const Opcode& opcode) {
    return (os << opcode.toText());
}
}
}
