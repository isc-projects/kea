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

#ifndef NSAS_ENTRY_H
#define NSAS_ENTRY_H

#include <boost/enable_shared_from_this.hpp>
#include <iostream>

#include <exceptions/exceptions.h>
#include <util/lru_list.h>

#include "hash_key.h"
#include "hash_table.h"

namespace isc {
namespace nsas {

/// \brief Invalid Iterator
///
/// Thrown if an attempt was made to access the iterator - the pointer into
/// the LRU list where this element is located - when it is marked as invalid.
class InvalidLruIterator : public isc::Exception {
public:
    InvalidLruIterator(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};

/// \brief Element of NSAS Internal Lists
///
/// This defines an element of the NSAS lists.  All elements stored in these
/// lists *MUST* be derived from this object.
///
/// The class provides two properties:
///
/// # The method hashKey(), which returns a hash key associated with the
/// object.
/// # Storage for a pointer into the LRU list, used to quickly locate the
/// element when it is being "touched".
///
/// Although it would be possible to require classes stored in the list
/// to have particular methods (and so eliminate the inheritance), this
/// would require the implementor to know something about the list and to
/// provide the appropriate logic.
///
/// Unfortunately, using a base class does not simplify the definition of
/// the list classes (by allowing the list to be defined as a list
/// of base class objects), as the lists are a list of shared pointers to
/// objects, not a list of pointers to object.  Arguments are shared
/// pointers, but a shared pointer to a base class is not a subclass of a
/// shared pointer to a derived class.  For this reason, the type of element
/// being stored is a template parameter.
///
/// This class is inherited from boost::enable_shared_from_this class
/// So within a member function a shared_ptr to current object can be obtained
template <typename T>
class NsasEntry : public boost::enable_shared_from_this <T> {
public:

    /// \brief Default Constructor
    ///
    /// Ensures that the handle into the LRU list is invalid.
    NsasEntry() : valid_(false)
    {}

    /// \brief Virtual Destructor
    virtual ~NsasEntry()
    {}

    /// Copy constructor and assignment operator OK for this class

    /// \brief Hash Key
    ///
    /// Returns the hash key for this element.
    ///
    /// TODO: Consider returning a reference to an internal object, for speed
    virtual HashKey hashKey() const = 0;

    /// \brief Sets the iterator of the object
    ///
    /// Sets the iterator of an object and, as a side effect, marks it as valid.
    ///
    /// \param iterator Iterator of this element in the list
    virtual void setLruIterator(typename isc::util::LruList<T>::iterator iterator) {
        iterator_ = iterator;
        valid_ = true;
    }

    /// \brief Return Iterator
    ///
    /// \return iterator Iterator of this element in the list.
    ///
    /// \exception InvalidLruIterator Thrown if the iterator is not valid.
    virtual typename isc::util::LruList<T>::iterator getLruIterator() const {
        if (! valid_) {
            isc_throw(InvalidLruIterator,
                "pointer of element into LRU list was not valid");
        }
        return iterator_;
    }

    /// \brief Iterator Valid
    ///
    /// \return true if the stored iterator is valid.
    virtual bool iteratorValid() const {
        return valid_;
    }

    /// \brief Invalidate Iterator
    ///
    /// Marks the iterator as invalid; it can oly be set valid again by a call
    /// to setLruIterator.
    virtual void invalidateIterator() {
        valid_ = false;
    }

private:
    typename isc::util::LruList<T>::iterator  iterator_;  ///< Handle into the LRU List
    bool                           valid_;     ///< true if handle is valid
};

} // namespace nsas
} // namespace isc


#endif // NSAS_ENTRY_H
