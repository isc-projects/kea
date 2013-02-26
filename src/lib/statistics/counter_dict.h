// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef COUNTER_DICT_H
#define COUNTER_DICT_H 1

#include <statistics/counter.h>
#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <cassert>
#include <stdexcept>
#include <string>
#include <map>
#include <iterator>
#include <utility>


namespace isc {
namespace statistics {

class CounterDictionary : boost::noncopyable {
private:
    typedef boost::shared_ptr<isc::statistics::Counter> CounterPtr;
    typedef std::map<std::string, CounterPtr> DictionaryMap;
    DictionaryMap dictionary_;
    const size_t items_;
    // Default constructor is forbidden; number of counter items must be
    // specified at the construction of this class.
    CounterDictionary();
public:
    /// The constructor.
    ///
    /// This constructor prepares a dictionary of set of counters.
    /// Initially the dictionary is empty.
    /// Each counter has \a items elements. The counters will be initialized
    /// with 0.
    ///
    /// \param items A number of counter items to hold (greater than 0)
    ///
    /// \throw isc::InvalidParameter \a items is 0
    explicit CounterDictionary(const size_t items) :
        items_(items)
    {
        // The number of items must not be 0
        if (items == 0) {
            isc_throw(isc::InvalidParameter, "Items must not be 0");
        }
    }

    /// \brief Add an element which has a key \a name to the dictionary.
    ///
    /// \param name A key of the element to add
    ///
    /// \throw isc::InvalidParameter an element which has \a name as key
    ///                              already exists
    void addElement(const std::string& name) {
        // throw if the element already exists
        if (dictionary_.find(name) != dictionary_.end()) {
            isc_throw(isc::InvalidParameter,
                      "Element " << name << " already exists");
        }
        assert(items_ != 0);
        // Create a new Counter and add to the map
        dictionary_.insert(
            DictionaryMap::value_type(name, CounterPtr(new Counter(items_))));
    }

    /// \brief Delete the element which has a key \a name from the dictionary.
    ///
    /// \param name A key of the element to delete
    ///
    /// \throw isc::OutOfRange an element which has \a name as key does not
    ///                        exist
    void deleteElement(const std::string& name) {
        const size_t result = dictionary_.erase(name);
        if (result != 1) {
            // If an element with specified name does not exist, throw
            // isc::OutOfRange.
            isc_throw(isc::OutOfRange,
                      "Element " << name << " does not exist");
        }
    }

    /// \brief Get a reference to a %Counter which has \a name as key
    ///
    /// \param name A key of the element
    ///
    /// \throw isc::OutOfRange an element which has \a name as key does not
    ///                        exist
    Counter& getElement(const std::string& name) {
        DictionaryMap::const_iterator i = dictionary_.find(name);
        if (i != dictionary_.end()) {
            // the key was found. return the element.
            return (*(i->second));
        } else {
            // If an element with specified name does not exist, throw
            // isc::OutOfRange.
            isc_throw(isc::OutOfRange,
                      "Element " << name << " does not exist");
        }
    }

    /// \brief Same as \c getElement()
    Counter& operator[](const std::string& name) {
        return (getElement(name));
    }

    /// \brief \c ConstIterator is a constant iterator that provides an
    /// interface for enumerating name of zones stored in CounterDictionary.
    ///
    /// This class is derived from boost::iterator_facade and uses pImpl
    /// idiom not to expose implementation detail of
    /// CounterDictionary::iterator.
    ///
    /// It is intended to walk through the elements when sending the
    /// counters to statistics module.
    class ConstIterator :
        public boost::iterator_facade<ConstIterator,
                                const std::string,
                                boost::forward_traversal_tag>
    {
        public:
            /// \brief The constructor.
            ConstIterator() {}

            /// \brief Constructor from implementation detail
            /// DictionaryMap::const_iterator
            ConstIterator(DictionaryMap::const_iterator iterator) :
                iterator_(iterator)
            {}

        private:
            // An internal method to increment this iterator.
            void increment() {
                ++iterator_;
                return;
            }

            // An internal method to check equality.
            bool equal(const ConstIterator& other) const {
                return (iterator_ == other.iterator_);
            }

            // An internal method to dereference this iterator.
            const value_type& dereference() const {
                return (iterator_->first);
            }

        private:
            friend class boost::iterator_core_access;
            DictionaryMap::const_iterator iterator_;
    };

    /// \brief Get an iterator for the beginning of the dictionary.
    ConstIterator begin() const {
        return (CounterDictionary::ConstIterator(dictionary_.begin()));
    }

    /// \brief Get an iterator for the end of the dictionary.
    ConstIterator end() const {
        return (CounterDictionary::ConstIterator(dictionary_.end()));
    }

    typedef ConstIterator const_iterator;
};

}   // namespace statistics
}   // namespace isc

#endif
