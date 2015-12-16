// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
    RdataPimplHolder(T* obj = NULL) :
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
