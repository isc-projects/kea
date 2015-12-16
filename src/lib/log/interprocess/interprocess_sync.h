// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef INTERPROCESS_SYNC_H
#define INTERPROCESS_SYNC_H

#include <string>

namespace isc {
namespace log {
namespace interprocess {

class InterprocessSyncLocker; // forward declaration

/// \brief Interprocess Sync Class
///
/// This class specifies an interface for mutual exclusion among
/// co-operating processes. This is an abstract class and a real
/// implementation such as InterprocessSyncFile should be used
/// in code. Usage is as follows:
///
/// 1. Client instantiates a sync object of an implementation (such as
/// InterprocessSyncFile).
/// 2. Client then creates an automatic (stack) object of
/// InterprocessSyncLocker around the sync object. Such an object
/// destroys itself and releases any acquired lock when it goes out of extent.
/// 3. Client calls lock() method on the InterprocessSyncLocker.
/// 4. Client performs task that needs mutual exclusion.
/// 5. Client frees lock with unlock(), or simply returns from the basic
/// block which forms the scope for the InterprocessSyncLocker.
///
/// NOTE: All implementations of InterprocessSync should keep the
/// is_locked_ member variable updated whenever their
/// lock()/tryLock()/unlock() implementations are called.
class InterprocessSync {
  // InterprocessSyncLocker is the only code outside this class that
  // should be allowed to call the lock(), tryLock() and unlock()
  // methods.
  friend class InterprocessSyncLocker;

public:
    /// \brief Constructor
    ///
    /// Creates an interprocess synchronization object
    ///
    /// \param task_name Name of the synchronization task. This has to be
    /// identical among the various processes that need to be
    /// synchronized for the same task.
    InterprocessSync(const std::string& task_name) :
        task_name_(task_name), is_locked_(false)
    {}

    /// \brief Destructor
    virtual ~InterprocessSync() {}

protected:
    /// \brief Acquire the lock (blocks if something else has acquired a
    /// lock on the same task name)
    ///
    /// \return Returns true if the lock was acquired, false otherwise.
    virtual bool lock() = 0;

    /// \brief Try to acquire a lock (doesn't block)
    ///
    /// \return Returns true if the lock was acquired, false otherwise.
    virtual bool tryLock() = 0;

    /// \brief Release the lock
    ///
    /// \return Returns true if the lock was released, false otherwise.
    virtual bool unlock() = 0;

    const std::string task_name_; ///< The task name
    bool is_locked_;              ///< Is the lock taken?
};

/// \brief Interprocess Sync Locker Class
///
/// This class is used for making automatic stack objects to manage
/// locks that are released automatically when the block is exited
/// (RAII). It is meant to be used along with InterprocessSync objects. See
/// the description of InterprocessSync.
class InterprocessSyncLocker {
public:
    /// \brief Constructor
    ///
    /// Creates a lock manager around a interprocess synchronization object
    ///
    /// \param sync The sync object which has to be locked/unlocked by
    /// this locker object.
    InterprocessSyncLocker(InterprocessSync& sync) :
        sync_(sync)
    {}

    /// \brief Destructor
    ~InterprocessSyncLocker() {
        if (isLocked())
            unlock();
    }

    /// \brief Acquire the lock (blocks if something else has acquired a
    /// lock on the same task name)
    ///
    /// \return Returns true if the lock was acquired, false otherwise.
    bool lock() {
        return (sync_.lock());
    }

    /// \brief Try to acquire a lock (doesn't block)
    ///
    /// \return Returns true if a new lock could be acquired, false
    ///         otherwise.
    bool tryLock() {
        return (sync_.tryLock());
    }

    /// \brief Check if the lock is taken
    ///
    /// \return Returns true if a lock is currently acquired, false
    ///         otherwise.
    bool isLocked() const {
        return (sync_.is_locked_);
    }

    /// \brief Release the lock
    ///
    /// \return Returns true if the lock was released, false otherwise.
    bool unlock() {
        return (sync_.unlock());
    }

protected:
    InterprocessSync& sync_; ///< Ref to underlying sync object
};

} // namespace interprocess
} // namespace log
} // namespace isc

#endif // INTERPROCESS_SYNC_H
