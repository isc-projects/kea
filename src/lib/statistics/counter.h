#ifndef __COUNTER_H
#define __COUNTER_H 1

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

namespace isc {
namespace statistics {

// forward declaration for pImpl idiom
class CounterImpl;

class Counter : boost::noncopyable {
    private:
        boost::scoped_ptr<CounterImpl> impl_;
    public:
        typedef unsigned int Type;
        typedef unsigned int Value;

        /// The constructor.
        ///
        /// This constructor is mostly exception free. But it may still throw
        /// a standard exception if memory allocation fails inside the method.
        ///
        /// Note: \a items must be greater than 0. Otherwise this constructor
        /// causes an assertion failure.
        /// 
        /// \param items A number of counter items to hold (greater than 0)
        Counter(const size_t items);

        /// The destructor.
        ///
        /// This method never throws an exception.
        ~Counter();

        /// \brief Increment a counter item specified with \a type.
        ///
        /// Note: \a type must be valid counter type. Otherwise this method
        /// causes an assertion failure.
        /// 
        /// \param type %Counter item to increment
        void inc(const Type& type);

        /// \brief Get the value of a counter item specified with \a type.
        /// 
        /// \param type %Counter item to get the value of
        const Value& get(const Type& type) const;
};

}   // namespace statistics
}   // namespace isc

#endif
