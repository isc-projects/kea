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

#include <util/memory_segment.h>

#include <dns/name.h>

#include "rdataset.h"
#include "rdata_encoder.h"
#include "zone_data.h"

#include <cassert>
#include <new>                  // for the placement new

using namespace isc::dns;

namespace isc {
namespace datasrc {
namespace memory {

ZoneData*
ZoneData::create(util::MemorySegment& mem_sgmt, const Name& zone_origin) {
    ZoneTree* tree = ZoneTree::create(mem_sgmt, true);
    ZoneNode* origin_node = NULL;
    const ZoneTree::Result result =
        tree->insert(mem_sgmt, zone_origin, &origin_node);
    assert(result == ZoneTree::SUCCESS);
    void* p = mem_sgmt.allocate(sizeof(ZoneData));
    ZoneData* zone_data = new(p) ZoneData(tree, origin_node);

    return (zone_data);
}

void
ZoneData::destroy(util::MemorySegment& mem_sgmt, ZoneData* zone_data) {
    ZoneTree::destroy(mem_sgmt, zone_data->zone_tree_.get());
    mem_sgmt.deallocate(zone_data, sizeof(ZoneData));
}

} // namespace memory
} // namespace datasrc
} // datasrc isc
