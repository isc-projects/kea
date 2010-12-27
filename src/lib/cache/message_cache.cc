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

#include "message_cache.h"
#include <nsas/nsas_entry_compare.h>
#include <nsas/hash_table.h>
#include <nsas/hash_deleter.h>

using namespace isc::nsas;

namespace isc {
namespace cache {

MessageCache::MessageCache(boost::shared_ptr<RRsetCache> rrset_cache,
    uint32_t cache_size):
    rrset_cache_(rrset_cache),
    message_table_(new NsasEntryCompare<MessageEntry>, cache_size),
    message_lru_((3 * cache_size),
                  new HashDeleter<MessageEntry>(message_table_))

{
}
    
bool
MessageCache::lookUp(const isc::dns::Name&,
       const isc::dns::RRType&,
       const isc::dns::RRClass&,
       isc::dns::Message& )
{
    return true;
}

bool
MessageCache::update(const isc::dns::Message&) {
    return true;
}

void
MessageCache::dump(const std::string&) {
}

void
MessageCache::load(const std::string&) {
}

bool
MessageCache::resize(uint32_t) {
    return true;
}

} // namespace cache
} // namespace isc

