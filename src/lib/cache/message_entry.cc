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

#include <limits>
#include <dns/message.h>
#include <nsas/nsas_entry.h>
#include <nsas/fetchable.h>
#include "message_entry.h"
#include "rrset_cache.h"

using namespace isc::dns;
using namespace std;

namespace isc {
namespace cache {

static uint32_t MAX_UINT32 = numeric_limits<uint32_t>::max();    

MessageEntry::MessageEntry(const isc::dns::Message& msg,
                           boost::shared_ptr<RRsetCache> rrset_cache):
    rrset_cache_(rrset_cache)
{
    initMessageEntry(msg);
}
    
bool
MessageEntry::genMessage(const time_t&,
                         isc::dns::Message&)
{
    //TODO, generate message according the query header flags.
    return true;
}

RRsetTrustLevel
MessageEntry::getRRsetTrustLevel(const Message& message,
                   const isc::dns::RRset&,
                   const isc::dns::Message::Section& section) 
{
    bool aa = message.getHeaderFlag(Message::HEADERFLAG_AA);
    switch(section) {
        case Message::SECTION_ANSWER: {
            if (aa) {
                //TODO, according RFC2181 section 5.4.1, only the record 
                // describing that ailas is necessarily authoritative.
                return RRSET_TRUST_ANSWER_AA;
            } else {
                return RRSET_TRUST_ANSWER_NONAA;
            }
            break;
        }
        
        case Message::SECTION_AUTHORITY: {
            if (aa) {
                return RRSET_TRUST_AUTHORITY_AA;
            } else {
                return RRSET_TRUST_AUTHORITY_NONAA;
            }
            break;
        }

        case Message::SECTION_ADDITIONAL: {
            if (aa) {
                return RRSET_TRUST_ADDITIONAL_AA;
            } else {
                return RRSET_TRUST_ADDITIONAL_NONAA;
            }
            break;
        }

        default:
            return RRSET_TRUST_DEFAULT;
    }
}

void
MessageEntry::parseSection(const isc::dns::Message& msg,
                           const Message::Section& section,
                           uint32_t& smaller_ttl)
{
    RRsetIterator iter;
    for (iter = msg.beginSection(section);
         iter != msg.endSection(section);
         ++iter) {
        // Add the rrset entry to rrset_cache or update the existed 
        // rrset entry if the new one is more authoritative.
        //TODO set proper rrset trust level.
        RRsetPtr rrset_ptr = *iter;
        RRsetTrustLevel level = getRRsetTrustLevel(msg, *rrset_ptr, section);
        RRsetEntryPtr rrset_entry = rrset_cache_->update(*rrset_ptr, level);
        rrsets_.push_back(rrset_entry);
        
        uint32_t rrset_ttl = rrset_entry->getTTL();
        if (smaller_ttl > rrset_ttl) {
            smaller_ttl = rrset_ttl;
        }
    }
}

void
MessageEntry::initMessageEntry(const isc::dns::Message& msg) {
    query_count_ = msg.getRRCount(Message::SECTION_QUESTION);
    answer_count_ = msg.getRRCount(Message::SECTION_ANSWER);
    authority_count_ = msg.getRRCount(Message::SECTION_AUTHORITY);
    additional_count_ = msg.getRRCount(Message::SECTION_ADDITIONAL);
    
    //TODO how to cache the header?
    // query_header 

    // We only cache the first question in question section.
    // TODO, do we need to support muptiple questions?
    QuestionIterator iter = msg.beginQuestion();
    query_name_ = (*iter)->getName().toText();
    query_type_ = (*iter)->getType().getCode();
    query_class_ = (*iter)->getClass().getCode();
    
    uint32_t min_ttl = MAX_UINT32;
    parseSection(msg, Message::SECTION_ANSWER, min_ttl);
    parseSection(msg, Message::SECTION_AUTHORITY, min_ttl);
    parseSection(msg, Message::SECTION_ADDITIONAL, min_ttl);

    expire_time_ = time(NULL) + min_ttl;
}

HashKey
MessageEntry::hashKey() const {
    CacheEntryKey keydata = genCacheEntryKey(query_name_, query_type_);
    return HashKey(keydata.first, keydata.second, RRClass(query_class_));
}

} // namespace cache
} // namespace isc


