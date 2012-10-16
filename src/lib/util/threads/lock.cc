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

using std::auto_ptr;

namespace isc {
namespace util {
namespace thread {

class Mutex::Impl {
public:
    Impl() :
        locked_count(0)
    {}
    pthread_mutex_t mutex;
    // Only in debug mode
    size_t locked_count;
};

namespace {

struct Deinitializer {
    Deinitializer(pthread_mutexattr_t& attributes):
        attributes_(attributes)
    {}
    ~Deinitializer() {
        const int result = pthread_mutexattr_destroy(&attributes_);
        // This should never happen. According to the man page,
        // if there's error, it's our fault.
        assert(result == 0);
    }
    pthread_mutexattr_t& attributes_;
};

}

Mutex::Mutex() :
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
            isc_throw(isc::InvalidOperation, std::strerror(result));
    }
    Deinitializer deinitializer(attributes);
    // TODO: Distinguish if debug mode is enabled in compilation.
    // If so, it should be PTHREAD_MUTEX_NORMAL or NULL
    result = pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_ERRORCHECK);
    if (result != 0) {
        isc_throw(isc::InvalidOperation, std::strerror(result));
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
            isc_throw(isc::InvalidOperation, std::strerror(result));
    }
}

Mutex::~Mutex() {
    if (impl_ != NULL) {
        const int result = pthread_mutex_destroy(&impl_->mutex);
        const bool locked = impl_->locked_count != 0;
        delete impl_;
        // We don't want to throw from the destructor. Also, if this ever
        // fails, something is really screwed up a lot.
        assert(result == 0);

        // We should not try to destroy a locked mutex, bad threaded monsters
        // could get loose if we ever do and it is also forbidden by pthreads.

        // This should not be possible to happen, since the
        // pthread_mutex_destroy should check for it already. But it seems
        // there are systems that don't check it.
        assert(!locked);
    }
}

void
Mutex::lock() {
    assert(impl_ != NULL);
    const int result = pthread_mutex_lock(&impl_->mutex);
    if (result != 0) {
        isc_throw(isc::InvalidOperation, std::strerror(result));
    }
    ++impl_->locked_count; // Only in debug mode
}

bool
Mutex::tryLock() {
    assert(impl_ != NULL);
    const int result = pthread_mutex_trylock(&impl_->mutex);

    // In the case of pthread_mutex_trylock(), if it is called on a
    // locked mutex from the same thread, some platforms (such as fedora
    // and debian) return EBUSY whereas others (such as centos 5) return
    // EDEADLK. We return false and don't pass the lock attempt in both
    // cases.
    if (result == EBUSY || result == EDEADLK) {
        return (false);
    } else if (result != 0) {
        isc_throw(isc::InvalidOperation, std::strerror(result));
    }
    ++impl_->locked_count; // Only in debug mode
    return (true);
}

void
Mutex::unlock() {
    assert(impl_ != NULL);
    --impl_->locked_count; // Only in debug mode
    const int result = pthread_mutex_unlock(&impl_->mutex);
    assert(result == 0); // This should never be possible
}

// TODO: Disable in non-debug build
bool
Mutex::locked() const {
    return (impl_->locked_count != 0);
}

}
}
}
