// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
//
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

#include <config.h>

#include <nsas/nsas_entry_compare.h>
#include <nsas/hash_table.h>
#include <nsas/hash_deleter.h>
#include "message_cache.h"
#include "message_utility.h"
#include "cache_entry_key.h"
#include "logger.h"

namespace isc {
namespace cache {

using namespace isc::nsas;
using namespace isc::dns;
using namespace std;
using namespace MessageUtility;

MessageCache::MessageCache(const RRsetCachePtr& rrset_cache,
                           uint32_t cache_size, uint16_t message_class,
                           const RRsetCachePtr& negative_soa_cache):
    message_class_(message_class),
    rrset_cache_(rrset_cache),
    negative_soa_cache_(negative_soa_cache),
    message_table_(new NsasEntryCompare<MessageEntry>, cache_size),
    message_lru_((3 * cache_size),
                  new HashDeleter<MessageEntry>(message_table_))
{
    LOG_DEBUG(logger, DBG_TRACE_BASIC, CACHE_MESSAGES_INIT).arg(cache_size).
        arg(RRClass(message_class));
}

MessageCache::~MessageCache() {
    // Destroy all the message entries in the cache.
    message_lru_.clear();
    LOG_DEBUG(logger, DBG_TRACE_BASIC, CACHE_MESSAGES_DEINIT);
}

bool
MessageCache::lookup(const isc::dns::Name& qname,
                     const isc::dns::RRType& qtype,
                     isc::dns::Message& response)
{
    std::string entry_name = genCacheEntryName(qname, qtype);
    HashKey entry_key = HashKey(entry_name, RRClass(message_class_));
    MessageEntryPtr msg_entry = message_table_.get(entry_key);
    if(msg_entry) {
        // Check whether the message entry has expired.
       if (msg_entry->getExpireTime() > time(NULL)) {
            LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_MESSAGES_FOUND).
                arg(entry_name);
            message_lru_.touch(msg_entry);
            return (msg_entry->genMessage(time(NULL), response));
        } else {
            // message entry expires, remove it from hash table and lru list.
            LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_MESSAGES_EXPIRED).
                arg(entry_name);
            message_table_.remove(entry_key);
            message_lru_.remove(msg_entry);
            return (false);
       }
    }

    LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_MESSAGES_UNKNOWN).arg(entry_name);
    return (false);
}

bool
MessageCache::update(const Message& msg) {
    if (!canMessageBeCached(msg)){
        LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_MESSAGES_UNCACHEABLE).
            arg((*msg.beginQuestion())->getName()).
            arg((*msg.beginQuestion())->getType()).
            arg((*msg.beginQuestion())->getClass());
        return (false);
    }

    QuestionIterator iter = msg.beginQuestion();
    LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_MESSAGES_UPDATE).
        arg((*iter)->getName()).arg((*iter)->getType()).
        arg((*iter)->getClass());
    std::string entry_name = genCacheEntryName((*iter)->getName(),
                                               (*iter)->getType());
    HashKey entry_key = HashKey(entry_name, RRClass(message_class_));

    // The simplest way to update is removing the old message entry directly.
    // We have find the existed message entry, since we need to delete it
    // from lru list too.
    // TODO, but there should be a better way, since we here have to remove and
    // add the message entry, maybe there is one way to touch it once.
    MessageEntryPtr old_msg_entry = message_table_.get(entry_key);
    if (old_msg_entry) {
        LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_MESSAGES_REMOVE).
            arg((*iter)->getName()).arg((*iter)->getType()).
            arg((*iter)->getClass());
        message_lru_.remove(old_msg_entry);
    }

    MessageEntryPtr msg_entry(new MessageEntry(msg, rrset_cache_,
                                               negative_soa_cache_));
    message_lru_.add(msg_entry);
    return (message_table_.add(msg_entry, entry_key, true));
}

} // namespace cache
} // namespace isc

