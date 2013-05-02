// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/zone_table_segment_local.h>
#include <datasrc/memory/zone_table_segment_mapped.h>
#include <datasrc/memory/zone_writer.h>

#include <string>

using namespace isc::dns;

namespace isc {
namespace datasrc {
namespace memory {

ZoneTableSegment*
ZoneTableSegment::create(const RRClass& rrclass, const std::string& type) {
    // This will be a few sequences of if-else and hardcoded.  Not really
    // sophisticated, but we don't expect to have too many types at the moment.
    // Until that it becomes a real issue we won't be too smart.
    if (type == "local") {
        return (new ZoneTableSegmentLocal(rrclass));
    } else if (type == "mapped") {
        return (new ZoneTableSegmentMapped(rrclass));
    }
    isc_throw(UnknownSegmentType, "Zone table segment type not supported: "
              << type);
}

void
ZoneTableSegment::destroy(ZoneTableSegment *segment) {
    delete segment;
}

} // namespace memory
} // namespace datasrc
} // namespace isc
