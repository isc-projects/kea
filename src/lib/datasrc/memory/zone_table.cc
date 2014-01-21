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

#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/domaintree.h>
#include <datasrc/memory/segment_object_holder.h>
#include <datasrc/memory/logger.h>

#include <exceptions/exceptions.h>

#include <util/memory_segment.h>

#include <dns/name.h>

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
    // We shouldn't delete empty zone data here; the only empty zone
    // that can be passed here is the placeholder for broken zones maintained
    // in the zone table.  It will stay there until the table is destroyed.
    if (zone_data && !zone_data->isEmpty()) {
        ZoneData::destroy(*mem_sgmt, zone_data, rrclass);
    }
}
typedef boost::function<void(ZoneData*)> ZoneDataDeleterType;
}

ZoneTable*
ZoneTable::create(util::MemorySegment& mem_sgmt, const RRClass& zone_class) {
    // Create a placeholder "null" zone data
    SegmentObjectHolder<ZoneData, RRClass> zdholder(mem_sgmt, zone_class);
    zdholder.set(ZoneData::create(mem_sgmt));

    // create and setup the tree for the table.
    SegmentObjectHolder<ZoneTableTree, ZoneDataDeleterType> tree_holder(
        mem_sgmt, boost::bind(deleteZoneData, &mem_sgmt, _1, zone_class));
    tree_holder.set(ZoneTableTree::create(mem_sgmt));
    void* p = mem_sgmt.allocate(sizeof(ZoneTable));

    // Build zone table with the created objects.  Its constructor doesn't
    // throw, so we can release them from the holder at this point.
    ZoneTable* zone_table = new(p) ZoneTable(zone_class, tree_holder.release(),
                                             zdholder.release());
    return (zone_table);
}

void
ZoneTable::destroy(util::MemorySegment& mem_sgmt, ZoneTable* ztable, int)
{
    ZoneTableTree::destroy(mem_sgmt, ztable->zones_.get(),
                           boost::bind(deleteZoneData, &mem_sgmt, _1,
                                       ztable->rrclass_));
    ZoneData::destroy(mem_sgmt, ztable->null_zone_data_.get(),
                      ztable->rrclass_);
    mem_sgmt.deallocate(ztable, sizeof(ZoneTable));
}

ZoneTable::AddResult
ZoneTable::addZone(util::MemorySegment& mem_sgmt,
                   const Name& zone_name, ZoneData* content)
{
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEMORY_MEM_ADD_ZONE).
        arg(zone_name).arg(rrclass_);

    if (!content || content->isEmpty()) {
        isc_throw(InvalidParameter,
                  (content ? "empty data" : "NULL") <<
                  " is passed to Zone::addZone");
    }

    return (addZoneInternal(mem_sgmt, zone_name, content));
}

ZoneTable::AddResult
ZoneTable::addEmptyZone(util::MemorySegment& mem_sgmt, const Name& zone_name) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEMORY_MEM_ADD_EMPTY_ZONE).
        arg(zone_name).arg(rrclass_);

    return (addZoneInternal(mem_sgmt, zone_name, null_zone_data_.get()));
}

ZoneTable::AddResult
ZoneTable::addZoneInternal(util::MemorySegment& mem_sgmt,
                           const dns::Name& zone_name,
                           ZoneData* content)
{
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

    ZoneData* old = node->setData(content);
    if (old != NULL) {
        return (AddResult(result::EXIST, old->isEmpty() ? NULL : old));
    } else {
        ++zone_count_;
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

    // Can Not Happen (remember, NOTFOUND is handled).  node should also have
    // data because the tree is constructed in the way empty nodes would
    // be "invisible" for find().
    assert(node != NULL);

    const ZoneData* zone_data = node->getData();
    assert(zone_data);
    const result::ResultFlags flags =
        zone_data->isEmpty() ? result::ZONE_EMPTY : result::FLAGS_DEFAULT;
    return (FindResult(my_result, zone_data->isEmpty() ? NULL : zone_data,
                       flags));
}

} // end of namespace memory
} // end of namespace datasrc
} // end of namespace isc
