#ifndef __COUNTER_DICT_H
#define __COUNTER_DICT_H 1

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
        /// Note: \a items must be greater than 0; otherwise thist constructor
        /// causes assertion failure.
        /// 
        /// \param items A number of counter items to hold (greater than 0)
        CounterDictionary(const size_t items);

        /// The destructor.
        ///
        /// This method never throws an exception.
        ~CounterDictionary();

        /// \brief Add an element
        ///
        /// \throw isc::InvalidParameter \a element alerady exists.
        ///
        /// \param element A name of the element to append
        void addElement(const std::string& element);

        /// \brief Delete
        ///
        /// \throw isc::OutOfRange \a element does not exist.
        ///
        /// \param element A name of the element to delete
        void deleteElement(const std::string& element);

        /// \brief Lookup
        ///
        /// \throw isc::OutOfRange \a element does not exist.
        ///
        /// \param element A name of the element to get the counters
        Counter& getElement(const std::string &element) const;

        /// Same as getElement()
        Counter& operator[](const std::string &element) const;

        /// Typedef for the pair which represents an element of
        /// CounterDictionary. This type is used for the iterator.
        typedef std::pair<const std::string&, const Counter&> ValueType;

        /// \brief \c ConstIterator is a constant iterator that provides an
        /// interface for accessing elements stored in CounterDictionary.
        ///
        /// This class is derived from boost::iterator_facade and uses pImpl
        /// idiom not to expose implementation detail of
        /// CounterDictionary::iterator.
        ///
        /// It is intended to walk through the elements when sending the
        /// counters to statistics module.
        class ConstIterator :
            public boost::iterator_facade<ConstIterator,
                                   const ValueType,
                                   boost::forward_traversal_tag>
        {
            private:
                boost::scoped_ptr<CounterDictionaryConstIteratorImpl> impl_;
            public:
                /// The constrcutor.
                ///
                /// This constructor is mostly exception free. But it may still
                /// throw a standard exception if memory allocation fails
                /// inside the method.
                ConstIterator();
                /// The destrcutor.
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
                const value_type dereference() const;
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
