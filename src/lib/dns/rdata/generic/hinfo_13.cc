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

#include <config.h>

#include <string>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace boost;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

HINFO::HINFO(const string& type_str) {
}

HINFO::HINFO(InputBuffer& buffer, size_t rdata_len) {
}

HINFO::HINFO(const HINFO& source) {
}

std::string
HINFO::toText() const {
}

void
HINFO::toWire(OutputBuffer& buffer) const {
}

void
HINFO::toWire(AbstractMessageRenderer& renderer) const {
}

int
HINFO::compare(const Rdata& other) const {
    // The compare method normally begins with this dynamic cast.
    const HINFO& other_hinfo = dynamic_cast<const HINFO&>(other);
    // ...
}


// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
