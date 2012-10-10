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

#include "condvar.h"

#include <exceptions/exceptions.h>

#include <cassert>
#include <pthread.h>

namespace isc {
namespace util {
namespace thread {

class CondVar::Impl {
public:
    Impl() {
        const int result = pthread_cond_init(&cond, NULL);
        if (result != 0) {
            isc_throw(isc::Unexpected, "pthread_cond_init failed: "
                      << std::strerror(result));
        }
    }
    ~Impl() {
        const int result = pthread_cond_destroy(&cond);
        assert(result == 0);
    }

private:
    pthread_cond_t cond;
};

CondVar::CondVar() : impl_(new Impl)
{}

CondVar::~CondVar() {
    delete impl_;
}

} // namespace thread
} // namespace util
} // namespace isc
