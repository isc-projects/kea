// Copyright (C) 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DNS_RDATA_PIMPL_HOLDER_H
#define DNS_RDATA_PIMPL_HOLDER_H 1

#include <boost/noncopyable.hpp>

#include <cstddef> // for NULL

namespace isc {
namespace dns {
namespace rdata {

template <typename T>
class RdataPimplHolder : boost::noncopyable {
public:
    explicit RdataPimplHolder(T* obj = NULL) :
        obj_(obj)
    {}

    ~RdataPimplHolder() {
        delete obj_;
    }

    void reset(T* obj = NULL) {
        delete obj_;
        obj_ = obj;
    }

    T* get() {
        return (obj_);
    }

    T* release() {
        T* obj = obj_;
        obj_ = NULL;
        return (obj);
    }

private:
    T* obj_;
};

} // namespace rdata
} // namespace dns
} // namespace isc

#endif // DNS_RDATA_PIMPL_HOLDER_H
