// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef UTIL_THREADS_CONDVAR_H
#define UTIL_THREADS_CONDVAR_H 1

#include "lock.h"

#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace util {
namespace thread {

// This class object internally holds pthread_cond_t and pthread_mutex_t
class CondVar : boost::noncopyable {
public:
    CondVar();
    ~CondVar();
private:
    class Impl;
    Impl* impl_;
};

} // namespace thread
} // namespace util
} // namespace isc

#endif UTIL_THREADS_CONDVAR_H

// Local Variables:
// mode: c++
// End:
