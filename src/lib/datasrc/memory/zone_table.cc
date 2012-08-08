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

#include <util/memory_segment.h>

#include <dns/name.h>

#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/domaintree.h>

#include <cassert>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace datasrc {
namespace memory {

ZoneTable::ZoneTable(util::MemorySegment& mem_sgmt) :
    zones_(ZoneTableTree::create(mem_sgmt))
{}

namespace {
// A simple holder to make resource allocation for ZoneTable exception safe.
// It works like std::auto_ptr but much more simplified.
struct ZoneTableHolder {
    ZoneTableHolder(util::MemorySegment& mem_sgmt, void* ptr) :
        mem_sgmt_(mem_sgmt), ptr_(ptr)
    {}
    ~ZoneTableHolder() {
        if (ptr_ != NULL) {
            mem_sgmt_.deallocate(ptr_, sizeof(ZoneTable));
        }
    }
    void* get() { return (ptr_); }
    void release() { ptr_ = NULL; }
private:
    util::MemorySegment& mem_sgmt_;
    void* ptr_;
};
}

ZoneTable*
ZoneTable::create(util::MemorySegment& mem_sgmt) {
    ZoneTableHolder holder(mem_sgmt, mem_sgmt.allocate(sizeof(ZoneTable)));
    ZoneTable* zone_table = new(holder.get()) ZoneTable(mem_sgmt);
    holder.release();
    return (zone_table);
}

void
ZoneTable::destroy(util::MemorySegment& mem_sgmt, ZoneTable* ztable) {
    ZoneTableTree::destroy(mem_sgmt, ztable->zones_);
    mem_sgmt.deallocate(ztable, sizeof(ZoneTable));
}

result::Result
ZoneTable::addZone(util::MemorySegment& mem_sgmt, const Name& zone_name,
                   ZoneData* zone_data)
{
    // Sanity check
    if (zone_data == NULL) {
        isc_throw(InvalidParameter,
                  "Null pointer is passed to ZoneTable::addZone()");
    }

    // Get the node where we put the zone
    ZoneTableNode* node(NULL);
    switch (zones_->insert(mem_sgmt, zone_name, &node)) {
        // This is OK
    case ZoneTableTree::SUCCESS:
    case ZoneTableTree::ALREADYEXISTS:
        break;
        // Can Not Happen
    default:
        assert(false);
    }
    // Can Not Happen
    assert(node != NULL);

    // Is it empty? We either just created it or it might be nonterminal
    if (node->isEmpty()) {
        node->setData(mem_sgmt, zone_data);
        return (result::SUCCESS);
    } else { // There's something there already
        return (result::EXIST);
    }
}

result::Result
ZoneTable::removeZone(const Name&) {
    // TODO Implement
    assert(false);
    // This should not ever be returned, the assert should kill us by now
    return (result::SUCCESS);
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
        // We have no data there, so translate the pointer to NULL as well
    case ZoneTableTree::NOTFOUND:
        return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
        // Can Not Happen
    default:
        assert(0);
        // Because of warning
        return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
    }

    // Can Not Happen (remember, NOTFOUND is handled)
    assert(node != NULL);

    // Temporarily return an easy fake value
    return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
    //return (FindResult(my_result, node->getData()));
}

} // end of namespace memory
} // end of namespace datasrc
} // end of namespace isc
