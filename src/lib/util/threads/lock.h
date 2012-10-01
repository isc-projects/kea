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

#ifndef B10_THREAD_LOCK_H
#define B10_THREAD_LOCK_H

#include <boost/noncopyable.hpp>

#include <cstdlib> // for NULL.

namespace isc {
namespace util {
namespace thread {

/// \brief Mutex with very simple interface
///
/// Since mutexes are very system dependant, we create our own wrapper around
/// whatever is available on the system and hide it.
///
/// To use this mutex, create it and then lock and unlock it by creating the
/// Mutex::Locker object.
///
/// Also, as mutex is a low-level system object, an error might happen at any
/// operation with it. We convert many errors to the isc::InvalidOperation,
/// since the errors usually happen only when used in a wrong way. Any methods,
/// constructors or even destructors in this class can throw. Allocation errors
/// are converted to std::bad_alloc (for example when OS-dependant limit of
/// mutexes is exceeded).
///
/// The current interface is somewhat minimalistic. If we ever need more, we
/// can add it later.
class Mutex : public boost::noncopyable {
public:
    /// \brief Constructor.
    ///
    /// Creates a mutex. It is a non-recursive mutex (can be locked just once,
    /// if the same threads tries to lock it again, Bad Things Happen).
    ///
    /// Depending on compilation parameters and OS, the mutex may or may not
    /// do some error and sanity checking. However, such checking is meant
    /// only to aid development, not rely on it as a feature.
    ///
    /// \throw std::bad_alloc In case allocation of something (memory, the
    ///     OS mutex) fails.
    /// \throw isc::InvalidOperation Other unspecified errors around the mutex.
    ///     This should be rare.
    Mutex();

    /// \brief Destructor.
    ///
    /// Destroys the mutex. It is not allowed to destroy a mutex which is
    /// currently locked. This means a Locker created with this Mutex must
    /// never live longer than the Mutex itself.
    ~Mutex();

    /// \brief This holds a lock on a Mutex.
    ///
    /// To lock a mutex, create a locker. It'll get unlocked when the locker
    /// is destroyed.
    ///
    /// If you create the locker on the stack or using some other "garbage
    /// collecting" mechanism (auto_ptr, for example), it ensures exception
    /// safety with regards to the mutex - it'll get released on the exit
    /// of function no matter by what means.
    class Locker : public boost::noncopyable {
    public:
        /// \brief Constructor.
        ///
        /// Locks the mutex. May block for extended period of time.
        ///
        /// \throw isc::InvalidOperation when OS reports error. This usually
        ///     means an attempt to use the mutex in a wrong way (locking
        ///     a mutex second time from the same thread, for example).
        Locker(Mutex& mutex) :
            mutex_(NULL)
        {
            // Set the mutex_ after we acquire the lock. This is because of
            // exception safety. If lock() throws, it didn't work, so we must
            // not unlock when we are destroyed. In such case, mutex_ is
            // NULL and checked in the destructor.
            mutex.lock();
            mutex_ = &mutex;
        }

        /// \brief Destructor.
        ///
        /// Unlocks the mutex.
        ///
        /// \throw isc::InvalidOperation when OS reports error. This usually
        ///     means an attempt to use the mutex in a wrong way (unlocking
        ///     a mutex belonging to a differen thread).
        ~Locker() {
            if (mutex_ != NULL) {
                mutex_->unlock();
            }
        }
    private:
        Mutex* mutex_;
    };
    /// \brief If the mutex is currently locked
    ///
    /// This is debug aiding method only. And it might be unavailable in
    /// non-debug build (because keeping the state might be needlesly
    /// slow).
    ///
    /// \todo Disable in non-debug build
    bool locked() const;
private:
    class Impl;
    Impl* impl_;
    void lock();
    void unlock();
};


}
}
}

#endif
