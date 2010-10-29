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

struct Zone::ZoneImpl {
    ZoneImpl(const RRClass& zone_class, const Name& origin) :
        zone_class_(zone_class), origin_(origin)
    {}
    RRClass zone_class_;
    Name origin_;
};

Zone::Zone(const RRClass& zone_class, const Name& origin) : impl_(NULL) {
    impl_ = new ZoneImpl(zone_class, origin);
}

Zone::~Zone() {
    delete impl_;
}

const Name&
Zone::getOrigin() const {
    return (impl_->origin_);
}

const RRClass&
Zone::getClass() const {
    return (impl_->zone_class_);
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

ZoneTable::Result
ZoneTable::add(ZonePtr zone) {
    if (!zone) {
        isc_throw(InvalidParameter,
                  "Null pointer is passed to ZoneTable::add()");
    }

    if (impl_->zones.insert(
            ZoneTableImpl::NameAndZone(zone->getOrigin(), zone)).second
        == true) {
        return (SUCCESS);
    } else {
        return (EXIST);
    }
}

ZoneTable::Result
ZoneTable::remove(const Name& origin) {
    return (impl_->zones.erase(origin) == 1 ? SUCCESS : NOTFOUND);
}

ZoneTable::FindResult
ZoneTable::find(const Name& name) const {
    Name qname(name);

    // Inefficient internal loop to find a longest match.
    // This will be replaced with a single call to more intelligent backend.
    for (int i = 0; i < name.getLabelCount(); ++i) {
        Name matchname(name.split(i));
        ZoneTableImpl::ZoneMap::const_iterator found =
            impl_->zones.find(matchname);
        if (found != impl_->zones.end()) {
            return (FindResult(i == 0 ? SUCCESS : PARTIALMATCH,
                               (*found).second.get()));
        }
    }
    return (FindResult(NOTFOUND, NULL));
}
} // end of namespace datasrc
} // end of namespace isc
