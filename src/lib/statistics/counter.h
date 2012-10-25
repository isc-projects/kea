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

#ifndef __COUNTER_H
#define __COUNTER_H 1

#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <vector>

namespace {
const unsigned int InitialValue = 0;
} // anonymous namespace

namespace isc {
namespace statistics {

class Counter : boost::noncopyable {
public:
    typedef unsigned int Type;
    typedef unsigned int Value;

private:
    std::vector<Counter::Value> counters_;

public:
    /// The constructor.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \param items A number of counter items to hold (greater than 0)
    ///
    /// \throw isc::InvalidParameter \a items is 0
    explicit Counter(const size_t items) :
        counters_(items, InitialValue)
    {
        if (items == 0) {
            isc_throw(isc::InvalidParameter, "Items must not be 0");
        }
    };

    /// The destructor.
    ///
    /// This method never throws an exception.
    ~Counter() {};

    /// \brief Increment a counter item specified with \a type.
    ///
    /// \param type %Counter item to increment
    ///
    /// \throw isc::OutOfRange \a type is invalid
    void inc(const Counter::Type type) {
        if (type >= counters_.size()) {
            isc_throw(isc::OutOfRange, "Counter type is out of range");
        }
        ++counters_.at(type);
        return;
    };

    /// \brief Get the value of a counter item specified with \a type.
    ///
    /// \param type %Counter item to get the value of
    ///
    /// \throw isc::OutOfRange \a type is invalid
    const Counter::Value& get(const Counter::Type type) const {
        if (type >= counters_.size()) {
            isc_throw(isc::OutOfRange, "Counter type is out of range");
        }
        return (counters_.at(type));
    };
};

}   // namespace statistics
}   // namespace isc

#endif // __COUNTER_H
