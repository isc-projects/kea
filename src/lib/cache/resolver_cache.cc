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

#include <config.h>

#include "resolver_cache.h"
#include "dns/message.h"
#include "rrset_cache.h"
#include <string>
#include <algorithm>

using namespace isc::dns;
using namespace std;

namespace isc {
namespace cache {

ResolverClassCache::ResolverClassCache(const RRClass& cache_class) :
    cache_class_(cache_class)
{
    local_zone_data_ = LocalZoneDataPtr(new LocalZoneData(cache_class_.getCode()));
    rrsets_cache_ = RRsetCachePtr(new RRsetCache(RRSET_CACHE_DEFAULT_SIZE,
                                                 cache_class_.getCode()));
    messages_cache_ = MessageCachePtr(new MessageCache(rrsets_cache_,
                                      MESSAGE_CACHE_DEFAULT_SIZE,
                                      cache_class_.getCode()));
}

ResolverClassCache::ResolverClassCache(CacheSizeInfo cache_info) :
    cache_class_(cache_info.cclass)
{
    uint16_t klass = cache_class_.getCode();
    // TODO We should find one way to load local zone data.
    local_zone_data_ = LocalZoneDataPtr(new LocalZoneData(klass));
    rrsets_cache_ = RRsetCachePtr(new
                        RRsetCache(cache_info.rrset_cache_size, klass));
    messages_cache_ = MessageCachePtr(new MessageCache(rrsets_cache_,
                                      cache_info.message_cache_size,
                                      klass));
}

const RRClass&
ResolverClassCache::getClass() const {
    return cache_class_;
}

bool
ResolverClassCache::lookup(const isc::dns::Name& qname,
                      const isc::dns::RRType& qtype,
                      isc::dns::Message& response) const
{
    // message response should has question section already.
    if (response.beginQuestion() == response.endQuestion()) {
        isc_throw(MessageNoQuestionSection, "Message has no question section");
    }

    // First, query in local zone, if the rrset(qname, qtype, qclass) can be
    // found in local zone, generated reply message with only the rrset in
    // answer section.
    RRsetPtr rrset_ptr = local_zone_data_->lookup(qname, qtype);
    if (rrset_ptr) {
        response.addRRset(Message::SECTION_ANSWER, rrset_ptr);
        return (true);
    }

    // Search in class-specific message cache.
    return (messages_cache_->lookup(qname, qtype, response));
}

isc::dns::RRsetPtr
ResolverClassCache::lookup(const isc::dns::Name& qname,
               const isc::dns::RRType& qtype) const
{
    // Algorithm:
    // 1. Search in local zone data first,
    // 2. Then do search in rrsets_cache_.
    RRsetPtr rrset_ptr = local_zone_data_->lookup(qname, qtype);
    if (rrset_ptr) {
        return (rrset_ptr);
    } else {
        RRsetEntryPtr rrset_entry = rrsets_cache_->lookup(qname, qtype);
        if (rrset_entry) {
            return (rrset_entry->getRRset());
        } else {
            return (RRsetPtr());
        }
    }
}

bool
ResolverClassCache::update(const isc::dns::Message& msg) {
    return (messages_cache_->update(msg));
}

bool
ResolverClassCache::updateRRsetCache(const isc::dns::ConstRRsetPtr rrset_ptr,
                                RRsetCachePtr rrset_cache_ptr)
{
    RRsetTrustLevel level;
    if (rrset_ptr->getType() == RRType::A() || 
        rrset_ptr->getType() == RRType::AAAA()) {
        level = RRSET_TRUST_PRIM_GLUE;
    } else {
        level = RRSET_TRUST_PRIM_ZONE_NONGLUE;
    }

    rrset_cache_ptr->update((*rrset_ptr.get()), level);
    return (true);
}

bool
ResolverClassCache::update(const isc::dns::ConstRRsetPtr rrset_ptr) {
    // First update local zone, then update rrset cache.
    local_zone_data_->update((*rrset_ptr.get()));
    updateRRsetCache(rrset_ptr, rrsets_cache_);
    return (true);
}


ResolverCache::ResolverCache()
{
    class_caches_.push_back(new ResolverClassCache(RRClass::IN()));
}

ResolverCache::ResolverCache(std::vector<CacheSizeInfo> caches_info)
{
    for (int i = 0; i < caches_info.size(); ++i) {
        class_caches_.push_back(new ResolverClassCache(caches_info[i]));
    }
}

ResolverCache::~ResolverCache()
{
    for (int i = 0; i < class_caches_.size(); ++i) {
        delete class_caches_[i];
    }
}

bool
ResolverCache::lookup(const isc::dns::Name& qname,
                      const isc::dns::RRType& qtype,
                      const isc::dns::RRClass& qclass,
                      isc::dns::Message& response) const
{
    ResolverClassCache* cc = getClassCache(qclass);
    if (cc) {
        return (cc->lookup(qname, qtype, response));
    } else {
        return (false);
    }
}

isc::dns::RRsetPtr
ResolverCache::lookup(const isc::dns::Name& qname,
               const isc::dns::RRType& qtype,
               const isc::dns::RRClass& qclass) const
{
    ResolverClassCache* cc = getClassCache(qclass);
    if (cc) {
        return (cc->lookup(qname, qtype));
    } else {
        return (RRsetPtr());
    }
}

isc::dns::RRsetPtr
ResolverCache::lookupClosestRRset(const isc::dns::Name& qname,
                                  const isc::dns::RRType& qtype,
                                  const isc::dns::RRClass& qclass) const
{
    ResolverClassCache* cc = getClassCache(qclass);
    if (cc) {
        unsigned int count = qname.getLabelCount();
        unsigned int level = 0;
        while(level < count) {
            Name close_name = qname.split(level);
            RRsetPtr rrset_ptr = cc->lookup(close_name, qtype);
            if (rrset_ptr) {
                return (rrset_ptr);
            } else {
                ++level;
            }
        }
    }

    return (RRsetPtr());
}

bool
ResolverCache::update(const isc::dns::Message& msg) {
    
    QuestionIterator iter = msg.beginQuestion();
    ResolverClassCache* cc = getClassCache((*iter)->getClass());
    if (cc) {
        return (cc->update(msg));
    } else {
        return (false);
    }
}

bool
ResolverCache::update(const isc::dns::ConstRRsetPtr rrset_ptr) {
    ResolverClassCache* cc = getClassCache(rrset_ptr->getClass());
    if (cc) {
        return (cc->update(rrset_ptr));
    } else {
        return (false);
    }
}

void
ResolverCache::dump(const std::string&) {
    //TODO
}

void
ResolverCache::load(const std::string&) {
    //TODO
}

ResolverClassCache*
ResolverCache::getClassCache(const isc::dns::RRClass& cache_class) const {
    for (int i = 0; i < class_caches_.size(); ++i) {
        if (class_caches_[i]->getClass() == cache_class) {
            return class_caches_[i];
        }
    }
    return NULL;
}

} // namespace cache
} // namespace isc

