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
#include <algorithm>

using namespace isc::dns;
using namespace std;

namespace isc {
namespace cache {

RecursorCache::RecursorCache() {
    uint16_t klass = 1; // class 'IN'
    class_supported_.push_back(klass);
    local_zone_data_[klass] = LocalZoneDataPtr(new LocalZoneData(klass));
    rrsets_cache_[klass] = RRsetCachePtr(new RRsetCache(RRSET_CACHE_DEFAULT_SIZE, klass));
    messages_cache_[klass] = MessageCachePtr(new MessageCache(rrsets_cache_[klass],
                                                        MESSAGE_CACHE_DEFAULT_SIZE,
                                                        klass));
}

RecursorCache::RecursorCache(std::vector<CacheSizeInfo> caches_size) {
    uint32_t index = 0;
    uint32_t size = caches_size.size();
    for (; index < size; ++index) {
        CacheSizeInfo* infop = &caches_size[index];
        uint16_t klass = infop->klass;
        class_supported_.push_back(klass);
        // TODO We should find one way to load local zone data.
        local_zone_data_[klass] = LocalZoneDataPtr(new LocalZoneData(klass));
        rrsets_cache_[klass] = RRsetCachePtr(new
                                     RRsetCache(infop->rrset_cache_size, klass));
        messages_cache_[klass] = MessageCachePtr(new MessageCache(rrsets_cache_[klass],
                                                      infop->message_cache_size,
                                                      klass));
    }

    // Sort the vector, so that binary_find can be used.
    sort(class_supported_.begin(), class_supported_.end());
}

bool
RecursorCache::classIsSupported(uint16_t klass) const {
    return binary_search(class_supported_.begin(),
                         class_supported_.end(), klass);
}

bool
RecursorCache::lookup(const isc::dns::Name& qname,
               const isc::dns::RRType& qtype,
               const isc::dns::RRClass& qclass,
               isc::dns::Message& response) const
{
    uint16_t class_code = qclass.getCode();
    if (!classIsSupported(class_code)) {
        return false;
    }

    // message response should has question section already.
    if (response.beginQuestion() == response.endQuestion()) {
        isc_throw(MessageNoQuestionSection, "Message has no question section");
    }

    // First, query in local zone, if the rrset(qname, qtype, qclass) can be
    // found in local zone, generated reply message with only the rrset in
    // answer section.
    RRsetPtr rrset_ptr = (local_zone_data_[class_code])->lookup(qname, qtype);
    if (rrset_ptr) {
        response.addRRset(Message::SECTION_ANSWER, rrset_ptr);
        return true;
    }

    // Search in class-specific message cache.
    return messages_cache_[class_code]->lookup(qname, qtype, response);
}

isc::dns::RRsetPtr
RecursorCache::lookup(const isc::dns::Name& qname,
               const isc::dns::RRType& qtype,
               const isc::dns::RRClass& qclass) const
{
    uint16_t klass = qclass.getCode();
    if (!classIsSupported(klass)) {
        return RRsetPtr();
    }

    // Algorithm:
    // 1. Search in local zone data first,
    // 2. Then do search in rrsets_cache_.
    RRsetPtr rrset_ptr = local_zone_data_[klass]->lookup(qname, qtype);
    if (rrset_ptr) {
        return rrset_ptr;
    } else {
        RRsetEntryPtr rrset_entry = rrsets_cache_[klass]->lookup(qname, qtype);
        if (rrset_entry) {
            return rrset_entry->getRRset();
        } else {
            return RRsetPtr();
        }
    }
}

isc::dns::RRsetPtr
RecursorCache::lookupClosestRRset(const isc::dns::Name& qname,
                                  const isc::dns::RRType& qtype,
                                  const isc::dns::RRClass& qclass) const
{
    unsigned int count = qname.getLabelCount();
    unsigned int level = 0;
    while(level < count) {
        Name close_name = qname.split(level);
        RRsetPtr rrset_ptr = lookup(close_name, qtype, qclass);
        if (rrset_ptr) {
            return rrset_ptr;
        } else {
            ++level;
        }
    }

    return RRsetPtr();
}

bool
RecursorCache::update(const isc::dns::Message& msg) {
    QuestionIterator iter = msg.beginQuestion();
    uint16_t klass = (*iter)->getClass().getCode();
    if (!classIsSupported(klass)) {
        return false;
    }

    return messages_cache_[klass]->update(msg);
}

bool
RecursorCache::updateRRsetCache(const isc::dns::ConstRRsetPtr rrset_ptr,
                                RRsetCachePtr rrset_cache_ptr)
{
    RRsetTrustLevel level;
    string typestr = rrset_ptr->getType().toText();
    if (typestr == "A" || typestr == "AAAA") {
        level = RRSET_TRUST_PRIM_GLUE;
    } else {
        level = RRSET_TRUST_PRIM_ZONE_NONGLUE;
    }

    rrset_cache_ptr->update((*rrset_ptr.get()), level);
    return true;
}

bool
RecursorCache::update(const isc::dns::ConstRRsetPtr rrset_ptr) {
    uint16_t klass = rrset_ptr->getClass().getCode();
    if (!classIsSupported(klass)) {
        return false;
    }

    // First update local zone, then update rrset cache.
    local_zone_data_[klass]->update((*rrset_ptr.get()));
    updateRRsetCache(rrset_ptr, rrsets_cache_[klass]);
    return true;
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

