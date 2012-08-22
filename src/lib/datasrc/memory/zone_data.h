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

#ifndef DATASRC_MEMORY_ZONE_DATA_H
#define DATASRC_MEMORY_ZONE_DATA_H 1

#include <util/memory_segment.h>

#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/memory/domaintree.h>
#include <datasrc/memory/rdataset.h>

#include <boost/interprocess/offset_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
class NSEC3PARAM;
}
}
}

namespace datasrc {
namespace memory {

typedef DomainTree<RdataSet> ZoneTree;
typedef DomainTreeNode<RdataSet> ZoneNode;

class NSEC3Data : boost::noncopyable {
public:
    static NSEC3Data* create(util::MemorySegment& mem_sgmt,
                             const dns::rdata::generic::NSEC3PARAM& rdata);
    static void destroy(util::MemorySegment& mem_sgmt, NSEC3Data* data,
                        dns::RRClass nsec3_class);

    const boost::interprocess::offset_ptr<ZoneTree> nsec3_tree_;
public:
    const uint8_t hashalg;
    const uint8_t flags;
    const uint16_t iterations;
    // For 64-bit machines there'll be a padding space here, but since
    // only at most one (or a few in very rare cases) instance will be
    // created per zone, the overhead should be acceptable.

    const ZoneTree* getNSEC3Tree() const { return (nsec3_tree_.get()); }
    ZoneTree* getNSEC3Tree() { return (nsec3_tree_.get()); }
    size_t getSaltLen() const { return (*getSaltBuf()); }
    const uint8_t* getSaltData() const { return (getSaltBuf() + 1); }

private:
    NSEC3Data(ZoneTree* nsec3_tree_param, uint8_t hashalg_param,
              uint8_t flags_param, uint16_t iterations_param) :
        nsec3_tree_(nsec3_tree_param), hashalg(hashalg_param),
        flags(flags_param), iterations(iterations_param)
    {}

    const uint8_t* getSaltBuf() const {
        return (reinterpret_cast<const uint8_t*>(this + 1));
    }
    uint8_t* getSaltBuf() {
        return (reinterpret_cast<uint8_t*>(this + 1));
    }
};

class ZoneData : boost::noncopyable {
public:

private:
    ZoneData(ZoneTree* zone_tree, ZoneNode* origin_node) :
        zone_tree_(zone_tree), origin_node_(origin_node)
    {}

public:
    static ZoneData* create(util::MemorySegment& mem_sgmt,
                            const dns::Name& zone_name);
    static void destroy(util::MemorySegment& mem_sgmt, dns::RRClass zone_class,
                        ZoneData* zone_data);

    void insertName(util::MemorySegment& mem_sgmt, const dns::Name& name,
                    ZoneNode** node);

    // This is a shortcut.
    const ZoneNode* getOriginNode() const {
        return (origin_node_.get());
    }

private:
    const boost::interprocess::offset_ptr<ZoneTree> zone_tree_;
    const boost::interprocess::offset_ptr<ZoneNode> origin_node_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_ZONE_DATA_H

// Local Variables:
// mode: c++
// End:
