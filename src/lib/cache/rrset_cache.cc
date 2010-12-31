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

#include <string>
#include "rrset_cache.h"
#include <nsas/nsas_entry_compare.h>
#include <nsas/hash_table.h>
#include <nsas/hash_deleter.h>

using namespace isc::nsas;
using namespace isc::dns;

namespace isc {
namespace cache {

RRsetCache::RRsetCache(uint32_t cache_size):
    rrset_table_(new NsasEntryCompare<RRsetEntry>, cache_size),
    rrset_lru_((3 * cache_size),
                  new HashDeleter<RRsetEntry>(rrset_table_))

{
}

RRsetEntryPtr
RRsetCache::lookup(const isc::dns::Name& qname,
                   const isc::dns::RRType& qtype)
{
    CacheEntryKey keydata = genCacheEntryKey(qname, qtype);
    //TODO, HashKey need to be refactored, since we don't need query class
    // as the parameters.
    RRsetEntryPtr entry_ptr = rrset_table_.get(HashKey(
           keydata.first, keydata.second, RRClass(class_)));

    //If the rrset entry has expired, return NULL.
    if(time(NULL) > entry_ptr->getExpireTime()) {
        return RRsetEntryPtr();
    }
    return entry_ptr;
}

RRsetEntryPtr
RRsetCache::update(const isc::dns::RRset& rrset, const RRsetTrustLevel& level) {
    // lookup first
    RRsetEntryPtr entry_ptr = lookup(rrset.getName(), rrset.getType());
    if(!entry_ptr) {
        // rrset entry doesn't exist, create one rrset entry for the rrset
        // and add it directly.
        entry_ptr.reset(new RRsetEntry(rrset, level));
        // Replace the expired rrset entry if it exists.
        rrset_table_.add(entry_ptr, entry_ptr->hashKey(), true);
        //TODO , lru list touch.
        return entry_ptr;
    } else {
        // there is one rrset entry in the cache, need to check whether
        // the new rrset is more authoritative.
        if (entry_ptr->getTrustLevel() > level) {
            // existed rrset entry is more authoritative, do nothing,
            // just return it.
            //TODO, lru list touch
            return entry_ptr;
        } else {
            HashKey key = entry_ptr->hashKey();
            rrset_table_.remove(key);
            entry_ptr.reset(new RRsetEntry(rrset, level));
            //TODO, lru list touch.
            // Replace the expired rrset entry if it exists.
            rrset_table_.add(entry_ptr, key, true);
            return entry_ptr;
        }
    }
}

HashKey
RRsetCache::getEntryHashKey(const Name& name, const RRType& type) const 
{
    CacheEntryKey keydata = genCacheEntryKey(name, type);
    return HashKey(keydata.first, keydata.second, RRClass(class_));
}

void
RRsetCache::dump(const std::string&) {
    //TODO
}

void
RRsetCache::load(const std::string&) {
    //TODO
}

bool
RRsetCache::resize(uint32_t) {
    //TODO
    return true;
}

} // namespace cache
} // namespace isc

