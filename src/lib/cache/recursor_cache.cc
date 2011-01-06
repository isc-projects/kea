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

#include "recursor_cache.h"
#include "dns/message.h"
#include "rrset_cache.h"
#include <string>

using namespace isc::dns;
using namespace std; 

namespace isc {
namespace cache {

RecursorCache::RecursorCache(std::vector<CacheSizeInfo> caches_size) {
    uint32_t index = 0;
    uint32_t size = caches_size.size();
    for (; index < size; index++) {
        CacheSizeInfo* infop = &caches_size[index];
        uint16_t klass = infop->class_;
        rrsets_cache1_[klass] = RRsetCachePtr(new 
                                     RRsetCache(infop->rrset_cache_size, klass));
        rrsets_cache2_[klass] = RRsetCachePtr(new 
                                     RRsetCache(infop->rrset_cache_size, klass));
        messages_cache_[klass] = MessageCachePtr(new MessageCache(rrsets_cache2_[klass], 
                                                      infop->message_cache_size, 
                                                      klass));
    }
}

bool
RecursorCache::lookup(const isc::dns::Name& qname, 
               const isc::dns::RRType& qtype,
               const isc::dns::RRClass& qclass,
               isc::dns::Message& response) const
{
    // First, query in rrsets_cache1_, if the rrset(qname, qtype, qclass) can be 
    // found in rrsets_cache1_, generated reply message with only the rrset in 
    // answer section.
    RRsetCacheMap::const_iterator cache_iter = rrsets_cache1_.find(qclass.getCode());
    if (cache_iter != rrsets_cache1_.end()) {
        RRsetEntryPtr rrset_entry = cache_iter->second->lookup(qname, qtype);
        if (rrset_entry) {
            boost::shared_ptr<isc::dns::RRset> rrset_ptr = rrset_entry->genRRset();
            response.addRRset(Message::SECTION_ANSWER, rrset_ptr);
        }
    }

    // Search in class-specific message cache.
    MessageCacheMap::const_iterator iter = messages_cache_.find(qclass.getCode());
    if (iter == messages_cache_.end()) {
        // Can't find the class-specific message cache, return false.
        return false;
    } else {
        return iter->second->lookup(qname, qtype, response);
    }
}

isc::dns::RRsetPtr
RecursorCache::lookup_in_rrset_cache(const isc::dns::Name& qname, 
                      const isc::dns::RRType& qtype,
                      const isc::dns::RRClass& qclass,
                      const RRsetCacheMap& rrsets_cache) const
{
    RRsetCacheMap::const_iterator cache_iter = rrsets_cache.find(qclass.getCode());
    if (cache_iter != rrsets_cache.end()) {
        RRsetEntryPtr rrset_entry = cache_iter->second->lookup(qname, qtype);
        if (rrset_entry) {
            return rrset_entry->genRRset();
        }
    }

    // Can't find the rrset in specified rrset cache, return NULL.
    return RRsetPtr();
}

isc::dns::RRsetPtr
RecursorCache::lookup(const isc::dns::Name& qname, 
               const isc::dns::RRType& qtype,
               const isc::dns::RRClass& qclass) const
{
    // Algorithm:
    // 1. Search in rrsets_cache1_ first, 
    // 2. Then do search in rrsets_cache2_.
    RRsetPtr rrset_ptr = lookup_in_rrset_cache(qname, qtype, qclass, rrsets_cache1_);
    if (rrset_ptr) {
        return rrset_ptr;
    } else {
        rrset_ptr = lookup_in_rrset_cache(qname, qtype, qclass, rrsets_cache2_);
    }

    return rrset_ptr;
}

bool
RecursorCache::update(const isc::dns::Message& msg) {
    QuestionIterator iter = msg.beginQuestion();
    MessageCacheMap::iterator cache_iter = messages_cache_.find((*iter)->getClass().getCode());
    if (cache_iter == messages_cache_.end()) {
        // The message is not allowed to cached.
        return false;
    } else {
        return cache_iter->second->update(msg);
    }
}

bool
RecursorCache::updateRRsetCache(const isc::dns::RRset& rrset,
                                RRsetCacheMap& rrset_cache_map) 
{
    uint16_t klass = rrset.getClass().getCode();
    RRsetCacheMap::iterator cache_iter = rrset_cache_map.find(klass);
    if (cache_iter == rrset_cache_map.end()) {
        // The rrset is not allowed to be cached.
        return false;
    } else {
        RRsetTrustLevel level;
        string typestr = rrset.getType().toText();
        if (typestr == "A" || typestr == "AAAA") {
            level = RRSET_TRUST_PRIM_GLUE;
        } else {
            level = RRSET_TRUST_PRIM_ZONE_NONGLUE;
        }

        cache_iter->second->update(rrset, level);
    }
    return true;
}

bool
RecursorCache::update(const isc::dns::RRset& rrset) {
    if (!updateRRsetCache(rrset, rrsets_cache1_)) {
        return false;
    }

    return updateRRsetCache(rrset, rrsets_cache2_);
}

void
RecursorCache::dump(const std::string&) {
    //TODO
}

void
RecursorCache::load(const std::string&) {
    //TODO
}

} // namespace cache
} // namespace isc

