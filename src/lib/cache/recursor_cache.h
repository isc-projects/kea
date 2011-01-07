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

#ifndef __RECURSOR_CACHE_H
#define __RECURSOR_CACHE_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <dns/message.h>
#include "message_cache.h"
#include "rrset_cache.h"

namespace isc {
namespace cache {
class RRsetCache;

typedef std::map<uint16_t, MessageCachePtr> MessageCacheMap;
typedef std::map<uint16_t, RRsetCachePtr> RRsetCacheMap;

//TODO a better proper default cache size
#define MESSAGE_CACHE_DEFAULT_SIZE 1000000 
#define RRSET_CACHE_DEFAULT_SIZE  10000

/// \brief Cache Size Information.
/// It is used to initialize the size of rrset/message.
struct CacheSizeInfo
{
    uint16_t class_; // class of the cache.
    uint32_t message_cache_size; // the size for message cache.
    uint32_t rrset_cache_size; // The size for rrset cache.
};

///    
/// \brief Recursor Cache
/// The object of RecursorCache represents the cache of the recursor. It holds
/// a list of message cache and rrset cache.
///
class RecursorCache {
public:
    /// \brief Construct Function
    /// \param caches_size cache size information for each 
    /// messages/rrsets.
    RecursorCache(std::vector<CacheSizeInfo> caches_size);

    /// \name Lookup Interfaces
    //@{
    /// \brief Look up message in cache.
    ///
    /// \param response the query message (must in RENDER mode),
    /// if the message can be found in cache, rrsets for the message
    /// will be added to different sections.
    ///
    /// \return return true if the message can be found, or else, return false.
    bool lookup(const isc::dns::Name& qname, 
                const isc::dns::RRType& qtype,
                const isc::dns::RRClass& qclass,
                isc::dns::Message& response) const;

    /// \brief Look up rrset in cache.
    /// \return return the shared_ptr of rrset if it can be found, 
    /// or else, return NULL. When looking up, cache1(localzone) will 
    /// be searched first, if not found, then search in cache2.
    ///
    /// \overload
    ///
    isc::dns::RRsetPtr lookup(const isc::dns::Name& qname, 
                              const isc::dns::RRType& qtype,
                              const isc::dns::RRClass& qclass) const;
    //@}

    /// \brief Update the message in the cache with the new one.
    /// \return return true if the message is updated into the cache,
    /// or else, return false. 
    ///
    /// \note, the function doesn't do any message
    /// validation check, the user should make sure the message is valid.
    bool update(const isc::dns::Message& msg);

    /// \brief Update the rrset in the cache with the new one.
    /// rrset_cache1_ and rrset_cache2_ should be updated together.
    /// If the rrset doesn't exist in both of them, then the rrset
    /// will be added into both of them.
    /// \return return false, if the class of the parameter rrset is
    /// allowed to be cached.
    /// 
    /// \overload 
    ///
    bool update(const isc::dns::RRset& rrset);

    /// \name Cache Serialization
    //@{
    /// \brief Dump the cache content to one file.
    /// \todo It should can be dumped to one configured database.
    void dump(const std::string& file_name);

    /// \brief Load the cache from one file.
    /// \todo It should can be loaded from one configured database.
    void load(const std::string& file_name);
    //@}

protected:    
    /// \brief Look up rrset in one specified rrset cache.
    /// This function is used internally by lookup()
    /// \param rrsets_cache the cache for looking up rrset.
    /// \return return the shared_ptr of the rrset if it can be
    /// found in the cache.
    isc::dns::RRsetPtr lookup_in_rrset_cache(const isc::dns::Name& qname, 
                      const isc::dns::RRType& qtype,
                      const isc::dns::RRClass& qclass,
                      const RRsetCacheMap& rrsets_cache) const;

    /// \brief Update the rrset in one rrset cache.
    /// \return return true if the rrset is updated in the rrset cache,
    /// or else return false.
    /// \param rrset_cache_map the map of rrset cache, the rrset cache needs
    /// to be updated should be found first according the class of the rrset.
    /// If the class-specific rrset cache can't be found in the map, it returns
    /// false.
    bool updateRRsetCache(const isc::dns::RRset& rrset,
                          RRsetCacheMap& rrset_cache_map);
protected:

    /// \brief the list of message cache for configured classes(message cache
    /// is class-specific)
    MessageCacheMap messages_cache_;
    
    /// \name rrset caches
    //@{
    /// \brief the list of rrset cache for configured classes.
    /// rrsets_cache1_ is used to cache the configured rrsets in localzone, rrsets 
    /// in it will never expire.
    RRsetCacheMap rrsets_cache1_;

    /// \brief cache the rrsets parsed from the received message.
    RRsetCacheMap rrsets_cache2_;
    //@}
};

} // namespace cache
} // namespace isc

#endif // __RECURSOR_CACHE_H

