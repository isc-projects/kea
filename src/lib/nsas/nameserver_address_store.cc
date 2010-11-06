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

// $Id$

#include <boost/shared_ptr.hpp>

#include <config.h>

#include "hash_deleter.h"
#include "nsas_entry_compare.h"
#include "nameserver_entry.h"
#include "nameserver_address_store.h"
#include "zone_entry.h"

using namespace isc::dns;
using namespace std;
using namespace boost;

namespace isc {
namespace nsas {

// Constructor.
//
// The LRU lists are set equal to three times the size of the respective
// hash table, on the assumption that three elements is the longest linear
// search we want to do when looking up names in the hash table.
NameserverAddressStore::NameserverAddressStore(ResolverInterface& resolver,
    uint32_t zonehashsize, uint32_t nshashsize) :
    zone_hash_(new NsasEntryCompare<ZoneEntry>, zonehashsize),
    nameserver_hash_(new NsasEntryCompare<NameserverEntry>, nshashsize),
    zone_lru_((3 * zonehashsize), new HashDeleter<ZoneEntry>(zone_hash_)),
    nameserver_lru_((3 * nshashsize), new HashDeleter<NameserverEntry>(
        nameserver_hash_)),
    resolver_(resolver)
{
}

namespace {

// Often used types
typedef shared_ptr<ZoneEntry> ZonePtr;
typedef shared_ptr<NameserverEntry> NameserverPtr;
typedef shared_ptr<AddressRequestCallback> CallbackPtr;

// One function to call new on both ZoneEntry and NameserverEntry
template<class T>
shared_ptr<T>
newT(const std::string& zone, uint16_t class_code) {
    return (shared_ptr<T>(new T(zone, class_code)));
}

}

void
NameserverAddressStore::lookup(const std::string& zone, uint16_t class_code,
    const AbstractRRset& authority, const vector<AbstractRRset>& ,
    CallbackPtr callback)
{
    // Try to look up the entry
    pair<bool, ZonePtr> zone_lookup(
        zone_hash_.getOrAdd(HashKey(zone, class_code),
        bind(newT<ZoneEntry>, zone, class_code)));
    ZonePtr zone_ptr(zone_lookup.second);
    if (zone_lookup.first) { // New value
        zone_lru_.add(zone_ptr);
        // Sanitize the authority section and put the data there
        if (authority.getClass().getCode() != class_code) {
            isc_throw(InconsistentZone,
                "Authority section is for different class, expected: " <<
                RRClass(class_code).toText() << ", got: " <<
                authority.getClass().toText());
        }
        if (authority.getName() != Name(zone)) {
            isc_throw(InconsistentZone,
                "Authority section is for different zone, expected: " <<
                zone << ", got: " << authority.getName().toText());
        }
        if (authority.getType() != RRType::NS()) {
            isc_throw(NotNS, "Authority section with non-NS RR type: " <<
                authority.getType().toText());
        }
    } else { // Was already here
        zone_lru_.touch(zone_ptr);
        // TODO Do we update the TTL and nameservers here?
    }
    zone_ptr->addCallback(callback);
    processZone(zone_ptr);
}

void NameserverAddressStore::processZone(ZonePtr) {

}

} // namespace nsas
} // namespace isc
