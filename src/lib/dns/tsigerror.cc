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

#include <ostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <dns/rcode.h>
#include <dns/tsigerror.h>

namespace isc {
namespace dns {
namespace {
const char* const tsigerror_text[] = {
    "BADSIG",
    "BADKEY",
    "BADTIME",
    "BADMODE",
    "BADNAME",
    "BADALG",
    "BADTRUNC"
};
}

TSIGError::TSIGError(Rcode rcode) : code_(rcode.getCode()) {
    if (code_ > MAX_RCODE_FOR_TSIGERROR) {
        isc_throw(OutOfRange, "Invalid RCODE for TSIG Error: " << rcode);
    }
}

std::string
TSIGError::toText() const {
    if (code_ <= MAX_RCODE_FOR_TSIGERROR) {
        return (Rcode(code_).toText());
    } else if (code_ <= BAD_TRUNC_CODE) {
        return (tsigerror_text[code_ - (MAX_RCODE_FOR_TSIGERROR + 1)]);
    } else {
        return (boost::lexical_cast<std::string>(code_));
    }
}

Rcode
TSIGError::toRcode() const {
    if (code_ <= MAX_RCODE_FOR_TSIGERROR) {
        return (Rcode(code_));
    }
    if (code_ > BAD_TRUNC_CODE) {
        return (Rcode::SERVFAIL());
    }
    return (Rcode::NOTAUTH());
}

std::ostream&
operator<<(std::ostream& os, const TSIGError& error) {
    return (os << error.toText());
}
} // namespace dns
} // namespace isc
