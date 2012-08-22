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
#include <dns/rrclass.h>
#include <dns/rdataclass.h>

#include "rdataset.h"
#include "rdata_encoder.h"
#include "zone_data.h"
#include "segment_object_holder.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <cassert>
#include <new>                  // for the placement new

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

namespace {
void
rdataSetDeleter(RRClass rrclass, util::MemorySegment* mem_sgmt,
                RdataSet* rdataset_head)
{
    for (RdataSet* rdataset = rdataset_head;
         rdataset != NULL;
         rdataset = rdataset->getNext()) {
        RdataSet::destroy(*mem_sgmt, rrclass, rdataset);
    }
}

void
nullDeleter(RdataSet* rdataset_head) {
    assert(rdataset_head == NULL);
}
}

NSEC3Data*
NSEC3Data::create(util::MemorySegment& mem_sgmt,
                  const generic::NSEC3PARAM& rdata)
{
    // NSEC3Data allocation can throw.  To avoid leaking the tree, we manage
    // it in the holder.
    // Note: we won't add any RdataSet, so we use the NO-OP deleter
    // (with an assertion check for that).
    typedef boost::function<void(RdataSet*)> RdataSetDeleterType;
    detail::SegmentObjectHolder<ZoneTree, RdataSetDeleterType> holder(
        mem_sgmt, ZoneTree::create(mem_sgmt, true),
        boost::bind(nullDeleter, _1));

    const size_t salt_len = rdata.getSalt().size();

    void* p = mem_sgmt.allocate(sizeof(NSEC3Data) + salt_len + 1);
    NSEC3Data* const param_data =
        new(p) NSEC3Data(holder.release(), rdata.getHashalg(),
                         rdata.getFlags(), rdata.getIterations());
    uint8_t* dp = param_data->getSaltBuf();
    *dp++ =  salt_len;
    memcpy(dp, &rdata.getSalt().at(0), salt_len); // use at for safety

    return (param_data);
}

void
NSEC3Data::destroy(util::MemorySegment& mem_sgmt, NSEC3Data* data,
                   RRClass nsec3_class)
{
    ZoneTree::destroy(mem_sgmt, data->nsec3_tree_.get(),
                      boost::bind(rdataSetDeleter, nsec3_class, &mem_sgmt,
                                  _1));

    mem_sgmt.deallocate(data, sizeof(NSEC3Data) + 1 + data->getSaltLen());
}

ZoneData*
ZoneData::create(util::MemorySegment& mem_sgmt, const Name& zone_origin) {
    // ZoneTree::insert() and ZoneData allocation can throw.  See also
    // NSEC3Data::create().
    typedef boost::function<void(RdataSet*)> RdataSetDeleterType;
    detail::SegmentObjectHolder<ZoneTree, RdataSetDeleterType> holder(
        mem_sgmt, ZoneTree::create(mem_sgmt, true),
        boost::bind(nullDeleter, _1));

    ZoneTree* tree = holder.get();
    ZoneNode* origin_node = NULL;
    const ZoneTree::Result result =
        tree->insert(mem_sgmt, zone_origin, &origin_node);
    assert(result == ZoneTree::SUCCESS);
    void* p = mem_sgmt.allocate(sizeof(ZoneData));
    ZoneData* zone_data = new(p) ZoneData(holder.release(), origin_node);

    return (zone_data);
}

void
ZoneData::destroy(util::MemorySegment& mem_sgmt, RRClass zone_class,
                  ZoneData* zone_data)
{
    ZoneTree::destroy(mem_sgmt, zone_data->zone_tree_.get(),
                      boost::bind(rdataSetDeleter, zone_class, &mem_sgmt,
                                  _1));
    mem_sgmt.deallocate(zone_data, sizeof(ZoneData));
}

void
ZoneData::insertName(util::MemorySegment& mem_sgmt, const Name& name,
                     ZoneNode** node)
{
    const ZoneTree::Result result = zone_tree_->insert(mem_sgmt, name, node);

    // This should be ensured by the API:
    assert((result == ZoneTree::SUCCESS ||
            result == ZoneTree::ALREADYEXISTS) && node!= NULL);
}

} // namespace memory
} // namespace datasrc
} // datasrc isc
