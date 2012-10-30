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

#ifndef HASH_DELETER_H
#define HASH_DELETER_H

#include <boost/shared_ptr.hpp>
#include <util/lru_list.h>

#include "hash_table.h"

namespace isc {
namespace nsas {

/// \brief Delete Object from Hash Table
///
/// This is the object passed to the LRU list constructors that deletes the
/// ZoneEntry from the hash table when the zone is deleted from the LRU list.
///
/// It is declared as a nested class so as to be able to access the
/// hash table without the need to be declared as "friend" or the need
/// to define accessor methods.
template <typename T>
class HashDeleter : public isc::util::LruList<T>::Dropped {
public:

    /// \brief Constructor
    ///
    /// \param hashtable Reference to the hash table from which information is
    /// to be deleted.  The table is assumed to remain in existence for the life
    /// of this object.
    ///
    /// \param hashtable Hash table from which the element should be deleted.
    HashDeleter(HashTable<T>& hashtable) : hashtable_(hashtable)
    {}

    /// \brief Destructor
    ///
    virtual ~HashDeleter(){}

    // The default copy constructor and assignment operator are correct for
    // this object.

    /// \brief Deletion Function
    ///
    /// Performs the deletion of the zone entry from the hash table.
    ///
    /// \param element Element to be deleted
    virtual void operator()(T* element) const;

private:
    HashTable<T>& hashtable_;         ///< Hash table to access element
};

// delete the object from the relevant hash table
template <class T>
void HashDeleter<T>::operator()(T* element) const {
    hashtable_.remove(element->hashKey());
}

} // namespace nsas
} // namespace isc

#endif // HASH_DELETER_H
