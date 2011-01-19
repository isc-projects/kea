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

#include <nsas/nsas_entry_compare.h>
#include <nsas/hash_table.h>
#include <nsas/hash_deleter.h>
#include "message_cache.h"
#include "cache_entry_key.h"

using namespace isc::nsas;
using namespace isc::dns;
using namespace std;

namespace isc {
namespace cache {

MessageCache::MessageCache(boost::shared_ptr<RRsetCache> rrset_cache,
    uint32_t cache_size, uint16_t message_class):
    message_class_(message_class),
    rrset_cache_(rrset_cache),
    message_table_(new NsasEntryCompare<MessageEntry>, cache_size),
    message_lru_((3 * cache_size),
                  new HashDeleter<MessageEntry>(message_table_))
{
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
        message_lru_.touch(msg_entry);
        return msg_entry->genMessage(time(NULL), response);
    }

    return false;
}

bool
MessageCache::update(const Message& msg) {
    QuestionIterator iter = msg.beginQuestion();
    std::string entry_name = genCacheEntryName((*iter)->getName(), (*iter)->getType());
    HashKey entry_key = HashKey(entry_name, RRClass(message_class_));
    
    // The simplest way to update is removing the old message entry directly.
    // We have find the existed message entry, since we need to delete it
    // from lru list too.
    // TODO, but there should be a better way, since we here have to remove and
    // add the message entry, maybe there is one way to touch it once.
    MessageEntryPtr old_msg_entry = message_table_.get(entry_key);
    if (old_msg_entry) {
        message_table_.remove(entry_key);
        message_lru_.remove(old_msg_entry);
    }

    MessageEntryPtr msg_entry(new MessageEntry(msg, rrset_cache_));
    message_lru_.add(msg_entry); 
    return message_table_.add(msg_entry, entry_key, true); 
}

void
MessageCache::dump(const std::string&) {
    //TODO
}

void
MessageCache::load(const std::string&) {
    //TODO
}

bool
MessageCache::resize(uint32_t) {
    //TODO
    return true;
}

} // namespace cache
} // namespace isc

