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

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <list>

#include <boost/shared_ptr.hpp>

#include <util/locks.h>

#include "hash.h"
#include "hash_key.h"

// Maximum key length if the maximum size of a DNS name
#define MAX_KEY_LENGTH 255

namespace isc {
namespace nsas {

/// \brief Hash Table Slot
///
/// Describes the entry for the hash table.  This is non-copyable (because
/// the mutex is non-copyable), but we need to be able to copy it to initialize
/// a vector of hash table slots.  As the copy is only needed for
/// initialization, and as there is no need to copy state when this happens, we
/// cheat: the copy constructor constructs a newly initialized HashTableSlot and
/// does not copy its argument.
template <typename T>
struct HashTableSlot {

    /// \brief Type definitions
    ///
    //@{

    typedef typename std::list<boost::shared_ptr<T> >::iterator  iterator;
                                    ///< Iterator over elements with same hash

    typedef isc::util::locks::upgradable_mutex mutex_type;
                                    ///< Mutex protecting this slot
    //@}

    /// \brief Default Constructor
    HashTableSlot()
    {}

    /// \brief Copy Constructor
    ///
    /// ... which as noted in the class description does not copy.
    HashTableSlot(const HashTableSlot<T>&) : mutex_(), list_()
    { }

public:
    mutex_type                          mutex_;     ///< Protection mutex
    std::list<boost::shared_ptr<T> >    list_;      ///< List head
};

/// \brief Comparison Object Class
///
/// The base class for a comparison object; this object is used to compare
/// an object in the hash table with a key, and indicates whether the two
/// match.  All objects used for comparison in hash tables should be derived
/// from this class.
template <typename T>
class HashTableCompare {
public:
    /// \brief Constructor
    HashTableCompare(){}

    /// \brief virtual Destructor
    virtual ~HashTableCompare() {}

    /// \brief Comparison Function
    ///
    /// Compares an object against a name in the hash table and reports if the
    /// object's name is the same.
    ///
    /// \param object Pointer to the object
    /// \param key Key describing the object
    ///
    /// \return bool true of the name of the object is equal to the name given.
    virtual bool operator()(T* object, const HashKey& key) const = 0;
};


/// \brief Hash Table
///
/// This class is an implementation of a hash table in which the zones and
/// nameservers of the Nameserver Address Store are held.
///
/// A special class has been written (rather than use an existing hash table
/// class) to improve concurrency.  Rather than lock the entire hash table when
/// an object is added/removed/looked up, only the entry for a particular hash
/// value is locked.  To do this, each entry in the hash table is a pair of
/// mutex/STL List; the mutex protects that particular list.
///
/// \param T Class of object to be stored in the table.
template <typename T>
class HashTable {
public:

    /// \brief Type Definitions
    ///
    //@{
    typedef typename
    isc::util::locks::sharable_lock<typename HashTableSlot<T>::mutex_type>
    sharable_lock;                  ///< Type for a scope-limited read-lock

    typedef typename
    isc::util::locks::scoped_lock<typename HashTableSlot<T>::mutex_type>
    scoped_lock;                    ///< Type for a scope-limited write-lock
    //@}

    /// \brief Constructor
    ///
    /// Initialises the hash table.
    ///
    /// \param cmp Compare function (or object) used to compare an object with
    /// to get the name to be used as a key in the table.  The object should be
    /// created via a "new" as ownership passes to the hash table.  The hash
    /// table will take the responsibility of deleting it.
    /// \param size Size of the hash table.  For best result, this should be a
    /// prime although that is not checked.  The default value is the size used
    /// in BIND-9 for its address database.
    HashTable(HashTableCompare<T>* cmp, uint32_t size = 1009);

    /// \brief Destructor
    ///
    virtual ~HashTable(){}

    /// \brief Get Entry
    ///
    /// Returns a shared_ptr object pointing to the table entry
    ///
    /// \param key Name of the object (and class).  The hash of this is
    /// calculated and used to index the table.
    ///
    /// \return Shared pointer to the object or NULL if it is not there.
    boost::shared_ptr<T> get(const HashKey& key) {
        uint32_t index = hash_(key);
        sharable_lock lock(table_[index].mutex_);
        return getInternal(key, index);
    }

    /// \brief Remove Entry
    ///
    /// Remove the specified entry.  The shared pointer to the object is
    /// destroyed, so if this is the last pointer, the object itself is also
    /// destroyed.
    ///
    /// \param key Name of the object (and class).  The hash of this is
    /// calculated and used to index the table.
    ///
    /// \return true if the object was deleted, false if it was not found.
    bool remove(const HashKey& key);

    /// \brief Add Entry
    ///
    /// Adds the specified entry to the table.  If there is an entry already
    /// there, it is either replaced or the addition fails, depending on the
    /// setting of the "replace" parameter.
    ///
    /// \param object Pointer to the object to be added.  If the addition is
    /// successful, this object will have a shared pointer pointing to it; it
    /// should not be deleted by the caller.
    /// \param key Key to use to calculate the hash.
    /// \param replace If true, when an object is added and an object with the
    /// same name already exists, the existing object is replaced.  If false,
    // the addition fails and a status is returned.
    /// \return true if the object was successfully added, false otherwise.
    bool add(boost::shared_ptr<T>& object, const HashKey& key,
        bool replace = false)
    {
        uint32_t index = hash_(key);
        scoped_lock lock(table_[index].mutex_);
        return addInternal(object, key, index, replace);
    }

    /**
     * \brief Attomicly lookup an entry or add a new one if it does not exist.
     *
     * Looks up an entry specified by key in the table. If it is not there,
     * it calls generator() and adds its result to the table under given key.
     * It is performed attomically to prevent race conditions.
     *
     * \param key The entry to lookup.
     * \param generator will be called when the item is not there. Its result
     *     will be added and returned. The generator should return as soon
     *     as possible, the slot is locked during its execution.
     * \return The boolean part of pair tells if the value was added (true
     *     means new value, false looked up one). The other part is the
     *     object, either found or created.
     * \todo This uses a scoped_lock, which does not allow sharing and is
     *     used a lot in the code. It might turn out in future that it is a
     *     problem and that most of the accesses is read only. In that case we
     *     could split it to fast-slow path - first try to find it with
     *     shared_lock. If it fails, lock by scoped_lock, try to find again (we
     *     unlocked it, so it might have appeared) and if it still isn't there,
     *     create it. Not implemented now as it might or might not help (it
     *     could even slow it down) and the code would get more complicated.
     */
    template<class Generator>
    std::pair<bool, boost::shared_ptr<T> > getOrAdd(const HashKey& key,
        const Generator& generator)
    {
        uint32_t index = hash_(key);
        scoped_lock lock(table_[index].mutex_);
        boost::shared_ptr<T> result(getInternal(key, index));
        if (result) {
            return (std::pair<bool, boost::shared_ptr<T> >(false, result));
        } else {
            result = generator();
            addInternal(result, key, index);
            return (std::pair<bool, boost::shared_ptr<T> >(true, result));
        }
    }

    /// \brief Returns Size of Hash Table
    ///
    /// \return Size of hash table
    uint32_t tableSize() const {
        return table_.size();
    }

protected:
    // Internal parts, expect to be already locked
    boost::shared_ptr<T> getInternal(const HashKey& key,
        uint32_t index);
    bool addInternal(boost::shared_ptr<T>& object, const HashKey& key,
        uint32_t index, bool replace = false);

private:
    Hash                             hash_;  ///< Hashing function
    std::vector<HashTableSlot<T> >   table_; ///< The hash table itself
    boost::shared_ptr<HashTableCompare<T> > compare_;  ///< Compare object
};


// Constructor
template <typename T>
HashTable<T>::HashTable(HashTableCompare<T>* compare, uint32_t size) :
    hash_(size, MAX_KEY_LENGTH), table_(size), compare_(compare)
{}

// Lookup an object in the table
template <typename T>
boost::shared_ptr<T> HashTable<T>::getInternal(const HashKey& key,
    uint32_t index)
{
    // Locate the object.
    typename HashTableSlot<T>::iterator i;
    for (i = table_[index].list_.begin(); i != table_[index].list_.end(); ++i) {
        if ((*compare_)(i->get(), key)) {

            // Found it, so return the shared pointer object
            return (*i);
        }
    }

    // Did not find it, return an empty shared pointer object.
    return boost::shared_ptr<T>();
}

// Remove an entry from the hash table
template <typename T>
bool HashTable<T>::remove(const HashKey& key) {

    // Calculate the hash value
    uint32_t index = hash_(key);

    // Access to the elements of this hash slot are accessed under a mutex.
    // The mutex will be released when this object goes out of scope and is
    // destroyed.
    scoped_lock lock(table_[index].mutex_);

    // Now search this list to see if the element already exists.
    typename HashTableSlot<T>::iterator i;
    for (i = table_[index].list_.begin(); i != table_[index].list_.end(); ++i) {
        if ((*compare_)(i->get(), key)) {

            // Object found so delete it.
            table_[index].list_.erase(i);
            return true;;
        }
    }

    // When we get here, we know that there is no element with the key in the
    // list, so tell the caller.
    return false;
}

// Add an entry to the hash table
template <typename T>
bool HashTable<T>::addInternal(boost::shared_ptr<T>& object,
    const HashKey& key, uint32_t index, bool replace)
{
    // Search this list to see if the element already exists.
    typename HashTableSlot<T>::iterator i;
    for (i = table_[index].list_.begin(); i != table_[index].list_.end(); ++i) {
        if ((*compare_)(i->get(), key)) {

            // Object found.  If we are not allowed to replace the element,
            // return an error.  Otherwise erase it from the list and exit the
            // loop.
            if (replace) {
                table_[index].list_.erase(i);
                break;
            }
            else {
                return false;
            }
        }
    }

    // When we get here, we know that there is no element with the key in the
    // list - in which case, add the new object.
    table_[index].list_.push_back(object);

    return true;
}

}   // namespace nsas
}   // namespace isc

#endif // HASH_TABLE_H
