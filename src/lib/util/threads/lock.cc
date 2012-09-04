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

#include "lock.h"

#include <exceptions/exceptions.h>

#include <cstring>
#include <memory>
#include <cerrno>
#include <cassert>

#include <pthread.h>

using namespace std;

namespace isc {
namespace util {
namespace thread {

class Mutex::Impl {
public:
    Impl() :
        locked(0)
    {}
    pthread_mutex_t mutex;
    // Only in debug mode
    size_t locked;
};

namespace {

struct Deinitializer {
    Deinitializer(pthread_mutexattr_t& attributes):
        attributes_(attributes)
    {}
    ~ Deinitializer() {
        int result = pthread_mutexattr_destroy(&attributes_);
        if (result != 0) {
            // This really should not happen. We might as well
            // try to use assert here.
            isc_throw(isc::InvalidOperation, strerror(result));
        }
    }
    pthread_mutexattr_t& attributes_;
};

}

Mutex::Mutex(bool recursive) :
    impl_(NULL)
{
    pthread_mutexattr_t attributes;
    int result = pthread_mutexattr_init(&attributes);
    switch (result) {
        case 0: // All 0K
            break;
        case ENOMEM:
            throw std::bad_alloc();
        default:
            isc_throw(isc::InvalidOperation, strerror(result));
    }
    Deinitializer deinitializer(attributes);
    // TODO: Distinguish if debug mode is enabled in compilation.
    // If so, it should be PTHREAD_MUTEX_NORMAL or NULL
    int type = PTHREAD_MUTEX_ERRORCHECK;
    if (recursive) {
        type = PTHREAD_MUTEX_RECURSIVE;
    }
    // Stop on first error you find and store the result.
    result = pthread_mutexattr_settype(&attributes, type) ||
        pthread_mutexattr_setrobust(&attributes, PTHREAD_MUTEX_ROBUST);
    if (result != 0) {
        isc_throw(isc::InvalidOperation, strerror(result));
    }
    auto_ptr<Impl> impl(new Impl);
    result = pthread_mutex_init(&impl->mutex, &attributes);
    switch (result) {
        case 0: // All 0K
            impl_ = impl.release();
            break;
        case ENOMEM:
        case EAGAIN:
            throw std::bad_alloc();
        default:
            isc_throw(isc::InvalidOperation, strerror(result));
    }
}

Mutex::~ Mutex() {
    if (impl_ != NULL) {
        int result = pthread_mutex_destroy(&impl_->mutex);
        bool locked = impl_->locked != 0;
        delete impl_;
        if (result != 0) {
            // Yes, really throwing from the destructor.
            // But the error should not happen during normal
            // operations, this means something is screwed up
            // and must be fixed.
            isc_throw(isc::InvalidOperation, strerror(result));
        }
        if (locked) {
            isc_throw(isc::InvalidOperation, "Destroying locked mutex");
        }
    }
}

void
Mutex::lock() {
    assert(impl_ != NULL);
    int result = pthread_mutex_lock(&impl_->mutex);
    if (result != 0) {
        isc_throw(isc::InvalidOperation, strerror(result));
    }
    impl_->locked ++; // Only in debug mode
}

void
Mutex::unlock() {
    assert(impl_ != NULL);
    impl_->locked --; // Only in debug mode
    int result = pthread_mutex_unlock(&impl_->mutex);
    if (result != 0) {
        isc_throw(isc::InvalidOperation, strerror(result));
    }
}

}
}
}
