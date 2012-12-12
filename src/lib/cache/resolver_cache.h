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

#ifndef RESOLVER_CACHE_H
#define RESOLVER_CACHE_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <dns/rrclass.h>
#include <dns/message.h>
#include <exceptions/exceptions.h>
#include "message_cache.h"
#include "rrset_cache.h"
#include "local_zone_data.h"

namespace isc {
namespace cache {
class RRsetCache;

//TODO a better proper default cache size
#define MESSAGE_CACHE_DEFAULT_SIZE 10000
#define RRSET_CACHE_DEFAULT_SIZE   20000
#define NEGATIVE_RRSET_CACHE_DEFAULT_SIZE   10000

/// \brief Cache Size Information.
///
/// Used to initialize the size of class-specific rrset/message cache.
struct CacheSizeInfo
{
public:
    /// \brief Constructor
    ///
    /// \param cls The RRClass code
    /// \param msg_cache_size The size for the message cache
    /// \param rst_cache_size The size for the RRset cache
    CacheSizeInfo(const isc::dns::RRClass& cls,
                  uint32_t msg_cache_size,
                  uint32_t rst_cache_size):
                    cclass(cls),
                    message_cache_size(msg_cache_size),
                    rrset_cache_size(rst_cache_size)
    {}

    isc::dns::RRClass cclass; // class of the cache.
    uint32_t message_cache_size; // the size for message cache.
    uint32_t rrset_cache_size; // The size for rrset cache.
};

/// \brief  Message has no question section.
///
/// Thrown if the given message has no question section when looking up
/// the message in cache.
class MessageNoQuestionSection : public isc::Exception {
public:
    MessageNoQuestionSection(const char*file, size_t line, const char*what) :
        isc::Exception(file, line, what)
    {}
};

/// \brief Class-specific Resolver Cache.
///
/// The object of ResolverCache represents the cache of the resolver. It may hold
/// a list of message/rrset cache which are in different class.
///
/// \note Public interaction with the cache should be through ResolverCache,
/// not directly with this one. (TODO: make this private/hidden/local to the .cc?)
///
/// \todo The resolver cache class should provide the interfaces for
///       loading, dumping and resizing.
class ResolverClassCache {
public:
    /// \brief Default Constructor.
    ///
    /// Only support for class "IN", and message cache size is
    /// MESSAGE_CACHE_DEFAULT_SIZE, rrset cache size is
    /// RRSET_CACHE_DEFAULT_SIZE
    ResolverClassCache(const isc::dns::RRClass& cache_class);

    /// \brief Construct Function.
    /// \param cache_info Cache size information for each message/rrsets of
    ///        different classes.
    ResolverClassCache(const CacheSizeInfo& cache_info);

    /// \name Lookup Interfaces
    //@{
    /// \brief Look up message in cache.
    ///
    /// \param qname The query name to look up
    /// \param qtype The query type to look up
    /// \param response the query message (must be in RENDER mode)
    ///        which has question section already (exception
    ///        MessageNoQeustionSection will be thrown if it has
    ///        no question section). If the message can be found
    ///        in cache, rrsets for the message will be added to
    ///        different sections(answer, authority, additional).
    /// \return return true if the message can be found, or else,
    ///         return false.
    bool lookup(const isc::dns::Name& qname,
                const isc::dns::RRType& qtype,
                isc::dns::Message& response) const;

    /// \brief Look up rrset in cache.
    ///
    /// \param qname The query name to look up
    /// \param qtype The query type to look up
    ///
    /// \return return the shared_ptr of rrset if it can be found,
    ///         or else, return NULL. When looking up, local zone
    ///         data will be searched first, if not found, then
    ///         search in rrset cache.
    ///
    /// \overload
    ///
    isc::dns::RRsetPtr lookup(const isc::dns::Name& qname,
                              const isc::dns::RRType& qtype) const;

    /// \brief Update the message in the cache with the new one.
    ///
    /// \param msg The message to update
    ///
    /// \return return true if the message is updated successfully,
    ///         or else, return false.
    ///
    /// \note the function doesn't do any message validation check,
    ///       the user should make sure the message is valid, and of
    ///       the right class
    /// TODO: Share the NXDOMAIN info between different type queries
    ///       current implementation can only cache for the type that
    ///       user quired, for example, if user query A record of
    ///       a.example. and the server replied with NXDOMAIN, this
    ///       should be cached for all the types queries of a.example.
    bool update(const isc::dns::Message& msg);

    /// \brief Update the rrset in the cache with the new one.
    ///
    /// local zone data and rrset cache will be updated together.
    /// If the rrset doesn't exist in both of them, then the rrset
    /// will be added into both of them.
    ///
    /// \param rrset_ptr The RRset to update
    ///
    /// \return return false, if the class of the parameter rrset is
    ///        allowed to be cached.
    ///
    /// \overload
    ///
    /// \note The class of the RRset must have been checked. It is not
    /// here.
    bool update(const isc::dns::ConstRRsetPtr& rrset_ptr);

    /// \brief Get the RRClass this cache is for
    ///
    /// \return The RRClass of this cache
    const isc::dns::RRClass& getClass() const;

private:
    /// \brief Update rrset cache.
    ///
    /// \param rrset_ptr The rrset to update with
    /// \param rrset_cache_ptr the rrset cache to update
    ///
    /// \return return true if the rrset is updated in the rrset cache,
    ///         or else return false if failed.
    /// \param rrset_cache_ptr The rrset cache need to be updated.
    bool updateRRsetCache(const isc::dns::ConstRRsetPtr& rrset_ptr,
                          RRsetCachePtr rrset_cache_ptr);

    /// \brief Class this cache is for.
    const isc::dns::RRClass cache_class_;

    /// \brief map of message caches for configured classes(each message
    /// cache is class-specific)
    MessageCachePtr messages_cache_;

    /// \name rrset caches
    //@{
    /// \brief Local Zone data cache
    /// Cache for rrsets in local zones, rrsets
    /// in it never expire.
    LocalZoneDataPtr local_zone_data_;
    //@}

    /// \brief cache the rrsets parsed from the received message.
    RRsetCachePtr rrsets_cache_;

    /// \brief cache the SOA rrset parsed from the negative response message.
    RRsetCachePtr negative_soa_cache_;
};

class ResolverCache {
public:
    /// \brief Default Constructor.
    ///
    /// Right now, only support for class "IN", and message cache size is
    /// MESSAGE_CACHE_DEFAULT_SIZE, rrset cache size is
    /// RRSET_CACHE_DEFAULT_SIZE
    ResolverCache();

    /// \brief Construct Function.
    /// \param caches_size cache size information for each
    ///        messages/rrsets of different classes.
    ResolverCache(std::vector<CacheSizeInfo> caches_size);

    /// \brief Destructor
    ~ResolverCache();

    /// \name Lookup Interfaces
    //@{
    /// \brief Look up message in cache.
    ///
    /// \param qname The query name to look up
    /// \param qtype The query type to look up
    /// \param qclass The query class to look up
    /// \param response the query message (must be in RENDER mode)
    ///        which has question section already (exception
    ///        MessageNoQeustionSection will be thrown if it has
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
    ///
    /// \param qname The query name to look up
    /// \param qtype The query type to look up
    /// \param qclass The query class to look up
    ///
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

    /// \brief Look up closest enclosing NS rrset in cache.
    ///
    /// \param qname The query name to look up
    /// \param qclass The query class to look up
    ///
    /// \return return the shared_ptr of closest enclosing ns rrset
    ///         if it can be found in cache, or else return NULL.
    ///
    /// Currently the implementation is: search exact ns rrset
    /// label by lable, If the ns rrset can't be found, remove the last
    /// label, then search again. The efficiency may be very low when
    /// the name is very long but it's closest rrset's name is very short.
    ///
    /// If a good perfermance is needed when looking up the closest
    /// enclosing ns rrset, cache structure(HashTable) should be
    /// redesigned. By using HashTable, it can only garantee the
    /// performance for looking up exact rrset.
    ///
    /// So here there is another question, which rrset looking up interface
    /// is used frequently? Exact or closest enclosing ns looking up.
    isc::dns::RRsetPtr lookupDeepestNS(const isc::dns::Name& qname,
                              const isc::dns::RRClass& qclass) const;
    //@}

    /// \brief Update the message in the cache with the new one.
    ///
    /// \param msg The message to update
    ///
    /// \return return true if the message is updated successfully,
    ///         or else, return false.
    ///
    /// \note the function doesn't do any message validation check,
    ///       the user should make sure the message is valid.
    bool update(const isc::dns::Message& msg);

    /// \brief Update the rrset in the cache with the new one.
    ///
    /// local zone data and rrset cache will be updated together.
    /// If the rrset doesn't exist in both of them, then the rrset
    /// will be added into both of them.
    ///
    /// \param rrset_ptr The RRset to update
    ///
    /// \return return false, if the class of the parameter rrset is
    ///        allowed to be cached.
    ///
    /// \overload
    ///
    bool update(const isc::dns::ConstRRsetPtr& rrset_ptr);

private:
    /// \brief Returns the class-specific subcache
    ///
    /// \param cache_class the class to get the subcache for
    /// \return The subcache, or NULL if there is no cache for this class
    ResolverClassCache* getClassCache(const isc::dns::RRClass& cache_class) const;

    /// The class-specific caches.
    /// TODO: I think we can optimize for IN, and always have that
    /// one directly available, use the vector for the rest?
    std::vector<ResolverClassCache*> class_caches_;
};

} // namespace cache
} // namespace isc

#endif // RESOLVER_CACHE_H

