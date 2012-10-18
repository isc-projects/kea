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

#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/domaintree.h>
#include <datasrc/memory/segment_object_holder.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <cassert>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace datasrc {
namespace memory {
using detail::SegmentObjectHolder;

namespace {
void
deleteZoneData(util::MemorySegment* mem_sgmt, ZoneData* zone_data,
               RRClass rrclass)
{
    if (zone_data != NULL) {
        ZoneData::destroy(*mem_sgmt, zone_data, rrclass);
    }
}
typedef boost::function<void(ZoneData*)> ZoneDataDeleterType;
}

ZoneTable*
ZoneTable::create(util::MemorySegment& mem_sgmt, RRClass zone_class) {
    SegmentObjectHolder<ZoneTableTree, ZoneDataDeleterType> holder(
        mem_sgmt, ZoneTableTree::create(mem_sgmt),
        boost::bind(deleteZoneData, &mem_sgmt, _1, zone_class));
    void* p = mem_sgmt.allocate(sizeof(ZoneTable));
    ZoneTable* zone_table = new(p) ZoneTable(zone_class, holder.get());
    holder.release();
    return (zone_table);
}

void
ZoneTable::destroy(util::MemorySegment& mem_sgmt, ZoneTable* ztable)
{
    ZoneTableTree::destroy(mem_sgmt, ztable->zones_.get(),
                           boost::bind(deleteZoneData, &mem_sgmt, _1,
                                       ztable->rrclass_));
    mem_sgmt.deallocate(ztable, sizeof(ZoneTable));
}

ZoneTable::AddResult
ZoneTable::addZone(util::MemorySegment& mem_sgmt, RRClass zone_class,
                   const Name& zone_name, ZoneData* content)
{
    if (content == NULL) {
        isc_throw(isc::BadValue, "Zone content must not be NULL");
    }
    SegmentObjectHolder<ZoneData, RRClass> holder(mem_sgmt, content,
                                                  zone_class);
    // Get the node where we put the zone
    ZoneTableNode* node(NULL);
    switch (zones_->insert(mem_sgmt, zone_name, &node)) {
    case ZoneTableTree::SUCCESS:
    case ZoneTableTree::ALREADYEXISTS:
        // These are OK
        break;
    default:
        // Can Not Happen
        assert(false);
    }
    // Can Not Happen
    assert(node != NULL);

    // We can release now, setData never throws
    ZoneData* old = node->setData(holder.release());
    if (old != NULL) {
        return (AddResult(result::EXIST, old));
    } else {
        return (AddResult(result::SUCCESS, NULL));
    }
}

ZoneTable::FindResult
ZoneTable::findZone(const Name& name) const {
    const ZoneTableNode* node(NULL);
    result::Result my_result;

    // Translate the return codes
    switch (zones_->find(name, &node)) {
    case ZoneTableTree::EXACTMATCH:
        my_result = result::SUCCESS;
        break;
    case ZoneTableTree::PARTIALMATCH:
        my_result = result::PARTIALMATCH;
        break;
    case ZoneTableTree::NOTFOUND:
        // We have no data there, so translate the pointer to NULL as well
        return (FindResult(result::NOTFOUND, NULL));
    default:
        // Can Not Happen
        assert(0);
        // Because of warning
        return (FindResult(result::NOTFOUND, NULL));
    }

    // Can Not Happen (remember, NOTFOUND is handled)
    assert(node != NULL);

    return (FindResult(my_result, node->getData()));
}

} // end of namespace memory
} // end of namespace datasrc
} // end of namespace isc
