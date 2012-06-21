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

#include <vector>

#include <boost/noncopyable.hpp>

#include <statistics/counter.h>

namespace {
const unsigned int InitialValue = 0;
} // namespace

namespace isc {
namespace statistics {

class CounterImpl : boost::noncopyable {
    private:
        std::vector<Counter::Value> counters_;
    public:
        CounterImpl(const size_t nelements);
        ~CounterImpl();
        void inc(const Counter::Type&);
        const Counter::Value& get(const Counter::Type&) const;
};

CounterImpl::CounterImpl(const size_t items) :
    counters_(items, InitialValue)
{
    if (items == 0) {
        isc_throw(isc::InvalidParameter, "Items must not be 0");
    }
}

CounterImpl::~CounterImpl() {}

void
CounterImpl::inc(const Counter::Type& type) {
    if(type >= counters_.size()) {
        isc_throw(isc::OutOfRange, "Counter type is out of range");
    }
    ++counters_.at(type);
    return;
}

const Counter::Value&
CounterImpl::get(const Counter::Type& type) const {
    if(type >= counters_.size()) {
        isc_throw(isc::OutOfRange, "Counter type is out of range");
    }
    return (counters_.at(type));
}

Counter::Counter(const size_t items) : impl_(new CounterImpl(items))
{}

Counter::~Counter() {}

void
Counter::inc(const Type& type) {
    impl_->inc(type);
    return;
}

const Counter::Value&
Counter::get(const Type& type) const {
    return (impl_->get(type));
}

}   // namespace statistics
}   // namespace isc
