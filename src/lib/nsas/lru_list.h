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

#ifndef __LRU_LIST_H
#define __LRU_LIST_H

#include <list>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include "config.h"


namespace isc {
namespace nsas {

/// \brief LRU List
///
/// Provides the LRU list for the zone and nameserver objects.  The list is
/// created with a specific size.  Entries are added to the back of the list
/// and removed from the front.  It is also possible to pull an element out
/// of the middle of the list and add it to the end of the list, an action that
/// should be done when the element is referenced.
///
/// It is not intended that the class be copied, and the derivation from
/// boost::noncopyable enforces this.
template <typename T>
class LruList : boost::noncopyable {
public:
    typedef typename std::list<boost::shared_ptr<T> >::iterator iterator;

    /// \brief Expired Operation
    ///
    /// When an object is removed from the LRU list because it has not been
    /// accessed for some time, it is possible that the action should trigger
    /// some other functions.  For this reason, it is possible to register
    /// a list-wide functor object to execute in this casee.
    ///
    /// Note that the function does not execute as the result of a call to
    /// remove() - that is an explicit call and it is assumed that the caller
    /// will handle any additional operations needed.
    class Expired {
    public:

        /// \brief Expired Object Handler
        ///
        /// Function object called when the object expires from the LRU list.
        ///
        /// \param expired Expired object.
        virtual void operator()(boost::shared_ptr<T>& element) = 0;
    };

    /// \brief Element of an LRU List
    ///
    /// This defines an element of the LRU List.  All objects stored in one
    /// of these lists MUST be derived from this element.
    ///
    /// The class provides the storage for a pointer into the LRU list,
    /// used to quickly locate the element when it is being "touched".
    ///
    /// Although it would be possible to require classes stored in the list
    /// to have particular methods (and so eliminate the inheritance), this
    /// would require the implementor to know something about the list and to
    /// provide the appropriate logic.
    ///
    /// Unfortunately, using a base class does not simplify the definition of
    /// the LRU list list class (by allowing the list to be defined as a list
    /// of base class objects), as the list is a list of shared pointers to
    /// objects, not a list of pointers to object.  Arguments are shared
    /// pointers, but a shared pointer to a base class is not a subclass of a
    /// shared pointer to a derived class.  For this reason, the list type
    /// is a template parameter.
    struct Element {
        typename LruList<T>::iterator  handle_;    ///< Handle into the LRU List
        bool                           valid_;     ///< true if handle is valid

        Element() : valid_(false)
        {}
    };

    /// \brief Constructor
    ///
    /// \param max_size Maximum size of the list before elements are dropped.
    /// \param expired Pointer to a function object that will get called as
    /// elements are dropped.  This object will be stored using a shared_ptr,
    /// so should be allocated with new().
    LruList(uint32_t max_size = 1000, Expired* expired = NULL) :
        max_size_(max_size), count_(0), expired_(expired)
    {}

    /// \brief Virtual Destructor
    virtual ~LruList()
    {}

    /// \brief Add Element
    ///
    /// Add a new element to the end of the list.
    ///
    /// \param element Reference to the element to add.
    ///
    /// \return Handle describing the element in the LRU list.
    virtual void add(boost::shared_ptr<T>& element);

    /// \brief Remove Element
    ///
    /// Removes an element from the list.  If the element is not present (i.e.
    /// its internal list pointer is invalid), this is a no-op.
    ///
    /// \param element Reference to the element to remove.
    virtual void remove(boost::shared_ptr<T>& element);

    /// \brief Touch Element
    ///
    /// The name comes from the Unix "touch" command.  All this does is to
    /// move the specified entry from the middle of the list to the end of
    /// the list.
    ///
    /// \param element Reference to the element to touch.
    virtual void touch(boost::shared_ptr<T>& element);

    /// \brief Return Size of the List
    ///
    /// An independent count is kept of the list size, as list.size() may take
    /// some time if the list is big.
    ///
    /// \return Number of elements in the list
    virtual uint32_t size() const {

        // Don't bother to lock the mutex.  If an update is in progress, we
        // receive either the value just before the update or just after it.
        // Either way, this call could have come just before or just after
        // that operation, so the value would have been just as uncertain.
        return count_;
    }

    /// \brief Return Maximum Size
    ///
    /// \return Maximum size of the list
    virtual uint32_t getMaxSize() const {
        return max_size_;
    }

    /// \brief Set Maximum Size
    ///
    /// \param new_size New maximum list size
    virtual void setMaxSize(uint32_t max_size) {
        max_size_ = max_size;
    }

private:
    boost::mutex                        mutex_;     ///< List protection
    std::list<boost::shared_ptr<T> >    lru_;       ///< The LRU list itself
    uint32_t                            max_size_;  ///< Max size of the list
    uint32_t                            count_;     ///< Count of elements
    boost::shared_ptr<Expired>          expired_;   ///< Expired object
};

// Add entry to the list
template <typename T>
void LruList<T>::add(boost::shared_ptr<T>& element) {

    // Protect list against concurrent access
    boost::interprocess::scoped_lock<boost::mutex> lock(mutex_);

    // Add the entry and set its pointer field to point into the list.
    // insert() is used to get the pointer.
    element.get()->handle_ = lru_.insert(lru_.end(), element);
    element.get()->valid_ = true;

    // ... and update the count while we have the mutex.
    ++count_;

    // If the count takes us above the maximum size of the list, remove elements
    // from the front.  The current list size could be more than one above the
    // maximum size of the list if the maximum size was changed after
    // construction.
    while (count_ > max_size_) {
        if (!lru_.empty()) {

            // Run the expiration handler (if there is one) on the
            // to-be-expired object.
            if (expired_) {
                (*expired_)(*lru_.begin());
            }

            // ... and get rid of it from the list
            lru_.pop_front();
            --count_;
        }
        else {

            // TODO: Log this condition (count_ > 0 when list empty) -
            // it should not happen
            count_ = 0;
            break;
        }
    }
}

// Remove an element from the list
template <typename T>
void LruList<T>::remove(boost::shared_ptr<T>& element) {

    // An element can only be removed it its internal pointer is valid.
    // If it is, the pointer can be used to access the list because no matter
    // what other elements are added or removed, the pointer remains valid.
    //
    // If the pointer is not valid, this is a no-op.
    if (element.get()->valid_) {

        // Is valid, so protect list against concurrent access
        boost::interprocess::scoped_lock<boost::mutex> lock(mutex_);

        element.get()->valid_ = false;      // Invalidate element
        lru_.erase(element.get()->handle_); // Remove element from list
        --count_;                           // One less element
    }
}

// Touch an element - remove it from the list and add to the end
template <typename T>
void LruList<T>::touch(boost::shared_ptr<T>& element) {

    // As before, if the pointer is not valid, this is a no-op.
    if (element.get()->valid_) {

        // Protect list against concurrent access
        boost::interprocess::scoped_lock<boost::mutex> lock(mutex_);

        // Move the element to the end of the list.
        lru_.splice(lru_.end(), lru_, element.get()->handle_);

        // Update the iterator in the element to point to it.  We can
        // offset from end() as a list has a bidirectional iterator.
        iterator i = lru_.end();
        element.get()->handle_ = --i;
    }
}

}   // namespace nsas
}   // namespace isc

#endif // __LRU_LIST_H
