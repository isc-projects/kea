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

#ifndef __RESOLVER_CACHE_H
#define __RESOLVER_CACHE_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <dns/message.h>
#include <exceptions/exceptions.h>
#include "message_cache.h"
#include "rrset_cache.h"
#include "local_zone_data.h"

namespace isc {
namespace cache {
class RRsetCache;

typedef std::map<uint16_t, MessageCachePtr> MessageCacheMap;
typedef std::map<uint16_t, RRsetCachePtr> RRsetCacheMap;
typedef std::map<uint16_t, LocalZoneDataPtr> LocalZoneDataMap;

//TODO a better proper default cache size
#define MESSAGE_CACHE_DEFAULT_SIZE 10000
#define RRSET_CACHE_DEFAULT_SIZE   20000

/// \brief Cache Size Information.
/// Used to initialize the size of class-specific rrset/message cache.
struct CacheSizeInfo
{
public:    
    CacheSizeInfo(uint16_t cls, 
                  uint32_t msg_cache_size,
                  uint32_t rst_cache_size):
                    klass(cls),
                    message_cache_size(msg_cache_size),
                    rrset_cache_size(rst_cache_size)
    {}

    uint16_t klass; // class of the cache.
    uint32_t message_cache_size; // the size for message cache.
    uint32_t rrset_cache_size; // The size for rrset cache.
};

/// \brief  Message has no question section.
/// Thrown if the given message has no question section when looking up
/// the message in cache.
class MessageNoQuestionSection : public isc::Exception {
public:
    MessageNoQuestionSection(const char*file, size_t line, const char*what) :
        isc::Exception(file, line, what)
    {}
};

///
/// \brief Resolver Cache.
/// The object of ResolverCache represents the cache of the resolver. It may holds
/// a list of message/rrset cache which are in different class.
///
class ResolverCache {
public:
    /// \brief Default Construct Function.
    ///  Only support for class "IN", and message cache size is
    /// MESSAGE_CACHE_DEFAULT_SIZE, rrset cache size is
    /// RRSET_CACHE_DEFAULT_SIZE
    ResolverCache();

    /// \brief Construct Function.
    /// \param caches_size cache size information for each
    ///        messages/rrsets of different classes.
    ResolverCache(std::vector<CacheSizeInfo> caches_size);

    /// \name Lookup Interfaces
    //@{
    /// \brief Look up message in cache.
    ///
    /// \param response the query message (must in RENDER mode)
    ///        which has question section already(exception
    ///        MessageNoQeustionSection) will be thrown if it has
    ///        no question section). If the message can be found
    ///        in cache, rrsets for the message will be added to
    ///        different sections(answer, authority, additional).
    /// \return return true if the message can be found, or else,
    ///         return false.
    bool lookup(const isc::dns::Name& qname,
                const isc::dns::RRType& qtype,
                const isc::dns::RRClass& qclass,
                isc::dns::Message& response) const;

    /// \brief Look up rrset in cache.
    /// \return return the shared_ptr of rrset if it can be found,
    ///         or else, return NULL. When looking up, local zone
    ///         data will be searched first, if not found, then
    ///         search in rrset cache.
    ///
    /// \overload
    ///
    isc::dns::RRsetPtr lookup(const isc::dns::Name& qname,
                              const isc::dns::RRType& qtype,
                              const isc::dns::RRClass& qclass) const;

    /// \brief Look up closest rrset in cache.
    /// \return return the shared_ptr of rrset if it can be found in
    ///         cache, or else return NULL.
    ///
    /// Currently the implementation is: search exact rrset
    /// label by lable, If the rrset can't be found, remove the last
    /// label, then search again. The efficiency may be very low when
    /// the name of rrset is very long but it's closest rrset's name
    /// is very short.
    /// If a good perfermance is needed when looking up the closest rrset,
    /// rrset cache structure(HashTable) should be redesigned. By using
    /// HashTable, it can only garantee the performance for looking
    /// up exact rrset.
    /// So here there is another question, which rrset looking up interface
    /// is used frequently? Exact or closest looking up.
    isc::dns::RRsetPtr lookupClosestRRset(const isc::dns::Name& qname,
                              const isc::dns::RRType& qtype,
                              const isc::dns::RRClass& qclass) const;
    //@}

    /// \brief Update the message in the cache with the new one.
    /// \return return true if the message is updated successfully,
    ///         or else, return false.
    ///
    /// \note the function doesn't do any message validation check,
    ///       the user should make sure the message is valid.
    bool update(const isc::dns::Message& msg);

    /// \brief Update the rrset in the cache with the new one.
    ///        local zone data and rrset cache will be updated together.
    ///        If the rrset doesn't exist in both of them, then the rrset
    ///        will be added into both of them.
    /// \return return false, if the class of the parameter rrset is
    ///        allowed to be cached.
    ///
    /// \overload
    ///
    bool update(const isc::dns::ConstRRsetPtr rrset_ptr);

    /// \brief Check whether the messages/rrsets of specified class
    ///        are cached.
    bool classIsSupported(uint16_t klass) const;

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
    /// \brief Update rrset cache.
    /// \return return true if the rrset is updated in the rrset cache,
    ///         or else return false if failed.
    /// \param rrset_cache_ptr The rrset cache need to be updated.
    bool updateRRsetCache(const isc::dns::ConstRRsetPtr rrset_ptr,
                          RRsetCachePtr rrset_cache_ptr);

protected:
    /// \brief Classes supported by the cache.
    std::vector<uint16_t> class_supported_;

    /// \brief map of message caches for configured classes(each message
    /// cache is class-specific)
    mutable MessageCacheMap messages_cache_;

    /// \name rrset caches
    //@{
    /// \brief Local Zone data cache
    /// Cache for rrsets in local zones, rrsets
    /// in it never expire.
    mutable LocalZoneDataMap local_zone_data_;

    /// \brief cache the rrsets parsed from the received message.
    mutable RRsetCacheMap rrsets_cache_;
    //@}
};

} // namespace cache
} // namespace isc

#endif // __RESOLVER_CACHE_H

