// Copyright (C) 2011, 2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
