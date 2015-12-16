// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef INTERPROCESS_SYNC_NULL_H
#define INTERPROCESS_SYNC_NULL_H

#include <log/interprocess/interprocess_sync.h>

namespace isc {
namespace log {
namespace interprocess {

/// \brief Null Interprocess Sync Class
///
/// This class specifies a concrete implementation for a null (no effect)
/// interprocess synchronization mechanism. Please see the
/// InterprocessSync class documentation for usage.
class InterprocessSyncNull : public InterprocessSync {
public:
    /// \brief Constructor
    ///
    /// Creates a null interprocess synchronization object
    ///
    /// \param task_name Name of the synchronization task. This has to be
    /// identical among the various processes that need to be
    /// synchronized for the same task.
    InterprocessSyncNull(const std::string& task_name) :
        InterprocessSync(task_name)
    {}

    /// \brief Destructor
    virtual ~InterprocessSyncNull();

protected:
    /// \brief Acquire the lock (never blocks)
    ///
    /// \return Always returns true
    bool lock();

    /// \brief Try to acquire a lock (doesn't block)
    ///
    /// \return Always returns true
    bool tryLock();

    /// \brief Release the lock
    ///
    /// \return Always returns true
    bool unlock();
};

} // namespace interprocess
} // namespace log
} // namespace isc

#endif // INTERPROCESS_SYNC_NULL_H
