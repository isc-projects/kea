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

// Note: map and utility (for 'pair') are for temporary workaround.
// we'll soon replace them with built-in intelligent backend structure. 
#include <map>
#include <utility>

#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/zonetable.h>

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

// This is a temporary, inefficient implementation using std::map and handmade
// iteration to realize longest match.

struct ZoneTable::ZoneTableImpl {
    typedef map<Name, ZonePtr> ZoneMap;
    typedef pair<Name, ZonePtr> NameAndZone;
    ZoneMap zones;
};

ZoneTable::ZoneTable() : impl_(new ZoneTableImpl)
{}

ZoneTable::~ZoneTable() {
    delete impl_;
}

result::Result
ZoneTable::addZone(ZonePtr zone) {
    if (!zone) {
        isc_throw(InvalidParameter,
                  "Null pointer is passed to ZoneTable::addZone()");
    }

    if (impl_->zones.insert(
            ZoneTableImpl::NameAndZone(zone->getOrigin(), zone)).second
        == true) {
        return (result::SUCCESS);
    } else {
        return (result::EXIST);
    }
}

result::Result
ZoneTable::removeZone(const Name& origin) {
    return (impl_->zones.erase(origin) == 1 ? result::SUCCESS :
                                              result::NOTFOUND);
}

ZoneTable::FindResult
ZoneTable::findZone(const Name& name) const {
    // Inefficient internal loop to find a longest match.
    // This will be replaced with a single call to more intelligent backend.
    for (int i = 0; i < name.getLabelCount(); ++i) {
        Name matchname(name.split(i));
        ZoneTableImpl::ZoneMap::const_iterator found =
            impl_->zones.find(matchname);
        if (found != impl_->zones.end()) {
            return (FindResult(i == 0 ? result::SUCCESS :
                               result::PARTIALMATCH, (*found).second));
        }
    }
    return (FindResult(result::NOTFOUND, ConstZonePtr()));
}
} // end of namespace datasrc
} // end of namespace isc
