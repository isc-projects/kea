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

#ifndef MESSAGE_CACHE_H
#define MESSAGE_CACHE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <dns/message.h>
#include "message_entry.h"
#include <nsas/hash_table.h>
#include <util/lru_list.h>
#include "rrset_cache.h"

namespace isc {
namespace cache {

/// \brief Message Cache
/// The object of MessageCache represents the cache for class-specific
/// messages.
///
/// \todo The message cache class should provide the interfaces for
///       loading, dumping and resizing.
class MessageCache {
// Noncopyable
private:
    MessageCache(const MessageCache& source);
    MessageCache& operator=(const MessageCache& source);
public:
    /// \param rrset_cache The cache that stores the RRsets that the
    ///        message entry will point to
    /// \param cache_size The size of message cache.
    /// \param message_class The class of the message cache
    /// \param negative_soa_cache The cache that stores the SOA record
    ///        that comes from negative response message
    MessageCache(const RRsetCachePtr& rrset_cache,
                 uint32_t cache_size, uint16_t message_class,
                 const RRsetCachePtr& negative_soa_cache);

    /// \brief Destructor function
    virtual ~MessageCache();

    /// \brief Look up message in cache.
    /// \param qname Name of the domain for which the message is being sought.
    /// \param qtype Type of the RR for which the message is being sought.
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
protected:
    /// \brief Get the hash key for the message entry in the cache.
    /// \param name query name of the message.
    /// \param type query type of the message.
    /// \return return the hash key.
    HashKey getEntryHashKey(const isc::dns::Name& name,
                            const isc::dns::RRType& type) const;

    // Make these variants be protected for easy unittest.
protected:
    uint16_t message_class_; // The class of the message cache.
    RRsetCachePtr rrset_cache_;
    RRsetCachePtr negative_soa_cache_;
    isc::nsas::HashTable<MessageEntry> message_table_;
    isc::util::LruList<MessageEntry> message_lru_;
};

typedef boost::shared_ptr<MessageCache> MessageCachePtr;

} // namespace cache
} // namespace isc

#endif // MESSAGE_CACHE_H

