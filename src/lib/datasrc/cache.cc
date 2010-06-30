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

#include <stdint.h>

#include <map>

#include <dns/question.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>

#include <list>

#include <datasrc/cache.h>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace datasrc {

/// \brief A \c CacheEntry object contains the data stored with
/// each \c CacheNode: a pointer to the cached RRset (empty in
/// the case of a negative cache entry), and a copy of the
/// query-response flags that were returned when the RRset
/// was originally looked up in the low-level data source.
class CacheEntry {
private:
    /// The copy constructor and the assignment operator are intentionally
    /// defined as private.
    CacheEntry(const CacheEntry& source);
    CacheEntry& operator=(const CacheEntry& source);

public:
    CacheEntry(RRsetPtr r, uint32_t f) : rrset(r), flags(f) {};

    RRsetPtr rrset;
    uint32_t flags;
};

typedef boost::shared_ptr<CacheEntry> CacheEntryPtr;

/// \brief A \c CacheNode is a node in the \c HotCache LRU queue.  It
/// contains a pointer to a \c CacheEntry, a reference to the \c Question
/// that we are answering, a lifespan during which this entry remains
/// valid, and pointers to the next and previous entries in the list.
class CacheNode {
private:
    /// \name Constructors and Assignment Operator
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.
    //@{
    CacheNode(const CacheNode& source);
    CacheNode& operator=(const CacheNode& source);

public:
    /// \brief Constructor for positive cache entry.
    ///
    /// \param rrset The \c RRset to cache.
    /// \param flags The query response flags returned from the low-level
    /// data source when this \c RRset was looked up.
    /// \param lifespan How long the cache node is to be considered valid.
    CacheNode(const RRsetPtr rrset, uint32_t flags, time_t lifespan);

    /// \brief Constructor for negative cache entry.
    ///
    /// \param name Query name
    /// \param rrclass Query class
    /// \param rrtype Query type
    /// \param flags Query response flags returned from the low-level
    /// data source, indicating why this lookup failed (name not found,
    /// type not found, etc).
    /// \param lifespan How long the cache node is to be considered valid.
    CacheNode(const Name& name,
              const RRClass& rrclass,
              const RRType& rrtype,
              uint32_t flags,
              time_t lifespan);
    //@}

    /// \name Getter and Setter Methods
    //@{
    /// \brief Returns a pointer to the cached RRset (or an empty
    /// RRsetPtr for negative cache entries).

    /// \return \c RRsetPtr
    RRsetPtr getRRset() const { return (entry->rrset); }

    /// \brief Returns the query response flags associated with the data.
    ///
    /// \return \c uint32_t
    uint32_t getFlags() const { return (entry->flags); }

    /// \brief Is this record still valid?
    ///
    /// \return True if the expiration time has not yet passed,
    /// or false if it has.
    bool isValid() const;
    //@}

    // An iterator referencing this entry in the LRU list. This
    // permits unit-time removal using list::erase().
    list<CacheNodePtr>::iterator lru_entry_;

    /// The \c Question (name/rrclass/rrtype) answered by this cache node
    const isc::dns::Question question;

private:
    // The cached RRset data
    CacheEntryPtr entry;

    // When this record should be discarded
    time_t expiry;
};

// CacheNode constructor for a positive cache entry
CacheNode::CacheNode(const RRsetPtr rrset, const uint32_t flags,
                     const time_t lifespan) :
    question(Question(rrset->getName(), rrset->getClass(), rrset->getType()))
{
    const time_t now = time(NULL);
    expiry = now + lifespan;

    entry = CacheEntryPtr(new CacheEntry(rrset, flags));
}

// CacheNode constructor for a negative cache entry
CacheNode::CacheNode(const Name& name,
                     const RRClass& rrclass,
                     const RRType& rrtype,
                     const uint32_t flags,
                     const time_t lifespan) :
    question(Question(name, rrclass, rrtype))
{
    const time_t now = time(NULL);
    expiry = now + lifespan;

    entry = CacheEntryPtr(new CacheEntry(RRsetPtr(), flags));
}
// Returns true if the node has not yet expired.
bool
CacheNode::isValid() const {
    const time_t now = time(NULL);
    return (now < expiry);
}

/// This class abstracts the implementation details for \c HotCache.
///
/// Each node inserted into the cache is placed at the head of a
/// doubly-linked list.  Whenever that node is retrieved from the cache,
/// it is again moved to the head of the list.  When the configured
/// number of slots in the cache has been exceeded, the least recently
/// used nodes will be removed from the tail of the list.
///
/// A pointer to each cache node is also placed in a \c std::map object,
/// keyed by \c isc::dns::Question.  This allows retrieval of data in
/// (usually) logarithmic time.  (Possible TODO item: replace this with a
/// hash table instead.)
class HotCacheImpl {
public:
    HotCacheImpl(int slots, bool enabled);

    // The LRU list
    list<CacheNodePtr> lru_;

    // Flag to indicate whether the cache is enabled
    bool enabled_;

    // The number of available slots in the LRU list.  (If zero,
    // then the list is unbounded; otherwise, items are removed
    // from the tail of the list whenever it grows past slots_.)
    int slots_;

    // The number of items currently in the list.
    int count_;

    // Map from query tuple to cache node pointer, allowing fast retrieval
    // of data without a linear search of the LRU list
    std::map<Question, CacheNodePtr> map_;

    // Move a node to the front of the LRU list.
    void promote(CacheNodePtr node);

    // Remove a node from the cache.
    void remove(ConstCacheNodePtr node);

    // Insert a node into the cache (called by both cache() and ncache())
    void insert(CacheNodePtr node);
};

// HotCacheImpl constructor
HotCacheImpl::HotCacheImpl(int slots, bool enabled) :
    enabled_(enabled), slots_(slots), count_(0)
{}

// Insert a cache node into the cache
inline void
HotCacheImpl::insert(const CacheNodePtr node) {
    std::map<Question, CacheNodePtr>::const_iterator iter;
    iter = map_.find(node->question);
    if (iter != map_.end()) {
        CacheNodePtr old = iter->second;
        if (old && old->isValid()) {
            remove(old);
        }
    }

    lru_.push_front(node);
    node->lru_entry_ = lru_.begin();

    map_[node->question] = node;
    ++count_;

    if (slots_ != 0 && count_ > slots_) {
        remove(lru_.back());
    }
}

// Promote a node to the head of the LRU list
void
HotCacheImpl::promote(CacheNodePtr node) {
    if (!node) {
        return;
    }
    if (node->lru_entry_ == lru_.begin()) {
        return;
    }
    lru_.erase(node->lru_entry_);
    lru_.push_front(node);
    node->lru_entry_ = lru_.begin();
}

// Remove a node from the LRU list and the map
void
HotCacheImpl::remove(ConstCacheNodePtr node) {
    lru_.erase(node->lru_entry_);
    map_.erase(node->question);
    --count_;
}

// HotCache constructor
HotCache::HotCache(const int slots) {
    impl_ = new HotCacheImpl(slots, true);
}

// HotCache destructor
HotCache::~HotCache() {
    delete impl_;
}

// Add a positive entry to the cache
void
HotCache::addPositive(RRsetPtr rrset, const uint32_t flags,
                      const time_t lifespan)
{
    if (!impl_->enabled_) {
        return;
    }

    impl_->insert(CacheNodePtr(new CacheNode(rrset, flags, lifespan)));
}

// Add a negative entry to the cache
void
HotCache::addNegative(const Name& name, const RRClass &rrclass,
                      const RRType& rrtype, const uint32_t flags,
                      const time_t lifespan)
{
    if (!impl_->enabled_) {
        return;
    }

    if (rrtype == RRType::ANY() || rrclass == RRClass::ANY()) {
        return;
    }

    impl_->insert(CacheNodePtr(new CacheNode(name, rrclass, rrtype,
                                             flags, lifespan)));
}

// Try to retrieve an entry from the cache, returning true if
// it was found and valid.
bool
HotCache::retrieve(const Name& n, const RRClass& c, const RRType& t,
                   RRsetPtr& rrset, uint32_t& flags)
{
    if (!impl_->enabled_) {
        return (false);
    }

    std::map<Question, CacheNodePtr>::const_iterator iter;
    iter = impl_->map_.find(Question(n, c, t));
    if (iter == impl_->map_.end()) {
        return (false);
    }

    CacheNodePtr node = iter->second;

    if (node->isValid()) {
        impl_->promote(node);
        rrset = node->getRRset();
        flags = node->getFlags();
        return (true);
    }

    impl_->remove(node);
    return (false);
}

// Set the number of slots in the cache.
void
HotCache::setSlots(const int slots) {
    impl_->slots_ = slots;

    if (!impl_->enabled_) {
        return;
    }

    while (impl_->slots_ != 0 && impl_->count_ > impl_->slots_) {
        impl_->remove(impl_->lru_.back());
    }
}

// Return the number of slots in the cache
int
HotCache::getSlots() const {
    return (impl_->slots_);
}

/// Enable or disable the cache
void
HotCache::setEnabled(const bool e) {
    impl_->enabled_ = e;
}

/// Indicate whether the cache is enabled
bool
HotCache::getEnabled() const {
    return (impl_->enabled_);
}

// Return the number of entries in the cache
int
HotCache::getCount() const {
    return (impl_->count_);
}

}
}
