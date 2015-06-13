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
