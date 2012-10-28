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

#include <string>
#include <vector>
#include <utility>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <exceptions/exceptions.h>
#include <statistics/counter.h>

namespace isc {
namespace statistics {

class CounterDictionaryImpl;
class CounterDictionaryConstIteratorImpl;

class CounterDictionary : boost::noncopyable {
private:
    boost::scoped_ptr<CounterDictionaryImpl> impl_;
    // Default constructor is forbidden; number of counter items must be
    // specified at the construction of this class.
    CounterDictionary();
public:
    /// The constructor.
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \param items A number of counter items to hold (greater than 0)
    ///
    /// \throw isc::InvalidParameter \a items is 0
    CounterDictionary(const size_t items);

    /// The destructor.
    ///
    /// This method never throws an exception.
    ~CounterDictionary();

    /// \brief Add an element
    ///
    /// \throw isc::InvalidParameter \a element already exists.
    ///
    /// \param name A name of the element to append
    void addElement(const std::string& name);

    /// \brief Delete
    ///
    /// \throw isc::OutOfRange \a element does not exist.
    ///
    /// \param name A name of the element to delete
    void deleteElement(const std::string& name);

    /// \brief Lookup
    ///
    /// \throw isc::OutOfRange \a element does not exist.
    ///
    /// \param name A name of the element to get the counters
    Counter& getElement(const std::string &name) const;

    /// Same as getElement()
    Counter& operator[](const std::string &name) const;

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
        private:
            boost::scoped_ptr<CounterDictionaryConstIteratorImpl> impl_;
        public:
            /// The constructor.
            ///
            /// This constructor is mostly exception free. But it may still
            /// throw a standard exception if memory allocation fails
            /// inside the method.
            ConstIterator();
            /// The destructor.
            ///
            /// This method never throws an exception.
            ~ConstIterator();
            /// The assignment operator.
            ///
            /// This method is mostly exception free. But it may still
            /// throw a standard exception if memory allocation fails
            /// inside the method.
            ConstIterator& operator=(const ConstIterator &source);
            /// The copy constructor.
            ///
            /// This constructor is mostly exception free. But it may still
            /// throw a standard exception if memory allocation fails
            /// inside the method.
            ConstIterator(const ConstIterator& source);
            /// The constructor from implementation detail.
            ///
            /// This method is used to create an instance of ConstIterator
            /// by CounterDict::begin() and CounterDict::end().
            ///
            /// This constructor is mostly exception free. But it may still
            /// throw a standard exception if memory allocation fails
            /// inside the method.
            ConstIterator(
                const CounterDictionaryConstIteratorImpl& source);
        private:
            /// \brief An internal method to increment this iterator.
            void increment();
            /// \brief An internal method to check equality.
            bool equal(const ConstIterator& other) const;
            /// \brief An internal method to dereference this iterator.
            const value_type& dereference() const;
        private:
            friend class boost::iterator_core_access;
    };

    typedef ConstIterator const_iterator;

    /// \brief Return an iterator corresponding to the beginning of the
    /// elements stored in CounterDictionary.
    ///
    /// This method is mostly exception free. But it may still throw a
    /// standard exception if memory allocation fails inside the method.
    const_iterator begin() const;

    /// \brief Return an iterator corresponding to the end of the elements
    /// stored in CounterDictionary.
    ///
    /// This method is mostly exception free. But it may still throw a
    /// standard exception if memory allocation fails inside the method.
    const_iterator end() const;
};

}   // namespace statistics
}   // namespace isc

#endif
