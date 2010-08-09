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

#ifndef __CACHE_H
#define __CACHE_H

#include <time.h>

#include <boost/shared_ptr.hpp>

#include <dns/rrset.h>

namespace isc {
namespace dns {
class Name;
class RRClass;
class RRType;
}

namespace datasrc {

class CacheNode;
typedef boost::shared_ptr<CacheNode> CacheNodePtr;
typedef boost::shared_ptr<const CacheNode> ConstCacheNodePtr;

class HotCacheImpl;

/// \brief A \c HotCache is a hot-spot cache for one or more data sources.
///
/// A \c HotCache must be instantiated prior to creating a \c Query.
/// The same instance should be passed to the constructor for all queries,
/// so that all of them will be using the same cache.
///
/// The cache may contain positive or negative entries, indicating
/// whether the data does or does not exist in the underlying data
/// source.  Entries have a fixed and limited lifespan (currently
/// set to 30 seconds, see LIFESPAN_ below).  If a cache entry is
/// found which has exceeded its lifespan, it will not be returned
/// to the caller--exactly as if it had not been found.
/// 
/// The current 30 second cache entry lifespan is experimental.  A longer
/// lifespan would improve performance somewhat; however, longer-lived
/// cache entries are more likely to be incorrect in the event that
/// the underlying data source had been updated.  Depending on the
/// frequency of queries and the frequency of updates, longer or
/// shorter lifespans may be desirable -- it's even possible
/// we may want the lifespan to be set differently depending on
/// the zone or the data source (i.e., with an infinite lifespan
/// for cached data from a static data source).  Additional benchmarking
/// and analysis will be needed for this.
/// 
/// The cache may be configured with a number of available slots for
/// for entries.  When set to a nonzero value, no more than that number
/// of entries can exist in the cache.  If more entries are inserted,
/// old entries will be dropped in "least recently used" order.  If
/// set to zero, the cache size is unlimited.  The current default is
/// based on one thousand queries per second, times the number of seconds
/// in the cache lifespan: 30,000 slots.
///
/// Notes to developers: The current implementation of HotCache uses
/// a std::map (keyed by isc::dns::Question) to locate nodes, so access
/// will generally be in O(log n) time.  (XXX: This might be faster if a
/// hash table were used instead.)
///
/// A linked list is also maintained to keep track of recent accesses
/// to cache entries; each time an entry is accessed, it is moved to the
/// head of the list; when entries need to be removed, they are taken
/// from the tail of the list.  This operation is not locked.  BIND 10
/// does not currently use threads, but if it ever does (or if libdatasrc
/// is ever used by a threaded application), this will need to be
//revisited.
class HotCache {
private:
    /// \name Static definitions
    //@{
    /// \brief Default validity period for cache entries
    static const int LIFESPAN_ = 30;

    /// \brief Default number of slots in cache
    static const int SLOTS_ = 1000 * LIFESPAN_;
    //@}

    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.
    //@{
    HotCache(const HotCache& source);
    HotCache& operator=(const HotCache& source);

public:
    /// \brief Constructor for HotCache
    ///
    /// \param slots The number of slots available in the cache.
    HotCache(const int slots = SLOTS_);

    /// \brief Destructor for HotCache
    ~HotCache();
    //@}

    /// \name Cache Manipulation Methods
    //@{
    /// \brief Enter a positive cache entry.
    ///
    /// If an entry already exists in the cache which matches the
    /// name/class/type of the RRset being cached, then the old entry
    /// is removed before the the new one is inserted.  (XXX: This is
    /// currently slightly inefficient; it would be quicker to keep the
    /// existing node and simply update the rrset, flags, and lifespan.)
    ///
    /// \param rrset The \c RRset to cache.
    /// \param flags The query response flags returned from the low-level
    /// data source when this \c RRset was looked up.
    /// \param lifespan How long the cache node is to be considered valid;
    /// defaulting to 30 seconds.
    void addPositive(isc::dns::RRsetPtr rrset,
                     uint32_t flags,
                     time_t lifespan = LIFESPAN_);

    /// \brief Enter a negative cache entry.
    ///
    /// In the case of a negative cache entry there is no \c RRset to
    /// cache, so instead a null \c RRsetPtr will be stored.  Since the
    /// name, class, and type cannot be retrieved from an \c RRset, they
    /// must be specified in the parameters.
    ///
    /// If an entry already exists in the cache which matches the
    /// specified name/class/type, then the old entry is removed
    /// before the the new one is inserted.  (XXX: As noted in the comments
    /// for addPositive(), this is currently slightly inefficient.)
    /// 
    /// \param name Query name
    /// \param rrclass Query class
    /// \param rrtype Query type
    /// \param flags Query response flags returned from the low-level
    /// data source, indicating why this lookup failed (name not found,
    /// type not found, etc).
    /// \param lifespan How long the cache node is to be considered valid;
    /// defaulting to 30 seconds.
    ///
    /// Note: 'rrclass' and 'rrtype' must refer to a specific class and
    /// type; it is not meaningful to cache type or class ANY.  Currently,
    /// this condition is silently ignored.
    void addNegative(const isc::dns::Name& name,
                     const isc::dns::RRClass& rrclass,
                     const isc::dns::RRType& rrtype,
                     uint32_t flags,
                     time_t lifespan = LIFESPAN_);

    /// \brief Retrieve (and promote) a record from the cache
    ///
    /// Retrieves a record from the cache matching the given 
    /// query-tuple.  Returns true if one is found.  If it is a
    /// posiitve cache entry, then 'rrset' is set to the cached
    /// RRset.  For both positive and negative cache entries, 'flags'
    /// is set to the query response flags.  The cache entry is 
    /// then promoted to the head of the LRU queue.  (NOTE: Because
    /// of this, "retrieve" cannot be implemented as a const method.)
    ///
    /// \param name The query name
    /// \param rrclass The query class
    /// \param rrtype The query type
    /// \param rrset Returns the RRset found, if any, to the caller
    /// \param flags Returns the flags, if any, to the caller
    ///
    /// \return \c bool, true if data was found in the cache, false if not.
    bool retrieve(const isc::dns::Name& qname,
                  const isc::dns::RRClass& qclass,
                  const isc::dns::RRType& qtype,
                  isc::dns::RRsetPtr& rrset,
                  uint32_t& flags);
    //@}

    /// \name Getter and Setter Methods
    //@{
    /// \brief Sets the number of slots in the cache.
    ///
    /// If slots is set to zero, the cache can grow without any imposed
    /// limit.  If slots is to set a lower number than the cache currently
    /// contains, then the least recently used records will be purged from
    /// the cache until the total number of items in the cache equals slots.
    void setSlots(int slots);

    /// \brief Returns the number of slots in the cache.
    int getSlots() const;

    /// \brief Enable or disable the cache
    void setEnabled(bool e);

    /// \brief Indicate whether the cache is enabled
    bool getEnabled() const;

    /// \brief Returns the number of nodes currently stored in the cache.
    ///
    /// Note that this doesn't indicate how many nodes are still valid;
    /// some may have expired.
    int getCount() const;
    //@}

private:
    /// \brief Hidden implementation details
    HotCacheImpl* impl_;
};

}
}

#endif

// Local Variables: 
// mode: c++
// End: 
