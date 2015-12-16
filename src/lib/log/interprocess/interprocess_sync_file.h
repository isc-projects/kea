// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef INTERPROCESS_SYNC_FILE_H
#define INTERPROCESS_SYNC_FILE_H

#include <log/interprocess/interprocess_sync.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace log {
namespace interprocess {

/// \brief InterprocessSyncFileError
///
/// Exception that is thrown if it's not possible to open the
/// lock file.
class InterprocessSyncFileError : public Exception {
public:
    InterprocessSyncFileError(const char* file, size_t line,
                              const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief File-based Interprocess Sync Class
///
/// This class specifies a concrete implementation for a file-based
/// interprocess synchronization mechanism. Please see the
/// InterprocessSync class documentation for usage.
///
/// An InterprocessSyncFileError exception may be thrown if there is an
/// issue opening the lock file.
///
/// Lock files are created typically in the local state directory
/// (var). They are typically named like "<task_name>_lockfile".
/// This implementation opens lock files lazily (only when
/// necessary). It also leaves the lock files lying around as multiple
/// processes may have locks on them.
class InterprocessSyncFile : public InterprocessSync {
public:
    /// \brief Constructor
    ///
    /// Creates a file-based interprocess synchronization object
    ///
    /// \param task_name Name of the synchronization task. This has to be
    /// identical among the various processes that need to be
    /// synchronized for the same task.
    InterprocessSyncFile(const std::string& task_name) :
        InterprocessSync(task_name), fd_(-1)
    {}

    /// \brief Destructor
    virtual ~InterprocessSyncFile();

protected:
    /// \brief Acquire the lock (blocks if something else has acquired a
    /// lock on the same task name)
    ///
    /// \return Returns true if the lock was acquired, false otherwise.
    bool lock();

    /// \brief Try to acquire a lock (doesn't block)
    ///
    /// \return Returns true if the lock was acquired, false otherwise.
    bool tryLock();

    /// \brief Release the lock
    ///
    /// \return Returns true if the lock was released, false otherwise.
    bool unlock();

private:
    bool do_lock(int cmd, short l_type);

    int fd_; ///< The descriptor for the open file
};

} // namespace interprocess
} // namespace log
} // namespace isc

#endif // INTERPROCESS_SYNC_FILE_H
