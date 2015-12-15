// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_THREAD_SYNC_H
#define KEA_THREAD_SYNC_H

#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

#include <cstdlib> // for NULL.

namespace isc {
namespace util {
namespace thread {
class CondVar;

/// \brief Mutex with very simple interface
///
/// Since mutexes are very system dependent, we create our own wrapper around
/// whatever is available on the system and hide it.
///
/// To use this mutex, create it and then lock and unlock it by creating the
/// Mutex::Locker object.
///
/// Also, as mutex is a low-level system object, an error might happen at any
/// operation with it. We convert many errors to the isc::InvalidOperation,
/// since the errors usually happen only when used in a wrong way. Any methods
/// or constructors in this class can throw. Allocation errors are converted
/// to std::bad_alloc (for example when OS-dependent limit of mutexes is
/// exceeded). Some errors which usually mean a programmer error abort the
/// program, since there could be no safe way to recover from them.
///
/// The current interface is somewhat minimalist. If we ever need more, we
/// can add it later.
class Mutex : boost::noncopyable {
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
    class Locker : boost::noncopyable {
    public:
        /// \brief Exception thrown when the mutex is already locked and
        ///     a non-blocking locker is attempted around it.
        struct AlreadyLocked : public isc::InvalidParameter {
            AlreadyLocked(const char* file, size_t line, const char* what) :
                isc::InvalidParameter(file, line, what)
            {}
        };

        /// \brief Constructor.
        ///
        /// Locks the mutex. May block for extended period of time if
        /// \c block is true.
        ///
        /// \throw isc::InvalidOperation when OS reports error. This usually
        ///     means an attempt to use the mutex in a wrong way (locking
        ///     a mutex second time from the same thread, for example).
        /// \throw AlreadyLocked if \c block is false and the mutex is
        ///     already locked.
        Locker(Mutex& mutex, bool block = true) :
            mutex_(mutex)
        {
            if (block) {
                mutex.lock();
            } else {
                if (!mutex.tryLock()) {
                    isc_throw(AlreadyLocked, "The mutex is already locked");
                }
            }
        }

        /// \brief Destructor.
        ///
        /// Unlocks the mutex.
        ~Locker() {
            mutex_.unlock();
        }
    private:
        Mutex& mutex_;
    };
    /// \brief If the mutex is currently locked
    ///
    /// This is debug aiding method only. And it might be unavailable in
    /// non-debug build (because keeping the state might be needlessly
    /// slow).
    ///
    /// \todo Disable in non-debug build
    bool locked() const;

private:
    /// \brief Lock the mutex
    ///
    /// This method blocks until the mutex can be locked.
    void lock();

    /// \brief Try to lock the mutex
    ///
    /// This method doesn't block and returns immediately with a status
    /// on whether the lock operation was successful.
    ///
    /// \return true if the lock was successful, false otherwise.
    bool tryLock();

    /// \brief Unlock the mutex
    void unlock();

private:
    friend class CondVar;

    // Commonly called after acquiring the lock, checking and updating
    // internal state for debug.
    //
    // Note that this method is only available when the build is
    // configured with debugging support.
    void postLockAction();

    // Commonly called before releasing the lock, checking and updating
    // internal state for debug.
    //
    // If throw_ok is true, it throws \c isc::InvalidOperation when the check
    // fails; otherwise it aborts the process.  This parameter must be set
    // to false if the call to this shouldn't result in an exception (e.g.
    // when called from a destructor).
    //
    // Note that this method is only available when the build is
    // configured with debugging support.
    void preUnlockAction(bool throw_ok);

    class Impl;
    Impl* impl_;
};

/// \brief Encapsulation for a condition variable.
///
/// This class provides a simple encapsulation of condition variable for
/// inter-thread synchronization.  It has similar but simplified interface as
/// that for \c pthread_cond_ variants.
///
/// It uses the \c Mutex class object for the mutex used with the condition
/// variable.  Since for normal applications the internal \c Mutex::Locker
/// class is the only available interface to acquire a lock, sample code
/// for waiting on a condition variable would look like this:
/// \code
/// CondVar cond;
/// Mutex mutex;
/// {
///     Mutex::Locker locker(mutex);
///     while (some_condition) {
///         cond.wait(mutex);
///     }
///     // do something under the protection of locker
/// }   // lock is released here
/// \endcode
/// Note that \c mutex passed to the \c wait() method must be the same one
/// used to construct the \c locker.
///
/// Right now there is no equivalent to pthread_cond_broadcast() or
/// pthread_cond_timedwait() in this class, because this class was meant
/// for internal development of BIND 10 and we don't need these at the
/// moment.  If and when we need these interfaces they can be added at that
/// point. Also, Kea likely to not use threading model, so the usefulness
/// of this class is uncertain.
///
/// \note This class is defined as a friend class of \c Mutex and directly
/// refers to and modifies private internals of the \c Mutex class.  It breaks
/// the assumption that the lock is only acquired or released via the
/// \c Locker class and breaks other integrity assumption on \c Mutex,
/// thereby making it more fragile, but we couldn't find other way to
/// implement a safe and still simple realization of condition variables.
/// So, this is a kind of compromise.  If this class is needed to be
/// extended, first consider a way to use public interfaces of \c Mutex;
/// do not easily rely on the fact that this class is a friend of it.
class CondVar : boost::noncopyable {
public:
    /// \brief Constructor.
    ///
    /// \throw std::bad_alloc memory allocation failure
    /// \throw isc::Unexpected other unexpected shortage of system resource
    CondVar();

    /// \brief Destructor.
    ///
    /// An object of this class must not be destroyed while some thread
    /// is waiting on it.  If this condition isn't met the destructor will
    /// terminate the program.
    ~CondVar();

    /// \brief Wait on the condition variable.
    ///
    /// This method works like \c pthread_cond_wait().  For mutex it takes
    /// an \c Mutex class object.  A lock for the mutex must have been
    /// acquired.  If this condition isn't met, it can throw an exception
    /// (in the debug mode build) or result in undefined behavior.
    ///
    /// The lock will be automatically released within this method, and
    /// will be re-acquired on the exit of this method.
    ///
    /// \throw isc::InvalidOperation mutex isn't locked
    /// \throw isc::BadValue mutex is not a valid \c Mutex object
    ///
    /// \param mutex A \c Mutex object to be released on wait().
    void wait(Mutex& mutex);

    /// \brief Unblock a thread waiting for the condition variable.
    ///
    /// This method wakes one of other threads (if any) waiting on this object
    /// via the \c wait() call.
    ///
    /// This method never throws; if some unexpected low level error happens
    /// it terminates the program.
    void signal();
private:
    class Impl;
    Impl* impl_;
};

} // namespace thread
} // namespace util
} // namespace isc

#endif

// Local Variables:
// mode: c++
// End:
