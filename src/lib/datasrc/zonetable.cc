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

#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/zonetable.h>
#include <datasrc/rbtree.h>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace datasrc {

struct MemoryZone::MemoryZoneImpl {
    MemoryZoneImpl(const RRClass& zone_class, const Name& origin) :
        zone_class_(zone_class), origin_(origin)
    {}
    RRClass zone_class_;
    Name origin_;
};

MemoryZone::MemoryZone(const RRClass& zone_class, const Name& origin) :
    impl_(new MemoryZoneImpl(zone_class, origin))
{
}

MemoryZone::~MemoryZone() {
    delete impl_;
}

const Name&
MemoryZone::getOrigin() const {
    return (impl_->origin_);
}

const RRClass&
MemoryZone::getClass() const {
    return (impl_->zone_class_);
}

Zone::FindResult
MemoryZone::find(const Name&, const RRType&) const {
    // This is a tentative implementation that always returns NXDOMAIN.
    return (FindResult(NXDOMAIN, RRsetPtr()));
}

/// \short Private data and implementation of ZoneTable
struct ZoneTable::ZoneTableImpl {
    // Type aliases to make it shorter
    typedef RBTree<Zone> ZoneTree;
    typedef RBNode<Zone> ZoneNode;
    // The actual storage
    ZoneTree zones_;

    /*
     * The implementation methods are here and just wrap-called in the
     * ZoneTable. We have variables locally (without impl_->), have
     * type aliases, etc. And they will get inlined anyway.
     */

    // Implementation of ZoneTable::addZone
    result::Result addZone(ZonePtr zone) {
        // Sanity check
        if (!zone) {
            isc_throw(InvalidParameter,
                      "Null pointer is passed to ZoneTable::addZone()");
        }

        // Get the node where we put the zone
        ZoneNode* node(NULL);
        switch (zones_.insert(zone->getOrigin(), &node)) {
            // This is OK
            case ZoneTree::SUCCEED:
            case ZoneTree::ALREADYEXIST:
                break;
            // Can Not Happen
            default:
                assert(0);
        }
        // Can Not Happen
        assert(node);

        // Is it empty? We either just created it or it might be nonterminal
        if (node->isEmpty()) {
            node->setData(zone);
            return (result::SUCCESS);
        } else { // There's something there already
            return (result::EXIST);
        }
    }

    // Implementation of ZoneTable::findZone
    ZoneTable::FindResult findZone(const Name& name) const {
        ZoneNode *node(NULL);
        result::Result my_result;

        // Translate the return codes
        switch (zones_.find(name, &node)) {
            case ZoneTree::EXACTMATCH:
                my_result = result::SUCCESS;
                break;
            case ZoneTree::PARTIALMATCH:
                my_result = result::PARTIALMATCH;
                break;
            // We have no data there, so translate the pointer to NULL as well
            case ZoneTree::NOTFOUND:
                return (FindResult(result::NOTFOUND, ConstZonePtr()));
            // Can Not Happen
            default:
                assert(0);
        }

        // Can Not Happen (remember, NOTFOUND is handled)
        assert(node);

        return (FindResult(my_result, node->getData()));
    }
};

ZoneTable::ZoneTable() : impl_(new ZoneTableImpl)
{}

ZoneTable::~ZoneTable() {
    delete impl_;
}

result::Result
ZoneTable::addZone(ZonePtr zone) {
    return (impl_->addZone(zone));
}

result::Result
ZoneTable::removeZone(const Name&) {
    // TODO Implement
    assert(0);
}

ZoneTable::FindResult
ZoneTable::findZone(const Name& name) const {
    return (impl_->findZone(name));
}

} // end of namespace datasrc
} // end of namespace isc
