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
    ZoneTable* zone_table = new(p) ZoneTable(holder.get());
    holder.release();
    return (zone_table);
}

void
ZoneTable::destroy(util::MemorySegment& mem_sgmt, ZoneTable* ztable,
                   RRClass zone_class)
{
    ZoneTableTree::destroy(mem_sgmt, ztable->zones_.get(),
                           boost::bind(deleteZoneData, &mem_sgmt, _1,
                                       zone_class));
    mem_sgmt.deallocate(ztable, sizeof(ZoneTable));
}

ZoneTable::AddResult
ZoneTable::addZone(util::MemorySegment& mem_sgmt, RRClass zone_class,
                   const Name& zone_name)
{
    // Create a new ZoneData instance first.  If the specified name already
    // exists in the table, the new data will soon be destroyed, but we want
    // to make sure if this allocation fails the tree won't be changed to
    // provide as strong guarantee as possible.  In practice, we generally
    // expect the caller tries to add a zone only when it's a new one, so
    // this should be a minor concern.
    SegmentObjectHolder<ZoneData, RRClass> holder(
        mem_sgmt, ZoneData::create(mem_sgmt, zone_name), zone_class);

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

    // Is it empty? We either just created it or it might be nonterminal
    if (node->isEmpty()) {
        node->setData(holder.get());
        return (AddResult(result::SUCCESS, holder.release()));
    } else { // There's something there already
        return (AddResult(result::EXIST, node->getData()));
    }
}

ZoneTable::FindResult
ZoneTable::findZone(const Name& name) const {
    ZoneTableNode* node(NULL);
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

ZoneTable::FindResult
ZoneTable::setZoneData(const Name& name, ZoneData* data)
{
    ZoneTableNode* node(NULL);

    ZoneTableTree::Result result(zones_->find(name, &node));

    if (result != ZoneTableTree::EXACTMATCH) {
        return (FindResult(result::NOTFOUND, NULL));
    } else {
        return (FindResult(result::SUCCESS, node->setData(data)));
    }
}

} // end of namespace memory
} // end of namespace datasrc
} // end of namespace isc
