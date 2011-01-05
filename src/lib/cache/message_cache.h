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

#ifndef __MESSAGE_CACHE_H
#define __MESSAGE_CACHE_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <dns/message.h>
#include "message_entry.h"
#include <nsas/hash_table.h>
#include <nsas/lru_list.h>

namespace isc {
namespace cache {

class RRsetCache;

/// \brief Message Cache
/// The object of MessageCache represents the cache for class-specific 
/// messages.
///
class MessageCache {
public:
    /// \param cache_size The size of message cache.
    MessageCache(boost::shared_ptr<RRsetCache> rrset_cache_,
                 uint32_t cache_size, uint16_t message_class);
    
    /// \brief Look up message in cache.
    /// \param message generated response message if the message entry 
    ///        can be found.
    ///
    /// \return return true if the message can be found in cache, or else,
    /// return false.
    //TODO Maybe some user just want to get the message_entry.
    bool lookup(const isc::dns::Name& qname,
                const isc::dns::RRType& qtype,
                isc::dns::Message& message);

    /// \brief Update the message in the cache with the new one.
    /// If the message doesn't exist in the cache, it will be added
    /// directly. 
    bool update(const isc::dns::Message& msg);

    /// \brief Dump the message cache to specified file.
    /// \todo It should can be dumped to one configured database.
    void dump(const std::string& file_name);

    /// \brief Load the cache from one file.
    /// \todo It should can be loaded from one configured database.
    void load(const std::string& file_name);

    /// \brief Resize the size of message cache in runtime. 
    bool resize(uint32_t size);

protected:
    /// \brief Get the hash key for the message entry in the cache.
    /// \param name query name of the message.
    /// \param type query type of the message.
    /// \return return the hash key.
    HashKey getEntryHashKey(const isc::dns::Name& name, 
                            const isc::dns::RRType& type) const;

private:
    uint16_t message_class_; // The class of the message cache.
    boost::shared_ptr<RRsetCache> rrset_cache_;
    isc::nsas::HashTable<MessageEntry> message_table_;
    isc::nsas::LruList<MessageEntry> message_lru_;
};
    
} // namespace cache
} // namespace isc

#endif // __MESSAGE_CACHE_H

