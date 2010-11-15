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
#include <boost/foreach.hpp>

#include <config.h>
#include <dns/rdataclass.h>

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

/*
 * Create a nameserver.
 * Called inside a mutex so it is filled in attomically.
 */
NameserverPtr
newNs(const std::string* name, uint16_t class_code,
    const vector<AbstractRRset>*)
{
    return (NameserverPtr(new NameserverEntry(*name, class_code)));
}

/*
 * Create a zone entry.
 * It is called inside the mutex so it is called and filled in attomically.
 * Pointers are used instead of references, because with references,
 * boost::bind copyes.
 */
ZonePtr
newZone(const std::string* zone, uint16_t class_code,
   const AbstractRRset* authority, const vector<AbstractRRset>* additional,
   HashTable<NameserverEntry>* ns_hash, LruList<NameserverEntry>* ns_lru)
{
    ZonePtr zone_ptr(new ZoneEntry(*zone, class_code));
    // Sanitize the authority section and put the data there
    if (authority->getClass().getCode() != class_code) {
        isc_throw(InconsistentZone,
            "Authority section is for different class, expected: " <<
            RRClass(class_code).toText() << ", got: " <<
            authority->getClass().toText());
    }
    if (authority->getName() != Name(*zone)) {
        isc_throw(InconsistentZone,
            "Authority section is for different zone, expected: " <<
            zone << ", got: " << authority->getName().toText());
    }
    if (authority->getType() != RRType::NS()) {
        isc_throw(NotNS, "Authority section with non-NS RR type: " <<
            authority->getType().toText());
    }
    // Make sure the name servers exist
    RdataIteratorPtr ns(authority->getRdataIterator());
    for (ns->first(); !ns->isLast(); ns->next()) {
        Name ns_name(dynamic_cast<const rdata::generic::NS&>(
                    ns->getCurrent()).getNSName());
        string ns_name_str(ns_name.toText());
        pair<bool, NameserverPtr> ns_lookup(
                ns_hash->getOrAdd(HashKey(ns_name_str, class_code),
                bind(newNs, &ns_name_str, class_code, additional)));
        if (ns_lookup.first) { // Is it a new nameserver?
            ns_lru->add(ns_lookup.second);
        } else {
            ns_lru->touch(ns_lookup.second);
        }
        zone_ptr->nameserverAdd(ns_lookup.second);
    }

    return zone_ptr;
}

}

void
NameserverAddressStore::lookup(const std::string& zone, uint16_t class_code,
    const AbstractRRset& authority, const vector<AbstractRRset>& additional,
    CallbackPtr callback)
{
    // Try to look up the entry, or create and fill it with initial data
    pair<bool, ZonePtr> zone_lookup(
        zone_hash_.getOrAdd(HashKey(zone, class_code),
        bind(newZone, &zone, class_code, &authority, &additional,
        &nameserver_hash_, &nameserver_lru_)));
    ZonePtr zone_ptr(zone_lookup.second);
    if (zone_lookup.first) { // New value
        zone_lru_.add(zone_ptr);
    } else { // Was already here
        // FIXME Check the TTL, delete and retry if outdated
        zone_lru_.touch(zone_ptr);
    }
    zone_ptr->addCallback(callback);
    processZone(zone_ptr);
}

namespace {

asiolink::IOAddress
chooseAddress(const NameserverEntry::AddressVector& addresses) {
    // TODO Something little bit more inteligent than just picking the first
    // one
    assert(!addresses.empty()); // Should not be called with empty list
    return addresses.front().getAddress();
}

}

void NameserverAddressStore::processZone(ZonePtr zone) {
    // Addresses of existing nameservers
    NameserverEntry::AddressVector addresses;
    // Current state
    Fetchable::State state;
    {
        // Nameservers we can still ask for their IP address
        vector<NameserverPtr> not_asked;
        // Are there any in-progress nameservers?
        bool pending(false);
        /**
         * This is inside a block so we can unlock the zone with nameservers
         * after we get all information from it. We do not need to keep the
         * lock on the nameservers when we run callbacks.
         */
        ZoneEntry::Lock lock(zone->getLock());

        if (zone->getState() != Fetchable::UNREACHABLE) {
            // Look into all the nameservers

            // FIXME This completely ignores TTLs, something shoud be done with them.
            // Maybe turn all outdated nameservers into NOT_ASKED?

            BOOST_FOREACH(NameserverPtr ns, *zone) {
                switch (ns->getState()) {
                    case Fetchable::NOT_ASKED:
                        not_asked.push_back(ns);
                        break;
                    case Fetchable::READY:
                        ns->getAddresses(addresses);
                        break;
                    case Fetchable::IN_PROGRESS:
                        pending = true;
                        break;
                    case Fetchable::UNREACHABLE:
                        // Nothing. We do not care about it.
                        break;
                }
            }
        }

        /*
         * If there is no data, noone to ask and noone to expect answer from
         * then bad luck, but this zone can't be reached.
         */
        if (not_asked.empty() && addresses.empty() && !pending) {
            zone->setState(Fetchable::UNREACHABLE);
        }

        // TODO Pick up to two not_asked ones and ask them

        state = zone->getState();
    } // Release the lock (and some other resources as a bonus)

    // If we are unreachable, tell everyone
    if (state == Fetchable::UNREACHABLE) {
        while (zone->hasCallbacks()) {
            zone->popCallback()->unreachable();
        }
    } else if (!addresses.empty()) { // Give everyone an address
        while (zone->hasCallbacks()) {
            // Get the address first, so the callback is removed after we are
            // sure there's no exception
            asiolink::IOAddress address(chooseAddress(addresses));
            zone->popCallback()->success(address);
        }
    }
    // Otherwise, we are still waiting for more info to come, let the
    // callbacks rest
}

} // namespace nsas
} // namespace isc
