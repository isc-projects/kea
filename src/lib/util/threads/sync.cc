// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include "sync.h"

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
    Impl()
#ifdef ENABLE_DEBUG
        : locked_count(0)
#endif // ENABLE_DEBUG
    {}

    pthread_mutex_t mutex;
#ifdef ENABLE_DEBUG
    size_t locked_count;
#endif // ENABLE_DEBUG
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

    // If debug mode is enabled in compilation, use the slower
    // error-checking mutexes that detect deadlocks. Otherwise, use fast
    // mutexes which don't. See the pthread_mutexattr_settype() POSIX
    // documentation which describes these type attributes.
#ifdef ENABLE_DEBUG
    result = pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_ERRORCHECK);
#else
    result = pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_NORMAL);
#endif // ENABLE_DEBUG
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

#ifdef ENABLE_DEBUG
        const bool locked = impl_->locked_count != 0;
#endif // ENABLE_DEBUG

        delete impl_;
        // We don't want to throw from the destructor. Also, if this ever
        // fails, something is really screwed up a lot.
        assert(result == 0);

#ifdef ENABLE_DEBUG
        // We should not try to destroy a locked mutex, bad threaded monsters
        // could get loose if we ever do and it is also forbidden by pthreads.

        // This should not be possible to happen, since the
        // pthread_mutex_destroy should check for it already. But it seems
        // there are systems that don't check it.
        assert(!locked);
#endif // ENABLE_DEBUG
    }
}

#ifdef ENABLE_DEBUG

void
Mutex::postLockAction() {
    assert(impl_->locked_count == 0);
    ++impl_->locked_count;
}

void
Mutex::preUnlockAction(bool throw_ok) {
    if (impl_->locked_count == 0) {
        if (throw_ok) {
            isc_throw(isc::InvalidOperation,
                      "Unlock attempt for unlocked mutex");
        } else {
            assert(false);
        }
    }
    --impl_->locked_count;
}

bool
Mutex::locked() const {
    return (impl_->locked_count != 0);
}

#endif // ENABLE_DEBUG

void
Mutex::lock() {
    assert(impl_ != NULL);
    const int result = pthread_mutex_lock(&impl_->mutex);
    if (result != 0) {
        isc_throw(isc::InvalidOperation, std::strerror(result));
    }
#ifdef ENABLE_DEBUG
    postLockAction();           // Only in debug mode
#endif // ENABLE_DEBUG
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
#ifdef ENABLE_DEBUG
    postLockAction();           // Only in debug mode
#endif // ENABLE_DEBUG
    return (true);
}

void
Mutex::unlock() {
    assert(impl_ != NULL);
#ifdef ENABLE_DEBUG
    preUnlockAction(false);     // Only in debug mode.  Ensure no throw.
#endif // ENABLE_DEBUG
    const int result = pthread_mutex_unlock(&impl_->mutex);
    assert(result == 0); // This should never be possible
}

class CondVar::Impl {
public:
    Impl() {
        const int result = pthread_cond_init(&cond_, NULL);
        if (result != 0) {
            isc_throw(isc::Unexpected, "pthread_cond_init failed: "
                      << std::strerror(result));
        }
    }
    ~Impl() {
        const int result = pthread_cond_destroy(&cond_);

        // This can happen if we try to destroy cond_ while some other thread
        // is waiting on it.  assert() may be too strong for such a case,
        // but we cannot safely destroy cond_ anyway.  In order to avoid
        // throwing from a destructor we simply let the process die.
        assert(result == 0);
    }

    // For convenience allow the main class to access this directly.
    pthread_cond_t cond_;
};

CondVar::CondVar() : impl_(new Impl)
{}

CondVar::~CondVar() {
    delete impl_;
}

void
CondVar::wait(Mutex& mutex) {
#ifdef ENABLE_DEBUG
    mutex.preUnlockAction(true);    // Only in debug mode
    const int result = pthread_cond_wait(&impl_->cond_, &mutex.impl_->mutex);
    mutex.postLockAction();     // Only in debug mode
#else
    const int result = pthread_cond_wait(&impl_->cond_, &mutex.impl_->mutex);
#endif
    // pthread_cond_wait should normally succeed unless mutex is completely
    // broken.
    if (result != 0) {
        isc_throw(isc::BadValue, "pthread_cond_wait failed unexpectedly: " <<
                  std::strerror(result));
    }
}

void
CondVar::signal() {
    const int result = pthread_cond_signal(&impl_->cond_);

    // pthread_cond_signal() can only fail when if cond_ is invalid.  It
    //should be impossible as long as this is a valid CondVar object.
    assert(result == 0);
}

}
}
}
