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

#include <dns/message.h>
#include <dns/rcode.h>

#include <datasrc/zonetable.h>

#include <auth/query.h>

using namespace isc::dns;
using namespace isc::datasrc;

namespace isc {
namespace auth {
void
Query::process() const {
    const ZoneTable::FindResult result = zone_table_.findZone(qname_);

    if (result.code != isc::datasrc::result::SUCCESS &&
        result.code != isc::datasrc::result::PARTIALMATCH) {
        response_.setRcode(Rcode::SERVFAIL());
        return;
    }

    // Right now we have no code to search the zone, so we simply return
    // NXDOMAIN for tests.
    response_.setRcode(Rcode::NXDOMAIN());
}
}
}
