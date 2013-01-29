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
#include "rdata_serialization.h"
#include "zone_data.h"
#include "segment_object_holder.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <cassert>
#include <cstring>
#include <new>                  // for the placement new
#include <vector>

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
    RdataSet* rdataset_next;
    for (RdataSet* rdataset = rdataset_head;
         rdataset != NULL;
         rdataset = rdataset_next)
    {
        rdataset_next = rdataset->getNext();
        RdataSet::destroy(*mem_sgmt, rdataset, rrclass);
    }
}

void
nullDeleter(RdataSet* rdataset_head) {
    assert(rdataset_head == NULL);
}
}

NSEC3Data*
NSEC3Data::create(util::MemorySegment& mem_sgmt,
                  const Name& zone_origin,
                  const generic::NSEC3PARAM& rdata)
{
    return (NSEC3Data::create(mem_sgmt, zone_origin,
                              rdata.getHashalg(), rdata.getFlags(),
                              rdata.getIterations(), rdata.getSalt()));
}

NSEC3Data*
NSEC3Data::create(util::MemorySegment& mem_sgmt,
                  const Name& zone_origin,
                  const generic::NSEC3& rdata)
{
    return (NSEC3Data::create(mem_sgmt, zone_origin,
                              rdata.getHashalg(), rdata.getFlags(),
                              rdata.getIterations(), rdata.getSalt()));
}

NSEC3Data*
NSEC3Data::create(util::MemorySegment& mem_sgmt,
                  const Name& zone_origin,
                  uint8_t hashalg, uint8_t flags, uint16_t iterations,
                  const std::vector<uint8_t>& salt)
{
    // NSEC3Data allocation can throw.  To avoid leaking the tree, we manage
    // it in the holder.
    // Note: we won't add any RdataSet, so we use the NO-OP deleter
    // (with an assertion check for that).
    typedef boost::function<void(RdataSet*)> RdataSetDeleterType;
    detail::SegmentObjectHolder<ZoneTree, RdataSetDeleterType> holder(
        mem_sgmt, ZoneTree::create(mem_sgmt, true),
        boost::bind(nullDeleter, _1));

    ZoneTree* tree = holder.get();
    const ZoneTree::Result result =
        tree->insert(mem_sgmt, zone_origin, NULL);
    assert(result == ZoneTree::SUCCESS);

    const size_t salt_len = salt.size();

    void* p = mem_sgmt.allocate(sizeof(NSEC3Data) + 1 + salt_len);
    NSEC3Data* const param_data =
        new(p) NSEC3Data(holder.release(), hashalg, flags, iterations);
    uint8_t* dp = param_data->getSaltBuf();
    *dp++ = salt_len;
    if (salt_len > 0) {
        std::memcpy(dp, &salt.at(0), salt_len); // use at for safety
    }

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

void
NSEC3Data::insertName(util::MemorySegment& mem_sgmt, const Name& name,
                      ZoneNode** node)
{
    const ZoneTree::Result result = nsec3_tree_->insert(mem_sgmt, name, node);

    // This should be ensured by the API:
    assert((result == ZoneTree::SUCCESS ||
            result == ZoneTree::ALREADYEXISTS) && node != NULL);
}

namespace {
// A helper to convert a TTL value in network byte order and set it in
// ZoneData::min_ttl_.  We can use util::OutputBuffer, but copy the logic
// here to guarantee it is exception free.
// Note: essentially this function is a local (re)implementation of the
// standard htonl() library function, but we avoid relying on it in case it's
// not available (it's not in the C++ standard library).
void
setTTLInNetOrder(uint32_t val, uint32_t* result) {
    uint8_t buf[4];
    buf[0] = static_cast<uint8_t>((val & 0xff000000) >> 24);
    buf[1] = static_cast<uint8_t>((val & 0x00ff0000) >> 16);
    buf[2] = static_cast<uint8_t>((val & 0x0000ff00) >> 8);
    buf[3] = static_cast<uint8_t>(val & 0x000000ff);
    std::memcpy(result, buf, sizeof(*result));
}
}

ZoneData::ZoneData(ZoneTree* zone_tree, ZoneNode* origin_node) :
    zone_tree_(zone_tree), origin_node_(origin_node),
    min_ttl_(0)          // tentatively set to silence static checkers
{
    setTTLInNetOrder(RRTTL::MAX_TTL().getValue(), &min_ttl_);
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
ZoneData::destroy(util::MemorySegment& mem_sgmt, ZoneData* zone_data,
                  RRClass zone_class)
{
    ZoneTree::destroy(mem_sgmt, zone_data->zone_tree_.get(),
                      boost::bind(rdataSetDeleter, zone_class, &mem_sgmt,
                                  _1));
    if (zone_data->nsec3_data_) {
        NSEC3Data::destroy(mem_sgmt, zone_data->nsec3_data_.get(), zone_class);
    }
    mem_sgmt.deallocate(zone_data, sizeof(ZoneData));
}

void
ZoneData::insertName(util::MemorySegment& mem_sgmt, const Name& name,
                     ZoneNode** node)
{
    const ZoneTree::Result result = zone_tree_->insert(mem_sgmt, name, node);

    // This should be ensured by the API:
    assert((result == ZoneTree::SUCCESS ||
            result == ZoneTree::ALREADYEXISTS) && node != NULL);
}

void
ZoneData::setMinTTL(uint32_t min_ttl_val) {
    setTTLInNetOrder(min_ttl_val, &min_ttl_);
}

} // namespace memory
} // namespace datasrc
} // datasrc isc
