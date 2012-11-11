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

#ifndef LRU_LIST_H
#define LRU_LIST_H

#include <list>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <util/locks.h>

namespace isc {
namespace util {

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
    typedef typename std::list<boost::shared_ptr<T> > lru_list;
    typedef typename lru_list::iterator               iterator;

    /// \brief Dropped Operation
    ///
    /// When an object is dropped from the LRU list because it has not been
    /// accessed for some time, it is possible that the action should trigger
    /// some other functions.  For this reason, it is possible to register
    /// a list-wide functor object to execute in this casee.
    ///
    /// Note that the function does not execute as the result of a call to
    /// remove() - that is an explicit call and it is assumed that the caller
    /// will handle any additional operations needed.
    class Dropped {
    public:
        /// \brief Constructor
        Dropped(){}

        /// \brief Virtual Destructor
        virtual ~Dropped(){}

        /// \brief Dropped Object Handler
        ///
        /// Function object called when the object drops off the end of the
        /// LRU list.
        ///
        /// \param drop Object being dropped.
        virtual void operator()(T* drop) const = 0;
    };

    /// \brief Constructor
    ///
    /// \param max_size Maximum size of the list before elements are dropped.
    /// \param dropped Pointer to a function object that will get called as
    /// elements are dropped.  This object will be stored using a shared_ptr,
    /// so should be allocated with new().
    LruList(uint32_t max_size = 1000, Dropped* dropped = NULL) :
        max_size_(max_size), count_(0), dropped_(dropped)
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

    /// \brief Drop All the Elements in the List .
    ///
    /// All the elements will be dropped from the list container, and their
    /// drop handler(if there is one) will be called, when done, the size of
    /// of list will be 0.
    virtual void clear();

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
    /// \param max_size New maximum list size
    virtual void setMaxSize(uint32_t max_size) {
        max_size_ = max_size;
    }

private:
    locks::mutex                   mutex_;     ///< List protection
    std::list<boost::shared_ptr<T> >    lru_;       ///< The LRU list itself
    uint32_t                            max_size_;  ///< Max size of the list
    uint32_t                            count_;     ///< Count of elements
    boost::shared_ptr<Dropped>          dropped_;   ///< Dropped object
};

// Add entry to the list
template <typename T>
void LruList<T>::add(boost::shared_ptr<T>& element) {

    // Protect list against concurrent access
    locks::scoped_lock<locks::mutex> lock(mutex_);

    // Add the entry and set its pointer field to point into the list.
    // insert() is used to get the pointer.
    element->setLruIterator(lru_.insert(lru_.end(), element));

    // ... and update the count while we have the mutex.
    ++count_;

    // If the count takes us above the maximum size of the list, remove elements
    // from the front.  The current list size could be more than one above the
    // maximum size of the list if the maximum size was changed after
    // construction.
    while (count_ > max_size_) {
        if (!lru_.empty()) {

            // Run the drop handler (if there is one) on the

            // to-be-dropped object.
            if (dropped_) {
                (*dropped_)(lru_.begin()->get());
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
    if (element->iteratorValid()) {

        // Is valid, so protect list against concurrent access
        locks::scoped_lock<locks::mutex> lock(mutex_);

        lru_.erase(element->getLruIterator());  // Remove element from list
        element->invalidateIterator();          // Invalidate pointer
        --count_;                               // One less element
    }
}

// Touch an element - remove it from the list and add to the end
template <typename T>
void LruList<T>::touch(boost::shared_ptr<T>& element) {

    // As before, if the pointer is not valid, this is a no-op.
    if (element->iteratorValid()) {

        // Protect list against concurrent access
        locks::scoped_lock<locks::mutex> lock(mutex_);

        // Move the element to the end of the list.
        lru_.splice(lru_.end(), lru_, element->getLruIterator());

        // Update the iterator in the element to point to it.  We can
        // offset from end() as a list has a bidirectional iterator.
        iterator i = lru_.end();
        element->setLruIterator(--i);
    }
}

// Clear the list-  when done, the size of list will be 0.
template <typename T>
void LruList<T>::clear() {
    // Protect list against concurrent access
    locks::scoped_lock<locks::mutex> lock(mutex_);

    // ... and update the count while we have the mutex.
    count_ = 0;
    typename std::list<boost::shared_ptr<T> >::iterator iter;
    if (dropped_) {
        for (iter = lru_.begin(); iter != lru_.end(); ++iter) {
            // Call the drop handler.
            (*dropped_)(iter->get());
        }
    }

    lru_.clear();
}

}   // namespace util
}   // namespace isc

#endif // LRU_LIST_H
